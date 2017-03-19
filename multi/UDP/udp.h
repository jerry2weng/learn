#ifndef UDP_H
#define UDP_H

#include <QWidget>
#include <QtNetwork>

namespace Ui {
class UDP;
}

class UDP : public QWidget
{
    Q_OBJECT

public:
    explicit UDP(QWidget *parent = 0);
    ~UDP();

private slots:
    void on_Listen_Btn_clicked();

    void on_Connect_Btn_clicked();

    void on_leRev_returnPressed();

    void on_leSend_returnPressed();

private:
    Ui::UDP *ui;
    QUdpSocket *UdpSend;
    QUdpSocket *UdpRev;
    void Init(void);

};

#endif // UDP_H
