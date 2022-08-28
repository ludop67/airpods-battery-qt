#include "devicebatteryinfo.h"
#include "ui_devicebatteryinfo.h"

DeviceBatteryInfo::DeviceBatteryInfo(QBluetoothAddress addr, char model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceBatteryInfo)
{
    m_timer.setInterval(TIMER_INTERVAL);
    connect(&m_timer, &QTimer::timeout, this, &DeviceBatteryInfo::timerTimeout);

    ui->setupUi(this);

    ui->deviceLabel->setText(QString("Device %1, %2").arg(addr.toString(), modelName(model)));
}

DeviceBatteryInfo::~DeviceBatteryInfo()
{
    delete ui;
}

void DeviceBatteryInfo::updateStatus(const ChargeStatus &status)
{
    m_lastSeenSeconds = 0;
    m_timer.start();
    updateTimerText();

    const char leftBatteryLevel = status.leftRightReversed
            ? AIRPODS_BATTERY_PERCENT(status.rightLevel)
            : AIRPODS_BATTERY_PERCENT(status.leftLevel);
    const char rightBatteryLevel = status.leftRightReversed
            ? AIRPODS_BATTERY_PERCENT(status.leftLevel)
            : AIRPODS_BATTERY_PERCENT(status.rightLevel);
    const char caseBatteryLevel = AIRPODS_BATTERY_PERCENT(status.caseLevel);

    const bool leftCharging = status.leftRightReversed ? status.rightCharging : status.leftCharging,
               rightCharging = status.leftRightReversed ? status.leftCharging : status.rightCharging;

    QString unknown("Unknown"),
            charging("Charging %1"),
            level("%1%");

    QString leftLevelText = leftBatteryLevel < 0 ? unknown : level.arg(QString::number(leftBatteryLevel)),
            rightLevelText = rightBatteryLevel < 0 ? unknown : level.arg(QString::number(rightBatteryLevel)),
            caseLevelText = caseBatteryLevel < 0 ? unknown : level.arg(QString::number(caseBatteryLevel));
    ui->leftText->setText(leftCharging ? charging.arg(leftLevelText) : leftLevelText);
    ui->rightText->setText(rightCharging ? charging.arg(rightLevelText) : rightLevelText);
    ui->caseText->setText(status.caseCharging ? charging.arg(caseLevelText) : caseLevelText);

    ui->leftProgress->setValue(leftBatteryLevel < 0 ? 0 : leftBatteryLevel);
    ui->rightProgress->setValue(rightBatteryLevel < 0 ? 0 : rightBatteryLevel);
    ui->caseProgress->setValue(caseBatteryLevel < 0 ? 0 : caseBatteryLevel);
}

void DeviceBatteryInfo::timerTimeout()
{
    m_lastSeenSeconds += TIMER_INTERVAL / 1000;
    updateTimerText();
}

QString DeviceBatteryInfo::modelName(char model)
{
    switch(model)
    {
        case AIRPODS_MODEL_1:
            return QString("AirPods 1st generation");
        case AIRPODS_MODEL_2:
            return QString("AirPods 2nd generation");
        case AIRPODS_MODEL_3:
            return QString("AirPods 3rd generation");
        case AIRPODS_MODEL_MAX:
            return QString("AirPods Max");
        case AIRPODS_MODEL_PRO:
            return QString("AirPods Pro");
        default:
            return QString("Unknown model (id: %1)").arg(QString::number(model));
    }
}

void DeviceBatteryInfo::updateTimerText()
{
    ui->timeLabel->setText(QString("%1s ago").arg(QString::number(m_lastSeenSeconds)));
}
