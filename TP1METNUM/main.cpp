#include "matriz.h"
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

//int main()
//{
//    pair<int,int> myints[] = {make_pair(2,1), make_pair(3,1), make_pair(4,1)}; //la entrada debe invertirse
//    vector< pair<int,int>> fifth (myints, myints + sizeof(myints) / sizeof(pair<int,int>) );
//
//    Matriz mat(4, 4, fifth);
//    mat.mutiplicarconst(0.9);
//    mat.dividirporgrado();
//    mat.restaraidentidad();
//
//    vector<double> resultado=mat.eliminacion_gaussiana();
//    cout<<"resultado "<<resultado[0]<<" "<<resultado[1]<<" "<<resultado[2]<<" "<<resultado[3]<<endl;
//}

vector< pair<int, int>> crearVectorNoCeros(char* argumento, ifstream &archivoIN);

void crearArchivoSalida();

vector<double> operacionesConMatriz(int filas, vector<pair<int, int>> noCeros, double p);

int main(int cantArgumentos, char** argumentos){
    ifstream archivoIN;

    //Obtengo valor p
    double p = stod(argumentos[2]);

    //Abro el archivo
    archivoIN.open(argumentos[1]);

    //Leemos la cantidad de filas (que es la misma que la de columnas)
    int filasYColumnas;

    string n;

    archivoIN >> n;

    filasYColumnas = stoi(n);

    //

    //Conseguimos la cantidad de relaciones de la matriz
    string cantRelacionesAux;

    archivoIN >> cantRelacionesAux;

    int cantRelaciones = stoi(cantRelacionesAux);

    //

    vector< pair<int, int>> noCeros(crearVectorNoCeros(argumentos[1], archivoIN));

    archivoIN.close();

    cout << "FILAS (Y COLUMNAS): " << filasYColumnas << endl;

    cout << "CANTIDAD DE RELACIONES: " << cantRelaciones << endl;

    cout << "VALOR P: " << p << endl;

    cout << "CONTENIDO DEL ARREGLO: " << endl;

    for(int i = 0; i < noCeros.size(); i++){
        cout << "FILA: " << noCeros[i].first << ", COLUMNA: " << noCeros[i].second << endl;
    }

    cout << "----------------------------------------" << endl;

    cout << "-------------------RESULTADOS DEL PAGERANK---------------------" << endl;

    cout << "VALOR P: " << p << endl;

    //Realizamos las operaciones

    vector<double> resultados = operacionesConMatriz(filasYColumnas, noCeros, p);

    for(int i = 0; i < resultados.size(); i++){
        cout << "RESULTADO " << i << ": " << resultados[i] << endl;
    }

    cout << "----------------------------------------" << endl;

    //crearArchivoSalida();

    return 0;
}

vector< pair<int, int>> crearVectorNoCeros(char* argumento, ifstream &archivoIN){

    //Recorremos el archivo

    //

    vector< pair<int,int>> noCeros;
    string line;

    //Leemos el archivo, esto avanza de a dos datos
    //es feo (muy feo de hecho) pero por ahora va, si programo algo que parta un string lo hago
    while(archivoIN >> line){

        //Esto está por si llega acá al final
        if(line == ""){
            break;
        }

        //cout << line << endl;

        int filaActual = stoi(line);

        //Leemos el segundo elemento de la fila del txt
        archivoIN >> line;

        int columnaActual = stoi(line);

        noCeros.push_back(make_pair(filaActual, columnaActual));
    }

    return noCeros;
};

vector<double> operacionesConMatriz(int filas, vector<pair<int, int>> noCeros, double p) {
    Matriz mat(filas, filas, noCeros);

    mat.mutiplicarconst(p);
    mat.dividirporgrado();
    mat.restaraidentidad();

    vector<double> res = mat.eliminacion_gaussiana();
    return res;
}

//Proximamente
void crearArchivoSalida(){
    ofstream archivoOUT;

    //Acá escribimos el out
    archivoOUT.open("ARCHIVOSALIDA.txt");

    //

    archivoOUT.close();

}
