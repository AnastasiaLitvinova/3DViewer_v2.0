#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace s21 {
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  m_openGL = new s21::MyOpenGLWidget();
  ui->OpenGLWidget = m_openGL;
  ui->verticalLayout->addWidget(ui->OpenGLWidget);
  ui->OpenGLWidget->hide();
  ui->ControlWidget->setEnabled(false);
  loadSettings();
  setCentralWidget(ui->mainwidget);
}

MainWindow::~MainWindow() noexcept {
  saveSettings();
  delete ui;
}

void MainWindow::on_xRotSpinBox_valueChanged(double arg1) {
  ui->xRotSlider->setValue(arg1);
}
void MainWindow::on_yRotSpinBox_valueChanged(double arg1) {
  ui->yRotSlider->setValue(arg1);
}
void MainWindow::on_zRotSpinBox_valueChanged(double arg1) {
  ui->zRotSlider->setValue(arg1);
}

void MainWindow::on_xTransSpinBox_valueChanged(double arg1) {
  ui->xTransSlider->setValue(static_cast<int>(arg1 * 100));
}
void MainWindow::on_yTransSpinBox_valueChanged(double arg1) {
  ui->yTransSlider->setValue(static_cast<int>(arg1 * 100));
}
void MainWindow::on_zTransSpinBox_valueChanged(double arg1) {
  ui->zTransSlider->setValue(static_cast<int>(arg1 * 100));
}

void MainWindow::on_xTransSlider_valueChanged(int position) {
  static float last_val = 0.0;
  const auto delta = position / 100.0 - last_val;
  m_openGL->c.manipulationModel(MOVE_X, delta);
  last_val += delta;
  m_openGL->update();
  ui->xTransSpinBox->setValue(last_val);
}
void MainWindow::on_yTransSlider_valueChanged(int position) {
  static float last_val = 0.0;
  const auto delta = position / 100.0 - last_val;
  m_openGL->c.manipulationModel(MOVE_Y, delta);
  last_val += delta;
  m_openGL->update();
  ui->yTransSpinBox->setValue(last_val);
}
void MainWindow::on_zTransSlider_valueChanged(int position) {
  static float last_val = 0.0;
  const auto delta = position / 100.0 - last_val;
  m_openGL->c.manipulationModel(MOVE_Z, delta);
  last_val += delta;
  m_openGL->update();
  ui->zTransSpinBox->setValue(last_val);
}

void MainWindow::on_xRotSlider_valueChanged(int position) {
  static int last_val = 0;
  m_openGL->c.manipulationModel(ROTATE_X, position - last_val);
  last_val = position;
  m_openGL->update();
  ui->xRotSpinBox->setValue(position);
}

void MainWindow::on_yRotSlider_valueChanged(int position) {
  static int last_val = 0;
  m_openGL->c.manipulationModel(ROTATE_Y, position - last_val);
  last_val = position;
  m_openGL->update();
  ui->yRotSpinBox->setValue(position);
}

void MainWindow::on_zRotSlider_valueChanged(int position) {
  static int last_val = 0;
  m_openGL->c.manipulationModel(ROTATE_Z, position - last_val);
  last_val = position;
  m_openGL->update();
  ui->zRotSpinBox->setValue(position);
}

