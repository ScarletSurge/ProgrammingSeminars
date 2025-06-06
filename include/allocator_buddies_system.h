#ifndef PUKSRENJK_ALLOCATOR_BUDDIES_SYSTEM_H
#define PUKSRENJK_ALLOCATOR_BUDDIES_SYSTEM_H

#include "allocator_with_fit_mode.h"
//#include "logger.h"
#include <mutex>
#include <cmath>

class allocator_buddies_system final:
    public allocator
{

    bool const free_block = true;
    bool const occupied_block = false;

private:

    void *_trusted_memory;

public:

    explicit allocator_buddies_system(
        size_t space_size_power_of_two,
        allocator *parent_allocator = nullptr,
        //logger *logger = nullptr,
        allocator_with_fit_mode::fit_mode allocate_fit_mode = allocator_with_fit_mode::fit_mode::first_fit);

public:

    [[nodiscard]] void *allocate(
        size_t value_size,
        size_t values_count) override
    {
        int additional_block_size_for_Kirill = 52;
        auto requested_size = value_size * values_count + additional_block_size_for_Kirill;
        auto current_block = get_first_available_block();
        void *previous_block = nullptr;

        void *previous_to_target_block = nullptr;
        void *target_block = nullptr;
        void *next_to_target_block = nullptr;

        while (current_block != nullptr)
        {
            if ((1 << get_block_size_power_of_2(current_block)) >= requested_size)
            {
                // TODO: прикрутить fit modes, Trufanova Anastasija
                previous_to_target_block = previous_block;
                target_block = current_block;
                next_to_target_block = get_next_available_block(current_block);
            }

            previous_block = current_block;
            current_block = get_next_available_block(current_block);
        }

        if (target_block == nullptr)
        {
            // TODO: logs
            throw std::bad_alloc();
        }

        auto target_block_size_power_of_2 = get_block_size_power_of_2(target_block);
        auto target_block_size = 1 << target_block_size_power_of_2;

        while (requested_size <= (target_block_size >>= 1))
        {
            set_block_size_and_is_ancillary(target_block, target_block_size_power_of_2 - 1, free_block);

            auto target_block_half_buddy = get_buddy(target_block);

            set_block_size_and_is_ancillary(target_block_half_buddy, target_block_size_power_of_2 - 1, free_block);

            get_next_available_block(target_block_half_buddy) = get_next_available_block(target_block);
            get_next_available_block(target_block) = target_block_half_buddy;

            if (next_to_target_block != nullptr)
            {
                get_previous_available_block(next_to_target_block) = target_block_half_buddy;
            }
            get_previous_available_block(target_block_half_buddy) = target_block;
        }

        if (get_next_available_block(target_block) != nullptr)
        {
            get_previous_available_block(get_next_available_block(target_block)) = get_previous_available_block(target_block);
        }

        if (get_previous_available_block(target_block) != nullptr)
        {
            get_next_available_block(get_previous_available_block(target_block)) = get_next_available_block(target_block);
        }
        else
        {
            get_first_available_block() = get_next_available_block(target_block);
        }

        get_block_trusted_memory(target_block) = _trusted_memory;
        set_block_size_and_is_ancillary(target_block, get_block_size_power_of_2(target_block), occupied_block);

        return reinterpret_cast<void *>(reinterpret_cast<unsigned char *>(target_block) + sizeof(unsigned char) + sizeof(void *));
    }

    void deallocate(
        void *at) override;

public:

    // TODO: implement rule of 5 (except copy constructor and assignment operator)

public:

    void *get_buddy(
        void *block) const;

    size_t get_block_size_power_of_2(
        void const *block) const;

    bool is_block_ancillary(
        void const *block) const;

    void set_block_size_and_is_ancillary(
        void *block,
        size_t block_size_power_of_2,
        bool is_ancillary);

    void *convert_from_global(
        void *global_address) const
    {
        return reinterpret_cast<void *>(reinterpret_cast<unsigned char *>(global_address) - (reinterpret_cast<unsigned char *>(_trusted_memory) + get_meta_size()));
    }

    void *convert_to_global(
        void *local_address) const
    {
        return reinterpret_cast<void *>(reinterpret_cast<unsigned char *> (local_address) + reinterpret_cast<unsigned long long>(_trusted_memory) + get_meta_size());
    }

    inline static constexpr int get_meta_size()
    {
        return sizeof(unsigned char) + sizeof(allocator *)
        + /*sizeof(logger *) + */ sizeof(allocator_with_fit_mode::fit_mode) + sizeof(std::mutex)
               + sizeof(void *);
    }

    inline static constexpr size_t get_free_block_meta_size()
    {
        return sizeof(unsigned char) + sizeof(void *) * 2;
    }

    inline static constexpr int get_block_size_power_of_2_shift()
    {
        return static_cast<int>(std::floor(std::log2(get_free_block_meta_size()))) + 1;
    }

    inline void *&get_next_available_block(
        void *block)
    {
        return *(&get_previous_available_block(block) + 1);
    }

    inline void *&get_previous_available_block(
        void *block)
    {
        return *reinterpret_cast<void **>(reinterpret_cast<unsigned char *>(block) + sizeof(unsigned char));
    }

    inline void *&get_block_trusted_memory(
        void *block)
    {
        return *reinterpret_cast<void **>(reinterpret_cast<unsigned char *>(block) + sizeof(unsigned char));
    }

    inline void *&get_first_available_block()
    {
        // TODO: this is not correct, San Sanych (который Spitler) - You must fix it!!1!1
        return *reinterpret_cast<void **>(reinterpret_cast<unsigned char *>(_trusted_memory) + 52);
    }

};

#endif //PUKSRENJK_ALLOCATOR_BUDDIES_SYSTEM_H