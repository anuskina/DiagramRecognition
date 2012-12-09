/********************************************************************************
** Form generated from reading UI file 'skeletonization.ui'
**
** Created: Sun 9. Dec 18:38:59 2012
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

class Ui_skeletonization
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *skeletonization)
    {
        if (skeletonization->objectName().isEmpty())
            skeletonization->setObjectName(QString::fromUtf8("skeletonization"));
        skeletonization->resize(400, 300);
        menuBar = new QMenuBar(skeletonization);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        skeletonization->setMenuBar(menuBar);
        mainToolBar = new QToolBar(skeletonization);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        skeletonization->addToolBar(mainToolBar);
        centralWidget = new QWidget(skeletonization);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        skeletonization->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(skeletonization);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        skeletonization->setStatusBar(statusBar);

        retranslateUi(skeletonization);

        QMetaObject::connectSlotsByName(skeletonization);
    } // setupUi

    void retranslateUi(QMainWindow *skeletonization)
    {
        skeletonization->setWindowTitle(QApplication::translate("skeletonization", "skeletonization", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class skeletonization: public Ui_skeletonization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SKELETONIZATION_H
