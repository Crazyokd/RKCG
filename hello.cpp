#include"rkcg.h"

using namespace rkcg;
int main()
{
	ege::initgraph(640, 480);				//初始化图形界面
	ege::setcolor(EGERGB(0xFF, 0x0, 0x0));	//设置绘画颜色为红色
	ege::setbkcolor(ege::WHITE);					//设置背景颜色为白色

	ege::setfont(14, 0, "宋体");
	//写文字，注意：outtextxy不支持\t \n这类格式化用的特殊字符，这类字符会被忽略
    //要使用特殊格式化字符请用outtextrect
    ege::outtextxy(setCoordinateX(200), setCoordinateY(0), "X");
    ege::outtextxy(setCoordinateX(5), setCoordinateY(200), "Y");
    // outtextrect(100, 120, 200, 100, "\tHello EGE Graphics\nHere is the next line.");
	// 画一个直角坐标系
	drawArrow(-200,0,200,0,0);
	drawScale(-180,0,180,0,0);
	drawArrow(0,-200,0,200,0);
	drawScale(0,-180,0,180,0);
	//画Z轴
	drawArrow(150,150,-150,-150,0);

	// ege::line(setCoordinateX(-100),setCoordinateY(-50),
	// 	setCoordinateX(100),setCoordinateY(50));
	// MidPointLineX(-100,-50,100,50,0x777777);//画一条直线
	// drawCircle(100,0);//画圆,圆心在坐标原点
	// CircleBres(100,0);
	// drawCircle(100,0,50,50);//画圆,指定圆心坐标
	// drawEllipse(50,70,0,50,50);
	// scanConversionPolygon(pp,7,0x777777);
	// scanConversionPolygon(pp,7,ege::RED);
	point pp2[]={*(new point(-50,-50)),*(new point(-50,0)),*(new point(0,0)),*(new point(0,-50))};
	point pp3[]={point(0,0),point(0,50),point(50,50),point(50,0)};
	// scanConversionPolygon(pp2,4,ege::GREEN);
	// scanConversionPolygon(pp3,4,0);

	// 确定边界
	// MidPointLineX(-50,-50,-50,0,ege::RED);
	// MidPointLineX(-50,0,0,0,ege::RED);
	// MidPointLineX(0,0,0,-50,ege::RED);
	// MidPointLineX(0,-50,-50,-50,ege::RED);

	// startFloodFill4(-25,-25,ege::BLUE);
	// startScanLineFill(65,25,ege::BLUE);

	// ege::ege_rect rect=ege::ege_rect();
	// rect.x=rect.y=-50;
	// rect.w=rect.h=100;
	// drawRectangle(rect,ege::COLORS::RED);
	// CohenSutherlandLineClip(-100,-100,100,100,&rect);
	// CohenSutherlandLineClip(-25,-75,25,75,&rect);
	// LiangBarskyLineClip(-100,-100,100,100,&rect);

	// CohenSutherlandLineClip(-25,25,25,-25,&rect);
	// // LiangBarskyLineClip(-25,25,25,-25,&rect);
	// LiangBarskyLineClip(200,-50,200,50,&rect);
	std::vector<point> points;
	// points.push_back(point(50,10));
	// points.push_back(point(20,40));
	// points.push_back(point(20,80));
	// points.push_back(point(70,70));
	// points.push_back(point(120,110));
	// points.push_back(point(120,50));
	// points.push_back(point(70,10));
	// getPolygonFromPoints(points,0);
	// // 演示五种基础变换
	// getPolygonFromPoints(transformationFromType(points,TRANSLATION,-50,0),0);
	// getPolygonFromPoints(transformationFromType(points,PROPORTION,1.5,1.5),0);
	// getPolygonFromPoints(transformationFromType(points,ROTATE,0,0,60),0);
	// getPolygonFromPoints(transformationFromType(points,SYMMETRICX),0);
	// getPolygonFromPoints(transformationFromType(points,SYMMETRICY),0);

	points.push_back(point(50,50));
	points.push_back(point(100,50));
	points.push_back(point(100,100));
	// getPolygonFromPoints(points,0);
	// //y=50+x;
	// MidPointLineX(0,50,150,200,0);
	// getPolygonFromPoints(reflectionTransformationByArbitraryLine(points,50,1,1),0);
	// MidPointLineX(20,-200,20,200,0);
	// getPolygonFromPoints(reflectionTransformationByArbitraryLine(points,-20,1,0),0);
	// MidPointLineX(-200,20,200,20,0);
	// getPolygonFromPoints(reflectionTransformationByArbitraryLine(points,20,0,1),0);

	// std::vector<point> datum_points;
	// datum_points.push_back({140, 25});
	// datum_points.push_back({150, 100});
	// datum_points.push_back({175, 125});
	// datum_points.push_back({200, 25});
	
	// connectPoints(getPointOfBezierCurve(datum_points),0);

	// std::vector<point> datum_points2;
	// datum_points2.push_back({-140, -25});
	// datum_points2.push_back({-150, -100});
	// datum_points2.push_back({-175, -125});
	// datum_points2.push_back({-200, -25});
	// datum_points2.push_back({-210,0});
	// connectPoints(getPointOfBezierCurve(datum_points2),ege::RED);

	//画一个立方体
	std::vector<std::vector<point>> ppp;
	std::vector<point> pp1;
	std::vector<point> ppp2;
	std::vector<point> ppp3;
	std::vector<point> pp4;
	pp1.push_back(point(0,100));
	for(int i=1;i<4;i++)
		pp1.push_back(point(pp1[i-1].x-30*DEVIATION,pp1[i-1].y-30*DEVIATION));

	ppp2.push_back(point(40,60));
	for(int i=1;i<4;i++)
		ppp2.push_back(point(ppp2[i-1].x-30*DEVIATION,ppp2[i-1].y-30*DEVIATION));

	ppp3.push_back(point(100,120));
	for(int i=1;i<4;i++)
		ppp3.push_back(point(ppp3[i-1].x-30*DEVIATION,ppp3[i-1].y-30*DEVIATION));

	pp4.push_back(point(120,80));
	for(int i=1;i<4;i++)
		pp4.push_back(point(pp4[i-1].x-30*DEVIATION,pp4[i-1].y-30*DEVIATION));

	ppp.push_back(pp1);
	ppp.push_back(ppp2);
	ppp.push_back(ppp3);
	ppp.push_back(pp4);

	connectPoints(drawBezierCurveSurface(ppp),0);


	ege::getch();							//暂停，等待键盘按键
	ege::closegraph();						//关闭图形界面
	return 0;
}