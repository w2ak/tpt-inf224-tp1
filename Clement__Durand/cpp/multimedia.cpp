#include "multimedia.h"
#include <sys/stat.h>

int Multimedia::check() const {
  if (!initialized) {
    cerr << "[";
    this->print(cerr);
    cerr << "]: Non initialized multimedia object." << endl;
    return 2;
  }
  struct stat buffer;
  if (stat(path.c_str(),&buffer)) {
    cerr << path << ": No such file." << endl;
    return 1;
  }
  return 0;
}
