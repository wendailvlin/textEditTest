#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTextBlock>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    btn = new QPushButton(ui->centralWidget);
    btn->setText("发送");
    showText = new QTextEdit(ui->centralWidget);
    myTextEdit = new MyTextEdit(ui->centralWidget);
    layout = new QVBoxLayout(ui->centralWidget);
    layout->addWidget(showText);
    layout->addWidget(myTextEdit);
    layout->addWidget(btn);

    connect(btn,SIGNAL(clicked(bool)),this,SLOT(send()));
    connect(myTextEdit,SIGNAL(send()),this,SLOT(send()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::send()
{
    QString str = myTextEdit->toPlainText();
    qDebug()<<"str==="<<str<<endl;
//    QStringList strlist = str.split( QChar::ObjectReplacementCharacter);
//    qDebug()<<"strlist count = "<<strlist.size()<<endl;
//    for(int i=0;i<strlist.size();i++){
//        qDebug()<<strlist.at(i)<<endl;
//    }

    QString html = myTextEdit->toHtml();
    qDebug()<<html;
    showText->setHtml(html);
    QTextDocument *document = myTextEdit->document();
    QVector<MsgInfo> list = myTextEdit->getMsgList();
    int count = list.size();
    qDebug()<<"list size===="<<count<<endl;
    for(int i=0;i<count;i++){
        qDebug()<<list[i].msgFlag<<" "<<list[i].text<<endl;

    }

    //QVariant var = document->loadResource(int type, const QUrl &name);
   // qDebug()<<"wenjian::::"<<document->toHtml();

    //QTextCursor cursor(document);
}

/*QPixmap MainWindow::getFilePixmap(const QString &FileName)
{
    QFileIconProvider provder;
    QFileInfo fileinfo(FileName);
    QIcon icon = provder.icon(fileinfo);

    QString strFileSize = getFileSize(fileinfo.size());
    qDebug() << "FileSize" << strFileSize;

    QFont font(QString("宋体"),10,QFont::Normal,false);
    QFontMetrics fontMetrics(font);
    QSize textSize = fontMetrics.size(Qt::TextSingleLine, fileinfo.fileName());

    QSize FileSize = fontMetrics.size(Qt::TextSingleLine, strFileSize);
    int maxWidth = textSize.width() > FileSize.width() ? textSize.width() :FileSize.width();
    QPixmap pix(m_nFixHeight + maxWidth + 10, m_nFixHeight);
    pix.fill();
    QPainter painter;
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setFont(font);    painter.begin(&pix);
    // 文件图标    QRect rect(0, 0, m_nFixHeight, m_nFixHeight);    painter.drawPixmap(rect, icon.pixmap(m_nFixHeight,m_nFixHeight));
    painter.setPen(Qt::black);
    // 文件名称    QRect rectText(m_nFixHeight+10, 0, textSize.width(), textSize.height());    painter.drawText(rectText, fileinfo.fileName());
    // 文件大小    QRect rectFile(m_nFixHeight+10, textSize.height()+5, FileSize.width(), FileSize.height());    painter.drawText(rectFile, strFileSize);    painter.end();
    return pix;
}*/
