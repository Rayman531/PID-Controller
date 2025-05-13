# PID-Controller

This is code for a PID controller with the purpose of balancing a ping pong ball in the middle of a scale.
The feedback system consisted of and infrared sensor which detected the ball's distance, it then relayed that information through an Arduino Uno microcontroller which calculated the error, based on this the PID controller would adjust the position of a servo motor to tilt the scale and move the ball back to its center.
The code contains constants kp, ki, kd which can be tweaked to change the the speed at which the system reacted to the movement of the ball

For more details on the project visit my portfolio
