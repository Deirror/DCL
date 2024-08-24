#include "strpool.h"
#include <strfunc.h>
#include <except.h>
#include <tydefios.h>

DCL_BEGIN

void strpool::resize(size_t cap)
{
	if (cap <= capacity)
	{
		return;
	}

	StringNode* newNodes = new StringNode[cap]{};

	for (size_t i = 0; i < size; i++)
	{
		newNodes[i] = nodes[i];
	}

	delete[] nodes;
	nodes = newNodes;
	capacity = cap;
}

int strpool::find(const char* str, bool& found) const
{
	int left = 0;
	int right = size - 1;

	while (left <= right)
	{
		int mid = (right - left) / 2 + left;
		int cmp = str_cmpr(nodes[mid].data, str);

		if (cmp == 0)
		{
			found = true;
			return mid;
		}
		else if (cmp > 0)
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}

	found = false;
	return left;
}

const char* strpool::insert(const char* str, size_t index)
{
	if (index > size)
	{
		throw dcl::out_of_bound();
	}

	if (size == capacity)
	{
		resize(calculateGrowth());
	}

	for (int i = size - 1; i >= (int)index; i--)
	{
		nodes[i + 1] = nodes[i];
	}

	nodes[index].allocateData(str);
	nodes[index].referenceCount = 1;

	++size;
	return nodes[index].data;
}

void strpool::removeInternal(int idx)
{
	if (idx >= size)
	{
		throw dcl::out_of_bound();
	}

	delete[] nodes[idx].data;

	for (int i = idx; i < size - 1; i++)
	{
		nodes[i] = nodes[i + 1];
	}

	nodes[size - 1].data = nullptr;
	nodes[size - 1].referenceCount = 0;

	size--;
}

size_t strpool::calculateGrowth() const
{
	return capacity + capacity / 2;
}

strpool::strpool() : nodes(nullptr), size(0), capacity(0)
{
	resize(8);
}

const char* strpool::getString(const char* str)
{
	bool found = false;
	int currentIndex = find(str, found);

	if (found)
	{
		nodes[currentIndex].referenceCount++;
		return nodes[currentIndex].data;
	}

	return insert(str, currentIndex);
}

void strpool::removeString(const char* str)
{
	bool found = false;
	int idx = find(str, found);

	if (!found) 
	{
		return;
	}

	if (nodes[idx].referenceCount == 1)
	{
		removeInternal(idx);
	}
	else
	{
		nodes[idx].referenceCount--;
	}
}

void strpool::debug() const
{
	for (size_t i = 0; i < size; i++)
	{
		dcl::cout << nodes[i].data << " ";
	}
	dcl::cout << '\n';
}

strpool::~strpool()
{
	for (size_t i = 0; i < size; i++)
		delete[] nodes[i].data;

	delete[] nodes;
}

void strpool::StringNode::allocateData(const char* str)
{
	size_t len = str_len(str);
	data = new char[len + 1] {};
	str_copy(data, str);
}

DCL_END