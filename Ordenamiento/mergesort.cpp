#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

void merge(vector<int>& arr, int left, int mid, int right)
{
    /*
    void merge
    Descripción: Función que realiza el merge de dos subarreglos ordenados.
    Complejidad: O(n)
    */
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right)
{
    /*
    void mergeSort
    Descripción: Función que ordena un arreglo usando el algoritmo de merge sort.
    Complejidad: O(nlogn)
    */
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void crearArchivo(vector<int>& arr, string archivo){
    /*
    void crearArchivo
    Descripción: Función que crea un archivo con los elementos de un vector.
    Complejidad: O(n)
    */
    ofstream sorted(archivo);
    for (int i = 0; i < arr.size(); i++){
        sorted << arr[i] << endl;
    }
    sorted.close();
}

void start(string archivo, string tam){
    /*
    void start
    Descripción: Función que lee un archivo, ordena los elementos y crea un archivo con los elementos ordenados.
    Complejidad: O(nlogn)
    */
    ifstream in(archivo);
    vector<int> arr;
    string line;
    while (getline(in, line)){
        arr.push_back(stoi(line));
    }
    auto inicio = high_resolution_clock::now();
    int len = arr.size();
    mergeSort(arr, 0, len - 1);
    crearArchivo(arr, "mergesort" + tam + ".txt");
    in.close();
    auto fin = high_resolution_clock::now();
    auto tiempo = duration_cast<duration<double>>(fin - inicio);
    cout << "Tiempo de ejecución: " << tiempo.count() << " segundos" << endl;
}

int main(){
    /*
    int main
    Descripción: Función principal que prueba el algoritmo de merge sort con diferentes tamaños de arreglos.
    */
    start("data10e3.txt", "10e3");
    start("data10e4.txt", "10e4");
    start("data10e5.txt", "10e5");
    start("data10e6.txt", "10e6");
    return 0;
}