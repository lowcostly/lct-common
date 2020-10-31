/**********************************************************************
 * @copyright   Copyright (C), 2017
 * @file        lct_time.inl
 * @version     1.0
 * @date        Oct 12, 2017 2:58:12 PM
 * @author      wayfarerly@yahoo.com
 * @brief       TODO
 *********************************************************************/
#ifndef SRC_COMMON_LCT_TIME_INL_
#define SRC_COMMON_LCT_TIME_INL_

#include "lct_time_impl.h"

//milli seconds sice epoch
inline int64_t LctCurrentDateTimeValue()
{
   return std::chrono::duration_cast<LctTimeValueType>(LctClockType::now().time_since_epoch()).count();;
}

inline std::string LctFormatDateTime(const int64_t& millisecondsSinceEpoch)
{
   return LCT_TIME->formatDateTime(millisecondsSinceEpoch);
}

//@return: YYYY-MM-DD HH:MM:SS +8000 UTC
inline std::string LctFormatUtcDateTime(const int64_t& millisecondsSinceEpoch)
{
   return LCT_TIME->formatUtcDateTime(millisecondsSinceEpoch);
}

inline std::string LctFormatTime(const int64_t& millisecondsSinceEpoch)
{
   return LCT_TIME->formatTime(millisecondsSinceEpoch);
}

//@return: YYYYMMDDHHMMSSmmm
inline std::string LctFullDateTime(const int64_t& millisecondsSinceEpoch)
{
   return LCT_TIME->LctFullDateTime(millisecondsSinceEpoch);
}

inline const std::string LctCurrentDateTime()  //YYYY-MM-DD HH:MM:SS
{
   return LCT_TIME->currentDateTime();
}

inline const std::string LctCurrentTime()  //HH:MM:SS
{
   return LCT_TIME->currentTime();
}

inline const std::string LctCurrentDate()  //YYYYMMDD
{
   return LCT_TIME->currentDate();
}

inline const std::string LctCurrentDay()   //YYMMDD
{
   return LCT_TIME->currentDay();
}

//@return: YYYY-MM-DD HH:MM:SS +8000 UTC
inline const std::string LctCurrentUtcTime()
{
   return LCT_TIME->currentUtcTime();
}

//@return: YYYY-MM-DDTHH:MM:SSZ
inline const std::string LctCurrentRFC3339Time()
{
   return LCT_TIME->currentRFC3339Time();
}

//@argv:   YYYY-MM-DD HH:MM:SS.000000+8000
//@return: UTC seconds
inline int64_t LctUtcTime2Seconds(const std::string& time)
{
   return LCT_TIME->utcTime2Seconds(time);
}

inline int64_t LctLocal2UtcTimezoneGap()
{
   return LCT_TIME->timeZoneGap();
}

#endif /* SRC_COMMON_LCT_TIME_INL_ */


