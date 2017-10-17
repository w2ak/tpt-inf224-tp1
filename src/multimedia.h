#ifndef _include_multimedia_h
#define _include_multimedia_h

/**
 * \file multimedia.h
 * \brief Generic class for multimedia files.
 * \author Clement Durand <clement.durand@telecom-paristech.fr>
 * \version 1.0
 * \date 2017-09-19
 */
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

/**
 * \class Multimedia multimedia.h multimedia.cpp
 * \brief Class for generic multimedia files.
 */
class Multimedia {
private:
  string id;
protected:
  bool initialized = false; /**< true iff the path has been initialized */
  string name = string();   /**< human readable name */
  string path = string();   /**< path of the media file */

  /**
   * \brief Constructor
   *
   * Creates an uninitialized media object.
   */
  Multimedia(const string& _id) { id = _id; }

  /**
   * \brief Constructor
   *
   * Creates a media object with a path and a name.
   *
   * \param _name: human-readable name
   * \param _path: path to media file
   */
  Multimedia(string _name, string _path):Multimedia(_name) {
    name = _name;
    path = _path;
    initialized = true;
  }

public:
  /**
   * \brief Destructor
   */
  virtual ~Multimedia() {}

  /**
   * \fn void setPath (string p)
   * \brief Changes the media file path.
   * \param p: New path.
   */
  void setPath(string p) { path=p; initialized=true; }

  /**
   * \fn string getPath (void) const
   * \brief Returns the media file path.
   * \return The media file path of the object.
   */
  string getPath() const { return path; }

  /**
   * \fn void setName (string n)
   * \brief Changes the display name.
   * \param n: New name.
   */
  void setName(string n) { name=n; }

  /**
   * \fn string getName (void) const
   * \brief Returns the display name.
   * \return The display name of the object.
   */
  string getName() const { return name; }

  /**
   * \fn string getID (void) const
   * \brief Returns the object id.
   * \return The object id.
   */
  string getID() const { return id; }

  /**
   * \fn int check (void) const
   * \brief Checks that the object is an existing file.
   * \return 0 iff the path in the object exists.
   */
  int check() const;

  /**
   * \fn virtual void className (ostream& s) const
   * \brief Prints the class name in s.
   * \param s: an output stream.
   */
  virtual void className(ostream& s) const = 0;

  /**
   * \fn virtual void print (ostream& s) const
   * \brief Prints the object description in s.
   * \param s: an output stream.
   */
  virtual void print(ostream& s) const {
    this->className(s);
    s << "(" << name << ") @ " << path;
  }

  /**
   * \fn virtual void open (void) const
   * \brief Tries to open the media file.
   */
  virtual void open() const = 0;

  /**
   * \fn virtual void parse (istream& s)
   * \brief Parses string into object
   *
   * \param s: an input stream.
   */
  virtual void parse(istream& s) {
    char sep = ';';
    getline(s,name,sep);
    getline(s,path,sep);
  }

  /**
   * \fn virtual void unparse (ostream& s)
   * \brief Serializes object into string
   *
   * \param s: an output stream.
   */
  virtual void unparse(ostream& s) const {
    char sep = ';';
    string n = name;
    replace(n.begin(),n.end(),sep,' ');
    string p = path;
    replace(p.begin(),p.end(),sep,' ');
    className(s);
    s << sep << n << sep << p << sep;
  }
};

#endif
