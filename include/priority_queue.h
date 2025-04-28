#ifndef PUKSRENJK_PRIORITY_QUEUE_H
#define PUKSRENJK_PRIORITY_QUEUE_H

class priority_queue
{

public:

    virtual ~priority_queue() noexcept = default;

public:

    virtual void insert(
        int priority,
        char const *value) = 0;

    virtual char const *remove_max() = 0;

    virtual char const *obtain_max() = 0;

public:

    virtual priority_queue *merge(
        priority_queue *with) = 0;

    virtual priority_queue *meld(
        priority_queue const *with) const = 0;

};

#endif //PUKSRENJK_PRIORITY_QUEUE_H