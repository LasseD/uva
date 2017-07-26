#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>
#include <string> 
#include <cstring>

#define ORIGIN_BROWSE_SEARCH 0
#define ORIGIN_BROWSE 1
#define ORIGIN_SEARCH 2
#define ORIGIN_NOTIFICATION_CENTER 3
#define ORIGIN_HOME 4
#define ORIGIN_PUSH 5
#define ORIGIN_DRAWER 6
#define ORIGIN_UNKNOWN 7
#define ORIGIN_DEEPLINK 8

using namespace std;

typedef pair<double,double> PD;
typedef pair<int,int> PI;

struct Impression {
  long time;
  bool isFirstMessage;
  // Ignore device (don't have time for this right now).
  int origin; // See ORIGIN_* enum ^^
  int adID;
  // Ignore image count for now.
  int interactions; // Sum impressions, views and messages (No time for better analysis for now)

  Impression() : time(-1), isFirstMessage(false), origin(-1), adID(-1), interactions(-1) {}
  Impression(const Impression &o) : time(o.time), isFirstMessage(o.isFirstMessage), origin(o.origin), adID(o.adID), interactions(o.interactions) {}
  Impression(long time, bool isFirstMessage, int origin, int adID, int interactions) : time(time), isFirstMessage(isFirstMessage), origin(origin), adID(adID), interactions(interactions) {}
};

struct User {
  PD lastPosition;
  vector<Impression> impressions;
};

struct Serving {
  int user;
  vector<int> addIDs;
};

struct Ad {
  int adID, sellerID, price;
  long creationTime;
  vector<string> keywords; // No description, no source, title -> keywords
  PD position;
  bool enabled;
};

std::ostream& operator<<(std::ostream& os, const Ad& a) {
  for(vector<string>::const_iterator it = a.keywords.begin(); it != a.keywords.end(); ++it) {
    cout << *it << " ";
  }
  os << " Ad ID " << a.adID << ", seller " << a.sellerID << ", Price " << a.price << " Created " << a.creationTime << ", at (" << a.position.first << "," << a.position.second << ")";
  if(a.enabled)
    os << " ENABLED";
  else
    os << " DISABLED";
  return os;
}

struct Category {
  map<int,Ad*> adMap; // id -> ad
};

void getKeywords(string &line, vector<string> &kw) {
  transform(line.begin(), line.end(), line.begin(), ::tolower);
  char w[1000];
  int j = 0;
  for(unsigned int i = 0; i < line.size(); ++i) {
    char c = line[i];
    if((c >= '0'&& c <= '9') || (c >= 'a'&& c <= 'z') || (c < 0)) {
      w[j++] = c;
    }
    else {
      if(j > 3) {
	w[j++] = '\0';
	kw.push_back(string(w));
      }
      j = 0;
    }
  }
  if(j > 3) {
    w[j++] = '\0';
    kw.push_back(string(w));
  }
}

