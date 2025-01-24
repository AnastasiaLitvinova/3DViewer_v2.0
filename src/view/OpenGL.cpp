#include "OpenGL.h"

namespace s21 {
void MyOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void MyOpenGLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  UpdateProjection();
  glClearColor(m_backgroundColor.redF(), m_backgroundColor.greenF(),
               m_backgroundColor.blueF(), 1.0f);
  if (circleVertex || squareVertex) DrawVertexes();
  DrawEdges();
}

void MyOpenGLWidget::UpdateProjection() {
  if (orthoProjection) {
    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
  } else {
    glFrustum(-0.5f, 0.5f, -0.5f, 0.5f, 0.1f, 100.f);
    glTranslated(0, 0, -1.04);
  }
}

void MyOpenGLWidget::DrawEdges() {
  auto& obj = c.getObject();
  auto& vertexes = obj.vertices_;
  auto& faces = obj.faces_;
  glColor3f(m_edgeColor.redF(), m_edgeColor.greenF(), m_edgeColor.blueF());
  glLineWidth(m_lineSize);
  for (const auto& face : faces) {
    if (stripLine) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(1, 0x00ff);
    } else
      glDisable(GL_LINE_STIPPLE);
    glBegin(GL_LINE_LOOP);
    for (size_t i = 0; i < face.vertex_indices.size(); i++) {
      int current_index = face.vertex_indices[i] - 1;
      int next_index =
          face.vertex_indices[(i + 1) % face.vertex_indices.size()] - 1;
      glVertex3d(vertexes[current_index].x_, vertexes[current_index].y_,
                 vertexes[current_index].z_);
      glVertex3d(vertexes[next_index].x_, vertexes[next_index].y_,
                 vertexes[next_index].z_);
    }
    glEnd();
  }
}

void MyOpenGLWidget::DrawVertexes() {
  glEnable(GL_BLEND);
  if (circleVertex) glEnable(GL_POINT_SMOOTH);
  if (squareVertex) glDisable(GL_POINT_SMOOTH);
  glPointSize(m_pointSize * 2);
  glColor3f(m_pointColor.redF(), m_pointColor.greenF(), m_pointColor.blueF());
  auto& obj = c.getObject();
  glBegin(GL_POINTS);
  for (size_t i = 0; i < obj.vertices_.size(); i++) {
    glVertex3d(obj.vertices_[i].x_, obj.vertices_[i].y_, obj.vertices_[i].z_);
  }
  glEnd();
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent* mouse) {
  c.manipulationModel(ROTATE_Y, (mouse->pos().x() - mouse_.x()) * 0.02);
  c.manipulationModel(ROTATE_X, (mouse->pos().y() - mouse_.y()) * 0.02);
  update();
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent* mouse) {
  mouse_ = mouse->pos();
}

void MyOpenGLWidget::wheelEvent(QWheelEvent* event) {
  if (event->angleDelta().y() < 0) {
    c.manipulationModel(SCALE, 0.9f);
  } else {
    c.manipulationModel(SCALE, 1.1f);
  }
  update();
}
}  // namespace s21
