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
 * \brief Creates, opens and deletes a list of Multimedia objects.
 * \return 0
 */
int main() {
  Multimedia ** m = new Multimedia * [6];
  stringstream s;
  m[0] = new Video("small vid","small.mp4",180);                  // Existing video
  m[1] = new Picture("small pic","small.jpg",48.856638,2.352241); // Existing picture
  m[2] = new Video("null vid","null.mp4",42);                     // Non-existing video
  m[3] = new Picture("null pic","null.jpg",13.37,3.14159265);     // Non-existing picture
  m[4] = new Video();                                             // Null video
  m[5] = new Picture();                                           // Null picture
  for (int i=0; i<6; i++) {
    s.str(string());
    m[i]->print(s);
    cerr << i << ": " << s.str() << endl;
    m[i]->open();
  }
  delete[] m;
  return 0;
}
