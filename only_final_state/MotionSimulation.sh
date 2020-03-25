#!/bin/bash
echo "Info: note that passing too big too small values of force/velocity"
echo "may result in weird animation at the end"
echo
echo "You should put values between 100 and 1000 for good animation"
echo
echo "As well note that passing initial position that is not 0"
echo "may result in throwing object out of window and making impossible to see it"
echo "To see animation leave initial position with (0,0,0) vector"
echo "If you want only to see final state then change it"
echo
echo "You can also pass velocity (vx, vy or vz) , location (rx,ry or rz), time (t), sin() , cos(), tan(), brackets, exponent (^) or factorial (!) to functions"
echo "For example if you want to simulate harmonic oscillator:"
echo "Fx = -2500 * rx"
echo
echo "Example simulations:"
echo "Fx=-5000*rx Fy=0 Fz=0 x=0 y=0 z=0 Vx=150 Vy=0 Vz=0 t=5 -> harmonic oscillator"
echo "Fx=-15*vx Fy=750 Fz=0 x=0 y=0 z=0 Vx=135 Vy=0 Vz=0 t=5 -> oblique projection with air resistance"
echo
echo "Please write your function F(t), where F(t) = (Fx,Fy,Fz): "
echo "Fx = "
read Fx
echo "Fy = "
read Fy
echo "Fz = " 
read Fz
echo
echo "Please specify the initial state, r0 = (x,y,z)
x = "
read x
echo "y = "
read y
echo "z = "
read z
echo
echo "Please specify the initial velocity, v0 = (Vx,Vy,Vz)
 Vx = "
read Vx
echo "Vy = "
read Vy
echo "Vz = "
read Vz
echo "Please specify the end time in seconds: "
read time
./a.out $Fx $Fy $Fz $x $y $z $Vx $Vy $Vz $time

