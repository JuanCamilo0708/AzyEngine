#include "Precompiled.h"

#include "TextureManager.h"

using namespace AzyEngine;
using namespace AzyEngine::Graphics;
namespace 
{
	std::unique_ptr<TextureManager> sTextureManager;
}

void TextureManager::StaticInitialize(const std::filesystem::path& root)
{
	ASSERT(sTextureManager == nullptr, "Texture Manager: is already initialize");
	sTextureManager = std::make_unique<TextureManager>();
	sTextureManager->SetRootDirectory(root);
}
void TextureManager::StaticTerminate()
{
	sTextureManager.reset();
}
TextureManager* TextureManager::Get()
{
	ASSERT(sTextureManager != nullptr, "Texture Manager: is not initialized");
	return sTextureManager.get();

}

TextureManager::~TextureManager()
{
	ASSERT(sTextureManager == nullptr, "Texture Manager: is not terminated");

}


void TextureManager::SetRootDirectory(const std::filesystem::path& root)
{
	mRootDirectory = root;
}
TextureID TextureManager::LoadTexture(const std::filesystem::path& fileName, bool useRootDir)
{
	const std::size_t textureId = std::filesystem::hash_value(fileName);
	auto [iter, success] = mInventory.insert({ textureId, Entry() });
	if (success)
	{
		iter->second.texture = std::make_unique<Texture>();
		iter->second.texture->Initialize((useRootDir) ? mRootDirectory / fileName:fileName);
		iter->second.refCount = 1;
	}
	else {
		++iter->second.refCount;
	}
	return textureId;
}
const Texture* TextureManager::GetTexture(TextureID id)
{
	auto iter = mInventory.find(id);
	if (iter != mInventory.end())
	{
		return iter->second.texture.get();
	}
	return nullptr;
}
void TextureManager::ReleaseTexture(TextureID id)
{
	auto iter = mInventory.find(id);
	if (iter != mInventory.end())
	{
		--iter->second.refCount;
		if (iter->second.refCount == 0)
		{
			iter->second.texture->Terminate();
			iter->second.texture.reset();
			mInventory.erase(iter);
		}
	}

}

void TextureManager::BindVS(TextureID id, uint32_t slot) const
{
	auto iter = mInventory.find(id);
	if (iter != mInventory.end())
	{
		iter->second.texture->BindVS(slot);
	}
}
void TextureManager::BindPS(TextureID id, uint32_t slot) const
{
	auto iter = mInventory.find(id);
	if (iter != mInventory.end())
	{
		iter->second.texture->BindPS(slot);
	}
}