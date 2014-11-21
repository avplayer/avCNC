/**
 *
 * main.cpp  -  the main file for avCNC
 *
 */

/*
 * PLL 缓冲。PLL 缓存，根据电机的物理特性来决定输出速度。
 * 并且根据剩下的 PLL 缓冲的大小来决定是否进一步解析 G 代码。
 *
 */

#include <bitset>
#include <boost/circular_buffer.hpp>
#include <functional>
#include <boost/function.hpp>
#include <vector>
#include <boost/scope_exit.hpp>
#include <boost/logic/tribool.hpp>

#include "coroutine.hpp"
#include "avos.hpp"

// 用一个 N bits 长的数字表示每一个时钟周期 所有输出信号线的状态
// 每个轴需要 3 条信号，一条使能，一条方向，一条脉冲
// 3轴需要 9 条
typedef std::bitset<9> out_signal_pins_t;

struct avCNC_axis_pulse
{
	std::bitset<1> step_dir;
	std::bitset<1> step_pulse;
};

struct motor_state
{
	// 当前运动方向
	std::bitset<1> step_dir;

	// 当前位置，使用距离原点的步数
	std::size_t location;

	//  上一个脉冲的时间，用来计算下一个脉冲输出时间
	std::size_t last_pulse;
	//  最近两次脉冲的间隔时间，用来指示当前速度，以便作出加减速考虑
	std::size_t last_interval;

	//  列队里至少需要多少步，否则要开始减速过程
	std::size_t least_steps;

	//  =========== readonly after initialize ===========
	// 每单位（毫米）步进数
	std::size_t stepperunit;

	// 工作范围，单位是步数
	std::pair<std::size_t, std::size_t> range;

	// 被认为需要执行加减速度考虑的最长脉冲时间, 超过
	// 这个时间，每个脉冲都可以独立步进，而无需考虑加
	// 减速度问题
	std::size_t max_pulse_interval;
	// 最低脉冲间隔，也就是限定了电机的最高速度
	std::size_t min_pulse_interval;

	// 加速度和减速使用的数据, 以便正确作出加减速选择
	double acceleration;
	double deacceleration;
};


static struct avCNC_PLL
{
	//out_signal_pins_t
	boost::circular_buffer<out_signal_pins_t> all_outs;

}avCNC_PLL_buffer;

// 记录电机加速曲线的。
struct accel_table{

};

void output_pins(const out_signal_pins_t & p)
{
	// TODO output pins
}

enum Axis {
	Axis_X,
	Axis_Y,
	Axis_Z,
	Axis_A,
	Axis_B,
	Axis_C,
};

enum motor_speed_guide_t
{
	SPEED_DECREASE = -1,
	SPEED_MAINTAIN = 0,
	SPEED_INCREASE = 1
};



class avCNC_PLL_output : avCNC::coro::coroutine
{
	// prepared signals for output.
	out_signal_pins_t prepared_signals;

public:
	avCNC_PLL_output() {}


	void operator()()
	{
		double distance, planed_speed;

		AVCNC_CORO_REENTER(this)
		{
			// 协程，正式开始输出 pinouts
			output_pins(prepared_signals);

			// 检查大小，小于设定值，就要申请调度插补器。
			if (! avCNC_PLL_buffer.all_outs.full())
			{
				// TODO 唤醒插补协程
			}

			// 默认就是减速，除非找到合理的保持速度或者加速的原因
			motor_speed_guide_t ms1 = SPEED_DECREASE;


			// 寻找加速原因

			//  第一个原因是，列队后续长度很长, 如果执意执行减速，会导致列队没有数据后速度就降低为0了。
			//  如果是这样，那么可以不需要减速。但是如果采取了加速，意味着，需要更长的后续数据


			//  为每个轴跑一次

			motor_speed_guide_t ms[3];

			ms[0] = motor_speed_look_ahead(Axis_X);
			ms[1] = motor_speed_look_ahead(Axis_Y);
			ms[2] = motor_speed_look_ahead(Axis_Z);

			// 如果大家都同意增加 speed 才能增加
			if (ms[0] ==  SPEED_INCREASE && ms[1] == SPEED_INCREASE&& ms[2] == SPEED_INCREASE)
			{
				ms1 = SPEED_INCREASE;
				
			}else if (ms[0] !=  SPEED_DECREASE && ms[1] != SPEED_DECREASE && ms[2] != SPEED_DECREASE)
			{
				ms1 = SPEED_MAINTAIN;
			}

			// 首先判断当前的速度是否到达 F 设定的速度，否，则重新设定


			// 然后开始速度设定，因为基本上一个移动距离已经固定了，所以速度就是指时间。



			// 计算下次执行时间 - aka， 控制电机速度

 			// 当前电机速度， 还有刀具速度都要考虑到。

 			// get next distance
 			distance = get_next_pol();

 			// 然后计算需要的速度
 			planed_speed = plane_speed();
 			// 根据速度和距离，计算下次脉冲输出的时间并设定下次调度为那个时间

			// 设定下次执行。

		}
	}

private:
    double get_next_pol();

    // 寻找该轴承是否有能提高速度的可能性，还是必须降低速度
    motor_speed_guide_t motor_speed_look_ahead(Axis)
    {
		return SPEED_DECREASE;
	}
	
    double plane_speed();
};


int main()
{
	// initialize
//
	avOS::init();

	// run the loop

	avOS::sched_run();
	return 0;
}