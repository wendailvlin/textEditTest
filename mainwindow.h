#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mytextedit.h"
#include <QPushButton>
#include <QVBoxLayout>
#include<QVector>
#include"commondata.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //QPixmap getFilePixmap(const QString &FileName);

public slots:
    void send();

private:
    Ui::MainWindow *ui;
    MyTextEdit *myTextEdit;
    QPushButton *btn;
    QTextEdit* showText;
    QVBoxLayout* layout;


};

#endif // MAINWINDOW_H
