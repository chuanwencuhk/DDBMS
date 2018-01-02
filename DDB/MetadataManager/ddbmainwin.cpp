#include "ddbmainwin.h"
#include "ui_ddbmainwin.h"
#include <QDir>
DDBMainWin::DDBMainWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DDBMainWin)
{
    this->setWindowTitle(QString("DDBMS V0.1"));

    ui->setupUi(this);
    //mtr = MetadataManager::getInstance();
    pwebview = new QWebEngineView(this);
    pwebview->setUrl(QUrl(QStringLiteral("http://127.0.0.1:8080/tree.jsp")));
    //this->resize(QSize(1080,800));
    pwebview->resize(800, 650);
    pwebview->show();
    //resize(1024, 750);


}

DDBMainWin::~DDBMainWin()
{
    delete ui;

}

void DDBMainWin::show_info_in_listView()
{
    ui->DDB_textEdit->setText(mtr->get_metadata_version().c_str());
}

void DDBMainWin::set_textEdit_GDD()
{
    QDir *pDir = new QDir(".");
            QString fileDir = pDir->filePath(METADATA_CONFIG_FILE);

            QFile file(METADATA_CONFIG_FILE);
            if (!file.open(QIODevice::ReadWrite))
                  return;
            QTextStream out(&file);
            while(!file.atEnd())
           {
                  ui->DDB_textEdit->setText(out.readAll());
           }

}

void DDBMainWin::on_button_show_DDB_clicked()
{
    show_info_in_listView();
    set_textEdit_GDD();

}
