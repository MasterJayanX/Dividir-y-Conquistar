#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

int partition(vector<int> &vec, int low, int high) {
    /*
    int partition
    Descripción: Función que selecciona un pivote y acomoda los elementos menores a la izquierda y los mayores a la derecha.
    Complejidad: O(n)
    */
    int pivote = vec[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (vec[j] <= pivote) {
            i++;
            swap(vec[i], vec[j]);
        }
    }
    swap(vec[i + 1], vec[high]);
    return (i + 1);
}

void quickSort(vector<int> &vec, int low, int high) {
    /*
    void quickSort
    Descripción: Función que ordena un arreglo usando el algoritmo de quick sort.
    Complejidad: O(nlogn)
    */
    if (low < high) {
        int p = partition(vec, low, high);
        quickSort(vec, low, p - 1);
        quickSort(vec, p + 1, high);
    }
}

void crearArchivo(vector<int> &vec, string archivo) {
    /*
    void crearArchivo
    Descripción: Función que crea un archivo con los elementos de un vector.
    Complejidad: O(n)
    */
    ofstream sorted(archivo);
    int n = vec.size();
    for (int i = 0; i < n; i++) {
        sorted << vec[i] << endl;
    }
    sorted.close();
}

void start(string archivo, string tam) {
    /*
    void start
    Descripción: Función que lee un archivo con números enteros, los ordena con quick sort y crea un archivo con los números ordenados.
    Complejidad: O(nlogn)
    */
    vector<int> vec;
    ifstream in(archivo);
    string line;
    while (getline(in, line)) {
        vec.push_back(stoi(line));
    }
    int N = vec.size();
    auto inicio = high_resolution_clock::now();
    quickSort(vec, 0, N - 1);
    crearArchivo(vec, "quicksort" + tam + ".txt");
    in.close();
    auto fin = high_resolution_clock::now();
    auto tiempo = duration_cast<duration<double>>(fin - inicio);
    cout << "Tiempo de ejecución: " << tiempo.count() << " segundos" << endl;
}

int main() {
    /*
    int main
    Descripción: Función principal que prueba el algoritmo de quick sort con diferentes tamaños de arreglos.
    */
    start("data10e3.txt", "10e3");
    start("data10e4.txt", "10e4");
    start("data10e5.txt", "10e5");
    start("data10e6.txt", "10e6");
    return 0;
}