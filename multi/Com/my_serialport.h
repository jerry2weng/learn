#ifndef MY_SERIALPORT_H
#define MY_SERIALPORT_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QWidget>
#include <QTimer>
#include <QEvent>

namespace Ui {
class my_serialPort;
}

class my_serialPort : public QWidget
{
    Q_OBJECT

public:
    explicit my_serialPort(QWidget *parent = 0);
    ~my_serialPort();
    QTimer *my_timer;


private slots:
    void timeOut(void);
    void btnOpen_com(void);
    void btnSave_data(void);
    void btnClear_dat(void);
    void btnSend_data(void);
    void readDat(void);

signals:
    void show_mainWindow(void);

protected:
    virtual void closeEvent(QCloseEvent *e) final;

private:
    Ui::my_serialPort *ui;
    QSerialPort *my_serial;
    QString portName;

    void detectCom_num(void);
    void Init(void);


    const unsigned char Flow_off = 0;


};

#endif // MY_SERIALPORT_H
