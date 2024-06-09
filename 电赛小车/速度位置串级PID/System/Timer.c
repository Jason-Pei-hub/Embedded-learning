#include "Timer.h"                  // Device header

int32_t count=0;//编码器脉冲数
float Speed=0;//期望速度转换成10ms内的脉冲

float expect_speed= 0;//期望速度	(几圈/s)
int expect_position= 0;//期望圈数	(几圈)

uint8_t stop_flag = 0;//停止标志位

//10ms定时
void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//选择APB1总线下的定时器Timer2
	
	TIM_InternalClockConfig(TIM5);		//使用内部时钟
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		//计数模式，此处为向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 100-1;		//ARR 
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200-1;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;		//高级计时器特有，重复计数
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM5, TIM_FLAG_Update);
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);		//使能中断
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;		//中断通道选择
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//优先级，同上
	
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM5, ENABLE);		//打开定时器
}   



void TIM5_IRQHandler(void){

	
	static short count_all_motor1 = 0;	// 第一个电机的编码器脉冲数的累加
	static short count_all_motor2 = 0;	// 第二个电机的编码器脉冲数的累加
	
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) == SET){
		int count_motor1 = Read_Encoder1();	// 读取第一个电机的编码器
		count_all_motor1 += count_motor1;	// 累加脉冲
		
		int count_motor2 = -Read_Encoder2();	// 读取第二个电机的编码器
		count_all_motor2 += count_motor2;	// 累加脉冲
		
		float speed_motor1 = (float)expect_speed * 1560 * 0.01;	// 将期望速度转换成10ms内的脉冲
		float speed_motor2 = (float)expect_speed * 1560 * 0.01;	// 将期望速度转换成10ms内的脉冲
		
		int motor1 = -PID_Position(expect_position * 1560, count_all_motor1);	// 计算第一个电机的PWM
		int motor2 = -PID_Position(expect_position * 1560, count_all_motor2);	// 计算第二个电机的PWM
		
		Limit(&motor1, (int)speed_motor1);	// 限幅第一个电机的PWM
		Limit(&motor2, (int)speed_motor2);	// 限幅第二个电机的PWM
		
		OLED_ShowSignedNum(2,9,count_motor1,5);
    OLED_ShowSignedNum(1,9,count_motor2,5);
		
    
		
		if (stop_flag == 1 || GFP_abs(count_all_motor1 - expect_position * 1560) < 30 || GFP_abs(count_all_motor2 - expect_position * 1560) < 30){									
			TIM1->CCR1 = 0;	// 停止第一个电机
			TIM1->CCR2 = 0;	// 停止第二个电机
			err_sum = 0;	// 清空积分值
		} else {
			motor1 = PID_Speed(motor1, count_motor1);	// 计算第一个电机的速度
			OLED_ShowSignedNum(4,9,motor1,5);
			Pwm_Out1(motor1);	// 输出第一个电机的PWM
			
			motor2 = PID_Speed(motor2, count_motor2);	// 计算第二个电机的速度
			OLED_ShowSignedNum(3,9,motor2,5);
			Pwm_Out2(motor2);	// 输出第二个电机的PWM
		}
		
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	}
}

