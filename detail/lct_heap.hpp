/**********************************************************************
 * @copyright   Copyright (C), 2018
 * @file        lct_heap.hpp
 * @version     1.0
 * @date        2019-10-28 09:49:17
 * @author      wayfarerly@yahoo.com
 * @brief       TODO
 *********************************************************************/

#ifndef SRC_COMMON_LCT_HEAP_HPP_
#define SRC_COMMON_LCT_HEAP_HPP_

template <typename T>
CLctHeap<T>::CLctHeap(const std::size_t defaultCapacity /* = 1024 */)
{
}

template <typename T>
CLctHeap<T>::~CLctHeap()
{
}

template <typename T>
LCT_ERR_CODE CLctHeap<T>::push(const CObjectType&)
{
   LCT_ERR_CODE errCode = LCT_SUCCESS;
   return errCode;
}

template <typename T>
LCT_ERR_CODE CLctHeap<T>::push(CObjectType&&)
{
   LCT_ERR_CODE errCode = LCT_SUCCESS;
   return errCode;
}

template <typename T>
LCT_ERR_CODE CLctHeap<T>::pop(CObjectType&);
{
   LCT_ERR_CODE errCode = LCT_SUCCESS;
   return errCode;
}

template <typename T>
LCT_ERR_CODE CLctHeap<T>::pop(CObjectType&&)
{
   LCT_ERR_CODE errCode = LCT_SUCCESS;
   return errCode;
}

template <typename T>
LCT_ERR_CODE CLctHeap<T>::peek(CObjectType&) const
{
   LCT_ERR_CODE errCode = LCT_SUCCESS;
   return errCode;
}

template <typename T>
inline bool CLctHeap<T>::empty() const
{
   return m_dataContainer.empty();
}

template <typename T>
inline std::size_t CLctHeap<T>::size() const
{
   return m_dataContainer.size();
}

#endif /* SRC_COMMON_LCT_HEAP_HPP_ */
