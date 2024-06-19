#include "SpacialObject.h"

SpacialObject::SpacialObject() {
	// Initialize Position, Rotation, Scale to default values
	// Initialize AmbientColor, DiffuseColor, SpecularColor to default values
	// Initialize Shininess to default value
	// Initialize TextureID to 0 (no texture)
}

void SpacialObject::setPosition(GLfloat x, GLfloat y, GLfloat z) {
	Position[0] = x;
	Position[1] = y;
	Position[2] = z;
}

void SpacialObject::setRotation(GLfloat x, GLfloat y, GLfloat z) {
	Rotation[0] = x;
	Rotation[1] = y;
	Rotation[2] = z;
}

void SpacialObject::setScale(GLfloat x, GLfloat y, GLfloat z) {
	Scale[0] = x;
	Scale[1] = y;
	Scale[2] = z;
}

GLfloat* SpacialObject::getPosition() {
	return Position;
}

GLfloat* SpacialObject::getRotation() {
	return Rotation;
}

GLfloat* SpacialObject::getScale() {
	return Scale;
}

void SpacialObject::setAmbientColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	AmbientColor[0] = r;
	AmbientColor[1] = g;
	AmbientColor[2] = b;
	AmbientColor[3] = a;
}

void SpacialObject::setDiffuseColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	DiffuseColor[0] = r;
	DiffuseColor[1] = g;
	DiffuseColor[2] = b;
	DiffuseColor[3] = a;
}

void SpacialObject::setSpecularColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	SpecularColor[0] = r;
	SpecularColor[1] = g;
	SpecularColor[2] = b;
	SpecularColor[3] = a;
}

void SpacialObject::setShininess(GLfloat shininess) {
	Shininess = shininess;
}

GLfloat* SpacialObject::getAmbientColor() {
	return AmbientColor;
}

GLfloat* SpacialObject::getDiffuseColor() {
	return DiffuseColor;
}

GLfloat* SpacialObject::getSpecularColor() {
	return SpecularColor;
}

GLfloat SpacialObject::getShininess() {
	return Shininess;
}


void SpacialObject::addChildObject(SpacialObject* child) {
	children.push_back(child);
}

std::vector<SpacialObject*>& SpacialObject::getChildren() {
	return children;
}
