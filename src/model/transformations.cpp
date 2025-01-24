#include "transformations.h"

namespace s21 {
void Move::transform(std::vector<Point_3D>& vertices, Shift shift,
                     float value) {
  if (shift == MOVE_X) moveX(vertices, value);
  if (shift == MOVE_Y) moveY(vertices, value);
  if (shift == MOVE_Z) moveZ(vertices, value);
}

void Move::moveX(std::vector<Point_3D>& vertices, float value) {
  for (Point_3D& p : vertices) {
    p.x_ += value;
  }
}

void Move::moveY(std::vector<Point_3D>& vertices, float value) {
  for (Point_3D& p : vertices) {
    p.y_ += value;
  }
}

void Move::moveZ(std::vector<Point_3D>& vertices, float value) {
  for (Point_3D& p : vertices) {
    p.z_ += value;
  }
}

void Rotate::transform(std::vector<Point_3D>& vertices, Shift shift,
                       float angle) {
  angle *= M_PI / 180.0f;
  if (shift == ROTATE_X) rotateX(vertices, angle);
  if (shift == ROTATE_Y) rotateY(vertices, angle);
  if (shift == ROTATE_Z) rotateZ(vertices, angle);
}

void Rotate::rotateX(std::vector<Point_3D>& vertices, float angle) {
  for (Point_3D& p : vertices) {
    float y = p.y_;
    p.y_ = p.y_ * std::cos(angle) - p.z_ * std::sin(angle);
    p.z_ = y * std::sin(angle) + p.z_ * std::cos(angle);
  }
}

void Rotate::rotateY(std::vector<Point_3D>& vertices, float angle) {
  for (Point_3D& p : vertices) {
    float x = p.x_;
    p.x_ = p.x_ * std::cos(angle) + p.z_ * std::sin(angle);
    p.z_ = -x * std::sin(angle) + p.z_ * std::cos(angle);
  }
}

void Rotate::rotateZ(std::vector<Point_3D>& vertices, float angle) {
  for (Point_3D& p : vertices) {
    float x = p.x_;
    p.x_ = p.x_ * std::cos(angle) - p.y_ * std::sin(angle);
    p.y_ = x * std::sin(angle) + p.y_ * std::cos(angle);
  }
}

void Scale::transform(std::vector<Point_3D>& vertices, Shift shift,
                      float scal) {
  if (shift == SCALE) scaleModel(vertices, scal);
}

void Scale::scaleModel(std::vector<Point_3D>& vertices, float scal) {
  for (Point_3D& p : vertices) {
    p.x_ *= scal;
    p.y_ *= scal;
    p.z_ *= scal;
  }
}

void ObjectTransformer::setStrategy(VirtualTransform* strategy) {
  strategy_ = strategy;
}

void ObjectTransformer::transformModel(std::vector<Point_3D>& vertices,
                                       Shift shift, float value) {
  strategy_->transform(vertices, shift, value);
}
}  // namespace s21
