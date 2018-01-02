#ifndef DDBMAINWIN_H
#define DDBMAINWIN_H

#include <QMainWindow>
#include <QWebEngineView>
#include "metadatamanager.h"
namespace Ui {
class DDBMainWin;
}

class DDBMainWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit DDBMainWin(QWidget *parent = 0);
    ~DDBMainWin();

    void show_info_in_listView();
    void set_textEdit_GDD();

    Ui::DDBMainWin *ui;
    MetadataManager* mtr;
    QWebEngineView* pwebview;

private slots:
    void on_button_show_DDB_clicked();

private:

};

#endif // DDBMAINWIN_H
