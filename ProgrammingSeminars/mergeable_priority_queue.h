#ifndef MERGEABLE_PRIORITY_QUEUE_H
#define MERGEABLE_PRIORITY_QUEUE_H

#include "priority_queue.h"

class mergeable_priority_queue:
	public priority_queue
{

public:

	virtual void merge(
		mergeable_priority_queue *to_merge_from) = 0;

	virtual mergeable_priority_queue *meld(
		mergeable_priority_queue const *to_meld_with) const = 0;

};

#endif