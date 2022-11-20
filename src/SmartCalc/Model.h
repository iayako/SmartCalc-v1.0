#ifndef MODEL_H
#define MODEL_H

#include <cmath>
#include <cstring>
#include <iostream>
#include <stack>
#include <vector>

using std::string;
namespace s21 {
class Model {
 public:
  bool MakeStr(const string &input, string &output, const string &x_value);
  void CalcGraph(
      std::pair<std::vector<double>, std::vector<double>> &graph_points,
      double xBegin, double xEnd);
  void CalcCredit(string &pay, string &overpay, string &total,
                  const double &sum, int &time, int time_type, double &percent,
                  int type);
  void CalcDeposit(string &total_profit, string &total_tax, string &total_sum,
                   double deposit, int time, double percent, double tax,
                   int period, int cap, double cb, double add, double sub,
                   int add_box, int sub_box);

 private:
  int count_left_bracket = 0;
  int count_right_bracket = 0;
  bool is_oper = false;
  bool is_exp = false;
  string rpn_str;

  char CheckInput(const string &input);
  bool CheckPoint(const string &output, int len);
  bool CheckAccess(const string &output, int len);
  void MakeStrResult(std::string &output, bool &make_graph,
                     const string &x_value);
  void MakeStrClear(const char sym, string &output);
  void MakeStrNum(const char sym, string &output);
  void MakeStrOps(const char sym, string &output);
  void MakeStrE(const char sym, string &output);
  void MakeStrFunc(const char sym, string &output, const string &input);
  void ReversePolishNotation(const string &str);
  int GetPriority(const char sym);
  double CalcRPN(string &str);

  int GetDays(int month);
  int GetDaysUntil(int month);
  int GetMonth(int days);
  int GetDaysInQuarter(int days);
  int GetDaysInCouple(int days);
};
}  // namespace s21
#endif  // MODEL_H