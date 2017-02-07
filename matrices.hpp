#pragma once

#include <iostream>
#include <array>
#include <type_traits>
#include <initializer_list>
#include <cmath>

namespace sal
{

	using size_type = unsigned int;

/*	template<typename TT, size_type N>
	class SquareMatrix;*/

	template<typename T, size_type Y, size_type X>
	class Matrix;

	template<typename TT, size_type N>
	using SquareMatrix = Matrix<TT, N, N>;


	template<typename T, size_type Y, size_type X>
	class Matrix
	{
	protected:
		std::array<std::array<T, X>, Y> data;
	public:
		Matrix()
		{
			for(auto& line : data)
			{
				for(auto& element : line)
				{
					element=0;
				}
			}
		}

		const T& operator()(auto y, auto x) const
		{
			return data[y][x];
		}

		T& operator()(auto y, auto x)
		{
			return const_cast<T&>(static_cast<const Matrix<T, Y, X>*>(this)->operator()(y, x));
		}

		const T& at(auto y, auto x) const
		{
			return data[y][x];	
		}

		T& at(auto y, auto x)
		{
			return const_cast<T&>(static_cast<const Matrix<T, Y, X>*>(this)->at(y,x));
		}

		//
		//	Get transposed matrix
		//

		Matrix<T, X, Y> get_T()
		{
			Matrix<T, Y, X> transposed;
			for(auto y=0; y < Y ; y++)
			{
				for(auto x=0; x < X; x++)
				{
					transposed(x, y)=(*this)(y, x);
				}
			}
			return transposed;
		}

		//
		//	Simple multiplying matrix //TODO make more universal
		//
		
		template<typename T2, size_type Z>
		auto operator*(const Matrix<T2, X, Z>& other) -> Matrix<decltype((data[0][0])*other.data[0][0]), Y, Z> const
		{

			Matrix<decltype((data[0][0])*other.data[0][0]), Y, Z> result;
			for(auto y=0; y < Y; y++)
			{
				for(auto z=0; z < Z; z++)
				{
					for(auto x=0; x < X; x++)
					{
						result(y,z)+=data[y][x]*(other(y,z));	
					}

				}
			}
			return result;
		}

/*		//
		//	Getting square matrix by multiplying if possible
		//

		SquareMatrix<T, Y> operator*(const Matrix<T, X, Y>& other) const
		{
			std::cout << "operator sqr" << std::endl;
			SquareMatrix<T, Y> result;
			for(auto y=0; y < Y; y++)
				for(auto z=0; z < Y; z++)
					for(auto x=0; x < X; x++)
						result(y, z)+=(*this)(y, x)*(other(x, z));
			return result;
		}*/

		//
		//	Convert matrix to double - useful for determinate or inverse
		//

		Matrix<double, Y, X> to_double() const
		{
			Matrix<double, Y, X> result;
			for(auto y=0; y < Y; y++)
				for(auto x=0; x < X; x++)
					result(y,x)=static_cast<double>(this->data[y][x]);
			return result;
		}
			
		

	protected:
			
		//
		//	Multiplying by scalar
		//

		template<typename N>
		friend auto operator*(const N& multiplier, const Matrix<T, Y, X>& matrix) -> Matrix<decltype(multiplier*matrix.data[0][0]), Y, X>
		{
			Matrix<decltype(multiplier*matrix.data[0][0]), Y, X> result;
			for(int y=0; y < Y; y++)
			{
				for(int x=0; x < Y; x++)
				{
					result.at(y, x)=multiplier*matrix.data[y][x];
				}
			}
			return result;
		}
		
		//
		//	Ostream operator overload - useful to debug, etc
		//
		
		friend std::ostream& operator<<(std::ostream& os, const Matrix<T, Y, X>& matrix)
		{
			for(const auto& line : matrix.data)
			{
				for(const auto& element : line)
				{
					os << element << "\t";	
				}
				os << "\n";
			}
			return os;
		}

	
	};

	
	//
	//	Get I matrix of given size and type
	//
	
	template<typename T, size_type N>
	SquareMatrix<T, N> IdentityMatrix()
	{
		SquareMatrix<T, N> result;
		for(int i=0; i < N; i++)
		{
			result(i,i)=1;
		}
		return result;
	}

	//
	//	Determinant for square matrices
	//	Gauss algorithm
	//
	
	template<typename T, size_type N>	
	T det(const SquareMatrix<T, N>& matrix)
	{
		const double epsilon=0.0000001f;
		auto copy=matrix.to_double();
		double result=1;
		for(auto n=0; n < N-1; n++)
		{
			auto diagonal_value=copy(n, n);
			if(std::abs(diagonal_value) < epsilon)
			{
				std::cout << n << std::endl;
				return static_cast<T>(0);
			}
			result*=diagonal_value;
			for(auto y=n+1; y < N; y++)
			{
				double to_divide=copy(y, n);
				if(std::abs(to_divide) > epsilon)
				{
					double coefficient=to_divide/copy.at(n, n);
					for(auto x=n; x < N; x++)
					{
						copy(y, x)-=copy(n, x)*coefficient;
					}
				}
			}
		}
		result*=copy(N-1, N-1);
		return static_cast<T>(result);
		
	}

	//
	//	Faster 2x2 determinant
	//

	template<typename T>
	T det(const SquareMatrix<T, 2>& matrix)
	{
		return matrix(0,0)*matrix(1,1)-matrix(1,0)*matrix(0,1);
	}
	
	//
	//	Determinate for 3x3 matrix
	//	Sarrus' rule
	//

	template<typename T>
	T det(const SquareMatrix<T, 3>& matrix)
	{
		return matrix(0,0)*matrix(1,1)*matrix(2,2)+matrix(2,0)*matrix(0,1)*matrix(1, 2)+matrix(0,2)*matrix(1,0)*matrix(2,1)-matrix(0,2)*matrix(1,1)*matrix(2,0)-matrix(0,0)*matrix(2,1)*matrix(1,2)-matrix(2,2)*matrix(1,0)*matrix(0,1);
	}

	
}

