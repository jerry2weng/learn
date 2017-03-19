#include "my_tcp.h"
#include "ui_my_tcp.h"
#include <QMessageBox>
#include <QTest>
#include <QDebug>

my_tcp::my_tcp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::my_tcp)
{
    ui->setupUi(this);
    this->My_Tcp_Init();
}

my_tcp::~my_tcp()
{
    delete my_Socket_Server;
    delete my_TcpClient;
    delete my_TcpServer;
    qDebug() << "tcp";
    delete ui;
}
/*
void my_tcp::keyPressEvent(QKeyEvent *event)
{
    emit show_mainWindow();

    if(Qt::Key_Escape == event->key())
    {
        this->close();
    }
}
*/
void my_tcp::closeEvent(QCloseEvent *e)
{
    emit show_mainWindow();
    if(e->isAccepted())
    {
        this->hide();
    }
}

void my_tcp::My_Tcp_Init()
{
    this->setWindowTitle("Tcp debug tool");
    /*TODO:
     * Init the port and ip addr
     */
    ui->txtPortServer->setText("60000");
    ui->txtPortClient->setText("60000");

    ui->txtIP->setText("192.168.2.123");
    /*TODO:
     *connect slots
     */
    connect(ui->btnClearClient,SIGNAL(clicked(bool)),this,SLOT(click_btnClearClient()));
    connect(ui->btnClearServer,SIGNAL(clicked(bool)),this,SLOT(click_btnClearServer()));
    connect(ui->btnConnect,SIGNAL(clicked(bool)),this,SLOT(click_btnConnect()));
    connect(ui->btnListen,SIGNAL(clicked(bool)),this,SLOT(click_btnListen()));

    connect(ui->btnSendClient,SIGNAL(clicked(bool)),this,SLOT(click_btnSendClient()));
    connect(ui->txtSendClient,SIGNAL(returnPressed()),this,SLOT(click_btnSendClient()));

    connect(ui->btnSendServer_2,SIGNAL(clicked(bool)),this,SLOT(click_btnSendServer()));
    connect(ui->txtSendServer_2,SIGNAL(returnPressed()),this,SLOT(click_btnSendServer()));

    //connect(ui,SIGNAL())

    /*TODO:
     * Init TCP server and client point
     */
    this->my_TcpClient= new QTcpSocket(this);
    this->my_TcpClient = new QTcpSocket(this);
    this->my_TcpServer = new QTcpServer(this);

}


void my_tcp::click_btnListen()
{
    if(ui->btnListen->text() == "监听")
    {
        bool ok = my_TcpServer->listen(QHostAddress::Any,ui->txtPortServer->text().toInt());
        if (ok)
        {
            connect(my_TcpServer,SIGNAL(newConnection()),this,SLOT(slotServer_Connection()));
            ui->btnListen->setText("停止");
            ui->txtDataServer_2->append("监听成功");
            ui->btnSendServer_2->setEnabled(true);
        }
    }
    else
    {
        //my_TcpServer->CloseAllClient();//断开所有已连接的客户端
        my_TcpServer->close();//停止监听
        ui->btnListen->setText("监听");
        ui->txtDataServer_2->append("停止监听成功");
        ui->btnSendServer_2->setEnabled(false);
    }

}

void my_tcp::slotServer_Connection()
{
    my_Socket_Server = my_TcpServer->nextPendingConnection();
    connect(my_Socket_Server,SIGNAL(readyRead()),this,SLOT(Server_Read()));
}

