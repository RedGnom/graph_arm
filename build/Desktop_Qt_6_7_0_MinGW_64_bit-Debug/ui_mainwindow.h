/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *add_button;
    QLineEdit *vert_insert;
    QLineEdit *vertex1;
    QLineEdit *vertex2;
    QPushButton *add_edge;
    QLineEdit *weight;
    QLabel *vert_text2;
    QLabel *weight_text;
    QLabel *vert_text1;
    QPushButton *seller_button;
    QPushButton *delete_vertex;
    QPushButton *delete_edge;
    QPushButton *change_edge;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        add_button = new QPushButton(centralwidget);
        add_button->setObjectName("add_button");
        add_button->setGeometry(QRect(10, 10, 111, 18));
        vert_insert = new QLineEdit(centralwidget);
        vert_insert->setObjectName("vert_insert");
        vert_insert->setGeometry(QRect(130, 10, 113, 20));
        vertex1 = new QLineEdit(centralwidget);
        vertex1->setObjectName("vertex1");
        vertex1->setGeometry(QRect(10, 40, 113, 20));
        vertex2 = new QLineEdit(centralwidget);
        vertex2->setObjectName("vertex2");
        vertex2->setGeometry(QRect(130, 40, 113, 20));
        add_edge = new QPushButton(centralwidget);
        add_edge->setObjectName("add_edge");
        add_edge->setGeometry(QRect(260, 40, 91, 18));
        weight = new QLineEdit(centralwidget);
        weight->setObjectName("weight");
        weight->setGeometry(QRect(130, 70, 113, 20));
        vert_text2 = new QLabel(centralwidget);
        vert_text2->setObjectName("vert_text2");
        vert_text2->setGeometry(QRect(40, 90, 51, 16));
        weight_text = new QLabel(centralwidget);
        weight_text->setObjectName("weight_text");
        weight_text->setGeometry(QRect(150, 110, 37, 12));
        vert_text1 = new QLabel(centralwidget);
        vert_text1->setObjectName("vert_text1");
        vert_text1->setGeometry(QRect(40, 120, 51, 16));
        seller_button = new QPushButton(centralwidget);
        seller_button->setObjectName("seller_button");
        seller_button->setGeometry(QRect(260, 70, 91, 18));
        delete_vertex = new QPushButton(centralwidget);
        delete_vertex->setObjectName("delete_vertex");
        delete_vertex->setGeometry(QRect(220, 110, 80, 18));
        delete_edge = new QPushButton(centralwidget);
        delete_edge->setObjectName("delete_edge");
        delete_edge->setGeometry(QRect(60, 160, 80, 18));
        change_edge = new QPushButton(centralwidget);
        change_edge->setObjectName("change_edge");
        change_edge->setGeometry(QRect(150, 160, 80, 18));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        add_button->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\262\320\265\321\200\321\210\320\270\320\275\321\203", nullptr));
        add_edge->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\263\321\200\320\260\320\275\321\214", nullptr));
        vert_text2->setText(QCoreApplication::translate("MainWindow", "\320\222\320\265\321\200\321\210\320\270\320\275\320\260 2", nullptr));
        weight_text->setText(QCoreApplication::translate("MainWindow", "\320\222\320\265\321\201", nullptr));
        vert_text1->setText(QCoreApplication::translate("MainWindow", "\320\222\320\265\321\200\321\210\320\270\320\275\320\260 1", nullptr));
        seller_button->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\274\320\274\320\270\320\262\320\276\321\217\320\266\320\265\321\200", nullptr));
        delete_vertex->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\262\320\265\321\200\321\210\320\270\320\275\321\203", nullptr));
        delete_edge->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\263\321\200\320\260\320\275\321\214", nullptr));
        change_edge->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\263\321\200\320\260\320\275\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
