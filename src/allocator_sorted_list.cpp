#include "../include/allocator_sorted_list.h"
#include "../include/not_implemented.h"

allocator_sorted_list::~allocator_sorted_list()
{
    deallocate_with_guard(_trusted_memory);
}

allocator_sorted_list::allocator_sorted_list(
    allocator_sorted_list &&other) noexcept:
        _trusted_memory(other._trusted_memory)
{
    other._trusted_memory = nullptr;
}

allocator_sorted_list &allocator_sorted_list::operator=(
    allocator_sorted_list &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    deallocate_with_guard(_trusted_memory);
    _trusted_memory = other._trusted_memory;
    other._trusted_memory = nullptr;

    return *this;
}

allocator_sorted_list::allocator_sorted_list(
    size_t space_size,
    allocator *parent_allocator,
    //logger *logger,
    allocator_with_fit_mode::fit_mode allocate_fit_mode)
{
    auto const target_size = get_metadata_size() + space_size;

    try
    {
        _trusted_memory = parent_allocator == nullptr
            ? ::operator new(target_size)
            : parent_allocator->allocate(target_size, 1);
    }
    catch (std::bad_alloc const &ex)
    {
        // TODO: logs
        throw;
    }

    get_memory_size() = space_size;
    get_parent_allocator() = parent_allocator;
    get_fit_mode() = allocate_fit_mode;
    // new (get_sync_object_ptr()) std::mutex;
    allocator::construct(get_sync_object_ptr());
    get_first_block_address() = &get_first_block_address() + 1;

    get_block_size(get_first_block_address()) = space_size - get_available_block_meta_size();
    get_next_available_block(get_first_block_address()) = nullptr;
}

[[nodiscard]] void *allocator_sorted_list::allocate(
    size_t value_size,
    size_t values_count)
{
    auto requested_size = value_size * values_count;

    void *target_previous_block = nullptr;
    void *target_current_block = nullptr;

    {
        void *previous_block = nullptr;
        void *current_block = get_first_block_address();
        auto fit_mode = get_fit_mode();

        while (current_block != nullptr)
        {
            if (requested_size <= get_block_size(current_block) &&
                (fit_mode == allocator_with_fit_mode::fit_mode::first_fit ||
                (fit_mode == allocator_with_fit_mode::fit_mode::the_best_fit && (target_current_block == nullptr ||
                    get_block_size(target_current_block) > get_block_size(current_block))) ||
                (fit_mode == allocator_with_fit_mode::fit_mode::the_worst_fit && (target_current_block == nullptr ||
                    get_block_size(target_current_block) < get_block_size(current_block)))))
            {
                target_previous_block = previous_block;
                target_current_block = current_block;

                if (fit_mode == allocator_with_fit_mode::fit_mode::first_fit)
                {
                    break;
                }
            }

            previous_block = current_block;
            current_block = get_next_available_block(current_block);
        }
    }

    if (target_current_block == nullptr)
    {
        // TODO: logs
        throw std::bad_alloc();
    }

    void *new_avail_block;
    auto block_remaining = get_block_size(target_current_block) - requested_size;

    if (block_remaining < get_available_block_meta_size())
    {
        requested_size += block_remaining;
        // requested_size = get_block_size(target_current_block);
        // TODO: logs

        (target_previous_block == nullptr
            ? get_first_block_address()
            : get_next_available_block(target_previous_block)) = get_next_available_block(target_current_block);
    }
    else
    {
        new_avail_block = (reinterpret_cast<unsigned char *>(target_current_block) + (get_block_size(target_current_block) - block_remaining));

        get_block_size(new_avail_block) = block_remaining;

        get_next_available_block(new_avail_block) = get_next_available_block(target_current_block);

        (target_previous_block == nullptr
         ? get_first_block_address()
         : get_next_available_block(target_previous_block)) = new_avail_block;
    }

    get_block_size(target_current_block) = requested_size;
    get_trusted_memory(target_current_block) = _trusted_memory;

    return reinterpret_cast<void *>(reinterpret_cast<unsigned char *>(target_current_block) + get_ancillary_block_meta_size());
}

void allocator_sorted_list::deallocate(
    void *at)
{
    auto left_bound = reinterpret_cast<void *>(reinterpret_cast<unsigned char *>(_trusted_memory) + get_metadata_size() + get_ancillary_block_meta_size());
    auto right_bound = reinterpret_cast<void *>(reinterpret_cast<unsigned char *>(_trusted_memory) + get_metadata_size() + get_memory_size());

    if (at == nullptr || at < left_bound || at > right_bound)
    {
        throw std::out_of_range("invalid block to deallocate address");
    }

    if (get_trusted_memory(at = reinterpret_cast<void *>(reinterpret_cast<unsigned char *>(at) - get_ancillary_block_meta_size())) != _trusted_memory)
    {
        throw std::logic_error("block to deallocate is not registered inside allocator instance");
    }


}

inline void allocator_sorted_list::set_fit_mode(
    allocator_with_fit_mode::fit_mode mode)
{
    get_fit_mode() = mode;
}

inline allocator *allocator_sorted_list::get_allocator() const
{
    return get_parent_allocator();
}

inline constexpr size_t allocator_sorted_list::get_metadata_size() noexcept
{
    return sizeof(size_t) + sizeof(allocator *) + sizeof(allocator_with_fit_mode::fit_mode) + sizeof(std::mutex) + sizeof(void *);
}

inline size_t &allocator_sorted_list::get_memory_size() const
{
    return *reinterpret_cast<size_t *>(_trusted_memory);
}

inline allocator *&allocator_sorted_list::get_parent_allocator() const
{
    return *reinterpret_cast<allocator **>(&get_memory_size() + 1);
}

inline allocator_with_fit_mode::fit_mode &allocator_sorted_list::get_fit_mode() const
{
    return *reinterpret_cast<allocator_with_fit_mode::fit_mode*>(&get_parent_allocator() + 1);
}

inline std::mutex *allocator_sorted_list::get_sync_object_ptr() const
{
    return reinterpret_cast<std::mutex *>(&get_fit_mode() + 1);
}

inline std::mutex &allocator_sorted_list::get_sync_object() const
{
    return *get_sync_object_ptr();
}

inline void *&allocator_sorted_list::get_first_block_address() const
{
    return *reinterpret_cast<void **>(get_sync_object_ptr() + 1);
}

inline constexpr size_t allocator_sorted_list::get_available_block_meta_size() noexcept
{
    return sizeof(size_t) + sizeof(void *);
}

inline constexpr size_t allocator_sorted_list::get_ancillary_block_meta_size() noexcept
{
    return get_available_block_meta_size();
}

inline size_t &allocator_sorted_list::get_block_size(
    void *block)
{
    return *reinterpret_cast<size_t *>(block);
}

inline void *&allocator_sorted_list::get_next_available_block(
    void *available_block)
{
    return *reinterpret_cast<void **>(&get_block_size(available_block) + 1);
}

inline void *&allocator_sorted_list::get_trusted_memory(
    void *ancillary_block)
{
    return get_next_available_block(ancillary_block);
}