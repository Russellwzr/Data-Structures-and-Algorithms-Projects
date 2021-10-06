/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *RootEdit;
    QLineEdit *FatherL;
    QLineEdit *LChild;
    QLineEdit *FatherR;
    QLineEdit *RChild;
    QPushButton *pushButton;
    QPushButton *InsertLChild;
    QPushButton *InsertRChild;
    QPushButton *BTreeShow;
    QPushButton *Change;
    QLabel *label_8;
    QLineEdit *FatherInsert;
    QLineEdit *Root1;
    QLineEdit *Root2;
    QPushButton *pushButton_7;
    QLineEdit *ChildInsert;
    QPushButton *pushButton_8;
    QLineEdit *FatherDelete;
    QLineEdit *ChildDelete;
    QPushButton *pushButton_10;
    QLabel *label;
    QPushButton *Exit;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(806, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("font: 25 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221 Light\";\n"
"background-image: url(:/new/prefix1/123.jpg);\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(0, 10, 811, 41));
        label_6->setLineWidth(1);
        label_6->setTextFormat(Qt::AutoText);
        label_6->setScaledContents(false);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(100, 50, 171, 31));
        label_7->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/123.jpg);"));
        label_7->setLineWidth(1);
        label_7->setTextFormat(Qt::AutoText);
        label_7->setScaledContents(false);
        RootEdit = new QLineEdit(centralwidget);
        RootEdit->setObjectName(QString::fromUtf8("RootEdit"));
        RootEdit->setGeometry(QRect(70, 90, 110, 20));
        FatherL = new QLineEdit(centralwidget);
        FatherL->setObjectName(QString::fromUtf8("FatherL"));
        FatherL->setGeometry(QRect(70, 120, 50, 20));
        LChild = new QLineEdit(centralwidget);
        LChild->setObjectName(QString::fromUtf8("LChild"));
        LChild->setGeometry(QRect(130, 120, 50, 20));
        FatherR = new QLineEdit(centralwidget);
        FatherR->setObjectName(QString::fromUtf8("FatherR"));
        FatherR->setGeometry(QRect(70, 150, 50, 20));
        RChild = new QLineEdit(centralwidget);
        RChild->setObjectName(QString::fromUtf8("RChild"));
        RChild->setGeometry(QRect(130, 150, 50, 20));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(190, 90, 110, 20));
        InsertLChild = new QPushButton(centralwidget);
        InsertLChild->setObjectName(QString::fromUtf8("InsertLChild"));
        InsertLChild->setGeometry(QRect(190, 120, 110, 20));
        InsertRChild = new QPushButton(centralwidget);
        InsertRChild->setObjectName(QString::fromUtf8("InsertRChild"));
        InsertRChild->setGeometry(QRect(190, 150, 110, 20));
        BTreeShow = new QPushButton(centralwidget);
        BTreeShow->setObjectName(QString::fromUtf8("BTreeShow"));
        BTreeShow->setGeometry(QRect(70, 330, 110, 20));
        Change = new QPushButton(centralwidget);
        Change->setObjectName(QString::fromUtf8("Change"));
        Change->setGeometry(QRect(190, 330, 110, 21));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(100, 180, 171, 31));
        label_8->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/123.jpg);"));
        label_8->setLineWidth(1);
        label_8->setTextFormat(Qt::AutoText);
        label_8->setScaledContents(false);
        FatherInsert = new QLineEdit(centralwidget);
        FatherInsert->setObjectName(QString::fromUtf8("FatherInsert"));
        FatherInsert->setGeometry(QRect(70, 220, 50, 20));
        Root1 = new QLineEdit(centralwidget);
        Root1->setObjectName(QString::fromUtf8("Root1"));
        Root1->setGeometry(QRect(70, 250, 50, 20));
        Root2 = new QLineEdit(centralwidget);
        Root2->setObjectName(QString::fromUtf8("Root2"));
        Root2->setGeometry(QRect(130, 250, 50, 20));
        pushButton_7 = new QPushButton(centralwidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(190, 220, 110, 20));
        ChildInsert = new QLineEdit(centralwidget);
        ChildInsert->setObjectName(QString::fromUtf8("ChildInsert"));
        ChildInsert->setGeometry(QRect(130, 220, 50, 20));
        pushButton_8 = new QPushButton(centralwidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(190, 250, 110, 20));
        FatherDelete = new QLineEdit(centralwidget);
        FatherDelete->setObjectName(QString::fromUtf8("FatherDelete"));
        FatherDelete->setGeometry(QRect(70, 280, 50, 20));
        ChildDelete = new QLineEdit(centralwidget);
        ChildDelete->setObjectName(QString::fromUtf8("ChildDelete"));
        ChildDelete->setGeometry(QRect(130, 280, 50, 20));
        pushButton_10 = new QPushButton(centralwidget);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(190, 280, 110, 20));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 380, 231, 131));
        label->setFrameShape(QFrame::Box);
        Exit = new QPushButton(centralwidget);
        Exit->setObjectName(QString::fromUtf8("Exit"));
        Exit->setGeometry(QRect(140, 530, 75, 23));
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(400, 80, 331, 441));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 331, 441));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFrameShape(QFrame::Box);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:600;\">Forest &amp; BinaryTree</span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">BinaryTree</span></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Initialize Root", nullptr));
        InsertLChild->setText(QCoreApplication::translate("MainWindow", "Insert LChild", nullptr));
        InsertRChild->setText(QCoreApplication::translate("MainWindow", "Insert RChild", nullptr));
        BTreeShow->setText(QCoreApplication::translate("MainWindow", "Visualition", nullptr));
        Change->setText(QCoreApplication::translate("MainWindow", "Change", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">Forest</span></p></body></html>", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Insert Node", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Link Root", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "Delete Node", nullptr));
        label->setText(QString());
        Exit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
