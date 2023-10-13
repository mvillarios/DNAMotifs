#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <string>

int menorValorDna(const std::vector<int>& count, float alpha);
int calcularDistancia(const std::string& str, const std::vector<std::string>& dataset);
std::tuple<int, std::vector<char>> greedy(std::vector<std::string> s, float alpha);
std::tuple<int, long long> grasp(std::vector<std::string> s, int tam_string, int n_sol_ini, int t_limite);

std::vector<std::string> read_file(const std::string& file_name);
std::string get_file_name(int argc, char* argv[]);
float get_alpha(int argc, char* argv[]);
bool extractValues(string filePath, int& inst, int& m, int& l);
void close_data(ofstream &file);
void clear_data(string file_name);
#endif  // FUNCIONES_H
