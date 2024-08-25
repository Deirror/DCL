#pragma once
#include <dcl_defines.h>
#include <tydefuint_t.h>

DCL_BEGIN

class dyn_bitset
{
public:
	dyn_bitset(unsigned n);

	dyn_bitset(const dyn_bitset& other);
	dyn_bitset& operator=(const dyn_bitset& other);

	dyn_bitset(dyn_bitset&& other) noexcept;
	dyn_bitset& operator=(dyn_bitset&& other) noexcept;

	~dyn_bitset();

	void add(unsigned num);
	void remove(unsigned num);
	bool contains(unsigned num) const;

private:
	byte* buckets = nullptr;
	unsigned bucketsCount = 0;
	unsigned N = 0;
	const unsigned elementsInBucket = sizeof(byte) * 8;

	void free();
	void copyFrom(const dyn_bitset& other);
	void moveFrom(dyn_bitset&& other);

	unsigned getBucketIndex(unsigned num) const;
};

DCL_END
