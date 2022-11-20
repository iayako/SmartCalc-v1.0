#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QTimer>

#include "Controller.h"
#include "GraphView.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(Controller *c, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void TimerSlot();
  void on_Button_AC_clicked();
  void on_Button_AC_pressed();
  void on_Button_AC_released();
  void signal_processing();

  void on_Button_credit_clicked();
  void on_Button_deposit_clicked();

 private:
  Ui::MainWindow *ui;
  GraphWindow *graph;
  QTimer *timer;
  int time;
  QString qstr;
  std::string output;
  Controller *controller;
};

}  // namespace s21

#endif  // VIEW_H
