
#include <stddef.h>

typedef struct HASH_ENTRY_T {
  struct HASH_ENTRY_T * next;
  HASH_KEY_T key;
  char data[];
} HASH_ENTRY_T;

typedef struct {
  HASH_ENTRY_T ** table;
  unsigned long table_size;
  unsigned long entry_count;
} HASH_T;

#ifdef HASH_CLEAR
extern void HASH_CLEAR(HASH_T * h);
#endif

#ifdef HASH_CREATE
extern void * HASH_CREATE(HASH_T * h, HASH_KEY_T key, size_t size);
#endif

#ifdef HASH_DESTROY
extern void HASH_DESTROY(HASH_T * h, HASH_KEY_T key);
#endif

#ifdef HASH_FIND
extern void * HASH_FIND(HASH_T * h, HASH_KEY_T key);
#endif

