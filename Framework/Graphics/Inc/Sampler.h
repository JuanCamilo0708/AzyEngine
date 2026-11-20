#pragma once

namespace AzyEngine::Graphics
{
	class Sampler
	{
	public:
		enum class Filter {Point, Linear, Anistropic};
		enum class Addressmode {Border, Clamp, Mirror, Wrap};

		Sampler() = default;
		~Sampler();

		Sampler(const Sampler&) = delete;
		Sampler(Sampler&&) = delete;
		Sampler& operator=(const Sampler&) = delete;
		Sampler& operator=(Sampler&&) = delete;

		void Initialize(Filter filter, Addressmode addressMode);
		void Terminate();

		void BindVS(uint32_t slot) const;
		void BindPS(uint32_t slot) const;
	private:
		ID3D11SamplerState* mSampler = nullptr;
	};
}