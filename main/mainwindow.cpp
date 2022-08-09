#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QFileDialog>
#include<QFile>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QTextStream>
#include"open_save.h"
#include"crear.h"
#include<QCheckBox>
#include<QTextCursor>
#include<QStringListModel>
#include<QCompleter>
#include<QGuiApplication>
#include<QByteArray>
#include<QCursor>
#include"inserdata.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) , ui(new Ui::MainWindow){
    ui->setupUi(this);

    // barra lateral

    ui->barraLateral->setVisible(false);
    ui->areaconfig->setVisible(false);

    // desconectar

    ui->actionDesconectar->setEnabled(false);

    // area

    ui->area->setCurrentIndex(0);

    // query action

    ui->actionQuery->setEnabled(false);

    // QTreeWidgetItem

    //topA = new QTreeWidgetItem();
    topA->setText(0,"DataBase");
    topA->setIcon(0,QIcon(":/new/prefix1/iconos/database.png"));

    ui->arbol->addTopLevelItem(this->topA);
    ui->arbol->expandItem(this->topA);

    // CREAR TABLA ACCTION

    ui->actionCrear_Tabla->setEnabled(false);

    // manual query

//    QTextCursor *completerQuerys = new QTextCursor();

//    completerQuerys->insertText("SELECT ");

    //completingTextEdit->setTextCursor(*completerQuerys);

        // completing code

    completingTextEdit = new TextEdit;
    completer = new QCompleter(this);
    completer->setModel(modelFromFile("qrc:/new/prefix1/palabras.txt"));
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);
    completingTextEdit->setCompleter(completer);

//    ui->stackedWidget->addWidget(completingTextEdit);
//    ui->stackedWidget->setCurrentIndex(0);

    //ui->manualQuery->setParent(completingTextEdit);

    ui->areaManualQuery->addWidget(completingTextEdit);



//    QStringList l;

//    l << "SELECT" << "FROM";

//    QCompleter *co = new QCompleter(l);

//    co->setWidget(ui->textEdit);

}

QAbstractItemModel *MainWindow::modelFromFile(const QString& fileName)
{
    qDebug()<<"Simon";
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
        return new QStringListModel(completer);

#ifndef QT_NO_CURSOR
    QGuiApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif
    QStringList words;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if (!line.isEmpty())
            words << QString::fromUtf8(line.trimmed());
    }

