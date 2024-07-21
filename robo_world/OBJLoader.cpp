#include "Loaders.h"

std::map<std::string, std::vector<Vertex>*> OBJLoader::loaded_objects; // Definition

bool OBJLoader::MyLoadOBJ(std::string path, std::vector<Vertex>** out_vertices)
{
	path = "models/" + path;
	auto it = loaded_objects.find(path);
	if (it != loaded_objects.end())
	{
		if (out_vertices != nullptr)
			*out_vertices = it->second;
		return true;
	}

	std::vector<Vertex>* new_vec = new std::vector<Vertex>();
	//todo: Use some loading surface for optimization
	bool res = false;
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	res = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str(), nullptr, true);

	if (!err.empty()) {
		std::cerr << "ERR: " << err << std::endl;
		delete new_vec;
		return false;
	}
	if (!res) {
		delete new_vec;
		return false;
	}

	// Extract the vertex data
	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			Vertex vertex = {};

			vertex.position[0] = attrib.vertices[3 * index.vertex_index + 0];
			vertex.position[1] = attrib.vertices[3 * index.vertex_index + 1];
			vertex.position[2] = attrib.vertices[3 * index.vertex_index + 2];

			if (!attrib.normals.empty()) {
				vertex.normal[0] = attrib.normals[3 * index.normal_index + 0];
				vertex.normal[1] = attrib.normals[3 * index.normal_index + 1];
				vertex.normal[2] = attrib.normals[3 * index.normal_index + 2];
			}

			if (!attrib.texcoords.empty()) {
				vertex.texCoord[0] = attrib.texcoords[2 * index.texcoord_index + 0];
				vertex.texCoord[1] = attrib.texcoords[2 * index.texcoord_index + 1];
			}

			new_vec->push_back(vertex);
		}
	}

	*out_vertices = new_vec;
	loaded_objects[path] = new_vec;

	return res;
}