void MainWindow::on_pushButton_clicked() {
  QFileDialog dialog(this);
  dialog.setFileMode(QFileDialog::ExistingFile);
  fileName = dialog.getOpenFileName(this, "Open model", "", "model (*.obj)");
  auto &obj = m_openGL->c.getObject();
  if (!fileName.isEmpty()) {
    obj.vertices_.clear();
    obj.faces_.clear();
    ui->xTransSpinBox->setValue(0.00);
    ui->yTransSpinBox->setValue(0.00);
    ui->zTransSpinBox->setValue(0.00);
    ui->xRotSlider->setValue(0);
    ui->yRotSlider->setValue(0);
    ui->zRotSlider->setValue(0);
    ui->scaleSlider->setValue(100);
    QElapsedTimer timer;
    timer.start();
    m_openGL->c.loadModel(fileName.toStdString());
    int loadTime_ = timer.elapsed();
    if (!obj.vertices_.empty() && !obj.faces_.empty()) {
      ui->OpenGLWidget->show();
      ui->ControlWidget->setEnabled(true);
      QMessageBox::about(this, "Успех",
                         "Файл успешно загружен!<br>Время загрузки: " +
                             QString::number(loadTime_ / 100000.0, 'f', 2) +
                             " sec.");
    } else {
      ui->OpenGLWidget->hide();
      ui->ControlWidget->setEnabled(false);
      QMessageBox::critical(this, "Ошибка",
                            "Файл некорректен!\
                            <br>Попробуйте открыть другой файл.");
    }
    m_openGL->c.normalization();
    m_openGL->update();
    showModelInfo();
  } else {
    QMessageBox::warning(this, "Внимание!", "Файл не был выбран!");
  }
}
void MainWindow::on_BackGroundColor_clicked() {
  QColor color = QColorDialog::getColor(m_openGL->m_backgroundColor, this,
                                        "Choose Background Color");
  if (color.isValid()) {
    m_openGL->m_backgroundColor = color;
    ui->BackGroundColor->setStyleSheet(
        QString("height: 19px; border: 3px solid %1").arg(color.name()));
    m_openGL->update();
  }
}
void MainWindow::on_edgeColor_clicked() {
  const auto color =
      QColorDialog::getColor(Qt::white, this, "Choose Edge Color");
  if (color.isValid()) {
    m_openGL->m_edgeColor = color;
    ui->edgeColor->setStyleSheet(
        QString("height: 19px; border: 3px solid %1").arg(color.name()));
    m_openGL->update();
  }
}
void MainWindow::on_pointColor_clicked() {
  const QColor color =
      QColorDialog::getColor(Qt::white, this, "Choose Vertex Color");
  if (color.isValid() && color != m_openGL->m_pointColor) {
    m_openGL->m_pointColor = color;
    ui->pointColor->setStyleSheet(
        QString("height: 19px; border: 3px solid %1").arg(color.name()));
    m_openGL->update();
  }
}
void MainWindow::on_DashedEdges_clicked() {
  if (!m_openGL->stripLine) {
    m_openGL->stripLine = true;
    ui->DashedEdges->setText("Dashed");
  } else {
    m_openGL->stripLine = false;
    ui->DashedEdges->setText("Solid");
  }
  m_openGL->update();
}
void MainWindow::on_OrthoProjection_clicked() {
  if (!m_openGL->orthoProjection) {
    m_openGL->orthoProjection = true;
    ui->OrthoProjection->setText("Ortho");
  } else {
    m_openGL->orthoProjection = false;
    ui->OrthoProjection->setText("Perspective");
  }
  m_openGL->update();
}
void MainWindow::on_VertexTypeButton_clicked() {
  if (!m_openGL->circleVertex && !m_openGL->squareVertex) {
    ui->VertexTypeButton->setText("Square");
    m_openGL->squareVertex = true;
    m_openGL->circleVertex = false;
  } else if (m_openGL->squareVertex && !m_openGL->circleVertex) {
    ui->VertexTypeButton->setText("Circle");
    m_openGL->squareVertex = false;
    m_openGL->circleVertex = true;
  } else if (!m_openGL->squareVertex && m_openGL->circleVertex) {
    ui->VertexTypeButton->setText("None");
    m_openGL->squareVertex = false;
    m_openGL->circleVertex = false;
  }
  m_openGL->update();
}
void MainWindow::saveSettings() {
  QSettings settings("School_21", "Viewer");

  settings.setValue("BackgroundColor", m_openGL->m_backgroundColor.name());
  settings.setValue("PointColor", m_openGL->m_pointColor.name());
  settings.setValue("EdgeColor", m_openGL->m_edgeColor.name());

  settings.beginGroup("Sizes");
  settings.setValue("PointSize", m_openGL->m_pointSize);
  settings.setValue("LineSize", m_openGL->m_lineSize);
  settings.endGroup();

  settings.beginGroup("VisualOptions");
  settings.setValue("StripLine", m_openGL->stripLine);
  settings.setValue("OrthoProjection", m_openGL->orthoProjection);
  settings.setValue("CircleVertex", m_openGL->circleVertex);
  settings.setValue("SquareVertex", m_openGL->squareVertex);
  settings.endGroup();
}

