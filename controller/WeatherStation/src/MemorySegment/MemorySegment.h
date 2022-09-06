
#ifndef MEMORY_SEGMENT_H
#define MEMORY_SEGMENT_H

#include <Logger.h>
#include <Vector.h>

template <typename T>
class MemorySegment
{
    public:
        MemorySegment(unsigned int segmentCount,unsigned int segmentSize);
        ~MemorySegment();
        void Add(T* data);

    private:
        unsigned int segmentCount_;
        unsigned int segmentSize_;
        Vector<Vector<T*>> segments_;
};

#endif