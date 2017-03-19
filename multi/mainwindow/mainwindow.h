#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcp/my_tcp.h"
#include "com/my_serialport.h"
#include "udp/udp.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    my_tcp *Tcp;
    my_serialPort *Serial;
    UDP *Udp;

    void init(void);


private slots:
    void Open_Tcp_Dailog(void);

    void Open_Com_Dailog(void);

    void Open_Udp_Dailog(void);

    void show_mainWindow(void);

};

#endif // MAINWINDOW_H
