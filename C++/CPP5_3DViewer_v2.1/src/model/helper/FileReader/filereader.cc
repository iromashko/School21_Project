#include "filereader.h"

#include <fstream>
#include <sstream>

namespace s21 {
std::pair<ObjectDataModel, bool> FileReader::Read(const std::string& path) {
  auto file_type = FileChecker::GetChecker(path).Check();
  FileChecker::PrintType(file_type);
  _type = file_type;
  if (file_type == ObjectFileType::with_error) {
    return {ObjectDataModel(), false};
  } else if (file_type == ObjectFileType::with_all) {
    return Read(path, _with_all());
  } else if (file_type == ObjectFileType::with_normal) {
    return Read(path, _with_normal());
  } else if (file_type == ObjectFileType::without_texture_normal) {
    return Read(path, _without_texture_normal());
  } else {
    return {ObjectDataModel(), false};
  }
}

std::pair<ObjectDataModel, bool> FileReader::Read(const std::string& path,
                                                  FileReader::_with_all) {
  std::ifstream file(path);

  std::vector<Vec3> vertexes_position;
  std::vector<Vec2> vertexes_texture;
  std::vector<Vec3> vertexes_normal;

  std::vector<unsigned int> vertex_position_indexes;
  std::vector<unsigned int> vertex_texture_indexes;
  std::vector<unsigned int> vertex_normal_indexes;

  std::string line;
  std::string prefix;
  std::stringstream ss;

  Vec3 vec3;
  Vec2 vec2;

  ObjectDataModel object_data;
  object_data.SetType(_type);

  while (std::getline(file, line)) {
    ss.clear();
    ss.str(line);
    ss >> prefix;

    if (prefix == "v") {
      ss >> vec3.x >> vec3.y >> vec3.z;
      object_data.SetVertexesCount(object_data.GetVertexesCount() + 1);
      vertexes_position.push_back(vec3);
    } else if (prefix == "vn") {
      ss >> vec3.x >> vec3.y >> vec3.z;
      vertexes_normal.push_back(vec3);
    } else if (prefix == "vt") {
      ss >> vec2.x >> vec2.y;
      vertexes_texture.push_back(vec2);
    } else if (prefix == "f") {
      object_data.SetFacetsCount(object_data.GetFacetsCount() + 1);
      unsigned int index = 0u, counter = 0u;
      while (ss >> index) {
        if (counter == 0u)
          vertex_position_indexes.push_back(index);
        else if (counter == 1u)
          vertex_texture_indexes.push_back(index);
        else if (counter == 2u)
          vertex_normal_indexes.push_back(index);

        if (ss.peek() == '/') {
          ++counter;
          ss.ignore(1, '/');
        } else if (ss.peek() == ' ') {
          ++counter;
          ss.ignore(1, ' ');
        }

        if (counter > 2) {
          counter = 0u;
        }
      }
    }
  }

  object_data.ResizeVertexes(vertex_position_indexes.size());
  for (std::size_t i = 0; i != object_data.SizeVertexes(); ++i) {
    object_data.SetVertex(
        i, VertexData(Vec3(vertexes_position[vertex_position_indexes[i] - 1]),
                      Vec2(vertexes_texture[vertex_texture_indexes[i] - 1]),
                      Vec3(vertexes_normal[vertex_normal_indexes[i] - 1])));
    object_data.SetIndex(object_data.SizeIndexes());
  }

  file.close();
  return {object_data, true};
}

std::pair<ObjectDataModel, bool> FileReader::Read(const std::string& path,
                                                  FileReader::_with_normal) {
  std::ifstream file(path);

  std::vector<Vec3> vertexes_position;
  std::vector<Vec3> vertexes_normal;

  std::vector<unsigned int> vertex_position_indexes;
  std::vector<unsigned int> vertex_normal_indexes;

  std::string line;
  std::string prefix;
  std::stringstream ss;

  Vec3 vec3;

  ObjectDataModel object_data;
  object_data.SetType(_type);

  while (std::getline(file, line)) {
    ss.clear();
    ss.str(line);
    ss >> prefix;

    if (prefix == "v") {
      ss >> vec3.x >> vec3.y >> vec3.z;
      object_data.SetVertexesCount(object_data.GetVertexesCount() + 1);
      vertexes_position.push_back(vec3);
    } else if (prefix == "vn") {
      ss >> vec3.x >> vec3.y >> vec3.z;
      vertexes_normal.push_back(vec3);
    } else if (prefix == "f") {
      object_data.SetFacetsCount(object_data.GetFacetsCount() + 1);
      std::size_t index = 0u;
      while (ss >> index) {
        vertex_position_indexes.push_back(index);
        ss.ignore(2);
        ss >> index;
        vertex_normal_indexes.push_back(index);
        ss.ignore(1);
      }
    }
  }

  object_data.ResizeVertexes(vertex_position_indexes.size());
  for (std::size_t i = 0; i != object_data.SizeVertexes(); ++i) {
    object_data.SetVertex(
        i, VertexData(Vec3(vertexes_position[vertex_position_indexes[i] - 1]),
                      Vec2(1.f, 1.f),
                      Vec3(vertexes_normal[vertex_normal_indexes[i] - 1])));
    object_data.SetIndex(object_data.SizeIndexes());
  }

  file.close();
  return {object_data, true};
}

std::pair<ObjectDataModel, bool> FileReader::Read(
    const std::string& path, FileReader::_without_texture_normal) {
  std::ifstream file(path);

  std::vector<Vec3> vertexes_position;

  std::vector<unsigned int> vertex_position_indexes;

  std::string line;
  std::string prefix;
  std::stringstream ss;

  Vec3 vec3;

  ObjectDataModel object_data;
  object_data.SetType(_type);

  while (std::getline(file, line)) {
    ss.clear();
    ss.str(line);
    ss >> prefix;

    if (prefix == "v") {
      ss >> vec3.x >> vec3.y >> vec3.z;
      object_data.SetVertexesCount(object_data.GetVertexesCount() + 1);
      vertexes_position.push_back(vec3);
    } else if (prefix == "f") {
      object_data.SetFacetsCount(object_data.GetFacetsCount() + 1);
      std::size_t index = 0u;
      while (ss >> index) {
        vertex_position_indexes.push_back(index);
        ss.ignore(1);
      }
    }
  }

  object_data.ResizeVertexes(vertex_position_indexes.size());
  for (std::size_t i = 0; i != object_data.SizeVertexes(); ++i) {
    object_data.SetVertex(
        i, VertexData(Vec3(vertexes_position[vertex_position_indexes[i] - 1]),
                      Vec2(1.f, 1.f), Vec3(0.f, 0.f, 0.f)));
    object_data.SetIndex(object_data.SizeIndexes());
  }
  object_data.SetNormals();

  file.close();
  return {object_data, true};
}
}  // namespace s21
