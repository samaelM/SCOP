#include "Parser.hpp"

inline GLfloat max(GLfloat a, GLfloat b) {
	return (a > b ? a : b);
}

inline GLfloat min(GLfloat a, GLfloat b) {
	return (a < b ? a : b);
}

void Data::normalizeVertices() {
    if (_vertex.empty()) {
        throw NoVertex();
    }

    // 1. Correct Initialization
    GLfloat minX = _vertex[0].position[0], maxX = _vertex[0].position[0];
    GLfloat minY = _vertex[0].position[1], maxY = _vertex[0].position[1];
    GLfloat minZ = _vertex[0].position[2], maxZ = _vertex[0].position[2];

    for (const auto& v : _vertex) {
        minX = std::min(minX, v.position[0]); maxX = std::max(maxX, v.position[0]);
        minY = std::min(minY, v.position[1]); maxY = std::max(maxY, v.position[1]);
        minZ = std::min(minZ, v.position[2]); maxZ = std::max(maxZ, v.position[2]);
    }

    // 2. Correct Centering
    GLfloat centerX = (minX + maxX) / 2.0f;
    GLfloat centerY = (minY + maxY) / 2.0f;
    GLfloat centerZ = (minZ + maxZ) / 2.0f;

    // 3. Correct Scaling
    GLfloat dx = maxX - minX;
    GLfloat dy = maxY - minY;
    GLfloat dz = maxZ - minZ;
    
    // Avoid division by zero for flat objects
    GLfloat extent = std::max(dx, std::max(dy, dz));
    if (extent == 0.0f) return; 
    
    GLfloat scale = 2.0f / extent;

    for (auto& v : _vertex) {
        v.position[0] = (v.position[0] - centerX) * scale;
        v.position[1] = (v.position[1] - centerY) * scale;
        v.position[2] = (v.position[2] - centerZ) * scale;
    }
}



Data Parser::getData(std::string fileName) {
	std::fstream f = openFile(fileName);
	return parseFile(f);
}

std::vector<std::string> split(std::string s, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
}

#include <string.h>

std::string printTab(std::vector<std::string> tab) {
	std::string str = "[";
	size_t i;
	for (i = 0; i < tab.size(); i++)
	{
		if (!tab[i].empty())
			str += std::to_string(i) + ":" + tab[i] + ", ";
		else
			str += std::to_string(i) + ": (empty), ";
	}
	str += "] size: " + std::to_string(i);
	return str;
}

Data Parser::parseFile(std::fstream &file) {
	Data data;
	std::string line;
	std::vector<std::string> elements; 
	Vertex vert;
	if (!file.good()) {
		throw std::out_of_range("file pas bon");
	}
	while (file.good()) {
		getline(file, line);
		// std::cout << "reading line:" << line << "\n";
		elements = split(line, " ");
		if (elements[0].compare("v") == 0) {
			// std::cout << "added vertex!\n";
			if (elements[0].empty() or elements[1].empty() or elements[2].empty() or elements[3].empty()) {
				throw std::out_of_range("not enough coordinates :" + printTab(elements));
			}
			GLfloat tab[3] = {std::stof(elements[1]), std::stof(elements[2]), std::stof(elements[3])};
			memcpy(vert.position, tab, sizeof(GLfloat) * 3);
			data.addVertex(vert);
		}
		else if (elements[0].compare("f") == 0) {
			std::vector<GLuint> face;
			size_t i;
			for (i = 1; i < elements.size(); i++)
			{
				face.push_back(std::stoul(elements[i]) - 1);
			}
			if (i == 4)
				data.addFace3(face.data());
			else if (i == 5)
				data.addFace4(face.data());
			else
				throw std::out_of_range("too much coordinates");
		}
		else {
			// std::cout << "added nothing!(" << line << ")\n";
		}
	}
	// std::cout <<std::endl;
	return (data);
}

std::fstream Parser::openFile(std::string &fileName) {
	return std::fstream(fileName);
}


// std::ostream &operator<<(std::ostream &os, const Data &data)
// {
// 	std::string str_vertex = "";
// 	std::string str_faces = "";
// 	std::vector<Vertex> vertex = data.getVertices();
// 	std::cout << "vertex size: " << vertex.size()<< "\n";
// 	for (size_t i = 0; i < vertex.size(); i++)
// 	{
// 		str_vertex += std::to_string(vertex[i].position[0]) + " " + std::to_string(vertex[i].position[1]) + " " + std::to_string(vertex[i].position[2]) + "\n";
// 	}
// 	std::vector<GLuint> faces = data.getFaces();
// 	std::cout << "faces size: " << faces.size()<< "\n";
// 	for (size_t i = 0; i < faces.size(); i+=3)
// 	{
// 		str_faces += "-" + std::to_string(faces[i]) + std::to_string(faces[i+1]) + std::to_string(faces[i+2]);
// 		// for (size_t j = 0; j < faces[i].size(); j++)
// 		// {
// 		// 	str_faces = str_faces + " " + std::to_string(faces[i][j]);
// 		// }
// 		str_faces += '\n';		
// 	}
// 	os << "Vertices:\n" << str_vertex << "Faces:\n" << str_faces;
// 	return (os);
// }