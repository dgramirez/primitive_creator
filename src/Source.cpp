#include "forward_dec.h"
#include "xplat.h"
#include <cmath>

//Global Functions
namespace {
	std::vector<OutVertex> vert;
	std::vector<uint32_t> idx;
	std::vector<glm::vec4> cPoints;
	const float _PI = 3.1415927f;
	const float _PI2 = _PI * 2;
}

//Forward Declarations (SHAPES)


//Main
int main()
{
	//Fill in a vertex
//	CreateCapsule(16, 16);
	CreateSphereV2(1.0f, 15.0f);

	//Expand
	Expand();

	//Calculate Normals
	CalculateNormals();

	//Compact
	Compact();

	//Write to File
	WriteToFile();

	//Open File Test
	OpenFile();

	return 0;
}

void CreateCube()
{
	cPoints.push_back({ -0.5f, -0.5f, -0.5f, 1.0f });
	cPoints.push_back({ 0.5f, -0.5f, -0.5f, 1.0f });
	cPoints.push_back({ 0.5f,  0.5f, -0.5f, 1.0f });
	cPoints.push_back({ -0.5f,  0.5f, -0.5f, 1.0f });
	cPoints.push_back({ -0.5f,  0.5f,  0.5f, 1.0f });
	cPoints.push_back({ 0.5f,  0.5f,  0.5f, 1.0f });
	cPoints.push_back({ 0.5f, -0.5f,  0.5f, 1.0f });
	cPoints.push_back({ -0.5f, -0.5f,  0.5f, 1.0f });

	AddTriangle(0, 2, 1, idx);
	AddTriangle(0, 3, 2, idx);

	AddTriangle(2, 3, 4, idx);
	AddTriangle(2, 4, 5, idx);

	AddTriangle(1, 2, 5, idx);
	AddTriangle(1, 5, 6, idx);

	AddTriangle(0, 7, 4, idx);
	AddTriangle(0, 4, 3, idx);

	AddTriangle(5, 4, 7, idx);
	AddTriangle(5, 7, 6, idx);

	AddTriangle(0, 6, 7, idx);
	AddTriangle(0, 1, 6, idx);
}
void CreateCone(const float& _diameter, const float& _degreeFactor)
{
	//Have a start and end
	float r = _diameter / 2.0f;
	glm::vec4 start =	{ 0.0f, -1.0f * r, 0.0f, 1.0f };
	glm::vec4 end =		{ 0.0f,  1.0f * r, 0.0f, 1.0f };

	//Vertex: Create the center Circle
	cPoints.push_back(start);

	//Vertex: Create the circle from that vertex
	for (float i = -_PI; i < _PI; i += (_PI / 180.0f) * _degreeFactor)
	{
		float _cos = cosf(i);
		float _sin = sinf(i);
		cPoints.push_back({_cos * r, start.y, _sin * r, 1.0f});
	}

	//Vertex: Create the top part of the cone
	cPoints.push_back(end);

	uint32_t halfsize = cPoints.size() / 2;

	//Index: Add the edges from the circle's radius
	for (uint32_t i = 2; i < cPoints.size() - 1; ++i)
		AddTriangle(0, i - 1, i, idx);

	//Index:
	for (uint32_t i = 2; i < cPoints.size() - 1; ++i)
		AddTriangle(cPoints.size() - 1, i, i - 1, idx);
}
void CreateCylinder(const float& _diameter, const float& _degreeFactor)
{
	//Have a start and end
	float r = _diameter / 2.0f;
	glm::vec4 bottom = { 0.0f, -1.0f * r, 0.0f, 1.0f };
	glm::vec4 top = { 0.0f,  1.0f * r, 0.0f, 1.0f };

	//Vertex: Create the center Circle
	cPoints.push_back(bottom);

	//Vertex: Create the circle from that vertex
	for (float i = -_PI; i < _PI; i += (_PI / 180.0f) * _degreeFactor)
	{
		float _cos = cosf(i);
		float _sin = sinf(i);
		cPoints.push_back({ _cos * r, bottom.y, _sin * r, 1.0f });
	}

	//Get Half Size
	uint32_t half = cPoints.size();

	//Vertex: Create the center circle of the end point
	cPoints.push_back(top);

	//Vertex: Create the circle from that vertex
	for (float i = -_PI; i < _PI; i += (_PI / 180.0f) * _degreeFactor)
	{
		float _cos = cosf(i);
		float _sin = sinf(i);
		cPoints.push_back({ _cos * r, top.y, _sin * r, 1.0f });
	}

	//Index: Add the edges from the circle's radius (bottom)
	for (uint32_t i = 2; i < half; ++i)
		AddTriangle(0, i - 1, i, idx);

	//Index: Add the edges from the circle's radius (top)
	for (uint32_t i = half + 2; i < cPoints.size(); ++i)
		AddTriangle(half, i, i - 1, idx);

	//Index: Add the center edges of the Cylinder
	for (uint32_t i = 1; i < half - 1; ++i)
	{
		AddTriangle(i, half + i + 1, i + 1, idx);
		AddTriangle(i, half + i, half + i + 1, idx);
	}
}
void CreateSphere(const uint32_t& hlines, const uint32_t& meridian)
{
	//Set the origin point in space
	cPoints.push_back({ 0, 1, 0, 1 });

	//Loop through every horizontal line
	for (uint32_t y = 0; y < hlines; ++y)
	{
		//Setting the polar angle
		float polar = _PI * (y + 1) / hlines;
		float sinP = sin(polar);
		float cosP = cos(polar);

		//Loop through every vertical line
		for (uint32_t x = 0; x < meridian; ++x)
		{
			//Setting up the azimuthal angle
			float azimuth = 2.0f * _PI * x / meridian;

			//Sin and Cosine of Azimuth
			float sinA = sin(azimuth);
			float cosA = cos(azimuth);

			//Push back the Vert
			cPoints.push_back({ sinP * cosA, cosP, sinP * sinA, 1 });
		}
	}

	//Set the final point in space
	cPoints.push_back({ 0, -1, 0, 1 });

	//Shrink Vertices by half (2 units to 1)
	for (uint32_t i = 0; i < cPoints.size(); ++i)
		cPoints[i] *= 0.5f;

	//Set up the (bottom) of the sphere
	for (uint32_t i = 0; i < meridian; ++i)
		AddTriangle(0, ((i + 1) % meridian) + 1, i + 1, idx);

	//Create the quads that will be inbetween the top and bottom triangles of the sphere
	uint32_t hlinesminus2 = hlines - 2;
	for (uint32_t y = 0; y < hlinesminus2; ++y)
	{
		uint32_t aStart = y * meridian + 1;
		uint32_t bStart = (y + 1) * meridian + 1;
		for (uint32_t x = 0; x < meridian; ++x)
		{
			const uint32_t a = aStart + x;
			const uint32_t a1 = aStart + (x + 1) % meridian;
			const uint32_t b = bStart + x;
			const uint32_t b1 = bStart + (x + 1) % meridian;
			AddQuad(a, a1, b1, b, idx);
		}
	}

	//Set up the (top) of the sphere
	for (uint32_t i = 0; i < meridian; ++i)
	{
		uint32_t const a = i + meridian * hlinesminus2 + 1;
		uint32_t const b = (i + 1) % meridian + meridian * hlinesminus2 + 1;
		AddTriangle(static_cast<uint32_t>(cPoints.size() - 1), a, b, idx);
	}
}

