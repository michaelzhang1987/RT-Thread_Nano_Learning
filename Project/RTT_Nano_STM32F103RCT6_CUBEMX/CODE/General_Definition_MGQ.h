#ifndef __General_Definition_MGQ_H
#define __General_Definition_MGQ_H

/**********************用于IO输入*********************************/
//有效电平
#define    Valid_LEV_L      GPIO_PIN_RESET
#define    Valid_LEV_H      GPIO_PIN_SET
//滤波时间基于10ms定时
#define    Filter_20ms_Time 0xD0
#define    Filter_30ms_Time 0xE0
#define    Filter_40ms_Time 0xF0
#define    Filter_50ms_Time 0x08
#define    Filter_60ms_Time 0x04
#define    Filter_70ms_Time 0x02
#define    Filter_80ms_Time 0x01

#endif  //General_Definition_MGQ.h