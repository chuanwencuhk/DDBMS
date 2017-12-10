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
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DDBMainWin)
    {
        if (DDBMainWin->objectName().isEmpty())
            DDBMainWin->setObjectName(QStringLiteral("DDBMainWin"));
        DDBMainWin->resize(800, 600);
        centralwidget = new QWidget(DDBMainWin);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        button_show_DDB = new QPushButton(centralwidget);
        button_show_DDB->setObjectName(QStringLiteral("button_show_DDB"));
        button_show_DDB->setGeometry(QRect(640, 40, 111, 41));
        DDB_textEdit = new QTextEdit(centralwidget);
        DDB_textEdit->setObjectName(QStringLiteral("DDB_textEdit"));
        DDB_textEdit->setGeometry(QRect(50, 40, 511, 451));
        DDBMainWin->setCentralWidget(centralwidget);
        menubar = new QMenuBar(DDBMainWin);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 28));
        DDBMainWin->setMenuBar(menubar);
        statusbar = new QStatusBar(DDBMainWin);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        DDBMainWin->setStatusBar(statusbar);

        retranslateUi(DDBMainWin);

        QMetaObject::connectSlotsByName(DDBMainWin);
    } // setupUi

    void retranslateUi(QMainWindow *DDBMainWin)
    {
        DDBMainWin->setWindowTitle(QApplication::translate("DDBMainWin", "MainWindow", Q_NULLPTR));
        button_show_DDB->setText(QApplication::translate("DDBMainWin", "Show DDB", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DDBMainWin: public Ui_DDBMainWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DDBMAINWIN_H
