#ifndef RESULTMODEL_H
#define RESULTMODEL_H

#include<QAbstractTableModel>
#include<vector>
#include<utility>
#include<tuple>
#include"palabra.h"
#include"operaciones.h"
#include"algorithm"

using namespace std;

class ResultModel : public QAbstractTableModel
{
        Q_OBJECT
    public:
        vector<Palabra> palabras;
        vector<QString> words;
        vector<long int> ids;
        vector<double> similaridad;
        ResultModel(QObject * parent);
        int rowCount(const QModelIndex & parent = QModelIndex()) const;
        int columnCount(const QModelIndex & parent = QModelIndex()) const;
        QVariant data(const QModelIndex & index, int role) const;
        void setWords(vector<QString> & v);
        void setIds(vector<long int> & v);
        void setSimilaridad(vector<double> & v);
        void setPalabras(vector<Palabra> & p);
};

#endif // RESULTMODEL_H
