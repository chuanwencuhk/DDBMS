#include "ddbmainwin.h"
#include "ui_ddbmainwin.h"

DDBMainWin::DDBMainWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DDBMainWin)
{

    ui->setupUi(this);
    //mtr = MetadataManager::getInstance();

}

DDBMainWin::~DDBMainWin()
{
    delete ui;

}

void DDBMainWin::show_info_in_listView()
{
    ui->DDB_textEdit->setText(mtr->get_metadata_version().c_str());
}

void DDBMainWin::on_button_show_DDB_clicked()
{
    show_info_in_listView();

}
