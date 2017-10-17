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
#include <algorithm>
#include <assert.h>
#include "picture.h"
#include "video.h"
#include "movie.h"
#include "group.h"
#include "library.h"

using namespace std;

/**
 * \fn int main (void)
 * \brief Creates a movie, changes chapter lengths and observes.
 * \return 0
 */
int main() {
  Picture pic1("a;beautiful;name","media/small.jpg",3.14,1.41);
  pic1.print(cerr);
  cerr << endl;
  stringstream s;
  string str;
  pic1.unparse(s);
  cerr << s.str() << endl;
  getline(s,str,';');
  Picture pic2;
  pic2.parse(s);
  pic2.print(cerr);
  cerr << endl;
  return 0;
}
