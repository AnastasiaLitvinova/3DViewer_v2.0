#ifndef MANIPULATION_H
#define MANIPULATION_H

#include "parser.h"
#include "transformations.h"

/** @namespace s21 */
namespace s21 {
/**
 * @class  ManipulationFacade
 * @brief  Facade for manipulating 3D model
 * @details This class contains all the methods for manipulating 3D model.
 */
class ManipulationFacade {
 private:
  ParseModel parser;
  ObjectTransformer transformer;

 public:
  /** @brief This constructor creates the facade and initializes its fields. */
  ManipulationFacade() : parser{}, transformer{} {}

  /**
   * @brief  Load 3D model from file
   * @param  model   Model to load data into
   * @param  filename  Filename to load data from
   */
  void loadModel(Model& model, const std::string& filename);

  /**
   * @brief  Apply transformation to 3D model
   * @param  vertices  Vertices of the model
   * @param  shift     Type of transformation
   * @param  value     Value to apply to the transformation
   */
  void manipulationModel(std::vector<Point_3D>& vertices, Shift shift,
                         float value);

  /** @brief Normalize 3D model to fit within a unit cube centered at the origin
   *  @param vertices Vertices of the model */
  void normalization(std::vector<Point_3D>& vertices);
};
}  // namespace s21

#endif  // MANIPULATION_H
