#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow),
      bst(16)
{
    ui->setupUi(this);

    bst.insert(8);
    bst.insert(7);
    bst.insert(11);
    bst.insert(9);
    bst.insert(14);
    bst.insert(21);
    bst.insert(30);
    bst.insert(25);
    bst.insert(46);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    std::vector<QPair<int,int>> vector;
    bst.placeNode(vector, 0);

    bst.draw(painter);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPainter painter(this);
    if (currentSelected != nullptr) {
        currentSelected->selected = false;
    }
    currentSelected = bst.getNodeInPosition(event->pos().x(), event->pos().y(), &painter);
    this->update();
}


void MainWindow::on_addButton_clicked()
{
    if(ui->keyInputField->text() != nullptr) {
        int key = ui->keyInputField->text().toInt();
        bst.insert(key);
        this->update();
    }
}

void MainWindow::on_findButton_clicked()
{
    if(ui->keyInputField->text() != nullptr) {
        int key = ui->keyInputField->text().toInt();
        if (currentSelected != nullptr) {
            currentSelected->selected = false;
        }
        currentSelected = bst.findAndSelect(key);
        qDebug() << "Entered key: " << currentSelected->key;
        qDebug() << "Selected: " << currentSelected;
        this->update();
    }
}


void MainWindow::on_deleteButton_clicked()
{
    if(currentSelected != nullptr) {
        bst.deleteNode(*currentSelected);
    }
}

