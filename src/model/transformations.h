#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <cmath>

#include "object.h"

/** @namespace s21 */
namespace s21 {
/** @enum Shift
 *  @brief  Enumeration for different types of transformations */
enum Shift { MOVE_X, MOVE_Y, MOVE_Z, ROTATE_X, ROTATE_Y, ROTATE_Z, SCALE };

/**
 * @class  VirtualTransform
 * @brief  Abstract class for different types of transformations
 * @details This class is an abstract class for different types of
 * transformations.
 */
class VirtualTransform {
 public:
  /**
   * @brief Apply a transformation to the vertices.
   * @param vertices Reference to a vector of 3D points to be transformed.
   * @param shift Type of transformation to apply.
   * @param value Value associated with the transformation, e.g., angle or scale
   * factor.
   */
  virtual void transform(std::vector<Point_3D>& vertices, Shift shift,
                         float value) = 0;
};

/** @class  Move
 *  @brief  Class for moving the vertices */
class Move : public VirtualTransform {
 public:
  /**
   * @brief Apply a move transformation to the vertices.
   * @param vertices Reference to a vector of 3D points to be transformed.
   * @param shift Type of transformation to apply.
   * @param value Translation value along the specified axis.
   */
  void transform(std::vector<Point_3D>& vertices, Shift shift,
                 float value) override;

 private:
  void moveX(std::vector<Point_3D>& vertices, float value);
  void moveY(std::vector<Point_3D>& vertices, float value);
  void moveZ(std::vector<Point_3D>& vertices, float value);
};

/** @class  Rotate
 *  @brief  Class for rotating the vertices */
class Rotate : public VirtualTransform {
 public:
  /**
   * @brief Apply a rotation transformation to the vertices.
   * @param vertices Reference to a vector of 3D points to be transformed.
   * @param shift Type of rotation to apply (around X, Y, or Z axis).
   * @param angle Rotation angle in degrees.
   */
  void transform(std::vector<Point_3D>& vertices, Shift shift,
                 float angle) override;

 private:
  void rotateX(std::vector<Point_3D>& vertices, float angle);
  void rotateY(std::vector<Point_3D>& vertices, float angle);
  void rotateZ(std::vector<Point_3D>& vertices, float angle);
};

/** @class  Scale
 *  @brief  Class for scaling the vertices */
class Scale : public VirtualTransform {
 public:
  /**
   * @brief Apply a scale transformation to the vertices.
   * @param vertices Reference to a vector of 3D points to be transformed.
   * @param shift Type of transformation to apply.
   * @param increment Scale factor to apply to the vertices.
   */
  void transform(std::vector<Point_3D>& vertices, Shift shift,
                 float increment) override;

 private:
  void scaleModel(std::vector<Point_3D>& vertices, float currentScale);
};

/** @class  ObjectTransformer
 *  @brief  Class for applying transformations to the vertices */
class ObjectTransformer {
  /** @brief Pointer to the current transformation strategy */
  VirtualTransform* strategy_;

 public:
  /** @brief Constructor for ObjectTransformer */
  ObjectTransformer() : strategy_(nullptr) {}

  /**
   * @brief Set the current transformation strategy
   * @param strategy Pointer to the new transformation strategy
   * @details This function sets the current transformation strategy to the
   *          given strategy.
   */
  void setStrategy(VirtualTransform* strategy);
  /**
   * @brief Apply a transformation to the vertices
   * @param vertices Reference to a vector of 3D points to be transformed
   * @param shift Type of transformation to apply
   * @param value Value to apply to the transformation
   * @details This function applies the current transformation strategy to the
   *          given vertices.
   */
  void transformModel(std::vector<Point_3D>& vertices, Shift shift,
                      float value);
};
}  // namespace s21

#endif  // TRANSFORMATIONS_H
