
#include "gcode.hpp"

gcode_ast::~gcode_ast()
{
}

bool gcode_ast::run(machine& m)
{
	_impl->run(m);
}
