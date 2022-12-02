build:
	rm -f tests.exe
	g++ -g -Wall tests.cpp -o tests.exe -lgtest -lgtest_main -lpthread
	
build1:
	rm -f tests.exe
	g++ -g -Wall tests2.cpp -o tests.exe -lgtest -lgtest_main -lpthread	
	
run:
	./tests.exe

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./tests.exe