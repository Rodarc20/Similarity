#ifndef RESULTMODEL_H
#define RESULTMODEL_H

#include<QAbstractTableModel>
#include<vector>
#include<utility>
#include<tuple>

using namespace std;

class ResultModel : public QAbstractTableModel
{
        Q_OBJECT
    public:
        vector<QString> words;
        //vector<long int> ids;
        vector<long long int> ids;
        vector<long long int> similaridad;
        ResultModel(QObject * parent);
        int rowCount(const QModelIndex & parent = QModelIndex()) const;
        int columnCount(const QModelIndex & parent = QModelIndex()) const;
        QVariant data(const QModelIndex & index, int role) const;
        void setWords(vector<QString> & v);
        void setIds(vector<long long int> & v);
        void setSimilaridad(vector<long long int> & v);
};

#endif // RESULTMODEL_H
