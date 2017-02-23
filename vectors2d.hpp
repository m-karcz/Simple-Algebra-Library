#pragma once
#include "matrices.hpp"

namespace MyAlgLib
{
	template <typename T=double>
	using Vector2d = Vector<T, 2>;

	template <typename T=double>
	using Vector2dT = VectorT<T, 2>;
	
	template <typename T=double>
	using Matrix2d = SquareMatrix<T, 2>;

	template <typename I>
	I deg2rad(I deg)
	{
		static_assert(std::is_arithmetic<I>::value, "Input is not integral type");
		return deg/180.0*M_PI;
	}

	template <typename I>
	I rad2deg(I rad)
	{
		static_assert(std::is_arithmetic<I>::value, "Input is not integral type");
		return rad*180.0/M_PI;
	}
	
	template <typename T=double>
	Matrix2d<T> rotation_matrix_rad(double rad)
	{
		Matrix2d<T> matrix;
		double cos=std::cos(rad);
		double sin=std::sin(rad);
		matrix(0,0)=matrix(1,1)=cos;
		matrix(1,0)=sin;
		matrix(0,1)=-sin;
		return matrix;
	}

	template <typename T>
	T& get_x(Vector2d<T>& vector)
	{
		return vector(0,0);
	}

	template <typename T>
	T get_x(const Vector2d<T>& vector)
	{
		return vector(0,0);
	}

	template <typename T>
	T& get_x(Vector2dT<T>& vector)
	{
		return vector(0,0);
	}

	template <typename T>
	T get_x(const Vector2dT<T>& vector)
	{
		return vector(0,0);
	}

	template <typename T>
	T& get_y(Vector2d<T>& vector)
	{
		return vector(1,0);
	}

	template <typename T>
	T get_y(const Vector2d<T>& vector)
	{
		return vector(1,0);
	}

	template <typename T>
	T& get_y(Vector2dT<T>& vector)
	{
		return vector(0,1);
	}

	template <typename T>
	T get_y(const Vector2dT<T>& vector)
	{
		return vector(0,1);
	}

	template <typename T>
	Vector2d<T> Vector2d_factory(T x, T y)
	{
		Vector2d<T> vector;
		get_x(vector)=x;
		get_y(vector)=y;
		return vector;
	}

	template <typename T>
	T arg(const Vector2d<T>& vector)
	{
		if(get_x(vector)==0.0)
		{
			return 0;
		}
		return std::atan( get_y(vector) / get_x(vector) );
	}

	
}
