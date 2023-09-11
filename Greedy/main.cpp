#include <iostream>
#include <fstream>
#include "funciones.h"
#include <ctime>

using namespace std;

// Leer archivo de entrada
vector<string> read_file(const string& file_name) {
    vector<string> lines;
    ifstream file(file_name);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }
    return lines;
}

// Obtener el nombre del archivo de entrada
string get_file_name(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Error: Debe ingresar el nombre del archivo de entrada" << endl;
        exit(1);
    }
    return argv[1];
}

int main(int argc, char* argv[]) {
    std::srand(std::time(NULL));
    string file_name = get_file_name(argc, argv);
    vector<string> lines = read_file(file_name);
    greedy(lines);
    return 0;
}