void readUserDataCsv(int userID, User* user) {
  string line;

  ifstream file;
  file.open("user_data.csv");

  int lines = 0;

  getline(file, line); // Header
  while(getline(file, line, ',')) {
    // Read time:
    // Timestamp of type "2017-06-30 12:34:56"
    //                   0 2 4 6 8  12  16  18
    int month, day, hour, minute, second;
    sscanf(&(line.c_str()[6]), "%d-%d %d:%d:%d", &month, &day, &hour, &minute, &second);

    long time = month * 32 + day;
    time = 24*time + hour;
    time = 60*time + minute;
    time = 60*time + second;
    // Read user id:
    getline(file, line, ',');
    int id;
    sscanf(&(line.c_str()[1]), "%d", &id);

    if(id != userID) {
      getline(file, line);
      continue;
    }
    ++lines;
    cout << "Date: 2017-" << month << "-" << day << " " << hour << ":" << minute << ":" << second;

    // event:
    getline(file, line, ',');
    bool isFirstMessage = line[1] == 'f';
    if(isFirstMessage)
      cout << " First";
    else
      cout << " View";

    // Channel (ignore for now:
    getline(file, line, ',');
    cout << " " << line;
    // User position:
    double lat, lon;
    getline(file, line, ',');
    sscanf(&(line.c_str()[1]), "%lf", &lat);    
    getline(file, line, ',');
    sscanf(&(line.c_str()[1]), "%lf", &lon);    
    cout << " (" << lat << "," << lon << ")";

    // Origin:
    getline(file, line, ',');
    int origin;
    if(line == "\"browse\"")
      origin = ORIGIN_BROWSE;
    else if(line == "\"browse_search\"")
      origin = ORIGIN_BROWSE_SEARCH;
    else if(line == "\"home\"")
      origin = ORIGIN_HOME;
    else if(line == "\"notification_center\"")
      origin = ORIGIN_NOTIFICATION_CENTER;
    else if(line == "\"search\"")
      origin = ORIGIN_SEARCH;
    else if(line == "\"push\"")
      origin = ORIGIN_PUSH;
    else if(line == "\"drawer\"")
      origin = ORIGIN_DRAWER;
    else if(line == "\"\"")
      origin = ORIGIN_UNKNOWN;
    else if(line == "\"deeplink\"")
      origin = ORIGIN_DEEPLINK;

    cout << " " << line;
    
    // Rest of line:
    int adID;
    float images, impressions, views, messages;
    getline(file, line, ',');
    sscanf(&(line.c_str()[1]), "%d", &adID);    
    getline(file, line, ',');
    sscanf(&(line.c_str()[1]), "%f", &images);    
    getline(file, line, ',');
    sscanf(&(line.c_str()[1]), "%f", &impressions);    
    getline(file, line, ',');
    sscanf(&(line.c_str()[1]), "%f", &views);    
    getline(file, line);
    sscanf(&(line.c_str()[1]), "%f", &messages);    
    cout << " Add ID: " << adID <<", image: "<< images<<", impressions: "<< impressions<<", views: "<< views<<", messages: "<< messages << endl;

    user->lastPosition = PD(lat,lon);
    Impression impression(time, isFirstMessage, origin, adID, impressions+views+messages);
    user->impressions.push_back(impression);
  }
  cout << "TOTAL " << lines << " lines read from user_data.csv." << endl;
  file.close();
}

void readUserMessagesTestCsv(map<int,vector<Serving*> > &categoryHints) {
  string line;

  ifstream file;
  file.open("user_messages.csv");

  int lines = 0;

  getline(file, line); // Header
  while(getline(file, line, ',')) {
    ++lines;
    // Read user id:
    int user;
    sscanf(line.c_str(), "%d", &user);
    // Read category id:
    getline(file, line, ',');
    int cat;
    sscanf(line.c_str(), "%d", &cat);
    //cerr << "User id " << user << ", Category " << cat << endl;
    // Ads:
    getline(file, line, '[');
    getline(file, line);
    stringstream ss; ss << line;
    int adID;
    vector<int> ads;
    while(ss >> adID) {
      ss >> line; // ","
      ads.push_back(adID);
      //cerr << " " << adID << endl;
    }

    if(categoryHints.find(cat) == categoryHints.end()) {
      vector<Serving*> sx;
      categoryHints.insert(make_pair(cat, sx));
    }
    
    vector<Serving*> &servings = categoryHints[cat];

    Serving *serving = new Serving;
    serving->user = user;
    serving->addIDs = ads;
    servings.push_back(serving);
  }
  cout << lines << " lines read from user_data.csv. " << categoryHints.size() << " categories." << endl;  
  file.close();
}

double distSq(PD a, PD b) {
  double dx = a.first-b.first;
  double dy = a.second-b.second;
  return dx*dx+dy*dy;
}

double getLocationDiff(int u1, int u2, map<int,User*> &userMap) {
  if(userMap.find(u1) == userMap.end())
    return 1e12;
  if(userMap.find(u2) == userMap.end())
    return 1e12;
  User *user1 = userMap[u1];
  User *user2 = userMap[u2];
  return distSq(user1->lastPosition, user2->lastPosition);
}

void addAdsByNearbyPeople(int cat, int user, map<int,vector<Serving*> > &categoryHints, map<int,User*> &userMap, vector<int> &ads) {
  if(ads.size() >= 10)
    return;

  vector<Serving*> servings = categoryHints[cat];
  vector<Serving*>::const_iterator it = servings.begin();
  Serving *bestServing = *it;
  double bestDist = getLocationDiff(user, bestServing->user, userMap);
  ++it;
  for(; it != servings.end(); ++it) {	
    Serving *serving = *it;
    double dist = getLocationDiff(user, serving->user, userMap);
    if(dist < bestDist) {
      bestDist = dist;
      bestServing = serving;
    }
  }
  for(vector<int>::const_iterator it = bestServing->addIDs.begin(); it != bestServing->addIDs.end(); ++it) {
    ads.push_back(*it);
    if(ads.size() >= 10)
      return;
  }
}

