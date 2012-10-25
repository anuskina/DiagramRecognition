#include    "mainwindow.h"
#include    "ui_mainwindow.h"
#include    "QFileDialog"
#include    "QTextStream"
#include    "QIODevice"
#include    "QMessageBox"

MainWindow::MainWindow(QWidget  *parent) :
    QMainWindow(parent),
    ui(new  Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this->ui->actionOpen,   SIGNAL(triggered()),    this,   SLOT(open()));
    connect(this->ui->actionSave,   SIGNAL(triggered()),    this,   SLOT(save()));
    connect(this->ui->actionSave_As,    SIGNAL(triggered()),    this,   SLOT(saveAs()));
    connect(this->ui->actionExit,   SIGNAL(triggered()), this,  SLOT(exit()));
    connect(this->ui->actionAbout,  SIGNAL(triggered()),   this,   SLOT(about()));
    connect(this->ui->actionNew,  SIGNAL(triggered()),   this,   SLOT(newFile()));
}
MainWindow::~MainWindow()
{
    delete  ui;
}
bool MainWindow::isEmptyTextEdit()
{
    return  this->ui->textEdit->toPlainText()   ==  "";
}
void MainWindow::messageBox()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Message");
    msgBox.setText("Attention: file not saved");
    msgBox.setInformativeText("Do you want to save file?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    switch (ret) {
        case QMessageBox::Yes:
            this->save();
            break;
        case QMessageBox::No:
            this->close();
            break;
        default:
            this->close();
            break;
        }
}
void    MainWindow::newFile()
{
    if  (!isEmptyTextEdit()    ||  fileOpenName != 0){
        messageBox();
    }
    this->ui->textEdit->clear();
}
void    MainWindow::open()
{
    if  (!isEmptyTextEdit()    ||  fileOpenName != 0){
        messageBox();
    }
    fileOpenName    =   QFileDialog::getOpenFileName(this, tr("Open"), "",  tr("Text Files (*.txt)"));
    if  (fileOpenName   !=  ""){
        QFile   file(fileOpenName);
        if  (file.open(QIODevice::ReadOnly)){
            QTextStream in(&file);
            this->ui->textEdit->setText(in.readAll());
        }
    }
}
void    MainWindow::saveAs()
{
       fileOpenName    =   QFileDialog::getSaveFileName(this,   tr("Save as"),  "",   tr("Text Files (*.txt)"));
       if   (fileOpenName !=  ""){
           QFile file(fileOpenName);
           if   (file.open(QIODevice::WriteOnly)){
               QTextStream stream(&file);
               stream  <<  this->ui->textEdit->toPlainText();
               stream.flush();
               file.close();
               fileOpenName.clear();
           }
       }
}
void    MainWindow::save()
{
    if  (fileOpenName ==  0){
       fileOpenName    =   QFileDialog::getSaveFileName(this,   tr("Save"), "", tr("Text Files (*.txt)"));
    }
    if  (fileOpenName !=  ""){
        QFile file(fileOpenName);
        if  (file.open(QIODevice::WriteOnly)){
            QTextStream stream(&file);
            stream  <<  this->ui->textEdit->toPlainText();
            stream.flush();
            file.close();
            fileOpenName.clear();
        }
    }
}
void    MainWindow::exit()
{
    if  (!isEmptyTextEdit()    ||  fileOpenName != 0){
        messageBox();
    }
    else{
        this->close();
    }
}
void    MainWindow::about()
{
    QMessageBox::about(this, tr("Message")
                       ,    tr("This application allows you to open, edit and save text files"));
}


