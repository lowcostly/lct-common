/**********************************************************************
 * @copyright   Copyright (C), 2017
 * @file        lct_time_impl.inl
 * @version     1.0
 * @date        Sep 24, 2017 11:22:08 AM
 * @author      wayfarerly@yahoo.com
 * @brief       TODO
 *********************************************************************/
#ifndef SRC_COMMON_LCT_TIME_IMPL_INL_
#define SRC_COMMON_LCT_TIME_IMPL_INL_

inline LctTmType CLctTime::timePoint2Tm(const LctTimePointType& tmPoint, bool isUTC) const
{
#ifndef WIN32   
   LctTmType tstruct = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, nullptr};
   std::time_t val = LctClockType::to_time_t(tmPoint);
#else
   LctTmType tstruct = {0, 0, 0, 0, 0, 0, 0, 0, 0};
   time_t val = LctClockType::to_time_t(tmPoint);
#endif
   if (!isUTC) {
     val += m_timezoneGap;
   }
#ifndef WIN32   
   tstruct = *gmtime_r(&val, &tstruct);
#else
   gmtime_s(&tstruct, &val);
#endif
   return tstruct;
}

inline int64_t CLctTime::timeZoneGap() const
{
   return m_timezoneGap;
}

#endif /* SRC_COMMON_LCT_TIME_IMPL_INL_ */


