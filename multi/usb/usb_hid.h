#ifndef USB_HID_H
#define USB_HID_H
#include "usb/usb_hid_lib/hidapi.h"

#include <QWidget>

namespace Ui {
class usb_hid;
}

class usb_hid : public QWidget
{
    Q_OBJECT

public:
    explicit usb_hid(QWidget *parent = 0);
    ~usb_hid();

private:
    Ui::usb_hid *ui;
    void init(void);

};

#endif // USB_HID_H
