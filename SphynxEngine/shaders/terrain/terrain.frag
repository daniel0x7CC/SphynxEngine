#version 330 core
 
layout (location=0) out vec4 color;	//fragment shader output

void main()
{
	//output solid white color as fragment output
   color = vec4(1,1,1,1);
}