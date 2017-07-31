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

using namespace std;

typedef pair<double,double> PD;
typedef pair<int,int> PI;

struct Impression {
  long time;
  int adID;
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
  int adID;
  PD position;
  bool enabled;
};

struct Category {
  map<int,Ad> adMap; // id -> ad
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

void readUserDataCsv(map<int,User*> &userMap, Category *cats, int const * const categoryMap, map<int,int> &adToCat, set<int> &enabledAds) {
  string line;

  ifstream file;
  file.open("user_data.csv");

  int lines = 0;

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
    
    // Rest of line:
    int adID;
    getline(file, line, ',');
    sscanf(&(line.c_str()[1]), "%d", &adID);    
    getline(file, line);

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

    Impression impression;
    impression.time = time;
    impression.adID = adID;

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

    int recommendedAdID;
    while(ss >> recommendedAdID) {
      Category &category = cats[categoryMap[cat]];
      u->recommendations.push_back(recommendedAdID);

      category.adRecommendationsCounts[recommendedAdID]++;

      ss >> line; // ","      
      //cerr << " " << adID << endl;
    }
  }

  cout << lines << " lines read from user_messages.csv." << endl;  
  file.close();
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
    getline(file, line, ',');

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
    ad.position = PD(lat, lon);
    ad.enabled = enabled;

    category.adMap[adID] = ad;

  }
  cout << lines << " lines read from ads_data.csv. " << endl;
  file.close();  
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
  readUserDataCsv(userMap, cats, categoryMap, adToCat, enabledAds);

  // Read user_messages.csv for hints:
  readUserMessagesCsv(userMap, cats, categoryMap);

  cerr << "Setting top recommended ads!" << endl;
  for(int i = 0; i < 10; ++i) {
    cats[i].setTopAdsRec();
    cats[i].setTopAdsImp();
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

      // Fill with top 10:
      addTopForCategory(true, 0.01, user, cat, userMap, cats, categoryMap, adToCat, ads);
      addTopForCategory(true, 0.1, user, cat, userMap, cats, categoryMap, adToCat, ads);
      addTopForCategory(false, 0.1, user, cat, userMap, cats, categoryMap, adToCat, ads);
      addTopForCategory(true, 100.0, user, cat, userMap, cats, categoryMap, adToCat, ads);
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
