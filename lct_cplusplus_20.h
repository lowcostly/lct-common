/**********************************************************************
 * @copyright   Copyright (C), 2018
 * @file        lct_cplusplus_20.h
 * @version     1.0
 * @date        2019-09-23 23:32:46
 * @author      wayfarerly@yahoo.com
 * @brief       TODO
 *********************************************************************/
#ifndef SRC_COMMON_LCT_CPLUSPLUS_20_H_
#define SRC_COMMON_LCT_CPLUSPLUS_20_H_

#if __cplusplus <= 201703L

#ifdef __linux__
#include <endian.h>
#endif

namespace std
{
   enum class endian
   {
   #ifdef _WIN32
       little = 0,
       big    = 1,
       native = little
   #else
       little = __ORDER_LITTLE_ENDIAN__,
       big    = __ORDER_BIG_ENDIAN__,
       native = __BYTE_ORDER__
   #endif
   };
}

#endif

#endif /* SRC_COMMON_LCT_CPLUSPLUS_20_H_ */
