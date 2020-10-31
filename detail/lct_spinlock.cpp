/**********************************************************************
 * @copyright   Copyright (C), 2020
 * @file        lct_spinlock.cpp
 * @version     1.0
 * @date        2020-02-12 23:17:05
 * @author      wayfarerly@yahoo.com
 * @brief       TODO
 *********************************************************************/

#include "lct_spinlock.h"

CLctSpinLock::CLctSpinLock()
{
}

CLctSpinLock::~CLctSpinLock()
{
}

void CLctSpinLock::lock()
{
   while (m_locked.test_and_set(std::memory_order_acquire)) { 
      ; 
   }
}

void CLctSpinLock::unlock()
{
   m_locked.clear(std::memory_order_release);
}

CLctLockGuard::CLctLockGuard(CLctSpinLock& lk): m_lock(lk)
{
   m_lock.lock();
}

CLctLockGuard::~CLctLockGuard()
{
   m_lock.unlock();
}

