#ifndef OPERACIONES_H
#define OPERACIONES_H
#include<iostream>
#include<string>
#include<vector>
#include<tuple>
#include<utility>
#include<math.h>
#include"palabra.h"

using namespace std;

long int binarySearch(vector<pair<long long int, long long int> > & v, long int ini, long int fin, long int n);//primer mayor o igual en este caso me dira el numero que quiero o el siguinte mayor que representa donde buscare en la siguiente iteracion

long long int modulo (vector<pair<long long int, long long int> > & v);//estos vectores estan libres de 0s;

long long int productoPunto(vector<pair<long long int, long long int> > & a, vector<pair<long long int, long long int> > & b);//aqui es donde aplicare la busqueda binaria, o en todo caso el avace linial sobre los dos vectores a ver cual es mas rapido

long long int productoPuntoLineal(vector<pair<long long int, long long int> > & a, vector<pair<long long int, long long int> > & b);//aqui es donde aplicare la busqueda binaria, o en todo caso el avace linial sobre los dos vectores a ver cual es mas rapido

double simcos(vector<pair<long long int, long long int> > & a, vector<pair<long long int, long long int> > & b);
double simcos2(vector<pair<long long int, long long int> > & a, vector<pair<long long int, long long int> > & b);

bool mayorSimilaridad(Palabra a, Palabra b);
/*Parece que solo tendre qu usar un pair, ua que lo recupero de la base de datos, si bien son tripletas, pero tengo que separar por palabra 1, y construir un vector, con los otros dos, serias estupido conser var tripletas
en la cual un valor sea igual en todas,
los pair<indicePalabra2, frecuencia>
*/

#endif // OPERACIONES_H
