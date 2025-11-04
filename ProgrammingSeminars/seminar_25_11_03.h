#ifndef SEMINAR_25_11_03
#define SEMINAR_25_11_03

#include <stdio.h>

#include "dynamic_array.h"

int seminar_25_11_03(
	int argc,
	char* argv[])
{
	dynamic_array instance;
	initialize_dynamic_array(&instance);
	insert_by_index_into_dynamic_array(&instance, (void const *)0x1, 0);
	insert_by_index_into_dynamic_array(&instance, (void const *)0x2, 1);
	insert_by_index_into_dynamic_array(&instance, (void const *)0x3, 2);
	insert_by_index_into_dynamic_array(&instance, (void const *)0x4, 0);
	insert_by_index_into_dynamic_array(&instance, (void const *)0x5, 1);
	insert_by_index_into_dynamic_array(&instance, (void const *)0x6, 1);
	destroy_dynamic_array(&instance);

	return 0;
}

#endif