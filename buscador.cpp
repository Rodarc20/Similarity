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
//quiza la final sea conveniente, yo recuperar todas la s palabras de la palabras y buscar en sete vector, lo que yo ncesito, usando busqueda bianria, esot para el momento final en la que ya he procesdo los vectores, pero no se a que palabra le pertenecen
//tal vez  no sea necesaria esta funcion siguiente
//hay en totoal 93243 palabras
QString Buscador::recuperarPalabraById(long long int indice){//antes de entra a la funcion el indice debe haber sido convertido a string
    //QString consulta = "select palabra from palabras where id_palabra = " + indice + "';";
    QString id = QString::number(indice);
    //QString consulta = "select palabra from palabra_izq where id_palabra_izq = " + id + ";";//para la forma 1
    QString consulta = "select palabra from palabra_izqpos where id_palabra_izq = " + id + ";";//para la forma 3
    QSqlQuery query(db);
    query.prepare(consulta);
    query.exec();
    query.first();
    QSqlRecord rec = query.record();
    return rec.field(0).value().toString();
}
//esta funcion quiza no la use, ya que no debo recuperar por vectores si no todo s la avez y hacer el calculo, por ahora probae asi

QString Buscador::recuperarIdByPalabra(QString palabra){
    //QString consulta = "select id_palabra from palabras where palabra = '" + palabra + "';";
    //QString consulta = "select id_palabra_izq from palabra_izq where palabra = '" + palabra + "';";//para la forma1
    QString consulta = "select id_palabra_izq from palabra_izqpos where palabra = '" + palabra + "';";//para la forma3
    QSqlQuery query(db);
    query.prepare(consulta);
    query.exec();
    query.first();
    QSqlRecord rec = query.record();
    return rec.field(0).value().toString();
}
//esta funcion quiza no la use, ya que no debo recuperar por vectores si no todo s la avez y hacer el calculo, por ahora probae asi
vector<pair<long long int, long long int> > Buscador::recuperarVectorByPalabra(QString palabra){//por haor recibe un id en forma de string o quiza pueda buscar el id si este strign ses unna palabra
    QSqlQuery query(db);
    QString id = recuperarIdByPalabra(palabra);
    //qDebug() << "id: " << id;
    //QString consulta = "select id_palabra_der, frecuencia from relacion_palabra where id_palabra_izq=" + id + " order by id_palabra_der;";//no necesito retornar id_palabra_izq
    //QString consulta = "select id_palabra_der, frecuencia from relacion_izq_der where id_palabra_izq=" + id + " order by id_palabra_der;";//forma1,no necesito retornar id_palabra_izq
    QString consulta = "select id_palabra_der, frecuencia from relacion_izq_derpos where id_palabra_izq=" + id + " order by id_palabra_der;";//forma3,no necesito retornar id_palabra_izq
    query.prepare(consulta);
    query.exec();
    query.first();
    vector<pair<long long int, long long int> > v (query.size());
    QSqlRecord rec;
    //qDebug() << "v size: " << v.size();
    for(int i = 0; i < v.size(); ++i){
        rec = query.record();
        v[i].first = rec.field(0).value().toLongLong();
        v[i].second = rec.field(1).value().toLongLong();
        query.next();
    }
    return v;
}

vector<pair<long long int, double> > Buscador::recuperarVectorByPalabra2(QString palabra){//por haor recibe un id en forma de string o quiza pueda buscar el id si este strign ses unna palabra
    QSqlQuery query(db);
    QString id = recuperarIdByPalabra(palabra);
    //qDebug() << "id: " << id;
    //QString consulta = "select id_palabra_der, frecuencia from relacion_palabra where id_palabra_izq=" + id + " order by id_palabra_der;";//no necesito retornar id_palabra_izq
    //QString consulta = "select id_palabra_der, frecuencia from relacion_izq_der where id_palabra_izq=" + id + " order by id_palabra_der;";//forma1,no necesito retornar id_palabra_izq
    QString consulta = "select id_palabra_der, frecuencia from relacion_izq_derpos_d where id_palabra_izq=" + id + " order by id_palabra_der;";//forma3,no necesito retornar id_palabra_izq
    query.prepare(consulta);
    query.exec();
    query.first();
    vector<pair<long long int, double> > v (query.size());
    QSqlRecord rec;
    //qDebug() << "v size: " << v.size();
    for(int i = 0; i < v.size(); ++i){
        rec = query.record();
        v[i].first = rec.field(0).value().toLongLong();
        v[i].second = rec.field(1).value().toDouble();
        query.next();
    }
    return v;
}

