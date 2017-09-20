#ifndef _include_group_h
#define _include_group_h

/**
 * \file group.h
 * \brief Class for groups of objects.
 * \author Clement Durand <clement.durand@telecom-paristech.fr>
 * \version 1.0
 * \date 2017-09-19
 */
#include <iostream>
#include <list>
#include "multimedia.h"

using namespace std;

/**
 * \class Class for groups of objects.
 * \brief Class for generic group files.
 */
template <class X, bool = is_base_of<Multimedia,X>::value> class Group : public list<X*> {
public:
  void foo() { cerr << "no" << endl; };
};

template <class X> class Group<X,true> : public list<X*> {
public:
  void foo() { cerr << "yes" << endl; };
};

#endif
