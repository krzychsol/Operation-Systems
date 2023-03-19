#ifndef SO_LIBRARY_H
#define SO_LIBRARY_H

typedef struct wc_array
{
    char** data;
    int size;
    int current_size;
} wc_array;

wc_array array_init(unsigned int size);

int wc_execute(char* file,struct wc_array *array);

char* show_index(int index,struct wc_array *array);

int delete_index(int index,struct wc_array *array);

int destroy_array(struct wc_array *array);

#endif