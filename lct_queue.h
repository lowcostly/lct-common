/**********************************************************************
 * @copyright   Copyright (C), 2017
 * @file        lct_queue.h
 * @version     1.0
 * @date        May 23, 2017 6:02:31 PM
 * @author      wayfarerly@yahoo.com
 * @brief       TODO
 *********************************************************************/
#ifndef SRC_COMMON_LCT_QUEUE_H_
#define SRC_COMMON_LCT_QUEUE_H_


#include <queue>
#include <limits>
#include <mutex>
#include <condition_variable>

#include "lct_common_define.h"

template <typename T>
class CLctQueue final
{
private:
   typedef std::mutex                CLctMutex;
   typedef std::condition_variable   CLctCond;

private:
   typedef T       CObjectType;
   typedef T*      CPointerType;

public:
   /*********************************************
    * enWaitTime(milliseconds), enqueue:
    *      By default, it is infinite
    *      0, return immediately
    *      0 < #waitTime < m_infinite, means waiting Time
    *
    * deWaitTime(milliseconds), dequeue:
    *      By default, it is infinite
    *      0, return immediately
    *      0 < #waitTime < m_infinite, means waiting Time
    *
    * maxSize:
    *      By default, its size is infinite
    *      0, return immediately
    *      0 < #maxSize < m_infinite, means the max size
    *
    *********************************************/
   explicit CLctQueue();
   explicit CLctQueue(const std::size_t maxSize);
   explicit CLctQueue(const std::size_t enWaitTime, const std::size_t deWaitTime);
   explicit CLctQueue(const std::size_t maxSize, const std::size_t enWaitTime, const std::size_t deWaitTime);

   ~CLctQueue();

   DISALLOW_COPY_MOVE_OR_ASSIGN(CLctQueue);

public:
   LCT_ERR_CODE enqueue(const CObjectType&);
   LCT_ERR_CODE enqueue(CObjectType&&);
   LCT_ERR_CODE enqueueInBlock(const CObjectType&);
   LCT_ERR_CODE enqueueInBlock(CObjectType&&);
   LCT_ERR_CODE enqueueInTimeout(const CObjectType&, std::size_t waitingDuration = 0);
   LCT_ERR_CODE enqueueInTimeout(CObjectType&&, std::size_t waitingDuration = 0);

   LCT_ERR_CODE dequeue();
   LCT_ERR_CODE dequeue(CObjectType&);
   LCT_ERR_CODE dequeue(CObjectType&&);
   LCT_ERR_CODE dequeueInBlock(CObjectType&);
   LCT_ERR_CODE dequeueInBlock(CObjectType&&);
   LCT_ERR_CODE dequeueInTimeout(CObjectType&, std::size_t waitingDuration = 0);
   LCT_ERR_CODE dequeueInTimeout(CObjectType&&, std::size_t waitingDuration = 0);

   bool        full() const;
   bool        empty() const;
   std::size_t size()  const;
   void        notifyAll();
   void        notifyAllQuit();

private:
   bool        fullImpl() const;
   bool        emptyImpl() const;
   std::size_t sizeImpl()  const;  

private:
   bool                       m_quit = false;
   const std::size_t          m_maxSize;
   const std::size_t          m_defaultEnDuration; // milliseconds
   const std::size_t          m_defaultDeDuration; // milliseconds
   CLctCond                   m_cond;
   mutable CLctMutex          m_mutex;

   typedef typename std::queue<T> CLctQueueDataType;
   CLctQueueDataType          m_dataQueue;

public:
   constexpr static std::size_t SIZE_INFINITE = std::numeric_limits<std::size_t>::max();
   constexpr static std::size_t TIME_INFINITE = std::numeric_limits<std::size_t>::max();
};

#include "detail/lct_queue.hpp"


#endif /* SRC_COMMON_LCT_QUEUE_H_ */
