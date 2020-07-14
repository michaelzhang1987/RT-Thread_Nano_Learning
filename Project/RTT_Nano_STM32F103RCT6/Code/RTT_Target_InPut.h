#ifndef __Rail_Car_Master_InPut_H
#define __Rail_Car_Master_InPut_H



#define    Key1_LEV         HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5)  //按键1
#define    Key2_LEV         HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)  //按键2
#define    Key3_LEV         HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)  //按键3
#define    Key4_LEV         HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_4)  //按键4
#define    Key5_LEV         HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5)  //按键5
#define    Key6_LEV         HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)  //按键6


#define  ADDRESS_DIAL_1    HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)  //拨码开关1
#define  ADDRESS_DIAL_2    HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_15)  //拨码开关2
#define  ADDRESS_DIAL_3    HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_14)  //拨码开关3
#define  ADDRESS_DIAL_4    HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_0)   //拨码开关4
#define  ADDRESS_DIAL_5    HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)   //拨码开关5
#define  ADDRESS_DIAL_6    HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1)   //拨码开关6
#define  ADDRESS_DIAL_7    HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)   //拨码开关7
#define  ADDRESS_DIAL_8    HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_3)   //拨码开关8


//*****************按键状态机结构体****************//
typedef struct
{
    volatile unsigned char FilterCounter;    // 滤波计数器
    union
    {
        volatile unsigned char Byte;
        struct
        {
            unsigned char Filter      :1;   // 滤波标志
            unsigned char Valid       :1;   // 开关动作有效标志
            unsigned char Event       :1;   // 事件
        };
    }Flag;

}SWITCH_INPUT;

//******************声明外部变量******************//
extern SWITCH_INPUT Key1,Key2,Key3,Key4,Key5,Key6;

//********************函数原型********************//

void Scan_InPut(void);
void Init_InPut_Struct(void);
unsigned char READ_DIAL_ADDRESS(void);
#endif //Battery_Car_InPut.h