#ifndef OPEN_SAVE_H
#define OPEN_SAVE_H

#include <QDialog>

namespace Ui {
class open_save;
}

class open_save : public QDialog
{
    Q_OBJECT

public:
    explicit open_save(QWidget *parent = nullptr);
    ~open_save();
    void Estado(QString);
    QString getRuta();
    void setArea(int);
    void setExtension(QString);

private slots:
    void on_pushButton_clicked();

    void on_buttonBox_accepted();

    void on_BuscarrutaGuardar_clicked();

    void on_guardar_clicked();

private:
    Ui::open_save *ui;
    QString estado;
    QString ruta;
};

#endif // OPEN_SAVE_H
