#ifndef PROGRAMMINGSEMINARS_ALLOCATOR_SORTED_LIST_H
#define PROGRAMMINGSEMINARS_ALLOCATOR_SORTED_LIST_H

#include <iostream>
#include <mutex>

#include "allocator.h"
#include "allocator_guardant.h"
#include "allocator_with_fit_mode.h"
#include "logger.h"
#include "logger_guardant.h"

class allocator_sorted_list final:
    private allocator_guardant,
    public allocator_with_fit_mode,
    private logger_guardant
{

private:

    void *_trusted_memory;

public:

    ~allocator_sorted_list() override;

    allocator_sorted_list(
        allocator_sorted_list const &other) = delete;

    allocator_sorted_list &operator=(
        allocator_sorted_list const &other) = delete;

    allocator_sorted_list(
        allocator_sorted_list &&other) noexcept;

    allocator_sorted_list &operator=(
        allocator_sorted_list &&other) noexcept;

public:

    explicit allocator_sorted_list(
        size_t space_size,
        allocator *parent_allocator = nullptr,
        logger *logger = nullptr,
        allocator_with_fit_mode::fit_mode allocate_fit_mode = allocator_with_fit_mode::fit_mode::first_fit);

public:

    [[nodiscard]] void *allocate(
        size_t value_size,
        size_t values_count) override;

    void deallocate(
        void *at) override;

public:

    inline void set_fit_mode(
        allocator_with_fit_mode::fit_mode mode) override;

private:

    inline allocator *get_allocator() const override;

private:

    inline logger *get_logger() const override;

private:

    inline static constexpr size_t get_metadata_size() noexcept;

    inline size_t &get_memory_size() const;

    inline allocator *&get_parent_allocator() const;

    inline logger *& get_log() const;

    inline allocator_with_fit_mode::fit_mode &get_fit_mode() const;

    inline std::mutex *get_sync_object_ptr() const;

    inline std::mutex &get_sync_object() const;

    inline void *& get_first_block_address() const;

private:

    inline static constexpr size_t get_available_block_meta_size() noexcept;

    inline static constexpr size_t get_ancillary_block_meta_size() noexcept;

    inline size_t &get_block_size(
        void *block);

    inline void *&get_next_available_block(
        void *available_block);

    inline void *&get_trusted_memory(
        void *ancillary_block);

};

#endif //PROGRAMMINGSEMINARS_ALLOCATOR_SORTED_LIST_H