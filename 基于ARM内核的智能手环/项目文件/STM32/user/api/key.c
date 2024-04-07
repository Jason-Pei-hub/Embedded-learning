#include "key.h"
#define check_count 5
#define long_press_count 10 

void KEY_Config()
{
	//KEY1 --paPA0
	//KEY2 --paPC5
	//KEY3 --paPC6
  //浮空输入
	//step1.开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOA,ENABLE);
	
	//step2.配置IO口模式
	GPIO_InitTypeDef	GPIO_InitSTRUCT;
	GPIO_InitSTRUCT.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitSTRUCT.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitSTRUCT.GPIO_Speed = GPIO_Speed_50MHz;
	
	//step3.初始化IO口
	GPIO_Init(GPIOA,&GPIO_InitSTRUCT);
	
	GPIO_InitSTRUCT.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	
	GPIO_Init(GPIOC,&GPIO_InitSTRUCT);
}


uint8_t KEY_Check(void)
{
    static uint8_t key_status[4] = {1, 1, 1, 1}; 
    static uint8_t key_count[4] = {0};
    uint8_t i;
    uint8_t key_press[4] = {0};

    // 检测按键状态变化
    for (i = 0; i < 4; i++)
    {
        switch (i)
        {
        case 0:
            key_press[i] = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
            break;
        case 1:
            key_press[i] = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4);
            break;
        case 2:
            key_press[i] = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5);
            break;
        case 3:
            key_press[i] = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6);
            break;
        }

        if (key_press[i] != key_status[i])
        {
            key_count[i]++;
            if (key_count[i] >= check_count) // 修改此处，移除类型转换
            {
                key_status[i] = key_press[i];
                key_count[i] = 0;
            }

            if (key_press[i] == 0)
            {
                if (i == 0) // 如果按下的是按钮1
                {
                    if (key_count[i] >= long_press_count) // 判断是否长按
                    {
                        return 5; // 长按返回5
                    }
                    else
                    {
                        return i + 1; // 否则按照原逻辑返回1
                    }
                }
                else
                {
                    return i + 1; // 其他按钮按照原逻辑返回对应编号
                }
            }
        }
    }

    return 0; 
}
