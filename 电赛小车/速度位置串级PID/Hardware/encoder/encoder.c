#include "encoder.h" 

void Encoder_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
    GPIO_InitTypeDef         GPIO_InitStructure;
    TIM_ICInitTypeDef        TIM_ICInitInitStructure;

    /* 时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // 定时器2
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // TIM2 初始化
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1; // ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 0; // PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    // TIM3 初始化
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

    // 输入捕获单元配置
    TIM_ICStructInit(&TIM_ICInitInitStructure);

    TIM_ICInitInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitInitStructure.TIM_ICFilter = 10;
    TIM_ICInit(TIM2, &TIM_ICInitInitStructure);

    TIM_ICInitInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM2, &TIM_ICInitInitStructure);

    TIM_ICInitInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInit(TIM3, &TIM_ICInitInitStructure);

    TIM_ICInitInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM3, &TIM_ICInitInitStructure);

    // 配置编码器接口
    TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_SetCounter(TIM2, 0);
    TIM_Cmd(TIM2, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
}

int32_t Read_Encoder1(void){
    int32_t Encoder_TIM;

    Encoder_TIM = (short)TIM_GetCounter(TIM2);
    TIM_SetCounter(TIM2, 0);

    return Encoder_TIM;
}

int32_t Read_Encoder2(void){
    int32_t Encoder_TIM;

    Encoder_TIM = (short)TIM_GetCounter(TIM3);
    TIM_SetCounter(TIM3, 0);

    return Encoder_TIM;
}
