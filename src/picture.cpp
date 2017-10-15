#include <cstdlib>
#include "picture.h"

void Picture::print(ostream& s) const {
  Multimedia::print(s);
  s << " : " << latitude << "," << longitude;
}

void Picture::open() const {
  if (this->check())
    return;
  system(("imagej " + path + ">/dev/null 2>/dev/null &").c_str());
}
