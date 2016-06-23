#ifndef BUSCADOR_H
#define BUSCADOR_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QtSql>
#include "operaciones.h"

namespace Ui {
class Buscador;
}

class Buscador : public QMainWindow
{
        Q_OBJECT

    public:
        void conectar();
        void loadInfo();//por ahora solo recuperare la informacion de unas cuantas palabras
        QSqlDatabase db;
        explicit Buscador(QWidget *parent = 0);
        ~Buscador();

    private slots:
        void on_pushButton_clicked();

        void on_pushButtonSearch_clicked();

    private:
        Ui::Buscador *ui;
};

#endif // BUSCADOR_H
