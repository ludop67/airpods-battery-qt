#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <map>
#include <memory>

#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QTimer>

#include "devicebatteryinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void bluetoothDevDiscovered(const QBluetoothDeviceInfo& devInfo);
    void bluetoothError(QBluetoothDeviceDiscoveryAgent::Error error);
    void bluetoothDiscoverFinished();

    void startScan();

private:
    Ui::MainWindow *ui;

    QBluetoothDeviceDiscoveryAgent m_discoveryAgent;
    QTimer m_restartTimer;

    std::map<QBluetoothAddress, std::unique_ptr<DeviceBatteryInfo>> m_devices;

    static constexpr int RESTART_INTERVAL = 5000;
};
#endif // MAINWINDOW_H
