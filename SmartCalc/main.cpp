#include <QApplication>
#include <QFile>

#include "View.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  s21::Controller controller(&model);
  s21::MainWindow view(&controller);

  view.show();
  return a.exec();
}
