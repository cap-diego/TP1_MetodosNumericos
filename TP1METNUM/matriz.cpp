#include "matriz.h"

Matriz::Matriz(int n_, int m_,  vector<pair<int,int>> v){
    sort (v.begin(), v.end());
    n=n_;
    m=m_;

    for (int i=0;i<=m;i++)
    {
        grado.push_back(0);
    }
    vector<double> valaux;
    vector<int> colaux;

    vector<double> valaux2;
    vector<double> colaux2;

    int posicion=1;

    for (std::vector< pair<int,int>>::iterator it = v.begin() ; it != v.end(); ++it) {

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
    while (posicion<=n){

        vector<double> valaux3;
        vector<int> colaux3;
        val.push_back(valaux3);
        col.push_back(colaux3);
        posicion++;
    }


}


void Matriz::mostrar(){
    for (vector<vector<double>>::iterator ite = val.begin() ; ite != val.end(); ++ite) {
        for (vector<double>::iterator it = (*ite).begin() ; it != (*ite).end(); ++it) {
            cout <<*it<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    for (std::vector<vector<int>>::iterator ite = col.begin() ; ite != col.end(); ++ite) {
        for (std::vector<int>::iterator it = (*ite).begin() ; it != (*ite).end(); ++it) {
            cout <<*it<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    for (std::vector<int>::iterator it = grado.begin() ; it != grado.end(); ++it) {
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
        }
        ite2++;
    }

}

void Matriz::restaraidentidad() {

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

//aprovechamos que es diagonal dominante ya que la diagonal de la adyacencia es 0 ya que no hay autolinks y todos los otros elementos son menores a 0 por lo que es diagonal domiannte.
// De ese modo se que cada columna tiene al menos un elemento. Lo que se debe hacer es avanzar en cada fila tal que la columna sea mayor o igual. Agarro los que son iguales y encuentro el de mayor
// valor (esa es la fila a usar). Ahora divido ese primer elemento por el del resto de la columna tal que al restar a la otra fila la primera multiplicada dé 0. Esto se hace haciendo una
//combinacion de los 2 vectores.
vector<double> Matriz::eliminacion_gaussiana()
{
    vector<double> resultado(n,1);
    //es posible asegurar que la columna actual es 0 o mayor porque los anteriores fueron eliminados porque es triangular superior hasta ese sector
    for (int columna = 1; columna <= m; columna++)
    {
        vector<vector<double>>::iterator maximo;
        vector<vector<int>>::iterator maximo2;

        int maximum = 0;
        int w = columna - 1;
        int maxw = 0;
        vector<vector<int>>::iterator ite2 = col.begin()+columna-1;

        for (vector<vector<double>>::iterator ite = val.begin() + columna - 1 ; ite != val.end(); ++ite)
        {
            if ((0<(*ite2).size())&&((*ite2)[0] == columna))
            {

                if (abs((*ite)[0]) >= maximum)
                {

                    maximum = abs(((*ite)[0]));
                    maximo = ite;
                    maximo2 = ite2;
                    maxw = w;
                }
            }
            ite2++;
            w++;
        }
        (col[columna-1]).swap(*maximo2);
        (val[columna-1]).swap(*maximo);

        double aux = resultado[columna-1];
        resultado[columna-1] = resultado[maxw];
        resultado[maxw] = aux;





        //con esto termina el proceso de colocar el maximo en la fila correspondiente para reducir error. Es necesario porque a lo largo del proceso el maximo puede dejar de estar en la diagonal
        //para hacer esto hago de forma similar pero en el paso se busca encontrar el valor por el que multiplicar la fila y luego se hace la combinación

        ite2 = col.begin()+columna;
        w = columna-1;//se usa para guardar el numero de fila actualmente siendo modificada
        for (vector<vector<double>>::iterator ite = val.begin()+columna ; ite != val.end(); ++ite)
        {
            w++;
            if ((0<(*ite2).size())&&((*ite2)[0]==columna))//ESTO SIGNIFICA QUE NO ES 0 EN LA COLUMNA ACTUAL LA FILA
            {

                vector<double> val2;
                vector<int> col2;

                double multiplo = (-1)*(((*ite)[0])/((*(val.begin()+columna-1))[0]));
                unsigned int i = 1;
                unsigned int j = 1;

                while((i<(*((col.begin())+columna-1)).size()) && (j<((*ite).size())))
                {
                    if ((*(col.begin()+columna-1))[i]<(*ite2)[j])
                    {
                        col2.push_back((*(col.begin()+columna-1))[i]);
                        val2.push_back(multiplo*(*(val.begin()+columna-1))[i]);
                        i++;
                    }

                    else if ((*(col.begin()+columna-1))[i]>(*ite2)[j])
                    {
                        col2.push_back((*ite2)[j]);
                        val2.push_back((*ite)[j]);
                        j++;
                    }

                    else if ((*(col.begin()+columna-1))[i]==(*ite2)[j])
                    {
                        col2.push_back((*ite2)[j]);
                        val2.push_back(multiplo*(*(val.begin()+columna-1))[i]+(*ite)[j]);
                        i++;
                        j++;
                    }
                }

                //repetir con elementos restantes
                while (i<(*((col.begin())+columna-1)).size())
                {
                    col2.push_back((*(col.begin()+columna-1))[i]);
                    val2.push_back(multiplo*(*(val.begin()+columna-1))[i]);
                    i++;
                }


                while (j<((*ite).size()))
                {
                    col2.push_back((*ite2)[j]);
                    val2.push_back((*ite)[j]);
                    j++;
                }

                (col2).swap(*ite2);
                (val2).swap(*ite);
                resultado[w]=resultado[w]+resultado[columna-1]*multiplo;



            }

            ite2++;
        }
    }


    //ya teniendo una matriz triangular puedo calcular los valores de las x

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 1; j<(val[i]).size(); j++)
        {
            resultado[i] = resultado[i] - resultado[(col[i])[j]-1]*(val[i])[j];
        }

        resultado[i] = resultado[i] / (val[i])[0];
    }
    //cout<<"resultado "<<resultado[0]<<" "<<resultado[1]<<" "<<resultado[2]<<" "<<resultado[3]<<endl;

    //el paso final seria la normalización
    double suma = 0;
    for (int i = 0; i < n ;i++)
    {
        suma = suma + resultado[i];
    }

    for (int i=0;i<n;i++)
    {
        resultado[i] = resultado[i] / suma;
    }

    return resultado;

}
