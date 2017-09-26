#include <cstdlib>
#include "movie.h"

void Movie::setChapters(const int* c, unsigned int n) {
  delete[] chapters;
  chapters = new int [n];
  for (unsigned int i=0; i<n; i++) chapters[i] = c[i];
  chapn = n;
}

void Movie::print(ostream& s) const {
  s << "Movie(" << name << ") @ " << path;
  s << " : " << this->getDuration() << "s";
  s << " : [";
  for (int i=0; i<chapn; i++) {
    if (i) s << ",";
    s << "(" << (i+1) << ")" << chapters[i] << "s";
  }
  s << "]";
}