vector<pair<long long int, long long int> > Buscador::recuperarVectorById(long long int indice){//por haor recibe un id en forma de string o quiza pueda buscar el id si este strign ses unna palabra
    QSqlQuery query(db);
    QString id = QString::number(indice);
    //qDebug() << "id: " << id;
    //QString consulta = "select id_palabra_der, frecuencia from relacion_palabra where id_palabra_izq=" + id + " order by id_palabra_der;";//no necesito retornar id_palabra_izq
    //QString consulta = "select id_palabra_der, frecuencia from relacion_izq_der where id_palabra_izq=" + id + " order by id_palabra_der;";//forma1,no necesito retornar id_palabra_izq
    QString consulta = "select id_palabra_der, frecuencia from relacion_izq_derpos where id_palabra_izq=" + id + " order by id_palabra_der;";//forma3,no necesito retornar id_palabra_izq
    query.prepare(consulta);
    query.exec();
    query.first();
    vector<pair<long long int, long long int> > v (query.size());
    QSqlRecord rec;
    //qDebug() << "v size: " << v.size();
    for(int i = 0; i < v.size(); ++i){
        rec = query.record();
        v[i].first = rec.field(0).value().toLongLong();
        v[i].second = rec.field(1).value().toLongLong();
        query.next();
    }
    return v;
}
/*double simcos2(vector<pair<long long int, long long int> > & a, vector<pair<long long int, long long int> > & b){
    double res;
    long long int acumPP = 0;
    long long int acumMA = 0;
    long long int acumMB = 0;
    long int j = 0; //j debe ser menor que b
    for(long int i = 0; i < a.size() && j < b.size(); i = -~i){//asumire que a es el mas grande
        while(j < b.size() && b[j].first < a[i].first){//no diferente sino que sea menor
            acumMB += b[j].second * b[j].second;
            j = -~j;
        }
        if(j < b.size() && a[i].first == b[j].first){//si j es menor que size eso quiere decir que el bucle anterior paro por que encontro una igualdad por lo tanto procedo a acumular
            acumPP += a[i].second * b[j].second;
            acumMB += b[j].second * b[j].second;
            j = -~j; //incremento j, puesto que ya use este valor por lo tanto no es necesario incluirlo en la busqueda binaria, tener cuidao si la busqueda bianri me da mas que b.size()
        }
        acumMA += a[i].second * a[i].second;
    }
    //si a termina primero, hay jotas por recorrer
    while(j < b.size()){//no diferente sino que sea menor
        acumMB += b[j].second * b[j].second;
        j = -~j;
    }
    res = (double)acumPP / (sqrt(acumMA)*sqrt(acumMB));
    return res;
}*/
void Buscador::process3(QString palabra){
    vector<pair<long long int, long long int> > vPalabra = recuperarVectorByPalabra(palabra);
    if(!vPalabra.size()){//si la palabra no esta, no debo procesarla
        return;
    }
    qDebug() << vPalabra.size();
    QSqlQuery query2 (db);
    //QString consulta2 = "select * from palabra_izq order by id_palabra_izq;";//forma1 quiza solod deba retornal palabra
    QString consulta2 = "select * from palabra_izqpos order by id_palabra_izq;";//forma3 quiza solod deba retornal palabra
    query2.prepare(consulta2);
    query2.exec();
    query2.first();
    QSqlRecord rec2;// = query2.record();
    QSqlQuery query (db);
    //QString consulta = "select * from relacion_izq_der order by id_palabra_izq, id_palabra_der;";//forma1
    QString consulta = "select * from relacion_izq_derpos order by id_palabra_izq, id_palabra_der;";//forma3
    query.prepare(consulta);
    query.exec();
    bool info = query.first();
    QSqlRecord rec = query.record();
    qDebug() << "recuperacion grande completa " << info;
    //vector<Palabra> palabras (88342);//forma1,93243 palabras en total me quedaron, tener cuidado con esto si hago modificaciones, los id de la base de datos son el id del vector +1
    vector<Palabra> palabras (68665);//forma3,93243 palabras en total me quedaron, tener cuidado con esto si hago modificaciones, los id de la base de datos son el id del vector +1
    //deberia trabajar con alotra tabla por que no todas la palabras tendra, vector seria estupido buscarlo, //88342
    for(long int i = 0; i < palabras.size(); i++){
        double res;
        long long int acumPP = 0;
        long long int acumMA = 0;
        long long int acumMB = 0;
        long int j = 0;
        while(info && rec.field(0).value().toLongLong()==i+1 ){/*lo anterior es el i<a.size() // && rec.field(0).value().toLongLong() < vPalabra[i].first){*/
            while(j < vPalabra.size() && vPalabra[j].first < rec.field(1).value().toLongLong()){//no diferente sino que sea menor
                acumMB += vPalabra[j].second * vPalabra[j].second;
                j = -~j;
            }
            if(j < vPalabra.size() && rec.field(1).value().toLongLong() == vPalabra[j].first){//si j es menor que size eso quiere decir que el bucle anterior paro por que encontro una igualdad por lo tanto procedo a acumular
                acumPP += rec.field(2).value().toLongLong() * vPalabra[j].second;
                acumMB += vPalabra[j].second * vPalabra[j].second;
                j = -~j; //incremento j, puesto que ya use este valor por lo tanto no es necesario incluirlo en la busqueda binaria, tener cuidao si la busqueda bianri me da mas que b.size()
            }
            acumMA += rec.field(2).value().toLongLong() * rec.field(2).value().toLongLong();
            info = query.next(); //i++
            rec = query.record();
        }
        while(j < vPalabra.size()){//no diferente sino que sea menor
            acumMB += vPalabra[j].second * vPalabra[j].second;
            j = -~j;
        }
        res = (double)acumPP / (sqrt(acumMA)*sqrt(acumMB));
        palabras[i].similaridad = res;
        palabras[i].indice = i+1;
        rec2 = query2.record();
        palabras[i].palabra = rec2.field(1).value().toString();
        //palabras[i].palabra = recuperarPalabraById(i+1);//no necesito hacer esto, como estoy usado las palabras de la tabal plabra 1 y alli ya estan ordenads solo debo recuperar eso y accedor con igualda a la posicion i
        //qDebug() << palabras[i].palabra;
        query2.next();
    }
    model = new ResultModel(this);
    model->setPalabras(palabras);
    ui->tableViewResults->setModel(model);
    ui->tableViewResults->resizeColumnsToContents();
    qDebug() << "Fin";
}
void Buscador::process2(QString palabra){
    vector<pair<long long int, long long int> > vPalabra = recuperarVectorByPalabra(palabra);
    if(!vPalabra.size()){//si la palabra no esta, no debo procesarla
        return;
    }
    qDebug() << vPalabra.size();
    QSqlQuery query2 (db);
    //QString consulta2 = "select * from palabra_izq order by id_palabra_izq;";//forma1, quiza solod deba retornal palabra
    QString consulta2 = "select * from palabra_izqpos order by id_palabra_izq;";//forma3, quiza solod deba retornal palabra
    query2.prepare(consulta2);
    query2.exec();
    qDebug() << query2.first();
    QSqlRecord rec2;// = query2.record();
    QSqlQuery query (db);
    //QString consulta = "select * from relacion_izq_der order by id_palabra_izq, id_palabra_der;";//forma1
    QString consulta = "select * from relacion_izq_derpos order by id_palabra_izq, id_palabra_der;";//forma3
    query.prepare(consulta);
    query.exec();
    bool info = query.first();
    QSqlRecord rec = query.record();
    qDebug() << "recuperacion grande completa " << info;
    //vector<Palabra> palabras (88342);//forma1,93243 palabras en total me quedaron, tener cuidado con esto si hago modificaciones, los id de la base de datos son el id del vector +1
    vector<Palabra> palabras (68665);//forma3,93243 palabras en total me quedaron, tener cuidado con esto si hago modificaciones, los id de la base de datos son el id del vector +1
    //deberia trabajar con alotra tabla por que no todas la palabras tendra, vector seria estupido buscarlo, //88342
    for(long int i = 0; i < palabras.size(); i++){
        vector<pair<long long int, long long int> > vec;//podria trbaajar recuperando la informacion de la forma1 en lugar de la forma2
        while(info && rec.field(0).value().toLongLong()==i+1){
            pair<long long int, long long int> par;
            par.first = rec.field(1).value().toLongLong();
            par.second = rec.field(2).value().toLongLong();
            vec.push_back(par);
            //vec.push_back(make_pair<long long int, long long int> (rec.field(1).value().toLongLong(), rec.field(2).value().toLongLong()));
            info = query.next();
            rec = query.record();
        }
        //qDebug() << i+1 << "vec.size(): " << vec.size();
        palabras[i].indice = i+1;
        rec2 = query2.record();
        palabras[i].palabra = rec2.field(1).value().toString();
        //palabras[i].palabra = recuperarPalabraById(i+1);//no necesito hacer esto, como estoy usado las palabras de la tabal plabra 1 y alli ya estan ordenads solo debo recuperar eso y accedor con igualda a la posicion i
        //qDebug() << palabras[i].palabra;
        palabras[i].similaridad = simcos2(vPalabra, vec);//parece que funcion mas rapido con simcos2, pero los resultados no son los mismos, investigar
        query2.next();
    }
    model = new ResultModel(this);
    model->setPalabras(palabras);
    ui->tableViewResults->setModel(model);
    ui->tableViewResults->resizeColumnsToContents();
    qDebug() << "Fin";
}

