#ifndef BUSCADOR_H
#define BUSCADOR_H

#include <QMainWindow>

namespace Ui {
class Buscador;
}

class Buscador : public QMainWindow
{
        Q_OBJECT

    public:
        explicit Buscador(QWidget *parent = 0);
        ~Buscador();

    private:
        Ui::Buscador *ui;
};

#endif // BUSCADOR_H
