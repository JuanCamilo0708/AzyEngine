#pragma once

#include "MeshTypes.h"

namespace AzyEngine::Graphics
{
	class MeshBuilder
	{
	public:
		//cube
		static MeshPC CreateCuberPC(float size, const Color& color);
		static MeshPC CreateCuberPC(float size);

		//rectangle
		static MeshPC CreateRectangle(float width, float height, float depth);

		//plane
		static MeshPC CreatePlanePC(int numRows, int numColumns, float spacing, bool horizontal = true);
		static MeshPX CreatePlanePX(int numRows, int numColumns, float spacing, bool horizontal = true);

		//cylinder
		static MeshPC CreateCylinderPC(int rings, int slices);

		//sphere
		static MeshPC CreateSpherePC(int rings, int slices, float radius);
		static MeshPX CreateSpherePX(int rings, int slices, float radius);

		//pyramid
		static MeshPC CreatePyramidPC(float size);


		// skybox
		static MeshPX CreateSkySpherePX(int rings, int slices, float radius);
	};
}