#include "my_serialport.h"
#include "ui_my_serialport.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTest>

my_serialPort::my_serialPort(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::my_serialPort)
{
    ui->setupUi(this);
    this->Init();
    qDebug() << "serial structure";
}

my_serialPort::~my_serialPort()
{
    if(my_timer->isActive())
        my_timer->stop();
    delete my_timer;

    if(my_serial->isOpen())
        my_serial->close();
    delete my_serial;
    qDebug() << "serial";
    delete ui;
}

void my_serialPort::closeEvent(QCloseEvent *e)
{
    emit show_mainWindow();
    if(e->isAccepted())
        this->hide();
}

void my_serialPort::Init(void)
{
    /*TODO:
     * for detect portname what pluged in
     */
    this->setWindowTitle(tr("COM debug tool"));
    this->my_timer = new QTimer;
    connect(my_timer,SIGNAL(timeout()),this,SLOT(timeOut()));
    my_timer->start(500);

    my_serial = new QSerialPort;

    ui->ckAsc_rcv->setChecked(true);
    ui->cbAsc_send->setChecked(true);

    connect(ui->Btn_Clear,SIGNAL(clicked(bool)),this,SLOT(btnClear_dat()));
    connect(ui->Btn_Open,SIGNAL(clicked(bool)),this,SLOT(btnOpen_com()));
    connect(ui->Btn_Save,SIGNAL(clicked(bool)),this,SLOT(btnSave_data()));
    connect(ui->Ledit_Send,SIGNAL(returnPressed()),this,SLOT(btnSend_data()));

}
void my_serialPort::timeOut()
{
    this->detectCom_num();
}

void my_serialPort::detectCom_num()
{
    if(ui->Btn_Open->isEnabled())
    {
        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
            if(info.availablePorts().count() == 1)
                 ui->cbPort_name->clear();
            qDebug() << "name " << info.portName();
            this->portName = info.portName();

            if(ui->cbPort_name->findText(portName,Qt::MatchExactly) == -1)
                {
                    ui->cbPort_name->addItem(info.portName());
                }

        }

    }
    else
    {
        my_timer->stop();
    }
}

void my_serialPort::btnClear_dat()
{
    ui->Tedit_Receive->clear();
}

void my_serialPort::btnOpen_com()
{
    connect(my_serial,SIGNAL(readyRead()),this,SLOT(readDat()));
    if(ui->Btn_Open->text() == "打开串口")
    {
        my_serial->setBaudRate(ui->cbBaund_rate->currentText().toInt());
        my_serial->setDataBits((QSerialPort::DataBits)ui->cbDate_bit->currentText().toInt());
        /*TODO:
         * set check bit
         */
        my_serial->setParity((QSerialPort::Parity)ui->cbCheck_bit->currentIndex());

        my_serial->setFlowControl((QSerialPort::FlowControl)Flow_off);

        if(ui->cbStop_bit->currentIndex() == 1)
            my_serial->setStopBits((QSerialPort::StopBits)1.5);
        else
            my_serial->setStopBits((QSerialPort::StopBits)ui->cbStop_bit->currentIndex());

        my_serial->setPortName(ui->cbPort_name->currentText());

        if(my_serial->open(QIODevice::ReadWrite))
        {
            ui->Btn_Open->setText(tr("关闭串口"));
        }
    }
    else
    {
        ui->Btn_Open->setText(tr("打开串口"));
        ui->ckAsc_rcv->setEnabled(true);
        ui->ckHex_rcv->setEnabled(true);
        ui->cbAsc_send->setEnabled(true);
        ui->cbHex_send->setEnabled(true);

        my_serial->close();
    }

}

void my_serialPort::btnSave_data()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("保存为"), tr("测试结果.txt"));
    QFile file(filename);
    //如果用户取消了保存则直接退出函数
    if(file.fileName().isEmpty())
        return;
     //如果打开失败则给出提示并退出函数
     if(!file.open(QFile::WriteOnly | QIODevice::Text))
     {
        QMessageBox::warning(this, tr("保存文件"), tr("打开文件 %1 失败, 无法保存\n%2").arg(filename).arg(file.errorString()), QMessageBox::Ok);
        return;
     }
     //写数据到文件
     QTextStream out(&file);
     out<<ui->Tedit_Receive->toPlainText();
     file.close();
     //修改窗口标题为保存文件路径
     setWindowTitle("saved: " + QFileInfo(filename).canonicalFilePath());
}

void my_serialPort::btnSend_data()
{
    if(ui->cbAsc_send->isChecked() && ui->cbHex_send->isChecked())
    {
        ui->cbAsc_send->setEnabled(true);
        ui->cbAsc_send->setChecked(true);
        ui->cbAsc_send->setEnabled(false);
        ui->cbHex_send->setChecked(false);
    }
    QString sendDat = ui->Ledit_Send->text();
    QByteArray Qba;
    if(ui->cbHex_send->isChecked())
        my_serial->write(Qba.append(sendDat).toHex());
    if(ui->cbAsc_send->isChecked())
        my_serial->write(sendDat.toLatin1());
    ui->Ledit_Send->clear();

}

void my_serialPort::readDat()
{
    QTest::qWait(100);
    if(ui->ckAsc_rcv->isChecked() && ui->ckHex_rcv->isChecked())
    {
        ui->ckHex_rcv->setEnabled(false);
        ui->ckAsc_rcv->setChecked(true);
        ui->ckHex_rcv->setChecked(false);
    }

    QByteArray TempDat;
    TempDat = my_serial->readAll();

    QString Dat = QVariant(TempDat).toString();
   // Dat = ui->Tedit_Receive->toPlainText() + Dat;

    if(ui->ckHex_rcv->isChecked())
    {

        ui->ckAsc_rcv->setDisabled(true);
        ui->Tedit_Receive->append(QString(TempDat.toHex()));
    }
    if(ui->ckAsc_rcv->isChecked())
    {
        ui->ckAsc_rcv->setDisabled(true);
        ui->Tedit_Receive->append(Dat);
    }
    QTextCursor cursor = ui->Tedit_Receive->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->Tedit_Receive->setTextCursor(cursor);

}
