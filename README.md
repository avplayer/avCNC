avCNC
=====

avCNC - truly open source CNC

avCNC is an attempt to create open source CNC machine aside with an CNC control software.

avCNC consists of 5 parts

* avCNCgui - an graphical front end
* avCNCinterpreter - a CORE that interprets G-code in real time
* avCNCinterpolation - a conponent that runs in realtime to control the serve motor or step motor.
* avCNCinterface - a hardware interface that connect CNC machine and CNC control software.
* avCNCmachine - a CNC machine with stardart set of axis.



avCNCgui
========

avCNCgui will run on embeded linux with Wayland as display server. so avCNCgui will use Qt as toolkit.


avCNCinterpreter
================

avCNCinterpreter is controled by avCNCgui. It's mainly for interpreting G-code and turn it into an internal data structure that avCNCinterpolation will relay on.


avCNCinterpolation
==================
avCNCinterpolation is the one that *must* runs *realtime*, so we will need an RT-kernel, or we can have  avCNCinterpolation run on seperated core. avCNCinterpolation generate *motor control signal* to drive motors on the CNC machine.





avCNCinterface
==============
this is not an program ,but a protocol that avCNCinterpolation used to communicate with CNC machine


avCNCmachine
============
this is not an program, but an CAD design that shows how an standard 5 axis CNC machine with avCNCinterface is .
