#include "Model.h"

namespace s21 {
char Model::CheckInput(const string& input) {
  char sym;
  if (input[1] == '\0') {
    sym = input[0];
  } else if (input[0] == 'a') {
    if (input[1] == 'c') sym = 'o';
    if (input[1] == 's') sym = 'i';
    if (input[1] == 't') sym = 'a';
  } else if (input[2] == 'g') {
    sym = 'g';
  } else if (input[1] == 'q') {
    sym = 'q';
  } else {
    sym = input[0];
  }
  return sym;
}

bool Model::CheckPoint(const string& output, int len) {
  bool res = false;
  for (int i = len; i >= 0; --i) {
    if (output[i] == ' ') {
      res = false;
      break;
    }
    if (output[i] == '.') {
      res = true;
      break;
    }
  }
  return res;
}

bool Model::CheckAccess(const string& output, int len) {
  int res;
  while (output[len] != ' ' && output[len] != '(' && len != -1) --len;
  if (output[len + 1] == '0' && output[len + 2] != '.')
    res = 0;
  else
    res = 1;
  return res;
}

bool Model::MakeStr(const string& input, string& output,
                    const string& x_value) {
  bool make_graph = false;
  char sym = CheckInput(input);
  if (sym == '=' && !is_exp && is_oper && output.size() >= 1 &&
      output[output.size() - 1] != '(') {
    MakeStrResult(output, make_graph, x_value);
  } else if (sym == 'E' || sym == 'C') {
    MakeStrClear(sym, output);
  } else if (sym == 'e' || (is_exp && (sym == '+' || sym == '-' ||
                                       (sym >= '0' && sym <= '9')))) {
    MakeStrE(sym, output);
  } else if (sym == 'x' || sym == '.' || (sym >= '0' && sym <= '9')) {
    MakeStrNum(sym, output);
  } else if (sym == '+' || sym == '-' || sym == '*' || sym == '/' ||
             sym == '^' || sym == 'm') {
    MakeStrOps(sym, output);
  } else if ((sym >= 'a' && sym <= 'z' && sym != 'm' && sym != 'x') ||
             sym == '(' || sym == ')') {
    MakeStrFunc(sym, output, input);
  }
  return make_graph;
}

void Model::MakeStrResult(string& output, bool& make_graph,
                          const string& x_value) {
  if (output[output.size() - 1] != 'n' && output[output.size() - 1] != 'f') {
    while (count_left_bracket > count_right_bracket) {
      output.push_back(')');
      ++count_right_bracket;
    }
    rpn_str.clear();
    ReversePolishNotation(output);
    if (!x_value.empty())
      for (int i = rpn_str.size(); i >= 0; --i)
        if (rpn_str[i] == 'x') rpn_str.replace(i, 1, x_value);
    if (!x_value.empty() || output.find('x') == string::npos) {
      output = std::to_string(CalcRPN(rpn_str));
      while (output[output.size() - 1] == '0' ||
             output[output.size() - 1] == '.') {
        if (output[output.size() - 1] == '.') {
          output.resize(output.size() - 1);
          break;
        }
        output.resize(output.size() - 1);
      }
      is_oper = 1;
    } else {
      make_graph = true;
    }
  }
}

void Model::MakeStrClear(const char sym, string& output) {
  if (sym == 'E') {
    output.clear();
    is_oper = false;
    is_exp = false;
  } else if (sym == 'C' && output.size() > 0) {
    if (output.size() >= 2 && output[output.size() - 1] == '(' &&
        output[output.size() - 2] >= 'a' && output[output.size() - 2] <= 'z') {
      do {
        output.resize(output.size() - 1);
      } while (output[output.size() - 1] != ' ' && output.size() != 0 &&
               output[output.size() - 1] != '(');
      --count_left_bracket;
    } else if (output.size() >= 1 && output[output.size() - 1] == ' ') {
      for (int i = 0; i < 3; ++i) {
        if (i == 1 && output[output.size() - 1] == 'd') i -= 2;
        output.resize(output.size() - 1);
      }
      is_oper = true;
    } else if (output.size() >= 1 && (output[output.size() - 1] == 'f' ||
                                      output[output.size() - 1] == 'n')) {
      do {
        output.resize(output.size() - 1);
      } while (output.size() != 0);
      is_oper = false;
    } else if (output.size() >= 1) {
      count_left_bracket -= (output[output.size() - 1] == '(') ? 1 : 0;
      count_right_bracket -= (output[output.size() - 1] == ')') ? 1 : 0;
      output.resize(output.size() - 1);
      if (output.size() > 1 && output[output.size() - 2] == 'e') is_exp = true;
      if (output[output.size() - 1] == '(' || output.size() == 0)
        is_oper = false;
    }
  }
}

void Model::MakeStrE(const char sym, string& output) {
  if (output[output.size() - 1] != 'n' && output[output.size() - 1] != 'f') {
    if (sym == 'e' && output[output.size() - 1] >= '0' &&
        output[output.size() - 1] <= '9') {
      output.push_back('e');
      is_exp = true;
    } else if (sym == '+' || sym == '-') {
      if (output[output.size() - 1] == 'e') output.push_back(sym);
      if (output[output.size() - 1] == '+' || output[output.size() - 1] == '-')
        output[output.size() - 1] = sym;
    } else if (sym >= '0' && sym <= '9' && output[output.size() - 4] != 'e') {
      if (output[output.size() - 1] == '+' ||
          output[output.size() - 1] == '-') {
        output.push_back(sym);
      } else if (output[output.size() - 1] == 'e') {
        output.push_back('+');
        output.push_back(sym);
      }
      is_exp = false;
    }
  }
}

void Model::MakeStrNum(const char sym, string& output) {
  if (!is_exp && output[output.size() - 1] != 'n' &&
      output[output.size() - 1] != 'f') {
    if (sym == 'x' && output[output.size() - 1] != 'x') {
      if (output[output.size() - 1] == ')' ||
          (output[output.size() - 1] >= '0' &&
           output[output.size() - 1] <= '9')) {
        output += " * ";
      }
      is_oper = 1;
      output += "x";
    }
    if ((sym >= '0' && sym <= '9' && output[output.size() - 4] != 'e') ||
        sym == '.') {
      if (output[output.size() - 1] == ')' || output[output.size() - 1] == 'x')
        output += " * ";
      if (sym != '.' || !CheckPoint(output, output.size())) {
        if (sym == '.' && (output.empty() || output[output.size() - 1] == '(' ||
                           output[output.size() - 1] == ' '))
          output.push_back('0');
        if (CheckAccess(output, output.size()) || sym == '.')
          output.push_back(sym);
      }
      is_oper = true;
    }
  }
}

void Model::MakeStrOps(const char sym, string& output) {
  if (!is_exp && output[output.size() - 1] != 'n' &&
      output[output.size() - 1] != 'f') {
    if (is_oper) {
      output.push_back(' ');
      if (sym != 'm') {
        output.push_back(sym);
      } else {
        output += "mod";
      }
      output.push_back(' ');
    } else if (output.size() == 0 || output[output.size() - 1] == '(') {
      if (sym == '-') output.push_back('-');
    } else if (output.size() > 1 && output[output.size() - 2] != '(') {
      if (output.size() > 2 && sym == 'm' && output[output.size() - 2] != 'd') {
        output.resize(output.size() - 2);
        output += "mod ";
      } else if (output.size() > 2 && sym != 'm') {
        if (output[output.size() - 2] == 'd') {
          output.resize(output.size() - 3);
          output.push_back(' ');
        }
        output[output.size() - 2] = sym;
      }
    }
    is_oper = false;
  }
}

void Model::MakeStrFunc(const char sym, string& output, const string& input) {
  if (!is_exp && output[output.size() - 1] != 'n' &&
      output[output.size() - 1] != 'f') {
    if (sym >= 'a' && sym <= 'z' && sym != 'm' && sym != 'x') {
      if (is_oper) {
        output += " * ";
        is_oper = false;
      }
      output += input;
      output.push_back('(');
      ++count_left_bracket;
    }

    if (sym == '(') {
      if (is_oper) {
        output += " * ";
        is_oper = false;
      }
      output.push_back('(');
      ++count_left_bracket;
    }

    if (sym == ')' &&
        (output.size() > 0 && output[output.size() - 1] != '(' && is_oper) &&
        count_right_bracket < count_left_bracket) {
      output.push_back(')');
      ++count_right_bracket;
    }
  }
}

void Model::ReversePolishNotation(const string& str) {
  std::stack<char> st;
  for (int i = 0; str[i] != '\0'; i += (str[i] == ' ') ? 1 : 0) {
    if (str[i] == ')') {
      while (st.top() != '(') {
        rpn_str += st.top();
        st.pop();
        rpn_str.push_back(' ');
      }
      st.pop();
      i += 1;
    }
    if (str[i] == '-' && str[i + 1] != ' ') rpn_str.push_back(str[i++]);
    if ((str[i] >= '0' && str[i] <= '9') || str[i] == 'x') {
      while ((str[i] >= '0' && str[i] <= '9') || str[i] == 'x' ||
             str[i] == '.' || str[i] == '+' || str[i] == '-' || str[i] == 'e')
        rpn_str.push_back(str[i++]);
      rpn_str.push_back(' ');
    }
    if (!strncmp(&str[i], "sin", 3)) {
      st.push('s');
      i += 3;
    }
    if (!strncmp(&str[i], "asin", 4)) {
      st.push('i');
      i += 4;
    }
    if (!strncmp(&str[i], "cos", 3)) {
      st.push('c');
      i += 3;
    }
    if (!strncmp(&str[i], "acos", 4)) {
      st.push('o');
      i += 4;
    }
    if (!strncmp(&str[i], "tg", 2)) {
      st.push('t');
      i += 2;
    }
    if (!strncmp(&str[i], "atg", 3)) {
      st.push('a');
      i += 3;
    }
    if (!strncmp(&str[i], "ln", 2)) {
      st.push('l');
      i += 2;
    }
    if (!strncmp(&str[i], "log", 3)) {
      st.push('g');
      i += 3;
    }
    if (!strncmp(&str[i], "sqrt", 4)) {
      st.push('q');
      i += 4;
    }
    if (str[i] == '(') {
      st.push('(');
      i += 1;
    }
    if ((str[i] == '-' && str[i + 1] == ' ') || str[i] == '+' ||
        str[i] == '^' ||
        (str[i] == 'm' && str[i + 1] == 'o' && str[i + 2] == 'd') ||
        str[i] == '/' || str[i] == '*') {
      if (st.empty()) {
        st.push(str[i]);
      } else {
        while (!st.empty() && ((st.top() >= 'a' && st.top() <= 'z') ||
                               GetPriority(st.top()) >= GetPriority(str[i]))) {
          rpn_str += st.top();
          st.pop();
          rpn_str += ' ';
        }
        st.push(str[i]);
      }
      i += (str[i] == 'm' && str[i + 1] == 'o' && str[i + 2] == 'd') ? 3 : 1;
    }
  }
  while (!st.empty()) {
    rpn_str += st.top();
    st.pop();
    rpn_str += ' ';
  }
}

int Model::GetPriority(const char sym) {
  int priority = 0;
  switch (sym) {
    case 'c':
    case 's':
    case 't':
    case 'o':
    case 'i':
    case 'a':
    case 'q':
    case 'l':
    case 'g':
    case '^':
      priority = 4;
      break;
    case '*':
    case '/':
    case 'm':  // mod
      priority = 3;
      break;
    case '-':
    case '+':
      priority = 2;
      break;
    case '(':
      priority = 1;
      break;
  }
  return priority;
}

double Model::CalcRPN(string& str) {
  std::stack<double> st;
  for (int i = 0; str[i] != '\0'; ++i) {
    if ((str[i] >= '0' && str[i] <= '9') ||
        (str[i] == '-' && str[i + 1] >= '0' && str[i + 1] <= '9')) {
      st.push(std::stod(&str[i]));
      while (str[i] != ' ') {
        ++i;
      }
      continue;
    }
    if (str[i] >= 'a' && str[i] <= 'z' && str[i] != 'm') {
      double arg = st.top();
      st.pop();
      switch (str[i]) {
        case 'c':
          arg = cos(arg);
          break;
        case 's':
          arg = sin(arg);
          break;
        case 't':
          arg = tan(arg);
          break;
        case 'o':
          arg = acos(arg);
          break;
        case 'i':
          arg = asin(arg);
          break;
        case 'a':
          arg = atan(arg);
          break;
        case 'q':
          arg = sqrt(arg);
          break;
        case 'l':
          arg = log(arg);
          break;
        case 'g':
          arg = log10(arg);
          break;
      }
      st.push(arg);
      ++i;
      continue;
    }
    if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' ||
        str[i] == '^' || str[i] == 'm') {
      double arg2 = st.top();
      st.pop();
      double arg1 = st.top();
      st.pop();
      switch (str[i]) {
        case '+':
          arg1 = arg1 + arg2;
          break;
        case '-':
          arg1 = arg1 - arg2;
          break;
        case '*':
          arg1 = arg1 * arg2;
          break;
        case '/':
          arg1 = arg1 / arg2;
          break;
        case '^':
          arg1 = pow(arg1, arg2);
          break;
        case 'm':
          arg1 = fmod(arg1, arg2);
          break;
      }
      st.push(arg1);
      ++i;
      continue;
    }
  }
  return st.top();
}
}  // namespace s21
