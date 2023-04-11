#ifndef INC_3DVIEWER_V2_0_SRC_MODEL_KERNEL_PARSER_H_
#define INC_3DVIEWER_V2_0_SRC_MODEL_KERNEL_PARSER_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../dao/data_model.h"

namespace s21 {

class Parser {
 public:
  void OpenFile(std::string& input_file);
  void SetDataVertexAndFacet(std::string& input_file,
                             std::vector<double>& vertex,
                             std::vector<unsigned int>& facets);
};

}  // namespace s21

#endif  // INC_3DVIEWER_V2_0_SRC_MODEL_KERNEL_PARSER_H_
