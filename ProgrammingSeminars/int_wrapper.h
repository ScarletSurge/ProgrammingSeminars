#ifndef INT_WRAPPER_H
#define INT_WRAPPER_H

class int_wrapper
{

private:

	void destruct();

	void copy(
		int_wrapper const& from);

private:

	int* _value;

public:

	/*explicit*/ int_wrapper(
		int value = 0) :
		_value(new int(value))
	{
		//std::cout << *_value;
	}

public:

	~int_wrapper() noexcept
	{
		destruct();
	}

	int_wrapper(
		int_wrapper const& other)
	{
		copy(other);
	}

	int_wrapper& operator=(
		int_wrapper const& other)
	{
		// in some cases, we can implement assignment operator in easier way
		// *this->_value = *other._value;
		// return *this;

		// but in common implementation steps are:
		// 1. self-assignment check
		if (this == &other)
		{
			return *this;
		}

		// 2. destruct old state
		destruct();

		// 3. copy new state
		copy(other);

		//int y = 10;
		//int z = 10;
		//auto func = [&](int x) { return x * y * z; };
		//std::cout << func(10) << std::endl;

		// 4. support Fluent API chain
		return *this;
	}

	// TODO: read about disposable/closable

	// a = b = c = d';
	// a''' += e;
	// builder

	// c = (int_wrapper(a) += b);
	int_wrapper &operator+=(
		int_wrapper const &summand) &;

	int_wrapper operator+(
		int_wrapper const &summand) const;

};

#endif // INT_WRAPPER_H