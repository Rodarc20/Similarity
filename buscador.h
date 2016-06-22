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
        QSqlDatabase db;
        explicit Buscador(QWidget *parent = 0);
        ~Buscador();

    private:
        Ui::Buscador *ui;
};

#endif // BUSCADOR_H
