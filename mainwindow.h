#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QDate>
#include <QDateTime>
#include <QTime>
#include <QDir>
#include <QMessageBox>
#include <QPixmap>
#include <QSettings>
#include "stdint.h"




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbEnterTime_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString fname;
    QString logYear;
    QString logMonth;
    QString dirName;
    QDir dir;
    QTime time;
    QTime timeNew;
    QTime exitTime;
    QFile file;



};
#endif // MAINWINDOW_H
