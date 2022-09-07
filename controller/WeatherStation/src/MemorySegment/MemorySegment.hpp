
#ifndef MEMORY_SEGMENT_H
#define MEMORY_SEGMENT_H

#include <Logger.h>
#include <Vector.h>


template <typename T>
using MsVectorData = Vector<T*>;

template <typename T>
using MsVector = Vector<MsVectorData<T>*>;

template <typename T>
class MemorySegment
{
    public:
        MemorySegment(unsigned int segmentCount,unsigned int segmentSize);
        ~MemorySegment();
        void Add(T* data);
        void Clear(unsigned int segmentIndex);
        void ClearAll();
        MsVectorData<T>* GetSegment(unsigned int segmentIndex);
        unsigned int GetSegmentCount();
        unsigned int GetSegmentSize();
        bool HasValue();

    private:
        unsigned int segmentCount_;
        unsigned int segmentSize_;
        MsVector<T>* segments_ = new MsVector<T>();
};

template <typename T>
MemorySegment<T>::MemorySegment(unsigned int segmentCount,unsigned int segmentSize) 
{ 
    segmentCount_ = segmentCount;
    segmentSize_ = segmentSize;
    segments_->setStorage(new MsVectorData<T>*[segmentCount],segmentCount,0);

    for (unsigned int i = 0; i < segmentCount; i++)
    {
        segments_->at(i)->setStorage(new T*[segmentSize],segmentSize,0);
    }
}

template <typename T>
MemorySegment<T>::~MemorySegment() 
{
    ClearAll();
    delete[] segments_->data();
    delete segments_;
}

template <typename T>
void MemorySegment<T>::Add(T* data)
{
    for (unsigned int i = 0; i < segmentCount_; i++)
    {
        if (segments_->at(i)->size() < segmentSize_)
        {
            segments_->at(i)->push_back(data);
            return;
        }
    }
}

template <typename T>
void MemorySegment<T>::Clear(unsigned int segmentIndex)
{
    for (unsigned int j = 0; j < segmentSize_; j++)
    {
        delete segments_->at(segmentIndex)->at(j);
    }

    delete[] segments_->at(segmentIndex)->data();
    segments_->at(segmentIndex)->clear();
}

template <typename T>
void MemorySegment<T>::ClearAll()
{
    for (unsigned int i = 0; i < segmentCount_; i++)
    {
        Clear(i);
    }
}

template <typename T>
MsVectorData<T>* MemorySegment<T>::GetSegment(unsigned int segmentIndex)
{
    return segments_->at(segmentIndex);
}

template <typename T>
unsigned int MemorySegment<T>::GetSegmentCount()
{
    return segmentCount_;
}

template <typename T>
unsigned int MemorySegment<T>::GetSegmentSize()
{
    return segmentSize_;
}

template <typename T>
bool MemorySegment<T>::HasValue()
{
    for (unsigned int i = 0; i < segmentCount_; i++)
    {
        if (segments_->at(i)->size() > 0)
        {
            return true;
        }
    }

    return false;
}

#endif