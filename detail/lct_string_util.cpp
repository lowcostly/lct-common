/**********************************************************************
 * @copyright   Copyright (C), 2017
 * @file        lct_string_util.cpp
 * @version     1.0
 * @date        Jun 9, 2017 9:12:42 AM
 * @author      wayfarerly@yahoo.com
 * @brief       TODO
 *********************************************************************/
#ifndef SRC_COMMON_LCT_STRING_UTIL_CPP_
#define SRC_COMMON_LCT_STRING_UTIL_CPP_

#include <locale>
#include <algorithm>
#include <sstream>
#include "lct_string_util.h"

bool StartsWith(const char* str, const char* prefix)
{
   if ((nullptr == str) || (nullptr == prefix)) {
      return false;
   }
   return StartsWith(std::string(str), std::string(prefix));
}

bool StartsWith(const std::string& str, const std::string& prefix) 
{
   return (str.size() >= prefix.size()) && (str.compare(0, prefix.size(), prefix) == 0);
}

bool CheckSubstring(const std::string& str, const std::string& substr)
{
   return str.find(substr) != std::string::npos;
}

std::vector<std::string> Split(const std::string& str, const std::string& delim)
{
   std::vector<std::string> parsed;
   std::string::size_type pos = 0;
   while (true) {
      const std::string::size_type colon = str.find(delim, pos);
      if (colon == std::string::npos) {
         parsed.push_back(str.substr(pos));
         break;
      } else {
         parsed.push_back(str.substr(pos, colon - pos));
         pos = colon + delim.size();
      }
   }
   return parsed;
}

std::string Trim(const std::string& str, const std::string& delc)
{
   const size_t pos = str.find_first_not_of(delc);
   if (std::string::npos == pos) {
      return "";
   }

   return str.substr(pos, str.find_last_not_of(delc) - pos + 1);
}

std::string Replace(const std::string& str, const char pattern, const char replacer)
{
   std::string result(str);
   size_t pos = str.find_first_of(pattern);
   while (str.npos != pos) {
      result.at(pos) = replacer;
      pos = str.find_first_of(pattern, pos + 1);
   }
   return result;
}

void ToUpper(std::string& str)
{
   std::for_each(str.begin(), str.end(), [](char & c) {
      c = std::toupper(c);
   });
}

void ToLower(std::string& str)
{
   std::for_each(str.begin(), str.end(), [](char & c) {
      c = std::tolower(c);
   });
}

std::string ToUpperString(const std::string& str)
{
   std::string copy(str);
   ToUpper(copy);
   return copy;
}

std::string ToLowerString(const std::string& str)
{
   std::string copy(str);
   ToLower(copy);
   return copy;
}

std::string MultiAddrs2Broker(const std::initializer_list<std::string>& hosts)
{
   std::stringstream ss;
   for (const auto& i: hosts) {
      ss << i << ",";
   }
   if (hosts.size() > 0) {
      ss.unget();
   }
   
   return ss.str();
}


std::string MultiAddrs2Broker(const std::vector<std::string>& config)
{
   std::stringstream ss;
   for (auto itRe = config.cbegin(); itRe != config.cend(); ++itRe) {
      ss << *itRe << ",";
   }
   if (config.size() > 0) {
      ss.unget();
   }

   return ss.str();
}

std::string MultiAddrs2Broker(std::vector<std::string>&& config)
{
   std::stringstream ss;
   for (auto it = config.begin(); it != config.end(); ++it) {
      ss << std::move(*it) << ",";
   }
   if (config.size() > 0) {
      ss.unget();
   }

   return ss.str();
}

#endif /* SRC_COMMON_LCT_STRING_UTIL_CPP_ */
