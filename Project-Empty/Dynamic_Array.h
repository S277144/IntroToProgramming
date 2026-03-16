#pragma once

class DynamicArray
{
public:

	DynamicArray(int capacity) : _capacity{ capacity }, _Size{ 0 }
	{
		if (_capacity == 0) _capacity = 1;
		_data = new int[_capacity];
	}

	~DynamicArray()
	{
		delete[] _data;
	}

	int getValue(int index) const {
		return _data[index];
	}

	void push_back(int value)
	{
		if (_Size == _capacity)
		{
			_capacity * +2;
			int* newArray = new int[_capacity];
			for (int i = 0; i < _Size; i++)
			{
				newArray[i] = _data[i];
			}
			delete[] _data;
			_data = newArray;
		}

		_data[_Size] = value;
		_Size++;
	}

	int size() const
	{
		return _capacity;
	}

	int capacity() const {
		return _capacity;
	}

private:
	int _capacity;
	int _Size;
	int* _data;
};
