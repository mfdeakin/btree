
#include "btree.h"

#ifdef BTREE_DEBUG
#undef b_printf
#define b_printf printf
#else
int fake(char *, ...);
#undef b_printf
#define b_printf fake
#endif

/* struct node */
/* { */
/* 	int size; */
/* 	int *ind; */
/* 	void *elems; */
/* }; */

#define NODESIZE(m) (m - 1) * sizeof(void *) + m * sizeof(int *) + sizeof(int)

int defcompare(void *lhs, void *rhs)
{
	return (int)((long)lhs - (long)rhs);
}

void *nodealloc(struct btree *tree)
{
	int *node;
	node = tree->funcs.memalloc(tree->order);
	/* Setting the current size of the node */
	/* Empty, so 0 */
	node[0] = 0;
	/* Make sure that the first indice is 0 so identification of leaves is easy */
	node[1] = 0;
	return node;
}

void *nodeel(struct btree *tree, void *node, unsigned idx)
{
	return (void *)((long)node + sizeof(int[tree->order]) + tree->elsize * idx);
}

void *nodeind(void *node, unsigned idx)
{
	if(idx > *(int *)node)
		return NULL;
	return (void *)(&((int *)node)[idx + 1]);
}

struct btree *btree_init(char *fn, unsigned order, size_t elemsz,
						 struct btreefunc *funcs)
{
	if(!fn || !order || !elemsz)
		return NULL;
	struct btree *tree;
	if(funcs)
		{
			tree = funcs->memalloc(sizeof(struct btree));
			tree->funcs = *funcs;
		}
	else
		{
			tree = malloc(sizeof(struct btree));
			memset(&tree->funcs, 0, sizeof(struct btreefunc));
			tree->funcs.comp_lt = &defcompare;
			tree->funcs.open = (void *(*)(const char *, const char *))&fopen;
			tree->funcs.write = (size_t (*)(const void *, size_t, size_t, void *))&fwrite;
			tree->funcs.read = (size_t (*)(void *, size_t, size_t, void *))&fread;
			tree->funcs.close = (void (*)(void *))&fclose;
			tree->funcs.memalloc = &malloc;
			tree->funcs.memfree = &free;
		}
	tree->root = tree->funcs.memalloc(NODESIZE(order));
	
	return tree;
}

struct btree *btree_read(char *fn, struct btreefunc *funcs)
{
	if(!fn)
		return NULL;
	struct btree *tree = malloc(sizeof(struct btree));
	return tree;
}

void btree_del(struct btree *tree)
{
}

unsigned btree_find(void *cmp, void *dest)
{
	return 0;
}

unsigned btree_rem(void *);
unsigned btree_add(void *);
