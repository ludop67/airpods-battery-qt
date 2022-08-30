#include "chargestatus.h"

ChargeStatus::ChargeStatus(bool leftCharging, bool rightCharging, bool caseCharging,
                           char leftLevel, char rightLevel, char caseLevel, bool leftRightReversed)
    : leftRightReversed(leftRightReversed),
      leftCharging(leftCharging), rightCharging(rightCharging), caseCharging(caseCharging),
      leftLevel(leftLevel), rightLevel(rightLevel), caseLevel(caseLevel)
{ }

ChargeStatus::ChargeStatus(const char data[AIRPODS_DATA_LENGTH])
    : ChargeStatus(AIRPODS_CHARGING_STATUS(data) & AIRPODS_CHARGING_LEFT,
                   AIRPODS_CHARGING_STATUS(data) & AIRPODS_CHARGING_RIGHT,
                   AIRPODS_CHARGING_STATUS(data) & AIRPODS_CHARGING_CASE,
                   AIRPODS_BATTERY_LEFT(data), AIRPODS_BATTERY_RIGHT(data), AIRPODS_BATTERY_CASE(data),
                   AIRPODS_REVERSED(data))
{ }
