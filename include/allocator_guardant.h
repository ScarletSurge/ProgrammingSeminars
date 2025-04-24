#ifndef PROGRAMMINGSEMINARS_ALLOCATOR_GUARDANT_H
#define PROGRAMMINGSEMINARS_ALLOCATOR_GUARDANT_H

#include "allocator.h"

class allocator_guardant
{

public:

    virtual ~allocator_guardant() noexcept = default;

public:

    [[nodiscard]] void *allocate_with_guard(
        size_t value_size,
        size_t values_count = 1) const;

    void deallocate_with_guard(
        void *at) const;

public:

    [[nodiscard]] inline virtual allocator *get_allocator() const = 0;

};

#endif //PROGRAMMINGSEMINARS_ALLOCATOR_GUARDANT_H