#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mytextedit.h"
#include <QPushButton>
#include <QVBoxLayout>
#include<QVector>
#include<QFileDialog>
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
    void sendFile();

private:
    Ui::MainWindow *ui;
    MyTextEdit *myTextEdit;
    QPushButton *btn;
    QPushButton *fileBtn;
    QTextEdit* showText;
    QGridLayout * layout;


};

#endif // MAINWINDOW_H
