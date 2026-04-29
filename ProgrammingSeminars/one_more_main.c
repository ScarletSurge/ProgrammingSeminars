#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

#pragma warning(disable: 4996)

#define DEREFERENCING_NULL_POINTER 1
#define MEMORY_ALLOCATION_ERROR 2

typedef struct key_value_pair
{
	char* key;
	char* value;
} kvp;

typedef struct key_value_pair_array
{
	kvp *values;
	size_t values_count;
	size_t values_capacity;
} kvp_array;

void free_all_07_03_26(
	void* to_free,
	...)
{
	// va_list va_start va_arg va_end
	va_list va;
	
	//va = (va_list)&to_free;
	va_start(va, to_free);

	while (to_free != NULL)
	{
		free(to_free);
		to_free = va_arg(va, void*);
	}

	va_end(va);
}

typedef struct Node
{
	// double a, b;
	// ... // initialization of a and b
	// a == b with eps =>
	// fabsl(a - b) < eps
	// <=> - partial ordering
	// == != > < >= <=
	int data;
	struct Node** subtrees;
	size_t subtrees_count;
} Node, *pNode;

// valgrind
int insert_node(
	Node **root,
	int (*comparer)(int const*, int const*),
	int value_to_insert)
{
	if (root == NULL)
	{
		return DEREFERENCING_NULL_POINTER;
	}

	if (*root == NULL)
	{
		if (!(*root = (Node*)malloc(sizeof(Node))))
		{
			return MEMORY_ALLOCATION_ERROR;
		}

		(*root)->data = value_to_insert;
		(*root)->subtrees = 2;
		if (!((*root)->subtrees = (Node **)malloc(sizeof(Node*) * 2)))
		{
			free_all_07_03_26(root, NULL);

			return MEMORY_ALLOCATION_ERROR;
		}
		
		(*root)->subtrees[0] = NULL;
		(*root)->subtrees[1] = NULL;

		//free_all(root, root->subtrees[0], root->subtrees[1], NULL);

		return 0;
	}
	// TODO: You can do it!

	return NULL;
}

// TODO: rework prototype
int int_comparer(
	int const *left,
	int const *right)
{
	return *left - *right;
}

int code_from_26_03_07(
	int argc,
	char* argv[])
{
	Node* root = NULL;

	insert_node(&root, int_comparer, 10);

	printf(root == NULL ? "Root is NULL" : "Root was initialized");

	return 0;
}

int handle_file(
	char const* path,
	kvp_array *result)
{
	kvp* temporary;
	FILE* fIn;
	kvp_array res;
	char c, c_ = ' ';
	char key_buf[BUFSIZ], * wb = key_buf;
	char value_buf[BUFSIZ];

	if ((res.values = (kvp*)malloc((res.values_count = 0) + (res.values_capacity = 16) * sizeof(kvp))) == NULL)
	{
		return 1;
	}

	// components of word: {a-zA-z0-9}
	fIn = fopen(path, "r");
	//
	// fIn = fopen("punjk.srenjk", "r");

	// errno - EVIL

	if (fIn == NULL)
	{
		// printf("(9(9(99");
		// TODO: файл не открылся((9(9
		free(res.values);
		return -1;
	}

	// new -> delete
	// new[] -> delete[]
	// malloc -> delete - BAN! UB

	int reading_key = 1;
	while (!feof(fIn))
	{
		c = fgetc(fIn);

		if (isalnum(c))
		{
			// int y;
			// int x = 10;
			// if (y = (x += 10))
			// {
			// 	printf("x == %d, y == %d// \n", x, y);
			// }

			*wb++ = c;
			// wb++;
		}
		else if (isalnum(c_))
		{
			*wb = '\0';
			wb = reading_key
				? value_buf
				: key_buf;

			if (reading_key = !reading_key)
			{
				// key and value has been read into buffers
				if (res.values_capacity == res.values_count)
				{
					if (!(res.values = (kvp*)realloc(res.values, res.values_capacity << 1)))
					{

					}
				}
			}

			// TODO: handle word
			// printf("\"%s\"\n", words_buf);
		}

		c_ = c;
	}

	fclose(fIn);

	*result = res;
	return 0;

	// result = &res; - BRJED
}

int code_from_26_03_14(
	int argc,
	char* argv[])
{
	kvp_array read_data;
	handle_file("puksrenjk.txt", &read_data);

	return 0;
}

int main52(
	int argc,
	char *argv[]
	/*, char* env[] */)
{
	// return code_from_26_03_07(argc, argv);
	return code_from_26_03_14(argc, argv);
}