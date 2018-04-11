#include "matriz.h"
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main(int cantidadDeArgumentos, char** argumentos)
{
    vector< pair<int,int>> fifth;
    double p;
    p = stod(argumentos[2]);

    ofstream salida;
    string sufijo = ".2OUT";
    string archivo = argumentos[1] + sufijo;
    salida.open (archivo);
    ifstream myfile (argumentos[1]);

    int n;
    int m;
    myfile >> n;
    myfile >> m;

    for (int i = 0; i < m; i++) {
        int a;
        int b;
        myfile >> a;
        myfile >> b;
        fifth.push_back(make_pair(b, a));
    }
    Matriz mat(n, n, fifth);
    mat.mutiplicarconst(p);
    mat.dividirporgrado();
    mat.restaraidentidad();
    //ya tenemos I - PWD

    vector<double> resultado = mat.eliminacion_gaussiana();
    salida << p << endl;

    for (int z = 0; z < n; z++) {
        salida << resultado[z] << endl;
    }

    cout << endl;

    salida.close();
    myfile.close();
    cout << "EL CONDICIONAMIENTO ES: " << mat.condicionamiento() <<endl;
}
