#include <gtest/gtest.h>

#include <filesystem>
#include <iostream>
#include <memory>

#include "../model/facade.h"
#include "test_view/test_view.h"

using std::cout;
using std::endl;
using namespace s21;

/**
 * Testing occurs by creating a test view
 */
class ModelTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  TestView test_view_;
};

TEST_F(ModelTest, TestOpenFile) {
  std::string current_path(std::filesystem::current_path().generic_string());
  std::string input_file = current_path + "/obj_files/cube.obj";
  test_view_.OpenFile(input_file);
  input_file = current_path + "/obj_files/Dragon.obj";
  test_view_.OpenFile(input_file);
  input_file = current_path + "/obj_files/Heli.obj";
  test_view_.OpenFile(input_file);
  input_file = current_path + "/obj_files/cat.obj";
  test_view_.OpenFile(input_file);
}

TEST_F(ModelTest, TestOpenFileExceptionNonExistent) {
  std::string input_file = "non_existent_file.obj";
  EXPECT_ANY_THROW(test_view_.OpenFile(input_file));
}

TEST_F(ModelTest, TestOpenFileException) {
  std::string current_path(std::filesystem::current_path().generic_string());
  std::string input_file = current_path + "/tests/broken_obj_file.obj";
  EXPECT_ANY_THROW(test_view_.OpenFile(input_file));
}

TEST_F(ModelTest, TestTransformObjectMoveX) {
  std::string current_path(std::filesystem::current_path().generic_string());
  std::string input_file = current_path + "/obj_files/cube.obj";
  test_view_.OpenFile(input_file);
  std::vector<double> vertex = {0, 0, 0, 0, 0, 0, 2, 2, 0, 2, 0, 0, 0, 2,
                                0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 0, 2};
  EXPECT_EQ(vertex, DataModel::GetInstance()->GetVertex());
  std::vector<double> vertex_move_x = {0,  0, 0, -9, 0, 0, -7, 2, 0,
                                       -7, 0, 0, -9, 2, 0, -9, 2, 2,
                                       -9, 0, 2, -7, 2, 2, -7, 0, 2};
  test_view_.TransformObject(MOVE, 10, X);
  EXPECT_EQ(vertex_move_x, DataModel::GetInstance()->GetVertex());
}

TEST_F(ModelTest, TestTransformObjectMoveY) {
  std::string current_path(std::filesystem::current_path().generic_string());
  std::string input_file = current_path + "/obj_files/cube.obj";
  test_view_.OpenFile(input_file);
  std::vector<double> vertex_move_y = {0, 0,  0, 0, -9, 0, 2, -7, 0,
                                       2, -9, 0, 0, -7, 0, 0, -7, 2,
                                       0, -9, 2, 2, -7, 2, 2, -9, 2};
  test_view_.TransformObject(MOVE, 10, Y);
  EXPECT_EQ(vertex_move_y, DataModel::GetInstance()->GetVertex());
}

TEST_F(ModelTest, TestTransformObjectMoveZ) {
  std::string current_path(std::filesystem::current_path().generic_string());
  std::string input_file = current_path + "/obj_files/cube.obj";
  test_view_.OpenFile(input_file);
  std::vector<double> vertex_move_z = {0, 0, 0,  0, 0, -9, 2, 2, -9,
                                       2, 0, -9, 0, 2, -9, 0, 2, -7,
                                       0, 0, -7, 2, 2, -7, 2, 0, -7};
  test_view_.TransformObject(MOVE, 10, Z);

  EXPECT_EQ(vertex_move_z, DataModel::GetInstance()->GetVertex());
}

TEST_F(ModelTest, TestTransformObjectRotateX) {
  std::string current_path(std::filesystem::current_path().generic_string());
  std::string input_file = current_path + "/obj_files/cube.obj";
  test_view_.OpenFile(input_file);
  std::vector<double> vertex_rotate_x = {
      0.00000000, 0.00000000, 0.00000000,  0.00000000, 0.00000000, 0.00000000,
      2.00000000, 1.97537668, -0.31286893, 2.00000000, 0.00000000, 0.00000000,
      0.00000000, 1.97537668, -0.31286893, 0.00000000, 2.28824561, 1.66250775,
      0.00000000, 0.31286893, 1.97537668,  2.00000000, 2.28824561, 1.66250775,
      2.00000000, 0.31286893, 1.97537668};
  test_view_.TransformObject(ROTATE, 10, X);
  auto iter_expect_begin = vertex_rotate_x.begin();
  auto iter_calculated_begin = DataModel::GetInstance()->GetVertex().begin();
  auto iter_expect_end = vertex_rotate_x.end();
  auto iter_calculated_end = DataModel::GetInstance()->GetVertex().end();

  for (; iter_expect_begin != iter_expect_end ||
         iter_calculated_begin != iter_calculated_end;
       ++iter_expect_begin, ++iter_calculated_begin) {
    EXPECT_NEAR(*iter_expect_begin, *iter_calculated_begin, 0.0000001);
  }
}