void CreateSphereV2(const float& _diameter, const float& _degreeFactor) {
	const float _radius = _diameter / 2.0f;
	uint32_t innerCount = 0;
	
	for (float theta = 0; theta < _PI2; theta += (_PI / 180.0f) * _degreeFactor)
	{
		float rCosTheta = _radius * cosf(theta);
		float rSinTheta = _radius * sinf(theta);

		for (float phi = 0; phi < _PI2; phi += (_PI / 180.0f) * _degreeFactor)
			cPoints.push_back({rSinTheta * cosf(phi), rSinTheta * sinf(phi), rCosTheta, 1.0f});
		
		++innerCount;
	}
	
	for (uint32_t y = 0; y < innerCount - 1; ++y)
	{
		for (uint32_t x = 0; x < innerCount - 1; ++x)
		{
			uint32_t cSide = y * innerCount + x;
			uint32_t nSide = (y+1) * innerCount + x;

			AddTriangle(cSide, cSide+1, nSide, idx);
			AddTriangle(nSide, cSide + 1, nSide + 1, idx);
		}
	}
}

void CreateCapsule(const uint32_t& hlines, const uint32_t& meridian)
{
	CreateSphere(hlines, meridian);
	uint32_t half = cPoints.size() / 2;
	for (uint32_t i = 0; i < half; ++i)
	{
		cPoints[i].y += 0.5f;
		cPoints[half + i].y -= 0.5f;
	}

	//Shrink Vertices by half (2 units to 1)
	for (uint32_t i = 0; i < cPoints.size(); ++i)
		cPoints[i] *= 0.5f;

	return;
}
void CreateTorus(const float& _innerRadius, const float& _tubeRadius, const float& _degreeFactor)
{
	uint32_t innerCount = 0;
	for (float theta = 0; theta < _PI2; theta += (_PI / 180.0f) * _degreeFactor)
	{
		float rCosTheta = _innerRadius + _tubeRadius * cosf(theta);
		float rSinTheta = _tubeRadius * sinf(theta);

		for (float phi = 0; phi < _PI2; phi += (_PI / 180.0f) * _degreeFactor)
			cPoints.push_back({rCosTheta * cosf(phi), rCosTheta * sinf(phi), rSinTheta, 1.0f});

		++innerCount;
	}
	
	for (uint32_t y = 0; y < innerCount - 1; ++y)
	{
		for (uint32_t x = 0; x < innerCount - 1; ++x)
		{
			uint32_t cSide = y * innerCount + x;
			uint32_t nSide = (y+1) * innerCount + x;

			AddTriangle(cSide, cSide+1, nSide, idx);
			AddTriangle(nSide, cSide + 1, nSide + 1, idx);
		}
	}

}

