
typedef struct HASH_ENTRY_T {
  struct HASH_ENTRY_T * next;
  HASH_KEY_T key;
  void * value;
} HASH_ENTRY_T;

typedef struct {
  HASH_ENTRY_T ** table;
  unsigned long table_size;
  unsigned long entry_count;
} HASH_T;

#ifdef HASH_CLEAR
extern void HASH_CLEAR(HASH_T * h);
#endif

#ifdef HASH_GET
extern void * HASH_GET(HASH_T * h, HASH_KEY_T key);
#endif

#ifdef HASH_SET
extern void * HASH_SET(HASH_T * h, HASH_KEY_T key, void * value);
#endif

