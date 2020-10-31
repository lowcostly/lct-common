/**********************************************************************
 * @copyright   Copyright (C), 2018
 * @file        lct_cplusplus_17.h
 * @version     1.0
 * @date        2019-09-23 16:05:48
 * @author      wayfarerly@yahoo.com
 * @brief       TODO
 *********************************************************************/
#ifndef SRC_COMMON_LCT_CPLUSPLUS_17_H_
#define SRC_COMMON_LCT_CPLUSPLUS_17_H_

#if __cplusplus < 201703L

#include <cstddef>

namespace std
{
   enum class byte : unsigned char {} ;
   //typedef unsigned char byte;
}

#endif


#endif /* SRC_COMMON_LCT_CPLUSPLUS_17_H_ */