void my_tcp::click_btnConnect()
{
    if(ui->txtIP->text().isEmpty() || ui->txtPortClient->text().isEmpty())
    {
        QMessageBox::warning(this,tr("warning"),tr("please text the ip or port num"));
        return;
    }
    ui->btnConnect->setEnabled(true);

    if(ui->btnConnect->text() == "连接")
    {
        my_TcpClient->abort();
        QString Dest_Ip = ui->txtIP->text();
        quint32 Dest_Port = ui->txtPortClient->text().toInt();

        my_TcpClient->connectToHost(Dest_Ip,Dest_Port);

        if (my_TcpClient->waitForConnected(3000))
        {
            ui->btnConnect->setText("断开");
            ui->txtDataClient->append("连接服务器成功");
            ui->btnSendClient->setEnabled(true);
            ui->txtIP->setEnabled(false);
            ui->txtPortClient->setEnabled(false);
        }

        connect(my_TcpClient,SIGNAL(readyRead()),this,SLOT(Client_Read()));
    }
    else
    {
        my_TcpClient->disconnectFromHost();
        if (my_TcpClient->state() == QAbstractSocket::UnconnectedState || my_TcpClient->waitForDisconnected(1000))
        {
            ui->btnConnect->setText("连接");
            ui->txtDataClient->append("断开连接成功");
            ui->btnSendClient->setEnabled(true);
            ui->txtIP->setEnabled(true);
            ui->txtPortClient->setEnabled(true);
        }
    }
}

void my_tcp::click_btnClearServer()
{
    ui->txtDataServer_2->clear();
}

void my_tcp::click_btnClearClient()
{
    ui->txtDataClient->clear();
}



/*******************************************************************************
 * TODO:
 * slot to Tcp client readyread signal
 *
 *
 *
 *******************************************************************************/

void my_tcp::Client_Read()
{
    QTest::qWait(100);
    QByteArray Qba = my_TcpClient->readAll();
    QString ReadData = QVariant(Qba).toString();

    QHostAddress Ip = my_TcpClient->peerAddress();
    if(ui->ckHexReceiveClient->isChecked())
    {
        QString Info = "Ip Address: " + Ip.toString() + " Time: " + QTime::currentTime().toString("hh:mm:ss ") + "Data: " + QString(Qba.toHex());
        ui->txtDataClient->append(Info);
    }
    else
    {
        QString Info = "Ip Address: " + Ip.toString() + " Time: " + QTime::currentTime().toString("hh:mm:ss ") + "Data: " + ReadData;
        ui->txtDataClient->append(Info);
    }
}
/*******************************************************************************
 * TODO:
 * slot to Tcp server readyread signal
 *
 *
 *
 *******************************************************************************/
void my_tcp::Server_Read(void)
{
    QByteArray Qba = my_Socket_Server->readAll();

    QString ReadData = QVariant(Qba).toString();
    QHostAddress Ip = my_Socket_Server->peerAddress();
    quint16 Port = my_Socket_Server->peerPort();
    if(ui->ckHexReceiveServer->isChecked())
    {
        QString Info = "Port: " + QString::number(Port,10) + " IP: "+ Ip.toString().remove(0,6) + " Time: " + QTime::currentTime().toString("hh:mm:ss") + "  数据:" + QString(Qba.toHex());
        ui->txtDataServer_2->append(Info);
    }
    else
    {
        QString Info = "Port: " + QString::number(Port,10) + " IP: "+ Ip.toString().remove(0,6) + " Time: " + QTime::currentTime().toString("hh:mm:ss") + "  数据:" + ReadData;
        ui->txtDataServer_2->append(Info);
    }
}
/*******************************************************************************
 * TODO:
 * slot to Tcp server send Message
 *
 *
 *
 *******************************************************************************/
void my_tcp::click_btnSendServer()
{
    if(ui->txtSendServer_2->text().isEmpty() || !my_Socket_Server->isValid())
        return;
    QString txt = ui->txtSendServer_2->text();
    QByteArray Qba;

    if(ui->ckHexSendServer->isChecked())
    {
        my_Socket_Server->write(Qba.append(txt).toHex());
    }
    else
    {
        my_Socket_Server->write(txt.toLatin1());
    }

}
/*******************************************************************************
 * TODO:
 * slot to Tcp client send Message
 *
 *
 *
 *******************************************************************************/
void my_tcp::click_btnSendClient()
{
    QString Qs = ui->txtSendClient->text();
    if(Qs.isEmpty() || !my_TcpClient->isValid())
        return;
    QByteArray Qba;
    if(ui->ckHexSendClient->isChecked())
    {
        my_TcpClient->write(Qba.append(Qs).toHex());
    }
    else
    {
        my_TcpClient->write(Qs.toLatin1());
    }
}







