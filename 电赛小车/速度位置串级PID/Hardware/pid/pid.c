#include "pid.h"

int err_sum=0;//积分和

float Speed_Kp=8,Speed_Ki=0.1;
float Position_Kp=1,Position_Ki=0.01,Position_Kd=0.01;  

//限制幅度
void Limit(int *Duty_cycle,int Amplitude){
	int Pwm_Max=Amplitude;
	int	Pwm_Min=-Amplitude;
	
	if(*Duty_cycle>Pwm_Max)	*Duty_cycle=Pwm_Max;
	if(*Duty_cycle<Pwm_Min)	*Duty_cycle=Pwm_Min;
}

//取绝对值函数
int GFP_abs (int p)
{
	int q;
	q=p>0?p:(-p);
	return q;
}

/*
	speed 期望速度
	encoder当前速度
*/
int16_t PID_Speed(int16_t speed, int16_t encoder){
	static int16_t out, err, err_lowout, err_lowout_last;
	static float integral_s = 0.0;
	
	err = speed - encoder;
	err_lowout = 0.3 * err + 0.7 * err_lowout_last; // 低通滤波
	err_lowout_last = err_lowout;
	
	integral_s += err_lowout * 0.01; // 假设采样周期为10ms
	
	integral_s = integral_s >= 50.0 ? 50.0 : (integral_s < -50.0 ? -50.0 : integral_s); // 积分限幅
	
	out = Speed_Kp * err_lowout + Speed_Ki * integral_s;
	
	return out;
}

/*
	trage_position 		期望位置
	current_position	当前位置
*/

int PID_Position(int expect_position, int current_position){
	static int out, err, integral_s, err_last;
	
	err = expect_position - current_position;
	
	integral_s += err;
	
	integral_s = integral_s >= 3000 ? 3000 : (integral_s < -3000 ? -3000 : integral_s); // 积分限幅
	
	out = Position_Kp * err + Position_Ki * integral_s + Position_Kd * (err - err_last) * 0.01; // 假设采样周期为10ms
	
	err_last = err;
	
	return out;
}
