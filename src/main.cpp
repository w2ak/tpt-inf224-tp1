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

using namespace std;

/**
 * \fn int main (void)
 * \brief Creates a movie, changes chapter lengths and observes.
 * \return 0
 */
int main() {
#define N 10
  int* c = new int[N];
  for (int i=0; i<N; c[i] = i, i++);
  Movie * m = new Movie();
  assert(m->getChapterCount() == 0);
  m->setChapters(c,N);
  assert(m->getChapterCount() == N);
  for (int i=0; i<N; i++) assert(m->getChapter(i+1)==i);
  for (int i=0; i<N; c[i] += N, i++);
  for (int i=0; i<N; i++) assert(m->getChapter(i+1)==i);
  for (int i=0; i<N; c[i] += N, i++);
  for (int i=0; i<N; i++) assert(m->getChapter(i+1)==i);
  delete[] c;
  for (int i=0; i<N; i++) assert(m->getChapter(i+1)==i);
  stringstream s;
  m->print(s);
  cerr << s.str() << endl;
  return 0;
#undef N
}
