/**
 * \file main.cpp
 * \brief Opens a list of media files.
 * \author Clement Durand <clement.durand@telecom-paristech.fr>
 * \version 1.0
 * \date 2017-09-19
 *
 * Test program for the implementation of the Multimedia classes.
 *
 */
#include <iostream>
#include <sstream>
#include "picture.h"
#include "video.h"
using namespace std;

/**
 * \fn int main (void)
 * \brief Hello World
 * \return 0
 */
int main() {
  stringstream s;
  Picture * p = new Picture();
  p->print(s);
  cerr << s.str() << endl;
  p->open();
  s.str(string());
  Video * v = new Video();
  v->print(s);
  cerr << s.str() << endl;
  v->open();
  return 0;
}
