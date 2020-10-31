/**********************************************************************
 * @copyright   Copyright (C), 2017
 * @file        lct_time_impl.h
 * @version     1.0
 * @date        Sep 24, 2017 11:22:08 AM
 * @author      wayfarerly@yahoo.com
 * @brief       TODO
 *********************************************************************/
#ifndef SRC_COMMON_LCT_TIME_IMPL_H_
#define SRC_COMMON_LCT_TIME_IMPL_H_

#include "lct_common_define.h"
#include "lct_singleton.h"
#include <chrono>
#include "lct_time_impl.h"
#ifdef WIN32
#include "lct_strptime.h"
#endif

typedef std::chrono::system_clock              LctClockType;
typedef std::chrono::time_point<LctClockType>  LctTimePointType;
typedef std::chrono::milliseconds              LctTimeValueType;
typedef struct tm                              LctTmType;

class CLctTime final: public CLctSingleton<CLctTime>
{
public:
   //milli seconds sice epoch
   int64_t currentDateTimeValue() const;

   //YYYY-MM-DD HH:MM:SS
   std::string formatDateTime(const int64_t& millisecondsSinceEpoch) const;   

   //@return: YYYY-MM-DD HH:MM:SS +8000 UTC
   std::string formatUtcDateTime(const int64_t& millisecondsSinceEpoch) const;

   //HH:MM:SS
   std::string formatTime(const int64_t& millisecondsSinceEpoch) const;    

   //YYYYMMDDHHMMSSmmm
   std::string LctFullDateTime(const int64_t& millisecondsSinceEpoch) const;  

   //YYYY-MM-DD
   std::string formatedDate() const;  

   //YYYY-MM-DD HH:MM:SS
   std::string currentDateTime() const;  

   //HH:MM:SS
   std::string currentTime() const;     

   //YYYYMMDD
   std::string currentDate() const;     

   //YYMMDD
   std::string currentDay() const;      

   //@return: YYYY-MM-DD HH:MM:SS +0000 UTC
   const std::string currentUtcTime() const;

   //@return: YYYY-MM-DDTHH:MM:SSZ
   const std::string currentRFC3339Time();

   //from YYYY-MM-DD HH:MM:SS to YYYY-MM-DD
   std::string formatedTime2Date(const std::string& time) const;  

   //from YYYY-MM-DD HH:MM:SS to YYYYMMDD
   int32_t formatedTime2IntDate(const std::string& time) const;   

   //from YYYY-MM-DD HH:MM:SS +8000 to UTC seconds
   int64_t utcTime2Seconds(const std::string& time) const;

   LctTmType timePoint2Tm(const LctTimePointType& tmPoint, bool isUTC = false) const;

   //@return:seconds
   int64_t timeZoneGap() const;
private:
   LCT_ERR_CODE initialize() override;

#ifdef WIN32
   template <typename ClassType>
#endif
   friend class CLctSingleton;
private:
   int64_t     m_timezoneGap  = 0;
};

#define LCT_TIME CLctTime::instance()

#include "lct_time_impl.inl"

#endif /* SRC_COMMON_LCT_TIME_IMPL_H_ */
