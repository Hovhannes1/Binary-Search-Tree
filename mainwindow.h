#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include "bst.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void on_addButton_clicked();

    void on_findButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::MainWindow *ui;

    BST bst;

    BST * currentSelected = nullptr;

};
#endif // MAINWINDOW_H
