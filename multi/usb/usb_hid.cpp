#include "usb_hid.h"
#include "ui_usb_hid.h"

usb_hid::usb_hid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::usb_hid)
{
    ui->setupUi(this);

}

usb_hid::~usb_hid()
{
    delete ui;
}

