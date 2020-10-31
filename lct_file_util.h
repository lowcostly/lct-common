/**********************************************************************
 * @copyright   Copyright (C), 2017
 * @file        lct_file_util.h
 * @version     1.0
 * @date        Jun 9, 2017 9:13:08 AM
 * @author      wayfarerly@yahoo.com
 * @brief       TODO
 *********************************************************************/
#ifndef SRC_COMMON_LCT_FILE_UTIL_H_
#define SRC_COMMON_LCT_FILE_UTIL_H_

#include <cstddef>
#include <cstdio>
#include <string>

#ifndef __APPLE__
size_t FileSize(FILE *f);
#endif

bool FileSize(const std::string& fileName);

bool FileExists(const std::string& fileName);


#endif /* SRC_COMMON_LCT_FILE_UTIL_H_ */
