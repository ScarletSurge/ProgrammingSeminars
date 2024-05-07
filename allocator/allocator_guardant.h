#ifndef INTERPRETERS_ALLOCATOR_GUARDANT_H
#define INTERPRETERS_ALLOCATOR_GUARDANT_H

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

void *allocator_guardant::allocate_with_guard(
    size_t value_size,
    size_t values_count) const
{
    allocator *target_allocator = get_allocator();
    return target_allocator == nullptr
           ? ::operator new(value_size * values_count)
           : target_allocator->allocate(value_size, values_count);
}

void allocator_guardant::deallocate_with_guard(
    void *at) const
{
    allocator *target_allocator = get_allocator();
    return target_allocator == nullptr
           ? ::operator delete(at)
           : target_allocator->deallocate(at);
}

#endif //INTERPRETERS_ALLOCATOR_GUARDANT_H