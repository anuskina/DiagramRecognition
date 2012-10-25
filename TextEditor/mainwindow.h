#pragma once

#include    <QtGui/QMainWindow>
#include    <QString>
namespace   Ui {
class   MainWindow;
}

class   MainWindow  :   public  QMainWindow
{
    Q_OBJECT
    
public:
    explicit    MainWindow(QWidget  *parent =   0);
    ~MainWindow();
public slots:
    void    open();
    void    save();
    void    saveAs();
    void    exit();
    void    about();
    void    newFile();
private:
    bool    isEmptyTextEdit();
    QString fileOpenName;
    void    messageBox();
    Ui::MainWindow  *ui;
};

#endif // MAINWINDOW_H
