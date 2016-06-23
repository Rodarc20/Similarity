#include "buscador.h"
#include "ui_buscador.h"

void Buscador::conectar()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("corpus_google");
    db.setUserName("postgres");
    db.setPassword("postgres");
    db.setPort(5432);
}

Buscador::Buscador(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Buscador)
{
    ui->setupUi(this);
    conectar();
}

Buscador::~Buscador()
{
    delete ui;
}

void Buscador::on_pushButtonSearch_clicked()
{
    QString word = ui->lineEditWord->text();
}
