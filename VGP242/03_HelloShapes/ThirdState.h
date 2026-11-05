#pragma once
#include <AzyEngine/Inc/AzyEngine.h>

class ThirdState : public AzyEngine::AppState
{
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Terminate() override;
private:
	struct Vertex
	{
		AzyEngine::Math::Vector3 position = AzyEngine::Math::Vector3::Zero;
		AzyEngine::Color color = AzyEngine::Colors::White;
	};
	using Vertices = std::vector<Vertex>;
	Vertices mVertices;

	ID3D11Buffer* mVertexBuffer = nullptr;

	ID3D11VertexShader* mVertexShader = nullptr;

	ID3D11InputLayout* mInputLayout = nullptr;

	ID3D11PixelShader* mPixelShader = nullptr;

};