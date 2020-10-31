/**********************************************************************
 * @copyright   Copyright (C), 2017
 * @file        lct_thread_pool_impl.h
 * @version     1.0
 * @date        May 23, 2017 6:03:22 PM
 * @author      wayfarerly@yahoo.com
 * @brief       TODO
 *********************************************************************/
#ifndef SRC_COMMON_LCT_THREAD_POOL_IMPL_H_
#define SRC_COMMON_LCT_THREAD_POOL_IMPL_H_

#include <vector>
#include <future>

#include "lct_common_define.h"
#include "lct_queue.h"

class CLctThreadpoolImpl
{
public:
   template<typename Callable, typename... Args>
   LCT_ERR_CODE emplaceTask(Callable&& func, Args&&... vargs);

   LCT_ERR_CODE start();
   LCT_ERR_CODE shutdown();
   std::size_t size() const
   {
      return m_threadCount;
   }

private:
   bool                          m_runningFlag;
   std::size_t                   m_threadCount;
   std::vector<std::thread>      m_workers;

   typedef std::function<void()> CLctThreadTask;
   CLctQueue<CLctThreadTask>     m_tasksQueue;

private:
   explicit CLctThreadpoolImpl(const std::size_t);
   ~CLctThreadpoolImpl();

   DISALLOW_COPY_MOVE_OR_ASSIGN(CLctThreadpoolImpl);

   friend class CLctThreadpool;
};


#include "lct_thread_pool_impl.hpp"

#endif /* SRC_COMMON_LCT_THREAD_POOL_IMPL_H_ */
