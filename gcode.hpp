/**
 *
 * gcode.hpp - an internal reprentation for GCODE
 */


namespace gcode{

enum GInterpolation {
	Interpolation_POINT,                                       // 	G0 直接定位。
	Interpolation_LINE,                                        // 	G1 直线插补。
	Interpolation_CYCLE,                                       // 	G2 圆弧插补。
	Interpolation_CYCLE_R,                                     // 	G3 反向圆弧插补。
};

struct Gcommand {
	GInterpolation command;

	double		X, Y, Z, A, B, C;                                  // 6 个坐标轴
};

}                                                           // namespace gcode