void MainWindow::loadSettings() {
  QSettings settings("School_21", "Viewer");
  loadLineSettings(settings);
  loadVertexSettings(settings);
  loadBackgroundSettings(settings);

  m_openGL->orthoProjection =
      settings.value("VisualOptions/OrthoProjection").toBool();
  ui->OrthoProjection->setChecked(m_openGL->orthoProjection);

  m_openGL->c.normalization();
  showModelInfo();
}

void MainWindow::loadLineSettings(QSettings &settings) {
  m_openGL->m_pointColor = QColor(settings.value("PointColor").toString());
  ui->pointColor->setStyleSheet(QString("height: 19px; border: 3px solid %1")
                                    .arg(m_openGL->m_pointColor.name()));

  settings.beginGroup("Sizes");
  m_openGL->m_lineSize = settings.value("LineSize").toFloat();
  settings.endGroup();
  ui->edgeSizeSpinBox->setValue(m_openGL->m_lineSize);

  m_openGL->stripLine = settings.value("VisualOptions/StripLine").toBool();
  ui->DashedEdges->setChecked(m_openGL->stripLine);
}

void MainWindow::loadVertexSettings(QSettings &settings) {
  m_openGL->m_edgeColor = QColor(settings.value("EdgeColor").toString());
  ui->edgeColor->setStyleSheet(QString("height: 19px; border: 3px solid %1")
                                   .arg(m_openGL->m_edgeColor.name()));

  settings.beginGroup("Sizes");
  m_openGL->m_pointSize = settings.value("PointSize").toFloat();
  settings.endGroup();
  ui->vertexSizeSpinBox->setValue(m_openGL->m_pointSize);

  m_openGL->circleVertex =
      settings.value("VisualOptions/CircleVertex").toBool();
  m_openGL->squareVertex =
      settings.value("VisualOptions/SquareVertex").toBool();
  const QString vertexText = m_openGL->circleVertex
                                 ? "Circle"
                                 : (m_openGL->squareVertex ? "Square" : "None");
  ui->VertexTypeButton->setText(vertexText);
}

void MainWindow::loadBackgroundSettings(QSettings &settings) {
  m_openGL->m_backgroundColor =
      QColor(settings.value("BackgroundColor").toString());
  ui->BackGroundColor->setStyleSheet(
      QString("height: 19px; border: 3px solid %1")
          .arg(m_openGL->m_backgroundColor.name()));
}

void MainWindow::showModelInfo() {
  auto &obj = m_openGL->c.getObject();
  int numOfVertices = obj.vertices_.size();
  int numOfEdges = 0;
  int lastSlash = fileName.lastIndexOf('/');
  QString _fileName = fileName.mid(lastSlash + 1);
  int lastDot = _fileName.lastIndexOf('.');
  if (lastDot != -1) {
    _fileName = _fileName.left(lastDot);
  }
  for (size_t i = 0; i < obj.faces_.size(); i++)
    numOfEdges += obj.faces_[i].vertex_indices.size();
  ui->statusbar->showMessage("Model: " + _fileName +
                             "    V: " + QString::number(numOfVertices) +
                             ",  E: " + QString::number(numOfEdges / 2));
}

