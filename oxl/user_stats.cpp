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

//#define EARLY_BREAK 10000

using namespace std;

typedef pair<double,double> PD;
typedef pair<int,int> PI;

struct Impression {
  long time;
  int month, day, hour, minute, second;
  bool isFirstMessage;
  // Ignore device (don't have time for this right now).
  int origin; // See ORIGIN_* enum ^^
  int adID;
  // Ignore image count for now.
  int interactions; // Sum impressions, views and messages (No time for better analysis for now)

  bool operator<(const Impression &b) const {
    return time < b.time;
  }
};

struct User {
  PD lastPosition;
  double maxViewDist;
  vector<Impression> impressions;
  vector<int> recommendations;
};

struct Ad {
  int adID, sellerID, price;
  long creationTime;
  string title, desc;
  vector<int> keywords; // No description, no source, title -> keywords
  PD position;
  bool enabled;
};

std::ostream& operator<<(std::ostream& os, const Ad& a) {
  os << " Title '" << a.title << "', description '" << a.desc << "'";
  os << " Ad ID " << a.adID << ", seller ID " << a.sellerID << ", Price " << a.price << " Created " << a.creationTime << ", at (" << a.position.first << "," << a.position.second << ")";
  if(a.enabled)
    os << " ENABLED";
  else
    os << " DISABLED";
  return os;
}

struct Category {
  map<int,Ad> adMap; // id -> ad
  map<int,vector<int> > keyWordMap;
  vector<PI> adToRecommendations;
  map<int,int> adRecommendationsCounts; // For top ten ads 
  vector<int> topTenAds;

  void setTopAds() {
    vector<PI> scoreToAd;
    for(map<int,int>::const_iterator it = adRecommendationsCounts.begin(); it != adRecommendationsCounts.end(); ++it) {
      scoreToAd.push_back(PI(-it->second, it->first));
    }
    sort(scoreToAd.begin(), scoreToAd.end());
    for(unsigned int i = 0; i < scoreToAd.size(); ++i)
      topTenAds.push_back(scoreToAd[i].second);
  }
};

// Taken from Java:
int hashCode(char *s, int size) {
  int h = 0;
  for (int i = 0; i < size; i++) {
    h = 31 * h + s[i];
  }
  return h;
}

void getKeywords(string &line, vector<int> &kw) {
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
	kw.push_back(hashCode(w, j));
      }
      j = 0;
    }
  }
  if(j > 3) {
    w[j++] = '\0';
    kw.push_back(hashCode(w, j));
  }
}

double distSq(PD a, PD b) {
  double dx = a.first-b.first;
  double dy = a.second-b.second;
  return dx*dx+dy*dy;
}

PD getAdPosition(int adID, Category *cats, int const * const categoryMap, map<int,int> &adToCat) {
  if(adToCat.find(adID) == adToCat.end())
    return PD(0,0);
  Category &c = cats[categoryMap[adToCat[adID]]];
  return c.adMap[adID].position;
}

