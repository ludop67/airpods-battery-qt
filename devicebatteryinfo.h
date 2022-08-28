#ifndef DEVICEBATTERYINFO_H
#define DEVICEBATTERYINFO_H

#include <QWidget>

#include <QBluetoothAddress>
#include <QTimer>

#include "chargestatus.h"

namespace Ui {
class DeviceBatteryInfo;
}

class DeviceBatteryInfo : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceBatteryInfo(QBluetoothAddress addr, char model,
                               QWidget *parent = nullptr);
    ~DeviceBatteryInfo();

public slots:
    void updateStatus(const ChargeStatus& status);
    void timerTimeout();

protected:
    QString modelName(char model);
    void updateTimerText();

private:
    Ui::DeviceBatteryInfo *ui;

    QTimer m_timer;
    unsigned int m_lastSeenSeconds;

    static constexpr int TIMER_INTERVAL = 5000;

};

#endif // DEVICEBATTERYINFO_H
