#include "matriz.h"

Matriz::Matriz(int n_, int m_,  vector<pair<int,int>> v){
    sort (v.begin(), v.end());
    n=n_;
    m=m_;
    for (int i=0;i<=m;i++)
    {
        grado.push_back(0);
    }

    vector<double> valaux2;
    vector<double> colaux2;
    int posicion=1;
    vector<double> valaux;
    vector<int> colaux;
    for (std::vector<pair<int,int>>::iterator it = v.begin() ; it != v.end(); ++it)
    {

        grado[(*it).second]++;
        while (posicion<(*it).first) {
            val.push_back(valaux);
            valaux.clear();
            col.push_back(colaux);
            colaux.clear();
            posicion++;
        }
        colaux.push_back((*it).second);
        valaux.push_back(1);
    }

    val.push_back(valaux);
    col.push_back(colaux);
    posicion++;

    while (posicion <= n) {
        vector<double> valaux3;
        vector<int> colaux3;
        val.push_back(valaux3);
        col.push_back(colaux3);
        posicion++;
    }


}


void Matriz::mostrar(){
    cout<<"valores"<<endl;
    for (vector<vector<double>>::iterator ite = val.begin() ; ite != val.end(); ++ite)
    {
        for (vector<double>::iterator it = (*ite).begin() ; it != (*ite).end(); ++it)
        {
            cout <<*it<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"columnas"<<endl;
    for (std::vector<vector<int>>::iterator ite = col.begin() ; ite != col.end(); ++ite)
    {
        for (std::vector<int>::iterator it = (*ite).begin() ; it != (*ite).end(); ++it)
        {
            cout <<*it<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"grado"<<endl;
    for (std::vector<int>::iterator it = grado.begin() ; it != grado.end(); ++it)
    {
        cout <<*it<<" ";

    }
    cout<<endl;
    cout<<endl;
}

int Matriz::columnas(){
    return m;
}

int Matriz::filas(){
    return n;
}

void Matriz::mutiplicarconst(double k){
    for (vector<vector<double>>::iterator ite = val.begin() ; ite != val.end(); ++ite)
    {

        for (vector<double>::iterator it = (*ite).begin() ; it != (*ite).end(); ++it)
        {
            (*it)=(*it)*k;
        }
    }
}
//no interesa perder el grado porque solo se usa para esta cuenta
void Matriz::dividirporgrado()
{
    vector<vector<int>>::iterator ite2 = col.begin();
    for (vector<vector<double>>::iterator ite = val.begin() ; ite != val.end(); ++ite)
    {
        vector<int>::iterator it2 = (*ite2).begin();
        for (vector<double>::iterator it = (*ite).begin() ; it != (*ite).end(); ++it)
        {
            (*it)=(*it)/grado[*it2];
            it2++;
        }
        ite2++;
    }

}

void Matriz::restaraidentidad()
{


    int f=0;
    vector<vector<int>>::iterator ite2 = col.begin();
    for (vector<vector<double>>::iterator ite = val.begin() ; ite != val.end(); ++ite)
    {
        vector<double> val2;
        vector<int> col2;
        bool estado=true;
        f++;
        vector<int>::iterator it2=(*ite2).begin();
        for (vector<double>::iterator it = (*ite).begin() ; it != (*ite).end(); ++it)
        {
            if ((*it2)==f)
            {
                val2.push_back(1-(*it));
                col2.push_back(*it2);
                estado=false;

            } else
            if (estado && (*it2)>f)
            {
                val2.push_back(1);
                col2.push_back(f);
                val2.push_back(-(*it));
                col2.push_back(*it2);
                estado=false;
            }
            else
            {
                val2.push_back(-(*it));
                col2.push_back(*it2);
            }

            it2++;
        }
        if (estado)
        {
            val2.push_back(1);
            col2.push_back(f);
        }
        swap((*ite),val2);
        swap((*ite2),col2);
        ite2++;
    }
}

double Matriz::condicionamiento() {
    double ac=0, pv=0;
    for(int i = 0; i < val.size();i++) {
        for(int j = 0; j < val.size();j++){
              ac+=abs(val[i][j]);
        }
        if(ac > pv) {
            pv=ac;
        }
        ac=0;
    }
    return pv;
}

vector<double> Matriz::eliminacion_gaussiana()
{
    vector<double> resultado(n,1);

    for (int columna = 1; columna <= m; columna++)
    {
        for (int w = columna; w < val.size(); w++)
        {
            if ((0 < col[w].size()) && (col[w][0] == columna))//ESTO SIGNIFICA QUE LA FILA NO ES 0 EN LA COLUMNA ACTUAL y la fila no es nula
            {

                vector<double> val2;
                vector<int> col2;

                double multiplo = (-1) * ((val[w][0]) / (val[columna - 1][0]));

                unsigned int i = 1;
                unsigned int j = 1;
                while((i < col[columna - 1].size()) && (j < (val[w].size())))
                {
                    if (col[columna - 1][i] < (col[w])[j])
                    {
                        col2.push_back(col[columna - 1][i]);
                        val2.push_back(multiplo * val[columna - 1][i]);
                        i++;
                    } else if (col[columna - 1][i] > col[w][j])
                    {
                        col2.push_back(col[w][j]);
                        val2.push_back(val[w][j]);
                        j++;
                    } else
                    {
                        col2.push_back(col[w][j]);
                        val2.push_back(multiplo * val[columna - 1][i] + val[w][j]);
                        i++;
                        j++;
                    }
                }

                //repetir con elementos restantes
                while (i < col[columna - 1].size())
                {
                    col2.push_back(col[columna-1][i]);
                    val2.push_back(multiplo * (val[columna - 1][i]));
                    i++;
                }


                while (j < (val[w].size()))
                {
                    col2.push_back(col[w][j]);
                    val2.push_back(val[w][j]);
                    j++;
                }

                (col2).swap(col[w]);
                (val2).swap(val[w]);
                resultado[w] = resultado[w] + resultado[columna - 1] * multiplo;



            }
        }
    }


    //ya teniendo una matriz triangular puedo calcular los valores de las x

    for (int i = n - 1; i >= 0; i--) {
        for (int j = 1; j < (val[i]).size(); j++)
        {
            resultado[i] = resultado[i] - resultado[(col[i])[j] - 1]*(val[i])[j];
        }
        resultado[i] = resultado[i] / (val[i])[0];

    }
    //cout<<"resultado "<<resultado[0]<<" "<<resultado[1]<<" "<<resultado[2]<<" "<<resultado[3]<<endl;

    //el paso final seria la normalización
    double suma=0;
    for (int i = 0; i < n; i++)
    {
        suma = suma + resultado[i];
    }

    for (int i = 0; i < n; i++)
    {
        resultado[i] = resultado[i] / suma;
    }

    return resultado;

}
