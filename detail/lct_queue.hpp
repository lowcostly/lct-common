/**********************************************************************
 * @copyright   Copyright (C), 2017
 * @file        lct_queue.hpp
 * @version     1.0
 * @date        May 23, 2017 6:01:35 PM
 * @author      wayfarerly@yahoo.com
 * @brief       TODO
 *********************************************************************/
#ifndef SRC_COMMON_LCT_QUEUE_HPP_
#define SRC_COMMON_LCT_QUEUE_HPP_

template <typename T>
CLctQueue<T>::CLctQueue():
   CLctQueue(SIZE_INFINITE, TIME_INFINITE, TIME_INFINITE)
{
}

template <typename T>
CLctQueue<T>::CLctQueue(const std::size_t maxSize):
   CLctQueue(maxSize, TIME_INFINITE, TIME_INFINITE)
{
}

template <typename T>
CLctQueue<T>::CLctQueue(const std::size_t enWaitTime, const std::size_t deWaitTime):
   CLctQueue(SIZE_INFINITE, enWaitTime, deWaitTime)
{
}

template <typename T>
CLctQueue<T>::CLctQueue(const std::size_t maxSize, const std::size_t enWaitTime, const std::size_t deWaitTime):
   m_maxSize(maxSize),
   m_defaultEnDuration(enWaitTime),
   m_defaultDeDuration(enWaitTime)
{
}

template <typename T>
CLctQueue<T>::~CLctQueue()
{
}

template <typename T>
LCT_ERR_CODE CLctQueue<T>::enqueue(const CObjectType& obj)
{
   std::unique_lock<CLctMutex> guard(m_mutex);
   while (fullImpl()) {
      if (m_quit) {
         return LCT_SERVICE_DOWN;
      } 
      return LCT_OVERFLOW;
   }
   m_dataQueue.push(obj);
   m_cond.notify_all();
   return LCT_SUCCESS;
}

template <typename T>
LCT_ERR_CODE CLctQueue<T>::enqueue(CObjectType&& obj)
{
   std::unique_lock<CLctMutex> guard(m_mutex);

   while (fullImpl()) {
      if (m_quit) {
         return LCT_SERVICE_DOWN;
      } 
      return LCT_OVERFLOW;
   }
   m_dataQueue.push(std::move(obj));
   m_cond.notify_all();
   return LCT_SUCCESS;
}

template <typename T>
LCT_ERR_CODE CLctQueue<T>::enqueueInBlock(const CObjectType& obj)
{
   std::unique_lock<CLctMutex> guard(m_mutex);
   while (fullImpl()) {
      if (m_quit) {
         return LCT_SERVICE_DOWN;
      }
      m_cond.wait(guard);
   }
   m_dataQueue.push(obj);
   m_cond.notify_all();
   return LCT_SUCCESS;
}

template <typename T>
LCT_ERR_CODE CLctQueue<T>::enqueueInBlock(CObjectType&& obj)
{
   std::unique_lock<CLctMutex> guard(m_mutex);

   while (fullImpl()) {
      if (m_quit) {
         return LCT_SERVICE_DOWN;
      } 
      m_cond.wait(guard);
   }
   m_dataQueue.push(std::move(obj));
   m_cond.notify_all();
   return LCT_SUCCESS;
}

template <typename T>
LCT_ERR_CODE CLctQueue<T>::enqueueInTimeout(const CObjectType& obj, std::size_t waitingDuration)
{
   std::unique_lock<CLctMutex> guard(m_mutex);
   if (waitingDuration == 0) {
      waitingDuration = m_defaultEnDuration;
   }
   while (fullImpl()) {
      if (m_quit) {
         return LCT_SERVICE_DOWN;
      } else if (0 == waitingDuration) {
         return LCT_OVERFLOW;
      } else if (TIME_INFINITE == waitingDuration) {
         m_cond.wait(guard);
      } else {
         if (m_cond.wait_for(guard, std::chrono::milliseconds(waitingDuration)) == std::cv_status::timeout) {
            return LCT_TIMEOUT;
         }
      }
   }
   m_dataQueue.push(obj);
   m_cond.notify_all();
   return LCT_SUCCESS;
}

template <typename T>
LCT_ERR_CODE CLctQueue<T>::enqueueInTimeout(CObjectType&& obj, std::size_t waitingDuration)
{
   std::unique_lock<CLctMutex> guard(m_mutex);
   if (waitingDuration == 0) {
      waitingDuration = m_defaultEnDuration;
   }
   while (fullImpl()) {
      if (m_quit) {
         return LCT_SERVICE_DOWN;
      } else if (0 == waitingDuration) {
         return LCT_OVERFLOW;
      } else if (TIME_INFINITE == waitingDuration) {
         m_cond.wait(guard);
      } else {
         if (m_cond.wait_for(guard, std::chrono::milliseconds(waitingDuration)) == std::cv_status::timeout) {
            return LCT_TIMEOUT;
         }
      }
   }
   m_dataQueue.push(std::move(obj));
   m_cond.notify_all();
   return LCT_SUCCESS;
}

template <typename T>
LCT_ERR_CODE CLctQueue<T>::dequeue()
{
   std::unique_lock<CLctMutex> guard(m_mutex);
   while (emptyImpl()) {
      if (m_quit) {
         return LCT_SERVICE_DOWN;
      }
      return LCT_EMPTY_RECORD;
   }
   m_dataQueue.pop();
   m_cond.notify_all();
   return LCT_SUCCESS;
}

