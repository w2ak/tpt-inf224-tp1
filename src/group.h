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
 * \class Group group.h group.cpp
 * \class Class for groups of Multimedia objects.
 */
template <class X, bool = is_base_of<Multimedia,X>::value> class Group : public list<X*> {};

template <class X> class Group<X,true> : public list<X*> {
private:
  string name = "noname"; /**< Name of the group */
public:
  Group() : list<X*>() {};
  Group(string n) : list<X*>() { name=n; }

  ~Group() {};

  void setName(string n) { name=n; };
  string getName() const { return name; };

  /**
   * \fn void print (ostream& s) const
   * \brief Prints the group elements to s.
   * \param s: an output stream.
   */
  void print(ostream& s) const {
    s << "Group(" << name << ")" << endl;
    class list<X*>::const_iterator b = this->cbegin(), e = this->cend();
    for (; b!=e; ++b) {
      (*b)->print(s); s << endl;
    }
  };
};

#endif
