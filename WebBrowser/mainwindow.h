#pragma once

#include    <QtGui/QMainWindow>

namespace   Ui {
class MainWindow;
}

class   MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
private slots:
    void    on_lineEdit_returnPressed();
};

#endif // MAINWINDOW_H
