#include <iostream>
#include <fstream>
#include "funciones.h"
#include <ctime>
#include <tuple>
#include <cmath>

using namespace std;

typedef std::tuple<int, long long> ResultadoGreedy;

int main(int argc, char* argv[]) {
    
    std::srand(std::time(NULL));

    // Obtener el valor objetivo y el tiempo de ejecucion de una instancia
    string file_name = get_file_name(argc, argv);
    vector<string> lines = read_file(file_name);
    ResultadoGreedy resultado = greedy(lines, 0);

    cout << "Valor objetivo: " << get<0>(resultado) << endl; // Valor objetivo
    cout << "Tiempo de ejecucion: " << get<1>(resultado) << " us" << endl; // Tiempo de ejecucion


    // // Obtener el promedio y la desviación estándar de todas las instancias
    // double promedio = 0;
    // double desviacion = 0;
    // int n = 100;

    // vector<int> total;

    // for (int i = 0; i < n; i++) {
    //     string file_name = "../Instancias/inst_200_15_4_" + to_string(i) + ".txt";
    //     vector<string> lines = read_file(file_name);
    //     ResultadoGreedy resultado = greedy(lines, 0);
    //     cout << get<0>(resultado) << endl;
    //     total.push_back(get<0>(resultado));
    //     promedio += get<0>(resultado);
    // }

    // promedio /= n;

    // for (int i = 0; i < n; i++) {
    //     desviacion += (total[i] - promedio) * (total[i] - promedio);
    // }

    // desviacion /= (n - 1);
    // desviacion = sqrt(desviacion);

    // cout << "Promedio: " << promedio << endl;
    // cout << "Desviacion estandar: " << desviacion << endl;

    return 0;
}