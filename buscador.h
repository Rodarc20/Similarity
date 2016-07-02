#ifndef BUSCADOR_H
#define BUSCADOR_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QtSql>
#include <QMessageBox>
#include <utility>
#include <algorithm>
#include<QLocale>
#include "operaciones.h"
#include "resultmodel.h"
#include "palabra.h"

namespace Ui {
class Buscador;
}

class Buscador : public QMainWindow
{
        Q_OBJECT

    public:
        QSqlDatabase db;
        void conectar();
        void loadInfo();//por ahora solo recuperare la informacion de unas cuantas palabras
        void process(QString palabra);
        ResultModel * model;
        explicit Buscador(QWidget *parent = 0);
        ~Buscador();

        QString recuperarPalabraById(long long int indice);
        QString recuperarIdByPalabra(QString palabra);
        vector<pair<long long, long long> > recuperarVectorByPalabra(QString palabra);
        vector<pair<long long, long long> > recuperarVectorById(long long indice);
        void process2(QString palabra);
        void process3(QString palabra);
        void process10(QString palabra);
    private slots:
        void on_pushButton_clicked();

        void on_pushButtonSearch_clicked();

    private:
        Ui::Buscador *ui;
};

#endif // BUSCADOR_H
