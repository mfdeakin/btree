
#ifndef _BTREE_H_
#define _BTREE_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct btreefunc
{
	int (*comp_lt)(void *, void *);
	void *(*open)(const char *, const char *flags);
	size_t (*read)(void *, size_t, size_t, void *);
	size_t (*write)(const void *, size_t, size_t, void *);
	void (*close)(void *);
	void *(*memalloc)(size_t);
	void (*memfree)(void *);
	void *(*mutex_create)();
	void (*mutex_destroy)(void *);
	void (*mutex_lock)(void *);
	void (*mutex_trylock)(void *);
	void (*mutex_unlock)(void *);
};

struct btree
{
	unsigned order, rootpos;
	size_t elsize;
	void *root;
	void *mutex, *file;
	struct btreefunc funcs;
};

struct btree *btree_init(char *, unsigned, size_t, struct btreefunc *);
struct btree *btree_read(char *, struct btreefunc *);
void btree_del(struct btree *);
unsigned btree_find(void *cmp, void *dest);
unsigned btree_rem(void *);
unsigned btree_add(void *);


#endif //_BTREE_H_
