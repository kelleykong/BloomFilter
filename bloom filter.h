#include <iostream>
using namespace std;

const unsigned char masks[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

class BloomFilter
{
public:
	BloomFilter(int d);
	~BloomFilter() {delete []bits; }
	int hash1(const char *key);
	int hash2(const char *key);
	void add(void *data);
	bool query(void *data);

private:
	int n;
	int size;
	unsigned char *bits;

};

BloomFilter::BloomFilter(int d)
{
	n = d;
	size = (d + 7) / 8;
	bits = new unsigned char[size];
	if(bits == NULL)
	{
		cout<<"no enough space";
	}
    memset(bits, 0, size);
	
}

int BloomFilter::hash1(const char *key)
{
	int hash = 1315423911;
    int len = 0;
	int sz = strlen(key);
    while (len < sz)
    {
        hash ^= (hash << 5) + key[len] + (hash >> 2);
        len++;
    }
    return (hash & 0x7fffffffl);
	
}

int BloomFilter::hash2(const char *key)
{
	int hash = 0;
    int len = 0;
	int sz = strlen(key);
    while (len < sz)
    {
        hash = (hash << 6) + (hash << 16) - hash + key[len];
        len++;
    }
    return (hash & 0x7fffffffl);
}

void BloomFilter::add(void *data)
{
    int h1 = hash1((char *)data) % n;
	int idx1 = h1 / 8;
	int h2 = hash2((char *)data) % n;
	int idx2 = h2 / 8;
    if (idx1 >= size && idx2 >= size)
    {
        cout<<"bloom_insert: hash value overflow\n";
		exit(-1);
    }
    bits[idx1] |= masks[h1 % 8];
	bits[idx2] |= masks[h2 % 8];
}

bool BloomFilter::query(void *data)
{
    int h1 = hash1((char *)data) % n;
	int idx1 = h1 / 8;
    int h2 = hash2((char *)data) % n;
	int idx2 = h2 / 8;
    if (idx1 >= size && idx2 >= size)
    {
        cout<<"bloom_insert: hash value overflow\n";
        exit(-1);
    }

	if ((bits[idx1] & masks[h1 % 8]) && (bits[idx2] & masks[h2 % 8]) )
	{
		cout<<(const char *)data<<" in set"<<endl;
		return true;
	}
	else
	{
		cout<<"can't find "<<(const char *)data<<endl;
		return false;
	}

}
