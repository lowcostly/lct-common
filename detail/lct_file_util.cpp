/**********************************************************************
 * @copyright   Copyright (C), 2017
 * @file        lct_file_util.cpp
 * @version     1.0
 * @date        Jun 9, 2017 9:15:08 AM
 * @author      wayfarerly@yahoo.com
 * @brief       TODO
 *********************************************************************/

#include "lct_file_util.h"

#include <sys/stat.h>

#ifndef __APPLE__
size_t FileSize(FILE *f)
{
   if (f == nullptr) {
      return 0;
   }
#if !defined(WIN32) && !defined(_WIN32) && !defined(_WIN64) && !defined(WIN64)
   int fd = fileno(f);
   struct stat64 st;
   if (fstat64(fd, &st) == 0) {
#else
   int fd = _fileno(f);
   struct _stat64 st;
   if (_fstat64(fd, &st) == 0) {
#endif
      return static_cast<size_t>(st.st_size);
   } else {
      return 0;
   }
}
#endif

bool FileSize(const std::string& fileName)
{
#if !defined(WIN32) && !defined(_WIN32) && !defined(_WIN64)
   struct stat st;
   if (stat(fileName.c_str(), &st) == 0) {
#else
   struct _stat64 st;
   if (_stat64(fileName.c_str(), &st) == 0) {
#endif
      return static_cast<size_t>(st.st_size);
   } else {
      return 0;
   } 
}

bool FileExists(const std::string& fileName)
{
   struct stat buffer;
   return (stat(fileName.c_str(), &buffer) == 0);
}
