/**********************************************************************
 * @copyright   Copyright (C), 2018
 * @file        lct_defer.h
 * @version     1.0
 * @date        2019-09-21 13:05:49
 * @author      wayfarerly@yahoo.com
 * @brief       TODO
 *********************************************************************/
#ifndef SRC_COMMON_LCT_DEFER_H_
#define SRC_COMMON_LCT_DEFER_H_

template <typename Func>
struct CDeferDeputy 
{
   CDeferDeputy(Func fn): m_fn(fn)
   {
   }

   ~CDeferDeputy() 
   {
      m_fn(); 
   }

private:
   Func m_fn;
};

template <typename Func>
CDeferDeputy<Func> deferCallable(Func fn) 
{
   return CDeferDeputy<Func>(fn);
}

#define PRIVATE_DEFER_1(x, y)    x##y
#define PRIVATE_DEFER_2(x, y)    PRIVATE_DEFER_1(x, y)
#define PRIVATE_DEFER_3(x)       PRIVATE_DEFER_2(x, __COUNTER__)

#define defer(code)              auto PRIVATE_DEFER_3(__defer__) = deferCallable([&](){code;})

#endif /* SRC_COMMON_LCT_DEFER_H_ */