void Buscador::process(QString palabra)
{//quiza en lugar de retornar los ids y lafrecuencia tambien deberia retornar la palabra de la izquierda, para asociarla de una sola vez a  su repsectivo id, en lugar de hacer despues
    //quiza tambien deberia usar mi propia estructura para almacenar todos los datos pertinentes y amnejarlo en el modelo a base de if como hago ahora, solo que ya todo estaria en unn solo vector
    //cuando haga el proceso de frente, lo que debo un vector<Palabra> con al cantidad exacta de palabras1 algo de 82000 mientras voy procesando, voy llenado datos de la primera, y asi sucesivamente, luego recien buscar a quien le pertenece esos datos,
    vector<pair<long long int, long long int> > vPalabra = recuperarVectorByPalabra(palabra);
    if(!vPalabra.size()){//si la palabra no esta, no debo procesarla
        return;
    }
    qDebug() << vPalabra.size();
    //vector<Palabra> palabras (88342);//forma1,93243 palabras en total me quedaron, tener cuidado con esto si hago modificaciones, los id de la base de datos son el id del vector +1
    vector<Palabra> palabras (68665);//forma3,93243 palabras en total me quedaron, tener cuidado con esto si hago modificaciones, los id de la base de datos son el id del vector +1
    //deberia trabajar con alotra tabla por que no todas la palabras tendra, vector seria estupido buscarlo, //88342
    for(long int i = 0; i < palabras.size(); i++){
        vector<pair<long long int, long long int> > vec = recuperarVectorById(i+1);//podria trbaajar recuperando la informacion de la forma1 en lugar de la forma2
        //ids[i] = i;
        qDebug() << i+1;
        palabras[i].indice = i+1;
        palabras[i].palabra = recuperarPalabraById(i+1);
        //qDebug() << pa[i].palabra;
        palabras[i].similaridad = simcos2(vPalabra, vec);
    }
    model = new ResultModel(this);
    //model->setWords(palabras);
    model->setPalabras(palabras);
    //model->setIds(ids);
    //model->setSimilaridad(similaridad);
    ui->tableViewResults->setModel(model);
    ui->tableViewResults->resizeColumnsToContents();
}

