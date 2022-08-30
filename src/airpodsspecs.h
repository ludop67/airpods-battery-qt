#ifndef AIRPODSSPECS_H
#define AIRPODSSPECS_H

/** Helpers to extract 4-byte values from bytes */
#define BYTE_HI(b) (((b) >> 4) & 0xF)
#define BYTE_LO(b) ((b) & 0xF)

/** AirPods technical specifications, taken from https://github.com/delphiki/AirStatus */

/** Minimum RSSI to obtain beacon */
constexpr int MIN_RSSI = -60;
/** Manufacturer id */
constexpr int AIRPODS_MANUFACTURER = 76;
/** Expected length of the beacon data */
constexpr int AIRPODS_DATA_LENGTH = 27;

/** Model identifier */
#define AIRPODS_MODEL(data) BYTE_LO((data)[3])

/** Are left and right reversed in usage */
#define AIRPODS_REVERSED(data) ((data)[5] & 0x20)

/** Battery level of the different elements */
#define AIRPODS_BATTERY_LEFT(data)    BYTE_LO((data)[6])
#define AIRPODS_BATTERY_RIGHT(data)   BYTE_HI((data)[6])
#define AIRPODS_BATTERY_CASE(data)    BYTE_LO((data)[7])

/** Convert battery level value to percentage value */
#define AIRPODS_BATTERY_PERCENT(level) ((level) == 10 ? 100 : ((level) < 10 ? (level) * 10 + 5 : -1))

/** Charging status of the different elements */
#define AIRPODS_CHARGING_STATUS(data) BYTE_HI((data)[7])
#define AIRPODS_CHARGING_RIGHT 0x1
#define AIRPODS_CHARGING_LEFT  0x2
#define AIRPODS_CHARGING_CASE  0x4

/** Identifier associated to the different models */
constexpr int AIRPODS_MODEL_1 = 2,
    AIRPODS_MODEL_2 = 15,
    AIRPODS_MODEL_3 = 3,
    AIRPODS_MODEL_MAX = 10,
    AIRPODS_MODEL_PRO = 14;


#endif // AIRPODSSPECS_H
