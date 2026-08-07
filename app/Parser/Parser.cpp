#include "Parser.hpp"
#include <string.h>

inline GLfloat max(GLfloat a, GLfloat b) {
	return (a > b ? a : b);
}

inline GLfloat min(GLfloat a, GLfloat b) {
	return (a < b ? a : b);
}

void MeshData::normalizeVertices() {
	if (_vertex.empty()) {
		throw NoVertex();
	}

	GLfloat minX = _vertex[0].position[0], maxX = _vertex[0].position[0];
	GLfloat minY = _vertex[0].position[1], maxY = _vertex[0].position[1];
	GLfloat minZ = _vertex[0].position[2], maxZ = _vertex[0].position[2];

	for (const auto& v : _vertex) {
		minX = std::min(minX, v.position[0]); maxX = std::max(maxX, v.position[0]);
		minY = std::min(minY, v.position[1]); maxY = std::max(maxY, v.position[1]);
		minZ = std::min(minZ, v.position[2]); maxZ = std::max(maxZ, v.position[2]);
	}

	GLfloat centerX = (minX + maxX) / 2.0f;
	GLfloat centerY = (minY + maxY) / 2.0f;
	GLfloat centerZ = (minZ + maxZ) / 2.0f;

	GLfloat dx = maxX - minX;
	GLfloat dy = maxY - minY;
	GLfloat dz = maxZ - minZ;
		
	GLfloat extent = std::max(dx, std::max(dy, dz));
	if (extent == 0.0f)
		return; 
		
	GLfloat scale = 2.0f / extent;

	for (auto& v : _vertex) {
		v.position[0] = (v.position[0] - centerX) * scale;
		v.position[1] = (v.position[1] - centerY) * scale;
		v.position[2] = (v.position[2] - centerZ) * scale;
	}
}

MeshData Parser::getMeshData(std::string fileName) {
	std::fstream f = openFile(fileName);
	return parseMeshFile(f);
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

static void sanitize(std::string &line) {
	std::string result;

	for (std::string::iterator it  = line.begin(); it < line.end(); it++) {
		result += *it;
		if (isblank(*it)) {
			std::string::iterator next = it+1;
			while (*next and (isblank(*next) or !isprint(*next))) {
				next++;
				it++;
			}
		}
	}
	line = result;
}

MeshData Parser::parseMeshFile(std::fstream &file) {
	MeshData data;
	std::string line;
	unsigned long linenb = 0;
	std::vector<std::string> elements; 
	Vertex vert;

	if (!file.good()) {
		throw std::invalid_argument("Mesh file could not be opened");
	}

	while (file.good()) {
		linenb++;
		getline(file, line);
		sanitize(line);
		elements = split(line, " ");
		if (elements[0].compare("v") == 0) {
			if (elements.size() != 4) {
				throw Parser::IncorectData(linenb, line);
			}
			GLfloat tab[3];
			try {
				tab[0] = std::stof(elements[1]);
				tab[1] = std::stof(elements[2]);
				tab[2] = std::stof(elements[3]);
			}
			catch(const std::exception& e) {
				throw Parser::IncorectData(linenb, line);
			}
			
			memcpy(vert.position, tab, sizeof(GLfloat) * 3);
			data.addVertex(vert);
		}
		else if (elements[0].compare("f") == 0) {
			if (elements.size() < 4 or elements.size() > 5)
				throw Parser::IncorectData(linenb, line);
			std::vector<GLuint> face;
			size_t i;

			for (i = 1; i < elements.size(); i++) {
				unsigned long number;
				number = std::stoul(elements[i]);
				if (number > UINT32_MAX)
					throw Parser::IncorectData(linenb, line);
				face.push_back(number - 1);
			}

			if (i == 4)
				data.addFace3(face.data());
			else if (i == 5)
				data.addFace4(face.data());
			else
				throw Parser::IncorectData(linenb, line);
		}
	}
	return (data);
}

std::fstream Parser::openFile(std::string &fileName) {
	return std::fstream(fileName);
}


std::optional<TextureData> Parser::getTextureData(std::string fileName) {
	std::ifstream file(fileName, std::ios::binary | std::ios::ate);
	if (!file.is_open()) {
		throw std::invalid_argument("Texture file could not be opened");
	}

	std::streamsize fileSize = file.tellg();
	if (fileSize < 18) {
		throw std::invalid_argument("Texture file is incorrect");
	}

	file.seekg(0, std::ios::beg);
	std::vector<u_int8_t> buffer(fileSize);
	if (!file.read(reinterpret_cast<char*>(buffer.data()), fileSize)) {
		throw std::invalid_argument("a problem happened while reading file");
	}
	const u_int8_t*raw = buffer.data();

	tga_header header_data = {
		static_cast<u_int8_t>	(*raw),
		static_cast<u_int8_t>	(raw[1]),
		static_cast<u_int8_t>	(raw[2]),
		
		static_cast<u_int16_t>	(raw[3] | (raw[4] << 8)),
		static_cast<u_int16_t>	(raw[5] | (raw[6] << 8)),
		static_cast<u_int8_t>	(raw[7]),

		static_cast<u_int16_t>	(raw[8] | (raw[9] << 8)),
		static_cast<u_int16_t>	(raw[10] | (raw[11] << 8)),
		static_cast<u_int16_t>	(raw[12] | (raw[13] << 8)),
		static_cast<u_int16_t>	(raw[14] | (raw[15] << 8)),
		static_cast<u_int8_t>	(raw[16]),
		static_cast<u_int8_t>	(raw[17])
	};

	if (header_data.imageType != 2 or header_data.pixelDepth != 24) {
		throw Parser::UnsupportedFile();
	}

	const unsigned long imgIndex = 18 + header_data.IDLen;
	if (imgIndex + 3 > buffer.size())
		return std::nullopt;
	const unsigned char *ptr = raw + imgIndex;

	TextureData data(header_data.imgHeight, header_data.imgWidth);
	data.fillPixels(ptr);
	return (data);
}

