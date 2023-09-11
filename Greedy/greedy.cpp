#include <iostream>
#include <fstream>
#include "funciones.h"
#include <ctime>

using namespace std;

int main(int argc, char* argv[]) {
    
    std::srand(std::time(NULL));
    string file_name = get_file_name(argc, argv);
    vector<string> lines = read_file(file_name);
    greedy(lines, 0);
    return 0;
}