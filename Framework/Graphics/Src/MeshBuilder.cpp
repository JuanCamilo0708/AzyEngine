#include "Precompiled.h"

#include "MeshBuilder.h"

using namespace AzyEngine;
using namespace AzyEngine::Graphics;

namespace {
	Color GetNextColor(int& index)
	{
		constexpr Color colorTable[] =
		{
			Colors::Green,
			Colors::AliceBlue,
			Colors::Black,
			Colors::LightCoral,
			Colors::Wheat,
			Colors::DarkGoldenrod,
			Colors::DarkOrchid,
			Colors::OrangeRed,
			Colors::Cornsilk,
			Colors::Green,
			Colors::LawnGreen,
			Colors::Goldenrod,
			Colors::MediumSeaGreen,
			Colors::SaddleBrown
		};
		index = (index + 1) % std::size(colorTable);
		return colorTable[index];
	}
	void CreateCubeIndices(std::vector<uint32_t>& indices)
	{
		indices = {
			0,1,2,
			0,2,3,

			7,5,4,
			7,6,5,

			3,2,6,
			3,6,7,

			4,5,1,
			4,1,0,

			1,5,6,
			1,6,2,

			0,3,7,
			0,7,4
		};
	}
	void CreatePlaneIndices(std::vector<uint32_t>& indices, int numRows, int numColumns)
	{
		for (int r = 0; r < numRows; ++r)
		{
			for (int c = 0; c < numColumns; ++c)
			{
				int i = (r * (numColumns + 1)) + c;

				indices.push_back(i);
				indices.push_back(i + numColumns + 1);
				indices.push_back(i + numColumns + 2);

				indices.push_back(i);
				indices.push_back(i + numColumns + 2);
				indices.push_back(i + 1);
			}

		}
	}
}

MeshPC MeshBuilder::CreateCuberPC(float size, const Color& color)
{
	MeshPC mesh;
	const float hs = size * 0.5f;
	mesh.vertices.push_back({ { -hs,-hs,-hs }, color });
	mesh.vertices.push_back({ { -hs, hs,-hs }, color });
	mesh.vertices.push_back({ {  hs, hs,-hs }, color });
	mesh.vertices.push_back({ {  hs,-hs,-hs }, color });

	mesh.vertices.push_back({ { -hs,-hs, hs }, color });
	mesh.vertices.push_back({ { -hs, hs, hs }, color });
	mesh.vertices.push_back({ {  hs, hs, hs }, color });
	mesh.vertices.push_back({ {  hs,-hs, hs }, color });

	CreateCubeIndices(mesh.indices);
	return mesh;
}

MeshPC MeshBuilder::CreateCuberPC(float size)
{
	MeshPC mesh;
	int index = rand() % 37;
	const float hs = size * 0.5f;
	mesh.vertices.push_back({ { -hs,-hs,-hs }, GetNextColor(index) });
	mesh.vertices.push_back({ { -hs, hs,-hs }, GetNextColor(index) });
	mesh.vertices.push_back({ {  hs, hs,-hs }, GetNextColor(index) });
	mesh.vertices.push_back({ {  hs,-hs,-hs }, GetNextColor(index) });

	mesh.vertices.push_back({ { -hs,-hs, hs }, GetNextColor(index) });
	mesh.vertices.push_back({ { -hs, hs, hs }, GetNextColor(index) });
	mesh.vertices.push_back({ {  hs, hs, hs }, GetNextColor(index) });
	mesh.vertices.push_back({ {  hs,-hs, hs }, GetNextColor(index) });

	CreateCubeIndices(mesh.indices);
	return mesh;
}

