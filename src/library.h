#ifndef _include_library_h
#define _include_library_h

/**
 * \file library.h
 * \brief Class for Multimedia library
 * \author Clement Durand <clement.durand@telecom-paristech.fr>
 * \version 1.0
 * \date 2017-09-19
 */
#include <map>
#include "multimedia.h"
#include "group.h"

using namespace std;

/**
 * \class Library library.h
 * \class Class for Multimedia library
 */
class Library {
private:
  map<string,shared_ptr<Multimedia>> files;
  map<string,shared_ptr<Group<Multimedia>>> groups;
public:
  Library() {};
};
#endif
