#include "textedit.h"
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
TextEdit::TextEdit()
{
    setAcceptDrops(true);
}
void TextEdit::dropEvent(QDropEvent *event)
{
    const QMimeData *mineData=event->mimeData();
    if(mineData->hasUrls())
    {
       QList<QUrl>urlList=mineData->urls();
       if(urlList.isEmpty())return ;
       QString fileName=urlList.at(0).toLocalFile();
       if(fileName.isEmpty())return;
       if(!fileName.isEmpty())
       {

       }
    }
}
