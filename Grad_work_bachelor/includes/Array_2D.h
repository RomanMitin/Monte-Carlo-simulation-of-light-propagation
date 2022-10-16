#pragma once

#include <cinttypes>
#include <algorithm>
#include <vector>
#include <assert.h>


template<typename T>
class Array_2d_t
{
public:
	
	Array_2d_t()
		:size_row(0), size_col(0), data(nullptr)
	{}

	Array_2d_t(size_t size_row, size_t size_col)
		:size_row(size_row), size_col(size_col), data(nullptr)
	{
		if (size_row * size_col)
			data = new T[size_row * size_col];
	}

	Array_2d_t(const Array_2d_t& rhs)
		: size_row(rhs.size_row), size_col(rhs.size_col), data(nullptr)
	{
		if (size_row * size_col)
		{
			data = new T[size_row * size_col];

			std::copy(rhs.data, rhs.data + rhs.size_row * rhs.size_col, data);
		}
	}

	Array_2d_t(Array_2d_t&& rhs)
		:size_row(rhs.size_row), size_col(rhs.size_col), data(rhs.data)
	{
		rhs.size_col = 0;
		rhs.size_row = 0;
		rhs.data = nullptr;
	}

	Array_2d_t& operator=(const Array_2d_t& rhs)
	{
		if (this != &rhs)
		{
			delete[] data;

			size_row = rhs.size_row;
			size_col = rhs.size_col;

			if (size_row * size_col)
			{
				data = new T[size_row * size_col];

				std::copy(rhs.data, rhs.data + rhs.size_row * rhs.size_col, data);
			}
			else
				data = nullptr;
		}

		return *this;
	}

	Array_2d_t& operator=(Array_2d_t&& rhs)
	{
		if (this != &rhs)
		{
			delete[] data;

			size_row = rhs.size_row;
			size_col = rhs.size_col;

			data = rhs.data;

			rhs.data = nullptr;
		}

		return *this;
	}

	T* operator[](size_t ind)
	{
		assert(ind < size_row);

		return data + ind * size_col;
	}

	~Array_2d_t()
	{
		delete[] data;
	}
private:

	size_t size_row;
	size_t size_col;
	T* data;
};

