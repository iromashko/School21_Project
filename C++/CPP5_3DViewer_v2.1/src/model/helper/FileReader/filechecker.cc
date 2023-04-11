#include "filechecker.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace s21 {
ObjectFileType FileChecker::Check() {
  std::ifstream file(_path);
  if (!file.is_open()) {
    std::cerr << "File by path '" << _path << "' doesn't exists!" << std::endl;
    return ObjectFileType::with_error;
  }
  ObjectFileType type;

  std::string line;
  std::string prefix;
  std::stringstream ss;

  bool checked = false, have_position_vertex = false, have_facet = false,
       have_texture = false;
  while (std::getline(file, line) && !checked) {
    ss.clear();
    ss.str(line);
    ss >> prefix;
    if (!have_position_vertex && prefix == "v") {
      have_position_vertex = true;
      type = ObjectFileType::without_texture_normal;
    } else if (prefix == "vt") {
      if (type == ObjectFileType::with_normal && have_position_vertex &&
          type != ObjectFileType::with_all)
        type = ObjectFileType::with_all;
      else
        type = ObjectFileType::with_texture;
      have_texture = true;
    } else if (prefix == "vn") {
      if ((type == ObjectFileType::with_texture && have_position_vertex) ||
          type == s21::with_all)
        type = ObjectFileType::with_all;
      else
        type = ObjectFileType::with_normal;
    } else if (!have_facet && prefix == "f") {
      have_facet = true;
    }

    if (type == ObjectFileType::with_all && have_facet) {
      checked = true;
    }
  }

  if (have_texture && type == ObjectFileType::with_texture)
    type = ObjectFileType::with_all;

  if (!have_position_vertex || !have_facet || type == with_texture)
    type = ObjectFileType::with_error;

  file.close();
  return type;
}

void FileChecker::PrintType(ObjectFileType type) {
  if (type == ObjectFileType::with_all) {
    std::cout << "Object file type is: with_all\n";
  } else if (type == ObjectFileType::with_texture) {
    std::cout << "Object file type is: with_texture\n";
  } else if (type == ObjectFileType::with_normal) {
    std::cout << "Object file type is: with_normal\n";
  } else if (type == ObjectFileType::without_texture_normal) {
    std::cout << "Object file type is: without_texture_normal\n";
  } else {
    std::cout << "Object file type is: with_error\n";
  }
}
}  // namespace s21
