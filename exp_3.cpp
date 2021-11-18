/* 
 * 计算机图形学实验三：多边形的扫描转换
 *
 * 任务：
 * 	A：扫描线算法
 * 	B：种子填充算法
 */

#include "include/next_rkcg.h"

#include <string>
#include <vector>

void draw() {
	// 图形 A
	std::cout << "begin " << std::endl;
	const std::vector<rkcg::point> aPoints{
		{0, 100},
		{30, 50},
		{100, 50},
		{60, 0},
		{80, -80},
		{0, -20},
		{-80, -80},
		{-60, 0},
		{-100, 50},
		{-30, 50},
	};
	scanConversionPolygon(aPoints, ege::COLORS::CYAN);
	std::cout << "ok" << std::endl;
	// startScanLineFill(-60,-30,ege::BLUE);

	// 图形 B
	const rkcg::point p0{200, 200};
	const rkcg::point p1{250, 250};
	const std::vector<rkcg::point> bPoints{
		p0,
		{p0.x, p1.y},
		p1,
		{p1.x, p0.y},
	};
	connectPoints(bPoints, ege::COLORS::RED);

	const rkcg::point seed{(p0.x + p1.x) >> 1, (p0.y + p1.y) >> 1};
	// 注意边界颜色和填充颜色不要和坐标轴颜色（也就是黑色）相同
	seedFill(seed, ege::COLORS::BLUE, ege::COLORS::RED);
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