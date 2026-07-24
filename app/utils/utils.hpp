#ifndef SCOP_UTILS_HPP
#	define SCOP_UTILS_HPP
#	include <iostream>		//Used to print info on the stdout
#	include <fstream>		//Used to open files


std::string load(std::string fileName) {
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

#endif