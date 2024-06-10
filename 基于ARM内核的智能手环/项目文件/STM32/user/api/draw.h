#ifndef _DRAW_H
#define _DRAW_H

#include "main.h"

#define M_PI 3.14159265358979323846

// 将份数转换为弧度
double portion_to_radians(int portion) ;
// 计算圆上的点坐标
// cx, cy: 圆心坐标
// r: 圆半径
// portion: 旋转的份数
void get_points_on_concentric_circles(int cx, int cy, double small_r, double big_r, int portion, int *x1, int *y1, int *x2, int *y2) ;

#endif