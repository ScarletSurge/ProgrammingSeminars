#ifndef PUKSRENJK_ALLOCATOR_BUDDIES_SYSTEM_H
#define PUKSRENJK_ALLOCATOR_BUDDIES_SYSTEM_H

#include "allocator.h"

class allocator_buddies_system final:
    public allocator
{

private:

    void *_trusted_memory;

public:

    [[nodiscard]] void *allocate(
        size_t value_size,
        size_t values_count) override;

    void deallocate(
        void *at) override;

public:

    // TODO: implement rule of 5 (except copy constructor and assignment operator)

public:

    // TODO: auxiliary operations section

};

#endif //PUKSRENJK_ALLOCATOR_BUDDIES_SYSTEM_H