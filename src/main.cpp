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
#include <assert.h>
#include "picture.h"
#include "video.h"
#include "movie.h"
#include "group.h"
#include "library.h"

using namespace std;
//typedef shared_ptr<Multimedia> mptr;

/**
 * \fn int main (void)
 * \brief Creates a movie, changes chapter lengths and observes.
 * \return 0
 */
int main() {
  Library lib;
  shared_ptr<Multimedia> pic;
  Multimedia * picobj;
  pic = lib.addPicture("picture","media/small.jpg",0,0);
  cerr << lib.size() << " " << pic << endl;
  pic = lib.addPicture("picture","media/small.jpg",0,0);
  cerr << lib.size() << " " << pic << endl;
  picobj = new Picture("picture","media/small.jpg",0,0);
  picobj->open();
  cerr << "Objects can still be created outside of libraries." << endl;
  return 0;
}
