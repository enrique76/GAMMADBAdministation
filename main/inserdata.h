#ifndef INSERDATA_H
#define INSERDATA_H

#include <QObject>
#include<QLineEdit>
#include<QComboBox>
#include<QCheckBox>

class inserData{
    public:
        inserData();
        void setTablas(QStringList);
        QWidget *getW1();
        QWidget *getW2();
        QWidget *getW3();
        QWidget *getW4();
        QWidget *getW5();
        QWidget *getW6();
        QWidget *getW7();
        QWidget *getW8();
        QWidget *getW9();
        QWidget *getW10();
        QString getData1();
        QString getData2();
        bool getData3();
        bool getData4();
        bool getData5();
        bool getData6();
        QString getData7();
        QString getData8();
        QString getData9();
        QString getData10();

        QString getLine();
    private:
        QLineEdit *nombre = new QLineEdit();
        QComboBox *type = new QComboBox();
        QCheckBox *NN = new QCheckBox();
        QCheckBox *PK = new QCheckBox();
        QCheckBox *AI = new QCheckBox();
        QCheckBox *U  = new QCheckBox();
        QLineEdit *DE = new QLineEdit();
        QLineEdit *CH = new QLineEdit();
        QComboBox *CO = new QComboBox();
        QComboBox *FY = new QComboBox();
        QStringList Tablas;
};

#endif // INSERDATA_H
