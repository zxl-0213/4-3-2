#pragma once
#include<iostream>
#include<vector>
#include<assert.h>
using namespace std;

namespace zxl
{
	template<class T>
	class vector
	{
	public:
		//vector是使用3个指针来执行数组的。
		//定义迭代器
		typedef T* iterator;
		typedef const T* const_iterator;


		//begin()
		iterator begin()
		{
			return _start;
		}

		//end()
		iterator end()
		{
			return _finish;
		}

		//const begin
		const_iterator begin()const
		{
			return _start;
		}
		//const end
		const_iterator end()const
		{
			return _finish;
		}
		//构造函数
		vector()
			:_start(nullptr)
			,_finish(nullptr)
			,_endofstorage(nullptr)
		{}

		//拷贝构造函数
		//v2(v1)
		vector(const vector<T>& v)
			:_start(new T[v.capacity()])
		{
			_finish = _start;
			_endofstorage = _start + v.capacity();
			for (size_t i = 0; i < v.size(); ++i)
			{
				*_finish = v[i];
				_finish++;
			}

		}

		//重载=
		//v2=v3
		/*vector<T>& operator=(const vector<T>& v)
		{
			delete[]_start;

			_start = new T[v.capacity()];
			for (size_t i = 0; i < v.size(); i++)
			{
				_start[i] = v._start[i];
			}
			
			_finish = _start + v.size();
			_endofstorage = _start + v.capacity();
			return* this;
		}*/
		//现代写法  operator=  v1=v2
		vector<T>& operator=(vector<T> v)
		{
			swap(v);
			return *this;
		}

		void swap(vector<T>& v)
		{
			::swap(_start, v._start);//::表示全局作用，表示该swap是全局的，不是这个空间里面的。
			::swap(_finish, v._finish);
			::swap(_endofstorage, v._endofstorage);
		}
		//扩容
		//reserve==v.reserve
		void reserve(size_t n)
		{

			if (n > capacity())
			{
				size_t se = size();

				T* tmp = new T[n];

				if (_start)//不为空才有空间值拷贝
				{
					for (size_t i = 0; i < size(); ++i)
					{
						//memcpy(tmp, _start, sizeof(t) * se);此写法不行，因为T如果是string类型，
						//按照字节拷贝就是浅拷贝。
						tmp[i] = _start[i];//此种方法才是正解，因为如果是string，会调用赋值重载，一样是深拷贝。
					}
				}
				
				_start = tmp;
				_finish = _start + se;
				_endofstorage = _start + n;
			}
		}

		//resize  开辟size并且赋值
		void resize(size_t n,const T& val = T())//T()表示赋值为缺省值。如果不传值，就为0.
		{
			if (n < size())
			{
				_finish = _start + n;
			}
			else
			{
				if (n > capacity())
				{
					reserve(n);
				}

				while (_finish <_start+n)
				{
					*_finish = val;
					_finish++;
				}
			}
		}

		//push_back==v.push_back
		void push_back(const T& val)
		{
			/*if (_finish == _endofstorage)
			{
				size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
				reserve(newcapacity);
			}
			*_finish = val;
			_finish++;*/

			insert(_finish-_start,val);
		}

		//insert
		void insert(size_t pos,const T& val)
		{
			assert(pos <= size());
			if (_finish == _endofstorage)
			{
				size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
				reserve(newcapacity);
			}
			T* end = _finish-1;
			while (end >=(_start + pos))
			{
				*(end + 1) = *end;
				end--;
			}
			_start[pos] = val;
			_finish++;
		}
		//pop_back
		void pop_back()
		{
			_finish--;
			
		}
		
		//删除erase
		iterator erase(iterator pos)
		{
			assert(pos <= _finish);
			T* tmp = pos;
			while (tmp < _finish)
			{
				*tmp = *(tmp + 1);
				tmp++;
			}
			_finish--;
			return pos;
		}
		//size
		size_t size()const
		{
			return _finish - _start;
		}

		//capacity
		size_t capacity()const
		{
			return _endofstorage - _start;
		}

		//重载[]
		T& operator[](const size_t i)
		{
			return _start[i];
		}

		//const重载[]
		const T& operator[](const size_t i)const
		{
			return _start[i];
		}
		//析构函数
		~vector()
		{
			delete[]_start;
			_start = _finish = _endofstorage;
		}
	private:
		T* _start;
		T* _finish;
		T* _endofstorage;
	};

	//const 迭代器
	void print(const vector<int>& v)
	{
		vector<int>::const_iterator it = v.begin();
		while (it != v.end())
		{
			cout << *it << " ";
			it++;
		} 
		cout << endl;
	}

	void test_vecttor()
	{
		vector<int> v;
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(1);
		v1.push_back(1);
		v1.push_back(1);

		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		//迭代器遍历
		vector<int>::iterator it = v.begin();
		while(it!=v.end())
		{
			cout << *it << " ";
			it++;
		}
		cout << endl;
		//范围for遍历
		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;
		//operator[]遍历
		for (size_t i = 0; i < v.size() ;++i)
		{
			cout << v[i] << " ";
		}
		cout << endl;

		v.insert(0, 0);
		v.insert(5, 5);
		v.insert(2, -1);
		print(v);

		print(v1);
		v1 = v;
		print(v1);
	}
	void vector_test2()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(2);
		v.push_back(4);
		v.push_back(5);
		v.push_back(6);
		print(v);

		vector<int>::iterator it = v.begin();
		while (it != v.end())
		{
			if (*it % 2 == 0)
			{
				it = v.erase(it);
			}
			else
			{
				it++;
			}
		}
	
		print(v);

		v.resize(10,3);
		print(v);
	}
}