void Expand()
{
	std::vector<OutVertex> expanded;
	expanded.resize(idx.size());

	for (uint32_t i = 0; i < expanded.size(); ++i)
		expanded[i].pos = cPoints[idx[i]];

	vert = expanded;
}
void CalculateNormals()
{
	for (uint32_t i = 0; i < vert.size(); i += 3)
	{
		glm::vec3 edge1 = vert[i].pos - vert[i+1].pos;
		glm::vec3 edge2 = vert[i+2].pos - vert[i+1].pos;

		vert[i].nrm = vert[i+1].nrm = vert[i+2].nrm = glm::vec4(glm::normalize(glm::cross(edge1, edge2)), 1.0f);
	}
}
void Compact()
{
	//Setup Buffer Variables
	std::unordered_map<OutVertex, uint32_t> unique_vertices;
	unique_vertices.reserve(idx.size());
	std::vector<uint32_t> new_idx; new_idx.resize(idx.size());
	uint32_t cpSize = 0;

	//Compactify
	for (uint32_t i = 0; i < idx.size(); ++i)
	{
		if (unique_vertices.count(vert[i]))
			new_idx[i] = unique_vertices[vert[i]];
		else
		{
			unique_vertices[vert[i]] = cpSize;
			new_idx[i] = cpSize++;
		}
	}

	//Copy Vertex
	std::vector<OutVertex> new_vertex; new_vertex.resize(cpSize);
	for (auto v_key : unique_vertices)
		_memcpy(&new_vertex[v_key.second], &v_key.first, sizeof(OutVertex));

	//Set New Vertex and Index
	vert = new_vertex;
	idx = new_idx;
}

void WriteToFile()
{
	//Setup File
	FILE* file;
	_fopen(&file, "shape.bin", "wb");
	if (!file)
		return;

	//Write Size of Vertices
	uint32_t temp = vert.size();
	fwrite(&temp, sizeof(uint32_t), 1, file);

	//Write Data
	fwrite(vert.data(), sizeof(OutVertex), vert.size(), file);

	//Write Size of Indices
	temp = idx.size();
	fwrite(&temp, sizeof(uint32_t), 1, file);

	//Write Index Data
	fwrite(idx.data(), sizeof(uint32_t), idx.size(), file);
	
	//Close File
	fclose(file);
}
struct InVertex
{
	float pos[4];
	float nrm[4];
};
void OpenFile()
{
	//Setup File
	FILE* file;
	_fopen(&file, "shape.bin", "rb");
	if (!file)
		return;

	//Get Vertex Count
	uint32_t temp;
	_fread(&temp, sizeof(uint32_t), 1, file);

	//Get Vertices
	std::vector<OutVertex> new_verts; new_verts.resize(temp);
	_fread(new_verts.data(), sizeof(OutVertex), temp, file);

	//Get Index Count
	_fread(&temp, sizeof(uint32_t), 1, file);

	//Get Indices
	std::vector<uint32_t> new_idx; new_idx.resize(temp);
	_fread(new_idx.data(), sizeof(uint32_t), temp, file);

	return;
}
