#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <string>

int menorValorDna(const std::vector<int>& count, float alpha);
int calcularDistancia(const std::string& str, const std::vector<std::string>& dataset);
std::tuple<int, std::vector<char>> greedy(std::vector<std::string> s, float alpha, int tam_string);
std::tuple<int, long long> grasp(std::vector<std::string> s, int tam_string, int t_limite);

std::vector<std::string> read_file(const std::string& file_name);
std::string get_file_name(int argc, char* argv[]);
int get_tam_string(int argc, char* argv[]);
float get_alpha(int argc, char* argv[]);
int get_t_limite(int argc, char* argv[]);
bool extractValues(std::string filePath, int& inst, int& m, int& l);
void close_data(std::ofstream &file);
void save_data(std::ofstream &file, int inst, int m, int l, int res1, long long res2);
void clear_data(std::string file_name);
#endif  // FUNCIONES_H
