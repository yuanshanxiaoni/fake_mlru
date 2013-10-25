/*
 * =====================================================================================
 *
 *       Filename:  lru.h
 *
 *    Description:  header
 *
 *        Version:  1.0
 *        Created:  2013/10/24 11时28分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  bigdog (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _LRU_H
#define _LRU_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <time.h>

#include "_c_list.h"

#define MAX_NUM  8
#define MAX_DLEN 256

#define MAX_KEY  128

typedef int (*hfunc)(char s);

struct _node_ ;
typedef struct _lru_buffer_ {
    struct _node_ *head, *cold, *tail;
    u16 total;
    u16 memsize;
    u8 full;
    struct _node_ *map[26]; // a-z
    hfunc func;
} lru_mgt;

#pragma pack(push)
#pragma pack(1)
typedef struct _node_ {
    // cycle list.
    struct _node_ *next, *prev; // for store, access change the order. 
    // uncycle list.
    struct _node_ *hn, *hp;     // for fast query.
    u8  idx ;        // for test
    time_t actime;   // last access time.
    u8  hint;        // access times.
    u16 dlen;        // data length.
    char data[0];    // data.
} node;
#pragma pack(pop)

int lru_buff_init(lru_mgt **mgt, size_t max_node) ;
void lru_buff_destructor(lru_mgt **mgt) ;
int lru_replace(lru_mgt *mgt, void *data, int dlen) ;
// int lru_append(lru_mgt *mgt, void *data, int dlen) ;
int lru_add_data (lru_mgt *mgt, void *data, int dlen) ;
node *lru_query(lru_mgt *mgt, void *data, int dlen) ;

void lru_hdump(lru_mgt *mgt) ;
void lru_dump(lru_mgt *mgt) ;

node *access_data(lru_mgt *mgt, char *query) ;
int prepare_data(lru_mgt *mgt, char **data, int dcount) ;
void node_dump(node *n) ;

#endif
