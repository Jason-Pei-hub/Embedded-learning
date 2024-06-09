#include "pid.h"

int err_sum=0;//���ֺ�

float Speed_Kp=8,Speed_Ki=0.1;
float Position_Kp=1,Position_Ki=0.01,Position_Kd=0.01;  

//���Ʒ���
void Limit(int *Duty_cycle,int Amplitude){
	int Pwm_Max=Amplitude;
	int	Pwm_Min=-Amplitude;
	
	if(*Duty_cycle>Pwm_Max)	*Duty_cycle=Pwm_Max;
	if(*Duty_cycle<Pwm_Min)	*Duty_cycle=Pwm_Min;
}

//ȡ����ֵ����
int GFP_abs (int p)
{
	int q;
	q=p>0?p:(-p);
	return q;
}

/*
	speed �����ٶ�
	encoder��ǰ�ٶ�
*/
int16_t PID_Speed(int16_t speed, int16_t encoder){
	static int16_t out, err, err_lowout, err_lowout_last;
	static float integral_s = 0.0;
	
	err = speed - encoder;
	err_lowout = 0.3 * err + 0.7 * err_lowout_last; // ��ͨ�˲�
	err_lowout_last = err_lowout;
	
	integral_s += err_lowout * 0.01; // �����������Ϊ10ms
	
	integral_s = integral_s >= 50.0 ? 50.0 : (integral_s < -50.0 ? -50.0 : integral_s); // �����޷�
	
	out = Speed_Kp * err_lowout + Speed_Ki * integral_s;
	
	return out;
}

/*
	trage_position 		����λ��
	current_position	��ǰλ��
*/

int PID_Position(int expect_position, int current_position){
	static int out, err, integral_s, err_last;
	
	err = expect_position - current_position;
	
	integral_s += err;
	
	integral_s = integral_s >= 3000 ? 3000 : (integral_s < -3000 ? -3000 : integral_s); // �����޷�
	
	out = Position_Kp * err + Position_Ki * integral_s + Position_Kd * (err - err_last) * 0.01; // �����������Ϊ10ms
	
	err_last = err;
	
	return out;
}
