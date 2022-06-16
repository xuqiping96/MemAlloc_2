#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "memory.h"

#define SPLIT_1 "********************************************Memory Dump********************************************\n"
#define SPLIT_2 "        id              header                data                 end  length  size  padding  used\n"
#define SPLIT_3 "***************************************************************************************************\n"

/**
 * @brief 内存结构体
 *
 */
typedef struct
{
    //下一个首部地址+分配位
    void *packed;
    //分配的块大小或，或是可用有效负载大小
    unsigned size;
} MemoryHeader;

//设定的算法
enum Algorithm algo;

//内存块头
MemoryHeader *memory_header;
void *allocated_memory;

///////////////////////////////////////////////////////////////////////////////
//函数声明区域

/**
 * @brief 是否运行分配
 *
 * @param current 当前内存块首部
 * @param size 需要分配块的大小
 * @return int 允许分配则返回1；不允许分配返回0
 */
int is_allow_allocate(MemoryHeader *current, int size);

/**
 * @brief 是否已经分配
 *
 * @param current 当前内存块首部
 * @return int 已经分配则返回1,未分配则返回0
 */
int is_allocated(MemoryHeader *current);

/**
 * @brief 是否空闲
 *
 * @param current 当前内存块首部
 * @return int 空闲则返回1,不空闲则返回0
 */
int is_free(MemoryHeader *current);

/**
 * @brief 获取下一个首部
 *
 * @param current 当前内存块首部
 * @return MemoryHeader* 有下一个则返回指针；如是最后一个则返回NULL
 */
MemoryHeader *get_next_header(MemoryHeader *current);

/**
 * @brief 获取分配的大小
 *
 * @param current 当前内存块首部
 * @return int 分配块的大小
 */
int get_size(MemoryHeader *current);

/**
 * @brief 获取数据的指针
 *
 * @param current 当前内存块首部
 * @return void* 写数据的指针
 */
void *get_data(MemoryHeader *current);

/**
 * @brief 从数据指针获取到首部指针
 *
 * @param current 当前内存块数据指针
 * @return MemoryHeader* 返回首部指针
 */
MemoryHeader *get_header_from_data(void *current);

/**
 * @brief 设置下一个首部地址+分配位
 *
 * @param current 当前内存块首部
 * @param size 分配的大小
 */
void set_next_packet(MemoryHeader *current, int size);

/**
 * @brief 设置已经分配的
 *
 * @param current 当前内存块首部
 */
void set_allocated(MemoryHeader *current);

/**
 * @brief 设置未分配的
 *
 * @param current 当前内存块首部
 */
void set_free(MemoryHeader *current);

/**
 * @brief 设置分配的大小
 *
 * @param current 当前内存块首部
 * @param size 分配块的大小
 */
void set_size(MemoryHeader *current, int size);

/**
 * @brief 合并
 *
 * @param current 当前内存块首部
 * @param last 上一个内存块首部
 */
void coalesce(MemoryHeader *current, MemoryHeader *last);

///////////////////////////////////////////////////////////////////////////////
//函数实现区域

int is_allow_allocate(MemoryHeader *current, int size)
{
    if(size % 4 == 0)
    {
        return current->size >= size;
    } else
    {
        size = size + (4 - size % 4);

        return current->size >= size;
    }
}

int is_allocated(MemoryHeader *current)
{
    if((uintptr_t)current & 1)
    {
        return 1;
    } else
    {
        return 0;
    }
}

int is_free(MemoryHeader *current)
{
    if((uintptr_t)current & 1)
    {
        return 0;
    } else
    {
        return 1;
    }
}

MemoryHeader *get_next_header(MemoryHeader *current)
{
    current = (uintptr_t)current & ~1;

    return current->packed;
}

int get_size(MemoryHeader *current)
{
    int size;

    current = (uintptr_t)current & ~1;
    size = current->size;
    if(size % 4 == 0)
    {
        return size;
    } else
    {
        return size + (4 - size % 4);
    }
}

void *get_data(MemoryHeader *current)
{
    return (void *)((uintptr_t)current & ~1) + sizeof(MemoryHeader);
}

MemoryHeader *get_header_from_data(void *current)
{
    return (void *)current - sizeof(MemoryHeader);
}

void set_next_packet(MemoryHeader *current, int size)
{
    MemoryHeader *next_packet;
    int allocated_size;
    if(size % 4 == 0)
    {
        allocated_size = size;
    } else {
        allocated_size = size + (4 - size % 4);
    }
    //判断是否有空间设置下一个packet
    if((current->size - allocated_size) >= (sizeof(MemoryHeader) + 4))
    {
        next_packet = (void *)current + sizeof(MemoryHeader) + allocated_size;
        next_packet->size = current->size - allocated_size - sizeof(MemoryHeader);
        next_packet->packed = current->packed;

        current->packed = next_packet;
    }
}

