/*******************************************************************************
                                包含头文件
*******************************************************************************/
#include "RTT_Nano_Include.h"

/*******************************************************************************
                                全局变量
*******************************************************************************/

/*
***************************************************************************************************
* 函数名: void Scan_Ctrl_RunLight(void)
* 说  明: 运行指示灯控制
* 参  数:
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20181030
* 修  改:
***************************************************************************************************
*/
//void Scan_Ctrl_RunLight(void)
//{
//  switch (SYSTEM_STATE)
//  {
//  case SYS_Power_ON:
//    LED_ON();
//    break;
//  case SYS_IN_STATION:
//    if (Sys_time.Flag.RunLight_SYS_IN_STATION)
//    {
//      Sys_time.Flag.RunLight_SYS_IN_STATION = 0;
//      LED_ROLLOVER();
//    }
//    break;
//  case SYS_RUN_IDLE:
//    if (Sys_time.Flag.RunLight_SYS_RUN_IDLE)
//    {
//      Sys_time.Flag.RunLight_SYS_RUN_IDLE = 0;
//      LED_ROLLOVER();
//    }
//    break;
//  case SYS_RUN:
//    if (Sys_time.Flag.RunLight_SYS_RUN)
//    {
//      Sys_time.Flag.RunLight_SYS_RUN = 0;
//      LED_ROLLOVER();
//    }
//    break;
//  }
//}

void Output_Ctrl_entry(void* parameter)
{
  HAL_TIM_Base_Start(&htim8);
  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, 0); //设置通道1--PWM占空比
  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, 0); //设置通道2--PWM占空比
  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, 0); //设置通道3--PWM占空比
  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, 0); //设置通道4--PWM占空比
  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);        //启动通道3
  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);        //启动通道4
  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);        //启动通道3
  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);        //启动通道4

  HAL_TIM_Base_Start(&htim1);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0); //设置通道1--PWM占空比
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0); //设置通道2--PWM占空比
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0); //设置通道3--PWM占空比
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0); //设置通道4--PWM占空比
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);        //启动通道3
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);        //启动通道4
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);        //启动通道3
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);        //启动通道4
  while (1)
  {
//    LED_ON();
    OUT2_PWMON(200);
    OUT4_PWMON(200);
    OUT6_PWMON(200);
    OUT8_PWMON(200);
    OUT1_OFF();
    OUT3_OFF();
    OUT5_OFF();
    OUT7_OFF();
//    RELAY_ON();
    rt_thread_mdelay(1000);
//    LED_OFF();
    OUT1_PWMON(200);
    OUT3_PWMON(200);
    OUT5_PWMON(200);
    OUT7_PWMON(200);
    OUT2_OFF();
    OUT4_OFF();
    OUT6_OFF();
    OUT8_OFF();
//    RELAY_OFF();
    rt_thread_mdelay(1000);
  }
}

/*************信号量 简易测试**********************/
static rt_sem_t sem1;
void test1_entry(void *parameter)
{
  uint8_t cnt = 0;
  
  while(1)
  {
    if(cnt<= 100)
    {
      cnt++;
    }
    else 
     return;
    if(cnt%10 == 0)
    {
      rt_kprintf("t1 release a dynamic sem!\n");
      rt_sem_release(sem1);
      rt_thread_mdelay(10);
    }
  }
   
}

void test2_entry(void *parameter)
{
  uint8_t num=0;
  while(1)
  {
    if(rt_sem_take(sem1,RT_WAITING_FOREVER) != RT_EOK)
    {
      rt_kprintf("t2 take a dynamic sem failed\n");
      rt_sem_delete(sem1);
      return;
    }
    else
    {
      num++;
      rt_kprintf("t2 take a dynamic sem. num= %d\n",num);
    }
  }  
}

int test_sem_sample(void)
{
    sem1 = rt_sem_create("sem1",0,RT_IPC_FLAG_FIFO);    
    if(sem1 == RT_NULL)
    {
     rt_kprintf("create sem fail!\n");
     return -1;
    }
    else
    {
      rt_kprintf("create a dynamic sem val = 0\n");
    }
    
     rt_thread_t test1_tid = rt_thread_create("test1_thread",
                                            test1_entry,
                                            RT_NULL,
                                            512,
                                            15,
                                            10);
    if(test1_tid != RT_NULL) {rt_thread_startup(test1_tid);}    
   rt_thread_t test2_tid = rt_thread_create("test2_thread",
                                            test2_entry,
                                            RT_NULL,
                                            512,
                                            13,
                                            10);
    if(test2_tid != RT_NULL) {rt_thread_startup(test2_tid);}  
    
return 0;
}

