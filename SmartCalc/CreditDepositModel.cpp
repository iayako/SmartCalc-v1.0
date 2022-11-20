#include "Model.h"

namespace s21 {
int Model::GetDays(int month) {
  month = (month >= 0 ? month : 12 + month);
  return month == 1 ? 28 : (30 + (month > 6 ? month : month + 1) % 2);
}

int Model::GetDaysUntil(int month) {
  int res = 0;
  for (int i = 0; i < month; ++i) res += GetDays(i % 12);
  return res;
}

int Model::GetMonth(int days) {
  int month = 0;
  int m;
  days = days % 365;
  while (days > (m = GetDays(month))) {
    days -= m;
    ++month;
  }
  return month;
}

int Model::GetDaysInQuarter(int days) {
  days = days % 365;
  int answer;
  if (days < 90)
    answer = 90;
  else if (days < 181)
    answer = 91;
  else if (days < 273)
    answer = 92;
  else
    answer = 91;
  return answer;
}

int Model::GetDaysInCouple(int days) {
  int month = GetMonth(days);
  return (GetDays(month) + GetDays(month - 1));
}

void Model::CalcCredit(string& pay, string& overpay, string& total,
                       const double& sum, int& time, int time_type,
                       double& percent, int type) {
  double payment;
  if (time_type == 1) time *= 12;
  if (!type) {
    percent = percent / (1200);
    payment = sum * percent / (1 - pow(1 + percent, -time));
    pay += std::to_string(payment);
    pay.resize(pay.size() - 4);
    pay += " руб.";
    overpay += std::to_string(payment * time - sum);
    total += std::to_string(payment * time);
  } else {
    double payment_min = 0, payment_max = 0;
    double month_payment = sum / time;
    double total_num = 0;
    percent = percent / 100;
    for (int i = 0; i < time; ++i) {
      payment =
          (sum - month_payment * (i + 1)) * percent * GetDays(i % 12) / 365;
      total_num += payment + month_payment;
      if (i == 0) payment_max = payment + month_payment;
      if (i == time - 1) payment_min = payment + month_payment;
    }
    pay += std::to_string(payment_min);
    pay.resize(pay.size() - 4);
    pay += " - ";
    pay += std::to_string(payment_max);
    pay.resize(pay.size() - 4);
    pay += " руб.";
    overpay += std::to_string(total_num - sum);
    total += std::to_string(total_num);
  }
  overpay.resize(overpay.size() - 4);
  overpay += " руб.";
  total.resize(total.size() - 4);
  total += " руб.";
}

void Model::CalcDeposit(string& total_profit, string& total_tax,
                        string& total_sum, double deposit, int time,
                        double percent, double tax, int period, int cap,
                        double cb, double add, double sub, int add_box,
                        int sub_box) {
  int L, T;
  switch (period) {
    case 0:
      L = 365;
      T = GetDaysUntil(time);
      break;
    case 1:
      L = 52;
      T = GetDaysUntil(time) / 7;
      break;
    case 2:
      L = 12;
      T = time;
      break;
    case 3:
      L = 4;
      T = time / 3;
      break;
    case 4:
      L = 2;
      T = time / 6;
      break;
    case 5:
      L = 1;
      T = time / 12;
      break;
    case 6:
      L = -1;
      T = -1;
      break;
  }
  double res_sum, res_tax, res_profit = 0;
  if (!add_box && !sub_box) {
    if (cap && L != -1) {
      res_sum = deposit * pow((1 + (percent / 100) / L), T);
      res_profit = res_sum - deposit;
    } else {
      res_profit = (deposit * percent * (GetDaysUntil(time) / 365.0)) / 100;
      res_sum = deposit;
    }
  } else {
    if (cap && L != -1) {
      int count1 = 0;
      int count2 = 0;
      int count3 = 0;
      int count4 = 0;
      int count5 = 0;
      int count6 = 0;
      int count11 = 0;
      int count12 = 0;
      int count13 = 0;
      int count14 = 0;
      int count15 = 0;
      double profit;
      for (int i = 0, days = GetDaysUntil(time), d; i < days; ++i) {
        if (period == 0) {
          profit = (deposit * percent * (1 / 365.0)) / 100;
          res_profit += profit;
          deposit += profit;
          ++count1;
        } else if (period == 1 && ((i + 1) % 7 == 0)) {
          profit = (deposit * percent * (7 / 365.0)) / 100;
          res_profit += profit;
          deposit += profit;
          ++count2;
        } else if (period == 2 && ((i + 1) % (d = GetDays(GetMonth(i))) == 0)) {
          profit = (deposit * percent * (d / 365.0)) / 100;
          res_profit += profit;
          deposit += profit;
          ++count3;
        } else if (period == 3 && ((i + 1) % (d = GetDaysInQuarter(i)) == 0)) {
          profit = (deposit * percent * (d / 365.0)) / 100;
          res_profit += profit;
          deposit += profit;
          ++count4;
        } else if (period == 4 &&
                   ((i + 1) % (d = (i % 365 < 181 ? 181 : 183)) == 0)) {
          profit = (deposit * percent * (d / 365.0)) / 100;
          res_profit += profit;
          deposit += profit;
          ++count5;
        } else if (period == 5 && ((i + 1) % 365 == 0)) {
          profit = (deposit * percent) / 100;
          res_profit += profit;
          deposit += profit;
          ++count6;
        }
        if (add_box == 1 && ((i + 1) % GetDays(GetMonth(i)) == 0)) {
          deposit += add;
          ++count11;
        } else if (add_box == 2 && ((i + 1) % (GetDaysInCouple(i) == 0))) {
          deposit += add;
          ++count12;
        } else if (add_box == 3 && ((i + 1) % (GetDaysInQuarter(i)) == 0)) {
          deposit += add;
          ++count13;
        } else if (add_box == 4 &&
                   ((i + 1) % (i % 365 < 181 ? 181 : 183) == 0)) {
          deposit += add;
          ++count14;
        } else if (add_box == 5 && ((i + 1) % 365 == 0)) {
          deposit += add;
          ++count15;
        }
        if (sub_box == 1 && ((i + 1) % GetDays(GetMonth(i)) == 0))
          deposit -= sub;
        else if (sub_box == 2 && ((i + 1) % (GetDaysInCouple(i) == 0)))
          deposit -= sub;
        else if (sub_box == 3 && ((i + 1) % (GetDaysInQuarter(i)) == 0))
          deposit -= sub;
        else if (sub_box == 4 && ((i + 1) % (i % 365 < 181 ? 181 : 183) == 0))
          deposit -= sub;
        else if (sub_box == 5 && ((i + 1) % 365 == 0))
          deposit -= sub;
      }
      res_sum = deposit - add;
    } else {
      for (int i = 1; i <= time; ++i) {
        res_profit += (deposit * percent * (GetDays(i) / 365.0)) / 100;
        if (add_box == 1 && i != time)
          deposit += add;
        else if (add_box == 2 && i % 2 == 0 && i != time)
          deposit += add;
        else if (add_box == 3 && i % 3 == 0 && i != time)
          deposit += add;
        else if (add_box == 4 && i % 4 == 0 && i != time)
          deposit += add;
        else if (add_box == 5 && i % 6 == 0 && i != time)
          deposit += add;
        else if (add_box == 6 && i % 12 == 0 && i != time)
          deposit += add;
        if (sub_box == 1 && i != time)
          deposit -= sub;
        else if (sub_box == 2 && i % 2 == 0 && i != time)
          deposit -= sub;
        else if (sub_box == 3 && i % 3 == 0 && i != time)
          deposit -= sub;
        else if (sub_box == 4 && i % 4 == 0 && i != time)
          deposit -= sub;
        else if (sub_box == 5 && i % 6 == 0 && i != time)
          deposit -= sub;
        else if (sub_box == 6 && i % 12 == 0 && i != time)
          deposit -= sub;
      }
      res_sum = deposit;
    }
  }
  res_tax = res_profit - cb / 100 * 1000000;
  res_tax = res_tax > 0 ? res_tax * tax / 100 : 0;
  total_profit = std::to_string(res_profit);
  total_profit.resize(total_profit.size() - 4);
  total_tax = std::to_string(res_tax);
  total_tax.resize(total_tax.size() - 4);
  total_sum = std::to_string(res_sum);
  total_tax.resize(total_tax.size() - 4);
}
}  // namespace s21
