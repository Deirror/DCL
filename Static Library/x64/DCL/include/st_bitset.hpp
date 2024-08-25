#pragma once
#include <dcl_defines.h>
#include <tydefuint_t.h>

DCL_BEGIN

template<size_t size>
class st_bitset
{
	static constexpr unsigned MAX_NUM = size;
	static constexpr unsigned NUMBERS_COUNT = MAX_NUM + 1;
	static constexpr unsigned BUCKET_SIZE = sizeof(byte) * 8;
	static constexpr unsigned BUCKETS_COUNT = NUMBERS_COUNT / BUCKET_SIZE + 1;

	byte buckets[BUCKETS_COUNT] = { 0 };
	unsigned getBucketIndex(unsigned n) const;
	unsigned getBitIndex(unsigned n) const;
public:
	st_bitset() = default;

	void add(unsigned n);
	void remove(unsigned n);

	bool contains(unsigned n) const;
};

template<size_t size>
inline unsigned st_bitset<size>::getBucketIndex(unsigned n) const
{
	return n / BUCKET_SIZE;
}

template<size_t size>
inline unsigned st_bitset<size>::getBitIndex(unsigned n) const
{
	return n % BUCKET_SIZE;
}

template<size_t size>
inline void st_bitset<size>::add(unsigned n)
{
	if (n > MAX_NUM)
		return;

	unsigned bucketIndex = getBucketIndex(n);
	unsigned bitIndex = getBitIndex(n);

	byte mask = 1 << bitIndex;

	buckets[bucketIndex] |= mask;

}

template<size_t size>
inline void st_bitset<size>::remove(unsigned n)
{
	unsigned bucketIndex = getBucketIndex(n);
	unsigned bitIndex = getBitIndex(n);

	byte mask = 1 << bitIndex;
	mask = ~mask;

	buckets[bucketIndex] &= mask;
}

template<size_t size>
inline bool st_bitset<size>::contains(unsigned n) const
{
	unsigned bucketIndex = getBucketIndex(n);
	unsigned bitIndex = getBitIndex(n);

	byte mask = 1 << bitIndex;

	return (buckets[bucketIndex] & mask) != 0;
}

DCL_END