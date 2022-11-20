#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Model.h"

using std::string;
namespace s21 {
class Controller {
 public:
  Controller(Model* m) : model(m){};
  bool MakeStr(const string& input, string& output, const string& x_value);
  void CalcGraph(
      std::pair<std::vector<double>, std::vector<double>>& graph_points,
      double xBegin, double xEnd);
  void CalcCredit(string& pay, string& overpay, string& total,
                  const double& sum, int& time, int time_type, double& percent,
                  int type);
  void CalcDeposit(string& total_profit, string& total_tax, string& total_sum,
                   double deposit, int time, double percent, double tax,
                   int period, int cap, double cb, double add, double sub,
                   int add_box, int sub_box);

 private:
  Model* model;
};
}  // namespace s21

#endif  // CONTROLLER_H
