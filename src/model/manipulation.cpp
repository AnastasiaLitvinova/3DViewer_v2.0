#include "manipulation.h"

namespace s21 {
void ManipulationFacade::loadModel(Model& model, const std::string& filename) {
  parser.loadModel(model, filename);
  model.vertices_.shrink_to_fit();
  model.faces_.shrink_to_fit();
}

void ManipulationFacade::manipulationModel(std::vector<Point_3D>& vertices,
                                           Shift shift, float value) {
  if (shift == MOVE_X || shift == MOVE_Y || shift == MOVE_Z) {
    Move strategy;
    transformer.setStrategy(&strategy);
  } else if (shift == ROTATE_X || shift == ROTATE_Y || shift == ROTATE_Z) {
    Rotate strategy;
    transformer.setStrategy(&strategy);
  } else {
    Scale strategy;
    transformer.setStrategy(&strategy);
  }
  transformer.transformModel(vertices, shift, value);
}

void ManipulationFacade::normalization(std::vector<Point_3D>& vertices) {
  double maxX = -100000000, maxY = -100000000, maxZ = -100000000;
  double minX = 100000000, minY = 100000000, minZ = 100000000;
  for (const Point_3D& p : vertices) {
    maxX = maxX < p.x_ ? p.x_ : maxX;
    maxY = maxY < p.y_ ? p.y_ : maxY;
    maxZ = maxZ < p.z_ ? p.z_ : maxZ;
    minX = minX > p.x_ ? p.x_ : minX;
    minY = minY > p.y_ ? p.y_ : minY;
    minZ = minZ > p.z_ ? p.z_ : minZ;
  }
  double centerX = minX + (maxX - minX) / 2;
  double centerY = minY + (maxY - minY) / 2;
  double centerZ = minZ + (maxZ - minZ) / 2;
  double dmax = std::max(maxX - minX, maxY - minY);
  dmax = std::max(dmax, maxZ - minZ);
  double scal = (0.5 - (0.5 * (-1))) / dmax;
  for (Point_3D& p : vertices) {
    p.x_ -= centerX;
    p.x_ *= scal;
    p.y_ -= centerY;
    p.y_ *= scal;
    p.z_ -= centerZ;
    p.z_ *= scal;
  }
}
}  // namespace s21
