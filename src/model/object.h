#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>

/** @namespace s21 */
namespace s21 {
/**
 * @class  Point_3D
 * @brief  Point in 3D space
 * @details This class represents a point in 3D space.
 */
class Point_3D {
 public:
  /** @brief X-coordinate of the point. */
  float x_;
  /** @brief Y-coordinate of the point. */
  float y_;
  /** @brief Z-coordinate of the point. */
  float z_;

  /** @brief Default constructor initializing the point to (0,0,0). */
  Point_3D() : x_{0}, y_{0}, z_{0} {}
  /**
   * @brief Constructor initializing the point with given coordinates.
   * @param x X-coordinate of the point.
   * @param y Y-coordinate of the point.
   * @param z Z-coordinate of the point.
   */
  Point_3D(float x, float y, float z) noexcept : x_{x}, y_{y}, z_{z} {}
  /** @brief Destructor for the Point_3D class. */
  ~Point_3D() = default;
};

/**
 * @class Edge
 * @brief Represents an edge in a 3D model.
 * @details This class contains the indices of the vertices that form an edge.
 */
class Edge {
 public:
  /** @brief Indices of the vertices that form this edge. */
  std::vector<int> vertex_indices;

  /** @brief Default constructor for the Edge class. */
  Edge() : vertex_indices{} {}
  /** @brief Constructor initializing the edge with given vertex indices.
   *  @param other A vector containing indices of the vertices. */
  explicit Edge(std::vector<int>& other) : vertex_indices{other} {}
  /** @brief Destructor for the Edge class. */
  ~Edge() {}
};

/**
 * @class Model
 * @brief Represents a 3D model.
 * @details This class contains all the vertices and edges of a 3D model.
 */
class Model {
 public:
  /** @brief Vector of vertices in the 3D model. */
  std::vector<Point_3D> vertices_{};
  /** @brief Vector of edges in the 3D model. */
  std::vector<Edge> faces_{};

  /** @brief Default constructor for the Model class. */
  Model() : vertices_{}, faces_{} {}
  /** @brief Destructor for the Model class. */
  ~Model() {}
};
}  // namespace s21

#endif  // OBJECT_H
