#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<bits/stdc++.h>
#include<QString>
#include<QInputDialog>
#include<QTextStream>
#include<string>
#include<vector>
#include <QPixmap>
#include <QMessageBox>
#include<QImageReader>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap background("D:/FCAI past semester/Level 2 Term 1/OOP (Object Oriented Programming)/3147823.png");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);

    setupProgramCounter();
    //    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    memoryModel = new QStandardItemModel(this);
    ui->tableView->setModel(memoryModel);
    memoryModel2 = new QStandardItemModel(this);
    ui->tableView2->setModel(memoryModel2);

    memoryModel3 = new QStandardItemModel(this);
    ui->tableView3->setModel(memoryModel3);
    ui->tableView3->setColumnWidth(0, 390);
    ui->tableView3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    QLinearGradient gradient(0, 0, 0, height());
    gradient.setColorAt(0, QColor(131, 191, 240));
    gradient.setColorAt(1, QColor(0, 0, 80));
    //gradient.setColorAt(1,QColor(100,20,100));
   // QPalette palette;
    //palette.setBrush(QPalette::Window, QBrush(gradient));
    //this->setPalette(palette);

    //QPalette palette2 = ui->tableView->palette();
    //palette2.setColor(QPalette::Base, QColor("#917df5"));  // Set your desired color
    //ui->tableView->setPalette(palette2);
    //palette2.setColor(QPalette::AlternateBase, QColor("#A0A0A0"));  // Set another color
    //ui->tableView->setPalette(palette2);

    displayMemory();
    displayRegister();
    setInstructionTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    QString programInput = ui->lineEdit->text();


    std::string word = programInput.toStdString();


    myMachine.inputIntoMemory(word);


    ui->lineEdit->clear();
    displayMemory();
    displayRegister();

}

void MainWindow::displayMemory()
{
    //myMachine.displayMemory();
    memoryModel->clear();
    memoryModel->setHorizontalHeaderLabels(QStringList() << "Address" << "Content");

    for (auto it = myMachine.machineMemory.memoryData.begin(); it != myMachine.machineMemory.memoryData.end(); ++it) {
        QList<QStandardItem *> rowItems;
        rowItems << new QStandardItem(QString::fromStdString(it->first))
                 << new QStandardItem(QString::fromStdString(it->second));
        memoryModel->appendRow(rowItems);
    }
    //for (auto it = myMachine.machineMemory.memoryData.begin(); it != myMachine.machineMemory.memoryData.end(); ++it) {
    //  QList<QStandardItem *> rowItems;
    //rowItems << new QStandardItem(QString::fromStdString(it->first))
    //       << new QStandardItem(QString::fromStdString(it->second));
    // memoryModel->appendRow(rowItems);
    //}
    ui->tableView->setModel(memoryModel);


    // ui->tableView->AdjustToContents;
}


void MainWindow::displayRegister(){
    memoryModel2->clear();
    memoryModel2->setHorizontalHeaderLabels(QStringList() << "Content");
    for (auto i : myMachine.R) {
        QList<QStandardItem *> rowItems;
        rowItems << new QStandardItem(QString::fromStdString(i.data));
        memoryModel2->appendRow(rowItems);
    }
    ui->tableView2->setModel(memoryModel2);

}

void MainWindow::setupProgramCounter() {
    bool ok;
    QString programCounter = QInputDialog::getText(this, "Welcome ya Agmad User", "Enter the program counter:", QLineEdit::Normal, "", &ok);

    if (ok && !programCounter.isEmpty()) {
        std::string counter = programCounter.toStdString();
        myMachine.setProgramCounter(counter);
    } else {
        myMachine.setProgramCounter("00");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    myMachine.reset();
    myMachine.pCounter=myMachine.tempCounter;
    myMachine.inst.clear();
    setInstructionTable();
    displayMemory();
    displayRegister();
}


void MainWindow::on_pushButton_3_clicked()
{
    myMachine.execute();
    memoryModel3->clear();
    memoryModel3->setHorizontalHeaderLabels(QStringList() << "Executed Instructions:");
    for (auto i : myMachine.inst) {
        QList<QStandardItem *> rowItems;
        rowItems << new QStandardItem(QString::fromStdString(i));
        memoryModel3->appendRow(rowItems);
    }
    ui->tableView3->setModel(memoryModel3);
    ui->tableView3->setColumnWidth(0, 390);
    if(myMachine.outRegister!=-1){ //3R00
        showMessage(QString::fromStdString(myMachine.R[myMachine.outRegister].data));
        myMachine.outRegister=-1;
    }

    //ui->tableView3->AdjustToContents;
 //   ui->tableView3->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
 //   ui->tableView3->resizeRowsToContents();

    displayMemory();
    displayRegister();
}

void MainWindow::setInstructionTable(){
    memoryModel3->clear();
    memoryModel3->setHorizontalHeaderLabels(QStringList() << "Executed Instructions:");
    ui->tableView3->setModel(memoryModel3);
  //  ui->tableView3->AdjustToContents;
    // ui->tableView3->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
   // ui->tableView3->resizeRowsToContents();
   // ui->tableView3->clearSpans();
    ui->tableView3->setColumnWidth(0, 390);

    // Manually resize rows to contents
    ui->tableView3->resizeRowsToContents();


}



void MainWindow::showMessage(const QString& message) {
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();
}
