#ifndef BUSCADOR_H
#define BUSCADOR_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QtSql>
#include <QMessageBox>
#include <utility>
#include <algorithm>
#include "operaciones.h"
#include "resultmodel.h"

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

        vector<pair<long long, long long> > recuperarVector(QString palabra);
    private slots:
        void on_pushButton_clicked();

        void on_pushButtonSearch_clicked();

    private:
        Ui::Buscador *ui;
};

#endif // BUSCADOR_H
