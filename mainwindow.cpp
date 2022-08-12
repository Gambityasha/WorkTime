#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    setWindowIcon(QIcon("ICON.png"));
    logYear = QDate::currentDate().toString("yyyy");
    logMonth = QDate::currentDate().toString("MM");
    dirName = "../logs/"+logYear+"/";
    dir.mkdir("../logs/");
    dir.mkdir("../logs/"+logYear);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pbEnterTime_clicked()
{

    //QTime::currentTime().toString("HH:mm:ss")
    QString h ;
    if (ui->leHTime->text().toInt()<10) {
        h="0"+ui->leHTime->text();
    }else {
        h=ui->leHTime->text();
    }
    QString m;
            if (ui->leMTime->text().toInt()<10) {
                m="0"+ui->leMTime->text();
            }else {
                m=ui->leMTime->text();
            }


    QString strTemp = h+":"+m+":00";
    time = QTime::fromString(strTemp,"HH:mm:ss");
    timeNew = time.addSecs(60*60*8+60*40);
    ui->lblExitTime->setText(timeNew.toString("HH:mm:ss"));

    fname=QDate::currentDate().toString("MM")+"_ExitTime.txt";
    file.setFileName("../logs/"+logYear+"/"+fname);
    QTextStream stream(&file);
    stream.setFieldAlignment(QTextStream::AlignLeft);
    stream.setFieldWidth(32);
    if (file.exists()){//Проверка - существует ли файл
        if (file.open(QIODevice::WriteOnly | QIODevice::Append)) { // Append - для записи в конец файла
            stream<<QDate::currentDate().toString("dd")+", "+QDate::currentDate().toString("dddd")<<" | " +time.toString("HH:mm:ss")<<" | " +timeNew.toString("HH:mm:ss");
            stream.setFieldWidth(0);
            stream<<"\r\n";
            stream.setFieldWidth(32);
        }
    }else{
        if (file.open(QIODevice::WriteOnly | QIODevice::Append)) { // Append - для записи в конец файла
            stream<<QString::fromUtf8(" Дата")<<QString::fromUtf8(" | Время прихода")<<QString::fromUtf8(" | Расчетное время ухода");
            stream.setFieldWidth(0);
            stream<<"\r\n";
            stream.setFieldWidth(32);
            stream<<QDate::currentDate().toString("dd")+", "+QDate::currentDate().toString("dddd")<<" | "+time.toString("HH:mm:ss")<<" | " +timeNew.toString("HH:mm:ss");
            stream.setFieldWidth(0);
            stream<<"\r\n";
            stream.setFieldWidth(32);
        }
    }
    file.close();
}


void MainWindow::on_pushButton_clicked()
{
    if (ui->checkBox->isChecked()){
#ifdef Q_OS_WIN32
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    settings.setValue("WorkTime.exe", QDir::toNativeSeparators(QCoreApplication::applicationFilePath()));
    settings.sync();
#endif
    }else{
#ifdef Q_OS_WIN32
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    settings.remove("WorkTime.exe");
#endif
    }
}

