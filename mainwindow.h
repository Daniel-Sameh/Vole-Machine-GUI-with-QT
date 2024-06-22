#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"volemachine.h"
#include <QStandardItem>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setupProgramCounter();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    machine myMachine;
    QStandardItemModel *memoryModel;
    QStandardItemModel *memoryModel2;
    QStandardItemModel *memoryModel3;
private slots:
    void displayMemory();
    void displayRegister();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void setInstructionTable();
    void showMessage(const QString& message);
};
#endif // MAINWINDOW_H
