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
  ~Library() {};

  /**
   * \fn int size
   */
  int size(void) const {
    return files.size();
  }

  /**
   * \fn int hasFile
   *
   * \brief Returns 1 if multimedia name is in the files.
   * \param _name: name of the multimedia file
   */
  int hasFile(string _name) const { return files.count(_name); };

  /**
   * \fn shared_ptr<Multimedia> getFile
   *
   * \brief Returns the multimedia file corresponding to the name.
   * \param _name: name of the multimedia file
   */
  shared_ptr<Multimedia> getFile(string _name) const {
    if (hasFile(_name)) return files.at(_name);
    throw invalid_argument("File not found.");
  };

  /**
   * \fn void fileInfo
   *
   * \brief Prints file info in output stream.
   * \param _name: name of the multimedia file
   * \param ss: output stream to print to
   */
  void fileInfo(string _name, ostream& ss) const { getFile(_name)->print(ss); };

  /**
   * \fn void open
   *
   * \brief Opens a multimedia file.
   */
  void open(string _name) const { getFile(_name)->open(); };

  /**
   * \fn int hasGroup
   *
   * \brief Returns 1 if group name is in the groups.
   * \param _name: name of the group
   */
  int hasGroup(string _name) const { return groups.count(_name); };

  /**
   * \fn shared_ptr<Group<Multimedia>> getGroup
   *
   * \brief Returns the group corresponding to the name.
   * \param _name: name of the group
   */
  shared_ptr<Group<Multimedia>> getGroup(string _name) const {
    if (hasGroup(_name)) return groups.at(_name);
    throw invalid_argument("Group not found.");
  };

  /**
   * \fn void groupInfo
   *
   * \brief Prints group info in output stream.
   * \param _name: name of the group
   * \param ss: output stream to print to
   */
  void groupInfo(string _name, ostream& ss) const { getGroup(_name)->print(ss); };

  /**
   * \fn shared_ptr<Multimedia> addPicture
   *
   * \brief Adds a Picture to the library.
   * \see Picture::Picture(string _name, string _path, double lat, double lon)
   */
  const shared_ptr<Multimedia> addPicture(string _name, string _path, double lat, double lon) {
    if (!hasFile(_name))
      files[_name] = shared_ptr<Multimedia>(new Picture(_name,_path,lat,lon));
    return files.at(_name);
  };

  /**
   * \fn shared_ptr<Multimedia> addVideo
   *
   * \brief Adds a Video to the library.
   * \see Video::Video(string _name, string _path, int _duration)
   */
  const shared_ptr<Multimedia> addVideo(string _name, string _path, int _duration) {
    if (!hasFile(_name))
      files[_name] = shared_ptr<Multimedia>(new Video(_name, _path, _duration));
    return files.at(_name);
  };

  /**
   * \fn shared_ptr<Multimedia> addMovie
   *
   * \brief Adds a Movie to the library.
   * \see Movie::Movie(string _name, string _path, int _durationstring _name, string _path, int _duration)
   */
  const shared_ptr<Multimedia> addMovie(string _name, string _path, int _duration) {
    if (!hasFile(_name))
      files[_name] = shared_ptr<Multimedia>(new Movie(_name, _path, _duration));
    return files.at(_name);
  };

  /**
   * \fn shared_ptr<Group<Multimedia>> addGroup
   *
   * \brief Adds a Group to the library.
   * \see Group::Group(string name)
   */
  const shared_ptr<Group<Multimedia>> addGroup(string _name) {
    if (!hasGroup(_name))
      groups[_name] = shared_ptr<Group<Multimedia>>(new Group<Multimedia>(_name));
    return groups.at(_name);
  };
};
#endif
