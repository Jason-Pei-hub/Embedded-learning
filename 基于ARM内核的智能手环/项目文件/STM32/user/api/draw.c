#include <draw.h>


// ������ת��Ϊ����
double portion_to_radians(int portion) 
	{
		
    return portion/60.0*360*M_PI/180; // ÿ��6�ȣ���PI/30����
}

void get_points_on_concentric_circles(int cx, int cy, double small_r, double big_r, int portion, int *x1, int *y1, int *x2, int *y2) 
{
    double angle_radians = portion_to_radians(portion);

    // ����СԲ�ϵĵ�����
    *x1 = cx + (int)(small_r * sin(angle_radians));
    *y1 = cy - (int)(small_r * cos(angle_radians)); // СԲ�ϵĵ�

    // �����Բ�ϵĵ�����
    double angle_radians_big = portion_to_radians(portion);
    *x2 = cx + (int)(big_r * sin(angle_radians_big));
    *y2 = cy - (int)(big_r * cos(angle_radians_big)); // ��Բ�ϵĵ�
}


