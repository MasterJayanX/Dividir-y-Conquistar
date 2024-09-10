#include <bits/stdc++.h>
#include <chrono>
using namespace std;
typedef long long lld;

inline lld** MatrixMultiply(lld** a, lld** b, int n, int l, int m)
{
    /*
    lld** MatrixMultiply
    Descripción: Función que multiplica dos matrices de tamaño n x l y l x m.
    Complejidad: O(nlm)
    */
    lld** c = new lld*[n];
    for (int i = 0; i < n; i++)
        c[i] = new lld[m];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c[i][j] = 0;
            for (int k = 0; k < l; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

inline lld** Strassen(lld** a, lld** b, int n, int l, int m)
{
    /*
    lld** Strassen
    Descripción: Función que multiplica dos matrices de tamaño n x l y l x m usando el algoritmo de Strassen.
    Complejidad: O(n^2.81)
    */
    if (n == 1 || l == 1 || m == 1)
        return MatrixMultiply(a, b, n, l, m);

    lld** c = new lld*[n];
    for (int i = 0; i < n; i++)
        c[i] = new lld[m];

    int adjN = (n >> 1) + (n & 1);
    int adjL = (l >> 1) + (l & 1);
    int adjM = (m >> 1) + (m & 1);

    lld**** As = new lld***[2];
    for (int x = 0; x < 2; x++) {
        As[x] = new lld**[2];
        for (int y = 0; y < 2; y++) {
            As[x][y] = new lld*[adjN];
            for (int i = 0; i < adjN; i++) {
                As[x][y][i] = new lld[adjL];
                for (int j = 0; j < adjL; j++) {
                    int I = i + (x & 1) * adjN;
                    int J = j + (y & 1) * adjL;
                    As[x][y][i][j] = (I < n && J < l) ? a[I][J] : 0;
                }
            }
        }
    }

    lld**** Bs = new lld***[2];
    for (int x = 0; x < 2; x++) {
        Bs[x] = new lld**[2];
        for (int y = 0; y < 2; y++) {
            Bs[x][y] = new lld*[adjN];
            for (int i = 0; i < adjL; i++) {
                Bs[x][y][i] = new lld[adjM];
                for (int j = 0; j < adjM; j++) {
                    int I = i + (x & 1) * adjL;
                    int J = j + (y & 1) * adjM;
                    Bs[x][y][i][j] = (I < l && J < m) ? b[I][J] : 0;
                }
            }
        }
    }

    lld*** s = new lld**[10];
    for (int i = 0; i < 10; i++) {
        switch (i) {
        case 0:
            s[i] = new lld*[adjL];
            for (int j = 0; j < adjL; j++) {
                s[i][j] = new lld[adjM];
                for (int k = 0; k < adjM; k++) {
                    s[i][j][k] = Bs[0][1][j][k] - Bs[1][1][j][k];
                }
            }
            break;
        case 1:
            s[i] = new lld*[adjN];
            for (int j = 0; j < adjN; j++) {
                s[i][j] = new lld[adjL];
                for (int k = 0; k < adjL; k++) {
                    s[i][j][k] = As[0][0][j][k] + As[0][1][j][k];
                }
            }
            break;
        case 2:
            s[i] = new lld*[adjN];
            for (int j = 0; j < adjN; j++) {
                s[i][j] = new lld[adjL];
                for (int k = 0; k < adjL; k++) {
                    s[i][j][k] = As[1][0][j][k] + As[1][1][j][k];
                }
            }
            break;
        case 3:
            s[i] = new lld*[adjL];
            for (int j = 0; j < adjL; j++) {
                s[i][j] = new lld[adjM];
                for (int k = 0; k < adjM; k++) {
                    s[i][j][k] = Bs[1][0][j][k] - Bs[0][0][j][k];
                }
            }
            break;
        case 4:
            s[i] = new lld*[adjN];
            for (int j = 0; j < adjN; j++) {
                s[i][j] = new lld[adjL];
                for (int k = 0; k < adjL; k++) {
                    s[i][j][k] = As[0][0][j][k] + As[1][1][j][k];
                }
            }
            break;
        case 5:
            s[i] = new lld*[adjL];
            for (int j = 0; j < adjL; j++) {
                s[i][j] = new lld[adjM];
                for (int k = 0; k < adjM; k++) {
                    s[i][j][k] = Bs[0][0][j][k] + Bs[1][1][j][k];
                }
            }
            break;
        case 6:
            s[i] = new lld*[adjN];
            for (int j = 0; j < adjN; j++) {
                s[i][j] = new lld[adjL];
                for (int k = 0; k < adjL; k++) {
                    s[i][j][k] = As[0][1][j][k] - As[1][1][j][k];
                }
            }
            break;
        case 7:
            s[i] = new lld*[adjL];
            for (int j = 0; j < adjL; j++) {
                s[i][j] = new lld[adjM];
                for (int k = 0; k < adjM; k++) {
                    s[i][j][k] = Bs[1][0][j][k] + Bs[1][1][j][k];
                }
            }
            break;
        case 8:
            s[i] = new lld*[adjN];
            for (int j = 0; j < adjN; j++) {
                s[i][j] = new lld[adjL];
                for (int k = 0; k < adjL; k++) {
                    s[i][j][k] = As[0][0][j][k] - As[1][0][j][k];
                }
            }
            break;
        case 9:
            s[i] = new lld*[adjL];
            for (int j = 0; j < adjL; j++) {
                s[i][j] = new lld[adjM];
                for (int k = 0; k < adjM; k++) {
                    s[i][j][k] = Bs[0][0][j][k] + Bs[0][1][j][k];
                }
            }
            break;
        }
    }

    lld*** p = new lld**[7];
    p[0] = Strassen(As[0][0], s[0], adjN, adjL, adjM);
    p[1] = Strassen(s[1], Bs[1][1], adjN, adjL, adjM);
    p[2] = Strassen(s[2], Bs[0][0], adjN, adjL, adjM);
    p[3] = Strassen(As[1][1], s[3], adjN, adjL, adjM);
    p[4] = Strassen(s[4], s[5], adjN, adjL, adjM);
    p[5] = Strassen(s[6], s[7], adjN, adjL, adjM);
    p[6] = Strassen(s[8], s[9], adjN, adjL, adjM);

    for (int i = 0; i < adjN; i++) {
        for (int j = 0; j < adjM; j++) {
            c[i][j] = p[4][i][j] + p[3][i][j] - p[1][i][j] + p[5][i][j];
            if (j + adjM < m)
                c[i][j + adjM] = p[0][i][j] + p[1][i][j];
            if (i + adjN < n)
                c[i + adjN][j] = p[2][i][j] + p[3][i][j];
            if (i + adjN < n && j + adjM < m)
                c[i + adjN][j + adjM] = p[4][i][j] + p[0][i][j] - p[2][i][j] - p[6][i][j];
        }
    }

    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            for (int i = 0; i < adjN; i++) {
                delete[] As[x][y][i];
            }
            delete[] As[x][y];
        }
        delete[] As[x];
    }
    delete[] As;

    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            for (int i = 0; i < adjL; i++) {
                delete[] Bs[x][y][i];
            }
            delete[] Bs[x][y];
        }
        delete[] Bs[x];
    }
    delete[] Bs;

    for (int i = 0; i < 10; i++) {
        switch (i) {
        case 0:
        case 3:
        case 5:
        case 7:
        case 9:
            for (int j = 0; j < adjL; j++) {
                delete[] s[i][j];
            }
            break;
        case 1:
        case 2:
        case 4:
        case 6:
        case 8:
            for (int j = 0; j < adjN; j++) {
                delete[] s[i][j];
            }
            break;
        }
        delete[] s[i];
    }
    delete[] s;

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < (n >> 1); j++) {
            delete[] p[i][j];
        }
        delete[] p[i];
    }
    delete[] p;

    return c;
}

