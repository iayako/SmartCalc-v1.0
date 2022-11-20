#include "Controller.h"

bool s21::Controller::MakeStr(const std::string &input, std::string &output,
                              const std::string &x_value) {
  bool access = model->MakeStr(input, output, x_value);
  return access;
}

void s21::Controller::CalcGraph(
    std::pair<std::vector<double>, std::vector<double>> &graph_points,
    double xBegin, double xEnd) {
  model->CalcGraph(graph_points, xBegin, xEnd);
}

void s21::Controller::CalcCredit(std::string &pay, std::string &overpay,
                                 std::string &total, const double &sum,
                                 int &time, int time_type, double &percent,
                                 int type) {
  model->CalcCredit(pay, overpay, total, sum, time, time_type, percent, type);
}

void s21::Controller::CalcDeposit(string &total_profit, string &total_tax,
                                  string &total_sum, double deposit, int time,
                                  double percent, double tax, int period,
                                  int cap, double cb, double add, double sub,
                                  int add_box, int sub_box) {
  model->CalcDeposit(total_profit, total_tax, total_sum, deposit, time, percent,
                     tax, period, cap, cb, add, sub, add_box, sub_box);
}
