#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <string>

typedef std::tuple<int, long long> ResultadoGreedy;

int menorValorDna(const std::vector<int>& count, float alpha);
std::string greedy(std::vector<std::string> s, float alpha);
std::vector<std::string> read_file(const std::string& file_name);
std::string get_file_name(int argc, char* argv[]);
float get_alpha(int argc, char* argv[]);
void metaheuristica(std::vector<std::string> s);
bool extractValues(string filePath, int& inst, int& m, int& l);

#endif  // FUNCIONES_H
