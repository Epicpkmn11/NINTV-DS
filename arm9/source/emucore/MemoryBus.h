
#ifndef MEMORYBUS_H
#define MEMORYBUS_H

#include <stdio.h>
#include <string.h>
#include "Memory.h"
#include "ROM.h"

extern UINT16 fast_memory[];

#define MAX_MAPPED_MEMORIES     15
#define MAX_OVERLAPPED_MEMORIES 3

/**
 * Emulates a 64K memory bus which may be composed of 8-bit or 16-bit memory units.
 *
 * @author Kyle Davis
 */
extern UINT16 r[8];

class MemoryBus
{
    public:
        MemoryBus();
        virtual ~MemoryBus();

        void reset();

        UINT16 peek(UINT16 location);
        inline UINT16 peek_fast(UINT16 location) {return readableMemorySpace[location][0]->peek(location);}
        //inline UINT16 peek_pc(void) {return readableMemorySpace[r[7]][0]->peek(r[7]);}
        inline UINT16 peek_pc(void) {return fast_memory[r[7]];}
        inline UINT16 peek_origPC(UINT16 location) 
        {
           if (readableMemorySpace[location])
           {
               if (readableMemorySpace[location][0])
                  return readableMemorySpace[location][0]->peek(location);
               else
                  return 0xFFFF;
           } else return 0xFFFF;
        }
        void poke(UINT16 location, UINT16 value);

        void addMemory(Memory* m);
        void removeMemory(Memory* m);
        void removeAll();

    private:
        Memory*     mappedMemories[MAX_MAPPED_MEMORIES];
        UINT16      mappedMemoryCount;
        UINT16*     writeableMemoryCounts;
        Memory***   writeableMemorySpace;
        UINT16*     readableMemoryCounts;
        Memory***   readableMemorySpace;
};

#endif