template <typename T>
LCT_ERR_CODE CLctQueue<T>::dequeue(CObjectType& obj)
{
   std::unique_lock<CLctMutex> guard(m_mutex);
   while (emptyImpl()) {
      if (m_quit) {
         return LCT_SERVICE_DOWN;
      }
      return LCT_EMPTY_RECORD;
   }
   obj = m_dataQueue.front();
   m_dataQueue.pop();
   m_cond.notify_all();
   return LCT_SUCCESS;
}

template <typename T>
LCT_ERR_CODE CLctQueue<T>::dequeue(CObjectType&& obj)
{
   std::unique_lock<CLctMutex> guard(m_mutex);
   while (emptyImpl()) {
      if (m_quit) {
         return LCT_SERVICE_DOWN;
      }
      return LCT_EMPTY_RECORD;
   }
   obj = std::move(m_dataQueue.front());
   m_dataQueue.pop();
   m_cond.notify_all();
   return LCT_SUCCESS;
}

template <typename T>
LCT_ERR_CODE CLctQueue<T>::dequeueInBlock(CObjectType& obj)
{
   std::unique_lock<CLctMutex> guard(m_mutex);
   while (emptyImpl()) {
      if (m_quit) {
         return LCT_SERVICE_DOWN;
      } 
      m_cond.wait(guard);
   }
   obj = m_dataQueue.front();
   m_dataQueue.pop();
   m_cond.notify_all();
   return LCT_SUCCESS;
}

template <typename T>
LCT_ERR_CODE CLctQueue<T>::dequeueInBlock(CObjectType&& obj)
{
   std::unique_lock<CLctMutex> guard(m_mutex);
   while (emptyImpl()) {
      if (m_quit) {
         return LCT_SERVICE_DOWN;
      } 
      m_cond.wait(guard);
   }
   obj = std::move(m_dataQueue.front());
   m_dataQueue.pop();
   m_cond.notify_all();
   return LCT_SUCCESS;
}

template <typename T>
LCT_ERR_CODE CLctQueue<T>::dequeueInTimeout(CObjectType& obj, std::size_t waitingDuration)
{
   std::unique_lock<CLctMutex> guard(m_mutex);
   if (waitingDuration == 0) {
      waitingDuration = m_defaultDeDuration;
   }
   while (emptyImpl()) {
      if (m_quit) {
         return LCT_SERVICE_DOWN;
      } else if (0 == waitingDuration) {
         return LCT_EMPTY_RECORD;
      } else if (TIME_INFINITE == waitingDuration) {
         m_cond.wait(guard);
      } else {
         if (m_cond.wait_for(guard, std::chrono::milliseconds(waitingDuration)) == std::cv_status::timeout) {
            return LCT_TIMEOUT;
         }
      }
   }
   obj = m_dataQueue.front();
   m_dataQueue.pop();
   m_cond.notify_all();
   return LCT_SUCCESS;
}

template <typename T>
LCT_ERR_CODE CLctQueue<T>::dequeueInTimeout(CObjectType&& obj, std::size_t waitingDuration)
{
   std::unique_lock<CLctMutex> guard(m_mutex);
   if (waitingDuration == 0) {
      waitingDuration = m_defaultDeDuration;
   }
   while (emptyImpl()) {
      if (m_quit) {
         return LCT_SERVICE_DOWN;
      } else if (0 == waitingDuration) {
         return LCT_EMPTY_RECORD;
      } else if (TIME_INFINITE == waitingDuration) {
         m_cond.wait(guard);
      } else {
         if (m_cond.wait_for(guard, std::chrono::milliseconds(waitingDuration)) == std::cv_status::timeout) {
            return LCT_TIMEOUT;
         }
      }
   }
   obj = std::move(m_dataQueue.front());
   m_dataQueue.pop();
   m_cond.notify_all();
   return LCT_SUCCESS;
}

template <typename T>
inline bool CLctQueue<T>::full() const
{
   std::unique_lock<CLctMutex> guard(m_mutex);
   return fullImpl();
}

template <typename T>
inline bool CLctQueue<T>::fullImpl() const
{
   return sizeImpl() >= m_maxSize;
}

template <typename T>
inline bool CLctQueue<T>::empty() const
{
   std::unique_lock<CLctMutex> guard(m_mutex);
   return emptyImpl();
}

template <typename T>
inline bool CLctQueue<T>::emptyImpl() const
{
   return m_dataQueue.empty();
}

template <typename T>
inline std::size_t CLctQueue<T>::size() const
{
   std::unique_lock<CLctMutex> guard(m_mutex);
   return sizeImpl();
}

template <typename T>
inline std::size_t CLctQueue<T>::sizeImpl() const
{
   return m_dataQueue.size();
}

template <typename T>
inline void CLctQueue<T>::notifyAll()
{
   std::unique_lock<CLctMutex> guard(m_mutex);
   m_cond.notify_all();
}

template <typename T>
inline void CLctQueue<T>::notifyAllQuit()
{
   m_quit = true;
   notifyAll();
}

#endif /* SRC_COMMON_LCT_QUEUE_HPP_ */
