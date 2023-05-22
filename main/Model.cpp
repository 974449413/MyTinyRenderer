#include"Model.h"

Model::Model(const char* file){
	std::ifstream in;
	in.open(file, std::ifstream::in);
	if (!in.is_open()) {
		std::cerr << in.rdstate() << std::endl;
		std::cerr << "failed open obj file " << std::endl;
		return;
	}
	std::string line;
	while (!in.eof()) {
		std::getline(in, line);
		std::istringstream iss(line.c_str());
		char trash;
		if (line.compare(0, 2, "v ") == 0) {
			iss >> trash;
			Eigen::Vector3f v;
			for (int i = 0; i < 3; i++) {
				iss >> v[i];
			}
			vertex.push_back(v);
		}
		else if (line.compare(0, 2, "f ") == 0) {
			iss >> trash;
			Eigen::Vector3i f;
			int trash2;
			for (int i = 0; i < 3; i++) {
				iss >> f[i];
				f[i]--;
				iss >> trash;
				iss >> trash2;
				iss >> trash;
				iss >> trash2;
			}
			face.push_back(f);
		}
	}
	GetTextureData(file);
}

void Model::GetTextureData(const char* file){
	std::string texture_filename(file);
	texture_filename = texture_filename.substr(0, texture_filename.size() - 4) + "_diffuse.tga";
	TGAImage::ReadTGAImage(texture_filename.c_str(), color);
}