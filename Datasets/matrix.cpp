#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

void generar(string archivo, int lado, char tipo) {
    /*
    void generar
    Descripción: Función que genera un archivo con una matriz de lado x lado con números aleatorios o una matriz identidad.
    Complejidad: O(n^2)
    */
    ofstream file(archivo);
    auto inicio = high_resolution_clock::now();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 1000);
    for(int i = 0; i < lado; i++){
        for(int j = 0; j < lado; j++){
            if(tipo == 't'){
                file << dist(gen) << " ";
            }else if(tipo == 'i'){
                if(i == j){
                    file << 1 << " ";
                }else{
                    file << 0 << " ";
                }
            }
        }
        file << endl;
    }
    file.close();
    auto fin = high_resolution_clock::now();
    auto tiempo = duration_cast<duration<double>>(fin - inicio);
    cout << "Tiempo de ejecución: " << tiempo.count() << " segundos" << endl;
}

int main(){
    /*
    int main
    Descripción: Función principal que genera archivos con matrices de diferentes tamaños y tipos.
    */
    generar("matrix10e4_1.txt", 100, 't');
    generar("matrix10e6_1.txt", 1000, 't');
    generar("matrix500_1.txt", 500, 't');
    generar("matrixid10e4.txt", 100, 'i');
    generar("matrixid10e6.txt", 1000, 'i');
    generar("matrixid500.txt", 500, 'i');
    generar("matrix10e4_2.txt", 100, 't');
    generar("matrix10e6_2.txt", 1000, 't');
    generar("matrix500_2.txt", 500, 't');
    return 0;
}