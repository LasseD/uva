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
  bool isFirstMessage;
  // Ignore device (don't have time for this right now).
  int origin; // See ORIGIN_* enum ^^
  int adID;
  // Ignore image count for now.
  int interactions; // Sum impressions, views and messages (No time for better analysis for now)

  Impression() : time(-1), isFirstMessage(false), origin(-1), adID(-1), interactions(-1) {}
  Impression(const Impression &o) : time(o.time), isFirstMessage(o.isFirstMessage), origin(o.origin), adID(o.adID), interactions(o.interactions) {}
  Impression(long time, bool isFirstMessage, int origin, int adID, int interactions) : time(time), isFirstMessage(isFirstMessage), origin(origin), adID(adID), interactions(interactions) {}
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
  string title;
  vector<int> keywords; // No description, no source, title -> keywords
  PD position;
  bool enabled;
};

struct Category {
  map<int,Ad> adMap; // id -> ad
  map<int,vector<int> > keyWordMap;
  vector<PI> adToRecommendations;
  map<int,int> adRecommendationsCounts, adImpressionsCounts; // For top ten ads 
  vector<int> topRecAds, topImpAds;

  void setTopAdsRec() {
    vector<PI> scoreToAd;
    for(map<int,int>::const_iterator it = adRecommendationsCounts.begin(); it != adRecommendationsCounts.end(); ++it) {
      scoreToAd.push_back(PI(-it->second, it->first));
    }
    sort(scoreToAd.begin(), scoreToAd.end());
    for(unsigned int i = 0; i < scoreToAd.size(); ++i)
      topRecAds.push_back(scoreToAd[i].second);
    cerr << "Setting top recommended ads. From " << adRecommendationsCounts.size() << ". Best score: " << -scoreToAd[0].first << endl;
  }
  void setTopAdsImp() {
    vector<PI> scoreToAd;
    for(map<int,int>::const_iterator it = adImpressionsCounts.begin(); it != adImpressionsCounts.end(); ++it) {
      scoreToAd.push_back(PI(-it->second, it->first));
    }
    sort(scoreToAd.begin(), scoreToAd.end());
    for(unsigned int i = 0; i < scoreToAd.size(); ++i)
      topImpAds.push_back(scoreToAd[i].second);
    cerr << "Setting top impressions ads. From " << adImpressionsCounts.size() << ". Best score: " << -scoreToAd[0].first << endl;
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
    if(c == '\n')
      break; // No multiline descriptions, please.
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

void readUserDataCsv(map<int,User*> &userMap, vector<PI> &alsoViewed, Category *cats, int const * const categoryMap, map<int,int> &adToCat, set<int> &enabledAds) {
  string line;

  ifstream file;
  file.open("user_data.csv");

  int lines = 0;

  int prevAdID = -1, prevprevAdID = -1;
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
    if(prevprevAdID != -1 && prevprevAdID != adID) {
      alsoViewed.push_back(PI(prevprevAdID, adID));
      alsoViewed.push_back(PI(adID, prevprevAdID));
    }
    if(prevAdID != adID) {
      prevAdID = adID;
      prevprevAdID = prevAdID;
    }

    // Update cnt for views:
    if(enabledAds.find(adID) != enabledAds.end()) {
      Category &CC = cats[categoryMap[adToCat[adID]]];
      CC.adImpressionsCounts[adID]++;
    }

    // Update last position:
    User *user;
    if(userMap.find(id) == userMap.end()) {
      user = new User;
      userMap[id] = user;
    }
    else
      user = userMap[id];
    user->lastPosition = PD(lat,lon);

    Impression impression(time, isFirstMessage, origin, adID, impressions+views+messages);

    user->impressions.push_back(impression);
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

void readUserMessagesCsv(map<int,User*> &userMap, Category *cats, int const * const categoryMap) {
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

    int recommendedAdID;
    while(ss >> recommendedAdID) {
      Category &category = cats[categoryMap[cat]];
      for(vector<Impression>::const_iterator it = impressions.begin(); it != impressions.end(); ++it) {
	category.adToRecommendations.push_back(PI(it->adID, recommendedAdID));
      }
      u->recommendations.push_back(recommendedAdID);

      category.adRecommendationsCounts[recommendedAdID]++;

      ss >> line; // ","      
      //cerr << " " << adID << endl;
    }
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
  for(vector<int>::iterator it = ads.begin(); it != ads.end(); ++it) {	
    seen.insert(*it);
  }

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

void addTopForCategory(bool rec, double precision, int user, int cat, map<int,User*> &userMap, Category *cats, int *categoryMap, map<int,int> &adToCat, vector<int> &ads) {
  vector<int> &TT = rec ? cats[categoryMap[cat]].topRecAds : cats[categoryMap[cat]].topImpAds;
  
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
    if(u != NULL && distSq(u->lastPosition, getAdPosition(aa, cats, categoryMap, adToCat)) > precision*u->maxViewDist)
      continue;
    ads.push_back(aa);
    seen.insert(aa);
    if(ads.size() >= 10)
      break;
  }
}

void addNearesForCategory(bool rec, int user, int cat, map<int,User*> &userMap, Category *cats, int *categoryMap, map<int,int> &adToCat, vector<int> &ads) {
  vector<int> &TT = rec ? cats[categoryMap[cat]].topRecAds : cats[categoryMap[cat]].topImpAds;
  
  User *u = NULL;
  if(user != -1)
    u = userMap[user];

  set<int> seen;
  for(vector<int>::const_iterator it = ads.begin(); it != ads.end(); ++it)
    seen.insert(*it);
  vector<pair<double,int> > V;
  for(vector<int>::const_iterator it = TT.begin(); it != TT.end(); ++it) {
    int aa = *it;
    if(seen.find(aa) != seen.end())
      continue;
    seen.insert(aa);
    V.push_back(make_pair(distSq(u->lastPosition, getAdPosition(aa, cats, categoryMap, adToCat)), aa));
  }
  sort(V.begin(), V.end());
  for(vector<pair<double,int> >::const_iterator it = V.begin(); it != V.end(); ++it) {
    if(ads.size() >= 10)
      break;
    int aa = it->second;
    ads.push_back(aa);
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
  int xx = 0;
  for(vector<Impression>::reverse_iterator it = impressions.rbegin(); it != impressions.rend() && ++xx < 5; ++it) {	
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
  User *u = userMap[user];
  vector<Impression> &impressions = u->impressions; // Already seen impressions.

  set<int> seen;
  for(vector<Impression>::reverse_iterator it = impressions.rbegin(); it != impressions.rend(); ++it) {	
    if(ads.size() >= MAX)
      return;
    
    Impression &i = *it;
    int a = i.adID;
    if(seen.find(a) != seen.end())
      continue; // Already added
    seen.insert(a);

    // Find ads which have been recommended based on what we have seen:
    map<int,int> recommendationHits;

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

    int bestScore = -1;
    int bestAd = -1;
    for(map<int,int>::const_iterator it = recommendationHits.begin(); it != recommendationHits.end(); ++it) {
      int score = it->second;
      if(score > bestScore) {
	bestScore = score;
	bestAd = it->first;
      }
    }
    ads.push_back(bestAd);
  }
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
    stringstream kw;
    getline(file, title, '"');
    kw << title << " " << title << " ";
    getline(file, line, ',');

    string desc;
    // Ignore description
    do {
      kw << line;
      desc = line;
      getline(file, line, ',');
      kw << line;
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
    string allKW = kw.str();
    getKeywords(allKW, ad.keywords);

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
void addAdsWithMatchingKeywords(double precision, unsigned int MAX, int cat, int user, map<int,User*> &userMap, 
				Category *cats, int const * const categoryMap, map<int,int> &adToCat, 
				vector<int> &ads) {
  if(ads.size() >= MAX)
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
  for(vector<int>::const_iterator it = ads.begin(); it != ads.end(); ++it) {
    if(viewedAds.find(*it) != viewedAds.end())
      continue;
    viewedAds.insert(*it);
  }

  // 0.1) Find keyword map and max dist:
  Category &c = cats[categoryMap[cat]];
  double maxDist = precision*u->maxViewDist;
  set<int> seen;

  // 1) Go through ads viewed by user in order to gather keyword sets
  map<int,int> relatedAds; // adID -> score
  int XX = 0;
  for(vector<Impression>::reverse_iterator it = impressions.rbegin(); it != impressions.rend(); ++it) {    
    int baseAdID = it->adID;
    if(seen.find(baseAdID) != seen.end())
      continue;
    if(++XX > 5)
      break;
    seen.insert(baseAdID);
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
	if(distSq(u->lastPosition, ad.position) > maxDist) {
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
  //cerr << "Matches: " << relatedAds.size() << endl;
  vector<PI> ret;
  for(map<int,int>::const_iterator it = relatedAds.begin(); it != relatedAds.end(); ++it) {
    ret.push_back(PI(-it->second, it->first));
  }
  sort(ret.begin(), ret.end());
  bool first = true;
  for(vector<PI>::const_iterator it = ret.begin(); it != ret.end() && ads.size() < MAX; ++it) {
    if(first)
      cerr << " " << user << "/" << cat << " high score: " << -it->first << endl;
    first = false;
    ads.push_back(it->second);
  }
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
  readUserDataCsv(userMap, alsoViewed, cats, categoryMap, adToCat, enabledAds);

  // Read user_messages.csv for hints:
  readUserMessagesCsv(userMap, cats, categoryMap);

  cerr << "Setting top recommended ads!" << endl;
  for(int i = 0; i < 10; ++i) {
    cats[i].setTopAdsRec();
    cats[i].setTopAdsImp();
    sort(cats[i].adToRecommendations.begin(), cats[i].adToRecommendations.end());
  }
  
  // Read user_messages_test.csv for task at hand:
  string line;
  ifstream infile;
  ofstream outfile;
  infile.open("user_messages_test.csv");
  outfile.open("ads_recommendation.csv");
  outfile << "user_id,category_id,ads" << endl;
  
  cerr << "Starting to handle user_messages_test.csv" << endl;
  getline(infile, line); // Header
  int cnt = 0;
  while(getline(infile, line)) {
    if(cnt++ % 100 == 0)
      cerr << ";";
    // Read user id:
    int user, cat;
    sscanf(line.c_str(), "%d,%d", &user, &cat);
    
    outfile << user << "," << cat << ",\"[";
      
    vector<int> ads;
    if(userMap.find(user) == userMap.end()) {
      // Unknown user!
      addTopForCategory(true, 1000.0, -1, cat, userMap, cats, categoryMap, adToCat, ads);
      addTopForCategory(false, 1000.0, -1, cat, userMap, cats, categoryMap, adToCat, ads);
    }
    else {
      addPreviouslySeenAds(10, cat, user, userMap, adToCat, enabledAds, ads);
      //addAdsWithMatchingKeywords(0.01, 10, cat, user, userMap, cats, categoryMap, adToCat, ads);
      //addAlsoViewed(2, cat, user, alsoViewed, userMap, cats, categoryMap, adToCat, enabledAds, ads);
      //addSimilarlyRecommendedAds(10, cat, user, userMap, cats, categoryMap, adToCat, ads);

      // Fill with top 10:
      addTopForCategory(true, 0.01, user, cat, userMap, cats, categoryMap, adToCat, ads);
      addTopForCategory(true, 0.1, user, cat, userMap, cats, categoryMap, adToCat, ads);
      addTopForCategory(false, 0.1, user, cat, userMap, cats, categoryMap, adToCat, ads);
      addTopForCategory(true, 100.0, user, cat, userMap, cats, categoryMap, adToCat, ads);
      //addNearesForCategory(false, user, cat, userMap, cats, categoryMap, adToCat, ads);
    }
    
    bool first = true;
    for(unsigned int i = 0; i < ads.size() && i < 10; ++i) {
      if(!first)
	outfile << ", ";
      first = false;
      outfile << ads[i];
    }
    outfile << "]\"" << endl;      
  }  

  infile.close(); outfile.close();
  return 0;
}
