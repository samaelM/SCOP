#include "Graphics.hpp"

void Camera::getPosition(GLfloat *out) const {
	const float cosPitch = std::cos(this->_pitch);

	out[0] = this->_target[0] + this->_radius * cosPitch * std::sin(this->_yaw);
	out[1] = this->_target[1] + this->_radius * std::sin(this->_pitch);
	out[2] = this->_target[2] + this->_radius * cosPitch * std::cos(this->_yaw);
}

void Camera::getViewMatrix(GLfloat *out) const {
	GLfloat eye[3];
	this->getPosition(eye);

	const GLfloat up[3] = {0.0f, 1.0f, 0.0f};
	lookAt(out, eye, this->_target, up);
}

void Camera::orbit(float deltaX, float deltaY) {
	this->_yaw += deltaX * this->_orbitSensitivity;
	this->_pitch += deltaY * this->_orbitSensitivity;

	const float limit = 1.55334f;
	if (this->_pitch > limit)
		this->_pitch = limit;
	if (this->_pitch < -limit)
		this->_pitch = -limit;
}

void Camera::zoom(float amount) {
	this->_radius -= amount * this->_zoomSensitivity;
	if (this->_radius < this->_minRadius)
		this->_radius = this->_minRadius;
	if (this->_radius > this->_maxRadius)
		this->_radius = this->_maxRadius;
}

void Camera::reset() {
	this->_yaw = 0.0f;
	this->_pitch = 0.0f;
	this->_radius = 3.0f;
}
