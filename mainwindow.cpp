#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QBluetoothLocalDevice>

#include <iostream>

#include "airpodsspecs.h"
#include "chargestatus.h"
#include "devicebatteryinfo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_restartTimer.setInterval(RESTART_INTERVAL);
    connect(&m_restartTimer, &QTimer::timeout, this, &MainWindow::startScan);

    m_discoveryAgent.setLowEnergyDiscoveryTimeout(5000);

    connect(&m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &MainWindow::bluetoothDevDiscovered);
    connect(&m_discoveryAgent, qOverload<QBluetoothDeviceDiscoveryAgent::Error>(&QBluetoothDeviceDiscoveryAgent::error), this, &MainWindow::bluetoothError);
    connect(&m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this, &MainWindow::bluetoothDiscoverFinished);

    startScan();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::bluetoothDevDiscovered(const QBluetoothDeviceInfo &devInfo)
{
    if(/*devInfo.rssi() < MIN_RSSI ||*/ !devInfo.manufacturerIds().contains(AIRPODS_MANUFACTURER))
        return;

    QByteArray data = devInfo.manufacturerData(AIRPODS_MANUFACTURER);
    if(data.length() != AIRPODS_DATA_LENGTH)
    {
        std::cerr << "Error: Invalid data length " << data.length()
                  << " from " << devInfo.address().toString().toStdString()
                  << ", expected " << AIRPODS_DATA_LENGTH << std::endl;
        return;
    }

    if(m_devices.find(devInfo.address()) == m_devices.end())
    {
        m_devices[devInfo.address()].reset(new DeviceBatteryInfo(devInfo.address(), AIRPODS_MODEL(data)));
        ui->devicesLayout->addWidget(m_devices[devInfo.address()].get());
    }

    ChargeStatus status(data.constData());
    m_devices[devInfo.address()]->updateStatus(status);
}

void MainWindow::bluetoothError(QBluetoothDeviceDiscoveryAgent::Error error)
{
    ui->mainLabel->setVisible(false);
    ui->errorLabel->setVisible(true);

    switch(error)
    {
        case QBluetoothDeviceDiscoveryAgent::NoError:
            ui->errorLabel->setText(QString("Bluetooth Error: No Error"));
            break;
        case QBluetoothDeviceDiscoveryAgent::InputOutputError:
            ui->errorLabel->setText(QString("Bluetooth Error: Error reading from bluetooth device"));
            break;
        case QBluetoothDeviceDiscoveryAgent::PoweredOffError:
            ui->errorLabel->setText(QString("Bluetooth Error: Bluetooth module is turned of or unavailable"));
            break;
        case QBluetoothDeviceDiscoveryAgent::InvalidBluetoothAdapterError:
            ui->errorLabel->setText(QString("Bluetooth Error: Bluetooth adapter error"));
            break;
        case QBluetoothDeviceDiscoveryAgent::UnsupportedPlatformError:
            ui->errorLabel->setText(QString("Bluetooth Error: Platform not supported"));
            break;
        case QBluetoothDeviceDiscoveryAgent::UnsupportedDiscoveryMethod:
            ui->errorLabel->setText(QString("Bluetooth Error: Low level energy device scan is not supported"));
            break;
        case QBluetoothDeviceDiscoveryAgent::UnknownError:
            ui->errorLabel->setText(QString("Bluetooth Error: Unknown error"));
            break;
    }

    m_restartTimer.start();
}

void MainWindow::bluetoothDiscoverFinished()
{
    ui->mainLabel->setText(QString("Scanning completed"));

    m_restartTimer.start();
}

void MainWindow::startScan()
{
    ui->mainLabel->setVisible(true);
    ui->errorLabel->setVisible(false);

    ui->mainLabel->setText(QString("Scanning for devices ..."));

    m_discoveryAgent.start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}
