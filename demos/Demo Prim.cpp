#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main(int argc, char* argv[])
{
	const Size resolution(1000, 600);

	CScene scene(Vec3f::all(0.4f));

	auto pShaderTop  	= std::make_shared<CShaderPhong>(scene, RGB(0.90f, 0.75f, 0.70f), 0.5f, 0.5f, 0.0f, 40);
	auto pShaderSide 	= std::make_shared<CShaderPhong>(scene, RGB(0.55f, 0.65f, 0.70f), 0.7f, 0.5f, 0.0f, 40);
	auto pShaderWhite	= std::make_shared<CShaderFlat>(Vec3f::all(1));
	
	// primitives
	scene.add(std::make_shared<CPrimPlane>(std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.5f, 0.5f, 0.0f, 40), Vec3f(0, 0, 0), Vec3f(0, 1, 0)));
	// --- cube ---
//	scene.add(std::make_shared<CPrimTriangle>(pShaderTop,  Vec3f(1, 2, 1), Vec3f(-1, 2, 1), Vec3f(-1, 2, -1)));
//	scene.add(std::make_shared<CPrimTriangle>(pShaderTop,  Vec3f(1, 2, 1), Vec3f(1, 2, -1), Vec3f(-1, 2, -1)));
//	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(1, 2, 1), Vec3f(-1, 2, 1), Vec3f(-1, 0, 1)));
//	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(1, 2, 1), Vec3f(1, 0, 1), Vec3f(-1, 0, 1)));
//	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(1, 2, 1), Vec3f(1, 2, -1), Vec3f(1, 0, -1)));
//	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(1, 2, 1), Vec3f(1, 0, 1), Vec3f(1, 0, -1)));
//	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(-1, 2, -1), Vec3f(1, 2, -1), Vec3f(1, 0, -1)));
//	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(-1, 2, -1), Vec3f(-1, 0, -1), Vec3f(1, 0, -1)));
//	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(-1, 2, -1), Vec3f(-1, 2, 1), Vec3f(-1, 0, 1)));
//	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(-1, 2, -1), Vec3f(-1, 0, -1), Vec3f(-1, 0, 1)));
	// --- ---- ---
	scene.add(std::make_shared<CPrimTriangle>(pShaderWhite, Vec3f(-10, 10.01f, -10), Vec3f(-10, 10.01f, 10), Vec3f(10, 10.01f, -10)));
	scene.add(std::make_shared<CPrimTriangle>(pShaderWhite, Vec3f(10, 10.01f, 10), Vec3f(-10, 10.01f, 10), Vec3f(10, 10.01f, -10)));
	
//	scene.parseOBJ("/Users/creator/Projects/CG/eyden-tracer-03/data/cow.obj");
	
	scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderMirror>(scene), Vec3f(0, 1, 0), 1));
	scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderMirror>(scene), Vec3f(-2, 1, 2), 1));
	scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderMirror>(scene), Vec3f(2, 1, -2), 1));
//	scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderPhong>(scene, RGB(1, 0, 0),   0.2f, 0.5f, 0.5f, 40), Vec3f(-3, 2.7f, -1), 2));
//	scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderPhong>(scene, RGB(0, 0, 1),   0.2f, 0.5f, 0.5f, 40), Vec3f(2, 1.8f, -3), 2));
//	scene.add(std::make_shared<CPrimTriangle>(std::make_shared<CShaderPhong>(scene, RGB(0, 1, 1), 0.2f, 0.5f, 0.5f, 40), Vec3f(-3, 4.7f, -1), Vec3f(0, 3, 0), Vec3f(2, 3.8f, -3)));
//	scene.add(std::make_shared<CPrimTriangle>(std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.2f, 0.5f, 0.5f, 40), Vec3f(2, 3, 2), Vec3f(2, 3, -4), Vec3f(-4, 3, -4)));

	// lights
//	scene.add(std::make_shared<CLightPoint>(Vec3f::all(50), Vec3f(-10, 10, -10)));
//	scene.add(std::make_shared<CLightPoint>(Vec3f::all(50), Vec3f(-10, 10, 10)));
//	scene.add(std::make_shared<CLightPoint>(Vec3f::all(50), Vec3f(10, 10, 10)));
//	scene.add(std::make_shared<CLightPoint>(Vec3f::all(50), Vec3f(10, 10, -10)));
//	scene.add(std::make_shared<CLightPoint>(Vec3f(50, 50, 50), Vec3f(-4, 6, 3)));
	scene.add(std::make_shared<CLightPoint>(Vec3f::all(50), Vec3f(0, 2, 10), false));
	scene.add(std::make_shared<CLightArea>(Vec3f::all(6), Vec3f(-10, 10, -10), Vec3f(10, 10, -10), Vec3f(10, 10, 10), Vec3f(-10, 10, 10), std::make_shared<CSamplerStratified>(10, true, true)));

	// camera	
	const float r = 17.5f;
	auto mainCam = std::make_shared<CCameraPerspective>(Vec3f(0, 1, r), Vec3f(0, 0, -1), Vec3f(0, 1, 0), 60, resolution);
	scene.add(mainCam);
	scene.add(std::make_shared<CCameraPerspective>(Vec3f(-8, 3, 8), Vec3f(1, -0.1f, -1), Vec3f(0, 1, 0), 45, resolution));
	scene.add(std::make_shared<CCameraPerspective>(Vec3f(-8, 3, 8), Vec3f(1, -0.1f, -1), Vec3f(0, 1, 0), 45, resolution));
	Vec3f camPos(sqrt(r), sqrt(r), sqrt(r));
	scene.add(std::make_shared<CCameraPerspective>(camPos, normalize(Vec3f(0, 0.5f, 0) - camPos), Vec3f(0, 1, 0), 45, resolution));
	
	scene.setActiveCamera(3);
#ifdef ENABLE_BSP
	scene.buildAccelStructure();
#endif
//	Timer::start("Rendering 1 frame... ");
//	for (int i = 0; ; i++) {
//		float x = r * sinf(i * Pif / 180);
//		float z = r * cosf(i * Pif / 180);
//		Vec3f pos(x, 1, z);
//		Vec3f dir = normalize(Vec3f::all(0) - pos);
//		mainCam->setPosition(pos);
//		mainCam->setDirection(dir);
//		Mat img = RenderFrame(scene);
//		imshow("Image", img);
//		auto key = waitKey(5);
//		if (key > 0) break;
//		if (i % 60 == 0) {
//			Timer::stop();
//			Timer::start("Rendering 60 frames... ");
//		}
//	}

	// render three images with different camera settings
	Timer::start("Rendering... ");
	Mat img1 = scene.render();
	Timer::stop();
	imshow("Image1", img1);
	imwrite("cube.jpg", img1);
	//
	//scene.setActiveCamera(1);
	//Mat img2 = RenderFrame(scene);
	//imshow("Image2", img2);
	//imwrite("perspective2.jpg", img2);
	//
	//scene.setActiveCamera(2);
	//Mat img3 = RenderFrame(scene);
	//imshow("Image3", img3);
	//imwrite("perspective3.jpg", img3);

	waitKey();
	return 0;
}
