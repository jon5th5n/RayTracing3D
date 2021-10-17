#pragma once

//=======

class Light
{
public:
	Light(float x, float y, float z, float brightness);

public:
	Vector3 position;

	float brightness;
};