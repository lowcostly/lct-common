/**********************************************************************
 * @copyright   Copyright (C), 2018
 * @file        lct_binary_util.h
 * @version     1.0
 * @date        2019-09-23 23:44:29
 * @author      wayfarerly@yahoo.com
 * @brief       TODO
 *********************************************************************/

#ifndef SRC_COMMON_LCT_BINARY_UTIL_H_
#define SRC_COMMON_LCT_BINARY_UTIL_H_

#include "lct_common_define.h"
#include "lct_cplusplus_17.h"
#include <vector>

LCT_ERR_CODE Bytes2UInt32(uint32_t& value, const std::vector<std::byte>& bytes, const std::size_t startIndex = 0);

LCT_ERR_CODE Bytes2Int32(int32_t& value, const std::vector<std::byte>& bytes, const std::size_t startIndex = 0);

LCT_ERR_CODE Bytes2Float32(float& value, const std::vector<std::byte>& bytes, const std::size_t startIndex = 0);

std::vector<uint32_t> Bytes2UInt32Array(const std::vector<std::byte>& bytes, const std::size_t startIndex = 0);

std::vector<float> Bytes2Float32Array(const std::vector<std::byte>& bytes);
std::vector<float> Bytes2Float32Array(const std::vector<std::byte>& bytes, const std::size_t startIndex, const std::size_t length);

std::vector<std::byte> UInt32ToBytes(const uint32_t value);

std::vector<std::byte> Int32ToBytes(const int32_t value);

std::vector<std::byte> Float32ToBytes(const float value);

std::vector<std::byte> UInt32Array2Bytes(const std::vector<uint32_t>& values);

std::vector<std::byte> Float32Array2Bytes(const std::vector<float>& values);

#include "detail/lct_binary_util.hpp"

#endif /* SRC_COMMON_LCT_BINARY_UTIL_H_ */
