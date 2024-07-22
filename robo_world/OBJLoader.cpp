#include "Loaders.h"

std::map<std::string, std::vector<Vertex>*> OBJLoader::loaded_objects; // Definition
struct GOMaterial
{
	GOvec4 AmbientColor = { 1,1,1,1 }; // Ambient color (RGBA)
	GOvec4 DiffuseColor = { 0,0,0,1 }; // Diffuse color (RGBA)
	GOvec4 SpecularColor = { 0,0,0,1 }; // Specular color (RGBA)
	GLfloat Shininess[1] = { 0 }; // Shininess factor};
};

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

	res = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str(), "models/", false);

	if (!err.empty()) {
		std::cerr << "ERR: " << err << std::endl;
		if (err.find("WARN:") == std::string::npos) {
			delete new_vec;
			return false;
		}
	}
	if (!res) {
		delete new_vec;
		return false;
	}

	// Extract the vertex data with material IDs
	for (const auto& shape : shapes) {
		for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); ++f) {
			int material_id = shape.mesh.material_ids[f]; // Get the material ID for the current face
			int num_vertices = shape.mesh.num_face_vertices[f];

			for (int v = 0; v < num_vertices; ++v) {
				const auto& index = shape.mesh.indices[3 * f + v];
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

				vertex.material_id = material_id; // Assign material ID to the vertex

				new_vec->push_back(vertex);
			}
		}
	}

	*out_vertices = new_vec;
	loaded_objects[path] = new_vec;

	return res;
}

bool OBJLoader::MyLoadOBJ(std::string path, std::vector<Vertex>** out_vertices, std::map<int, GOMaterial>* materials_out)
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

	res = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str(), "models/", false);

	if (!err.empty()) {
		std::cerr << "ERR: " << err << std::endl;
		if (err.find("WARN:") == std::string::npos) {
			delete new_vec;
			return false;
		}
	}
	if (!res) {
		delete new_vec;
		return false;
	}

	// Extract the vertex data with material IDs
	for (const auto& shape : shapes) {
		for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); ++f) {
			int material_id = shape.mesh.material_ids[f]; // Get the material ID for the current face
			int num_vertices = shape.mesh.num_face_vertices[f];

			for (int v = 0; v < num_vertices; ++v) {
				const auto& index = shape.mesh.indices[3 * f + v];
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

				vertex.material_id = material_id; // Assign material ID to the vertex

				new_vec->push_back(vertex);
			}
		}
	}

	for (int i = 0; i < materials.size(); i++)
	{
		auto a = materials[i];
		auto b = GOMaterial{ GOvec4{a.ambient[0],a.ambient[1],a.ambient[2],1},GOvec4{a.diffuse[0],a.diffuse[1],a.diffuse[2],1} ,GOvec4{a.specular[0],a.specular[1],a.specular[2],1} ,a.shininess };
		(*materials_out)[i] = b;
	}
	*out_vertices = new_vec;
	loaded_objects[path] = new_vec;

	return res;
}

