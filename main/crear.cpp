#include "crear.h"
#include "ui_crear.h"
#include<QSqlQuery>
#include<QSqlQueryModel>

crear::crear(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::crear)
{
    ui->setupUi(this);
}

crear::~crear()
{
    delete ui;
}

void crear::setData(QString t,QSqlDatabase db){
    QSqlQuery *q = new QSqlQuery(db);

    q->prepare(t);

    q->exec();

    QSqlQueryModel *data = new QSqlQueryModel();

    data->setQuery(*q);

    ui->tableView->setModel(data);

    ui->columnas->setText(QString::number(data->columnCount()));
    ui->filas->setText(QString::number(data->rowCount()));

}
