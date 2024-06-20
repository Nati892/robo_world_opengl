#include "DrawableObject.h"

DrawableObject::DrawableObject() {
	// Initialize Position, Rotation, Scale to default values
	// Initialize AmbientColor, DiffuseColor, SpecularColor to default values
	// Initialize Shininess to default value
	// Initialize TextureID to 0 (no texture)
}

DrawableObject::~DrawableObject()
{
}

void DrawableObject::DrawObject()
{
	printf("DrawableObject called from papa,does nothing");
}

void DrawableObject::PushObjectTransformMatrix()
{
	glPushMatrix();
	glTranslatef(this->Position[0], this->Position[1], this->Position[2]);
	glRotatef(this->Rotation[0], 1, 0, 0);
	glRotatef(this->Rotation[1], 0, 1, 0);
	glRotatef(this->Rotation[2], 0, 0, 1);
	glScalef(this->Scale[0], this->Scale[1], this->Scale[2]);
}

void DrawableObject::PopObjectTransformMatrix()
{
	glPopMatrix();
}

void DrawableObject::SetObjectMaterial()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, this->AmbientColor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, this->DiffuseColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, this->SpecularColor);
	glMaterialfv(GL_FRONT, GL_SHININESS, this->Shininess);

}

void DrawableObject::setPosition(GLfloat x, GLfloat y, GLfloat z) {
	Position[0] = x;
	Position[1] = y;
	Position[2] = z;
}

void DrawableObject::setRotation(GLfloat x, GLfloat y, GLfloat z) {
	Rotation[0] = x;
	Rotation[1] = y;
	Rotation[2] = z;
}

void DrawableObject::setScale(GLfloat x, GLfloat y, GLfloat z) {
	Scale[0] = x;
	Scale[1] = y;
	Scale[2] = z;
}

GLfloat* DrawableObject::getPosition() {
	return Position;
}

GLfloat* DrawableObject::getRotation() {
	return Rotation;
}

GLfloat* DrawableObject::getScale() {
	return Scale;
}

void DrawableObject::setAmbientColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	AmbientColor[0] = r;
	AmbientColor[1] = g;
	AmbientColor[2] = b;
	AmbientColor[3] = a;
}

void DrawableObject::setDiffuseColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	DiffuseColor[0] = r;
	DiffuseColor[1] = g;
	DiffuseColor[2] = b;
	DiffuseColor[3] = a;
}

void DrawableObject::setSpecularColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	SpecularColor[0] = r;
	SpecularColor[1] = g;
	SpecularColor[2] = b;
	SpecularColor[3] = a;
}

void DrawableObject::setShininess(GLfloat shininess) {
	Shininess[0] = shininess;
}

GLfloat* DrawableObject::getAmbientColor() {
	return AmbientColor;
}

GLfloat* DrawableObject::getDiffuseColor() {
	return DiffuseColor;
}

GLfloat* DrawableObject::getSpecularColor() {
	return SpecularColor;
}

GLfloat DrawableObject::getShininess() {
	return Shininess[0];
}


void DrawableObject::addChildObject(DrawableObject* child) {
	children.push_back(child);
}

std::vector<DrawableObject*>& DrawableObject::getChildren() {
	return children;
}
