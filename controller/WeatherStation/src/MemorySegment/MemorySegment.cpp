#include "MemorySegment.h"

template <typename T>
MemorySegment<T>::MemorySegment(unsigned int segmentCount,unsigned int segmentSize) 
{ 
    segmentCount_ = segmentCount;
    segmentSize_ = segmentSize;
    segments_.setStorage(new Vector<T*>[segmentCount]);

    for (unsigned int i = 0; i < segmentCount; i++)
    {
        segments_[i].setStorage(new T*[segmentSize]);
    }
}

template <typename T>
MemorySegment<T>::~MemorySegment() 
{
    for (unsigned int i = 0; i < segmentCount_; i++)
    {
        delete[] segments_[i].data();
    }
    delete[] segments_.data();
}

template <typename T>
void MemorySegment<T>::Add(T* data)
{
    for (unsigned int i = 0; i < segmentCount_; i++)
    {
        if (segments_[i].size() < segmentSize_)
        {
            segments_[i].push_back(data);
            return;
        }
    }
}


