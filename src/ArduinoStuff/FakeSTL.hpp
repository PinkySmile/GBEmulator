//
// Created by PinkySmile on 26/05/2021.
//

#ifndef GBEMULATOR_FAKESTL_HPP
#define GBEMULATOR_FAKESTL_HPP



#include <string.h>
#include <stdlib.h>

template<typename T>
void *operator new(size_t, T *ptr)
{
	return ptr;
}

namespace standard
{
	typedef unsigned long long sizetype;
	template<typename T>
	struct remove_reference
	{
		typedef T type;
	};

	template<typename T>
	constexpr T &&move(T &&t) noexcept
	{
		return static_cast<T &&>(t);
	}

	template<typename T>
	constexpr T &&forward(T &t) noexcept
	{
		return static_cast<T &&>(t);
	}

	class string {
	private:
		char *_buffer;
		sizetype _size;
		sizetype _allocSize;

	public:
		static constexpr sizetype npos = -1;

		~string();
		string();

		string(const char *elem);
		string(const char *begin, const char *end);
		string(const string &elem);
		string substr(sizetype pos, sizetype n = string::npos) const;
		sizetype find_last_of(char c) const;
		void reserve(sizetype size);
		string operator+(const string &elem) const;
		string operator+(const char *elem) const;
		string &operator+=(const string &elem);
		string &operator=(const string &elem);
		const char *c_str() const;
		bool empty() const;
		sizetype size() const;
		sizetype length() const;
	};

	template<typename T>
	class vector {
	private:
		T *_buffer;
		sizetype _size;
		sizetype _allocSize;

		template<typename ...Args>
		inline void _insert(const T &elem, Args &...args)
		{
			memcpy(&this->_buffer[this->_size], &elem, sizeof(elem));
			this->_size++;
			this->_insert(args...);
		}

		inline void _insert() {}

	public:
		vector() : _buffer(nullptr), _size(0), _allocSize(0) {}

		vector(sizetype size) : vector()
		{
			this->resize(size);
		}

		vector(sizetype size, const T &value) : vector()
		{
			this->reserve(size);
			while (size--)
				this->push_back(value);
		}

		template<typename ...Args>
		vector(Args &&...args)
		{
			const auto n = sizeof...(Args);

			this->_buffer = reinterpret_cast<T *>(malloc(n * sizeof(T)));
			this->_allocSize = n;
			this->_size = 0;
			this->_insert(args...);
		}

		vector(vector<T> &&other) {
			this->swap(other);
		}

		~vector() {
			if (!__has_trivial_destructor(T)) {
				for (int i = 0; i < this->_size; i++)
					this->_buffer[i].~T();
			}
			free(this->_buffer);
		}

		vector<T> &operator=(const vector<T> &other)
		{
			this->clear();
			this->reserve(other.size());
			while (this->_size != other.size()) {
				this->_buffer[this->_size] = other[this->_size];
				this->_size++;
			}
			return *this;
		}

		void swap(vector<T> &other) {
			auto oldB = this->_buffer;
			auto oldS = this->_size;
			auto oldA = this->_allocSize;

			this->_buffer    = other._buffer;
			this->_size      = other._size;
			this->_allocSize = other._allocSize;
			other._buffer    = oldB;
			other._size      = oldS;
			other._allocSize = oldA;
		}

		void resize(sizetype newSize)
		{
			if (newSize > this->_size) {
				this->reserve(newSize);
				while (this->_size != newSize) {
					new (&this->_buffer[this->_size]) T;
					this->_size++;
				}
			} else if (newSize < this->_size) {
				if (__has_trivial_destructor(T))
					this->_size = newSize;
				else while (this->_size != newSize) {
					this->_size--;
					this->_buffer[this->_size].~T();
				}
			}
		}

		void resize(sizetype newSize, const T &value)
		{
			if (newSize > this->_size) {
				this->reserve(newSize);
				while (this->_size != newSize) {
					new (&this->_buffer[this->_size]) T(value);
					this->_size++;
				}
			} else if (newSize < this->_size) {
				if (__has_trivial_destructor(T))
					this->_size = newSize;
				else while (this->_size != newSize) {
						this->_size--;
						this->_buffer[this->_size].~T();
					}
			}
		}

		void resize(sizetype newSize, T &&value)
		{
			if (newSize > this->_size) {
				this->reserve(newSize);
				while (this->_size != newSize) {
					new (&this->_buffer[this->_size]) T(value);
					this->_size++;
				}
			} else if (newSize < this->_size) {
				if (__has_trivial_destructor(T))
					this->_size = newSize;
				else while (this->_size != newSize) {
						this->_size--;
						this->_buffer[this->_size].~T();
					}
			}
		}

		void push_back(T &v)
		{
			this->reserve(this->_size + 1);
			new (&this->_buffer[this->_size]) T(v);
			this->_size++;
		}

		void push_back(T &&v)
		{
			this->reserve(this->_size + 1);
			new (&this->_buffer[this->_size]) T(v);
			this->_size++;
		}

		void reserve(sizetype newSize)
		{
			if (newSize > this->_allocSize) {
				this->_buffer = reinterpret_cast<T *>(realloc(this->_buffer, newSize * sizeof(T)));
				this->_allocSize = newSize;
			}
		}

		void clear() {
			if (!__has_trivial_destructor(T)) {
				for (int i = 0; i < this->_size; i++)
					this->_buffer[i].~T();
			}
			this->_size = 0;
		}

		sizetype size() const { return this->_size; }
		T *data() { return this->_buffer; }

		T &operator[](sizetype i) { return this->_buffer[i]; }
		const T &operator[](sizetype i) const { return this->_buffer[i]; }

		T *begin() { return this->_buffer; }
		const T *begin() const { return this->_buffer; }

		T *end() { return this->_buffer + this->_size; }
		const T *end() const { return this->_buffer + this->_size; }
	};

	template<typename T1, typename T2>
	class pair {
	public:
		T1 first;
		T2 second;

		pair(const T1 &&f, const T2 &&s) : first(f), second(s) {}
	};

	template<typename keyType, typename valueType>
	class map {
	private:
		standard::vector<pair<keyType, valueType>> _buffer;

	public:
		template<typename ...Args>
		map(Args &&...list) :
			_buffer(forward<Args>(list)...)
		{}
		map(const standard::vector<pair<keyType, valueType>> &&buffer) :
			_buffer(reinterpret_cast<const standard::vector<pair<keyType, valueType>> &&>(buffer))
		{}

		pair<keyType, valueType> *find(const keyType &elem) const{
			auto begin = this->begin();

			while (begin < this->end())
			{
				if (begin->first == elem)
					return begin;
				begin++;
			}
			return this->end();
		}
		pair<keyType, valueType> *begin() { return this->_buffer.begin(); }
		const pair<keyType, valueType> *begin() const { return this->_buffer.begin(); }
		pair<keyType, valueType> *end() { return this->_buffer.end(); }
		const pair<keyType, valueType> *end() const { return this->_buffer.end(); }
	};
}

standard::string operator+(const char *v, const standard::string &v2);


#endif //GBEMULATOR_FAKESTL_HPP
