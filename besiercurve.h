#ifndef BESIERCURVE_H
#define BESIERCURVE_H

#include <functional>

namespace ___bezier_curve___
{
	template<typename T, typename T2>
	inline T& x( T* v, const T2& p ){ return *(v + p * 2); }
	template<typename T, typename T2>
	inline T& y( T* v, const T2& p ){ return *(v + p * 2 + 1); }
}


template< typename T, typename T2, size_t N >
inline void getRealCubicBezierCurve2d(
		T(&point_xy)[N],
		const T2& step,
		std::function<void(float(&array)[4])> draw )
{
	using namespace ___bezier_curve___;
	static_assert(N == 4 * 2, "Error::getRealCubicBezierCurve2d()::Size_Of_point_xy_Should_Be_8");
	if (!(step < 1.0))throw("Error::getRealCubicBezierCurve2d()::Size_Of_Step_Is_Too_Big");
	if(!(step > 0.0)) throw("Error::getRealCubicBezierCurve2d()::Size_Of_Step_Is_Too_Small");

	const unsigned L = (unsigned)(1.0/step) - 1;

	unsigned start = 0;

	for ( unsigned i = start; i < L; ++i )
	{
		T2 t = (T2)i * step, nt = 1.0 - t;
		T2 t_ = t + step, nt_ = 1.0 - t_;
		T2 nt2 = nt*nt, nt3 = nt2*nt;
		T2 nt2_ = nt_*nt_, nt3_ = nt2_*nt_;
		T2 t2 = t*t, t3 = t2*t;
		T2 t2_ = t_*t_, t3_ = t2_*t_;

		float array[4] = {
			nt3 * x(point_xy,0)
							+ 3 * (nt2 * t * x(point_xy,1) + nt * t2 * x(point_xy,2))
							+ t3 * x(point_xy,3),
			nt3 * y(point_xy,0)
							+ 3 * (nt2 * t * y(point_xy,1) + nt * t2 * y(point_xy,2))
							+ t3 * y(point_xy,3),

			nt3_ * x(point_xy,0)
							+ 3 * (nt2_ * t_ * x(point_xy,1) + nt_ * t2_ * x(point_xy,2))
							+ t3_ * x(point_xy,3),
			nt3_ * y(point_xy,0)
							+ 3 * (nt2_ * t_ * y(point_xy,1) + nt_ * t2_ * y(point_xy,2))
							+ t3_ * y(point_xy,3)
		};

		draw( array );
	}
}
#endif // BESIERCURVE_H
