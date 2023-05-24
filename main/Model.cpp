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
			Eigen::Vector3i ft;
			Eigen::Vector3i fn;
			int trash2;
			for (int i = 0; i < 3; i++) {
				iss >> f[i];
				f[i]--;
				iss >> trash;
				iss >> ft[i];
				ft[i]--;
				iss >> trash;
				iss >> fn[i];
				fn[i]--;
			}
			face.push_back(f);
			face_texture.push_back(ft);
			face_normal.push_back(fn);
		}
		else if(line.compare(0, 3, "vt ") == 0) {
			iss >> trash;
			iss >> trash;
			Eigen::Vector3f v;
			for (int i = 0; i < 3; i++) {
				iss >> v[i];
			}
			texture.push_back(v);
		}
		else if (line.compare(0, 3, "vn ") == 0) {
			iss >> trash;
			iss >> trash;
			Eigen::Vector3f n;
			for (int i = 0; i < 3; i++) {
				iss >> n[i];
			}
			normal.push_back(n);
		}
	}
}
