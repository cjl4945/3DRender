#include "Renderer3D.h"

Renderer3D::Renderer3D(SDL_Window* _window, SDL_Renderer* _renderer, vector<Point3D>& _points, vector<Vertex> _verticies)
{
	SDL_GetWindowSize(_window, &WindowSizeX, &WindowSizeY);
	renderer = _renderer;
	points = _points;
	verticies = _verticies;
}

void Renderer3D::render()
{
	//frame-independent timing
	auto time1 = chrono::high_resolution_clock::now();
	chrono::duration<double> duration(0);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	rotation += 1 * DeltaTime;

	for (auto& vertex : verticies)
	{
		Point3D rotatedStartPoint = rotateX(rotateY(points[vertex.start]));
		Point3D rotatedEndPoint = rotateX(rotateY(points[vertex.start]));
		Point3D start = projection(rotatedStartPoint);
		Point3D end = projection(rotatedEndPoint);
		SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);

	}
	SDL_RenderPresent(renderer);

	auto time2 = chrono::high_resolution_clock::now();
	duration = time2 - time1;
	DeltaTime - duration.count();
	time1 = time2;
}
Point3D Renderer3D::rotateX(Point3D point)
{
	Point3D returnPoint;
	returnPoint.x = point.x;
	returnPoint.y = cos(rotation) * point.y - sin(rotation) * point.z;
	returnPoint.z = sin(rotation) * point.y - cos(rotation) * point.z;
	return returnPoint;
}

Point3D Renderer3D::rotateY(Point3D point)
{
	Point3D returnPoint;
	returnPoint.x = cos(rotation)* point.x - sin(rotation) * point.z;
	returnPoint.y = point.x;
	returnPoint.z = sin(rotation) * point.x - cos(rotation) * point.z;
	return returnPoint;
}

Point2D Renderer3D::projection(Point3D point) {
	return Point2D{WindowSizeX / 2 + (FOV * point.x) / (FOV + point.z) * 100, WindowSizeY / 2 + (FOV * point.y)}
}

