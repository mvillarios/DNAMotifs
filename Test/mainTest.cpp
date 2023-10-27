#include <iostream>
#include <fstream>
#include "../Funciones/funciones.h"
#include <ctime>
#include <tuple>
#include <cmath>
#include <chrono>

using namespace std;

int main(int argc, char* argv[]) {

    std::srand(std::time(NULL));

    int t_limite = get_t_limite(argc, argv);
    float alpha = get_alpha(argc, argv);

    cout << "Inicio" << endl;
    allInst (t_limite, alpha);
    cout << "Fin" << endl;
    return 0;
}