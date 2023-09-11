#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <string>

int menorValorDna(const std::vector<int>& count, float alpha);
int greedy(std::vector<std::string> s, float alpha);
std::vector<std::string> read_file(const std::string& file_name);
std::string get_file_name(int argc, char* argv[]);
float get_alpha(int argc, char* argv[]);

#endif  // FUNCIONES_H
