/**********************************************************************
 * @copyright   Copyright (C), 2020
 * @file        lct_spinlock.h
 * @version     1.0
 * @date        2020-02-12 23:14:16
 * @author      wayfarerly@yahoo.com
 * @brief       TODO
 *********************************************************************/
#ifndef SRC_COMMON_LCT_SPINLOCK_H_
#define SRC_COMMON_LCT_SPINLOCK_H_

#include <atomic>
#include "lct_common_define.h"

class CLctSpinLock final
{
protected:
   void lock();
   void unlock();

   friend class CLctLockGuard;

public:
   CLctSpinLock();
   ~CLctSpinLock();

   DISALLOW_COPY_MOVE_OR_ASSIGN(CLctSpinLock);
   
private:
   std::atomic_flag m_locked = ATOMIC_FLAG_INIT;
};

class CLctLockGuard final
{
public:
   explicit CLctLockGuard(CLctSpinLock& lk);
   ~CLctLockGuard();

   DISALLOW_COPY_MOVE_OR_ASSIGN(CLctLockGuard);

private:
   CLctSpinLock&  m_lock;
};

#endif /* SRC_COMMON_LCT_SPINLOCK_H_ */