void set_allocated(MemoryHeader *current)
{
    MemoryHeader *cur_header = memory_header;
    MemoryHeader *prev_header = NULL;

    while(cur_header != current)
    {
        prev_header = cur_header;
        cur_header = get_next_header(cur_header);
    }

    if(prev_header == NULL)
    {
        memory_header = (uintptr_t)memory_header | 1;
    } else
    {
        prev_header = (uintptr_t)prev_header & ~1;
        prev_header->packed = (uintptr_t)(prev_header->packed) | 1;
    }
}

void set_free(MemoryHeader *current)
{
    int size;

    if(current == NULL)
    {
        memory_header = (uintptr_t)memory_header & ~1;
        size = get_size(memory_header);
        set_size(memory_header, size);
    } else
    {
        current = (uintptr_t)current & ~1;
        current->packed = (uintptr_t)(current->packed) & ~1;
        current = current->packed;
        size = get_size(current);
        set_size(current, size);
    }
}

void set_size(MemoryHeader *current, int size)
{
    current->size = size;
}

void coalesce(MemoryHeader *current, MemoryHeader *last)
{
    int size = last->size + sizeof(MemoryHeader) + current->size;
    set_size(last, size);
    last->packed = current->packed;
}

int mem_init(int size, enum Algorithm selectAlgo)
{
    algo = selectAlgo;
    allocated_memory = malloc(size + 1);
    if(allocated_memory == NULL)
    {
        return -1;
    }

    memory_header = (uintptr_t)allocated_memory + (4 - (uintptr_t)allocated_memory % 4);
    memory_header->size = size - sizeof(MemoryHeader);
    memory_header->packed = NULL;
    memory_header  = (uintptr_t)memory_header & ~1;

    return 0;
}

void *mem_alloc(int size)
{
    MemoryHeader *cur_header = memory_header;
    //遍历header，判断是否空闲，然后判断是否允许分配
    switch(algo)
    {
        case FIRST_FIT:
            while(cur_header != NULL)
            {
                if(is_free(cur_header) && is_allow_allocate(cur_header, size))
                {
                    set_next_packet(cur_header, size);
                    set_size(cur_header, size);
                    set_allocated(cur_header);

                    return (void *)cur_header + sizeof(MemoryHeader);   
                } else
                {
                    cur_header = get_next_header(cur_header);
                }
            }

            return NULL;

        default:
            return NULL;

    }
}

int mem_free(void *data)
{
    MemoryHeader *cur_header = memory_header;
    MemoryHeader *cur_real_addr = (uintptr_t)cur_header & ~1;
    MemoryHeader *prev_header = NULL;
    //遍历首部，找到属于data的首部，将分配位设为0
    while(cur_header != NULL)
    {
        if((void *)cur_real_addr + sizeof(MemoryHeader) != data)
        {
            prev_header = cur_header;
            cur_header = cur_real_addr->packed;
            cur_real_addr = (uintptr_t)cur_header & ~1;
        } else
        {
            break;
        } 
    }

    if(get_header_from_data(data) != cur_real_addr)
    {
        return -1;
    }

    set_free(prev_header);
    cur_header = cur_real_addr;

    //如果当前首部不是第一个，且如果前一个首部的分配位也为0，则合并
    if((prev_header != NULL) && is_free(prev_header))
    {
        coalesce(cur_header, prev_header);
        cur_header = prev_header;
    }
    //如果当前不是最后一个首部，再判断下一个首部是否为0，如果是，则合并
    if((cur_header->packed != NULL) && is_free(cur_header->packed))
    {
        coalesce(cur_header->packed, cur_header);
    }

    return 0;
}

void mem_dump()
{
    int id = 1;
    int length;
    int size;
    int padding;
    int used;
    int total_size = 0;
    int total_padding = 0;
    int total_used = 0;
    int total_free = 0;
    MemoryHeader *cur_header = memory_header;
    void *data;
    void *end;

    printf(SPLIT_1);
    printf(SPLIT_2);

    while((void *)((uintptr_t)cur_header & ~1) != NULL)
    {

        if(is_allocated(cur_header))
        {
            used = 1;
            cur_header = (uintptr_t)cur_header & ~1;

            size = cur_header->size;
            padding = get_size(cur_header) - size;

            total_size += size;
            total_padding += padding;
            total_used += (sizeof(MemoryHeader) + size + padding);
        } else
        {
            used = 0;

            size = cur_header->size;
            padding = 0;

            total_used += sizeof(MemoryHeader);
            total_free += size;
        }

        data = (void *)cur_header + sizeof(MemoryHeader);
        end = data + size + padding;
        length = sizeof(MemoryHeader) + size + padding;
 
        printf("%10d  %18p  %18p  %18p  %6d  %4d  %7d  %4d\n", id, cur_header, data, end, length, size, padding, used);
        
        cur_header = get_next_header(cur_header);
        ++id;
    }

    printf("Total size = %d, padding = %d, free = %d, used = %d\n", total_size, total_padding, total_free, total_used);
    printf(SPLIT_3);
}
