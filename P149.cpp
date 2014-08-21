#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <algorithm>

typedef std::pair<double,double> pp;

struct SimpleIntervalHandler {
  std::vector<pp> ivs;
  int ivsI;

  SimpleIntervalHandler() : ivsI(-1) {
  }

  void merge(const std::vector<pp> &newIvs) {
    ///std::cerr << "Merging " << newIvs.size() << " into " << ivs.size() << std::endl;
    ivsI = 0;
    std::vector<pp> res;
    for(unsigned int i = 0; i < newIvs.size(); ++i) {
      pp p = newIvs[i];
      // add all old interval up until p:
      while(ivsI < (int)ivs.size() && ivs[ivsI].second < p.first) {
	res.push_back(ivs[ivsI++]);
      }
      // spool if ivs is done:
      if(ivsI == (int)ivs.size()) {
	res.push_back(p);
	continue;
      }
      // merge if necessary:
      if(ivs[ivsI].first < p.first) {
	p.first = ivs[ivsI].first;
      }
      while(ivsI < (int)ivs.size() && ivs[ivsI].first <= p.second) {
	if(ivs[ivsI].second > p.second)
	  p.second = ivs[ivsI].second;
	++ivsI;
      }
      res.push_back(p);
    }
    ivsI = -1;
    ivs = res;
    ///std::cerr << "Merged to " << ivs.size() << std::endl;
  }

  bool inInterval(double d) {
    if(ivs.empty())
      return false;
    if(ivsI != -1 && d < ivs[ivsI].first) {
      ivsI = -1;
    }
    if(ivsI == -1) {
      if(d < ivs[0].first)
	return false;
      ivsI = 0;
    }
    while(ivs[ivsI].second < d) {
      if(ivsI == (int)ivs.size()-1)
	return false;
      ++ivsI;
    }
    return ivs[ivsI].first <= d && d <= ivs[ivsI].second;
  }

  bool full(const double &min, const double &max) {
    if(ivs.empty())
      return false;
    if(ivs[0].first > min + 0.01)
      return false;
    if(ivs[ivs.size()-1].second < max - 0.01)
      return false;
    for(unsigned int i = 1; i < ivs.size(); ++i) {
      if(ivs[i-1].second < ivs[i].first - 0.01)
	return false;
    }
    return true;
  }
};
std::ostream& operator<<(std::ostream& os, const pp& obj) {
  os << "[" << obj.first << ";" << obj.second << "]";
  return os;
}
std::ostream& operator<<(std::ostream& os, const SimpleIntervalHandler& obj) {
  for(unsigned int i = 0; i < obj.ivs.size(); ++i) {
    os << " ";
    if((int)i == obj.ivsI)
      os << "(";
    os << obj.ivs[i];
    if((int)i == obj.ivsI)
      os << ")";
  }
  return os;
}


/*
Times:
sort distance: 13.5s
no sort: 6.6s

 */

double angle(double x, double y) {
  if(x == 0)
    return y > 0 ? 90 : 270;
  if(y == 0)
    return x > 0 ? 0 : 180;
  if(y > 0)
    return atan(y/x) * 180 / M_PI;
  return 180 + (atan(y/x) * 180 / M_PI);
}
double angle(const pp &p) {
  return angle(p.first, p.second);
}

int inQuadrant(double ox, double oy, double diam) {
  // Find degree span of tree 1 unit away:
  double angle1 = 2 * asin(diam/2) * 180 / M_PI;
  int largestDist = (int)(angle1 / 0.01)+1;
  ///double angleLargestDist = 2 * asin(diam/2/largestDist) * 180 / M_PI;
  ///std::cerr << "diam:" << diam << " ox:" << ox << " oy:" << oy << " angle1:" << angle1 << " largest dist:" << largestDist << " => " << angleLargestDist << std::endl;

  // Find all eligible trees:
  int res = 0;
  SimpleIntervalHandler sih;
  for(int i1 = 1; i1 <= largestDist; ++i1) {
    std::vector<pp> line;
    ///std::cerr << "Line before: " << sih << std::endl;
    int beforeRes = res;
    for(int i2 = 1; i2 <= i1; ++i2) {
      double x = i1-i2+1-ox;
      double y = i2-oy;

      double dist = sqrt(x*x+y*y);
      double radius = asin(diam/2/dist) * 180 / M_PI;
      
      ///std::cerr << "Running " << " x:" << x << " y:" << y << " dist:" << dist << " radius: " << radius << std::endl;

      if(radius >= 0.005) {
	double a = angle(x, y);
	double min = a - radius;
	double max = a + radius;

	///std::cerr << "angle " << a << " min:" << min << " max:" << max << std::endl;

	line.push_back(std::make_pair(min-0.01, max+0.01));
	if(!sih.inInterval(min) && !sih.inInterval(max)) {
	  ++res;
	  /////std::cerr << "Visible: " << p.first << "," << p.second << ", min:" << d.first << ", max: " << d.second << ", dist:" << distP << ", angle span:" << (2*radiusP) << std::endl;
	}
      }
    }
    if(res == beforeRes && i1 > 20)
      return res;
    sih.merge(line);
    ///std::cerr << "Line after merge: " << sih << std::endl;
  }
  return res;
}

int main() {
  while(true) {
    double diam, ox, oy;
    std::cin >> diam >> ox >> oy;
    if(diam == 0)
      return 0;

    int res = 0;
    res += inQuadrant(ox, oy, diam);
    res += inQuadrant(1-ox, oy, diam);
    res += inQuadrant(ox, 1-oy, diam);
    res += inQuadrant(1-ox, 1-oy, diam);
    std::cout << res << std::endl;
  }
}
