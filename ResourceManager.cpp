#include "ResourceManager.h"
#include <iostream>
#include <future>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	//free any remaining texture data in the queue
	while (!resourceQueue.empty())
	{
		ResourceData res = resourceQueue.front();
		stbi_image_free(res.data);
		resourceQueue.pop();
	}
}

ResourceData ResourceManager::loadResource(const std::string& path)
{
	ResourceData res;
	res.name = path;

	//
}
