#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

void generar(string archivo, int num) {
    /*
    void generar
    Descripción: Función que genera un archivo con números enteros aleatorios.
    Complejidad: O(n)
    */
    ofstream file(archivo);
    auto inicio = high_resolution_clock::now();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 1000000);

    for (int i = 0; i < num; i++) {
        file << dist(gen) << endl;
    }

    file.close();
    auto fin = high_resolution_clock::now();
    auto tiempo = duration_cast<duration<double>>(fin - inicio);
    cout << "Tiempo de ejecución: " << tiempo.count() << " segundos" << endl;
}

int main(){
    /*
    int main
    Descripción: Función principal que genera archivos con números enteros aleatorios.
    */
    generar("data10e3.txt", 1000);
    generar("data10e4.txt", 10000);
    generar("data10e5.txt", 100000);
    generar("data10e6.txt", 1000000);
    return 0;
}