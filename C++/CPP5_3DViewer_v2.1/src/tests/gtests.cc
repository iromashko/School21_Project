#include "gtests.h"

#include <filesystem>

#include "../model/helper/FileReader/filereader.h"
#include "../model/helper/TransformModel/transformmodel.h"

TEST_F(Test, ParseFile1) {
  auto result = s21::FileReader::GetReader().Read(
      std::filesystem::absolute("tests/cube.obj"));
  ASSERT_DOUBLE_EQ(result.first.GetVertexesCount(), 8);
  ASSERT_DOUBLE_EQ(result.first.GetFacetsCount(), 12);
}

TEST_F(Test, ParseFile2) {
  auto result = s21::FileReader::GetReader().Read(
      std::filesystem::absolute("tests/cube2.obj"));
  ASSERT_DOUBLE_EQ(result.first.GetVertexesCount(), 9);
  ASSERT_DOUBLE_EQ(result.first.GetFacetsCount(), 10);
}

TEST_F(Test, ParseFile3) {
  auto result = s21::FileReader::GetReader().Read(
      std::filesystem::absolute("tests/FinalBaseMesh.obj"));
  ASSERT_DOUBLE_EQ(result.first.GetVertexesCount(), 24461);
  ASSERT_DOUBLE_EQ(result.first.GetFacetsCount(), 24459);
}

TEST_F(Test, TransformZoom) {
  auto result = s21::FileReader::GetReader().Read(
      std::filesystem::absolute("tests/cube.obj"));
  double zoom = 3.0;
  result.first.SetNormals();
  s21::TransformModel::GetTransform().Scale(result.first, zoom);
  ASSERT_DOUBLE_EQ(result.first.GetVertexes()[0].position.x, zoom);
}

TEST_F(Test, TransformRotate) {
  auto result = s21::FileReader::GetReader().Read(
      std::filesystem::absolute("tests/cube.obj"));
  s21::TransformModel::GetTransform().Rotate(result.first, 125.2, true, false,
                                             false);
  s21::TransformModel::GetTransform().Rotate(result.first, 12.2, false, true,
                                             false);
  s21::TransformModel::GetTransform().Rotate(result.first, 87.2, false, false,
                                             true);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
