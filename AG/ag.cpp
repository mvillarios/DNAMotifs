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

    string file_name = get_file_name(argc, argv);

    vector<string> lines = read_file(file_name);

    int pobl_inicial = get_tam_poblacion(argc, argv);

    float alpha = get_alpha(argc, argv);

    int t_limite = get_t_limite(argc, argv);

    bool tunning = get_tunning(argc, argv);

    int inst, m, l;

    extractValues(file_name, inst, m, l);

    std::tuple<int, long long> res = genetico(lines, l, pobl_inicial, alpha, t_limite, tunning);

    // Imprimo el resultado
    if(tunning == false){
        cout << "Resultado Final: " << std::get<0>(res) << endl;
        cout << "Tiempo Final: " << std::get<1>(res) << endl;
    }else{
        cout << std::get<0>(res) << endl;
    }

    return 0;
}