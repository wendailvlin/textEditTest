#ifndef COMMONDATA_H
#define COMMONDATA_H

struct MsgInfo{
    QString msgFlag;//"text,image,file"
    QString text;//表示文件和图像的url,文本信息
    QPixmap pixmap;//文件和图片的缩略图
};


#endif // COMMONDATA_H