void Buscador::process102(QString palabra)
{//quiza en lugar de retornar los ids y lafrecuencia tambien deberia retornar la palabra de la izquierda, para asociarla de una sola vez a  su repsectivo id, en lugar de hacer despues
    //quiza tambien deberia usar mi propia estructura para almacenar todos los datos pertinentes y amnejarlo en el modelo a base de if como hago ahora, solo que ya todo estaria en unn solo vector
    //cuando haga el proceso de frente, lo que debo un vector<Palabra> con al cantidad exacta de palabras1 algo de 82000 mientras voy procesando, voy llenado datos de la primera, y asi sucesivamente, luego recien buscar a quien le pertenece esos datos,
    vector<Palabra> palabras (10);//93243 palabras en total me quedaron, tener cuidado con esto si hago modificaciones, los id de la base de datos son el id del vector +1
    palabras[0].palabra = "god";
    palabras[1].palabra = "allah";
    palabras[2].palabra = "buddha";
    palabras[3].palabra = "lion";
    palabras[4].palabra = "tiger";
    palabras[5].palabra = "cat";
    palabras[6].palabra = "hamburger";
    palabras[7].palabra = "pizza";
    palabras[8].palabra = "pen";
    palabras[9].palabra = "notebook";
    //recuperar la palabra que busco y procesarla contra todas las palabras
    vector<pair<long long int, double> > vPalabra = recuperarVectorByPalabra2(palabra);
    if(!vPalabra.size()){//si la palabra no esta, no debo procesarla
        return;
    }
    qDebug() << vPalabra.size();
    for(long int i = 0; i < palabras.size(); i++){
        vector<pair<long long int, double> > vec = recuperarVectorByPalabra2(palabras[i].palabra);//podria trbaajar recuperando la informacion de la forma1 en lugar de la forma2
        qDebug() << i+1;
        palabras[i].indice = recuperarIdByPalabra(palabras[i].palabra).toLongLong();
        //qDebug() << pa[i].palabra;
        palabras[i].similaridad = simcos2d(vPalabra, vec);
    }
    model = new ResultModel(this);
    model->setPalabras(palabras);
    ui->tableViewResults->setModel(model);
    ui->tableViewResults->resizeColumnsToContents();
}
void Buscador::process10(QString palabra)
{//quiza en lugar de retornar los ids y lafrecuencia tambien deberia retornar la palabra de la izquierda, para asociarla de una sola vez a  su repsectivo id, en lugar de hacer despues
    //quiza tambien deberia usar mi propia estructura para almacenar todos los datos pertinentes y amnejarlo en el modelo a base de if como hago ahora, solo que ya todo estaria en unn solo vector
    //cuando haga el proceso de frente, lo que debo un vector<Palabra> con al cantidad exacta de palabras1 algo de 82000 mientras voy procesando, voy llenado datos de la primera, y asi sucesivamente, luego recien buscar a quien le pertenece esos datos,
    vector<Palabra> palabras (10);//93243 palabras en total me quedaron, tener cuidado con esto si hago modificaciones, los id de la base de datos son el id del vector +1
    palabras[0].palabra = "god";
    palabras[1].palabra = "allah";
    palabras[2].palabra = "buddha";
    palabras[3].palabra = "lion";
    palabras[4].palabra = "tiger";
    palabras[5].palabra = "cat";
    palabras[6].palabra = "hamburger";
    palabras[7].palabra = "pizza";
    palabras[8].palabra = "pen";
    palabras[9].palabra = "notebook";
    //recuperar la palabra que busco y procesarla contra todas las palabras
    vector<pair<long long int, long long int> > vPalabra = recuperarVectorByPalabra(palabra);
    if(!vPalabra.size()){//si la palabra no esta, no debo procesarla
        return;
    }
    qDebug() << vPalabra.size();
    for(long int i = 0; i < palabras.size(); i++){
        vector<pair<long long int, long long int> > vec = recuperarVectorByPalabra(palabras[i].palabra);//podria trbaajar recuperando la informacion de la forma1 en lugar de la forma2
        qDebug() << i+1;
        palabras[i].indice = recuperarIdByPalabra(palabras[i].palabra).toLongLong();
        //qDebug() << pa[i].palabra;
        palabras[i].similaridad = simcos2(vPalabra, vec);
    }
    model = new ResultModel(this);
    model->setPalabras(palabras);
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
    process102(word);//debo asegurarme que la palabra exista antes de mandar a procesar todo o fallara esta cosa
}

void Buscador::on_pushButton_clicked()
{

}
