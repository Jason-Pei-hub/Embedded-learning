#include "pwm.h"

void Pwm_Init(u16 arr, u16 psc) {
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    GPIO_InitTypeDef         GPIO_InitStructure;
    TIM_OCInitTypeDef        TIM_OCInitStructure;

    TIM_OCStructInit(&TIM_OCInitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_InternalClockConfig(TIM1);

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = arr - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);  // 通道1  PA8
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);  // 通道2  PA9

    TIM_CtrlPWMOutputs(TIM1, ENABLE);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM1, ENABLE);
    TIM_Cmd(TIM1, ENABLE);
}
	
//占空比调节
void Pwm_Out1(int Duty_cycle){   
	if(Duty_cycle >= 0){	
		GPIO_SetBits(GPIOE,GPIO_Pin_3);
		GPIO_ResetBits(GPIOE,GPIO_Pin_2);
	}
	else{
		GPIO_SetBits(GPIOE,GPIO_Pin_2);
		GPIO_ResetBits(GPIOE,GPIO_Pin_3);

	}
	
	Duty_cycle=GFP_abs(Duty_cycle);
		
	Limit(&Duty_cycle,7000);//限幅
		
	TIM1->CCR1 = Duty_cycle; //输出
		
}                                                                                                                

void Pwm_Out2(int Duty_cycle){   
	if(Duty_cycle >= 0){	
		GPIO_SetBits(GPIOE,GPIO_Pin_5);
		GPIO_ResetBits(GPIOE,GPIO_Pin_6);
	}
	else{
		GPIO_SetBits(GPIOE,GPIO_Pin_6);
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);

	}
	
	Duty_cycle=GFP_abs(Duty_cycle);
		
	Limit(&Duty_cycle,7000);//限幅
		
	TIM1->CCR2 = Duty_cycle; //输出
		
}                                                                                                                
