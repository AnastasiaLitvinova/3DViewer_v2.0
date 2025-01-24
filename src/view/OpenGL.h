#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWheelEvent>
#include <QWidget>
#include <iostream>

#include "../controller/controller.h"

/** @namespace s21 */
namespace s21 {
class MainWindow;
/**
 * @class  MyOpenGLWidget
 * @brief  OpenGL widget for 3D visualization
 * @details This class represents an OpenGL widget for 3D visualization.
 */
class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
  /**
   * @brief Friend class for s21::MainWindow
   * @details This class is a friend class of s21::MainWindow, so it can access
   *          private members of s21::MainWindow.
   */
  friend class MainWindow;

 public:
  /** @brief Constructor for the MyOpenGLWidget class
   *  @details This constructor creates an instance of the MyOpenGLWidget class.
   */
  MyOpenGLWidget() : c{Controller::getInstance()} {}
  /** @brief Destructor for the MyOpenGLWidget class
   *  @details This destructor destroys an instance of the MyOpenGLWidget class.
   */
  ~MyOpenGLWidget() = default;

 protected:
  /** @brief Initializes the OpenGL context.
   *  @details Called once before the first rendering, to set up the OpenGL
   * state. */
  void initializeGL() override;
  /** @brief Renders the OpenGL scene.
   *  @details Called whenever the widget needs to be updated, responsible for
   * all drawing operations. */
  void paintGL() override;

  /**
   * @brief Handles mouse movement events.
   * @param mouse The event containing information about the mouse movement.
   * @details Used for interaction, such as rotating the view based on mouse
   * movement.
   */
  void mouseMoveEvent(QMouseEvent* mouse) override;
  /**
   * @brief Handles mouse press events.
   * @param mouse The event containing information about the mouse press.
   * @details Captures the initial position of the mouse when pressed.
   */
  void mousePressEvent(QMouseEvent* mouse) override;
  /**
   * @brief Handles mouse wheel events.
   * @param event The event containing information about the wheel movement.
   * @details Used for zooming in and out of the view.
   */
  void wheelEvent(QWheelEvent* event) override;

 private:
  s21::Controller& c;
  QPoint mouse_;
  QColor m_backgroundColor = QColor::fromRgb(0, 0, 0);
  QColor m_pointColor = QColor::fromRgb(255, 255, 255);
  QColor m_edgeColor = QColor::fromRgb(255, 255, 255);
  float m_zoom = 1.0f;
  float m_pointSize = 1.0f;
  float m_lineSize = 1.0f;
  bool stripLine = false;
  bool orthoProjection = false;
  bool circleVertex = false;
  bool squareVertex = false;
  void UpdateProjection();
  void DrawEdges();
  void DrawVertexes();
};
}  // namespace s21

#endif  // MYOPENGLWIDGET_H
