#ifndef TEXTEDIT_H
#define TEXTEDIT_H
#include <QTextEdit>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>

class TextEdit:public QTextEdit
{
public:
    TextEdit();
    void setEditFile(const QString& filePath);
protected:
    void dropEvent(QDropEvent *event);
};

#endif // TEXTEDIT_H
