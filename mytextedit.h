#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QTextEdit>
#include <QMouseEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QMimeType>
#include <QDebug>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QMessageBox>
#include <QPainter>
#include <QVector>

#include"commondata.h"
class MyTextEdit : public QTextEdit
{

    Q_OBJECT

public:
    MyTextEdit(QWidget *parent = 0);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void keyPressEvent(QKeyEvent *e);

public:
    void insertFileFromUrl(const QStringList &urls);
    void insertImages(const QString &url);
    void insertTextFile(const QString &url);
    bool canInsertFromMimeData(const QMimeData *source) const;
    void insertFromMimeData(const QMimeData *source);

    QVector<MsgInfo> getMsgList();

public slots:
    void textEditChanged();
signals:
    void send();
private:
    QVector<MsgInfo> mMsgList;
    QVector<MsgInfo> mGetMsgList;
    QStringList getUrl(QString text);
    bool isImage(QString url);//判断文件是否为图片
    QPixmap getFileIconPixmap(const QString &url);//获取文件图标及大小信息，并转化成图片
    QString getFileSize(qint64 size);//获取文件大小
    void insertMsgList(QVector<MsgInfo> &list,QString flag, QString text, QPixmap pix);
};

#endif // MYTEXTEDIT_H
