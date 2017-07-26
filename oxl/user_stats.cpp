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

void readUserMessagesCsv(map<PI,vector<int> > &fromOxl) {
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
  }

  infile.close();
}

void report(int userID, int catID, Category *cats, int const * const categoryMap, map<int,int> &adToCat, map<PI,vector<int> > &fromOxl) {
  string line;

  ifstream file;
  ofstream os;
  file.open("user_data.csv");
  stringstream ss;
  ss << userID << "_" << catID << ".oxlinfo";
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
    if(allLines % 1000 == 0)
      cout << ".";
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

    int catCnt = categoryMap[adToCat[adID]];
    Category &cat = cats[catCnt];
    Ad *ad = cat.adMap[adID];
    os << " " << *ad << endl;
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

  // Read user_messages.csv:
  map<PI,vector<int> > fromOxl;
  readUserMessagesCsv(fromOxl);

  // Read ads_data.csv:
  Category cats[11];
  map<int,int> adToCat; // adID -> cat (800, 806, etc.)
  readAdsDataCsv(cats, categoryMap, adToCat);

  while(true) {
    cout << "Please type user ID and category, then press ENTER" << endl << endl;
    int userID, cat; cin >> userID >> cat;
    cout << "OK. Please wait." << endl;

    // Read user_data.csv for user map.
    report(userID, cat, cats, categoryMap, adToCat, fromOxl);
    
    cout << "REPORT DONE FOR USER " << userID << ", CATEGORY " << cat << " DONE!" << endl << endl;
  }
  return 0;
}
