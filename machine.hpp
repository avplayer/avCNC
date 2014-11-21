#pragma once

struct Axis{
	double X, Y, Z, A, B, C;
};

Axis operator + (const Axis& a, const Axis& b)
{
	Axis r;
	r.X = a.X + b.X;
	r.Y = a.Y + b.Y;
	r.Z = a.Z + b.Z;
	r.A = a.A + b.A;
	r.B = a.B + b.B;
	r.C = a.C + b.C;
	return r;
}

Axis operator - (const Axis& a, const Axis& b)
{
	Axis r;
	r.X = a.X - b.X;
	r.Y = a.Y - b.Y;
	r.Z = a.Z - b.Z;
	r.A = a.A - b.A;
	r.B = a.B - b.B;
	r.C = a.C - b.C;
	return r;
}

class machine
{
	// 6 轴绝对位置
	Axis phy;

	// 偏移量
	Axis offset;

	// 从绝对位置和偏移量计算当前工作坐标
	const Axis& current() const
	{
		return phy - offset;
	}


public:
    virtual void rapit_move(Axis dest) = 0;
    virtual void liner_move(Axis dest) = 0;
};

// 演示的模拟机器
class machine_sim : public machine
{
    virtual void rapit_move(Axis dest)
	{

	}

};

