/********************************************************************************
** Form generated from reading UI file 'skeletonization.ui'
**
** Created: Sun 9. Dec 21:54:10 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKELETONIZATION_H
#define UI_SKELETONIZATION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Skeletonization
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Skeletonization)
    {
        if (Skeletonization->objectName().isEmpty())
            Skeletonization->setObjectName(QString::fromUtf8("Skeletonization"));
        Skeletonization->resize(400, 300);
        centralWidget = new QWidget(Skeletonization);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Skeletonization->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Skeletonization);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        Skeletonization->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Skeletonization);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Skeletonization->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Skeletonization);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Skeletonization->setStatusBar(statusBar);

        retranslateUi(Skeletonization);

        QMetaObject::connectSlotsByName(Skeletonization);
    } // setupUi

    void retranslateUi(QMainWindow *Skeletonization)
    {
        Skeletonization->setWindowTitle(QApplication::translate("Skeletonization", "Skeletonization", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Skeletonization: public Ui_Skeletonization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SKELETONIZATION_H
