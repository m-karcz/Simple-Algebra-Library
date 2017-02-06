#pragma once
#include <array>
#include <algorithm>
#include <string>
#include <iostream>
#include <cmath>
#include <type_traits>

namespace sal
{
	template<typename T, unsigned int N>
	class Vector
	{
	public:
		template<typename ... X>
		constexpr Vector(X&&... x) : data{std::forward<X>(x)...}
		{
			static_assert(sizeof...(x) == N, "Invalid number of arguments");
		}

		Vector(const Vector<T, N>& other)
		{
			std::copy(other.data.begin(), other.data.end(), data.begin());
		}

		Vector(Vector<T, N>& other) : Vector(static_cast<const Vector&>(other)) {}

		Vector(const Vector<T, N>&& other)
		{
			data=std::move(other.data);
		}

		Vector(Vector<T, N>&& other) : Vector(static_cast<const Vector&&>(other)) {}




		//
		//	Getting leghth of vector using sqrt of dot product of itself
		//

		template<typename U=T>
		U length()
		{
			static_assert(std::is_arithmetic<T>::value, "Type is not arithmetic!");
			return std::sqrt(std::accumulate(data.begin(), data.end(), U(0), [](U sum, T value){ return sum+value*value; }));
		}
		
		//
		//	Dot product of 2 vectors
		//
			
		template<typename X=T>
		X operator*(const Vector<T, N>& other)
		{
			X result=0;
			for(std::size_t i=0; i<N; i++)
			{
				result+=this->data[i]*other.data[i];
			}
			return result;
		}

		//
		//	Multiplying by scalar
		//
	
		template<typename X>
		Vector<T, N> operator*(const X& num)
		{
			return num*(*this);
		}
	private:
		std::array<T, N> data;

		//
		//	std::ostream operator to print out vector in [x, y, ...]^T way
		//

		friend std::ostream& operator<<(std::ostream& os, Vector<T,N>& vector)
		{
			
			os << "[";
			if(N>0)
			{
				os << vector.data[0];
				if(N > 0)
				{
					for(unsigned int i=1; i < N; i++)
					{
						os << ", " << vector.data[i];
					}
				}	
			}
			os << "]^T";
			return os;
		}

		//
		//	Multiplying by scalar
		//

		template<typename X>
		friend Vector<T, N> operator*(const X& num, const Vector<T, N>& vector)
		{
			static_assert(std::is_arithmetic<X>::value, "Scalar is not arithmetic type!");
			Vector<T, N> result=vector;
			for(auto& value : result.data)
			{
				value*=num;
			}
			return result;

		}
	};

	
}