void MainWindow::on_ScreenShot_clicked() {
  QImage screenshot = m_openGL->grabFramebuffer();
  QFileDialog dialog(this, "Сохранить изображение", "",
                     "BMP Files (*.bmp);;JPEG Files (*.jpg *.jpeg)");
  dialog.setAcceptMode(QFileDialog::AcceptSave);

  if (dialog.exec() == QDialog::Accepted) {
    QString imageFileName = dialog.selectedFiles().first();
    QString selectedFilter = dialog.selectedNameFilter();
    if (selectedFilter.contains("BMP")) {
      if (!imageFileName.endsWith(".bmp", Qt::CaseInsensitive)) {
        imageFileName += ".bmp";
      }
    } else if (selectedFilter.contains("JPEG") ||
               selectedFilter.contains("JPG")) {
      if (!imageFileName.endsWith(".jpg", Qt::CaseInsensitive) &&
          !imageFileName.endsWith(".jpeg", Qt::CaseInsensitive)) {
        imageFileName += ".jpg";
      }
    }
    screenshot.save(imageFileName);
    QMessageBox::information(
        this, "Скриншот",
        "Скриншот успешно сохранен! <br>Путь к файлу: <br><br>" +
            imageFileName);
  }
}

void MainWindow::on_RecordGif_clicked() {
  gif = new QGifImage(QSize(640, 480));
  timer = new QTimer(this);
  frame_count = 0;

  QFileDialog dialog(this, "Сохранить анимацию", "", "GIF Files (*.gif)");
  dialog.setAcceptMode(QFileDialog::AcceptSave);

  if (dialog.exec() == QDialog::Accepted) {
    gifFileName = dialog.selectedFiles().first();
    QString selectedFilter = dialog.selectedNameFilter();
    if (!gifFileName.endsWith(".gif", Qt::CaseInsensitive)) {
      gifFileName += ".gif";
    }
    connect(timer, &QTimer::timeout, this, &MainWindow::renderFrame);
    ui->RecordGif->setEnabled(false);
    timer->start(100);
    start = QTime::currentTime();
  }
}

void MainWindow::renderFrame() {
  QImage frame(QSize(640, 480), QImage::Format_RGB888);
  if (frame_count < 50) {
    frame = m_openGL->grabFramebuffer().scaled(640, 480, Qt::IgnoreAspectRatio);
    gif->addFrame(frame, 0);
    if (frame_count % 5 == 0)
      ui->RecordGif->setText("Recording... " +
                             QString::number((50 - frame_count) / 10));
    frame_count++;
  } else {
    QTime end = QTime::currentTime();
    timer->stop();
    gif->save(gifFileName);
    frame_count = 0;
    ui->RecordGif->setText("GIF");
    ui->RecordGif->setEnabled(true);

    int duration = start.QTime::msecsTo(end) / 1000;
    int FPS = gif->frameCount() / duration;

    QMessageBox::information(
        this, "Запись завершена",
        "GIF-анимация успешно сохранена! <br>Количество кадров: " +
            QString::number(gif->frameCount()) +
            "<br>Продолжительность: " + QString::number(duration) +
            " сек.<br>FPS: " + QString::number(FPS) +
            "<br><br>Путь к файлу:<br>" + gifFileName);
  }
}

void MainWindow::on_vertexSizeSpinBox_valueChanged(double arg1) {
  m_openGL->m_pointSize = arg1;
  m_openGL->update();
}

void MainWindow::on_edgeSizeSpinBox_valueChanged(double arg1) {
  m_openGL->m_lineSize = arg1;
  m_openGL->update();
}

void MainWindow::on_scaleSpinBox_valueChanged(double arg1) {
  int val = static_cast<int>(arg1 * 100);
  ui->scaleSlider->setValue(val);
}

void MainWindow::on_scaleSlider_valueChanged(int arg1) {
  static double last_val = 1.0;
  m_openGL->c.manipulationModel(SCALE, arg1 / 100.0 / last_val);
  last_val = static_cast<double>(arg1 * 1.0 / 100);
  m_openGL->update();
  ui->scaleSpinBox->setValue(last_val);
}
}  // namespace s21