void readUserDataCsv(map<int,User*> &userMap, vector<PI> &alsoViewed, Category *cats, int const * const categoryMap, map<int,int> &adToCat) {
  string line;

  ifstream file;
  file.open("user_data.csv");

  int lines = 0;

  int prevAdID = -1;
  getline(file, line); // Header
  while(getline(file, line, ',')) {
    if(lines % 10000 == 0)
      cerr << ":";
    #ifdef EARLY_BREAK
    if(lines > EARLY_BREAK)
      break;
    #endif
    ++lines;
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
    //cerr << "User id " << id << endl;
    // event:
    getline(file, line, ',');
    bool isFirstMessage = line[1] == 'f';
    //cerr << "First message: " << isFirstMessage << endl;
    // Channel (ignore for now:
    getline(file, line, ',');
    // User position:
    double lat, lon;
    getline(file, line, ',');
    sscanf(&(line.c_str()[1]), "%lf", &lat);    
    getline(file, line, ',');
    sscanf(&(line.c_str()[1]), "%lf", &lon);    
    //cerr << "Position: " << lat << ", " << lon << endl;

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
    else
      cerr << "Unknown origin: " << line << endl;
    
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
    //cerr << "Rest: " << adId <<", "<< images<<", "<< impressions<<", "<< views<<", "<< messages << endl;

    // Update alsoViewed:
    if(prevAdID != -1 && prevAdID != adID) {
      alsoViewed.push_back(PI(prevAdID, adID));
      alsoViewed.push_back(PI(adID, prevAdID));
    }
    prevAdID = adID;

    // Update last position:
    User *user;
    if(userMap.find(id) == userMap.end()) {
      user = new User;
      userMap[id] = user;
    }
    else
      user = userMap[id];
    user->lastPosition = PD(lat,lon);

    Impression im;
    im.time = time;
    im.month = month;
    im.day = day;
    im.hour = hour;
    im.minute = minute;
    im.isFirstMessage = isFirstMessage;
    im.origin = origin;
    im.adID = adID;
    im.interactions = impressions+views+messages;

    user->impressions.push_back(im);
  }

  // Find maxViewDist for all users:
  cerr << "Finding max dist view for all users." << endl;
  for(map<int,User*>::iterator it = userMap.begin(); it != userMap.end(); ++it) {
    User *user = it->second;

    // Sort impressions by date:
    sort(user->impressions.begin(), user->impressions.end());

    // Find maximal allowed dist for ads by considering the last 5 impressions:
    PD userPos = user->lastPosition;
    user->maxViewDist = 0;
    int cnt = 0;
    for(vector<Impression>::reverse_iterator it2 = user->impressions.rbegin(); it2 != user->impressions.rend() && ++cnt <= 5; ++it2) {
      double dist = distSq(userPos, getAdPosition(it2->adID, cats, categoryMap, adToCat));
      if(dist > user->maxViewDist)
	user->maxViewDist = dist;
    }    
  }

  sort(alsoViewed.begin(), alsoViewed.end());
  cout << lines << " lines read from user_data.csv. " << userMap.size() << " users." << endl;
  file.close();
}

