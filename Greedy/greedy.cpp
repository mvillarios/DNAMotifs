#include <iostream>
#include <fstream>
#include "funciones.h"

using namespace std;

//para compilar:g++ main.cpp greedy.cpp -o main.exe

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
    std::vector<char> dna = {'A', 'C', 'G', 'T'};
    std::vector<int> count = {0, 0, 0, 0};
    int x = 15;
    int tam_s = s.size();

    //almacena el la distancia de cada S_i hasta el momento
    std::vector<int> distancia_s_i(tam_s, 0);
    
    //es un una matriz de tamaño: tam_s x 4, almacena la distancia para cada letra, se calcula cada vez que se
    //pasa a la siguiente columna.
    std::vector<std::vector<int>> matriz(tam_s, std::vector<int>(4,0)); 
    //sumatoria de las distancias para cada letra, en cada iteracion se escoge la que tenga menor distancia
    std::vector<int> count = {0, 0, 0, 0};
    
    std::vector<char> respuesta;

    for (int i = 0; i < x; i++){ // recorre cada columna
        for (int j = 0; j < tam_s; j++){ //recorre cada fila
        
            for(int k=0;k<4;k++){// se prueba con todas las letras A-C-G-T
                if(s[j][i]!=dna[k]){//si es diferente
                    matriz[j][k]++;//se le suma 1 a la matriz y columna que corresponde
                    count[k]+=1;//distancia acumulada de cada letra

                }
            }
            
            
        }
        cout<<"-----------Columna "<<i<<" ------------"<<endl;
        for (int j = 0; j < 4; j++) cout<<count[j]<<" ";//distancia acumulada de cada letra
        cout<<""<<endl;
        cout<<"A C G T"<<endl;    

        for(int s = 0; s < tam_s; s++){//distancia de cada letra en su respectivo S_i
            for (int t = 0; t < 4; t++){
                cout<< matriz[s][t]<<" "; 
            }
            cout<<endl;
        }    
        int next = menorValorDna(count);//Se calcula la letra que añadira menos distancia
        cout<<"mejor: "<<dna[next]<<endl;
        respuesta.push_back(dna[next]);// y se añade a la respuesta
        for(int s=0;s<tam_s;s++){
            distancia_s_i[s] += matriz[s][next];//a distancia_i se le suma la fila de la matriz correspondiente a la nueva letra
            cout<<distancia_s_i[s]<<endl;
        }
        for(int s=0;s<tam_s;s++){
            for (int t = 0; t < 4; t++) matriz[s][t]=0;//se reinicia la matriz para la siguiente iteracion
        }
        for (int t = 0; t < 4; t++) count[t]=0;//se reinicia count para la siguiente iteracion
    }
    cout<<"respuesta: ";
    for(int i=0;i<respuesta.size();i++) cout<<respuesta[i];

    return 0;
}