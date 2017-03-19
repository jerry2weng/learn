#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->init();
}

MainWindow::~MainWindow()
{
    /*TODO:
     * notice to delete Data what i new!
     */
    delete Serial;
    delete Tcp;
    delete Udp;
    cout << "mainwindow"<<endl;
    delete ui;
}

void MainWindow::init()
{
    connect(ui->Tcp_Btn,SIGNAL(clicked(bool)),this,SLOT(Open_Tcp_Dailog(void)));
    connect(ui->Com_Btn,SIGNAL(clicked(bool)),this,SLOT(Open_Com_Dailog(void)));

    connect(ui->Udp_Btn,SIGNAL(clicked(bool)),this,SLOT(Open_Udp_Dailog(void)));


    /*TODO:
     *notice!!!allocate a memory,no use to free memory on qt...errrrrr
     */
    Tcp = new my_tcp;
    /*TODO:
     * trigger the signal to hide mainwindow
     */
    connect(Tcp,SIGNAL(show_mainWindow()),this,SLOT(show_mainWindow()));
    /*TODO:
     *notice!!!allocate a memory,no use to free memory on qt...errrrrr
     */
    Serial = new my_serialPort;
    /*TODO:
     * trigger the signal to hide mainwindow
     */
    connect(Serial,SIGNAL(show_mainWindow()),this,SLOT(show_mainWindow()));

    Udp = new UDP;
    connect(Udp,SIGNAL(show_mainWindow()),this,SLOT(show_mainWindow()));

}
/*TOO:
 * open the TCP debug tools
 */
void MainWindow::Open_Tcp_Dailog(void)
{
    Tcp->show();
    this->hide();
}
/*TODO:
 * Open the UART debug tools
 */
void MainWindow::Open_Com_Dailog(void)
{
    Serial->show();
    this->hide();
}

void MainWindow::Open_Udp_Dailog(void)
{
    Udp->show();
    this->close();
}


void MainWindow::show_mainWindow(void)
{
    this->showNormal();
}


