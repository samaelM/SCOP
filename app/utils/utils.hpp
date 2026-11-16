#ifndef SCOP_UTILS_HPP
#	define SCOP_UTILS_HPP
#	include <iostream>		//Used to print info on the stdout
#	include <fstream>		//Used to open files
#	include <string.h>		//Used for memset
#	include <math.h>		//Used for sqrtf/tanf (matrix maths)
#	define ERRNOF std::cout << std::to_string(errno) << std::endl

inline std::string load(std::string fileName) {
	std::fstream f = std::fstream(fileName);
	if (!f.is_open()) {
		throw std::invalid_argument("Shader file could not be open"); //change error
	}
	std::string content;
	std::string line;
	while (f.good()) {
		std::getline(f, line);
		content += line + "\n";
	}
	return (content);
}


inline float dot3(const float a[3], const float b[3]) {
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

inline void cross3(const float a[3], const float b[3], float out[3]) {
	const float x = a[1] * b[2] - a[2] * b[1];
	const float y = a[2] * b[0] - a[0] * b[2];
	const float z = a[0] * b[1] - a[1] * b[0];
	out[0] = x; out[1] = y; out[2] = z;
}

inline void normalize3(float v[3]) {
	const float len = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (len > 1e-6f) {
		v[0] /= len; v[1] /= len; v[2] /= len;
	}
}

inline void lookAt(float *m, const float eye[3], const float center[3], const float up[3]) {
	float f[3] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
	normalize3(f);

	float s[3];
	cross3(f, up, s);
	normalize3(s);

	float u[3];
	cross3(s, f, u);

	m[0] = s[0];  m[4] = s[1];  m[8]  = s[2];  m[12] = -dot3(s, eye);
	m[1] = u[0];  m[5] = u[1];  m[9]  = u[2];  m[13] = -dot3(u, eye);
	m[2] = -f[0]; m[6] = -f[1]; m[10] = -f[2]; m[14] =  dot3(f, eye);
	m[3] = 0.0f;  m[7] = 0.0f;  m[11] = 0.0f;  m[15] = 1.0f;
}


inline void perspective(float* m, float fov_y_radians, float aspect, float near_plane, float far_plane) {
	float tan_half_fov = tanf(fov_y_radians / 2.0f);
	float z_range = far_plane - near_plane;

	memset(m, 0, 16 * sizeof(float));

	m[0] = 1.0f / (aspect * tan_half_fov);
	m[5] = 1.0f / tan_half_fov;
	m[10] = -(far_plane + near_plane) / z_range;
	m[11] = -1.0f;
	m[14] = -(2.0f * far_plane * near_plane) / z_range;
}

inline void multiplyMatrix(const float* A, const float* B, float* out) {
	float temp[16] = {0.0f};
	for (int col = 0; col < 4; ++col) {
		for (int row = 0; row < 4; ++row) {
			temp[col * 4 + row] = 
				A[0 * 4 + row] * B[col * 4 + 0] +
				A[1 * 4 + row] * B[col * 4 + 1] +
				A[2 * 4 + row] * B[col * 4 + 2] +
				A[3 * 4 + row] * B[col * 4 + 3];
		}
	}
	for (int i = 0; i < 16; ++i) {
		out[i] = temp[i];
	}
}

#endif