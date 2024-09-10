#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

void selectionSort(vector<int>& v, int n){
    /*
    void selectionSort
    Descripción: Función que ordena un arreglo usando el algoritmo de selection sort.
    Complejidad: O(n^2)
    */
    for (int i = 0; i < n - 1; i++){
        int min_idx = i;
        for (int j = i + 1; j < n; j++){
            if (v[j] < v[min_idx]){
                min_idx = j;
            }
        }
        if (min_idx != i){ 
            int temp = v[min_idx];
            v[min_idx] = v[i];
            v[i] = temp;
        }
    }
}

void crearArchivo(vector<int> v, int n, string archivo){
    /*
    void crearArchivo
    Descripción: Función que crea un archivo con los elementos de un vector.
    Complejidad: O(n)
    */
    ofstream sorted(archivo);
    for (int i = 0; i < n; i++){
        sorted << v[i] << endl;
    }
    sorted.close();
}

void sort(string archivo, string tam){
    /*
    void sort
    Descripción: Función que lee un archivo con números enteros, los ordena con selection sort y crea un archivo con los números ordenados.
    Complejidad: O(n^2)
    */
    ifstream in(archivo);
    vector<int> v;
    int len = 0;
    string line;
    while (getline(in, line)){
        v.push_back(stoi(line));
        len++;
    }
    auto inicio = high_resolution_clock::now();
    selectionSort(v, len);
    crearArchivo(v, len, "selsort" + tam + ".txt");
    auto fin = high_resolution_clock::now();
    auto tiempo = duration_cast<duration<double>>(fin - inicio);
    cout << "Tiempo de ejecución: " << tiempo.count() << " segundos" << endl;
}

int main(){
    /*
    int main
    Descripción: Función principal inicializa el selection sort para arreglos de diferentes tamaños.
    */
    sort("data10e3.txt", "10e3");
    sort("data10e4.txt", "10e4");
    sort("data10e5.txt", "10e5");
    sort("data10e6.txt", "10e6");
    return 0;
}