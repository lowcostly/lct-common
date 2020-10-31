/**********************************************************************
 * @copyright   Copyright (C), 2018
 * @file        lct_binary_util.hpp
 * @version     1.0
 * @date        2019-09-24 00:18:29
 * @author      wayfarerly@yahoo.com
 * @brief       TODO
 *********************************************************************/

#ifndef SRC_COMMON_LCT_BINARY_UTIL_HPP_
#define SRC_COMMON_LCT_BINARY_UTIL_HPP_

#include <vector>
#include "lct_cplusplus_17.h"
#include "lct_cplusplus_20.h"
#include "lct_error_code.h"

template <std::endian> 
class BinaryConverter
{
public:

};

constexpr static std::size_t bits4Byte   = 8;
constexpr static std::size_t bytes4Float = 4;

template <> 
class BinaryConverter<std::endian::little>
{
private:
      union FloatBytes 
      { 
         float     floatVal; 
         std::byte bytes[sizeof(float)]; 
      };

public:
   static uint32_t Bytes2UInt32(const std::vector<std::byte>& bytes, const std::size_t startIndex) 
   {
      uint32_t value  = static_cast<uint32_t>(bytes[startIndex]);
               value |= static_cast<uint32_t>(bytes[startIndex + 1]) << 8; 
               value |= static_cast<uint32_t>(bytes[startIndex + 2]) << 16;
               value |= static_cast<uint32_t>(bytes[startIndex + 3]) << 24;

      return value;
   }

   static float Bytes2Float32(const std::vector<std::byte>& bytes, const std::size_t startIndex) 
   {
      FloatBytes fb;

      fb.bytes[0] = bytes[startIndex];
      fb.bytes[1] = bytes[startIndex + 1];
      fb.bytes[2] = bytes[startIndex + 2];
      fb.bytes[3] = bytes[startIndex + 3];

      return fb.floatVal;
   }

   static std::vector<uint32_t> Bytes2UInt32Array(const std::vector<std::byte>& bytes, const std::size_t startIndex) 
   {
      const std::size_t size = bytes.size()/bytes4Float;

      std::vector<uint32_t> values;
      values.reserve(size);

      for (std::size_t i = startIndex; i < bytes.size();) {
         values.push_back(Bytes2UInt32(bytes, i));
         i += bytes4Float;
      }

      return values;
   }

   static std::vector<float> Bytes2Float32Array(const std::vector<std::byte>& bytes) 
   {
      return Bytes2Float32Array(bytes, 0, bytes.size());
   }

   static std::vector<float> Bytes2Float32Array(const std::vector<std::byte>& bytes, const std::size_t startIndex, const std::size_t length) 
   {
      const std::size_t limit = startIndex + length;
      const std::size_t size  = length / bytes4Float;

      std::vector<float> values;
      values.reserve(size);

      for (std::size_t i = startIndex; i < limit;) {
         values.push_back(Bytes2Float32(bytes, i));
         i += bytes4Float;
      }

      return values;
   }

   static std::vector<std::byte> UInt32ToBytes(const uint32_t value)
   {
      std::vector<std::byte> blob(4);
      blob[0] = static_cast<std::byte>(static_cast<uint32_t>(value      ) & 0xFF);
      blob[1] = static_cast<std::byte>(static_cast<uint32_t>(value >> 8 ) & 0xFF);
      blob[2] = static_cast<std::byte>(static_cast<uint32_t>(value >> 16) & 0xFF);
      blob[3] = static_cast<std::byte>(static_cast<uint32_t>(value >> 24) & 0xFF);

      return blob;
   }

   static std::vector<std::byte> Float32ToBytes(const float value)
   {
      FloatBytes fb;
      fb.floatVal = value;

      std::vector<std::byte> blob(4);
      blob[0] = fb.bytes[0];
      blob[1] = fb.bytes[1];
      blob[2] = fb.bytes[2];
      blob[3] = fb.bytes[3];

      return blob;
   }

   static std::vector<std::byte> UInt32Array2Bytes(const std::vector<uint32_t>& values)
   {
      const std::size_t size = values.size() * 4;
      std::vector<std::byte> blobs;
      blobs.reserve(size);

      for (auto itRe = values.cbegin(); itRe != values.cend(); ++itRe) {
         const uint32_t cur = *itRe;
         auto temp = UInt32ToBytes(cur);
         blobs.insert(blobs.end(), temp.begin(), temp.end());
      }

      return blobs; 
   }

   static std::vector<std::byte> Float32Array2Bytes(const std::vector<float>& values)
   {
      const std::size_t size = values.size() * 4;
      std::vector<std::byte> blobs;
      blobs.reserve(size);

      for (auto itRe = values.cbegin(); itRe != values.cend(); ++itRe) {
         const float cur = *itRe;
         auto temp = Float32ToBytes(cur);
         blobs.insert(blobs.end(), temp.begin(), temp.end());
      }

      return blobs; 
   }
};

template <> 
class BinaryConverter<std::endian::big>;


#endif /* SRC_COMMON_LCT_BINARY_UTIL_HPP_ */
