#ifndef _DRAW_H
#define _DRAW_H

#include "main.h"

#define M_PI 3.14159265358979323846

// ������ת��Ϊ����
double portion_to_radians(int portion) ;
// ����Բ�ϵĵ�����
// cx, cy: Բ������
// r: Բ�뾶
// portion: ��ת�ķ���
void get_points_on_concentric_circles(int cx, int cy, double small_r, double big_r, int portion, int *x1, int *y1, int *x2, int *y2) ;

#endif