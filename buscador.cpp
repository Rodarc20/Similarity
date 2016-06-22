#include "buscador.h"
#include "ui_buscador.h"

Buscador::Buscador(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Buscador)
{
    ui->setupUi(this);
}

Buscador::~Buscador()
{
    delete ui;
}
