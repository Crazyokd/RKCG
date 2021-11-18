#include "include/next_rkcg.h"

void draw() {
	// 绘制代码放这里
}

int main() {
	// 初始化画布
	const int WIDTH = 800, HEIGHT = 800;
	const ege::color_t BG_COLOR = ege::COLORS::WHITE;
	rkcg::createCanvas(WIDTH, HEIGHT, BG_COLOR);

	draw();

	// UI 关闭才退出程序
	while (ege::is_run()) {
		ege::delay(1000);
		// std::cout << "running" << std::endl;
	}
	return 0;
}