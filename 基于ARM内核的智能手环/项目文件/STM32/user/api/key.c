#include "key.h"
#define check_count 5

void KEY_Config()
{
	//KEY1 --paPA0
	//KEY2 --paPC5
	//KEY3 --paPC6
  //��������
	//step1.��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOA,ENABLE);
	
	//step2.����IO��ģʽ
	GPIO_InitTypeDef	GPIO_InitSTRUCT;
	GPIO_InitSTRUCT.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitSTRUCT.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitSTRUCT.GPIO_Speed = GPIO_Speed_50MHz;
	
	//step3.��ʼ��IO��
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

    // ��ⰴ��״̬�仯
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
					if(key_count >=(u8 *) check_count)
					{
            key_status[i] = key_press[i];
						key_count[i] =0;
					}
               
            if (key_press[i] == 0)
            {
                return i + 1; 
            }
        }
    }

    return 0; 
}
