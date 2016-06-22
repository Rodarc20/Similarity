#include "operaciones.h"

long int binarySearch(vector<pair<long int, long int> > & v, long int ini, long int fin, long int n){//primer mayor o igual en este caso me dira el numero que quiero o el siguinte mayor que representa donde buscare en la siguiente iteracion
    ini--;
    fin++;
    while(fin > ini+1){
        long int med = (ini+fin) >> 1;
        if(v[med].first >= n)//n en realidad es al pair<>.first
            fin = med;
        else//v[med].first < n
            ini=med;
    }
    return fin;
}

long long int modulo (vector<pair<long int, long int> > & v){//estos vectores estan libres de 0s;
    long long int acum = 0;
    for(long int i = 0; i < v.size(); i = -~i){
        acum += v[i].second * v[i].second;
    }
    return acum;
}

long long int productoPunto(vector<pair<long int, long int> > & a, vector<pair<long int, long int> > & b){//aqui es donde aplicare la busqueda binaria, o en todo caso el avace linial sobre los dos vectores a ver cual es mas rapido
    long long int acum = 0;//hace la busqueda binaria sobre el as grandi, y avanzar linealmente por el mas pequeño
    long int j = 0; //j debe ser menor que b
    for(long int i = 0; i < a.size() and j < b.size(); i = -~i){//asumire que a es el mas grande
        j = binarySearch(b, j, b.size()-1, a[i].first);
        if(j < b.size() and b[j].first == a[i].first){
            acum += a[i].second * b[j].second;
            j = -~j; //incremento j, puesto que ya use este valor por lo tanto no es necesario incluirlo en la busqueda binaria, tener cuidao si la busqueda bianri me da mas que b.size()
        }
    }
    return acum;
}

long long int productoPuntoLineal(vector<pair<long int, long int> > & a, vector<pair<long int, long int> > & b){//aqui es donde aplicare la busqueda binaria, o en todo caso el avace linial sobre los dos vectores a ver cual es mas rapido
    long long int acum = 0;//hace la busqueda binaria sobre el as grandi, y avanzar linealmente por el mas pequeño
    long int j = 0; //j debe ser menor que b
    for(long int i = 0; i < a.size() and j < b.size(); i = -~i){//asumire que a es el mas grande
        while(j < b.size() and b[j].first != a[i].first){
            j = -~j;
        }
        if(j < b.size()){//si j es menor que size eso quiere decir que el bucle anterior paro por que encontro una igualdad por lo tanto procedo a acumular
            acum += a[i].second * b[j].second;
            j = -~j; //incremento j, puesto que ya use este valor por lo tanto no es necesario incluirlo en la busqueda binaria, tener cuidao si la busqueda bianri me da mas que b.size()
        }
    }
    return acum;
}

double simcos(vector<pair<long int, long int> > & a, vector<pair<long int, long int> > & b){
    double res;
    if(a.size() >= b.size())
        res = productoPunto(a, b);
    else
        res = productoPunto(b, a);
    res /= modulo(a)*modulo(b); //quiza los modulos deberian estar precalculados
    return res; // y hacer el return defrente
}

