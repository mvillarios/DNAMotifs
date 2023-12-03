#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <string>
#include <unordered_map>

std::tuple<int, std::vector<char>> greedy(std::vector<std::string> s, float alpha, int tam_string);
std::tuple<int, long long> grasp(std::vector<std::string> s, int tam_string, long long t_limite, int tunning);
std::tuple<int, long long> genetico(std::vector<std::string> s, int tam_string, int tam_poblacion, float alpha, long long t_limite, bool tunning);
std::tuple<int, long long> mh_hibrida(std::vector<std::string> s, int tam_string, long long t_limite, int tunning, int tam_pobl_inicial, float porcentaje_seleccionados, float prob_mutacion, float prob_cruce, float prob_local_search);

int menorValorDna(const std::vector<int>& count, float alpha);
int calcularDistancia(const std::string& str, const std::vector<std::string>& dataset);

std::vector<std::string> read_file(const std::string& file_name);
std::string get_file_name(int argc, char* argv[]);
int get_tam_string(int argc, char* argv[]);
float get_alpha(int argc, char* argv[]);
long long get_t_limite(int argc, char* argv[]);
bool get_tunning(int argc, char* argv[]);
int get_m (int argc, char* argv[]);
int get_l (int argc, char* argv[]);
int get_algoritmo (int argc, char* argv[]);

int get_tam_poblacion(int argc, char* argv[]);
float get_porcentaje_seleccionados(int argc, char* argv[]);
float get_prob_mutacion(int argc, char* argv[]);
float get_prob_cruce(int argc, char* argv[]);
float get_prob_local_search(int argc, char* argv[]);

bool extractValues(std::string filePath, int& inst, int& m, int& l);
void close_data(std::ofstream &file);
void save_data(std::ofstream &file, int inst, int m, int l, int res1, long long res2);
void clear_data(std::string file_name);

void allInst (long long t_limite, float alpha, int tam_poblacion, bool tunning, int m, int l, int algoritmo);

std::string localSearch(const std::string& sol_inicial, const std::vector<std::string>& s);

#endif  // FUNCIONES_H
