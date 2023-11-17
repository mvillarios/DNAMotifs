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
    int tam_poblacion = get_tam_poblacion(argc, argv);
    bool tunning = get_tunning(argc, argv);

    int m = get_m(argc, argv);
    int l = get_l(argc, argv);
    int algoritmo = get_algoritmo(argc, argv);

    cout << "Inicio" << endl;
    allInst (t_limite, alpha, tam_poblacion, tunning, m, l, algoritmo);
    cout << "Fin" << endl;

    return 0;
}

// -p 102 -a 0.895