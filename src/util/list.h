#ifndef UTIL_LIST_H
#define UTIL_LIST_H


typedef struct list_node {
  struct list_node * head;
  struct list_node * next;
  struct list_node * prev;
  void * value;
} list_node_t;

typedef struct list {
  list_node_t node;
} list_t;

// clears the entire list, invalidates all nodes
// `l` is safe to free after this function is called
void list_clear(list_t * l);

// prepends a value to the beginning of the list
void list_prepend(list_t * l, void * value);
// appends a value to the end of the list
void list_append (list_t * l, void * value);

// returns the value of the first node in the list, or `NULL` if the list is empty
void * list_front(list_t * l);
// returns the value of the last node in the list, or `NULL` if the list is empty
void * list_back (list_t * l);

// returns the first node in the list, or `NULL` if the list is empty
list_node_t * list_begin(list_t * l);
// returns the last node in the list, or `NULL` if the list is empty
list_node_t * list_end  (list_t * l);

// returns the node after `node`, or `NULL` if `node` is at the end of the list
list_node_t * list_next(list_node_t * node);
// returns the node before `node`, or `NULL` if `node` is at the beginning of the list
list_node_t * list_prev(list_node_t * node);

// removes the node from its list
// the node is invalid after this function is called
void list_erase(list_node_t * node);

// gets the current value
void * list_getvalue(list_node_t * node);
// sets a new value; returns the old value
void * list_setvalue(list_node_t * node, void * value);

// inserts a new node containing `value` before `ref`
void list_insertbefore(list_node_t * ref, void * value);
// inserts a new node containing `value` after `ref`
void list_insertafter (list_node_t * ref, void * value);

// counts the number of elements in the list
long list_length(list_t * l);


void list_each  (list_t * l, void (* each_fn)(void * val));
void list_eachi (list_t * l, void (* each_fn)(void * val, long idx));
void list_eachd (list_t * l, void (* each_fn)(void * val, void * ud), void * ud);
void list_eachid(list_t * l, void (* each_fn)(void * val, long idx, void * ud), void * ud);

void list_map  (list_t * l, void * (* map_fn)(void * val));
void list_mapi (list_t * l, void * (* map_fn)(void * val, long idx));
void list_mapd (list_t * l, void * (* map_fn)(void * val, void * ud), void * ud);
void list_mapid(list_t * l, void * (* map_fn)(void * val, long idx, void * ud), void * ud);

void list_eraseif  (list_t * l, int (* erase_fn)(void * val));
void list_eraseifi (list_t * l, int (* erase_fn)(void * val, long idx));
void list_eraseifd (list_t * l, int (* erase_fn)(void * val, void * ud), void * ud);
void list_eraseifid(list_t * l, int (* erase_fn)(void * val, long idx, void * ud), void * ud);


#endif
