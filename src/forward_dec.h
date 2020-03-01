#ifndef FORWARD_DEC_H
#define FORWARD_DEC_H

#define GLM_ENABLE_EXPERIMENTAL

#include <vector>
#include <unordered_map>
#include "glm/glm.hpp"
#include "glm/gtx/hash.hpp"

//This is Boost's Hash Combine Function! Credit to them!
static void hash_combine(size_t& seed, const size_t& v)
{
	//V is already a hash value from GLM's hash algorithm
	seed ^= v + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

struct OutVertex
{
	glm::vec4 pos;
	glm::vec4 nrm;

	bool operator==(const OutVertex& o) const {
		return (pos == o.pos) && (nrm == o.nrm);
	}

};

namespace std {
	template<> struct hash<OutVertex> {
		size_t operator()(const OutVertex& vertex) const {
			size_t seed = 0;
			hash_combine(seed, hash<glm::vec3>()(vertex.pos));
			hash_combine(seed, hash<glm::vec3>()(vertex.nrm));
			return seed;
		}
	};
}

//Shape Helper Functions
static void AddTriangle(const uint32_t& a, const uint32_t& b, const uint32_t& c, std::vector<uint32_t>& _outIndices)
{
	//Simply Adds three indices to make a triangle
	_outIndices.push_back(a);
	_outIndices.push_back(b);
	_outIndices.push_back(c);
}
static void AddQuad(const uint32_t& a, const uint32_t& b, const uint32_t& c, const uint32_t& d, std::vector<uint32_t>& _outIndices)
{
	//Adds a quad, separated as two triangles
	_outIndices.push_back(a);
	_outIndices.push_back(b);
	_outIndices.push_back(d);
	_outIndices.push_back(b);
	_outIndices.push_back(c);
	_outIndices.push_back(d);
}

void Expand();
void CalculateNormals();
void Compact();

void WriteToFile();
void OpenFile();

void CreateCube();
void CreateSphere(const uint32_t& hlines, const uint32_t& meridian);
void CreateSphereV2(const float& _diameter, const float& _degreeFactor);
void CreateCone(const float& _diameter, const float& _degreeFactor);
void CreateCylinder(const float& _diameter, const float& _degreeFactor);
void CreateCapsule(const uint32_t& hlines, const uint32_t& meridian);
void CreateTorus(const float& _innerRadius, const float& _tubeRadius, const float& _degreeFactor);

#endif
