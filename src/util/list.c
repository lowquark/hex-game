
#include <assert.h>
#include <stdlib.h>

#include <util/list.h>

static void node_init(list_node_t * node, void * value) {
  node->head = node;
  node->next = node;
  node->prev = node;
  node->value = value;
}
static void list_ensureinit(list_t * l) {
  if(!l->node.head) {
    node_init(&l->node, NULL);
  }
}

static void node_remove(list_node_t * node) {
  node->prev->next = node->next;
  node->next->prev = node->prev;
}
static void node_putafter(list_node_t * ref, list_node_t * node) {
  node->head = ref->head;

  ref->next->prev = node;
  node->next = ref->next;
  node->prev = ref;
  ref->next = node;
}
static void node_putbefore(list_node_t * ref, list_node_t * node) {
  node->head = ref->head;

  ref->prev->next = node;
  node->prev = ref->prev;
  node->next = ref;
  ref->prev = node;
}


void list_clear(list_t * l) {
  list_node_t * head;
  list_node_t * next;
  list_node_t * node;

  list_ensureinit(l);

  head = l->node.head;

  if(head) {
    // must be head of its own list to loop correctly
    assert(head == &l->node);

    // start here
    node = head->next;

    while(node != head) {
      // save next element
      next = node->next;

      // free this node
      free(node);

      node = next;
    }

    node_init(head, NULL);
  }
}

void list_append(list_t * l, void * value) {
  list_ensureinit(l);
  list_insertbefore(&l->node, value);
}
void list_prepend(list_t * l, void * value) {
  list_ensureinit(l);
  list_insertafter(&l->node, value);
}

void * list_front(list_t * l) {
  if(l->node.head == NULL) { return NULL; }
  return l->node.next->value;
}
void * list_back(list_t * l) {
  if(l->node.head == NULL) { return NULL; }
  return l->node.prev->value;
}

list_node_t * list_begin(list_t * l) {
  if(l->node.head == NULL) { return NULL; }
  return list_next(&l->node);
}
list_node_t * list_end(list_t * l) {
  if(l->node.head == NULL) { return NULL; }
  return list_prev(&l->node);
}

list_node_t * list_next(list_node_t * node) {
  assert(node);

  list_node_t * head = node->head;
  list_node_t * next = node->next;

  if(head && next != head) {
    return next;
  }

  return NULL;
}
list_node_t * list_prev(list_node_t * node) {
  assert(node);

  list_node_t * head = node->head;
  list_node_t * prev = node->prev;

  if(head && prev != head) {
    return prev;
  }

  return NULL;
}

void list_erase(list_node_t * node) {
  assert(node);
  node_remove(node);
  free(node);
}

void * list_getvalue(list_node_t * node) {
  assert(node);
  return node->value;
}
void * list_setvalue(list_node_t * node, void * value) {
  assert(node);
  void * old = node->value;
  node->value = value;
  return old;
}

void list_insertbefore(list_node_t * ref, void * value) {
  list_node_t * new_node = calloc(sizeof(*new_node), 1);

  if(new_node) {
    node_init(new_node, value);
    // put before ref
    node_putbefore(ref, new_node);
  }
}
void list_insertafter(list_node_t * ref, void * value) {
  list_node_t * new_node = calloc(sizeof(*new_node), 1);

  if(new_node) {
    node_init(new_node, value);
    // put after ref
    node_putafter(ref, new_node);
  }
}

long list_length(list_t * l) {
  const list_node_t * head = l->node.head;

  list_node_t * node = l->node.next;

  long count = 0;

  while(node != head) {
    count ++;

    node = node->next;
  }

  return count;
}

void list_each(list_t * l, void (* each_fn)(void * val)) {
  const list_node_t * head = l->node.head;

  list_node_t * node = l->node.next;

  while(node != head) {
    each_fn(node->value);

    node = node->next;
  }
}
void list_eachi(list_t * l, void (* each_fn)(void * val, long idx)) {
  const list_node_t * head = l->node.head;

  long idx = 0;
  list_node_t * node = l->node.next;

  while(node != head) {
    each_fn(node->value, idx);

    idx ++;
    node = node->next;
  }
}
void list_eachd(list_t * l, void (* each_fn)(void * val, void * ud), void * ud) {
  const list_node_t * head = l->node.head;

  list_node_t * node = l->node.next;

  while(node != head) {
    each_fn(node->value, ud);

    node = node->next;
  }
}
void list_eachid(list_t * l, void (* each_fn)(void * val, long idx, void * ud), void * ud) {
  const list_node_t * head = l->node.head;

  long idx = 0;
  list_node_t * node = l->node.next;

  while(node != head) {
    each_fn(node->value, idx, ud);

    idx ++;
    node = node->next;
  }
}

void list_map(list_t * l, void * (* map_fn)(void * val)) {
  const list_node_t * head = l->node.head;

  list_node_t * node = l->node.next;

  while(node != head) {
    node->value = map_fn(node->value);

    node = node->next;
  }
}
void list_mapi(list_t * l, void * (* map_fn)(void * val, long idx)) {
  const list_node_t * head = l->node.head;

  long idx = 0;
  list_node_t * node = l->node.next;

  while(node != head) {
    node->value = map_fn(node->value, idx);

    idx ++;
    node = node->next;
  }
}
void list_mapd(list_t * l, void * (* map_fn)(void * val, void * ud), void * ud) {
  const list_node_t * head = l->node.head;

  list_node_t * node = l->node.next;

  while(node != head) {
    node->value = map_fn(node->value, ud);

    node = node->next;
  }
}
void list_mapid(list_t * l, void * (* map_fn)(void * val, long idx, void * ud), void * ud) {
  const list_node_t * head = l->node.head;

  long idx = 0;
  list_node_t * node = l->node.next;

  while(node != head) {
    node->value = map_fn(node->value, idx, ud);

    idx ++;
    node = node->next;
  }
}

void list_eraseif(list_t * l, int (* erase_fn)(void * val)) {
  const list_node_t * head = l->node.head;

  list_node_t * node = l->node.next;

  while(node != head) {
    list_node_t * next = node->next;

    if(erase_fn(node->value)) {
      list_erase(node);
    }

    node = next;
  }
}
void list_eraseifi(list_t * l, int (* erase_fn)(void * val, long idx)) {
  const list_node_t * head = l->node.head;

  long idx = 0;
  list_node_t * node = l->node.next;

  while(node != head) {
    list_node_t * next = node->next;

    if(erase_fn(node->value, idx)) {
      list_erase(node);
    }

    idx ++;
    node = next;
  }
}
void list_eraseifd(list_t * l, int (* erase_fn)(void * val, void * ud), void * ud) {
  const list_node_t * head = l->node.head;

  list_node_t * node = l->node.next;

  while(node != head) {
    list_node_t * next = node->next;

    if(erase_fn(node->value, ud)) {
      list_erase(node);
    }

    node = next;
  }
}
void list_eraseifid(list_t * l, int (* erase_fn)(void * val, long idx, void * ud), void * ud) {
  const list_node_t * head = l->node.head;

  long idx = 0;
  list_node_t * node = l->node.next;

  while(node != head) {
    list_node_t * next = node->next;

    if(erase_fn(node->value, idx, ud)) {
      list_erase(node);
    }

    idx ++;
    node = next;
  }
}

