#include <iostream>
#include <fstream>
#include "funciones.h"
#include <ctime>
#include <tuple>
#include <cmath>
#include <chrono>

using namespace std;

typedef std::tuple<int, long long> ResultadoGreedy;

int main(int argc, char* argv[]) {

    std::srand(std::time(NULL));

    // Obtener el valor objetivo y el tiempo de ejecucion de una instancia
    string file_name = get_file_name(argc, argv);
    float alpha = get_alpha(argc, argv);
    vector<string> lines = read_file(file_name);
    
    int menor = 0;
    cout << "Valor objetivo" << endl;

    // while que dura 60 seg
    auto start_time = std::chrono::high_resolution_clock::now(); // Marcar el tiempo de inicio
    while (//std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start_time).count() < 60
    1
    ) {

        ResultadoGreedy resultado = greedy(lines, alpha);
        int valor = std::get<0>(resultado);
        // Calcular tiempo que lleva el while corriendo
        auto end_time = std::chrono::high_resolution_clock::now(); // Marcar el tiempo de finalización
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
        long long tiempo = duration.count();

        if (menor == 0 || valor < menor){
            menor = valor;
            cout << "Valor: "<<menor << " Tiempo: "<<tiempo<<endl;
        } 
    }

    cout << "Valor final: " << menor <<endl;
    cout << "Valor real: " << 23673 << endl;

    return 0;
}