void addPreviouslySeenAds(int cat, int user, map<int,User*> &userMap, vector<int> &ads) {
  if(ads.size() >= 10)
    return;

  set<int> seen;
  if(userMap.find(user) == userMap.end()) {
    cout << "Unknown user: " << user << endl;
    return;
  }

  User *u = userMap[user];
  vector<Impression> &impressions = u->impressions;
  
  for(vector<Impression>::reverse_iterator it = impressions.rbegin(); it != impressions.rend(); ++it) {	
    Impression &i = *it;
    int a = i.adID;
    if(seen.find(a) != seen.end())
      continue; // Already added
    ads.push_back(a);
    seen.insert(a);
    if(ads.size() >= 10)
      break;
  }
}

void readAdsDataCsv(Category *cats, int const * const categoryMap, map<int,int> &adToCat, map<string,vector<int> > &keyWordMap) {
  cerr << "Reading ads_data.csv" << endl;
  string line;

  ifstream file;
  file.open("ads_data.csv");

  int lines = 0;

  getline(file, line); // Header line

  while(getline(file, line, ',')) {
    if(lines % 1000 == 0)
      cerr << ".";
    #ifdef EARLY_BREAK
    if(lines > EARLY_BREAK)
      break;
    #endif
    ++lines;
    // Read adID, cat, seller:
    int adID, cat, sellerID;
    sscanf(&(line.c_str()[1]), "%d", &adID);
    getline(file, line, ',');
    sscanf(&(line.c_str()[1]), "%d", &cat);
    getline(file, line, ',');
    sscanf(&(line.c_str()[1]), "%d", &sellerID);

    // Read time:
    // Timestamp of type "2017-06-30 12:34:56"
    //                   0 2 4 6 8  12  16  18
    int year, month, day, hour, minute, second;
    getline(file, line, ',');
    sscanf(&(line.c_str()[1]), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);

    long time = year;
    time = time*366 + month;
    time = time*32 + day;
    time = 24*time + hour;
    time = 60*time + minute;
    time = 60*time + second;

    // Read title
    getline(file, line, '"');
    string title;
    getline(file, title, '"');
    getline(file, line, ',');

    string desc;
    // Ignore description
    do {
      desc = line;
      getline(file, line, ',');
      getline(file, line, '"');
    }
    while(!line.empty());

    // Price
    getline(file, line, ',');
    int price;
    sscanf(line.c_str(), "%d", &price);

    // User position:
    double lat, lon;
    getline(file, line, ',');
    sscanf(&(line.c_str()[1]), "%lf", &lat);    
    getline(file, line, ',');
    sscanf(&(line.c_str()[1]), "%lf", &lon);    
    
    // Ignore source
    getline(file, line, ',');
    
    // Enabled
    getline(file, line);
    bool enabled = line[1] == '1';

    adToCat[adID] = cat;
    if(cat < 0 || cat > 900)
      cerr << "Unknown category: " << cat << ", title " << title << ", line " << lines << ", desc: " << desc << ", adID=" << adID << endl;
    int catID = categoryMap[cat];
    if(catID == -1)
      cerr << "Unknown category: " << cat << endl;
    Category &category = cats[catID];
    Ad *ad = new Ad;
    ad->adID = adID;
    ad->sellerID = sellerID;
    ad->price = price;
    ad->creationTime = time;
    ad->position = PD(lat, lon);
    ad->enabled = enabled;
    getKeywords(title, ad->keywords);

    // Update map<string,vector<int> > &keyWordMap:
    if(enabled) {
      for(unsigned int j = 0; j < ad->keywords.size(); ++j) {
	string &kw = ad->keywords[j];
	if(keyWordMap.find(kw) == keyWordMap.end()) {
	  vector<int> empty;
	  keyWordMap[kw] = empty;
	}
	keyWordMap[kw].push_back(adID);
      }
    }

    category.adMap[adID] = ad;
  }
  cout << lines << " lines read from ads_data.csv. " << endl;
  file.close();  
}