#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif



    return new QStringListModel(words, completer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionBara_de_Herramientas_triggered(){
    ui->barraLateral->setVisible(!ui->barraLateral->isVisible());
}

void MainWindow::on_actionCrear_DB_triggered()
{
    ui->areaconfig->setVisible(true);

    ui->areaconfig->setCurrentIndex(1);
}

void MainWindow::on_pushButton_clicked(){

    if(ui->rutaCrearDB->text().isEmpty() || ui->NombreCrearDB->text().isEmpty()){
        QMessageBox::critical(this,"Crear DataBase","Acomplete Todos Los Campos");
    }
    else{
        QMessageBox::StandardButton reply;
        QMessageBox messageBox;

          reply = messageBox.question(this, "Crear DataBase", "Quieres Crear esta DataBase " + ui->NombreCrearDB->text() +"?",  QMessageBox::Yes | QMessageBox::No);
          if (reply == QMessageBox::Yes){

              if(ui->conectarCrearDB->isChecked()){
                  ConectarDB(ui->motorCrearDB->currentIndex());

                  ui->actionQuery->setEnabled(true);
              }



            ui->area->setCurrentIndex(0);
            ui->actionCrear_Tabla->setEnabled(true);
            ui->actionQuery->setEnabled(true);
          }
    }


}

void MainWindow::on_BuscarrutaCrearDB_clicked(){
    QString ruta = QFileDialog::getExistingDirectory(this,"Guardar DataBase",QDir::homePath());
    ui->rutaCrearDB->setText(ruta);
}

void MainWindow::ConectarDB(int i){
    if(i == 0){
        //db.addDatabase("QSQLITE");
    }

    this->ruta = ui->rutaCrearDB->text()+"/"+ui->NombreCrearDB->text()+".db";

    ui->estado->setText(ui->NombreCrearDB->text());

    QFile a(this->ruta);

    a.open(QFile::WriteOnly | QFile::Text);

    if(a.exists()){



        db.setDatabaseName(this->ruta);

        if(!db.open()){
            QMessageBox::critical(this,"Conectar DataBase",db.lastError().text());
        }
    }
    else{
        QMessageBox::critical(this,"Crear DataBase","No se Creo La DataBase");
    }

    a.flush();
    a.close();

    QTreeWidgetItem * it = new QTreeWidgetItem(this->topA);

    it->setText(0,ui->NombreCrearDB->text());
    it->setIcon(0,QIcon(":/new/prefix1/iconos/R.png"));




    this->a.push_back(it);

}

void MainWindow::on_actionConectar_triggered(){
    ui->areaconfig->setVisible(true);

    ui->areaconfig->setCurrentIndex(0);

    ui->barraLateral->setVisible(true);

}

void MainWindow::on_buscarrutaConectarDataBase_clicked(){
    QString filter = " .db File (*.db)";

    QString ruta = QFileDialog::getOpenFileName(this,"Abrir DataBase",QDir::homePath(),filter);
    ui->rutaConectarDataBase->setText(ruta);
}

void MainWindow::on_AceptarConectar_clicked(){
    if(ui->rutaConectarDataBase->text().isEmpty()){
        QMessageBox::critical(this,"Abrir DataBase","Acomplete Todos Los Campos");
    }
    else{
        QMessageBox::StandardButton reply;
        QMessageBox messageBox;

          reply = messageBox.question(this, "Abrir DataBase", "Si Abre esta base de datos, se descanectara de la anterior, desea hacerlo?",  QMessageBox::Yes | QMessageBox::No);
          if (reply == QMessageBox::Yes){

              db.removeDatabase(this->ruta);

              this->ruta = ui->rutaConectarDataBase->text();

              db.setDatabaseName(this->ruta);

              QStringList n = this->ruta.split("/");

              ui->estado->setText(n.at(n.size()-1));

              if(!db.open()){
                  QMessageBox::critical(this,"Conectar DataBase",db.lastError().text());
              }



            //ui->area->setCurrentIndex(0);

            ui->actionQuery->setEnabled(true);


            ui->barraLateral->setVisible(true);

            QString t = "SELECT name FROM sqlite_master WHERE type = 'table';";

            QSqlQuery *q = new QSqlQuery(this->db);

            q->prepare(t);
            q->exec();

            QSqlQueryModel *data = new QSqlQueryModel();

            data->setQuery(*q);

            for(int i=1;i<data->rowCount();i++){
                QTreeWidgetItem *it = new QTreeWidgetItem(this->topA);

                it->setText(0,data->index(i,0).data().toString());
                it->setIcon(0,QIcon(":/new/prefix1/iconos/tabla.png"));





                this->topA->addChild(it);
                //ui->arbol->addTopLevelItem(this->topA);

                this->a.push_back(it);

                crear *c = new crear();

                c->setData("Select * From "+data->index(i,0).data().toString()+";",this->db);

                ui->view->addTab(c,data->index(i,0).data().toString());
                //ui->view->setCurrentIndex(ui->view->currentIndex()+1);
            }
          }

          ui->areaconfig->setVisible(false);
          ui->actionCrear_Tabla->setEnabled(true);
          ui->actionQuery->setEnabled(true);

          // dar valores a descripccion

          QString t = "SELECT name from sqlite_master where type='table';";

          QSqlQuery *q = new QSqlQuery(this->db);

         q->prepare(t);

         q->exec();

         QSqlQueryModel *data = new QSqlQueryModel();

         data->setQuery(*q);

         for(int i=0;i<data->rowCount();i++){
             ui->tablasInformacion->addItem(data->index(i,0).data().toString());
         }

    }
}


void MainWindow::on_actionQuery_triggered(){
    ui->area->setCurrentIndex(2);

    // from

    QString qTablas = "SELECT name from sqlite_master where type='table';";

    QSqlQuery *q = new QSqlQuery(this->db);

    q->prepare(qTablas);


    q->exec();

    QSqlQueryModel *data = new QSqlQueryModel();

    data->setQuery(*q);


    for(int i=1;i<data->rowCount();i++){
        ui->autoFrom->addItem(data->index(i,0).data().toString());
    }



}

void MainWindow::on_autoFrom_currentIndexChanged(int index){

}


void MainWindow::on_autoFrom_editTextChanged(const QString &arg1)
{

    qDebug()<<arg1;


}


void MainWindow::on_autoFrom_currentTextChanged(const QString &arg1)
{
    QSqlQuery *q = new QSqlQuery(this->db);

   q->prepare("pragma table_info("+ui->autoFrom->currentText()+")");

   q->exec();

   QSqlQueryModel *data = new QSqlQueryModel();

   data->setQuery(*q);

//    for(int i=0;i<ui->autoOrden->count();i++){
//        ui->autoOrden->removeItem(i);
//    }

   ui->autoOrden->clear();


   for(int i=0;i<data->rowCount();i++){
       ui->autoOrden->addItem(data->index(i,1).data().toString());
       ui->autoWhere_2->addItem(data->index(i,1).data().toString());
   }
}


void MainWindow::on_autolRun_clicked(){
    if(!ui->autoSelect->text().isEmpty() || !ui->autoWhere->text().isEmpty()){
        QString t = "SELECT " +ui->autoSelect->text() + " FROM " + ui->autoFrom->currentText();

        if(!ui->autoWhere->text().isEmpty()){
           t += " WHERE " + ui->autoWhere_2->currentText() + " = " + ui->autoWhere->text();
        }

        t+= " ORDER BY " + ui->autoOrden->currentText();

        if(ui->autoAD->currentIndex() == 0 ){
            t += " ASC";
        }
        else{
            t += " DESC";
        }

        QSqlQuery *q = new QSqlQuery(this->db);

       q->prepare(t);

       q->exec();

       QSqlQueryModel *data = new QSqlQueryModel();

       data->setQuery(*q);

       ui->viewData->setModel(data);

       ui->countColumnas->setText(QString::number(data->columnCount()));
       ui->countFilas->setText(QString::number(data->rowCount()));
    }
}

void MainWindow::on_manualRun_clicked(){
    QSqlQuery *q = new QSqlQuery(this->db);

   q->prepare(completingTextEdit->toPlainText());

   q->exec();

   QSqlQueryModel *data = new QSqlQueryModel();

   data->setQuery(*q);

   ui->viewData->setModel(data);

   ui->countColumnas->setText(QString::number(data->columnCount()));
   ui->countFilas->setText(QString::number(data->rowCount()));
}


void MainWindow::on_pushButton_3_clicked(){
    open_save *os = new open_save();

    os->setArea(0);

    os->setWindowTitle("Abrir Query");

    os->setWindowIcon(ui->pushButton_3->icon());

    os->Estado(ui->pushButton_3->text());

    os->exec();

    QString ruta = os->getRuta();

    QFile a(ruta);

    a.open(QFile::ReadOnly | QFile::Text);

    if(a.exists()){

        QTextStream in(&a);


        QString t = in.readAll();

        completingTextEdit->setPlainText(t);

        a.flush();
        a.close();
    }
    else{
        QMessageBox::critical(this,"Abrir Query","Query no encontrado");
    }


}


void MainWindow::on_saveQuerySQL_clicked(){
    open_save *os = new open_save();

    os->setArea(1);

    os->setWindowTitle("Guardar Query");

    os->setWindowIcon(ui->saveQuerySQL->icon());

    os->setExtension(".sql");

    os->exec();

    QString ruta = os->getRuta();

    QFile a(ruta);

    a.open(QFile::WriteOnly | QFile::Text);

    if(a.exists()){
         QTextStream out(&a);

         QString t = completingTextEdit->toPlainText();

         out << t;

         a.flush();
         a.close();
    }
}


void MainWindow::on_saveQuerytxt_clicked(){
    open_save *os = new open_save();

    os->setArea(1);

    os->setWindowTitle("Guardar Query");

    os->setWindowIcon(ui->saveQuerySQL->icon());

    os->setExtension(".txt");

    os->exec();

    QString ruta = os->getRuta();

    QFile a(ruta);

    a.open(QFile::WriteOnly | QFile::Text);

    if(a.exists()){
         QTextStream out(&a);

         QString t = completingTextEdit->toPlainText();

         out << t;

         a.flush();
         a.close();
    }
}


void MainWindow::on_autoSaveQuerySql_clicked(){
    open_save *os = new open_save();

    os->setArea(1);

    os->setWindowTitle("Guardar Query");

    os->setWindowIcon(ui->saveQuerySQL->icon());

    os->setExtension(".sql");

    os->exec();

    QString ruta = os->getRuta();

    QFile a(ruta);

    a.open(QFile::WriteOnly | QFile::Text);

    if(a.exists()){
         QTextStream out(&a);

          QString t = "SELECT " +ui->autoSelect->text() + " FROM " + ui->autoFrom->currentText();

         if(!ui->autoWhere->text().isEmpty()){
            t += " WHERE " + ui->autoWhere_2->currentText() + " = " + ui->autoWhere->text();
         }

         t+= " ORDER BY " + ui->autoOrden->currentText();

         if(ui->autoAD->currentIndex() == 0 ){
             t += " ASC";
         }
         else{
             t += " DESC";
         }

         out << t;

         a.flush();
         a.close();
    }
}


void MainWindow::on_autoSaveQueryTxt_clicked()
{
    open_save *os = new open_save();

    os->setArea(1);

    os->setWindowTitle("Guardar Query");

    os->setWindowIcon(ui->saveQuerySQL->icon());

    os->setExtension(".txt");

    os->exec();

    QString ruta = os->getRuta();

    QFile a(ruta);

    a.open(QFile::WriteOnly | QFile::Text);

    if(a.exists()){
         QTextStream out(&a);

          QString t = "SELECT " +ui->autoSelect->text() + " FROM " + ui->autoFrom->currentText();

         if(!ui->autoWhere->text().isEmpty()){
            t += " WHERE " + ui->autoWhere_2->currentText() + " = " + ui->autoWhere->text();
         }

         t+= " ORDER BY " + ui->autoOrden->currentText();

         if(ui->autoAD->currentIndex() == 0 ){
             t += " ASC";
         }
         else{
             t += " DESC";
         }

         out << t;

         a.flush();
         a.close();
    }
}


void MainWindow::on_savescv_clicked(){
    open_save *os = new open_save();

    os->setArea(1);

    os->setWindowTitle("Guardar Query");

    os->setWindowIcon(ui->saveQuerySQL->icon());

    os->setExtension(".csv");

    os->exec();

    QString ruta = os->getRuta();

    QFile a(ruta);

    a.open(QFile::WriteOnly | QFile::Text);

    if(a.exists()){
         QTextStream out(&a);

         QString t;

         for(int i=0;i<ui->viewData->model()->rowCount();i++){
             for(int j=0;j<ui->viewData->model()->columnCount();j++){
                 t += ui->viewData->model()->index(i,j).data().toString();
             }
             t+="\n";
             out<<t;
         }

         a.flush();
         a.close();
    }
}


void MainWindow::on_Savetxt_clicked(){
    open_save *os = new open_save();

    os->setArea(1);

    os->setWindowTitle("Guardar Query");

    os->setWindowIcon(ui->saveQuerySQL->icon());

    os->setExtension(".txt");

    os->exec();

    QString ruta = os->getRuta();

    QFile a(ruta);

    a.open(QFile::WriteOnly | QFile::Text);

    if(a.exists()){
         QTextStream out(&a);

         QString t;



         for(int i=0;i<ui->viewData->model()->rowCount();i++){
             for(int j=0;j<ui->viewData->model()->columnCount();j++){
                 t += ui->viewData->model()->index(i,j).data().toString()+", ";
             }
             t+="\n";
             out<<t;
             t.clear();
         }

         a.flush();
         a.close();
    }
}


void MainWindow::on_arbol_itemDoubleClicked(QTreeWidgetItem *item, int column){
    if(item->text(0) != "DataBase"){
        ui->area->setCurrentIndex(0);
        ui->view->setCurrentIndex(this->topA->indexOfChild(item));
    }
}


void MainWindow::on_actionBarra_de_Configuraciones_triggered()
{
    ui->areaconfig->setVisible(!ui->areaconfig->isVisible());
}


void MainWindow::on_actionCrear_Tabla_triggered()
{
    ui->area->setCurrentIndex(1);
}


void MainWindow::on_pushButton_5_clicked(){
    ui->datosCrearTabla->setRowCount(ui->datosCrearTabla->rowCount()+1);

    inserData *id = new inserData();

    QStringList l;

    QString qTablas = "SELECT name from sqlite_master where type='table';";

    QSqlQuery *q = new QSqlQuery(this->db);

    q->prepare(qTablas);


    q->exec();

    QSqlQueryModel *data = new QSqlQueryModel();

    data->setQuery(*q);




    for(int i=0;i<data->rowCount();i++){
        l << data->index(i,0).data().toString();
    }

    id->setTablas(l);

    ui->datosCrearTabla->setCellWidget(ui->datosCrearTabla->rowCount()-1,0,id->getW1());
    ui->datosCrearTabla->setCellWidget(ui->datosCrearTabla->rowCount()-1,1,id->getW2());
    ui->datosCrearTabla->setCellWidget(ui->datosCrearTabla->rowCount()-1,2,id->getW3());
    ui->datosCrearTabla->setCellWidget(ui->datosCrearTabla->rowCount()-1,3,id->getW4());
    ui->datosCrearTabla->setCellWidget(ui->datosCrearTabla->rowCount()-1,4,id->getW5());
    ui->datosCrearTabla->setCellWidget(ui->datosCrearTabla->rowCount()-1,5,id->getW6());
    ui->datosCrearTabla->setCellWidget(ui->datosCrearTabla->rowCount()-1,6,id->getW7());
    ui->datosCrearTabla->setCellWidget(ui->datosCrearTabla->rowCount()-1,7,id->getW8());
    ui->datosCrearTabla->setCellWidget(ui->datosCrearTabla->rowCount()-1,8,id->getW9());
    ui->datosCrearTabla->setCellWidget(ui->datosCrearTabla->rowCount()-1,9,id->getW10());

    this->idALL.push_back(id);
    //qDebug()<<id->getLine();
}

void MainWindow::on_actionAgregar_triggered(){
    ui->areaconfig->setVisible(true);
    ui->areaconfig->setCurrentIndex(2);
}


void MainWindow::on_actionModificar_triggered()
{
    ui->areaconfig->setVisible(true);
    ui->areaconfig->setCurrentIndex(3);
}


void MainWindow::on_actionEliminar_triggered()
{
    ui->areaconfig->setVisible(true);
    ui->areaconfig->setCurrentIndex(4);
}


void MainWindow::on_actionDescripccion_triggered()
{
    ui->areaconfig->setVisible(true);
    ui->areaconfig->setCurrentIndex(5);


    QSqlQuery *q = new QSqlQuery(this->db);

   q->prepare("pragma table_info("+ui->tablasInformacion->currentText()+");");

   q->exec();

   QSqlQueryModel *data = new QSqlQueryModel();

   data->setQuery(*q);

   ui->viewDescripccion->setModel(data);


}


void MainWindow::on_modificarTV_currentIndexChanged(int index)
{
    ui->areaModificar->setCurrentIndex(index);
}


void MainWindow::on_tablasInformacion_activated(int index)
{
    QSqlQuery *q = new QSqlQuery(this->db);

   q->prepare("pragma table_info("+ui->tablasInformacion->currentText()+");");

   q->exec();

   QSqlQueryModel *data = new QSqlQueryModel();

   data->setQuery(*q);

   ui->viewDescripccion->setModel(data);
}


void MainWindow::on_areaconfig_currentChanged(int index)
{

    if(index == 5){
        QSqlQuery *q = new QSqlQuery(this->db);

       q->prepare("pragma table_info("+ui->tablasInformacion->currentText()+");");

       q->exec();

       QSqlQueryModel *data = new QSqlQueryModel();

       data->setQuery(*q);

       ui->viewDescripccion->setModel(data);
    }


}


void MainWindow::on_guardarCsvDescripccion_clicked(){
    open_save *os = new open_save();

    os->setArea(1);

    os->setWindowTitle("Guardar Query");

    os->setWindowIcon(ui->saveQuerySQL->icon());

    os->setExtension(".csv");

    os->exec();

    QString ruta = os->getRuta();

    QFile a(ruta);

    a.open(QFile::WriteOnly | QFile::Text);

    if(a.exists()){
         QTextStream out(&a);

         QString t;

         for(int i=0;i<ui->viewDescripccion->model()->rowCount();i++){
             for(int j=0;j<ui->viewDescripccion->model()->columnCount();j++){
                 t += ui->viewDescripccion->model()->index(i,j).data().toString();
             }
             t+="\n";
             out<<t;
         }

         a.flush();
         a.close();
    }
}

void MainWindow::on_guardarTxtDescripccion_clicked(){
    open_save *os = new open_save();

    os->setArea(1);

    os->setWindowTitle("Guardar Query");

    os->setWindowIcon(ui->saveQuerySQL->icon());

    os->setExtension(".txt");

    os->exec();

    QString ruta = os->getRuta();

    QFile a(ruta);

    a.open(QFile::WriteOnly | QFile::Text);

    if(a.exists()){
         QTextStream out(&a);

         QString t;



         for(int i=0;i<ui->viewDescripccion->model()->rowCount();i++){
             for(int j=0;j<ui->viewDescripccion->model()->columnCount();j++){
                 t += ui->viewDescripccion->model()->index(i,j).data().toString()+", ";
             }
             t+="\n";
             out<<t;
             t.clear();
         }

         a.flush();
         a.close();
    }
}


void MainWindow::on_pushButton_9_clicked(){
    for(int i=0;i<idALL.size();i++){
        qDebug()<<idALL.at(i)->getLine();
    }

    // Guardar Query

    QMessageBox::StandardButton reply;
    QMessageBox messageBox;

      reply = messageBox.question(this, "Creando Tabla", "Desea Guardar el Query",  QMessageBox::Yes | QMessageBox::No);
      if (reply == QMessageBox::Yes){
          QString ruta = QFileDialog::getExistingDirectory(this,"Guardar Query",QDir::homePath());
      }
}

