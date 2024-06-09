#include "Timer.h"                  // Device header

int32_t count=0;//������������
float Speed=0;//�����ٶ�ת����10ms�ڵ�����

float expect_speed= 0;//�����ٶ�	(��Ȧ/s)
int expect_position= 0;//����Ȧ��	(��Ȧ)

uint8_t stop_flag = 0;//ֹͣ��־λ

//10ms��ʱ
void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//ѡ��APB1�����µĶ�ʱ��Timer2
	
	TIM_InternalClockConfig(TIM5);		//ʹ���ڲ�ʱ��
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		//����ģʽ���˴�Ϊ���ϼ���
	TIM_TimeBaseInitStructure.TIM_Period = 100-1;		//ARR 
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200-1;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;		//�߼���ʱ�����У��ظ�����
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM5, TIM_FLAG_Update);
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);		//ʹ���ж�
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;		//�ж�ͨ��ѡ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//���ȼ���ͬ��
	
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM5, ENABLE);		//�򿪶�ʱ��
}   



void TIM5_IRQHandler(void){

	
	static short count_all_motor1 = 0;	// ��һ������ı��������������ۼ�
	static short count_all_motor2 = 0;	// �ڶ�������ı��������������ۼ�
	
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) == SET){
		int count_motor1 = Read_Encoder1();	// ��ȡ��һ������ı�����
		count_all_motor1 += count_motor1;	// �ۼ�����
		
		int count_motor2 = -Read_Encoder2();	// ��ȡ�ڶ�������ı�����
		count_all_motor2 += count_motor2;	// �ۼ�����
		
		float speed_motor1 = (float)expect_speed * 1560 * 0.01;	// �������ٶ�ת����10ms�ڵ�����
		float speed_motor2 = (float)expect_speed * 1560 * 0.01;	// �������ٶ�ת����10ms�ڵ�����
		
		int motor1 = -PID_Position(expect_position * 1560, count_all_motor1);	// �����һ�������PWM
		int motor2 = -PID_Position(expect_position * 1560, count_all_motor2);	// ����ڶ��������PWM
		
		Limit(&motor1, (int)speed_motor1);	// �޷���һ�������PWM
		Limit(&motor2, (int)speed_motor2);	// �޷��ڶ��������PWM
		
		OLED_ShowSignedNum(2,9,count_motor1,5);
    OLED_ShowSignedNum(1,9,count_motor2,5);
		
    
		
		if (stop_flag == 1 || GFP_abs(count_all_motor1 - expect_position * 1560) < 30 || GFP_abs(count_all_motor2 - expect_position * 1560) < 30){									
			TIM1->CCR1 = 0;	// ֹͣ��һ�����
			TIM1->CCR2 = 0;	// ֹͣ�ڶ������
			err_sum = 0;	// ��ջ���ֵ
		} else {
			motor1 = PID_Speed(motor1, count_motor1);	// �����һ��������ٶ�
			OLED_ShowSignedNum(4,9,motor1,5);
			Pwm_Out1(motor1);	// �����һ�������PWM
			
			motor2 = PID_Speed(motor2, count_motor2);	// ����ڶ���������ٶ�
			OLED_ShowSignedNum(3,9,motor2,5);
			Pwm_Out2(motor2);	// ����ڶ��������PWM
		}
		
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	}
}

