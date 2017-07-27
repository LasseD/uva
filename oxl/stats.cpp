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

//#define EARLY_BREAK 20000
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
  double maxViewDist;
  map<int,Impression> impressions;
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
    os << *it << " ";
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

double distSq(PD a, PD b) {
  double dx = a.first-b.first;
  double dy = a.second-b.second;
  return dx*dx+dy*dy;
}

PD getAdPosition(int adID, Category *cats, int const * const categoryMap, map<int,int> &adToCat) {
  if(adToCat.find(adID) == adToCat.end())
    return PD(0,0);
  Category &c = cats[categoryMap[adToCat[adID]]];
  return c.adMap[adID]->position;
}
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

void readUserDataCsv(map<int,User*> &userMap, Category *cats, int const * const categoryMap, map<int,int> &adToCat) {
  string line;

  ifstream file;
  file.open("user_data.csv");

  int lines = 0;

  getline(file, line); // Header
  while(getline(file, line, ',')) {
    if(lines % 1000 == 0)
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

    User *user;
    if(userMap.find(id) == userMap.end()) {
      user = new User;
      userMap[id] = user;
    }
    else
      user = userMap[id];
    user->lastPosition = PD(lat,lon);

    Impression impression(time, isFirstMessage, origin, adID, impressions+views+messages);

    // Update maxViewDist:
    double dist = distSq(user->lastPosition, getAdPosition(adID, cats, categoryMap, adToCat));
    if(dist > user->maxViewDist)
      user->maxViewDist = dist;

    user->impressions[adID] = impression;
  }
  cout << lines << " lines read from user_data.csv. " << userMap.size() << " users." << endl;
  file.close();
}

void readUserMessagesCsv(map<PI,vector<int> > &fromOxl, map<int,User*> &userMap, Category *cats, int const * const categoryMap, const map<int,int> &adToCat) {
  cout << "---- Stats from user_messages.csv ----" << endl << endl;

  // Stats:
  int cntUsers = 0, prevUser = -1, cntLines = 0, cntAllAds = 0;
  int cntAdsThatHaveBeenServedBefore = 0;
  int cntServedBeforeOrigins[9] = {0,0,0,0,0,0,0,0,0};
  int cntServedBeforeFirstMessages = 0;
  /*
Impression:
!  long time;
V  bool isFirstMessage;
V  int origin;
  int adID;
X  int interactions;
User::
!  PD lastPosition;
X  double maxViewDist;
  map<int,Impression> impressions;
   */

  string line;
  ifstream infile;
  infile.open("user_messages.csv");
  
  getline(infile, line); // Header

  while(getline(infile, line, ',')) {
    // Read user id:
    int user, cat;
    sscanf(line.c_str(), "%d", &user);
    getline(infile, line, ',');
    sscanf(line.c_str(), "%d", &cat);

    vector<int> v;

    ++cntLines;
    if(user != prevUser)
      ++cntUsers;
    prevUser = user;

    getline(infile, line, '[');
    int adID = 0;
    getline(infile, line);
    for(unsigned int i = 0; i < line.size(); ++i) {
      char c = line[i];
      if(isdigit(c)) {
	adID = 10*adID + c-'0';
      }
      else {
	if(adID != 0)
	  v.push_back(adID);
	adID = 0;
      }
    }
    fromOxl[PI(user, cat)] = v;

    cntAllAds += v.size();
    for(vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
      if(userMap.find(user) == userMap.end())
	continue; // unknown user.
      User *u = userMap[user];
      int adID = *it;
      if(u->impressions.find(adID) == u->impressions.end())
	continue;
      ++cntAdsThatHaveBeenServedBefore;

      Impression &imp = u->impressions[adID]; 
      ++cntServedBeforeOrigins[imp.origin];
      if(imp.isFirstMessage)
	++cntServedBeforeFirstMessages;

      //int catCnt = categoryMap[catID];
      //Category &cat = cats[catCnt];
      //Ad *ad = cat.adMap[adID];
    }
  }

  // TODO: Write result of analysis
  
  cout << "Number of users: " << cntUsers << endl;
  cout << "Number of lines in file: " << cntLines << endl;
  cout << "Total number of ads suggested: " << cntAllAds << endl;
  cout << "Of these, " << cntAdsThatHaveBeenServedBefore << " have been viewed before (" << (cntAdsThatHaveBeenServedBefore*100.0/cntAllAds) << "%)" << endl;
  cout << "Last seen origins of these previously seen ads:" << endl;

  cout << "Browse search: " << cntServedBeforeOrigins[ORIGIN_BROWSE_SEARCH] << endl;
  cout << "Browse: " << cntServedBeforeOrigins[ORIGIN_BROWSE] << endl;
  cout << "Search: " << cntServedBeforeOrigins[ORIGIN_SEARCH] << endl;
  cout << "Notification center: " << cntServedBeforeOrigins[ORIGIN_NOTIFICATION_CENTER] << endl;
  cout << "Home: " << cntServedBeforeOrigins[ORIGIN_HOME] << endl;
  cout << "Push: " << cntServedBeforeOrigins[ORIGIN_PUSH] << endl;
  cout << "Drawer: " << cntServedBeforeOrigins[ORIGIN_DRAWER] << endl;
  cout << "Unknown: " << cntServedBeforeOrigins[ORIGIN_UNKNOWN] << endl;
  cout << "Deeplink: " << cntServedBeforeOrigins[ORIGIN_DEEPLINK] << endl;

  cout << "Of these " << cntServedBeforeFirstMessages << " were first messages (" << (100.0*cntServedBeforeFirstMessages/cntAdsThatHaveBeenServedBefore) << ")" << endl << endl;

  infile.close();
}

