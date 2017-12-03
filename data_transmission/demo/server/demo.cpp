#include <iostream>
#include <string>
#include <fstream>

using std::string;
using std::ifstream;
using std::cout;
using std::endl;


string getFileData(string name){
    ifstream ifile(name, std::ios::in);
    char tmp[100];
    string ret;
    while (ifile.getline(tmp, 100)){
        ret.append(tmp);
        ret.append("\n");
    }
    return ret;
}

int main(){
	string ret = getFileData("greet.txt");
	cout << ret << endl;
	return 0;
}