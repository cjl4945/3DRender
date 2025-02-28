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

	//flip image vertically
	stbi_set_flip_vertically_on_load(true);
	
	//load image data
	res.data = stbi_load(path.c_str(), &res.width, &res.height, &res.channels, 0);
	if (!res.data)
	{
		std::cerr << "Failed to load texture: " << path << std::endl;
	}
	
		return res;
	}





void ResourceManager::loadResourceAsync(const std::string& path)
{
	//launch an asynchronous task to load the texture
	std::future<ResourceData> futureRes = std::async(std::launch::async, &ResourceManager::loadResource, this, path);

	//Wait for resource to load. Look into decoupling this later
	ResourceData res = futureRes.get();
	{
		std::lock_guard<std::mutex> lock(queueMutex);
		resourceQueue.push(res);
	}


}

bool ResourceManager::getNextResource(ResourceData& resource)
{
	//resources can't be modified
	std::lock_guard<std::mutex> lock(queueMutex);
	if (resourceQueue.empty())
		return false;
	resource = resourceQueue.front();
	resourceQueue.pop();
	return true;
}
