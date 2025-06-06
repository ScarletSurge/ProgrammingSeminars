#include "../include/allocator_buddies_system.h"

void *allocator_buddies_system::get_buddy(
    void *block) const
{
    auto block_local = convert_from_global(block);

    size_t block_size = 1 << get_block_size_power_of_2(block_local);

    block_local = reinterpret_cast<void *>(reinterpret_cast<long long>(block_local) ^ block_size);

    return convert_to_global(block_local);
}

size_t allocator_buddies_system::get_block_size_power_of_2(
    void const *block) const
{
    return static_cast<size_t>((*reinterpret_cast<unsigned char const *>(block) & 127) + get_block_size_power_of_2_shift());
}

bool allocator_buddies_system::is_block_ancillary(
    void const *block) const
{
    return static_cast<bool>(*reinterpret_cast<unsigned char const *>(block) >> 7);
}

void allocator_buddies_system::set_block_size_and_is_ancillary(
    void *block,
    size_t block_size_power_of_2,
    bool is_ancillary)
{
    unsigned char meta_part = ((is_ancillary ? 1 : 0) << 7) | ((block_size_power_of_2 & 127) - get_block_size_power_of_2_shift());
}