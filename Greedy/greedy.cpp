#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int menorValorDna(const std::vector<int>& count){//modificar en caso de igualdades
    if(count.empty()) return -1;// si esta vacio
    int minIndex = 0; 
    for (int i = 1; i < count.size(); ++i) {
        if (count[i] < count[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex;//retorna el index del menor valor
}


int greedy(vector<string> s){
    vector<string> dna = {"A", "C", "G", "T"};
    vector<int> count = {0, 0, 0, 0};
    vector<int> costo_s_i;
    int x = 14;
    int tam_s = s.size();

    costo_s_i.resize(tam_s);
    
    

    for (int i = 0; i < x; i++){ // recorre cada columna
        for (int j = 0; j < tam_s; j++){ //recorre cada fila
            if(i==0){//if para testear
                if (s[j][i] != 'A'){
                    count[0] += 1;
                }
                if (s[j][i] != 'C'){
                    count[1] += 1;
                }
                if (s[j][i] != 'G'){
                    count[2] += 1;
                }
                if (s[j][i] != 'T'){
                    count[3] += 1;
                }
            }
        }        
    }
    cout<<"siguiente letra: "<<menorValorDna(count)<<endl;
    cout<<"Columna: 1"<<"  A: "<<count[0]<<", C: "<<count[1]<<",G: "<<count[2]<<" ,T: "<<count[3]<<endl;    

    return 0;
};