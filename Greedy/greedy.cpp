#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int greedy(vector<string> s){
    vector<string> dna = {"A", "C", "G", "T"};
    vector<int> count = {0, 0, 0, 0};
    vector<int> costo_s_i;
    int x = 14;
    int tam_s = s.size();

    costo_s_i.resize(tam_s);

    for (int i = 0; i < x; i++){ // recorre cada columna
        for (int j = 0; j < tam_s; j++){ //recorre cada fila
            if (s[j][i] != 'A'){
                count[0] += 1;
            }
            else if (s[j][i] != 'C'){
                count[1] += 1;
            }
            else if (s[j][i] != 'G'){
                count[2] += 1;
            }
            else if (s[j][i] != 'T'){
                count[3] += 1;
            }
        }

    }

    return 0;
};