/*
  Find all views by user. => keyword list.
  From keyword list: Find all unseen adds and count them.

 Impression::
  long time;
  bool isFirstMessage;
  int origin; // See ORIGIN_* enum ^^
  int adID;
  int interactions; // Sum impressions, views and messages (No time for better analysis for now)
 Ad::
  int adID, sellerID, price;
  long creationTime;
  vector<string> keywords; // No description, no source, title -> keywords
  PD position;
  bool enabled;

 Category::map<int,Ad> adMap; // id -> ad
*/
void reportAdsWithMatchingKeywords(int cat, User *u, 
				Category *cats, int const * const categoryMap, map<int,int> &adToCat, map<string,vector<int> > &keyWordMap) {
  // 0) Find all viewed ads so they don't accidentally get put into "ads":
  cout << endl << "Viewed ads (those from user_data.csv):" << endl;
  set<int> viewedAds;
  vector<Impression> &impressions = u->impressions;
  for(vector<Impression>::const_iterator it = impressions.begin(); it != impressions.end(); ++it) {
    if(viewedAds.find(it->adID) != viewedAds.end())
      continue;
    viewedAds.insert(it->adID);    
    int viewedCatID = adToCat[it->adID];
    int viewedCatCnt = categoryMap[viewedCatID];
    cout << *(cats[viewedCatCnt].adMap[it->adID]) << endl;
  }  

  // 1) Go through ads viewed by user in order to gather keyword sets
  map<int,int> relatedAds; // adID -> score
  for(set<int>::const_iterator it = viewedAds.begin(); it != viewedAds.end(); ++it) {
    int baseAdID = *it;
    if(adToCat.find(baseAdID) == adToCat.end()) {
      cerr << "Unknown ad ID " << baseAdID << endl;
      continue;
    }
    int baseCatID = adToCat[baseAdID];
    int baseCatIndex = categoryMap[baseCatID];
    Category &baseCat = cats[baseCatIndex];
    Ad &ad = *(baseCat.adMap[baseAdID]);
    vector<string> &baseKeywords = ad.keywords;

    // 1.1) For each keyword set: Find related ads
    map<int,int> relatedAddedNow; // adID -> count seen for this keyword set
    for(vector<string>::const_iterator it2 = baseKeywords.begin(); it2 != baseKeywords.end(); ++it2) {
      const string &kw = *it2;
      vector<int> &matches = keyWordMap[kw];
      for(vector<int>::const_iterator it3 = matches.begin(); it3 != matches.end(); ++it3) {
	if(viewedAds.find(*it3) != viewedAds.end()) {
	  continue;
	}
	relatedAddedNow[*it3]++;
      }
    }
    // Update scores:
    for(map<int,int>::const_iterator it2 = relatedAddedNow.begin(); it2 != relatedAddedNow.end(); ++it2) {
      relatedAds[it2->first] += 1 << it2->second;
    }
  }

  // 2: Add most highly scoring ads.
  cout << "Highest scoring ads by keyword matching:" << endl;
  vector<PI> ret;
  for(map<int,int>::const_iterator it = relatedAds.begin(); it != relatedAds.end(); ++it) {
    ret.push_back(PI(-it->second, it->first));
  }
  sort(ret.begin(), ret.end());
  int XX = 1;
  for(vector<PI>::const_iterator it = ret.begin(); it != ret.end(); ++it) {
    int catID = adToCat[it->second];
    if(catID != cat)
      continue;
    int catIndex = categoryMap[catID];
    Ad &ad = *(cats[catIndex].adMap[it->second]);
    cout << XX << ": " << ad << endl;
    if(30 == XX++)
      break;
  }
}

int main() {
  cout << "Please type user ID and category, then press ENTER" << endl << endl;
  int userID, cat; cin >> userID >> cat;

  int categoryMap[890];
  memset(categoryMap, -1, sizeof(categoryMap));
  categoryMap[362] = 0; // Cars
  categoryMap[800] = 1; // Electronics
  categoryMap[806] = 2; // Kitchen
  categoryMap[811] = 3; // Games
  categoryMap[815] = 4; // Clothes and shoes
  categoryMap[853] = 5; // Baby and toys
  categoryMap[859] = 6; // Records
  categoryMap[881] = 7; // Power supplies
  categoryMap[887] = 8; // Etc.
  categoryMap[888] = 9; // Male fashion

  // Read ads_data.csv:
  Category cats[11];
  map<int,int> adToCat; // adID -> cat (800, 806, etc.)
  map<string,vector<int> > keyWordMap;
  readAdsDataCsv(cats, categoryMap, adToCat, keyWordMap);

  // Read user_data.csv for user map.
  map<int,User*> userMap;
  User *user = new User;
  readUserDataCsv(userID, user);

  reportAdsWithMatchingKeywords(cat, user, cats, categoryMap, adToCat, keyWordMap);

  cout << "REPORT DONE FOR USER " << userID << ", CATEGORY " << cat << endl;

  return 0;
}
