#include "Model.h"

void s21::Model::CalcGraph(
    std::pair<std::vector<double>, std::vector<double>>& graph_points,
    double xBegin, double xEnd) {
  double step;
  if (xEnd - xBegin <= 10)
    step = 0.00001;
  else if (xEnd - xBegin <= 100)
    step = 0.0001;
  else if (xEnd - xBegin <= 1000)
    step = 0.001;
  else if (xEnd - xBegin <= 10000)
    step = 0.01;
  else if (xEnd - xBegin <= 100000)
    step = 0.1;
  else if (xEnd - xBegin > 100000)
    step = 0.5;
  for (double x = xBegin; x <= xEnd; x += step) {
    string copy = rpn_str;
    for (int i = rpn_str.size(); i >= 0; --i)
      if (rpn_str[i] == 'x') copy.replace(i, 1, std::to_string(x));
    graph_points.first.push_back(x);
    double y = CalcRPN(copy);
    graph_points.second.push_back(y);
  }
}
