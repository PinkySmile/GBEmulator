//
// Created by PinkySmile on 27/05/2021.
//

#include <string.h>
#include <stdlib.h>
#include "FakeSTL.hpp"

namespace standard
{
	string::~string()
	{
		free(this->_buffer);
	}

	string::string() :
		_buffer(reinterpret_cast<char *>(malloc(1))),
		_size(0),
		_allocSize(1)
	{
		*this->_buffer = 0;
	}

	string::string(const char *elem) :
		_buffer(strdup(elem)),
		_size(strlen(elem)),
		_allocSize(this->_size + 1)
	{
	}

	string::string(const char *begin, const char *end) :
		_buffer(reinterpret_cast<char *>(malloc(end - begin + 1))),
		_size(end - begin),
		_allocSize(this->_size + 1)
	{
		memcpy(this->_buffer, begin, end - begin);
		this->_buffer[this->_size] = 0;
	}

	string::string(const string &elem) :
		_buffer(reinterpret_cast<char *>(malloc(elem._size + 1))),
		_size(elem._size),
		_allocSize(elem._size + 1)
	{
		memcpy(this->_buffer, elem._buffer, elem._size);
		this->_buffer[this->_size] = 0;
	}

	string string::substr(sizetype pos, sizetype n) const
	{
		return { this->_buffer, this->_buffer + (n == npos ? this->_size : n)};
	}

	sizetype string::find_last_of(char c) const
	{
		auto ptr = strrchr(this->_buffer, c);

		if (!ptr)
			return string::npos;
		return ptr - this->_buffer;
	}

	void string::reserve(sizetype size)
	{
		if (this->_allocSize < size + 1) {
			this->_buffer = reinterpret_cast<char *>(realloc(this->_buffer, size + 1));
			this->_allocSize = size + 1;
		}
	}

	string string::operator+(const string &elem) const
	{
		string result;

		result.reserve(this->_size + elem.size());
		strcpy(result._buffer, this->_buffer);
		strcat(result._buffer, elem._buffer);
		return result;
	}

	string string::operator+(const char *elem) const
	{
		string result;

		result.reserve(this->_size + strlen(elem));
		strcpy(result._buffer, this->_buffer);
		strcat(result._buffer, elem);
		return result;
	}

	string &string::operator+=(const string &elem)
	{
		this->reserve(this->_size + elem.size());
		strcat(this->_buffer, elem._buffer);
		return *this;
	}

	string &string::operator=(const string &elem)
	{
		if (this->_allocSize < elem._size + 1) {
			free(this->_buffer);
			this->_buffer = reinterpret_cast<char *>(malloc(elem._size + 1));
			this->_allocSize = elem._size + 1;
		}
		this->_size = elem._size;
		memcpy(this->_buffer, elem._buffer, elem._size);
		this->_buffer[this->_size] = 0;
		return *this;
	}

	const char *string::c_str() const { return this->_buffer; }
	bool string::empty() const { return this->_size == 0; }
	sizetype string::size() const { return this->_size; }
	sizetype string::length() const { return this->_size; }
}

standard::string operator+(const char *v, const standard::string &v2)
{
	return standard::string(v) + v2;
}