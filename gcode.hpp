
#pragma once

/**
 *
 * gcode.hpp - an internal reprentation for GCODE
 */
#include <memory>
#include <type_traits>

#include "machine.hpp"


namespace detail{
	class gcode_ast_impl
	{
		virtual bool run(machine & m) = 0;
		virtual ~gcode_ast_impl(){}
	};

	template<class RealASTObject>
	class gcode_ast_wrapper : public gcode_ast_impl
	{
		virtual bool run(machine & m)
		{
			m_impl.run(m);
		}

		gcode_ast_wrapper(const RealASTObject& ast)
		{
			m_impl = ast;
		}

	private:
		RealASTObject m_impl;
	};
}

struct gcode_ast{
	bool run(machine & m);

	~gcode_ast();

	template<class RealType>
	gcode_ast(const RealType& ast)
	{
		auto impl = new gcode_ast_wrapper<std::remove_reference<RealType>::type>(ast);
		_impl.reset(dynamic_cast<gcode_ast_impl>(impl));
	}

private:
	std::unique_ptr<gcode_ast_impl> _impl;
};

namespace gcode{

// G00 命令 快速定位
struct G00{
	Axis dest;

	bool run(machine & m)
	{
		m.rapit_move(dest);
	}
};

// G01 命令, 直线插补
struct G01{
	Axis dest;

	bool run(machine & m)
	{
		m.liner_move(dest);
	}

};

}                                                           // namespace gcode
