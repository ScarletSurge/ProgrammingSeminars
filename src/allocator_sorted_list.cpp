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

    // TODO:
    // 1. requested size overriding
    // 2. reevaluate (allocator meta first block address || previous block next pointer block
    // 3. асеевские приколы))0)0
}

void allocator_sorted_list::deallocate(
    void *at)
{
    throw not_implemented("void allocator_sorted_list::deallocate(void *)", "your code should be here...");
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