#include "GOLightSourceData.h"

void GOLightSourceData::SetData(GOLightSourceData* other)
{
	if (other == nullptr)
		return;

	_light_ambient = other->_light_ambient;
	_light_diffuse = other->_light_diffuse;
	_light_specular = other->_light_specular;
	_spot_direction = other->_spot_direction;
	_spotlight_cuttoff = other->_spotlight_cuttoff;
	_shininess = other->_spotlight_cuttoff;
	_exponent = other->_exponent;
}
