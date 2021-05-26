//
// Created by PinkySmile on 26/05/2021.
//

#ifndef GBEMULATOR_MEMORYSTL_HPP
#define GBEMULATOR_MEMORYSTL_HPP


#include "FakeSTL.hpp"

namespace standard
{
	template<typename T>
	class unique_ptr {
	private:
		T *_ptr;

	public:
		unique_ptr() : _ptr(nullptr) {};
		unique_ptr(T *ptr) : _ptr(ptr) {};
		template<typename T2>
		unique_ptr(unique_ptr<T2> &&other) {
			this->_ptr = static_cast<T *>(other.release());
		}
		~unique_ptr() { delete this->_ptr; }

		void reset(T *ptr) {
			delete this->_ptr;
			this->_ptr = ptr;
		}

		T *release()
		{
			auto t = this->_ptr;

			this->_ptr = nullptr;
			return t;
		}

		T &operator*() const {
			return *this->_ptr;
		}

		T *operator->() const {
			return this->_ptr;
		}
	};

	template<typename T>
	struct _MakeUniq
	{
		typedef unique_ptr<T> single_object;
	};

	template<typename T, typename... Args>
	inline typename _MakeUniq<T>::single_object make_unique(Args &&...args)
	{
		return unique_ptr<T>(new T(forward<Args>(args)...));
	}
}


#endif //GBEMULATOR_MEMORYSTL_HPP
