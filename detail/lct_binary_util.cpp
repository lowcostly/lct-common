/**********************************************************************
 * @copyright   Copyright (C), 2018
 * @file        lct_binary_util.cpp
 * @version     1.0
 * @date        2019-09-26 23:21:06
 * @author      wayfarerly@yahoo.com
 * @brief       TODO
 *********************************************************************/

#include "lct_binary_util.h"

LCT_ERR_CODE Bytes2UInt32(uint32_t& value, const std::vector<std::byte>& bytes, const std::size_t startIndex)
{
   if (bytes.size() < (startIndex + sizeof(uint32_t))) {
      return LCT_INVALID_PARAM;
   }

   value = BinaryConverter<std::endian::native>::Bytes2UInt32(bytes, startIndex);
   
   return LCT_SUCCESS;
}

LCT_ERR_CODE Bytes2Int32(int32_t& value, const std::vector<std::byte>& bytes, const std::size_t startIndex)
{
   uint32_t temp = static_cast<uint32_t>(value);
   LCT_ERR_CODE errCOde = Bytes2UInt32(temp, bytes, startIndex);
   if (LCT_SUCCESS != errCOde) {
      return errCOde;
   }
   value = static_cast<int32_t>(temp);

   return errCOde;
}

LCT_ERR_CODE Bytes2Float32(float& value, const std::vector<std::byte>& bytes, const std::size_t startIndex)
{
   if (bytes.size() < (startIndex + sizeof(float))) {
      return LCT_INVALID_PARAM;
   }

   value = BinaryConverter<std::endian::native>::Bytes2Float32(bytes, startIndex);
   
   return LCT_SUCCESS;
}

std::vector<uint32_t> Bytes2UInt32Array(const std::vector<std::byte>& bytes, const std::size_t startIndex)
{
   return BinaryConverter<std::endian::native>::Bytes2UInt32Array(bytes, startIndex);
}

std::vector<float> Bytes2Float32Array(const std::vector<std::byte>& bytes)
{
   return Bytes2Float32Array(bytes, 0, bytes.size());
}

std::vector<float> Bytes2Float32Array(const std::vector<std::byte>& bytes, const std::size_t startIndex, const std::size_t length)
{
   return BinaryConverter<std::endian::native>::Bytes2Float32Array(bytes, startIndex, length);
}

std::vector<std::byte> UInt32ToBytes(const uint32_t value)
{
   return BinaryConverter<std::endian::native>::UInt32ToBytes(value);
}

std::vector<std::byte> Int32ToBytes(const int32_t value)
{
   return BinaryConverter<std::endian::native>::UInt32ToBytes(static_cast<uint32_t>(value));
}

std::vector<std::byte> Float32ToBytes(const float value)
{
   return BinaryConverter<std::endian::native>::Float32ToBytes(value);
}

std::vector<std::byte> UInt32Array2Bytes(const std::vector<uint32_t>& values)
{
   return BinaryConverter<std::endian::native>::UInt32Array2Bytes(values);
}

std::vector<std::byte> Float32Array2Bytes(const std::vector<float>& values)
{
   return BinaryConverter<std::endian::native>::Float32Array2Bytes(values);
}