MeshPC MeshBuilder::CreateRectangle(float width, float height, float depth)
{
	MeshPC mesh;

	int index = rand() % 37;
	const float hw = width * 0.5f;
	const float hh = height * 0.5f;
	const float hd = depth * 0.5f;

	mesh.vertices.push_back({ {-hw,-hh, -hd}, GetNextColor(index) });
	mesh.vertices.push_back({ {-hw, hh, -hd}, GetNextColor(index) });
	mesh.vertices.push_back({ { hw, hh, -hd}, GetNextColor(index) });
	mesh.vertices.push_back({ { hw,-hh, -hd}, GetNextColor(index) });

	mesh.vertices.push_back({ {-hw,-hh,  hd}, GetNextColor(index) });
	mesh.vertices.push_back({ {-hw, hh,  hd}, GetNextColor(index) });
	mesh.vertices.push_back({ { hw, hh,  hd}, GetNextColor(index) });
	mesh.vertices.push_back({ { hw,-hh,  hd}, GetNextColor(index) });

	CreateCubeIndices(mesh.indices);
	return mesh;
}

MeshPC MeshBuilder::CreatePlanePC(int numRows, int numColumns, float spacing, bool horizontal)
{
	MeshPC mesh;

	int index = rand() % 40;
	const float hpw = static_cast<float>(numColumns) * spacing * 0.5f;
	const float hph = static_cast<float>(numRows) * spacing * 0.5f;

	float w = -hpw;
	float h = -hph;

	for (int r = 0; r <= numRows; ++r)
	{
		for (int c = 0; c <= numColumns; ++c)
		{
			Math::Vector3 pos = (horizontal) ? Math::Vector3(w, 0.0f, h) : Math::Vector3(w, h, 0.0f);
			mesh.vertices.push_back({ pos,GetNextColor(index) });
			w += spacing;
		}
		w = -hpw;
		h += spacing;
	}
	CreatePlaneIndices(mesh.indices, numRows, numColumns);

	return mesh;
}

MeshPC MeshBuilder::CreateCylinderPC(int rings, int slices)
{
	MeshPC mesh;

	int index = rand() % 69;
	const float hh = static_cast<float>(rings) * 0.5f;
	const float fSlices = static_cast<float>(slices);
	for (int r = 0; r <= rings; ++r)
	{
		float ring = static_cast<float>(r);

		for (int s = 0; s <= slices; ++s)
		{
			float slice = static_cast<float>(s);
			float rotation = (slice / fSlices) * Math::Constants::TwoPi;

			mesh.vertices.push_back({ {
					sin(rotation),
					ring - hh,
					-cos(rotation)},
					GetNextColor(index) });
		}

	}
	CreatePlaneIndices(mesh.indices, rings, slices);
	mesh.vertices.push_back({ {0.0f, hh, 0.0f},GetNextColor(index) });
	mesh.vertices.push_back({ {0.0f, -hh, 0.0f},GetNextColor(index) });

	int topIndex = mesh.vertices.size() - 2;
	int bottomIndex = mesh.vertices.size() - 1;

	for (int s = 0; s < slices; ++s)
	{
		mesh.indices.push_back(bottomIndex);
		mesh.indices.push_back(s);
		mesh.indices.push_back(s+1);

		int topRowIndex = topIndex - slices - 1 + s;
		mesh.indices.push_back(topIndex);
		mesh.indices.push_back(topRowIndex +1);
		mesh.indices.push_back(topRowIndex);
	}
	return mesh;
}

MeshPC MeshBuilder::CreateSpherePC(int rings, int slices, float radius)
{

	MeshPC mesh;
	int index = rand() % 69;
	const float vertRotation = (Math::Constants::Pi / static_cast<float>(rings));
	const float horzRotation = (Math::Constants::TwoPi / static_cast<float>(slices));

	for (int r = 0; r <= rings; ++r)
	{
		float ring = static_cast<float>(r);
		float phi = ring * vertRotation;
		for (int s = 0; s <= slices; ++s)
		{
			float slice = static_cast<float>(s);
			float rotation = slice * horzRotation;
			mesh.vertices.push_back({ {
					radius * sin(rotation) * sin(phi),
					radius * cos(phi),
					radius * cos(rotation) * sin(phi)
					}, GetNextColor(index)});

		}
	}
	CreatePlaneIndices(mesh.indices, rings, slices);
	return mesh;
}

MeshPC MeshBuilder::CreatePyramidPC(float size)
{
	MeshPC mesh;

	return mesh;
}
