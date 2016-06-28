#include <iostream>
#include <stdio.h>
#include <set>
#include <map>
#include <string>
#include <sstream>

typedef std::string String;
typedef std::map<int,String> MapIS;
typedef std::map<String,int> MapSI;
typedef std::stringstream SS;

#define EPOCH 1596

void die() {
  int *d = NULL;
  d[0] = 666;
}

class Calendar {
  MapSI weekdaysSI, monthsSI;
  MapIS weekdaysIS, monthsIS;

public:
  Calendar() {
    String weekdays[7] = {
      "Monday",
      "Tuesday",
      "Wednesday",
      "Thursday",
      "Friday",
      "Saturday",
      "Sunday"
    };
    for(int i = 0; i < 7; ++i) {
      weekdaysIS[i] = weekdays[i];
      weekdaysSI[weekdays[i]] = i;
    }
    String months[12] = {
      "January",
      "February",
      "March",
      "April",
      "May",
      "June",
      "July",
      "August",
      "September",
      "October",
      "November",
      "December"
    };
    for(int i = 0; i < 12; ++i) {
      monthsIS[i] = months[i];
      monthsSI[months[i]] = i;
    }    
  }

  int daysOfMonth(int monthI, bool leap) {
    int a[12] = {31, 28, 31, 30, 31, 30, 
		 31, 31, 30, 31, 30, 31};
    return a[monthI] + (leap && monthI==1 ? 1 : 0);
  }

  int parseJulian(char * const w) {
    SS ss;
    ss << String(w);
    String weekdayStr, monthStr;
    int dayOfMonth, year;
    if(!(ss >> weekdayStr >> dayOfMonth >> monthStr >> year))
      die();
    if(weekdaysSI.find(weekdayStr) == weekdaysSI.end())
      die();
    if(monthsSI.find(monthStr) == monthsSI.end())
      die();
    int ret = (year-EPOCH) * 365 + ((year-EPOCH+3)/4);
    int monthI = monthsSI[monthStr];
    for(int i = 0; i < monthI; ++i)
      ret += daysOfMonth(i, (year%4) == 0);
    //std::cerr << "MonthI=" << monthI << ", year=" << year << ", days of month: " << daysOfMonth(monthI, (year/4) == 0) << ", day of month: " << dayOfMonth << std::endl;
    if(dayOfMonth > daysOfMonth(monthI, (year%4) == 0))
      return -1;
    ret += dayOfMonth-1;
    //std::cerr << "Day " << ret << ", mod 7=" << (ret%7) << ", ret=" << ret << std::endl;
    if((ret+3)%7 != weekdaysSI[weekdayStr])
      return -1;
    return ret;
  }
  bool leapGregorian(int year) {
    return (year%400 == 0) || (year%4 == 0 && year%100 != 0);
  }
  int parseGregorian(char * const w) {
    SS ss;
    ss << String(w);
    String weekdayStr, monthStr;
    int dayOfMonth, year;
    if(!(ss >> weekdayStr >> dayOfMonth >> monthStr >> year))
      die();
    if(weekdaysSI.find(weekdayStr) == weekdaysSI.end())
      die();
    if(monthsSI.find(monthStr) == monthsSI.end())
      die();

    int ret = (year-EPOCH) * 365 + ((year-EPOCH+3)/4) - ((year-EPOCH-4+99)/100) + ((year-EPOCH-4+399)/400);
    //std::cerr << "Init ret: " << ret << std::endl;
    int monthI = monthsSI[monthStr];
    for(int i = 0; i < monthI; ++i)
      ret += daysOfMonth(i, leapGregorian(year));
    //std::cerr << "MonthI=" << monthI << ", year=" << year << ", days of month: " << daysOfMonth(monthI, (year/4) == 0) << ", day of month: " << dayOfMonth << std::endl;
    if(dayOfMonth > daysOfMonth(monthI, leapGregorian(year)))
      return -1;
    ret += dayOfMonth-1;

    //std::cerr << "Day " << ret << ", mod 7=" << (ret%7) << std::endl;
    if((ret+0)%7 != weekdaysSI[weekdayStr])
      return -1;
    return ret;
  }
  int yearLengthJulian(int year) {
    return 365 + (year%4 == 0 ? 1 : 0);
  }
  void printJulian(const int dayOfCalendar) {
    int rem = dayOfCalendar;
    int year = EPOCH;
    while(rem >= yearLengthJulian(year)) {
      rem-=yearLengthJulian(year);
      ++year;
    }
    int monthI = 0;
    while(rem >= daysOfMonth(monthI, year%4 == 0)) {
      rem-=daysOfMonth(monthI, year%4 == 0);
      ++monthI;
    }    
    std::cout << weekdaysIS[(dayOfCalendar+3)%7] << " " << (rem+1) << "* " << monthsIS[monthI] << " " << year << std::endl;
  }
  int yearLengthGregorian(int year) {
      return 365 + (leapGregorian(year) ? 1 : 0);
  }
  void printGregorian(const int dayOfCalendar) {
    int rem = dayOfCalendar;
    int year = EPOCH;
    while(rem >= yearLengthGregorian(year)) {
      rem-=yearLengthGregorian(year);
      ++year;
    }
    int monthI = 0;
    while(rem >= daysOfMonth(monthI, leapGregorian(year))) {
      rem-=daysOfMonth(monthI, leapGregorian(year));
      ++monthI;
    }    
    std::cout << weekdaysIS[(dayOfCalendar+0)%7] << " " << (rem+1) << " " << monthsIS[monthI] << " " << year << std::endl;
  }
};

int main() {
  char w[109];
  Calendar c;

  // Test:
  //for(int i = 0; i < 600*365; ++i)
  //  c.printJulian(i);
  //for(int i = 0; i < 600*365; ++i)
  //  c.printGregorian(i);
  //return 0;
  /*for(int i = 0; i < 600*365; ++i) {
    gets(w);
    //int d = c.parseJulian(w);
    int d = c.parseGregorian(w);
    if(d == i)
      continue;
    std::cerr << String(w) << " for i=" << i << " != " << d << std::endl;
    die();
  }
  return 0;
  //*/

  while(true) {
    gets(w);
    if(w[0] == '#')
      return 0;
    int julian = c.parseJulian(w);
    int gregorian = c.parseGregorian(w);
    int diff = 10;
    if(julian == -1 && gregorian == -1)
      die();
    if(julian != -1 && gregorian != -1)
      die();
    if(julian == -1)
      c.printJulian(gregorian-diff);
    else
      c.printGregorian(julian+diff);    
  }
}
