#include <cstdlib>
#include "picture.h"

void Picture::print(ostream& s) const {
  Multimedia::print(s);
  s << " : " << latitude << "," << longitude;
};

void Picture::open() const {
  if (this->check())
    return;
  system(("imagej " + path + ">/dev/null 2>/dev/null &").c_str());
};

void Picture::parse(istream& s) {
  Multimedia::parse(s);
  char sep = ';';
  string str;
  getline(s,str,sep);
  latitude = stod(str);
  getline(s,str,sep);
  longitude = stod(str);
};

void Picture::unparse(ostream& s) const {
  Multimedia::unparse(s);
  char sep = ';';
  s << latitude << sep << longitude << sep;
};
