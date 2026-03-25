#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

class priority_queue
{

public:

	virtual ~priority_queue() noexcept = default;

public:

	virtual void insert(
		int priority,
		char const *value) = 0;

	virtual char *remove_max() = 0;

	virtual char const *get_max() = 0;

};

#endif
