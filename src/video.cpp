#include <cstdlib>
#include "video.h"

void Video::print(ostream& s) const {
  Multimedia::print(s);
  s << " : " << duration << "s";
}

void Video::open() const {
  if (this->check())
    return;
  system(("mpv " + path + ">/dev/null 2>/dev/null &").c_str());
}

void Video::parse(istream& s) {
  Multimedia::parse(s);
  char sep = ';';
  string str;
  getline(s,str,sep);
  duration = stoi(str);
}

void Video::unparse(ostream& s) const {
  Multimedia::unparse(s);
  char sep = ';';
  s << duration << sep;
}
