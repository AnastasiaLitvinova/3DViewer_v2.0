#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <memory>
#include <sstream>

#include "object.h"

/** @namespace s21 */
namespace s21 {
/**
 * @class  VirtualParser
 * @brief  Abstract class for parsing models
 * @details This class represents an abstract class for parsing models.
 */
class VirtualParser {
 public:
  /** @brief  Virtual destructor */
  virtual ~VirtualParser() {}
  /** @brief  Parse a string
   *  @param  edge  String to parse */
  virtual void parser(const std::string& edge) const = 0;
};

/**
 * @class  VertexParser
 * @brief  Class for parsing vertices
 * @details This class represents a class for parsing vertices.
 */
class VertexParser : public VirtualParser {
 public:
  /** @brief  Model to which the vertices will be added */
  Model& model_;

  /** @brief  Constructor
   *  @param  model  Model to which the vertices will be added */
  explicit VertexParser(Model& model) : model_{model} {}

  /** @brief  Parse a string
   *  @param  edge  String to parse */
  void parser(const std::string& edge) const override;
};

/**
 * @class  EdgeParser
 * @brief  Class for parsing edges
 * @details This class represents a class for parsing edges.
 */
class EdgeParser : public VirtualParser {
 public:
  /** @brief  Model to which the edges will be added */
  Model& model_;

  /** @brief  Constructor
   *  @param  model  Model to which the edges will be added */
  explicit EdgeParser(Model& model) : model_{model} {}

  /** @brief  Parse a string
   *  @param  edge  String to parse */
  void parser(const std::string& edge) const override;
};

/**
 * @class  ParseModel
 * @brief  Class for parsing 3D models from .obj files
 * @details This class represents a class for parsing 3D models from .obj files.
 */
class ParseModel {
 private:
  std::unique_ptr<VirtualParser> currentStrategy_;
  void setStrategy(std::unique_ptr<VirtualParser>&& strategy);

 public:
  /** @brief  Constructor */
  ParseModel() {}
  /** @brief  Destructor */
  ~ParseModel() {}

  /**
   * @brief  Load a model from .obj file
   * @param  model  Model to populate
   * @param  filename  Name of the file to read
   */
  void loadModel(Model& model, const std::string& filename);
};
}  // namespace s21

#endif  // PARSER_H
