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

using namespace std;

/**
 * \fn int main (void)
 * \brief Creates a movie, changes chapter lengths and observes.
 * \return 0
 */
int main() {
#define N 30
  Multimedia ** m = new Multimedia * [N];
  for (int i=0; i<N; i+=3) {
    stringstream ss; ss << i;
    m[i] = new Video(ss.str(),"/dev/null",0);
    m[i+1] = new Movie(ss.str(),"/dev/null",0);
    m[i+2] = new Picture(ss.str(),"/dev/null",0,0);
  }
  Group<Multimedia> ** g = new Group<Multimedia> * [3];
  g[0] = new Group<Multimedia>("first one");
  g[1] = new Group<Multimedia>("second one");
  g[2] = new Group<Multimedia>("third one");
  int x;
  for (int i=0; i<3; i++) {
    x = 6 + (((11-3*i)*i)>>1);
    for (int j=0; j<N; j+=x) g[i]->push_back(m[j]);
  }
  for (int k=0; k<3; k++) {
    for (int i=k; i<3; i++) {
      g[i]->print(cerr);
      cerr << "------" << endl;
    }
    delete g[k];
  }
  delete[] g;
  for (int i=0; i<N; i++) delete m[i];
  delete[] m;
  return 0;
#undef N
}
