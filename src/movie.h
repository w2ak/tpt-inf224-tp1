#ifndef _include_movie_h
#define _include_movie_h

/**
 * \file movie.h
 * \brief Class for video files.
 * \author Clement Durand <clement.durand@telecom-paristech.fr>
 * \version 1.0
 * \date 2017-09-19
 */
#include "video.h"

/**
 * \class Movie movie.h movie.cpp
 * \brief Class for movie files.
 */
class Movie : public Video {
  friend class Library;

private:
  int* chapters=nullptr; /**< Duration of chapters */
  int  chapn=0;          /**< Number of chapters */

protected:
  /**
   * \brief Constructor
   *
   * Creates an uninitialized video object.
   */
  Movie():Video() {};

  /**
   * \brief Constructor
   *
   * Creates a movie object.
   *
   * \param _name: human-readable name
   * \param _path: path to media file
   * \param _duration: movie duration
   */
  Movie(string _name, string _path, int _duration):
  Video(_name,_path,_duration) {};

  /**
   * \brief Copy Constructor
   *
   * Copies a movie object.
   *
   * \param obj: the original Movie object.
   */
  Movie(const Movie &obj):Video(obj) {
    chapn = 0;
    if (obj.chapters != nullptr)
      this->setChapters(obj.chapters, obj.chapn);
  };

public:
  ~Movie() { delete[] chapters; };

  /**
   * \fn void setChapters (int _duration)
   * \brief Changes the movie chapters durations.
   * \param _chapters: new list of durations.
   * \param _chapn: number of chapters.
   */
  void setChapters(const int* chapters, unsigned int chapn);

  /**
   * \fn int getChapterCount (void)
   * \brief Gives the number of chapters.
   * \return The number of chapters chapn.
   */
  int getChapterCount() { return chapn; };

  /**
   * \fn int getChapter (int i)
   * \brief Gives length of chapter i.
   * \return The length of chapter i chapters[i-1].
   */
  int getChapter(int i) { return ((0<i) && (i<=chapn)) ? chapters[i-1] : -1; };

  void className(ostream& s) const override { s << "Movie"; }

  void print(ostream& s) const override;
};

#endif
