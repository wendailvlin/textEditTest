#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTextBlock>
#include<QTextCursor>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    btn = new QPushButton(ui->centralWidget);
    fileBtn = new QPushButton(ui->centralWidget);
    btn->setText("发送");
    fileBtn->setText("发送文件");
    showText = new QTextEdit(ui->centralWidget);
    myTextEdit = new MyTextEdit(ui->centralWidget);
    layout = new QGridLayout(ui->centralWidget);
    layout->addWidget(showText,0,0,1,2);
    layout->addWidget(myTextEdit,1,0,1,2);
    layout->addWidget(fileBtn,2,0,1,1);
    layout->addWidget(btn,2,1,1,1);

    connect(btn,SIGNAL(clicked(bool)),this,SLOT(send()));
    connect(myTextEdit,SIGNAL(send()),this,SLOT(send()));
    connect(fileBtn,SIGNAL(clicked(bool)),this,SLOT(sendFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::send()
{
    QString str = myTextEdit->toPlainText();
    qDebug()<<"str==="<<str<<endl;
    if(str.isEmpty()){
        QMessageBox::information(this,"提示","不能发送空白信息");
        return;
    }

    QVector<MsgInfo> list = myTextEdit->getMsgList();
    int count = list.size();
    qDebug()<<"list size===="<<count<<endl;
    QTextCursor showCur= showText->textCursor();
    for(int i=0;i<count;i++){
        if(list[i].msgFlag=="text")
            showCur.insertText(list[i].text);
        else
            showCur.insertImage(list[i].pixmap.toImage());
        qDebug()<<list[i].msgFlag<<" "<<list[i].text<<endl;
    }
}

void MainWindow::sendFile()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.exec();
    QStringList urls = dialog.selectedFiles();
    if(urls.isEmpty()) return;
    int count = urls.size();
    for(int i=0;i<count;i++)
        qDebug()<<urls.at(i)<<endl;
    myTextEdit->insertFileFromUrl(urls);
}


