#include <cstdlib>
#include "movie.h"

void Movie::setChapters(const int* c, unsigned int n) {
  delete[] chapters;
  chapters = new int [n];
  for (unsigned int i=0; i<n; i++) chapters[i] = c[i];
  chapn = n;
}

void Movie::print(ostream& s) const {
  Video::print(s);
  s << " : [";
  for (int i=0; i<chapn; i++) {
    if (i) s << ",";
    s << "(" << (i+1) << ")" << chapters[i] << "s";
  }
  s << "]";
}

void Movie::parse(istream& s) {
  Video::parse(s);
  char sep = ';';
  string str;
  stringstream buf;
  getline(s,str,sep);
  chapn = stoi(str);
  getline(s,str,sep);
  if (chapn > 0) {
    chapters = new int [chapn];
    buf.str(str);
    for (int i=0; i<chapn; i++) {
      getline(buf,str,',');
      chapters[i] = stoi(str);
    }
  } else {
    chapn = 0;
  }
}

void Movie::unparse(ostream& s) const {
  Video::unparse(s);
  char sep = ';';
  s << chapn << sep;
  for (int i=0; i<chapn; i++) {
    if (i) s << ',';
    s << chapters[i];
  }
  s << sep;
}