void readUserMessagesCsv(map<int,User*> &userMap, Category *cats, int const * const categoryMap, map<PI,vector<int> > &fromOxl) {
  ifstream file;
  file.open("user_messages.csv");

  int lines = 0;

  string line;
  getline(file, line); // Header
  while(getline(file, line, ',')) {
    ++lines;
    if(lines%1000 == 0)
      cerr << ",";
    // Read user id:
    int user;
    sscanf(line.c_str(), "%d", &user);
    if(userMap.find(user) == userMap.end()) {
      getline(file, line); // Rest of line.      
      continue;
    }

    // Read category id:
    getline(file, line, ',');
    int cat;
    sscanf(line.c_str(), "%d", &cat);
    // Ads:
    getline(file, line, '[');
    getline(file, line);
    stringstream ss; ss << line;

    User *u = userMap[user];
    vector<Impression> &impressions = u->impressions;
    vector<int> v; 

    int recommendedAdID;
    while(ss >> recommendedAdID) {
      Category &category = cats[categoryMap[cat]];
      for(vector<Impression>::const_iterator it = impressions.begin(); it != impressions.end(); ++it) {
	category.adToRecommendations.push_back(PI(it->adID, recommendedAdID));
      }
      u->recommendations.push_back(recommendedAdID);

      category.adRecommendationsCounts[recommendedAdID]++;

      ss >> line; // ","      
      v.push_back(recommendedAdID);
    }

    fromOxl[PI(user, cat)] = v;;
  }

  cerr << "Setting top recommended ads!" << endl;
  for(int i = 0; i < 10; ++i) {
    cats[i].setTopAds();
    sort(cats[i].adToRecommendations.begin(), cats[i].adToRecommendations.end());
  }

  cout << lines << " lines read from user_messages.csv." << endl;  
  file.close();
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

void addPreviouslySeenAds(unsigned int MAX, int cat, int user, map<int,User*> &userMap, map<int,int> &adToCat, set<int> &enabledAds, vector<int> &ads) {
  if(ads.size() >= MAX)
    return;

  User *u = userMap[user];
  vector<Impression> &impressions = u->impressions;
  
  set<int> seen;
  for(vector<Impression>::reverse_iterator it = impressions.rbegin(); it != impressions.rend(); ++it) {	
    Impression &i = *it;
    int a = i.adID;
    if(adToCat[a] != cat)
      continue; // Wrong category.
    if(seen.find(a) != seen.end())
      continue; // Already added
    if(enabledAds.find(a) == enabledAds.end())
      continue;
    ads.push_back(a);
    seen.insert(a);
    if(ads.size() >= MAX)
      break;
  }
}

void addTopForCategory(int user, int cat, map<int,User*> &userMap, Category *cats, int *categoryMap, map<int,int> &adToCat, vector<int> &ads) {
  vector<int> &TT = cats[categoryMap[cat]].topTenAds;
  
  User *u = NULL;
  if(user != -1)
    u = userMap[user];

  set<int> seen;
  for(vector<int>::const_iterator it = ads.begin(); it != ads.end(); ++it)
    seen.insert(*it);
  for(vector<int>::const_iterator it = TT.begin(); it != TT.end(); ++it) {
    int aa = *it;
    if(seen.find(aa) != seen.end())
      continue;
    if(u != NULL && distSq(u->lastPosition, getAdPosition(aa, cats, categoryMap, adToCat)) > u->maxViewDist)
      continue;
    ads.push_back(aa);
    seen.insert(aa);
    if(ads.size() >= 10)
      break;
  }
}

/*
 If user A has seen ad X and is served Y, then B seeing X should also get Y 
*/
void addSimilarlyRecommendedAds(unsigned int MAX, int cat, int user, map<int,User*> &userMap, Category *cats, int *categoryMap, map<int,int> &adToCat, vector<int> &ads) {
  if(ads.size() >= MAX)
    return;

  User *u = userMap[user];
  vector<Impression> &impressions = u->impressions; // Already seen impressions.

  // Find ads which have been recommended based on what we have seen:
  map<int,int> recommendationHits;

  Category &c = cats[categoryMap[cat]];
  
  set<int> seen;
  //int xx = 0;
  for(vector<Impression>::reverse_iterator it = impressions.rbegin(); it != impressions.rend(); ++it) {	
    Impression &i = *it;
    int a = i.adID;
    if(seen.find(a) != seen.end())
      continue; // Already added
    seen.insert(a);

    // Find all recommended for this ad:
    vector<PI>::const_iterator it2 = lower_bound(c.adToRecommendations.begin(), c.adToRecommendations.end(), PI(a,-1));
    while(it2 != c.adToRecommendations.end() && it2->first == a) {
      int aa = it2->second;
      if(distSq(u->lastPosition, getAdPosition(aa, cats, categoryMap, adToCat)) <= u->maxViewDist)
	recommendationHits[aa]++;
      ++it2;
    }
  }

  // Take top:
  vector<PI> scoreToAd;
  for(map<int,int>::const_iterator it = recommendationHits.begin(); it != recommendationHits.end(); ++it) {
    scoreToAd.push_back(PI(-it->second, it->first));
  }
  sort(scoreToAd.begin(), scoreToAd.end());
  for(vector<PI>::const_iterator it = scoreToAd.begin(); ads.size() < MAX && it != scoreToAd.end(); ++it)
    ads.push_back(it->second);
}

void addAlsoViewed(unsigned int MAX, int cat, int user, vector<PI> &alsoViewed, map<int,User*> &userMap, Category *cats, int *categoryMap, map<int,int> &adToCat, set<int> &enabledAds, vector<int> &ads) {
  if(ads.size() >= MAX)
    return;

  User *u = userMap[user];
  vector<Impression> &impressions = u->impressions; // Already seen impressions.

  // Find ads which have been recommended based on what we have seen:
  map<int,int> recommendationHits;

  set<int> seen;
  //int xx = 0;
  for(vector<Impression>::reverse_iterator it = impressions.rbegin(); it != impressions.rend(); ++it) {	
    Impression &i = *it;
    int a = i.adID;
    if(seen.find(a) != seen.end())
      continue; // Already added
    seen.insert(a);

    // Find all recommended for this ad:
    vector<PI>::const_iterator it2 = lower_bound(alsoViewed.begin(), alsoViewed.end(), PI(a,-1));
    while(it2 != alsoViewed.end() && it2->first == a) {
      int aa = it2->second;
      ++it2;
      if(adToCat[aa] != cat)
	continue;
      if(enabledAds.find(aa) == enabledAds.end())
	continue;
      if(distSq(u->lastPosition, getAdPosition(aa, cats, categoryMap, adToCat)) > u->maxViewDist)
	continue;

      recommendationHits[aa]++;
    }
  }

  // Take top:
  vector<PI> scoreToAd;
  for(map<int,int>::const_iterator it = recommendationHits.begin(); it != recommendationHits.end(); ++it) {
    scoreToAd.push_back(PI(-it->second, it->first));
  }
  sort(scoreToAd.begin(), scoreToAd.end());
  for(vector<PI>::const_iterator it = scoreToAd.begin(); ads.size() < MAX && it != scoreToAd.end(); ++it)
    ads.push_back(it->second);
}

void readAdsDataCsv(Category *cats, int const * const categoryMap, map<int,int> &adToCat, set<int> &enabledAds) {
  cerr << "Reading ads_data.csv" << endl;
  string line;

  ifstream file;
  file.open("ads_data.csv");

  int lines = 0;

  getline(file, line); // Header line

  while(getline(file, line, ',')) {
    if(lines % 10000 == 0)
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
    //cerr << "Read time " << month <<", "<< day<<", "<< hour<<", "<< minute<<", "<< second << endl;

    // Read title
    getline(file, line, '"');
    string title;
    getline(file, title, '"');
    getline(file, line, ',');

    string desc;
    stringstream ss;
    // Ignore description
    do {
      ss << line;
      desc = line;
      getline(file, line, ',');
      ss << line;
      getline(file, line, '"');
      ss << line;
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
    if(enabled)
      enabledAds.insert(adID);

    adToCat[adID] = cat;
    if(cat < 0 || cat > 900)
      cerr << "Unknown category: " << cat << ", title " << title << ", line " << lines << ", desc: " << desc << ", adID=" << adID << endl;
    int catID = categoryMap[cat];
    if(catID == -1)
      cerr << "Unknown category: " << cat << endl;
    Category &category = cats[catID];
    Ad ad;
    ad.adID = adID;
    ad.sellerID = sellerID;
    ad.price = price;
    ad.creationTime = time;
    ad.position = PD(lat, lon);
    ad.enabled = enabled;
    getKeywords(title, ad.keywords);
    ad.title = title;
    ad.desc = ss.str();

    // Update map<int,vector<int> > &keyWordMap:
    if(enabled) {
      map<int,vector<int> > &keyWordMap = category.keyWordMap;
      for(unsigned int j = 0; j < ad.keywords.size(); ++j) {
	int &kw = ad.keywords[j];
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
  vector<int> keywords; // No description, no source, title -> keywords
  PD position;
  bool enabled;

 Category::map<int,Ad> adMap; // id -> ad, , map<int,vector<int> > &keyWordMap
*/
void addAdsWithMatchingKeywords(int cat, int user, map<int,User*> &userMap, 
				Category *cats, int const * const categoryMap, map<int,int> &adToCat, 
				vector<int> &ads) {
  if(ads.size() >= 10)
    return;

  // 0) Find all viewed ads so they don't accidentally get put into "ads":
  User *u = userMap[user];
  set<int> viewedAds;
  vector<Impression> &impressions = u->impressions;
  for(vector<Impression>::const_iterator it = impressions.begin(); it != impressions.end(); ++it) {
    if(viewedAds.find(it->adID) != viewedAds.end())
      continue;
    viewedAds.insert(it->adID);
  }  

  // 0.1) Find keyword map:
  Category &c = cats[categoryMap[cat]];

  // 0.2) Maintain distance map:
  map<int,double> dists;
  double maxDist = u->maxViewDist;

  // 1) Go through ads viewed by user in order to gather keyword sets
  map<int,int> relatedAds; // adID -> score
  for(set<int>::const_iterator it = viewedAds.begin(); it != viewedAds.end(); ++it) {
    int baseAdID = *it;
    if(adToCat.find(baseAdID) == adToCat.end()) {
      cerr << "Unknown ad ID " << baseAdID << " seen by user " << user << endl;
      continue;
    }
    int baseCatID = adToCat[baseAdID];
    int baseCatIndex = categoryMap[baseCatID];
    Category &baseCat = cats[baseCatIndex];
    Ad &ad = baseCat.adMap[baseAdID];
    vector<int> &baseKeywords = ad.keywords;

    // 1.1) For each keyword set: Find related ads
    map<int,int> relatedAddedNow; // adID -> count seen for this keyword set
    for(vector<int>::const_iterator it2 = baseKeywords.begin(); it2 != baseKeywords.end(); ++it2) {
      int kw = *it2;
      vector<int> &matches = c.keyWordMap[kw];
      for(vector<int>::const_iterator it3 = matches.begin(); it3 != matches.end(); ++it3) {
	if(viewedAds.find(*it3) != viewedAds.end()) {
	  continue;
	}
	if(dists.find(*it3) == dists.end()) {
	  // Add ad dist to dists:
	  dists[*it3] = distSq(u->lastPosition, ad.position);
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
  vector<PI> ret;
  for(map<int,int>::const_iterator it = relatedAds.begin(); it != relatedAds.end(); ++it) {
    ret.push_back(PI(-it->second, it->first));
  }
  sort(ret.begin(), ret.end());
  bool first = true;
  for(vector<PI>::const_iterator it = ret.begin(); it != ret.end(); ++it) {
    if(first || dists[it->second] <= maxDist)
      ads.push_back(it->second);

    first = false;
    if(ads.size() >= 10)
      break;
  }
}

void report(int userID, int catID, map<int,User*> &userMap, Category *cats, int const * const categoryMap, map<int,int> &adToCat, map<PI,vector<int> > &fromOxl) {
  string line;

  ofstream os;
  stringstream ss;
  ss << "oxlinfo/" << userID << "_" << catID << ".oxlinfo";
  os.open(ss.str().c_str());

  os << "Reporting for user " << userID << " and category " << catID << endl << endl;

  if(fromOxl.find(PI(userID,catID)) != fromOxl.end()) {
    os << "OXL recommends the following ads:" << endl;
    vector<int> &ads = fromOxl[PI(userID,catID)];
    for(vector<int>::const_iterator it = ads.begin(); it != ads.end(); ++it) {
      int adID = *it;
      int catCnt = categoryMap[catID];
      Category &cat = cats[catCnt];
      //  map<int,Ad*> adMap; // id -> ad
      Ad ad = cat.adMap[adID];
      os << " " << ad << endl;
    }
  }
  else
    os << "This data is not in user_messages.csv" << endl;      

  os << endl << endl << "These are the matching lines from user_data.csv:" << endl;

  User *u = userMap[userID];
  for(vector<Impression>::iterator it = u->impressions.begin(); it != u->impressions.end(); ++it) {    
    Impression &i = *it;
    os << endl << "Date: 2017-" << i.month << "-" << i.day << " " << i.hour << ":" << i.minute << ":" << i.second;

    // event:
    if(i.isFirstMessage)
      os << " First";
    else
      os << " View";

    os << ", origin " << i.origin;
    
    os << ", Add ID: " << i.adID <<", impressions(incl. views and messages): "<< i.interactions << endl;    

    int catID = adToCat[i.adID];
    int catCnt = categoryMap[catID];
    Category &cat = cats[catCnt];
    Ad &ad = cat.adMap[i.adID];
    os << " Category " << catID << " " << ad << endl;
  }
  os << endl << "In total: " << u->impressions.size() << " impressions for user " << userID << endl;
  os.close();
  cout << "Results are in file: " << ss.str() << endl;
}

int main() {
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
  Category cats[10];
  map<int,int> adToCat; // adID -> cat (800, 806, etc.)
  set<int> enabledAds;
  readAdsDataCsv(cats, categoryMap, adToCat, enabledAds);

  // Read user_data.csv for user map.
  map<int,User*> userMap;
  vector<PI> alsoViewed; // ad -> also viewed ad
  readUserDataCsv(userMap, alsoViewed, cats, categoryMap, adToCat);

  // Read user_messages.csv for hints:
  map<PI,vector<int> > fromOxl;
  readUserMessagesCsv(userMap, cats, categoryMap, fromOxl);

  for(map<PI,vector<int> >::const_iterator it = fromOxl.begin(); it != fromOxl.end(); ++it) {
    report(it->first.first, it->first.second, userMap, cats, categoryMap, adToCat, fromOxl);
  }
  return 0;
}
