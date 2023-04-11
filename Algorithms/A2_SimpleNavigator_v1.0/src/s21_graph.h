// #ifndef S21_GRAHP_H
// #define S21_GRAHP_H
#pragma once

#include <fstream>
// #include <iostream>
#include <sstream>
#include <vector>

#include "s21_containers/s21_containers.h"

class Graph {
 public:
  Graph();
  Graph &operator=(const Graph &);
  Graph(const Graph &);
  Graph &operator=(Graph &&);
  Graph(Graph &&);
  ~Graph();
  // загрузка графа из файла в формате матрицы смежности:
  int loadGraphFromFile(std::string);
  // выгрузка графа в файл в формате dot:
  int exportGraphToDot(std::string);
  std::vector<std::vector<int> > &getGraph();
  unsigned int getSizeGraph();

 private:
  std::vector<std::vector<int> > graph_;
  unsigned int size_;
  std::vector<int> makeVector(std::string const &, char);
  std::string convertGraphToDot();
};

// #endif