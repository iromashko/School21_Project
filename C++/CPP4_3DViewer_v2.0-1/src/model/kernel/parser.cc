#include "parser.h"

//#include <ctime>
#include <sstream>

class exception_empty_file : public std::logic_error {
 public:
  exception_empty_file(const std::string &what_arg)
      : std::logic_error(what_arg) {}
};

void s21::Parser::OpenFile(std::string &input_file) {
  //  unsigned int start_time = clock();  // начальное время
  //  std::cout << "s21::Parser::OpenFile\n";  // !!!

  std::vector<double> &vertex = DataModel::GetInstance()->AccessVertex();
  std::vector<unsigned int> &facets = DataModel::GetInstance()->AccessFacets();
  vertex.clear();
  facets.clear();
  SetDataVertexAndFacet(input_file, vertex, facets);
  if (vertex.size() == 3 || facets.empty())
    throw exception_empty_file("File is empty");

  //  unsigned int end_time = clock();  // конечное время
  //  std::cout << "OpenFile TIME = " << end_time - start_time;  // искомое
}

void s21::Parser::SetDataVertexAndFacet(std::string &input_file,
                                        std::vector<double> &vertex,
                                        std::vector<unsigned int> &facets) {
  std::ifstream s_file(input_file);
  if (!s_file.is_open()) {
    throw std::invalid_argument("SetDataVertexAndFacet: file open error");
  }

  vertex.push_back(0);
  vertex.push_back(0);
  vertex.push_back(0);

  std::string line;
  int count{};

  while (getline(s_file, line)) {
    std::stringstream s_stream(line);
    std::string token;
    int f_temp{};

    // vertex c++
    if (line[0] == 'v' && line[1] == ' ') {
      while (getline(s_stream, token, ' ')) {
        if (token == "v") continue;
        vertex.push_back(std::stod(token));
      }
    }

    //     facets c++
    if (line[0] == 'f' && line[1] == ' ') {
      count = 0;
      while (getline(s_stream, token, ' ')) {
        if (token == "f") {
          ++count;
          continue;
        }
        if (count == 1) {
          f_temp = std::stoi(token);
          facets.push_back(f_temp);
          ++count;
        } else {
          facets.push_back(std::stoi(token));
          facets.push_back(std::stoi(token));
        }
      }
      facets.push_back(f_temp);
    }

  }  // end while
  s_file.close();
}
