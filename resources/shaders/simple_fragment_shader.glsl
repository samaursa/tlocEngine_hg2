#version 120

varying lowp vec4 vVaryingColor;

void main(void)
{
	gl_FragColor = vVaryingColor;
}