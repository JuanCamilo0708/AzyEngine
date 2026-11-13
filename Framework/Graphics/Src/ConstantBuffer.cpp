#include "Precompiled.h"
#include "ConstantBuffer.h"
#include "GraphicsSystem.h"

using namespace AzyEngine;
using namespace AzyEngine::Graphics;

ConstantBuffer::~ConstantBuffer() 
{
	ASSERT(mConstantBuffer == nullptr, "ConstantBuffer: terminate must be called");
}

void ConstantBuffer::Initialize(uint32_t bufferSize)
{
	auto device = GraphicsSystem::Get()->GetDivice();

	D3D11_BUFFER_DESC desc{};
	desc.ByteWidth = bufferSize;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	HRESULT hr = device->CreateBuffer(&desc, nullptr, &mConstantBuffer);
	ASSERT(SUCCEEDED(hr), "ConstantBuffer: failde to create constant buffer");
}
void ConstantBuffer::Terminate()
{
	SafeRelease(mConstantBuffer);
}
void ConstantBuffer::Update(const void* data) const
{
	auto contex = GraphicsSystem::Get()->GetContext();
	contex->UpdateSubresource(mConstantBuffer, 0, nullptr, data, 0, 0);
}
void ConstantBuffer::BindVS(uint32_t slot) const
{
	auto contex = GraphicsSystem::Get()->GetContext();
	contex->VSSetConstantBuffers(slot, 1, &mConstantBuffer);
}
void ConstantBuffer::BindPS(uint32_t slot) const
{
	auto contex = GraphicsSystem::Get()->GetContext();
	contex->PSSetConstantBuffers(slot, 1, &mConstantBuffer);

}