all:
	g++ -std=c++11 -shared -fPIC test_plugin.cpp -o testplugin.o
	g++ -std=c++11 test_main.cpp -ldl -o test_main
