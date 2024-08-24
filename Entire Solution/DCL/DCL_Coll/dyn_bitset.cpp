#include "dyn_bitset.h"
#include <move.hpp>

DCL_BEGIN

dyn_bitset::dyn_bitset(unsigned N)
{
	bucketsCount = N / elementsInBucket + 1;
	buckets = new byte[bucketsCount]{ 0 };
	this->N = N;
}

void dyn_bitset::free()
{
	delete[] buckets;
	bucketsCount = 0;
	buckets = nullptr;
}
void dyn_bitset::copyFrom(const dyn_bitset& other)
{
	buckets = new byte[other.bucketsCount];
	for (size_t i = 0; i < other.bucketsCount; i++)
		buckets[i] = other.buckets[i];
	bucketsCount = other.bucketsCount;
	N = other.N;
}

void dyn_bitset::moveFrom(dyn_bitset&& other)
{
	buckets = other.buckets;
	bucketsCount = other.bucketsCount;
	N = other.N;

	other.buckets = nullptr;
	other.bucketsCount = other.N = 0;
}

dyn_bitset::dyn_bitset(const dyn_bitset& other)
{
	copyFrom(other);
}
dyn_bitset& dyn_bitset::operator=(const dyn_bitset& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
dyn_bitset::dyn_bitset(dyn_bitset&& other) noexcept
{
	moveFrom(dcl::move(other));
}
dyn_bitset& dyn_bitset::operator=(dyn_bitset&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(dcl::move(other));
	}
	return *this;
}
dyn_bitset::~dyn_bitset()
{
	free();
}

unsigned dyn_bitset::getBucketIndex(unsigned num) const
{
	return num / elementsInBucket;
}

void dyn_bitset::add(unsigned num)
{
	if (num > N)
		return;

	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = num % elementsInBucket;

	byte mask = 1 << bitIndex;
	buckets[bucketIndex] |= mask;
}

void dyn_bitset::remove(unsigned num)
{

	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = num % elementsInBucket;

	byte mask = ~(1 << bitIndex);
	buckets[bucketIndex] &= mask;
}

bool dyn_bitset::contains(unsigned num) const
{
	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = num % elementsInBucket;

	byte mask = 1 << bitIndex;

	return buckets[bucketIndex] & mask;
}

DCL_END