/* 
 * 计算机图形学实验三：多边形的扫描转换
 *
 * 任务：
 * 	A：扫描线算法
 * 	B：种子填充算法
 */

#include "rkcg.h"

#include <string>
#include <vector>

inline void putString(const int relativeX, const int relatevieY, const LPCSTR str) {
	//写文字，注意：outtextxy不支持\t \n这类格式化用的特殊字符，这类字符会被忽略
    //要使用特殊格式化字符请用outtextrect
	outtextxy(setCoordinateX(relativeX), setCoordinateY(relatevieY), str);
}
inline void putString(const int relativeX, const int relatevieY, const std::string &str) {
	outtextxy(setCoordinateX(relativeX), setCoordinateY(relatevieY), str.c_str());
}

void createCanvas(const int width, const int height, const ege::color_t bgColor = ege::COLORS::WHITE) {
	const int half_width = width >> 1;
	const int half_height = height >> 1;
	const int shift = 10;

	// 坐标轴颜色
	const ege::color_t axis_color = ege::COLORS::BLACK;

	// x 坐标轴端点坐标
	const int x_left_x = -half_width + shift;
	const int x_left_y = 0;
	const int x_right_x = half_width - shift;
	const int x_right_y = 0;

	// y 坐标轴端点坐标
	const int y_top_x = 0;
	const int y_top_y = half_height - shift;
	const int y_bottom_x = 0;
	const int y_bottom_y = -half_height + shift;

	initgraph(width, height);
	setbkcolor(bgColor);
	setcolor(ege::COLORS::BLACK);
	setfont(20, 0, "宋体");

	drawArrow(x_left_x, x_left_y, x_right_x, x_right_y, axis_color);
	drawArrow(y_bottom_x, y_bottom_y, y_top_x, y_top_y, axis_color);

	drawScale(0, 0, x_right_x, x_right_y, axis_color);
	drawScale(x_left_x, x_left_y, 0, 0, axis_color);
	drawScale(0, 0, y_top_x, y_top_y, axis_color);
	drawScale(y_bottom_x, y_bottom_y, 0, 0, axis_color);
	putString(-20, -shift, "O");
	putString(half_width - (shift << 1), -shift, "x");
	putString(-15, half_height - shift, std::string("y"));
}

namespace rkcg {
	inline void putPixel(const int relativeX, const int relativeY, const ege::color_t color) {
		ege::putpixel(setCoordinateX(relativeX), setCoordinateY(relativeY), color);
	}
	inline void putPixel(const point &relativePoint, const ege::color_t color) {
		ege::putpixel(setCoordinateX(relativePoint.x), setCoordinateY(relativePoint.y), color);
	}
	inline ege::color_t getPixel(const int relativeX, const int relativeY) {
		return ege::getpixel(setCoordinateX(relativeX), setCoordinateY(relativeY));
	}
};

inline void MidPointLineX(const point &p0, const point &p1, const ege::color_t color) {
	MidPointLineX(p0.x, p0.y, p1.x, p1.y, color);
}

// 顺时针连接各点
void connectPoints(const std::vector<point> &points, const ege::color_t color = ege::COLORS::BLACK) {
	if (points.empty()) return;
	MidPointLineX(points.back(), points.front(), color);
	for (size_t i = 1; i < points.size(); ++i) {
		MidPointLineX(points[i - 1], points[i], color);
	}
}
void connectPoints(const point points[], const int len, const ege::color_t color = ege::COLORS::BLACK) {
	if (len <= 0) return;
	MidPointLineX(points[0], points[len - 1], color);
	for (size_t i = 1; i < len; ++i) {
		MidPointLineX(points[i - 1], points[i], color);
	}
}

// 真正的区域填充函数，使用绝对坐标提高效率
void egeSeedFill(const int x, const int y, const ege::color_t fillColor, const ege::color_t borderColor = ege::COLORS::BLACK) {
	const ege::color_t color = ege::getpixel(x, y);
	if (color == borderColor || color == fillColor) return;
	ege::putpixel(x, y, fillColor);

	// 区域填充过于费时，不推荐增加延迟观察填充过程
	// ege::delay(1);

	egeSeedFill(x - 1, y, fillColor, borderColor);
	egeSeedFill(x, y + 1, fillColor, borderColor);
	egeSeedFill(x + 1, y, fillColor, borderColor);
	egeSeedFill(x, y - 1, fillColor, borderColor);
}

// 使用相对坐标的区域填充函数，先转化成绝对坐标再调用真正的填充函数提高效率
inline void seedFill(const int relativeX, const int relativeY, const ege::color_t fillColor, const ege::color_t borderColor = ege::COLORS::BLACK) {
	egeSeedFill(setCoordinateX(relativeX), setCoordinateY(relativeY), fillColor, borderColor);
}
inline void seedFill(const point &seed, const ege::color_t fillColor, const ege::color_t borderColor = ege::COLORS::BLACK) {
	egeSeedFill(setCoordinateX(seed.x), setCoordinateY(seed.y), fillColor, borderColor);
}

inline void scanConversionPolygon(const std::vector<point> &points, const ege::color_t &color) {
	scanConversionPolygon(&points.front(), points.size(), color);
}

int main() {
	// 初始化画布
	const int WIDTH = 800, HEIGHT = 800;
	const ege::color_t BG_COLOR = ege::COLORS::WHITE;
	createCanvas(WIDTH, HEIGHT, BG_COLOR);

	// 实验代码 begin

	// 图形 A
	std::cout << "begin " << std::endl;
	const std::vector<point> aPoints{
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
	const point p0{200, 200};
	const point p1{250, 250};
	const std::vector<point> bPoints{
		p0,
		{p0.x, p1.y},
		p1,
		{p1.x, p0.y},
	};
	connectPoints(bPoints, ege::COLORS::RED);

	const point seed{(p0.x + p1.x) >> 1, (p0.y + p1.y) >> 1};
	// 注意边界颜色和填充颜色不要和坐标轴颜色（也就是黑色）相同
	seedFill(seed, ege::COLORS::BLUE, ege::COLORS::RED);

	// 实验代码 end


	// UI 关闭才退出程序
	while (ege::is_run()) {
		delay(1000);
		// std::cout << "running" << std::endl;
	}
	return 0;
}