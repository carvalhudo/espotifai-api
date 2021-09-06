/**
 * @file
 *
 * @brief This file defines a set of common types used along the api and client
 * code.
 */
#ifndef TYPES_H_
#define TYPES_H_

#include <string>

namespace espotifai_api {

/**
 * @brief This structure holds informations about a single music.
 */
struct MusicInfo {
  std::string name;
  std::string artist;
  std::string uri;
  int duration;

  bool operator==(const MusicInfo& other) const {
    return (name == other.name && artist == other.artist && uri == other.uri &&
            duration == other.duration);
  }
};

}  // namespace espotifai_api

#endif  // TYPES_H_
