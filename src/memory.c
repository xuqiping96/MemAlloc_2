/**
 * @file memory.h
 * @author 智识之道 (binary@techbootcamp)
 * @brief 内存分配
 * @version 0.1
 * @date 2022-01-18
 *
 * @copyright Copyright (c) 2022
 *
 */
///////////////////////////////////////////////////////////////////////////////
//头文件区域
//其他头文件自行添加

#include <stdio.h>

#include "memory.h"

///////////////////////////////////////////////////////////////////////////////
//结构体区域

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

///////////////////////////////////////////////////////////////////////////////
//变量区域

//设定的算法
enum Algorithm algo;

//内存块头
MemoryHeader *memory_header;

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
 * @param current 当前内存块首部
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
    printf("TODO: is_allow_allocate\n");
    return 0;
}

int is_allocated(MemoryHeader *current)
{
    printf("TODO: is_allocated\n");
    return 0;
}

int is_free(MemoryHeader *current)
{
    printf("TODO: is_free\n");
    return 0;
}

MemoryHeader *get_next_header(MemoryHeader *current)
{
    printf("TODO: get_next_header\n");
    return NULL;
}

int get_size(MemoryHeader *current)
{
    printf("TODO: get_size\n");
    return 0;
}

void *get_data(MemoryHeader *current)
{
    printf("TODO: get_data\n");
    return NULL;
}

MemoryHeader *get_header_from_data(void *current)
{
    printf("TODO: get_header_from_data\n");
    return NULL;
}

void set_next_packet(MemoryHeader *current, int size)
{
    printf("TODO: set_next_packet\n");
}

void set_allocated(MemoryHeader *current)
{
    printf("TODO: set_allocated\n");
}

void set_free(MemoryHeader *current)
{
    printf("TODO: set_free\n");
}

void set_size(MemoryHeader *current, int size)
{
    printf("TODO: set_size\n");
}

void coalesce(MemoryHeader *current, MemoryHeader *last)
{
    printf("TODO: coalesce\n");
}

int mem_init(int size, enum Algorithm selectAlgo)
{
    printf("TODO: mem_init\n");
    return -1;
}

void *mem_alloc(int size)
{
    printf("TODO: mem_alloc\n");

    return NULL;
}

int mem_free(void *data)
{
    printf("TODO: mem_free\n");

    return -1;
}

void mem_dump()
{
    printf("TODO: mem_dump\n");
}
