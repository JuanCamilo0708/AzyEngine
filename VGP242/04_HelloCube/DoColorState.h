#pragma once
#include <AzyEngine/Inc/AzyEngine.h>

class DoColorState : public AzyEngine::AppState
{
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Terminate() override;
private:
	using Vertices = std::vector<AzyEngine::Graphics::VertexPC>;
	Vertices mVertices;
	AzyEngine::Graphics::MeshBuffer mMeshBuffer;
	AzyEngine::Graphics::VertexShader mVertexShader;
	AzyEngine::Graphics::PixelShader mPixelShader;
	AzyEngine::Graphics::Camera mCamera;
	AzyEngine::Graphics::ConstantBuffer mTransformBuffer;
};
