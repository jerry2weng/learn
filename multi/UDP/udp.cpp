#include "udp.h"
#include "ui_udp.h"

UDP::UDP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UDP)
{
    ui->setupUi(this);
    this->Init();
}

UDP::~UDP()
{
    delete ui;
}
void UDP::Init(void)
{
    this->UdpSend = new QUdpSocket;
    this->UdpRev  = new QUdpSocket;


    ui->listen_port->setText(tr("6666"));
    ui->leLocal_Port->setText(tr("8888"));
    ui->lePosition_Port->setText(tr("6666"));
    ui->leSend_Ip->setText(tr("192.168.1.1"));


}

void UDP::on_Listen_Btn_clicked()
{

}

void UDP::on_Connect_Btn_clicked()
{

}

void UDP::on_leRev_returnPressed()
{

}

void UDP::on_leSend_returnPressed()
{

}
