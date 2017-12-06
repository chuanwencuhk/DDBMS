#pragma once
#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;

static string file = "/home/lh2debug/useful/test_log/mylog";

template <typename T>
void Println(T message){
	ofstream of(file, std::ios::app);
	of << message << endl;
	of.close();
}

template <typename T>
void Println2(string message, T value){
	ofstream of(file, std::ios::app);
	of << message << value << endl;
	of.close();
}
