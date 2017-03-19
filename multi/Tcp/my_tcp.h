#ifndef MY_TCP_H
#define MY_TCP_H

#include <QWidget>

#include <QTcpSocket>
#include <QTcpServer>

namespace Ui {
class my_tcp;
}

class my_tcp : public QWidget
{
    Q_OBJECT

public:
    explicit my_tcp(QWidget *parent = 0);
    ~my_tcp();

private slots:
    void click_btnListen(void);
    void click_btnClearServer(void);
    void click_btnSendServer(void);

    void click_btnClearClient(void);
    void click_btnConnect(void);
    void click_btnSendClient(void);

    void Client_Read(void);
    void Server_Read(void);

    void slotServer_Connection(void);
protected:
    //virtual void keyPressEvent(QKeyEvent *event) final;
    virtual void closeEvent(QCloseEvent *e) final;

signals:
    void show_mainWindow(void);

private:
    Ui::my_tcp *ui;
    void My_Tcp_Init(void);

    QTcpServer *my_TcpServer;
    QTcpSocket *my_TcpClient;
    /*TODO:
     * connected socket
     */
    QTcpSocket *my_Socket_Server;

};

#endif // MY_TCP_H
