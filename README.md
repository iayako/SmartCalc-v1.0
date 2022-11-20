# SmartCalc v1.0
## In this project we will implement an extended version of the usual calculator, which can be found in the standard applications of each operating system. In addition to basic arithmetic operations such as add/subtract and multiply/divide, we need to supplement the calculator with the ability to calculate arithmetic expressions by following the order, as well as some mathematical functions (sin, cos, sqrt, etc.).

![Image alt](https://github.com/iayako/fuzzy-quasar/blob/main/images/smartcalc1.png)

## Bracketed arithmetic expressions in infix notation must support the following arithmetic operations and mathematical functions:

	Brackets: (a + b);
	Addition: a + b;
	Subtraction: a - b;
	Multiplication: a * b;
	Division: a / b;
	Power: a ^ b;
	Modulus: a mod b;
	Unary minus: -a;
	cos(x);
	sin(x);
	tan(x);
	acos(x);
	asin(x);
	atan(x);
	sqrt(x);
	ln(x);
	log(x).

## It is possible to graph the function

![Image alt](https://github.com/iayako/fuzzy-quasar/blob/main/images/smartcalc2.png)

## There is a special mode "Credit calculator":

![Image alt](https://github.com/iayako/fuzzy-quasar/blob/main/images/smartcalc3.png)

	Input: total loan amount, term, interest rate, type (annuity, differentiated)
	Output: monthly payment, loan overpayment, total payment

## There is a special mode "Deposit calculator":

![Image alt](https://github.com/iayako/fuzzy-quasar/blob/main/images/smartcalc4.png)

	Input: deposit amount, deposit term, interest rate, tax rate, periodicity of payments, capitalization of interest, replenishments list, partial withdrawals list
	Output: accrued interest, tax amount, deposit amount by the end of the term
