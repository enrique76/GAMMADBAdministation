#include "inserdata.h"

inserData::inserData(){

    // mombre

    this->nombre->setText("NOMBRE");

    QStringList l;

    l << "INTEGER" << "TEXT" << "BLOB" << "REAL" << "NUMERIC";


    // tipos de datos
    this->type->addItems(l);

    l.clear();

    l << " " <<"BINARY" << "NOCASE" << "RTRIM" << "UTF16" << "UTF16CI";


    // collation
    this->CO->addItems(l);
}

void inserData::setTablas(QStringList l){
    this->FY->addItems(l);
}

QWidget *inserData::getW1(){
    return this->nombre;
}

QWidget *inserData::getW2(){
    return this->type;
}

QWidget *inserData::getW3(){
    return this->NN;
}

QWidget *inserData::getW4(){
    return this->PK;
}

QWidget *inserData::getW5(){
    return this->AI;
}

QWidget *inserData::getW6(){
    return this->U;
}

QWidget *inserData::getW7(){
    return this->DE;
}

QWidget *inserData::getW8(){
    return this->CH;
}

QWidget *inserData::getW9(){
    return this->CO;
}

QWidget *inserData::getW10(){
    return this->FY;
}

QString inserData::getData1(){
    return this->nombre->text();
}

QString inserData::getData2(){
    return this->type->currentText();
}

bool inserData::getData3(){
    return this->NN->isChecked();
}

bool inserData::getData4(){
    return this->PK->isChecked();
}

bool inserData::getData5(){
    return this->AI->isChecked();
}

bool inserData::getData6(){
    return this->U->isChecked();
}

QString inserData::getData7(){
    return this->DE->text();
}

QString inserData::getData8(){
    return this->CH->text();
}

QString inserData::getData9(){
    return this->CO->currentText();
}

QString inserData::getData10(){
    return this->FY->currentText();
}

QString inserData::getLine(){
    QString t = "";

    // nombre
    t += this->nombre->text() + " \t ";

    // tipo de dato

    t += this->type->currentText() + " \t ";

    // NOT NULL

    if(this->NN->isChecked()){
        t += "NOT NULL \t";
    }

    // Primary key

    // AutoIncrement

    if(this->AI->isChecked()){
        t += "AUTOINCREMENT \t";
    }

    // Unique

    if(this->U->isChecked()){
        t += "UNIQUE \t";
    }

    // Default

    if(!this->DE->text().isEmpty()){
        t += "DEFAULT '" + this->DE->text()+"' \t";
    }

    // CHEck

    if(!this->CH->text().isEmpty()){
        t += "CHECK("+this->CH->text()+") \t";
    }

    // COLLAtion

    if(this->CO->currentIndex() != 0){
        t += "COLLATE "+this->CO->currentText();
    }

    t += ",";

    return t;
}













