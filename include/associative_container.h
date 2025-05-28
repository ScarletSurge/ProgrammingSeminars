#ifndef COURSE1_CPP_RGU_ASSOCIATIVE_CONTAINER_H
#define COURSE1_CPP_RGU_ASSOCIATIVE_CONTAINER_H

template<
    typename tkey,
    typename tvalue>
class associative_container
{

public:

    struct key_value_pair final
    {

    public:

        tkey key;
        tvalue value;

    };

    struct key_value_ptr_pair
    {

    public:

        tkey key;
        tvalue *value_ptr;

    };

public:

    // TODO
    struct associative_container_iterator
    {

    public:

    };

public:

    virtual ~associative_container() noexcept = default;

public:

    virtual void insert(
        tkey const &key,
        tvalue &&value) = 0;

    virtual tvalue const &obtain(
        tkey const &key) = 0;

    virtual tvalue dispose( // RVO/NRVO
        tkey const &key) = 0;

};

#endif //COURSE1_CPP_RGU_ASSOCIATIVE_CONTAINER_H