#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

void matrix(const string& archivo1, const string& archivo2, string tam, int n) {
    /*
    void matrix
    Descripción: Función que lee dos archivos con matrices de tamaño n x n, las multiplica y crea un archivo con la matriz resultante.
    Complejidad: O(n^3)
    */
    ifstream file1(archivo1);
    ifstream file2(archivo2);

    if (!file1.is_open() || !file2.is_open()) {
        cerr << "Error al abrir uno de los archivos" << endl;
        return;
    }

    vector<vector<int>> matrix1(n, vector<int>(n));
    vector<vector<int>> matrix2(n, vector<int>(n));
    vector<vector<int>> matrix2T(n, vector<int>(n)); // Matriz transpuesta

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file1 >> matrix1[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file2 >> matrix2[i][j];
        }
    }
    file1.close();
    file2.close();

    // Transponer la segunda matriz
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix2T[j][i] = matrix2[i][j];
        }
    }

    auto inicio = chrono::high_resolution_clock::now();
    vector<vector<int>> result(n, vector<int>(n, 0));

    // Multiplicación de matrices usando la matriz transpuesta
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                result[i][j] += matrix1[i][k] * matrix2T[j][k];
            }
        }
    }

    ofstream file("cubico" + tam + ".txt");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file << result[i][j] << " ";
        }
        file << endl;
    }
    file.close();

    auto fin = chrono::high_resolution_clock::now();
    auto tiempo = chrono::duration_cast<chrono::duration<double>>(fin - inicio);
    cout << "Tiempo de ejecución: " << tiempo.count() << " segundos" << endl;
}

int main() {
    /*
    int main
    Descripción: Función principal que multiplica matrices de diferentes tamaños.
    */
    matrix("matrix10e4_1.txt", "matrix10e4_2.txt", "10e4", 100);
    matrix("matrix500_1.txt", "matrix500_2.txt", "500", 500);
    matrix("matrix10e6_1.txt", "matrix10e6_2.txt", "10e6", 1000);
    matrix("matrix10e4_1.txt", "matrixid10e4.txt", "id10e4", 100);
    matrix("matrix500_1.txt", "matrixid500.txt", "id500", 500);
    matrix("matrix10e6_1.txt", "matrixid10e6.txt", "id10e6", 1000);
    return 0;
}