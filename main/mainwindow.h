#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSqlDatabase>
#include<QSqlError>
#include<QSqlQuery>
#include<QCompleter>
#include<QSqlQueryModel>
#include<QtSql>
#include<QTreeWidgetItem>
#include"textedit.h"
#include"inserdata.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;

}

class QAbstractItemModel;
class QCompleter;
QT_END_NAMESPACE

class TextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionBara_de_Herramientas_triggered();

    void on_actionCrear_DB_triggered();

    void on_pushButton_clicked();

    void on_BuscarrutaCrearDB_clicked();

    void ConectarDB(int);

    void on_actionConectar_triggered();

    void on_buscarrutaConectarDataBase_clicked();

    void on_AceptarConectar_clicked();

    void on_actionQuery_triggered();

    void on_autoFrom_currentIndexChanged(int index);

    void on_autoFrom_editTextChanged(const QString &arg1);

    void on_autoFrom_currentTextChanged(const QString &arg1);

    void on_autolRun_clicked();

    void on_manualRun_clicked();

    void on_pushButton_3_clicked();

    void on_saveQuerySQL_clicked();

    void on_saveQuerytxt_clicked();

    void on_autoSaveQuerySql_clicked();

    void on_autoSaveQueryTxt_clicked();

    void on_savescv_clicked();

    void on_Savetxt_clicked();

    void on_arbol_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_actionBarra_de_Configuraciones_triggered();

    void on_actionCrear_Tabla_triggered();

    void on_pushButton_5_clicked();


    void on_actionAgregar_triggered();

    void on_actionModificar_triggered();

    void on_actionEliminar_triggered();

    void on_actionDescripccion_triggered();

    void on_modificarTV_currentIndexChanged(int index);


    void on_tablasInformacion_activated(int index);

    void on_areaconfig_currentChanged(int index);

    void on_guardarCsvDescripccion_clicked();

    void on_guardarTxtDescripccion_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString ruta;
    QVector<QTreeWidgetItem *> a;
    QTreeWidgetItem *topA = new QTreeWidgetItem();
    int rowSelection;
    QAbstractItemModel *modelFromFile(const QString& fileName);

    QCompleter *completer = nullptr;
    TextEdit *completingTextEdit;
    QVector<inserData *> idALL;
};
#endif // MAINWINDOW_H
