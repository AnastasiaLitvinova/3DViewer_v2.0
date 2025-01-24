#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/manipulation.h"

/** @namespace s21 */
namespace s21 {
/**
 * @class  Controller
 * @brief  Controller class for manipulating 3D model
 * @details This class is responsible for handling user interactions and
 * updating the 3D model.
 */
class Controller {
 public:
  /** @brief Copy constructor
   *  @details This constructor is deleted, as the Controller class is a
   * singleton. */
  Controller(const Controller&) = delete;
  /** @brief Move constructor
   *  @details This constructor is deleted, as the Controller class is a
   * singleton. */
  Controller(Controller&&) = delete;
  /** @brief Copy assignment operator
   *  @details This operator is deleted, as the Controller class is a singleton.
   */
  Controller& operator=(const Controller&) = delete;
  /** @brief Get the singleton instance of the Controller class
   *  @details This function returns a reference to the only instance of the
   * Controller class. */
  static Controller& getInstance() noexcept {
    static Controller controller;
    return controller;
  }

  /**
   * @brief Manipulate the 3D model.
   * @param[in] shift The type of transformation to apply.
   * @param[in] value The value to apply to the transformation.
   */
  void manipulationModel(Shift shift, float value) {
    facade.manipulationModel(model_.vertices_, shift, value);
  }
  /** @brief Normalize the 3D model. */
  void normalization() { facade.normalization(model_.vertices_); }
  /** @brief Get the 3D model object.
   *  @return The 3D model object. */
  Model& getObject() noexcept { return model_; }
  /** @brief Load a 3D model from a file.
   *  @param[in] filename The name of the file to load. */
  void loadModel(const std::string& filename) {
    facade.loadModel(model_, filename);
  }

 private:
  Controller() noexcept = default;
  ~Controller() noexcept = default;
  Model model_{};
  ManipulationFacade facade{};
};
}  // namespace s21

#endif  // CONTROLLER_H
