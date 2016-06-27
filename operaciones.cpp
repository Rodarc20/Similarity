#include "operaciones.h"

long int binarySearch(vector<pair<long long int, long long int> > & v, long int ini, long int fin, long int n){//primer mayor o igual en este caso me dira el numero que quiero o el siguinte mayor que representa donde buscare en la siguiente iteracion
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

long long int modulo (vector<pair<long long int, long long int> > & v){//estos vectores estan libres de 0s;
    long long int acum = 0;
    for(long int i = 0; i < v.size(); i = -~i){
        acum += v[i].second * v[i].second;
    }
    return acum;//me deberia devolver la raiz cuadrada por ahora lo dejare afuera
}

long long int productoPunto(vector<pair<long long int, long long int> > & a, vector<pair<long long int, long long int> > & b){//aqui es donde aplicare la busqueda binaria, o en todo caso el avace linial sobre los dos vectores a ver cual es mas rapido
    long long int acum = 0;//hace la busqueda binaria sobre el as grandi, y avanzar linealmente por el mas pequeño
    long int j = 0; //j debe ser menor que b
    for(long int i = 0; i < a.size() && j < b.size(); i = -~i){//asumire que a es el mas grande
        j = binarySearch(b, j, b.size()-1, a[i].first);
        if(j < b.size() && b[j].first == a[i].first){
            acum += a[i].second * b[j].second;
            j = -~j; //incremento j, puesto que ya use este valor por lo tanto no es necesario incluirlo en la busqueda binaria, tener cuidao si la busqueda bianri me da mas que b.size()
        }
    }
    return acum;
}

long long int productoPuntoLineal(vector<pair<long long int, long long int> > & a, vector<pair<long long int, long long int> > & b){//aqui es donde aplicare la busqueda binaria, o en todo caso el avace linial sobre los dos vectores a ver cual es mas rapido
    long long int acum = 0;//hace la busqueda binaria sobre el as grandi, y avanzar linealmente por el mas pequeño
    long int j = 0; //j debe ser menor que b
    for(long int i = 0; i < a.size() && j < b.size(); i = -~i){//asumire que a es el mas grande/ j < b.size() esta bien en estas funciones por que si ya llegue al final, no tienes sentido seuir iterando por a
        while(j < b.size() && b[j].first < a[i].first){//no diferente sino que sea menor
            j = -~j;
        }
        if(j < b.size() && a[i].first == b[j].first){//si j es menor que size eso quiere decir que el bucle anterior paro por que encontro una igualdad por lo tanto procedo a acumular
            acum += a[i].second * b[j].second;
            j = -~j; //incremento j, puesto que ya use este valor por lo tanto no es necesario incluirlo en la busqueda binaria, tener cuidao si la busqueda bianri me da mas que b.size()
        }
    }
    return acum;
}

double simcos(vector<pair<long long int, long long int> > & a, vector<pair<long long int, long long int> > & b){
    long long int resI;
    if(a.size() >= b.size())
        resI = productoPunto(a, b);
    else
        resI = productoPunto(b, a);
    double mods = sqrt(modulo(a))*sqrt(modulo(b));
    double res = (double)resI / mods; //quiza los modulos deberian estar precalculados, al  menos el del vector con el que estoy comparando no lo deberia calcular siempre
    return res; // y hacer el return defrente
}

double simcos2(vector<pair<long long int, long long int> > & a, vector<pair<long long int, long long int> > & b){
    long long int acumPP = 0;
    long long int acumMA = 0;
    long long int acumMB = 0;
    long int j = 0; //j debe ser menor que b
    for(long int i = 0; i < a.size() /*&& j < b.size()*/; i = -~i){//asumire que a es el mas grande
        while(j < b.size() && b[j].first < a[i].first){//no diferente sino que sea menor
            acumMB += b[j].second * b[j].second;
            j = -~j;
        }
        if(j < b.size() && a[i].first == b[j].first){//si j es menor que size eso quiere decir que el bucle anterior paro por que encontro una igualdad por lo tanto procedo a acumular
            acumPP += a[i].second * b[j].second;
            acumMB += b[j].second * b[j].second;
            j = -~j; //incremento j, puesto que ya use este valor por lo tanto no es necesario incluirlo en la busqueda binaria, tener cuidao si la busqueda bianri me da mas que b.size()
        }
        acumMA += a[i].second * a[i].second;
    }
    //si a termina primero, hay jotas por recorrer
    while(j < b.size()){//no diferente sino que sea menor
        acumMB += b[j].second * b[j].second;
        j = -~j;
    }
    double res = (double)acumPP / (sqrt(acumMA)*sqrt(acumMB));
    return res;
}

bool mayorSimilaridad(Palabra a, Palabra b){
    if(a.similaridad > b.similaridad){
        return 1;
    }
    else{
        if(a.indice == b.indice){//si son iguales, los oredenare por orden alfabetico, es decir el mayor sera el que tenga el indice mas alto
            return a.indice > b.indice;//quiza solo deba poner este return, y quitar el return 0,
        }
        return 0;
    }
}
