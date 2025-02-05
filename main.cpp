#include "Renderer3D.h"
#include <vector>
#include <SDL.h>


//cube shape
vector<Point3D> points{ Point3D{-1.0f, -1.0f, -1.0f}, Point3D{-1.0f, -1.0f, 1.0f}, Point3D{1.0f, -1.0f, -1.0f}, Point3D{-1.0f, 1.0f, -1.0f},
						Point3D{-1.0f, 1.0f, 1.0f}, Point3D{1.0f, -1.0f, 1.0f}, Point3D{1.0f, 1.0f, -1.0f}, Point3D{1.0f, 1.0f, 1.0f} };

vector<Vertex> verticies{ Vertex{0, 1 }, Vertex{0, 2 }, Vertex{0, 3 },
							Vertex{2, 5 }, Vertex{3, 6 }, Vertex{3, 4 },
							Vertex{4, 7 }, Vertex{6, 7 }, Vertex{7, 5 },
							Vertex{5, 1 }, Vertex{4, 1 }, Vertex{2, 6 } };


//pyramid
//vector<point3d> points2{ point3d{-1.0f, -1.0f, -1.0f}, point3d{-1.0f, -1.0f, 1.0f}, point3d{1.0f, -1.0f, -1.0f}, point3d{-1.0f, 1.0f, -1.0f},
//						point3d{-1.0f, 1.0f, 1.0f}, point3d{1.0f, -1.0f, 1.0f}, point3d{1.0f, 1.0f, -1.0f}, point3d{1.0f, 1.0f, 1.0f} };
//
//vector<vertex> verticies2{ vertex{0, 1 }, vertex{0, 2 }, vertex{0, 3 },
//							vertex{2, 5 }, vertex{3, 6 }, vertex{3, 4 },
//							vertex{4, 7 }, vertex{6, 7 }, vertex{7, 5 },
//							vertex{5, 1 }, vertex{4, 1 }, vertex{2, 6 } };
//
////random object
//vector<point3d> points3{ point3d{-1.0f, -1.0f, -1.0f}, point3d{-1.0f, -1.0f, 1.0f}, point3d{1.0f, -1.0f, -1.0f},
//						point3d{-1.0f, 1.0f, -1.0f}, point3d{-1.0f, 1.0f, 1.0f}, point3d{1.0f, -1.0f, 1.0f} };
//
//vector<vertex> verticies3{ vertex{0, 1 }, vertex{0, 2 }, vertex{0, 3 },
//							vertex{2, 5 }, vertex{3, 6 }, vertex{3, 4 } };

int main(int argc, char** argv) {

	//creation of window and a renderer
	//sdl_window* window;
	//sdl_renderer* renderer;
	//window = sdl_createwindow("3d renderer", sdl_windowpos_centered, sdl_windowpos_centered, 960, 540, 0);
	//renderer = sdl_createrenderer(window, 1, sdl_renderer_accelerated);

	//bool running = true;

	//creating a 3d renderer
	//renderer3d renderer3d1(window, renderer, points, verticies);

	//while (running)
	//{
	//	close window
	//	if (sdl_quitrequested()) { running = false; break; }
	//	renderer3d1.render();
	//}
	//return 0;




}