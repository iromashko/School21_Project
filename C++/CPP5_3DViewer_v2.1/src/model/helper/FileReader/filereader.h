#pragma once

#include <iostream>

#include "../VertexData/vertexdata.h"
#include "filechecker.h"

namespace s21 {
class FileReader {
 private:
  FileReader(){};

 public:
  FileReader(const FileReader &) = delete;
  FileReader &operator=(const FileReader &) = delete;

  static FileReader &GetReader() {
    static FileReader reader;
    return reader;
  }

  std::pair<ObjectDataModel, bool> Read(const std::string &path);

 private:
  struct _with_all {};
  struct _with_normal {};
  struct _without_texture_normal {};

  std::pair<ObjectDataModel, bool> Read(const std::string &path, _with_all);
  std::pair<ObjectDataModel, bool> Read(const std::string &path, _with_normal);
  std::pair<ObjectDataModel, bool> Read(const std::string &path,
                                        _without_texture_normal);

  ObjectFileType _type = ObjectFileType::with_error;

  void SavePositionTextureNormal(std::stringstream &ss,
                                 const std::string &prefix,
                                 std::vector<Vec3> &pos, std::vector<Vec2> &tex,
                                 std::vector<Vec3> &nor);
  void SaveFacets(std::stringstream &ss, std::vector<unsigned int> &pos_indexes,
                  std::vector<unsigned int> &tex_indexes,
                  std::vector<unsigned int> &nor_indexes);
};
}  // namespace s21
