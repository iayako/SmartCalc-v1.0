#include <gtest/gtest.h>

#include "SmartCalc/model.h"

TEST(Calculator, case_1) {
  s21::Model test;
  string output;
  test.MakeStr("1", output, "");
  test.MakeStr("+", output, "");
  test.MakeStr("2", output, "");
  test.MakeStr("=", output, "");
  EXPECT_EQ(output, "3");
}

TEST(Calculator, case_2) {
  s21::Model test;
  string output;
  test.MakeStr("1", output, "");
  test.MakeStr("2", output, "");
  test.MakeStr("*", output, "");
  test.MakeStr("2", output, "");
  test.MakeStr("=", output, "");
  EXPECT_EQ(output, "24");
}

TEST(Calculator, case_3) {
  s21::Model test;
  string output;
  test.MakeStr("1", output, "");
  test.MakeStr("2", output, "");
  test.MakeStr("/", output, "");
  test.MakeStr("3", output, "");
  test.MakeStr("=", output, "");
  EXPECT_EQ(output, "4");
}

TEST(Calculator, case_4) {
  s21::Model test;
  string output;
  test.MakeStr("1", output, "");
  test.MakeStr("2", output, "");
  test.MakeStr("-", output, "");
  test.MakeStr("9", output, "");
  test.MakeStr("=", output, "");
  EXPECT_EQ(output, "3");
}

TEST(Calculator, case_5) {
  s21::Model test;
  string output;
  test.MakeStr("sqrt", output, "");
  test.MakeStr("6", output, "");
  test.MakeStr("4", output, "");
  test.MakeStr("=", output, "");
  EXPECT_EQ(output, "8");
}

TEST(Calculator, case_6) {
  s21::Model test;
  string output;
  test.MakeStr("1", output, "");
  test.MakeStr("2", output, "");
  test.MakeStr("^", output, "");
  test.MakeStr("2", output, "");
  test.MakeStr("=", output, "");
  EXPECT_EQ(output, "144");
}

TEST(Calculator, case_7) {
  s21::Model test;
  string output("5 + 5 + 5 + 5");
  test.MakeStr("E", output, "");
  EXPECT_EQ(output, "");
}

TEST(Calculator, case_8) {
  s21::Model test;
  string output("5 + 5 + 5 + 5");
  test.MakeStr("C", output, "");
  EXPECT_EQ(output, "5 + 5 + 5 + ");
}

TEST(Calculator, case_9) {
  s21::Model test;
  string output;
  test.MakeStr("1", output, "");
  test.MakeStr("8", output, "");
  test.MakeStr(".", output, "");
  test.MakeStr("8", output, "");
  test.MakeStr("-", output, "");
  test.MakeStr("5", output, "");
  test.MakeStr(".", output, "");
  test.MakeStr("4", output, "");
  test.MakeStr("C", output, "");
  test.MakeStr("C", output, "");
  test.MakeStr("=", output, "");
  EXPECT_EQ(output, "13.8");
}

TEST(Calculator, case_10) {
  s21::Model test;
  string output;
  test.MakeStr("5", output, "");
  test.MakeStr("e", output, "");
  test.MakeStr("-", output, "");
  test.MakeStr("+", output, "");
  test.MakeStr("C", output, "");
  test.MakeStr("2", output, "");
  test.MakeStr("=", output, "");
  EXPECT_EQ(output, "500");
}

TEST(Calculator, case_11) {
  s21::Model test;
  string output;
  test.MakeStr("cos", output, "");
  test.MakeStr("C", output, "");
  test.MakeStr("acos", output, "");
  test.MakeStr("C", output, "");
  test.MakeStr("asin", output, "");
  test.MakeStr("C", output, "");
  test.MakeStr("atg", output, "");
  test.MakeStr("C", output, "");
  test.MakeStr("tg", output, "");
  test.MakeStr("C", output, "");
  test.MakeStr("ctg", output, "");
  test.MakeStr("C", output, "");
  test.MakeStr("sin", output, "");
  test.MakeStr("0", output, "");
  test.MakeStr("=", output, "");
  EXPECT_EQ(output, "0");
}

TEST(Calculator, case_12) {
  s21::Model test;
  string output("nan");
  test.MakeStr("C", output, "");
  test.MakeStr("(", output, "");
  test.MakeStr("5", output, "");
  test.MakeStr("mod", output, "");
  test.MakeStr("C", output, "");
  test.MakeStr("+", output, "");
  test.MakeStr("5", output, "");
  test.MakeStr(")", output, "");
  test.MakeStr("4", output, "");
  test.MakeStr("=", output, "");
  EXPECT_EQ(output, "40");
}

TEST(Calculator, case_14) {
  s21::Model test;
  string output("");
  test.MakeStr("-", output, "");
  test.MakeStr("4", output, "");
  test.MakeStr("+", output, "");
  test.MakeStr("(", output, "");
  test.MakeStr("5", output, "");
  test.MakeStr("+", output, "");
  test.MakeStr("mod", output, "");
  test.MakeStr("-", output, "");
  test.MakeStr("4", output, "");
  test.MakeStr("=", output, "");
  EXPECT_EQ(output, "-3");
}

TEST(Calculator, case_15) {
  s21::Model test;
  string output("");
  test.MakeStr("1", output, "");
  test.MakeStr("*", output, "");
  test.MakeStr("4", output, "");
  test.MakeStr("asin", output, "");
  test.MakeStr("0", output, "");
  test.MakeStr("-", output, "");
  test.MakeStr("cos", output, "");
  test.MakeStr("0", output, "");
  test.MakeStr("ln", output, "");
  test.MakeStr("2", output, "");
  test.MakeStr("=", output, "");
  EXPECT_EQ(output, "-6.283185");
}

TEST(Calculator, case_16) {
  s21::Model test;
  string output("");
  test.MakeStr("(", output, "");
  test.MakeStr("8", output, "");
  test.MakeStr("-", output, "");
  test.MakeStr("4", output, "");
  test.MakeStr(")", output, "");
  test.MakeStr("5", output, "");
  test.MakeStr("0", output, "");
  test.MakeStr("+", output, "");
  test.MakeStr("x", output, "");
  test.MakeStr("=", output, "13");
  EXPECT_EQ(output, "213");
}

TEST(Calculator, case_17) {
  s21::Model test;
  string output("");
  test.MakeStr("x", output, "");
  bool ans = test.MakeStr("=", output, "");
  EXPECT_EQ(ans, true);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}