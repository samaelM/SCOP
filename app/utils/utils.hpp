#ifndef SCOP_UTILS_HPP
#	define SCOP_UTILS_HPP
#	include <iostream>		//Used to print info on the stdout
#	include <fstream>		//Used to open files
#	include <string.h>		//Used for memset
#	define ERRNOF std::cout << std::to_string(errno) << std::endl

inline std::string load(std::string fileName) {
	std::fstream f = std::fstream(fileName);
	if (!f.is_open()) {
		throw std::out_of_range("file could not be open"); //change error
	}
	std::string content;
	std::string line;
	while (f.good()) {
		std::getline(f, line);
		content += line + "\n";
	}
	// std::cout << "loaded: \n" << content;
	return (content);
}

inline void translate(GLfloat *m, const GLfloat vec[3]) {
	m[3] = m[0] * vec[0] + m[1] * vec[1] + m[2] * vec[2] + m[3];
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