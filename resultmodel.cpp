#include "resultmodel.h"

ResultModel::ResultModel(QObject *parent)
{

}

int ResultModel::rowCount(const QModelIndex &parent) const
{
    return palabras.size();
}

int ResultModel::columnCount(const QModelIndex &parent) const
{
    return 3;//tengo tres columnas que mostrar talvez, solo sean 2

}

/*QVariant ResultModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole){
        int col = index.column();
        int row = index.row();
        if(col == 0){
            //return QVariant(ids[row]);
            return QVariant(qlonglong (ids[row]));
        }
        if(col == 1){
            return words[row];
        }
        if(col == 2){
            return QVariant(similaridad[row]);
        }
    }
    return QVariant();
}*/
QVariant ResultModel::data(const QModelIndex &index, int role) const{
    if(role == Qt::DisplayRole){//esto es para cuando use la clase palabras
        int col = index.column();
        int row = index.row();
        if(col == 0){
            //return QVariant(ids[row]);
            return QVariant(qlonglong (palabras[row].indice));
        }
        if(col == 1){
            return palabras[row].palabra;
        }
        if(col == 2){
            return QVariant(palabras[row].similaridad);
        }
    }
    return QVariant();
}


void ResultModel::setWords(vector<QString> &v)
{
    words = v;
}

void ResultModel::setIds(vector<long int> &v)
{
    ids = v;
}

void ResultModel::setSimilaridad(vector<double> &v)
{
    similaridad = v;
}

void ResultModel::setPalabras(vector<Palabra> &p)
{
    palabras = p;
    std::sort(palabras.begin(), palabras.end(), mayorSimilaridad);
}


/*quiza deba agergar un par de metodos para setear los vectores, o que el constructor los reciba, tambien, cosa que esto solo se encarga de mostrarlos*/
