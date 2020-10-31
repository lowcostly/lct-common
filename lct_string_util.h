/**********************************************************************
 * @copyright   Copyright (C), 2017
 * @file        lct_string_util.h
 * @version     1.0
 * @date        Jun 9, 2017 9:12:02 AM
 * @author      wayfarerly@yahoo.com
 * @brief       TODO
 *********************************************************************/
#ifndef SRC_COMMON_LCT_STRING_UTIL_H_
#define SRC_COMMON_LCT_STRING_UTIL_H_

#include <string>
#include <vector>
#include <initializer_list>

bool StartsWith(const char* str, const char* prefix);
bool StartsWith(const std::string& str, const std::string& prefix);

bool CheckSubstring(const std::string& str, const std::string& substr);

std::vector<std::string> Split(const std::string& str, const std::string& delim = " ");

std::string Trim(const std::string& str, const std::string& delc = " \t\r\n");

std::string Replace(const std::string& str, const char pattern, const char replacer);

void ToUpper(std::string& str);

void ToLower(std::string& str);

std::string ToUpperString(const std::string& str);

std::string ToLowerString(const std::string& str);

std::string MultiAddrs2Broker(const std::initializer_list<std::string>& hosts);

std::string MultiAddrs2Broker(const std::vector<std::string>& config);

std::string MultiAddrs2Broker(std::vector<std::string>&& config);

template <typename... Args>
std::string MultiAddrs2Broker(const Args&... hosts)
{
   return MultiAddrs2Broker({hosts...});
}


#endif /* SRC_COMMON_LCT_STRING_UTIL_H_ */
