/**********************************************************************
 * @copyright   Copyright (C), 2018
 * @file        lct_heap.h
 * @version     1.0
 * @date        2019-10-28 09:39:03
 * @author      wayfarerly@yahoo.com
 * @brief       TODO
 *********************************************************************/

#ifndef SRC_COMMON_LCT_HEAP_H_
#define SRC_COMMON_LCT_HEAP_H_

#include <vector>
#include <limits>
#include <mutex>

#include "lct_common_define.h"

template <typename T>
class CLctHeap final
{
private:
   typedef std::mutex                CLctHeapMutex;
   typedef std::condition_variable   CLctCond;

private:
   typedef T       CObjectType;
   typedef T*      CPointerType;

public:
   explicit CLctHeap();
   explicit CLctHeap(const std::size_t defaultCapacity = 1024);

   ~CLctHeap();

   DISALLOW_COPY_MOVE_OR_ASSIGN(CLctHeap);

public:
   LCT_ERR_CODE push(const CObjectType&);
   LCT_ERR_CODE push(CObjectType&&);

   LCT_ERR_CODE pop(CObjectType&);
   LCT_ERR_CODE pop(CObjectType&&);

   LCT_ERR_CODE peek(CObjectType&) const;
   LCT_ERR_CODE readjust();

   bool        empty() const;
   std::size_t size()  const;

private:
   mutable CLctHeapMutex      m_mutex;

   typedef typename std::vector<T> CLctHeapDataContainerType;
   CLctHeapDataContainerType  m_dataContainer;
};

#include "detail/lct_heap.hpp"


#endif /* SRC_COMMON_LCT_HEAP_H_ */

