#include "include/next_rkcg.h"

int main() {

    // 初始化画布
	const int WIDTH = 800, HEIGHT = 800;
	const ege::color_t BG_COLOR = ege::COLORS::WHITE;
	rkcg::createCanvas(WIDTH, HEIGHT, BG_COLOR);


    rkcg::Rectangle rect(200, -100, 200, -100);
    rect.draw();

    rkcg::Segment seg1(-50, -50, 50, 50);
    rkcg::Segment seg2(-150, 50, 250, 100);
    rkcg::Segment seg3(100, 100, -50, 230);

    seg1.draw(ege::COLORS::RED);
    seg2.draw(ege::COLORS::BLUE);
    seg3.draw(ege::COLORS::GREEN);

    rkcg::CohenSutherlandLineClip(seg1, rect, ege::COLORS::RED);
    rkcg::CohenSutherlandLineClip(seg2, rect, ege::COLORS::BLUE);

    rkcg::LiangBarskyLineClip(seg3, rect, ege::COLORS::GREEN);

    // UI 关闭才退出程序
	while (ege::is_run()) {
		ege::delay(1000);
		// std::cout << "running" << std::endl;
	}
    return 0;
}