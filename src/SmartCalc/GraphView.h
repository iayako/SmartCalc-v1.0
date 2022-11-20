#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QDialog>

#include "Controller.h"
#include "qcustomplot.h"

namespace Ui {
class GraphWindow;
}

namespace s21 {
class GraphWindow : public QDialog {
  Q_OBJECT

 public:
  explicit GraphWindow(Controller *c, QWidget *parent = nullptr);
  ~GraphWindow();

 private:
  Ui::GraphWindow *ui;
  double xBegin = -1000, xEnd = 1000;
  std::pair<std::vector<double>, std::vector<double>> graph_points;
  QVector<double> qfirst;
  QVector<double> qsecond;
  Controller *controller;
 public slots:
  void signal();
 private slots:
  void on_graph_button_clicked();
};
}  // namespace s21

#endif  // GRAPHWINDOW_H
