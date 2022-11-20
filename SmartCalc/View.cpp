#include "View.h"

#include "ui_View.h"

s21::MainWindow::MainWindow(Controller *c, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller(c) {
  ui->setupUi(this);
  ui->x_value->setValidator(new QDoubleValidator(-1000000, 1000000, 6, this));
  time = 0;
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(TimerSlot()));

  connect(ui->Button_x, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_0, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_1, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_2, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_3, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_4, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_5, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_6, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_7, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_8, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_9, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_point, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_Bleft, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_Bright, SIGNAL(clicked()), this,
          SLOT(signal_processing()));
  connect(ui->Button_add, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_sub, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_mul, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_div, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_mod, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_cos, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_sin, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_tg, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_acos, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_asin, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_atg, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_sqrt, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_pow, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_log, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_ln, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_e, SIGNAL(clicked()), this, SLOT(signal_processing()));
  connect(ui->Button_equal, SIGNAL(clicked()), this, SLOT(signal_processing()));
}

s21::MainWindow::~MainWindow() { delete ui; }

namespace s21 {

void MainWindow::on_Button_AC_clicked() {
  controller->MakeStr("C", output, ui->x_value->text().toStdString());
  ui->label->setText(&output[0]);
}

void MainWindow::on_Button_AC_pressed() {
  time = 0;
  timer->start(1);
}

void MainWindow::TimerSlot() {
  time++;
  if (time > 500) {
    timer->stop();
    time = 0;
    controller->MakeStr("E", output, ui->x_value->text().toStdString());
    ui->label->setText(&output[0]);
  }
}

void MainWindow::on_Button_AC_released() {
  timer->stop();
  time = 0;
}

void MainWindow::signal_processing() {
  QPushButton *button = (QPushButton *)sender();
  qstr = button->text();
  if (controller->MakeStr(qstr.toStdString(), output,
                          ui->x_value->text().toStdString())) {
    graph = new s21::GraphWindow(controller);
    graph->signal();
    graph->show();
  } else {
    ui->label->setText(&output[0]);
  }
}

void MainWindow::on_Button_credit_clicked() {
  ui->credit_line_sum->setValidator(
      new QDoubleValidator(-1000000, 1000000, 6, this));
  ui->credit_line_time->setValidator(
      new QDoubleValidator(-1000000, 1000000, 6, this));
  ui->credit_line_percent->setValidator(
      new QDoubleValidator(-1000000, 1000000, 6, this));
  double credit_sum = ui->credit_line_sum->text().toDouble();
  int credit_time = ui->credit_line_time->text().toInt();
  int time_box = ui->Credit_time_type_cb->currentIndex();
  double credit_percent = ui->credit_line_percent->text().toDouble();
  int type_box = ui->Credit_type_cb->currentIndex();
  std::string payment;
  std::string overpayment;
  std::string total;
  controller->CalcCredit(payment, overpayment, total, credit_sum, credit_time,
                         time_box, credit_percent, type_box);

  payment.insert(0, "Выплата: ");
  overpayment.insert(0, "Переплата:");
  total.insert(0, "Общая выплата: ");
  ui->Credit_mounth_payment->setText(&payment[0]);
  ui->Credit_overpayment->setText(&overpayment[0]);
  ui->Credit_total_payment->setText(&total[0]);
}

void MainWindow::on_Button_deposit_clicked() {
  ui->line_sum_dep->setValidator(
      new QDoubleValidator(-1000000, 1000000, 6, this));
  ui->line_time_dep->setValidator(
      new QDoubleValidator(-1000000, 1000000, 6, this));
  ui->line_percent_dep->setValidator(
      new QDoubleValidator(-1000000, 1000000, 6, this));
  ui->line_tax_dep->setValidator(
      new QDoubleValidator(-1000000, 1000000, 6, this));
  ui->line_cb->setValidator(new QDoubleValidator(-1000000, 1000000, 6, this));
  ui->add_line->setValidator(new QDoubleValidator(-1000000, 1000000, 6, this));
  ui->sub_line->setValidator(new QDoubleValidator(-1000000, 1000000, 6, this));
  double deposit = ui->line_sum_dep->text().toDouble();
  int time = ui->line_time_dep->text().toInt();
  double percent = ui->line_percent_dep->text().toDouble();
  double tax = ui->line_tax_dep->text().toDouble();
  double cb = ui->line_cb->text().toDouble();
  int period = ui->period->currentIndex();
  bool cap = ui->capitalization_2->isChecked();
  double add = ui->add_line->text().toDouble();
  double sub = ui->sub_line->text().toDouble();
  int add_box = ui->add_box->currentIndex();
  int sub_box = ui->sub_box->currentIndex();
  std::string total_profit;
  std::string total_tax;
  std::string total_sum;
  controller->CalcDeposit(total_profit, total_tax, total_sum, deposit, time,
                          percent, tax, period, cap, cb, add, sub, add_box,
                          sub_box);
  total_profit.insert(0, "Начисленные проценты: ");
  total_profit += " руб.";
  total_tax.insert(0, "Налог: ");
  total_profit += " руб.";
  total_sum.insert(0, "Сумма в конце срока: ");
  total_sum += " руб.";
  ui->total_profit->setText(&total_profit[0]);
  ui->total_tax->setText(&total_tax[0]);
  ui->total_sum->setText(&total_sum[0]);
}

}  // namespace s21
