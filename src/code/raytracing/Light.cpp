#include "Light.hpp"

//=======

Light::Light(float x, float y, float z, float _brightness)
{
	position = NewVector3(x, y, z);
	brightness = _brightness;
}