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
    // string file_name = get_file_name(argc, argv);
    // float alpha = get_alpha(argc, argv);
    // vector<string> lines = read_file(file_name);
    // ResultadoGreedy resultado = greedy(lines, alpha);

    // cout << get<0>(resultado) << endl; // Valor objetivo
    // cout << get<1>(resultado) << endl; // Tiempo de ejecucion

    int num_alpha_values = 20; // Número de valores de alpha a probar
    int num_repetitions = 50; // Número de veces que se repetirá el proceso
    int n = 100;              // Tamaño de la muestra

    for (int alpha_iteration = 0; alpha_iteration < num_alpha_values; alpha_iteration++) {
        double alpha = 0.05 + alpha_iteration * 0.05;
        vector<double> promedios;
        vector<double> desviaciones;

        for (int repetition = 0; repetition < num_repetitions; repetition++) {
            vector<int> total;

            for (int i = 0; i < n; i++) {
                string file_name = "../Instancias/inst_200_15_4_" + to_string(i) + ".txt";
                vector<string> lines = read_file(file_name);
                ResultadoGreedy resultado = greedy(lines, alpha);
                total.push_back(get<0>(resultado));
            }

            double promedio = 0;
            for (int i = 0; i < n; i++) {
                promedio += total[i];
            }
            promedio /= n;

            double desviacion = 0;
            for (int i = 0; i < n; i++) {
                desviacion += (total[i] - promedio) * (total[i] - promedio);
            }
            desviacion /= (n - 1);
            desviacion = sqrt(desviacion);

            promedios.push_back(promedio);
            desviaciones.push_back(desviacion);
        }

        double promedio_total_promedios = 0;
        double promedio_total_desviaciones = 0;

        for (int i = 0; i < num_repetitions; i++) {
            promedio_total_promedios += promedios[i];
            promedio_total_desviaciones += desviaciones[i];
        }

        promedio_total_promedios /= num_repetitions;
        promedio_total_desviaciones /= num_repetitions;

        cout << "Alpha: " << alpha << endl;
        cout << "Promedio Total de Promedios: " << promedio_total_promedios << endl;
        cout << "Promedio Total de Desviaciones Estandar: " << promedio_total_desviaciones << endl;
    }

    return 0;
}