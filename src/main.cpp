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

/**
 * \fn int main (void)
 * \brief Creates a movie, changes chapter lengths and observes.
 * \return 0
 */
int main() {
  Library lib;
  shared_ptr<Multimedia> pic1,pic2,pic3;
  stringstream ss;
  pic1 = lib.addPicture("picture","media/small.jpg",0,0);
  cerr << pic1.use_count() << endl;
  pic2 = lib.getFile("picture");
  cerr << pic1.use_count() << endl;
  pic3 = lib.getFile("picture");
  cerr << pic1.use_count() << endl;
  pic1 = lib.getFile("picture");
  cerr << pic1.use_count() << endl;
  pic2 = 0;
  cerr << pic1.use_count() << endl;
  pic3 = 0;
  cerr << pic1.use_count() << endl;
  Multimedia * picobj;
  try {
    pic1 = lib.getFile("something");
  } catch (exception& e) {
    cerr << e.what() << endl;
  }
  picobj = new Picture("picture","media/small.jpg",0,0);
  picobj->open();
  cerr << "Objects can still be created outside of libraries." << endl;
  return 0;
}
