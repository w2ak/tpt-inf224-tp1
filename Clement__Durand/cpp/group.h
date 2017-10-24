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
#include <memory>
#include "multimedia.h"

using namespace std;

/**
 * \class Group group.h
 * \class Class for groups of Multimedia objects.
 */
template <class X> class Group: public list<shared_ptr<X>> {
  friend class Library;

private:
  string name = string(); /**< Name of the group */

protected:
  Group() : list<shared_ptr<X>>() {}
  Group(string n) : list<shared_ptr<X>>() { name=n; }

public:
  ~Group() {}

  void setName(string n) { name=n; }
  string getName() const { return name; }

  void className(ostream& s) const { s << "Group"; }

  /**
   * \fn void print (ostream& s) const
   * \brief Prints the group elements to s.
   * \param s: an output stream.
   */
  void print(ostream& s) const {
    className(s);
    s << "(" << name << ")" << endl;
    typename list<shared_ptr<X>>::const_iterator b = this->cbegin(), e = this->cend();
    for (; b!=e; ++b) {
      (*b)->print(s); s << " (used by " << (*b).use_count() << ")" << endl;
    }
  }

  void unparse(ostream& s) const {
    char sep=';';
    className(s);
    s << sep;
    typename list<shared_ptr<X>>::const_iterator b = this->cbegin(), e = this->cend();
    for (; b!=e; ++b) {
      s << (*b)->getID() << sep;
    }
  }

  void parse(istream& s, function<shared_ptr<X>(const string&)> getFile) {
    char sep=';';
    string key;
    getline(s,key,sep);
    while (!key.empty()) {
      this->push_back(getFile(key));
      getline(s,key,sep);
    }
  }
};

#endif
