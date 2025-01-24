#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QElapsedTimer>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QTime>
#include <QTimer>

#include "OpenGL.h"
#include "gif/qtgifimage/src/gifimage/qgifimage.h"

/**
 * @namespace Ui
 * @brief The namespace for the UI classes.
 */
QT_BEGIN_NAMESPACE
namespace Ui {
/**
 * @class MainWindow
 * @brief The UI class for the main window.
 */
class MainWindow;
}  // namespace Ui
QT_END_NAMESPACE

/**
 * @namespace s21
 * @brief The main namespace for the application.
 */
namespace s21 {
/**
 * @class MainWindow
 * @brief The main window of the application.
 *
 * This class contains the GUI and the logic for the main window.
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  /** @brief Constructor. Creates the main window.
   *  @param parent The parent widget. */
  explicit MainWindow(QWidget *parent = nullptr);

  /** @brief Destructor. Destroys the main window. */
  ~MainWindow() noexcept;

 private slots:
  /** @brief The slot for the x translation spin box.
   *  @param arg1 The new value of the spin box. */
  void on_xTransSpinBox_valueChanged(double arg1);
  /** @brief The slot for the y translation spin box.
   *  @param arg1 The new value of the spin box. */
  void on_yTransSpinBox_valueChanged(double arg1);
  /** @brief The slot for the z translation spin box.
   *  @param arg1 The new value of the spin box. */
  void on_zTransSpinBox_valueChanged(double arg1);
  /** @brief The slot for the x rotation spin box.
   *  @param arg1 The new value of the spin box. */
  void on_xRotSpinBox_valueChanged(double arg1);
  /** @brief The slot for the y rotation spin box.
   *  @param arg1 The new value of the spin box. */
  void on_yRotSpinBox_valueChanged(double arg1);
  /** @brief The slot for the z rotation spin box.
   *  @param arg1 The new value of the spin box. */
  void on_zRotSpinBox_valueChanged(double arg1);
  /** @brief The slot for the x translation slider.
   *  @param position The new position of the slider. */
  void on_xTransSlider_valueChanged(int position);
  /** @brief The slot for the y translation slider.
   *  @param position The new position of the slider. */
  void on_yTransSlider_valueChanged(int position);
  /** @brief The slot for the z translation slider.
   *  @param position The new position of the slider. */
  void on_zTransSlider_valueChanged(int position);
  /** @brief The slot for the x rotation slider.
   *  @param position The new position of the slider. */
  void on_xRotSlider_valueChanged(int position);
  /** @brief The slot for the y rotation slider.
   *  @param position The new position of the slider. */
  void on_yRotSlider_valueChanged(int position);
  /** @brief The slot for the z rotation slider.
   *  @param position The new position of the slider. */
  void on_zRotSlider_valueChanged(int position);

  /** @brief This slot is called when the load button is clicked. */
  void on_pushButton_clicked();
  /** @brief This slot is called when the background color button is clicked. */
  void on_BackGroundColor_clicked();
  /** @brief This slot is called when the edge color button is clicked. */
  void on_edgeColor_clicked();
  /** @brief This slot is called when the point color button is clicked. */
  void on_pointColor_clicked();
  /** @brief This slot is called when the dashed edges button is clicked. */
  void on_DashedEdges_clicked();
  /** @brief This slot is called when the ortho projection button is clicked. */
  void on_OrthoProjection_clicked();
  /** @brief This slot is called when the vertex type button is clicked. */
  void on_VertexTypeButton_clicked();

  /** @brief Saves the current settings to the settings file. */
  void saveSettings();
  /** @brief Loads the settings from the settings file. */
  void loadSettings();
  /** @brief Loads the line settings from the settings file.
   *  @param settings The settings object. */
  void loadLineSettings(QSettings &settings);
  /** @brief Loads the vertex settings from the settings file.
   *  @param settings The settings object. */
  void loadVertexSettings(QSettings &settings);
  /** @brief Loads the background settings from the settings file.
   *  @param settings The settings object. */
  void loadBackgroundSettings(QSettings &settings);

  /** @brief Shows the model information in the text box. */
  void showModelInfo();
  /** @brief The slot for the screenshot button. */
  void on_ScreenShot_clicked();
  /** @brief This slot is called when the record GIF button is clicked. */
  void on_RecordGif_clicked();
  /** @brief This slot is called when the GIF timer is triggered. */
  void renderFrame();
  /** @brief This slot is called when the vertex size spin box is changed.
   *  @param arg1 The new size of the vertices. */
  void on_vertexSizeSpinBox_valueChanged(double arg1);
  /** @brief This slot is called when the edge size spin box is changed.
   *  @param arg1 The new thickness of the edges. */
  void on_edgeSizeSpinBox_valueChanged(double arg1);
  /** @brief This slot is called when the scale spin box is changed.
   *  @param arg1 The new scale value. */
  void on_scaleSpinBox_valueChanged(double arg1);
  /** @brief This slot is called when the scale slider is changed.
   *  @param arg1 The new scale value. */
  void on_scaleSlider_valueChanged(int arg1);

 private:
  Ui::MainWindow *ui;
  s21::MyOpenGLWidget *m_openGL;
  QString fileName;
  QString gifFileName;
  QTimer *timer;
  QGifImage *gif;
  int frame_count;
  QTime start;
  QSettings *settings;
};
}  // namespace s21

#endif  // MAINWINDOW_H
