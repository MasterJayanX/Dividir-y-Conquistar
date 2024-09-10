#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

void crearArchivo(vector<int>& arr, string archivo) {
    /*
    void crearArchivo
    Descripción: Función que crea un archivo con los elementos de un vector.
    Complejidad: O(n)
    */
    ofstream sorted(archivo);
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        sorted << arr[i] << endl;
    }
    sorted.close();
}

void start(string archivo, string tam) {
    /*
    void start
    Descripción: Función que lee un archivo con números enteros, los ordena con sort de la STL y crea un archivo con los números ordenados.
    Complejidad: O(nlogn)
    */
    vector<int> arr;
    ifstream in(archivo);
    string line;
    while (getline(in, line)) {
        arr.push_back(stoi(line));
    }
    auto inicio = high_resolution_clock::now();
    sort(arr.begin(), arr.end());
    crearArchivo(arr, "sortestandar" + tam + ".txt");
    in.close();
    auto fin = high_resolution_clock::now();
    auto tiempo = duration_cast<duration<double>>(fin - inicio);
    cout << "Tiempo de ejecución: " << tiempo.count() << " milisegundos" << endl;
}

int main() {
    /*
    int main
    Descripción: Función principal inicializa el sort estándar para arreglos de diferentes tamaños.
    */
    start("data10e3.txt", "10e3");
    start("data10e4.txt", "10e4");
    start("data10e5.txt", "10e5");
    start("data10e6.txt", "10e6");
    return 0;
}