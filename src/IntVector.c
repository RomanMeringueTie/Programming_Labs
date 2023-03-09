#include "IntVector.h"
#include <string.h>

IntVector *int_vector_new(size_t initial_capacity)
{
	IntVector *v = NULL;
	v = malloc(sizeof(*v));
	if (!v)
		return NULL;
	v->data = calloc(initial_capacity, sizeof(int));
	if (!v->data)
	{
		free(v);
		return NULL;
	}
	v->capacity = initial_capacity;
	return v;
}

IntVector *int_vector_copy(const IntVector *v)
{
	IntVector *copy = NULL;
	copy = malloc(sizeof(*v));
	if (!copy)
		return NULL;
	copy->capacity = int_vector_get_capacity(v);
	copy->data = calloc(int_vector_get_capacity(copy), sizeof(int));
	if (!copy->data)
	{
		free((IntVector *)v);
		return NULL;
	}
	memmove(copy->data, v->data, int_vector_get_capacity(copy) * sizeof(int));
	return copy;
}

void int_vector_free(IntVector *v)
{
	free(v->data);
	free(v);
}

int int_vector_get_item(const IntVector *v, size_t index)
{
	int item = v->data[index];
	return item;
}

void int_vector_set_item(IntVector *v, size_t index, int item)
{
	v->data[index] = item;
}

size_t int_vector_get_size(const IntVector *v)
{
	size_t size = 0;
	for (int i = 0; i < int_vector_get_capacity(v); i++)
	{
		if (v->data[i] != 0)
			size++;
	}
	return size;
}

size_t int_vector_get_capacity(const IntVector *v)
{
	return v->capacity;
}

int int_vector_push_back(IntVector *v, int item)
{
	if (int_vector_get_size(v) < int_vector_get_capacity(v))
		v->data[(int_vector_get_size(v))] = item;
	else
	{
		v->capacity *= 2;
		v->data = realloc(v->data, int_vector_get_capacity(v) * sizeof(int));
		if (!v->data)
		{
			free(v);
			return -1;
		}
		v->data[(int_vector_get_size(v))] = item;
	}
	if (v->data[int_vector_get_size(v) - 1] == item)
		return 0;
	else
		return -1;
}

void int_vector_pop_back(IntVector *v)
{
	if (int_vector_get_size(v) != 0)
		v->data[int_vector_get_size(v) - 1] = 0;
}

int int_vector_shrink_to_fit(IntVector *v)
{
	v->capacity = int_vector_get_size(v);
	v->data = realloc(v->data, int_vector_get_capacity(v) * sizeof(int));
	if (!v->data)
	{
		free(v);
		return -1;
	}
	if (int_vector_get_capacity(v) == int_vector_get_size(v))
		return 0;
	else
		return -1;
}

int int_vector_resize(IntVector *v, size_t new_size)
{
	size_t old_size = int_vector_get_size(v);
	v->size = new_size;
	if (new_size > old_size)
	{
		for (int i = old_size; i < new_size; i++)
			v->data[i] = 0;
	}
	else
	{
		for (int i = new_size; i < old_size; i++)
			v->data[i] = 0;
	}
	if (int_vector_get_size(v) == new_size)
		return 0;
	else
		return -1;
}

int int_vector_reserve(IntVector *v, size_t new_capacity)
{
	v->data = realloc(v->data, new_capacity * sizeof(int));
	if (!v->data)
	{
		free(v);
		return -1;
	}
	v->capacity = new_capacity;
	return 0;
}