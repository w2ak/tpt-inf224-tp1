#include <cstdlib>
#include "video.h"

void Video::print(ostream& s) const {
  s << "Video(" << name << ") @ " << path;
  s << " : " << duration << "s";
}

void Video::open() const {
  if (this->check())
    return;
  system(("mpv " + path + ">/dev/null 2>/dev/null &").c_str());
}
