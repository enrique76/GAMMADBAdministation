#ifndef CREAR_H
#define CREAR_H

#include <QWidget>
#include<QSqlDatabase>
#include<QSqlError>
#include<QSqlQuery>

namespace Ui {
class crear;
}

class crear : public QWidget
{
    Q_OBJECT

public:
    explicit crear(QWidget *parent = nullptr);
    ~crear();
    void setData(QString,QSqlDatabase);

private:
    Ui::crear *ui;
};

#endif // CREAR_H
