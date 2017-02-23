#pragma once
#include "matrices.hpp"

namespace MyAlgLib
{
	using size_type = unsigned int;
	
	template<typename T, size_type N>
	class SquareMatrix : public Matrix<T, N, N>
	{
	public:
		SquareMatrix() : Matrix<T, N, N>()
		{
			
		}

		SquareMatrix(const Matrix<T, N, N>& matrix)
		{
			for(auto y=0; y < N; y++)
			{
				for(auto x=0; x < N; x++)
				{
					this->at(y,x)=matrix.at(y,x);
				}
			}
		}
		SquareMatrix<double, N> to_double() const
		{
			SquareMatrix<double, N> result;
			for(auto y=0; y < N; y++)
				for(auto x=0; x < N; x++)
					result(y, x)=static_cast<double>((*this)(y, x));
			return result;	
		}

	protected:
			

	};
	
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
	
	template<typename T, size_type N>	
	T det(const SquareMatrix<T, N>& matrix)
	{
		const double epsilon=0.0000001f;
		auto copy=matrix.to_double();
		double result=1;
		std::cout << matrix << std::endl;
		std::cout << copy << std::endl;
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
						copy(y, x)-=copy(y, x)*coefficient;
					}
				}
			}
		}
		result*=copy(N-1, N-1);
		std::cout << copy << std::endl;
		std::cout << "==" << std::endl;
		return static_cast<T>(result);
		
	}

	template<typename T, size_type N>
	T det(const Matrix<T, N, N>& matrix)
	{
		return det(matrix * IdentityMatrix<T, N>());
	}
	
}
