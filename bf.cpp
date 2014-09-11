/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int jshash(const char *s, unsigned size);
unsigned int sdbmhash(const char *s, unsigned size);

//bloom types and funcs
const unsigned char masks[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

typedef unsigned (*hash_func_ptr)(const char *buffer, unsigned size);
struct __bloom_filter
{
    unsigned n;
    unsigned size;
    unsigned char *bits;
    hash_func_ptr hash;
};
typedef struct __bloom_filter* bloom_filter;

bloom_filter bloom_init (unsigned n, hash_func_ptr hash);
int bloom_insert(bloom_filter b, void *data, unsigned size);
int bloom_check(bloom_filter b, void *data, unsigned size);
void bloom_destroy(bloom_filter b);


int main()
{
    const int size = 655371;
    bloom_filter b1 = bloom_init(size, sdbmhash);
    for (int i = 0; i < size / 2; i += 2)
    {
        if (!bloom_insert(b1, &i, sizeof(i)))
        {
            fprintf(stderr, "err insert %d\n", i);
            exit(1);
        }
    }
    printf("insert ok\n");

    int cnt = 0;
    for (i = 0; i < size / 2; i++)
    {
        if (bloom_check(b1, &i, sizeof(i)))
        {
            if (i & 1)
            {
                //printf("i = %d should not be checked, tolerable.\n", i);
                cnt++;
            }
        }
        else
        {
            if (!(i & 1))
            {
                printf("i = %d should be checked! BUG!\n", i);
            }
        }
    }
    printf("cnt = %d\n", cnt);
    return 0;
}

bloom_filter bloom_init (unsigned n, hash_func_ptr hash)
{
    bloom_filter b = (bloom_filter)malloc(sizeof(__bloom_filter));
    if (b == NULL)
    {
        fprintf(stderr, "bloom_init: err malloc bloom_filter\n");
        return NULL;
    }

    b->n    = n;
    b->size = (n + 7) / 8;
    b->hash = hash;

    b->bits = (unsigned char *)malloc(b->size);
    memset(b->bits, 0, b->size);
    if (b->bits == NULL)
    {
        fprintf(stderr, "bloom_init: err malloc bits\n");
        return NULL;
    }
    return b;
}

int bloom_insert(bloom_filter b, void *data, unsigned size)
{
    unsigned h = b->hash((const char *)data, size) % (b->n);
    unsigned idx = h / 8;
    if (idx >= b->size)
    {
        fprintf(stderr, "bloom_insert: hash value overflow\n");
        return 0;
    }
    b->bits[idx] |= masks[h % 8];
    //printf("h = %2d, idx = %2d, bit = %2d\n", h, idx, h % 8);
    return 1;
}

int bloom_check(bloom_filter b, void *data, unsigned size)
{
    unsigned h = b->hash((const char *)data, size) % (b->n);
    unsigned idx = h / 8;
    if (idx >= b->size)
    {
        fprintf(stderr, "bloom_insert: hash value overflow\n");
        exit(1);
    }
    return !!(b->bits[idx] & masks[h % 8]);
}

void bloom_destroy(bloom_filter b)
{
    if (b != NULL)
    {
        if (b->bits != NULL)
            free(b->bits);
        free(b);
    }
}

//-----------------------------------------------

unsigned int jshash(const char *s, unsigned size)
{
    int hash = 1315423911;
    unsigned len = 0;
    while (len < size)
    {
        hash ^= (hash << 5) + s[len] + (hash >> 2);
        len++;
    }
    return (hash & 0x7fffffffl);
}

unsigned int sdbmhash(const char *s, unsigned size)
{
    int hash = 0;
    unsigned len = 0;
    while (len < size)
    {
        hash = (hash << 6) + (hash << 16) - hash + s[len];
        len++;
    }
    return (hash & 0x7fffffffl);
}
*/