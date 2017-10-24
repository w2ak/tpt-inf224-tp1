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
  Library lib1;
  Library lib2;
  unsigned int chapn = 7;
  int chapters[7] = {1,1,2,3,5,8,13};
  lib1.addPicture("picture","media/small.jpg",3.14,1.41);
  lib1.addVideo("video","media/small.mp4",42);
  const shared_ptr<Movie> movie = dynamic_pointer_cast<Movie>(lib1.addMovie("movie","media/small.mp4",42));
  if (movie) movie->setChapters(chapters,chapn);
  const shared_ptr<Group<Multimedia>> grp = lib1.addGroup("group");
  grp->push_back(movie);
  grp->push_back(lib1.getFile("picture"));
  lib1.unparse(cerr);
  lib1.save("/tmp/lib1.txt");
  cerr << "=====" << endl;
  lib2.load("/tmp/lib1.txt");
  lib2.unparse(cerr);
  return 0;
}
