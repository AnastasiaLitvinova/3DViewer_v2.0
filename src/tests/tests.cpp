#include <gtest/gtest.h>

#include "../model/manipulation.h"

TEST(ManipulationFacadeTest, Move) {
  s21::ManipulationFacade facade;
  std::vector<s21::Point_3D> vertices = {s21::Point_3D{1.0, 2.0, 3.0},
                                         s21::Point_3D{4.0, 5.0, 6.0}};
  facade.manipulationModel(vertices, s21::MOVE_X, 2.0);
  EXPECT_EQ(vertices[0].x_, 3.0);
  EXPECT_EQ(vertices[1].x_, 6.0);
  facade.manipulationModel(vertices, s21::MOVE_Y, 1.0);
  EXPECT_EQ(vertices[0].y_, 3.0);
  EXPECT_EQ(vertices[1].y_, 6.0);
  facade.manipulationModel(vertices, s21::MOVE_Z, 3.0);
  EXPECT_EQ(vertices[0].z_, 6.0);
  EXPECT_EQ(vertices[1].z_, 9.0);
}

TEST(ManipulationFacadeTest, Rotate) {
  s21::ManipulationFacade facade;
  std::vector<s21::Point_3D> vertices = {s21::Point_3D{1.0, 2.0, 3.0},
                                         s21::Point_3D{4.0, 5.0, 6.0}};
  facade.manipulationModel(vertices, s21::ROTATE_X, 2.0);
  EXPECT_NEAR(vertices[0].x_, 1.0, 1e-5);
  EXPECT_NEAR(vertices[1].x_, 4.0, 1e-5);
  facade.manipulationModel(vertices, s21::ROTATE_Y, 1.0);
  EXPECT_NEAR(vertices[0].y_, 1.89408, 1e-5);
  EXPECT_NEAR(vertices[1].y_, 4.78756, 1e-5);
  facade.manipulationModel(vertices, s21::ROTATE_Z, 1.0);
  EXPECT_NEAR(vertices[0].z_, 3.05005, 1e-5);
  EXPECT_NEAR(vertices[1].z_, 6.10009, 1e-5);
}

TEST(ManipulationFacadeTest, Scale) {
  s21::ManipulationFacade facade;
  std::vector<s21::Point_3D> vertices = {s21::Point_3D{1.0, 2.0, 3.0},
                                         s21::Point_3D{4.0, 5.0, 6.0}};

  facade.manipulationModel(vertices, s21::SCALE, 0.5);
  EXPECT_NEAR(vertices[0].x_, 0.5, 1e-5);
  EXPECT_NEAR(vertices[0].y_, 1.0, 1e-5);
  EXPECT_NEAR(vertices[0].z_, 1.5, 1e-5);
  EXPECT_NEAR(vertices[1].x_, 2.0, 1e-5);
  EXPECT_NEAR(vertices[1].y_, 2.5, 1e-5);
  EXPECT_NEAR(vertices[1].z_, 3.0, 1e-5);
}

TEST(ManipulationFacadeTest, Normalization) {
  s21::ManipulationFacade facade;
  std::vector<s21::Point_3D> vertices = {s21::Point_3D{-1.0, -1.0, -1.0},
                                         s21::Point_3D{1.0, 1.0, 1.0}};

  facade.normalization(vertices);
  EXPECT_NEAR(vertices[0].x_, -0.5, 1e-5);
  EXPECT_NEAR(vertices[0].y_, -0.5, 1e-5);
  EXPECT_NEAR(vertices[0].z_, -0.5, 1e-5);
  EXPECT_NEAR(vertices[1].x_, 0.5, 1e-5);
  EXPECT_NEAR(vertices[1].y_, 0.5, 1e-5);
  EXPECT_NEAR(vertices[1].z_, 0.5, 1e-5);
}

TEST(ManipulationFacadeTest, LoadModel) {
  s21::Model m{};
  s21::ManipulationFacade model;
  std::string filename = "tests/models/test.obj";
  model.loadModel(m, filename);
  EXPECT_EQ(m.vertices_.size(), 8);
  EXPECT_NEAR(m.vertices_[0].x_, 0.0, 1e-5);
  EXPECT_NEAR(m.vertices_[0].y_, 0.0, 1e-5);
  EXPECT_NEAR(m.vertices_[0].z_, 0.0, 1e-5);
  EXPECT_NEAR(m.vertices_[1].x_, 0.0, 1e-5);
  EXPECT_NEAR(m.vertices_[1].y_, 0.0, 1e-5);
  EXPECT_NEAR(m.vertices_[1].z_, 1.0, 1e-5);
  EXPECT_NEAR(m.vertices_[2].x_, 0.0, 1e-5);
  EXPECT_NEAR(m.vertices_[2].y_, 1.0, 1e-5);
  EXPECT_NEAR(m.vertices_[2].z_, 0.0, 1e-5);
  EXPECT_NEAR(m.vertices_[3].x_, 0.0, 1e-5);
  EXPECT_NEAR(m.vertices_[3].y_, 1.0, 1e-5);
  EXPECT_NEAR(m.vertices_[3].z_, 1.0, 1e-5);
  EXPECT_NEAR(m.vertices_[4].x_, 1.0, 1e-5);
  EXPECT_NEAR(m.vertices_[4].y_, 0.0, 1e-5);
  EXPECT_NEAR(m.vertices_[4].z_, 0.0, 1e-5);
  EXPECT_NEAR(m.vertices_[5].x_, 1.0, 1e-5);
  EXPECT_NEAR(m.vertices_[5].y_, 0.0, 1e-5);
  EXPECT_NEAR(m.vertices_[5].z_, 1.0, 1e-5);
  EXPECT_NEAR(m.vertices_[6].x_, 1.0, 1e-5);
  EXPECT_NEAR(m.vertices_[6].y_, 1.0, 1e-5);
  EXPECT_NEAR(m.vertices_[6].z_, 0.0, 1e-5);
  EXPECT_NEAR(m.vertices_[7].x_, 1.0, 1e-5);
  EXPECT_NEAR(m.vertices_[7].y_, 1.0, 1e-5);
  EXPECT_NEAR(m.vertices_[7].z_, 1.0, 1e-5);
  EXPECT_EQ(m.faces_.size(), 12);
}
TEST(ManipulationFacadeTest, LoadModelError) {
  s21::Model m{};
  s21::ManipulationFacade model;
  std::string filenameError = "test_error.obj";
  model.loadModel(m, filenameError);
  EXPECT_EQ(m.vertices_.size(), 0);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