MSH_CMD_EXPORT(test_sem_sample,test_sem_sample);



/*************信号量 生产者消费者问题*****************************/
rt_sem_t sem_lock,sem_empty,sem_full;
#define MAXSEM 5
rt_uint32_t array[MAXSEM];
static rt_uint32_t set,get;
void producer_thread_entry(void * parameter)
{
  int cnt = 0;
  while(cnt < 10)
  {
    rt_sem_take(sem_empty,RT_WAITING_FOREVER);
    rt_sem_take(sem_lock,RT_WAITING_FOREVER);
    array[set%MAXSEM] = cnt+1;
    rt_kprintf("the procucer generates a num:%d\n",array[set%MAXSEM]);
    set++;
    rt_sem_release(sem_lock);
    rt_sem_release(sem_full);
    cnt++;
    rt_thread_mdelay(10);
  }
  rt_kprintf("the producer is exit\n");
  
}

void comsumer_thread_entry(void * parameter)
{
  rt_uint32_t sum = 0;

  while(1)
  {
    rt_sem_take(sem_full,RT_WAITING_FOREVER);
    rt_sem_take(sem_lock,RT_WAITING_FOREVER);
    sum += array[get%MAXSEM];
    rt_kprintf("the consumer [%d] get a num : %d\n",(get%MAXSEM),array[get%MAXSEM]);
    get++;
    rt_sem_release(sem_lock);
    rt_sem_release(sem_empty);
    
    if(get==10)break;
    rt_thread_mdelay(10);
  }
  rt_kprintf("the consumer sum is %d\n",sum);
  rt_kprintf("the comsumer exit\n");
  
}
int producer_consumer(void)
{
    set = 0;
    get = 0;
    sem_lock  = rt_sem_create("sem_lock", 1,      RT_IPC_FLAG_FIFO);    
    sem_empty = rt_sem_create("sem_empty",MAXSEM, RT_IPC_FLAG_FIFO);    
    sem_full  = rt_sem_create("sem_full", 0,      RT_IPC_FLAG_FIFO);    
    
     rt_thread_t producer_tid = rt_thread_create("producer_thread",
                                            producer_thread_entry,
                                            RT_NULL,
                                            512,
                                            7,
                                            10);
    if(producer_tid != RT_NULL) {rt_thread_startup(producer_tid);}    
   rt_thread_t comsumer_tid = rt_thread_create("comsumer_thread",
                                            comsumer_thread_entry,
                                            RT_NULL,
                                            512,
                                            6,
                                            10);
    if(comsumer_tid != RT_NULL) {rt_thread_startup(comsumer_tid);}  
    
return 0;
}
MSH_CMD_EXPORT(producer_consumer,producer_consumer);

/*************事件集********************/
rt_event_t event;
#define EVENT_FLAG3 1<<3
#define EVENT_FLAG5 1<<5

void thread1_recv_event(void *para)
{
  rt_uint32_t e;
  if(rt_event_recv(event,(EVENT_FLAG3 | EVENT_FLAG5),
                   RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,
                   RT_WAITING_FOREVER,&e) == RT_EOK)
  {
    rt_kprintf("thread1:OR recv event 0x%x\n",e);
  }
  rt_kprintf("thread1: delay 1s to prepare the second evnet\n");
  rt_thread_mdelay(1000);
  
  if(rt_event_recv(event,(EVENT_FLAG3 | EVENT_FLAG5),
                   RT_EVENT_FLAG_AND|RT_EVENT_FLAG_CLEAR,
                   RT_WAITING_FOREVER,&e) == RT_EOK)
  {
    rt_kprintf("thread1:AND recv event 0x%x\n",e);
  }
  rt_kprintf("thread1 leave\n");
}

void thread2_send_event(void *para)
{
  rt_kprintf("thread2 send event3\n");
  rt_event_send(event,EVENT_FLAG3);
  rt_thread_mdelay(100);
  
  
  rt_kprintf("thread2 send event5\n");
  rt_event_send(event,EVENT_FLAG5);
  rt_thread_mdelay(100);
  
  
  rt_kprintf("thread2 send event3\n");
  rt_event_send(event,EVENT_FLAG3);
  rt_kprintf("thread2 leave\n");

}
int event_test_sample(void)
{
  event = rt_event_create("event",RT_IPC_FLAG_FIFO);
  
  rt_thread_t tid1 = rt_thread_create("thread1",
                                      thread1_recv_event,
                                      RT_NULL,
                                      512,
                                      7,
                                      10);
  if(tid1 != RT_NULL){rt_thread_startup(tid1);}
  rt_thread_t tid2 = rt_thread_create("thread2",
                                     thread2_send_event,
                                     RT_NULL,
                                     512,
                                     9,
                                     10);
  if(tid2 != RT_NULL){rt_thread_startup(tid2);}
  return 0;
}

