#pragma once
#include <string>
#include <queue>
#include <mutex>

struct ResourceData
{
	std::string name;
	unsigned char* data;
	int width, height, channels;

};

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	//async load texture from disk
	void loadResourceAsync(const std::string& path);

	bool getNextResource(ResourceData& resource);

private:
	//thread-safe queue to store loaded resources
	std::queue<ResourceData> resourceQueue;
	std::mutex queueMutex;

	//Load the resource using stb_image
	ResourceData loadResource(const std::string& path);
};

