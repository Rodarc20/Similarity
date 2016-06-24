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
    bool ok = db.open();
    if(ok){
        QMessageBox::information(this, "Conection", "Conexion realizada!");
    }
    else{
        QMessageBox::information(this, "Conection", "Error al conectar");
    }
}

vector<pair<long long int, long long int> > Buscador::recuperarVector(QString palabra){//por haor recibe un id en forma de string o quiza pueda buscar el id si este strign ses unna palabra
    QString consulta = "select * from palabras where palabra = '" + palabra + "';";//seria bueno hacer este filtrado antes, y soolo recuperar el vector;
    qDebug() << consulta;
    QSqlQuery query(db);
    query.prepare(consulta);
    query.exec();
    query.first();
    QSqlRecord rec = query.record();
    QString id = rec.field(0).value().toString();
    qDebug() << "id: " << id;
    consulta = "select id_palabra_der, frecuencia from relacion_palabra where id_palabra_izq=" + id + " order by id_palabra_der;";//no necesito retornar id_palabra_izq
    query.prepare(consulta);
    query.exec();
    query.first();
    vector<pair<long long int, long long int> > v (query.size());
    qDebug() << "v size: " << v.size();
    for(int i = 0; i < v.size(); ++i){
        rec = query.record();
        v[i].first = rec.field(0).value().toLongLong();
        v[i].second = rec.field(1).value().toLongLong();
        query.next();
    }
    return v;
}
void Buscador::process(QString palabra)
{//quiza en lugar de retornar los ids y lafrecuencia tambien deberia retornar la palabra de la izquierda, para asociarla de una sola vez a  su repsectivo id, en lugar de hacer despues
    //quiza tambien deberia usar mi propia estructura para almacenar todos los datos pertinentes y amnejarlo en el modelo a base de if como hago ahora, solo que ya todo estaria en unn solo vector
    vector<QString> palabras (10);//ya no debo repuperar nada mas que sus vectores
    palabras[0] = "god";
    palabras[1] = "allah";
    palabras[2] = "buddha";
    palabras[3] = "lion";
    palabras[4] = "tiger";
    palabras[5] = "cat";
    palabras[6] = "hamburger";
    palabras[7] = "pizza";
    palabras[8] = "pen";
    palabras[9] = "notebook";
    int pal = 0;
    for(; pal < palabras.size() && palabras[pal] != palabra; pal = -~pal){
    }
    vector<vector<pair<long long int, long long int> > > vectores (10);
    vector<double> similaridad (10);
    vector<long int> ids (10);
    for(int i = 0; i < palabras.size(); i++){
        vectores[i] = recuperarVector(palabras[i]);
        ids[i] = i;
    }
    qDebug() << "repuracion de vectores completada";
    for(int i = 0; i < palabras.size(); i++){
        similaridad[i] = simcos(vectores[pal], vectores[i]);
        qDebug() << similaridad[i];
    }
    model = new ResultModel(this);
    model->setWords(palabras);
    model->setIds(ids);
    model->setSimilaridad(similaridad);
    ui->tableViewResults->setModel(model);
    ui->tableViewResults->resizeColumnsToContents();
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
    db.close();
    delete ui;
}

void Buscador::on_pushButtonSearch_clicked()
{
    QString word = ui->lineEditWord->text();
    process(word);
}

void Buscador::on_pushButton_clicked()
{

}
