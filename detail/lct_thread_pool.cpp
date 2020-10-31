/**********************************************************************
 * @copyright   Copyright (C), 2017
 * @file        lct_thread_pool.cpp
 * @version     1.0
 * @date        May 23, 2017 6:06:02 PM
 * @author      wayfarerly@yahoo.com
 * @brief       TODO
 *********************************************************************/

#include "lct_thread_pool.h"

CLctThreadpool::CLctThreadpool()
{
}

CLctThreadpool::~CLctThreadpool()
{
   shutdown();
}

LCT_ERR_CODE CLctThreadpool::init(const std::size_t threadCount)
{
   if (m_isRunning || (m_threadpoolImplPtr != nullptr)) {
      return LCT_FAIL;
   }

   if (threadCount == 0) {
      m_threadCount = std::thread::hardware_concurrency();
   } else {
      m_threadCount = threadCount;
   }

   try {
      m_threadpoolImplPtr = new CLctThreadpoolImpl(m_threadCount);
   } catch (const std::exception& e) {
      return LCT_EXCEPTION;
   } catch (...) {
      return LCT_UNEXPECTED;
   }

   return LCT_SUCCESS;
}

LCT_ERR_CODE CLctThreadpool::start()
{
   if (m_isRunning || (m_threadpoolImplPtr == nullptr)) {
      return LCT_FAIL;
   }

   LCT_ERR_CODE errCode = LCT_SUCCESS;

   try {
      errCode = m_threadpoolImplPtr->start();
   } catch (const std::exception& e) {
      return LCT_EXCEPTION;
   } catch (...) {
      return LCT_UNEXPECTED;
   }

   m_isRunning = (LCT_SUCCESS == errCode);

   return errCode;
}

LCT_ERR_CODE CLctThreadpool::shutdown()
{
   if (!m_isRunning) {
      return LCT_FAIL;
   }

   LCT_ERR_CODE errCode = LCT_SUCCESS;

   if (m_threadpoolImplPtr != nullptr) {
      errCode = m_threadpoolImplPtr->shutdown();
      delete m_threadpoolImplPtr;
      m_threadpoolImplPtr = nullptr;
   }

   m_isRunning = false;
   return errCode;
}

std::size_t CLctThreadpool::size() const
{
   if (!m_isRunning || (m_threadpoolImplPtr == nullptr)) {
      return 0;
   }
   return m_threadpoolImplPtr->size();
}
