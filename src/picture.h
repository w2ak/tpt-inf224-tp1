#ifndef _include_picture_h
#define _include_picture_h

/**
 * \file picture.h
 * \brief Class for picture files.
 * \author Clement Durand <clement.durand@telecom-paristech.fr>
 * \version 1.0
 * \date 2017-09-19
 */
#include "multimedia.h"

/**
 * \class Picture picture.h picture.cpp
 * \brief Class for picture files.
 */
class Picture : public Multimedia {
  friend class Library;

private:
  double latitude;  /**< Latitude of the shoot location */
  double longitude; /**< Longitude of the shoot location */

protected:
  /**
   * \brief Constructor
   *
   * Creates an uninitialized picture object.
   */
  Picture():Multimedia() {
    latitude = 0;
    longitude = 0;
  };

  /**
   * \brief Constructor
   *
   * Creates a picture object.
   *
   * \param _name: human-readable name
   * \param _path: path to media file
   * \param lat: latitude of the shoot location
   * \param lon: latitude of the shoot location
   */
  Picture(string _name, string _path, double lat, double lon):
  Multimedia(_name,_path) {
    latitude = lat;
    longitude = lon;
  };

public:
  ~Picture() {};

  /**
   * \fn void setPosition (double lat, double lon)
   * \brief Changes the picture location.
   * \param lat: latitude of the shoot location
   * \param lon: latitude of the shoot location
   */
  void setPosition(double lat, double lon) {
    latitude = lat;
    longitude = lon;
  };

  /**
   * \fn void getPosition (double * lat, double * lon)
   * \brief Gives the picture location.
   * \param lat: a valid double address
   * \param lon: a valid double address
   *
   * Puts the picture's location in lat and lon.
   */
  void getPosition(double * lat, double * lon) {
    *lat = latitude;
    *lon = longitude;
  };

  void className(ostream& s) const override { s << "Picture"; }

  void print(ostream& s) const override;
  void open() const override;
};

#endif
