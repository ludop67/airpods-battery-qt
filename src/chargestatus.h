#ifndef CHARGESTATUS_H
#define CHARGESTATUS_H

#include "airpodsspecs.h"

struct ChargeStatus
{
    ChargeStatus(bool leftCharging, bool rightCharging, bool caseCharging,
                    char leftLevel, char rightLevel, char caseLevel, bool leftRightReversed);

    ChargeStatus(const char data[AIRPODS_DATA_LENGTH]);

    bool leftRightReversed;
    bool leftCharging, rightCharging, caseCharging;
    char leftLevel, rightLevel, caseLevel;
};

#endif // CHARGESTATUS_H
