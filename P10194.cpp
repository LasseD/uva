#include <iostream>
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <map>
#include <algorithm>

struct String;
struct Team;
typedef std::map<String,Team*> Map;

bool isOK(char c) {
  return c >= 32 || c < 0;
}

struct String {
  char w[31];

  String() {}
  String(char *ww, bool lower) {
    int i = 0;
    for(; isOK(ww[i]); ++i)
      w[i] = lower ? tolower(ww[i]) : ww[i];
    w[i] = '\0';
  }
  String(const String &t) {
    int i = 0;
    for(; isOK(t.w[i]); ++i)
      w[i] = t.w[i];
    w[i] = '\0';
  }

  bool operator<(const String &t) const {
    for(int i = 0; true; ++i) {
      if(w[i] == '\0' || t.w[i] == '\0')
	return w[i] < t.w[i];
      if(w[i] != t.w[i])
	return w[i] < t.w[i];
    }
  }
  bool operator!=(const String &t) const {
    return *this < t || t < *this;
  }
};

struct Team {
  String name, lower;
  int points, games, wins, ties, losses, goals, negGoals;

  Team() {}
  Team(char *w) : name(w, false), lower(w, true), points(0), games(0), wins(0), ties(0), losses(0), goals(0), negGoals(0) {}
  Team(const Team &t) : name(t.name), lower(t.lower), points(t.points), games(t.games), wins(t.wins), ties(t.ties), losses(t.losses), goals(t.goals), negGoals(t.negGoals){}

  bool operator<(const Team &t) const {
    if(3*wins+ties != 3*t.wins+t.ties)
      return 3*wins+ties > 3*t.wins+t.ties;
    if(wins != t.wins)
      return wins > t.wins;
    if(goals-negGoals != t.goals-t.negGoals)
      return goals-negGoals > t.goals-t.negGoals;
    if(goals != t.goals)
      return goals > t.goals;
    if(games != t.games)
      return games < t.games;
    return lower < t.lower;
  }

  void print(int i) {
    printf("%d) %s %dp, %dg (%d-%d-%d), %dgd (%d-%d)\n", i+1, name.w, (3*wins+ties), games, wins, ties, losses, goals-negGoals, goals, negGoals);
  }
};

int main() {
  char c, line[1509];
  int N, numTeams, numMatches;
  scanf("%d\n", &N);
  for(int tournament = 0; tournament < N; ++tournament) {
    gets(line);
    int xx = 0;
    while(isOK(line[xx]))
      ++xx;
    line[xx] = '\0';
    
    if(tournament != 0)
      printf("\n");
    printf("%s\n", line);
    // Read teams:
    scanf("%d\n", &numTeams);
    Team *teams = new Team[numTeams];
    Map teamMap;
    for(int i = 0; i < numTeams; ++i) {
      gets(line);
      int k = 0;
      for(; isOK(line[k]); ++k)
	;
      line[k] = '\0';
      teams[i] = Team(line);
      teamMap.insert(std::make_pair(String(line, false), &teams[i]));
    }
    // Read matches:
    scanf("%d\n", &numMatches);
    for(int i = 0; i < numMatches; ++i) {
      gets(line);
      int j = 0;
      int goals1 = 0, goals2 = 0;
      while(line[j] != '#')
	++j;
      line[j] = '\0';
      String team1(line, false);
      while((c = line[++j]) != '@')
	goals1 = 10*goals1 + (c-'0');
      while((c = line[++j]) != '#')
	goals2 = 10*goals2 + (c-'0');
      ++j;
      int k = j;
      while(isOK(line[k]))
	++k;
      line[k] = '\0';
      String team2(&line[j], false);
      //std::cerr << "Read match '" << line << "' vs '" << &line[j] << "': " << goals1 << " " << goals2 << std::endl; 
      if(teamMap.find(team1) == teamMap.end() || teamMap.find(team2) == teamMap.end())
	while(true)
	  std::cerr << "'" << team1.w << "'VS1'" << team2.w << "' j=" << j << ", k=" << k <<", goals1=" << goals1 << ", goals2=" << goals2 << std::endl;
      Team *t1 = teamMap[team1];
      Team *t2 = teamMap[team2];
      t1->goals += goals1;
      t2->negGoals += goals1;
      t2->goals += goals2;
      t1->negGoals += goals2;
      t1->games++;
      t2->games++;
      if(goals1 > goals2) {
	++t1->wins;
	++t2->losses;
	t1->points += 3;
      }
      else if(goals1 < goals2) {
	++t2->wins;
	++t1->losses;
	t2->points += 3;
      }
      else {
	++t1->ties;
	++t2->ties;
	++t1->points;
	++t2->points;
      }
    }
    std::sort(teams, teams+numTeams);
    for(int i = 0; i < numTeams; ++i)
      teams[i].print(i);

    delete[] teams;
  }
  return 0;  
}