MSH_CMD_EXPORT(event_test_sample,event_test_sample);

/*************消息队列**********************/
rt_mq_t mq;

static uint8_t state = 0;
uint8_t buff[20];
uint8_t flag = 0;
uint32_t count = 0;
void thread1_recv_mq(void *para)
{
  
  uint8_t recv = 0;
  rt_uint32_t cnt = 0;
  while(1)
  {
    if(rt_mq_recv(uart5_mq,&recv,1,100) == RT_EOK)//RT_WAITING_FOREVER
    {

      switch(state)
      {
        case 0:
            state = 1;
            buff[0] = recv;
        break;
        case 1:
            state = 2;
            buff[1] = recv;
        break;
        case 2:
            state = 3;
            buff[2] = recv;
        break;
        case 3:
            buff[3] = recv;
            state = 4;
        break;
        case 4:
            buff[4] = recv;
            flag = 1;
            state = 0;
        break;
      default:state = 0;
      }
      if(flag)
      {
        if(buff[4] == Computed_Checksum(buff,4))
        {
          if(buff[0] == 0xaa)
          {
            if(buff[1] == 0x55)
            {
              if(buff[2] == 0x05)
              {
                if(buff[3]==0x01)
                {
                  RELAY_ON();
                  cnt+=5;
                  rt_kprintf("count=%d\n",cnt);
                }
                else if(buff[3]==0x02)
                {
                  RELAY_OFF();
                  cnt+=5;
                  rt_kprintf("count=%d\n",cnt);
                }
              }
            }
          }
        }
         flag = 0;
      }
    }
    else
    {
      flag = 0;
      state = 0;
    }
  }
  rt_kprintf("thread1 delete mq\n");
  rt_mq_delete(mq);
}

void thread2_send_mq(void *para)
{
  uint8_t dat1[4]  = {0xaa,0x55, 0x05, 0x01};
  uint8_t dat2[4]  = {0xaa, 0x55, 0x05, 0x02};
  rt_uint8_t cnt = 0;
  while(1)
  {
//    if(cnt == 3)
//    {
//      if(rt_mq_urgent(mq,dat,sizeof(dat)) == RT_EOK)
//      {
//        for(rt_uint8_t i=0;i<sizeof(dat);i++)
//        {
//          rt_kprintf("thread2: send urgent message - %d\n",dat[i]);
//        }     
//      }
//    }
//    else if(cnt >= 10)
//    if(cnt >= 2)
//    {
//      rt_kprintf("message queue stop send,thread2 quit!\n");
//      break;
//    }
//    else
//    {
      if(cnt%2)
      {  
      if(rt_mq_send(mq,dat1,sizeof(dat1)) == RT_EOK)
      {
//        for(rt_uint8_t i=0;i<sizeof(dat);i++)
//        {
          //rt_kprintf("thread2: send message - %d\n",dat[i]);
//        } 
        rt_kprintf("thread2: send message data1\n");
      }
      }
      else
      {
            if(rt_mq_send(mq,dat2,sizeof(dat2)) == RT_EOK)
      {
//        for(rt_uint8_t i=0;i<sizeof(dat);i++)
//        {
          //rt_kprintf("thread2: send message - %d\n",dat[i]);
//        } 
        rt_kprintf("thread2: send message data2\n");
      }
      }
//    }
    cnt++;
    rt_thread_mdelay(1000);
  }
}
int mq_test_sample(void)
{
  mq = rt_mq_create("mq",15,4,RT_IPC_FLAG_FIFO);
  
  rt_thread_t tid1 = rt_thread_create("thread1",
                                      thread1_recv_mq,
                                      RT_NULL,
                                      512,
                                      7,
                                      10);
  if(tid1 != RT_NULL){rt_thread_startup(tid1);}
  rt_thread_t tid2 = rt_thread_create("thread2",
                                     thread2_send_mq,
                                     RT_NULL,
                                     512,
                                     9,
                                     10);
  if(tid2 != RT_NULL){rt_thread_startup(tid2);}
  return 0;
}
INIT_APP_EXPORT(mq_test_sample);
MSH_CMD_EXPORT(mq_test_sample,mq_test_sample);