void readMatrix(const string& filename, lld**& matrix, int n, int m) {
    /*
    void readMatrix
    Descripción: Función que lee un archivo con una matriz de tamaño n x m.
    Complejidad: O(nm)
    */
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo " << filename << endl;
        exit(1);
    }
    matrix = new lld*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new lld[m];
        for (int j = 0; j < m; j++) {
            file >> matrix[i][j];
        }
    }
    file.close();
}

void writeMatrix(const string& filename, lld** matrix, int n) {
    /*
    void writeMatrix
    Descripción: Función que crea un archivo con una matriz de tamaño n x m.
    Complejidad: O(n^2)
    */
    ofstream file(filename);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file << matrix[i][j] << " ";
        }
        file << endl;
    }
    file.close();
}

void matrixMultiplication(const string& fileA, const string& fileB, const string& outputFile, int n, int l, int m) {
    /*
    void matrixMultiplication
    Descripción: Función que lee dos archivos con matrices de tamaño n x l y l x m, respectivamente, y crea un archivo con la matriz resultante de la multiplicación.
    Complejidad: O(n^2.81)
    */
    lld** matA;
    lld** matB;
    readMatrix(fileA, matA, n, l);
    readMatrix(fileB, matB, l, m);

    auto inicio = chrono::high_resolution_clock::now();
    lld** matC = Strassen(matA, matB, n, l, m);
    auto fin = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::duration<double>>(fin - inicio);
    cout << "Tiempo de ejecución: " << duration.count() << " segundos" << endl;

    writeMatrix(outputFile, matC, n);

    for (int i = 0; i < n; i++) {
        delete[] matA[i];
        delete[] matC[i];
    }
    delete[] matA;
    delete[] matC;

    for (int i = 0; i < l; i++) {
        delete[] matB[i];
    }
    delete[] matB;
}

int main() {
    /*
    int main
    Descripción: Función principal que realiza la multiplicación de matrices de diferentes tamaños.
    */
    matrixMultiplication("matrix10e4_1.txt", "matrix10e4_2.txt", "strassen10e4.txt", 100, 100, 100);
    matrixMultiplication("matrix500_1.txt", "matrix500_2.txt", "strassen500.txt", 500, 500, 500);
    matrixMultiplication("matrix10e6_1.txt", "matrix10e6_2.txt", "strassen10e6.txt", 1000, 1000, 1000);
    matrixMultiplication("matrix10e4_1.txt", "matrixid10e4.txt", "strassenid10e4.txt", 100, 100, 100);
    matrixMultiplication("matrix500_1.txt", "matrixid500.txt", "strassenid500.txt", 500, 500, 500);
    matrixMultiplication("matrix10e6_1.txt", "matrixid10e6.txt", "strassenid10e6.txt", 1000, 1000, 1000);
    return 0;
}