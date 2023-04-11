#ifndef SRC_GTEST_H_
#define SRC_GTEST_H_

#include <gtest/gtest.h>

#include "../model/helper/FileReader/filereader.h"

class Test : public ::testing::Test {
 protected:
  // double zoom = 3.0;
  // auto result = s21::FileReader::GetReader().Read("cube-2.obj");

 public:
  Test() {
    // auto result = s21::FileReader::GetReader().Read("cube-2.obj");
    //  parser.parseFile("cube-2.obj");
  }
  ~Test() {}
  void SetUp() {}
  void TearDown() {}
};

#endif  // SRC_GTEST_H_
