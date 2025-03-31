#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 10

#define list(T)                                                                                                        \
    typedef void (*T##_free_fn)(T item);                                                                               \
    typedef int (*T##_int_property_fn)(T item);                                                                        \
    typedef char *(*T##_string_property_fn)(T item);                                                                   \
    typedef void (*T##_print_fn)(T item);                                                                              \
                                                                                                                       \
    struct T##s                                                                                                        \
    {                                                                                                                  \
        T *buffer;                                                                                                     \
        int size;                                                                                                      \
        int count;                                                                                                     \
        T##_print_fn print_fn;                                                                                         \
        T##_free_fn free_fn;                                                                                           \
    };                                                                                                                 \
                                                                                                                       \
    typedef struct T##s *T##s;                                                                                         \
                                                                                                                       \
    T##s T##s_create(T##_print_fn print_fn, T##_free_fn free_fn)                                                       \
    {                                                                                                                  \
        T##s list = malloc(sizeof(struct T##s));                                                                       \
        list->buffer = malloc(INITIAL_SIZE * sizeof(T));                                                               \
        list->size = INITIAL_SIZE;                                                                                     \
        list->count = 0;                                                                                               \
        list->print_fn = print_fn;                                                                                     \
        list->free_fn = free_fn;                                                                                       \
                                                                                                                       \
        return list;                                                                                                   \
    }                                                                                                                  \
                                                                                                                       \
    int T##s_get_count(T##s list)                                                                                      \
    {                                                                                                                  \
        return list->count;                                                                                            \
    }                                                                                                                  \
                                                                                                                       \
    void T##s_push(T##s list, T item)                                                                                  \
    {                                                                                                                  \
        if (list->count == list->size)                                                                                 \
        {                                                                                                              \
            list->size *= 2;                                                                                           \
            list->buffer = realloc(list->buffer, list->size * sizeof(T));                                              \
        }                                                                                                              \
                                                                                                                       \
        list->buffer[list->count] = item;                                                                              \
        list->count++;                                                                                                 \
    }                                                                                                                  \
                                                                                                                       \
    void T##s_free(T##s list)                                                                                          \
    {                                                                                                                  \
        for (int i = 0; i < list->count; i++)                                                                          \
        {                                                                                                              \
            list->free_fn(list->buffer[i]);                                                                            \
        }                                                                                                              \
                                                                                                                       \
        free(list->buffer);                                                                                            \
        free(list);                                                                                                    \
    }                                                                                                                  \
                                                                                                                       \
    void T##s_free_only_buffer(T##s list)                                                                              \
    {                                                                                                                  \
        free(list->buffer);                                                                                            \
        free(list);                                                                                                    \
    }                                                                                                                  \
                                                                                                                       \
    T T##s_get(T##s list, int i)                                                                                       \
    {                                                                                                                  \
        if (i < 0 || list->count <= i)                                                                                 \
        {                                                                                                              \
            return NULL;                                                                                               \
        }                                                                                                              \
                                                                                                                       \
        return list->buffer[i];                                                                                        \
    }                                                                                                                  \
                                                                                                                       \
    T T##s_get_by_char_property(T##s list, const char *value, T##_string_property_fn property_fn)                      \
    {                                                                                                                  \
        for (int i = 0; i < list->count; i++)                                                                          \
        {                                                                                                              \
            if (strcmp(property_fn(list->buffer[i]), value) == 0)                                                      \
            {                                                                                                          \
                return list->buffer[i];                                                                                \
            }                                                                                                          \
        }                                                                                                              \
                                                                                                                       \
        return NULL;                                                                                                   \
    }                                                                                                                  \
                                                                                                                       \
    int T##s_average(T##s list, T##_int_property_fn property_fn)                                                       \
    {                                                                                                                  \
        int sum = 0;                                                                                                   \
                                                                                                                       \
        for (int i = 0; i < list->count; i++)                                                                          \
        {                                                                                                              \
            sum += property_fn(list->buffer[i]);                                                                       \
        }                                                                                                              \
                                                                                                                       \
        return sum / list->count;                                                                                      \
    }                                                                                                                  \
                                                                                                                       \
    void T##s_print(T##s list)                                                                                         \
    {                                                                                                                  \
        for (int i = 0; i < list->count; i++)                                                                          \
        {                                                                                                              \
            list->print_fn(list->buffer[i]);                                                                           \
        }                                                                                                              \
    }                                                                                                                  \
                                                                                                                       \
    T##s T##s_to_sorted(T##s list, __compar_fn_t compare_fn)                                                           \
    {                                                                                                                  \
        T##s sortedList = malloc(sizeof(struct T##s));                                                                 \
        memcpy(sortedList, list, sizeof(struct T##s));                                                                 \
        sortedList->buffer = malloc(list->count * sizeof(T));                                                          \
        memcpy(sortedList->buffer, list->buffer, list->count * sizeof(T));                                             \
        qsort(sortedList->buffer, sortedList->count, sizeof(T), compare_fn);                                           \
                                                                                                                       \
        return sortedList;                                                                                             \
    }
