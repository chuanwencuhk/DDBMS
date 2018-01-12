/********************************************************************************
** Form generated from reading UI file 'ddbmainwin.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DDBMAINWIN_H
#define UI_DDBMAINWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DDBMainWin
{
public:
    QWidget *centralwidget;
    QPushButton *button_show_DDB;
    QTextEdit *DDB_textEdit;
    QMenuBar *menubar;
    QMenu *menuDDBMS_V0_1;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DDBMainWin)
    {
        if (DDBMainWin->objectName().isEmpty())
            DDBMainWin->setObjectName(QStringLiteral("DDBMainWin"));
        DDBMainWin->resize(1600, 800);
        centralwidget = new QWidget(DDBMainWin);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        button_show_DDB = new QPushButton(centralwidget);
        button_show_DDB->setObjectName(QStringLiteral("button_show_DDB"));
        button_show_DDB->setGeometry(QRect(1490, 710, 100, 40));
        DDB_textEdit = new QTextEdit(centralwidget);
        DDB_textEdit->setObjectName(QStringLiteral("DDB_textEdit"));
        DDB_textEdit->setGeometry(QRect(1190, 20, 381, 621));
        DDBMainWin->setCentralWidget(centralwidget);
        menubar = new QMenuBar(DDBMainWin);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1600, 26));
        menuDDBMS_V0_1 = new QMenu(menubar);
        menuDDBMS_V0_1->setObjectName(QStringLiteral("menuDDBMS_V0_1"));
        DDBMainWin->setMenuBar(menubar);
        statusbar = new QStatusBar(DDBMainWin);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        DDBMainWin->setStatusBar(statusbar);

        menubar->addAction(menuDDBMS_V0_1->menuAction());

        retranslateUi(DDBMainWin);

        QMetaObject::connectSlotsByName(DDBMainWin);
    } // setupUi

    void retranslateUi(QMainWindow *DDBMainWin)
    {
        DDBMainWin->setWindowTitle(QApplication::translate("DDBMainWin", "MainWindow", Q_NULLPTR));
        button_show_DDB->setText(QApplication::translate("DDBMainWin", "Show DDB", Q_NULLPTR));
        menuDDBMS_V0_1->setTitle(QApplication::translate("DDBMainWin", "DDBMS V0.1", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DDBMainWin: public Ui_DDBMainWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DDBMAINWIN_H
