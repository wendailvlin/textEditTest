#include "mytextedit.h"

MyTextEdit::MyTextEdit(QWidget *parent)
    :QTextEdit(parent)
{
    connect(this,SIGNAL(textChanged()),this,SLOT(textEditChanged()));
}

QStringList MyTextEdit::getUrl(QString text)//获取绝对路径
{
    QStringList list = text.split("\n");
    QStringList urls;
    foreach (QString url, list) {
        if(!url.isEmpty()){
            urls.append(url.split("///").at(1));
        }
    }
    return urls;
}

QVector<MsgInfo> MyTextEdit::getMsgList()
{
    mGetMsgList.clear();
    QString doc = this->document()->toPlainText();
//    qDebug()<<"doc===="<<doc<<endl;
//    qDebug()<<"doc size===="<<doc.size()<<endl;
    QString text="";//存储文本信息
    int indexUrl = 0;
    int count = mMsgList.size();
//    qDebug()<<"urls count==="<<count<<endl;
//    for(int i=0;i<count;i++){
//        qDebug()<<mMsgList[i].msgFlag<<"---"<<mMsgList[i].text<<endl;
//    }
    for(int i=0;i<doc.size();i++){
        if(doc[i]==QChar::ObjectReplacementCharacter){
            qDebug()<<"!!!!is ObjectReplacementCharacter"<<endl;
            if(!text.isEmpty()){
                QPixmap pix;
                insertMsgList(mGetMsgList,"text",text,pix);
               //qDebug()<<"text==="<<text<<endl;
                text.clear();
            }
            while(indexUrl<count){
                MsgInfo msg =  mMsgList[indexUrl];
                if(this->document()->toHtml().contains(msg.text,Qt::CaseSensitive)) {
                    indexUrl++;
                    mGetMsgList.append(msg);
                    break;
                }
                indexUrl++;
            }
        }
        else text.append(doc[i]);
    }
    if(!text.isEmpty()){
        QPixmap pix;
//        qDebug()<<"text==="<<text<<endl;
        insertMsgList(mGetMsgList,"text",text,pix);
        text.clear();
    }
    return mGetMsgList;
}

void MyTextEdit::textEditChanged()
{
    qDebug()<<"text changed!!!"<<endl;
}

bool MyTextEdit::isImage(QString url)
{
    QString imageFormat = "bmp,jpg,png,tif,gif,pcx,tga,exif,fpx,svg,psd,cdr,pcd,dxf,ufo,eps,ai,raw,wmf,webp";
    QStringList imageFormatList = imageFormat.split(",");
    QFileInfo fileInfo(url);
    QString suffix = fileInfo.suffix();
    //qDebug()<<"后缀:"<<suffix<<endl;
    if(imageFormatList.contains(suffix,Qt::CaseInsensitive)){
        return true;
    }
    return false;
}

QPixmap MyTextEdit::getFileIconPixmap(const QString &url)
{
    QFileIconProvider provder;
    QFileInfo fileinfo(url);
    QIcon icon = provder.icon(fileinfo);

    QString strFileSize = getFileSize(fileinfo.size());
    qDebug() << "FileSize=" << fileinfo.size();

    QFont font(QString("宋体"),10,QFont::Normal,false);
    QFontMetrics fontMetrics(font);
    QSize textSize = fontMetrics.size(Qt::TextSingleLine, fileinfo.fileName());

    QSize FileSize = fontMetrics.size(Qt::TextSingleLine, strFileSize);
    int maxWidth = textSize.width() > FileSize.width() ? textSize.width() :FileSize.width();
    QPixmap pix(50 + maxWidth + 10, 50);
    pix.fill();

    QPainter painter;
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setFont(font);
    painter.begin(&pix);
    // 文件图标
    QRect rect(0, 0, 50, 50);
    painter.drawPixmap(rect, icon.pixmap(40,40));
    painter.setPen(Qt::black);
    // 文件名称
    QRect rectText(50+10, 3, textSize.width(), textSize.height());
    painter.drawText(rectText, fileinfo.fileName());
    // 文件大小
    QRect rectFile(50+10, textSize.height()+5, FileSize.width(), FileSize.height());
    painter.drawText(rectFile, strFileSize);
    painter.end();
    return pix;
}

QString MyTextEdit::getFileSize(qint64 size)
{
    QString Unit;
    double num;
    if(size < 1024){
        num = size;
        Unit = "B";
    }
    else if(size < 1024 * 1224){
        num = size / 1024.0;
        Unit = "KB";
    }
    else if(size <  1024 * 1024 * 1024){
        num = size / 1024.0 / 1024.0;
        Unit = "MB";
    }
    else{
        num = size / 1024.0 / 1024.0/ 1024.0;
        Unit = "GB";
    }
    return QString::number(num,'f',2) + " " + Unit;
}

void MyTextEdit::insertMsgList(QVector<MsgInfo> &list, QString flag, QString text, QPixmap pix)
{
    MsgInfo msg;
    msg.msgFlag=flag;
    msg.text = text;
    msg.pixmap = pix;
    list.append(msg);
}
bool MyTextEdit::canInsertFromMimeData(const QMimeData *source) const
{
    return QTextEdit::canInsertFromMimeData(source);
}

void MyTextEdit::insertFromMimeData(const QMimeData *source)
{
       QStringList urls = getUrl(source->text());

       foreach (QString url, urls) {
            if(isImage(url))
                insertImages(url);
            else
                insertTextFile(url);
       }
}

void MyTextEdit::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->source()==this)
        event->ignore();
    else
        event->accept();
}

void MyTextEdit::dropEvent(QDropEvent *event)
{
    qDebug()<<"url==="<<event->mimeData()->text();
    insertFromMimeData(event->mimeData());
    event->accept();
}

void MyTextEdit::keyPressEvent(QKeyEvent *e)
{
    if((e->key()==Qt::Key_Enter||e->key()==Qt::Key_Return)&& !(e->modifiers() & Qt::ShiftModifier)){
        //qDebug()<<"快捷键！！！"<<endl;
        emit send();
        return;
    }
    QTextEdit::keyPressEvent(e);

}

void MyTextEdit::insertImages(const QString &url)
{
    QImage image(url);
    //按比例缩放图片
    if(image.width()>120||image.height()>80){
        if(image.width()>image.height()){
          image =  image.scaledToWidth(120,Qt::SmoothTransformation);
        }
        else
            image = image.scaledToHeight(80,Qt::SmoothTransformation);
    }
    QTextCursor cursor = this->textCursor();
//    QTextDocument *document = this->document();
//    document->addResource(QTextDocument::ImageResource, QUrl(url), QVariant(image));
    cursor.insertImage(image,url);

    insertMsgList(mMsgList,"image",url,QPixmap::fromImage(image));
}

void MyTextEdit::insertTextFile(const QString &url)
{
    QFileInfo fileInfo(url);
    if(fileInfo.isDir()){
        QMessageBox::information(this,"拖拽文件","只允许拖拽单个文件!");
    }
    else{
        if(fileInfo.size()>100*1024*1024){
            QMessageBox::information(this,"提示","发送的文件大小不能大于100M");
        }
        else{
            QPixmap pix = getFileIconPixmap(url);
            QTextCursor cursor = this->textCursor();
           // qDebug()<<"插入文件前:"<<cursor.anchor();
            cursor.insertImage(pix.toImage(),url);
           // qDebug()<<"插入文件后:"<<cursor.anchor();
            insertMsgList(mMsgList,"file",url,pix);
        }
    }
}

