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
    if(ui->Listen_Btn == "开始监听")
    {
        ui->Listen_Btn->setText(tr("监听中"));
        QHostAddress Port = QHostAddress(ui->listen_port->text().toInt());
        UdpRev->bind(QHostAddress::Any,Port);
        if(UdpRev->waitForConnected(2000))
        {
           ui->tbRev->setText(tr("connect successfully"));
           connect(this->UdpRev,SIGNAL(readyRead()),this,readUdp_data());
        }
        ui->tbRev->setText(tr("connect failure"));
    }
    else
    {
        ui->Listen_Btn->setText(tr("开始监听"));
        UdpRev->close();
    }




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

void UDP::readUdp_data()
{
    while(UdpRev->hasPendingDatagrams())
    {\
        QByteArray Datagram;
        Datagram.resize(UdpRev->pendingDatagramSize());

        /*TODO:
         * what is it for?
         */
        QHostAddress my_addr;
        unsigned int my_port;

        UdpRev->readDatagram(Datagram.data(),Datagram.size(),&my_addr,&my_port);
        if(ui->ckHex->isChecked())
        {
            ui->tbRev->append(QString(Datagram.toHex()));
        }
        if(ui->ckAssic->isChecked())
        {
            ui->tbRev->append(QVariant(Datagram).toString());
        }
    }
}



