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

using namespace std;

/**
 * \class Multimedia multimedia.h multimedia.cpp
 * \brief Class for generic multimedia files.
 */
class Multimedia {
protected:
  bool initialized = false; /**< true iff the path has been initialized */
  string name;              /**< human readable name */
  string path;              /**< path of the media file */
public:
  /**
   * \brief Constructor
   *
   * Creates an uninitialized media object.
   */
  Multimedia() {
    name = "null";
    path = "/dev/null";
  };

  /**
   * \brief Constructor
   *
   * Creates a media object with a path and a name.
   *
   * \param _name: human-readable name
   * \param _path: path to media file
   */
  Multimedia(string _name, string _path) {
    name = _name;
    path = _path;
    initialized = true;
  };

  /**
   * \brief Destructor
   */
  ~Multimedia() {};

  /**
   * \fn void setPath (string p)
   * \brief Changes the media file path.
   * \param p: New path.
   */
  void setPath(string p) { path=p; initialized=true; };

  /**
   * \fn string getPath (void) const
   * \brief Returns the media file path.
   * \return The media file path of the object.
   */
  string getPath() const { return path; };

  /**
   * \fn void setName (string n)
   * \brief Changes the display name.
   * \param n: New name.
   */
  void setName(string n) { name=n; };

  /**
   * \fn string getName (void) const
   * \brief Returns the display name.
   * \return The display name of the object.
   */
  string getName() const { return name; };

  /**
   * \fn int check (void) const
   * \brief Checks that the object is an existing file.
   * \return 0 iff the path in the object exists.
   */
  int check() const;

  /**
   * \fn virtual void print (ostream& s) const
   * \brief Prints the object description in s.
   * \param s: an output stream.
   */
  virtual void print(ostream& s) const = 0;

  /**
   * \fn virtual void open (void) const
   * \brief Tries to open the media file.
   */
  virtual void open() const = 0;
};

#endif