void report(int userID, int catID, Category *cats, int const * const categoryMap, map<int,int> &adToCat, map<PI,vector<int> > &fromOxl) {
  string line;

  ifstream file;
  ofstream os;
  file.open("user_data.csv");
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
      Ad *ad = cat.adMap[adID];
      os << " " << *ad << endl;
    }
  }
  else
    os << "This data is not in user_messages.csv" << endl;      

  os << endl << endl << "These are the matching lines from user_data.csv:" << endl;

  int lines = 0;
  int allLines = 0;

  getline(file, line); // Header
  while(getline(file, line, ',')) {
    ++allLines;
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
    os << "Date: 2017-" << month << "-" << day << " " << hour << ":" << minute << ":" << second;

    // event:
    getline(file, line, ',');
    bool isFirstMessage = line[1] == 'f';
    if(isFirstMessage)
      os << " First";
    else
      os << " View";

    // Channel (ignore for now:
    getline(file, line, ',');
    os << " " << line;
    // User position:
    double lat, lon;
    getline(file, line, ',');
    sscanf(&(line.c_str()[1]), "%lf", &lat);    
    getline(file, line, ',');
    sscanf(&(line.c_str()[1]), "%lf", &lon);    
    os << " (" << lat << "," << lon << ")";

    // Origin:
    getline(file, line, ',');

    os << " " << line;
    
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
    os << " Add ID: " << adID <<", image: "<< images<<", impressions: "<< impressions<<", views: "<< views<<", messages: "<< messages << endl;    

    int catID = adToCat[adID];
    int catCnt = categoryMap[catID];
    Category &cat = cats[catCnt];
    Ad *ad = cat.adMap[adID];
    os << " Category " << catID << " " << *ad << endl;
  }
  os << "TOTAL " << lines << " lines read from user_data.csv." << endl;
  file.close();
  os.close();
  cout << "Results are in file: " << ss.str() << endl;
}

void readAdsDataCsv(Category *cats, int const * const categoryMap, map<int,int> &adToCat) {
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
  Category cats[11];
  map<int,int> adToCat; // adID -> cat (800, 806, etc.)
  readAdsDataCsv(cats, categoryMap, adToCat);

  // Read user_data.csv:
  map<int,User*> userMap;
  readUserDataCsv(userMap, cats, categoryMap, adToCat);

  // Get info from user_messages.csv:
  map<PI,vector<int> > fromOxl;
  readUserMessagesCsv(fromOxl, userMap, cats, categoryMap, adToCat);

  return 0;
}
