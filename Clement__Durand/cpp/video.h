#ifndef _include_video_h
#define _include_video_h

/**
 * \file video.h
 * \brief Class for video files.
 * \author Clement Durand <clement.durand@telecom-paristech.fr>
 * \version 1.0
 * \date 2017-09-19
 */
#include "multimedia.h"

/**
 * \class Video video.h video.cpp
 * \brief Class for video files.
 */
class Video : public Multimedia {
  friend class Library;

private:
  int duration; /**< Duration of the video */

protected:
  /**
   * \brief Constructor
   *
   * Creates an uninitialized video object.
   */
  Video(const string& id):Multimedia(id) { duration = -1; }

  /**
   * \brief Constructor
   *
   * Creates a video object.
   *
   * \param _name: human-readable name
   * \param _path: path to media file
   * \param _duration: video duration
   */
  Video(string _name, string _path, int _duration):
  Multimedia(_name,_path) {
    duration = _duration;
  }

public:
  virtual ~Video() {}

  /**
   * \fn void setDuration (int _duration)
   * \brief Changes the video duration.
   * \param _duration: new duration.
   */
  void setDuration(int _duration) { duration = _duration; }

  /**
   * \fn int getDuration (void) const
   * \brief Returns the video duration.
   * \return The video duration contained in the object.
   */
  int getDuration() const { return duration; }

  void className(ostream& s) const override { s << "Video"; }

  void print(ostream& s) const override;
  void open() const override;

  void parse(istream& s) override;
  void unparse(ostream& s) const override;
};

#endif
