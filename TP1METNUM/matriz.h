#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>
#include <iostream>
#include <iterator>     // std::next
#include <algorithm>    // std::sort y swap
#include <utility> // std::pair
#include <cmath>    //std::abs

using namespace std;
class Matriz {

public:
    // n = filas, m = columnas
    Matriz(int n, int m, vector<pair<int,int>> v);

    void mutiplicarconst(double k);

    void dividirporgrado();

    void restaraidentidad();

    void mostrar();

    int columnas();

    int filas();


    vector<double> eliminacion_gaussiana();




private:
    int n;
    int m;
    vector<vector<double>> val;
    vector<vector<int>> col;
    vector<int> grado;//es el valor que tenía al momento de crearse

};

#endif // MATRIZ_H