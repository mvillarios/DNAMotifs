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

    long long t_limite = get_t_limite(argc, argv);
    bool tunning = get_tunning(argc, argv);

    float tam_poblacion = get_tam_poblacion(argc, argv);
    float porcentaje_seleccionados = get_porcentaje_seleccionados(argc, argv);
    float prob_mutacion = get_prob_mutacion(argc, argv);
    float prob_cruce = get_prob_cruce(argc, argv);
    float prob_local_search = get_prob_local_search(argc, argv);


    int inst, m, l;

    extractValues(file_name, inst, m, l);

    std::tuple<int, long long> res = mh_hibrida(lines, l, t_limite, tunning, tam_poblacion, porcentaje_seleccionados, prob_mutacion, prob_cruce, prob_local_search);

    // Imprimo el resultado
    if(tunning == false){
        cout << "Costo Final: " << std::get<0>(res) << endl;
        cout << "Tiempo Final: " << std::get<1>(res) / 1e9<< endl;
    }else{
        cout << std::get<0>(res) << endl;
    }

    return 0;
}