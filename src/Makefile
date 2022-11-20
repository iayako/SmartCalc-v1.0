GCC = g++ -std=c++17 -Wall -Werror -Wextra
OS := $(shell uname -s)
ifeq ($(OS), Darwin)
  FLAGS = -lgtest
  GCOV = --coverage
else
  FLAGS = -lgtest -lpthread -lrt -lm
  GCOV = -fprofile-arcs -ftest-coverage
endif

SOURCES = SmartCalc/main.cpp \
			SmartCalc/View.cpp \
			SmartCalc/GraphView.cpp \
			SmartCalc/Controller.cpp \
			SmartCalc/CalcModel.cpp \
			SmartCalc/CreditDepositModel.cpp \
			SmartCalc/GraphModel.cpp

HEADERS = SmartCalc/View.h \
			SmartCalc/GraphView.h \
			SmartCalc/Controller.h \
			SmartCalc/Model.h

all: install tests

install:
	cd ./SmartCalc; qmake
	cd ./SmartCalc; make
	@mkdir $(HOME)/Desktop/SmartCalc/
	@cp -rf SmartCalc/CalcS21.app $(HOME)/Desktop/SmartCalc/
	@open $(HOME)/Desktop/SmartCalc/CalcS21.app
	make clean

run:
	@open $(HOME)/Desktop/SmartCalc/CalcS21.app

clean:
	rm -rf SmartCalc/CalcS21.app SmartCalc/CalcS21.pro.user report SmartCalc/ui_* SmartCalc/Makefile
	rm -rf SmartCalc.tgz SmartCalc/.qmake.stash tests SmartCalc/*.o SmartCalc/moc_* gcov_rep

uninstall:
	rm -rf $(HOME)/Desktop/SmartCalc/

tests: clean
	$(GCC) test.cpp SmartCalc/CalcModel.cpp $(FLAGS) -o tests
	./tests

dist:
	open SmartCalc.html

dvi:
	tar -czvf SmartCalc.tgz SmartCalc images test.cpp Makefile SmartCalc.html

gcov_report: clean
	$(GCC) $(GCOV) test.cpp  SmartCalc/CalcModel.cpp $(FLAGS) -o gcov_rep
	./gcov_rep
	lcov -t "gcov_rep" --no-external --output-file=coverag.info --capture --directory .
	genhtml -o ./report coverag.info
	rm -rf *.gcda *.gcno *.info
	open report/index.html

code_style:
	clang-format -n $(SOURCES) $(HEADERS)

cppcheck:
	cppcheck --suppress=missingIncludeSystem --suppress=unknownMacro --std=c++17 --language=c++ $(SOURCES) $(HEADERS)

leaks: tests
	leaks -atExit -- ./tests
