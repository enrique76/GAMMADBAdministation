#include "open_save.h"
#include "ui_open_save.h"
#include<QFileDialog>

open_save::open_save(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::open_save)
{
    ui->setupUi(this);
}

open_save::~open_save()
{
    delete ui;
}

void open_save::Estado(QString t){
    this->estado = t;
}

QString open_save::getRuta()
{
    return this->ruta;
}

void open_save::setArea(int i){
    ui->area->setCurrentIndex(i);
}

void open_save::setExtension(QString t)
{
    ui->extension->setText(t);
}

void open_save::on_pushButton_clicked(){
    if(this->estado == "Abrir Query"){
        QString filter = " SQL File (*.sql)";

        QString ruta = QFileDialog::getOpenFileName(this,"Abrir Query",QDir::homePath(),filter);

        ui->lineEdit->setText(ruta);
    }
}


void open_save::on_buttonBox_accepted(){
    this->ruta = ui->lineEdit->text();

    close();
}


void open_save::on_BuscarrutaGuardar_clicked(){
    QString ruta = QFileDialog::getExistingDirectory(this,"Guardar",QDir::homePath());

    ui->rutaGuardar->setText(ruta+"/");
}


void open_save::on_guardar_clicked(){
    this->ruta = ui->rutaGuardar->text()+ui->extension->text();

    close();
}