TEST_F(ModelTest, TestTransformObjectRotateY) {
  std::string current_path(std::filesystem::current_path().generic_string());
  std::string input_file = current_path + "/obj_files/cube.obj";
  test_view_.OpenFile(input_file);
  std::vector<double> vertex_rotate_y = {
      0.00000000, 0.00000000, 0.00000000,  0.00000000, 0.00000000, 0.00000000,
      1.97537668, 2.00000000, -0.31286893, 1.97537668, 0.00000000, -0.31286893,
      0.00000000, 2.00000000, 0.00000000,  0.31286893, 2.00000000, 1.97537668,
      0.31286893, 0.00000000, 1.97537668,  2.28824561, 2.00000000, 1.66250775,
      2.28824561, 0.00000000, 1.66250775};
  test_view_.TransformObject(ROTATE, 10, Y);
  auto iter_expect_begin = vertex_rotate_y.begin();
  auto iter_calculated_begin = DataModel::GetInstance()->GetVertex().begin();
  auto iter_expect_end = vertex_rotate_y.end();
  auto iter_calculated_end = DataModel::GetInstance()->GetVertex().end();

  for (; iter_expect_begin != iter_expect_end ||
         iter_calculated_begin != iter_calculated_end;
       ++iter_expect_begin, ++iter_calculated_begin) {
    EXPECT_NEAR(*iter_expect_begin, *iter_calculated_begin, 0.0000001);
  }
}

TEST_F(ModelTest, TestTransformObjectRotateZ) {
  std::string current_path(std::filesystem::current_path().generic_string());
  std::string input_file = current_path + "/obj_files/cube.obj";
  test_view_.OpenFile(input_file);
  std::vector<double> vertex_rotate_z = {
      0.00000000, 0.00000000,  0.00000000, 0.00000000, 0.00000000,  0.00000000,
      2.28824561, 1.66250775,  0.00000000, 1.97537668, -0.31286893, 0.00000000,
      0.31286893, 1.97537668,  0.00000000, 0.31286893, 1.97537668,  2.00000000,
      0.00000000, 0.00000000,  2.00000000, 2.28824561, 1.66250775,  2.00000000,
      1.97537668, -0.31286893, 2.00000000};
  test_view_.TransformObject(ROTATE, 10, Z);
  auto iter_expect_begin = vertex_rotate_z.begin();
  auto iter_calculated_begin = DataModel::GetInstance()->GetVertex().begin();
  auto iter_expect_end = vertex_rotate_z.end();
  auto iter_calculated_end = DataModel::GetInstance()->GetVertex().end();

  for (; iter_expect_begin != iter_expect_end ||
         iter_calculated_begin != iter_calculated_end;
       ++iter_expect_begin, ++iter_calculated_begin) {
    EXPECT_NEAR(*iter_expect_begin, *iter_calculated_begin, 0.0000001);
  }
}

TEST_F(ModelTest, TestTransformObjectScale) {
  std::string current_path(std::filesystem::current_path().generic_string());
  std::string input_file = current_path + "/obj_files/cube.obj";
  test_view_.OpenFile(input_file);
  std::vector<double> vertex_scale = {
      0.00000000,  0.00000000,  0.00000000,  0.00000000,  0.00000000,
      0.00000000,  20.00000000, 20.00000000, 0.00000000,  20.00000000,
      0.00000000,  0.00000000,  0.00000000,  20.00000000, 0.00000000,
      0.00000000,  20.00000000, 20.00000000, 0.00000000,  0.00000000,
      20.00000000, 20.00000000, 20.00000000, 20.00000000, 20.00000000,
      0.00000000,  20.00000000};
  test_view_.TransformObject(SCALE, 10, {});
  auto iter_expect_begin = vertex_scale.begin();
  auto iter_calculated_begin = DataModel::GetInstance()->GetVertex().begin();
  auto iter_expect_end = vertex_scale.end();
  auto iter_calculated_end = DataModel::GetInstance()->GetVertex().end();

  for (; iter_expect_begin != iter_expect_end ||
         iter_calculated_begin != iter_calculated_end;
       ++iter_expect_begin, ++iter_calculated_begin) {
    EXPECT_NEAR(*iter_expect_begin, *iter_calculated_begin, 0.0000001);
  }
}

TEST_F(ModelTest, TestOptimizeScale) {
  std::string current_path(std::filesystem::current_path().generic_string());
  std::string input_file = current_path + "/obj_files/cube.obj";
  test_view_.OpenFile(input_file);
  double optimize_scale = 0.46383977;
  EXPECT_NEAR(optimize_scale, test_view_.GetOptimizeScale(), 0.0000001);
}