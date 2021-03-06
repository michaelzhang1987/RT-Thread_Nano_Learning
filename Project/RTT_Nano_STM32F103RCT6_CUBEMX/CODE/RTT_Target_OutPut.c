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
                  rt_kprintf("uart5count=%d\n",cnt);
                }
                else if(buff[3]==0x02)
                {
                  RELAY_OFF();
                  cnt+=5;
                  rt_kprintf("uart5count=%d\n",cnt);
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

#define LED_PIN_NUM 15    /*PA15*/
#define RELAY_PIN_NUM 12  /*PA12*/

void thread_drv_pin(void *para)
{
   while(1)
  {
    rt_pin_write(LED_PIN_NUM,PIN_HIGH);
//    rt_pin_write(RELAY_PIN_NUM,PIN_LOW);
    rt_kprintf("LED ON\r\n");
    rt_thread_mdelay(500);
    rt_pin_write(LED_PIN_NUM,PIN_LOW);
//    rt_pin_write(RELAY_PIN_NUM,PIN_HIGH);
    rt_kprintf("LED OFF\r\n");
    rt_thread_mdelay(500);
  }
}

//学到一招  系统中这种临时shell中执行的函数不能有死循环出现

int Drv_Pin_Test_Sample(void)
{
  rt_pin_mode(LED_PIN_NUM,PIN_MODE_OUTPUT);
  rt_pin_mode(RELAY_PIN_NUM,PIN_MODE_OUTPUT);
  rt_pin_write(LED_PIN_NUM,PIN_LOW);
  rt_pin_write(RELAY_PIN_NUM,PIN_HIGH);
  rt_thread_t tid_pin = rt_thread_create("thread_drv_pin",
                              thread_drv_pin,
                              RT_NULL,
                              512,
                              3,
                              10);
  if(tid_pin != RT_NULL){rt_thread_startup(tid_pin);}
  return 0;
}
MSH_CMD_EXPORT(Drv_Pin_Test_Sample,Drv_Pin_Test_Sample);

#define PWM_DEV_NAME           "pwm8"  /* PWM设备名称 */
#define PWM_DEV_CHANNEL         2       /* PWM通道 */
#define THREAD_PRIORITY         25      /* 线程优先级 */
#define THREAD_STACK_SIZE       512     /* 线程栈大小 */
#define THREAD_TIMESLICE        5       /* 线程时间片大小 */

static rt_thread_t tid1 = RT_NULL;      /* 线程句柄 */
struct rt_device_pwm *pwm_dev;          /* PWM设备句柄 */
static rt_uint32_t period = 500000;     /* 周期为0.5ms，单位为纳秒ns */
static rt_uint32_t pulse = 0;           /* PWM脉冲宽度值的增减方向 */
static rt_uint32_t dir = 1;             /* PWM脉冲宽度值，单位为纳秒ns */


/* 线程 pwm_entry 的入口函数 */
static void pwm_entry(void *parameter)
{
     while (1)
    {
        rt_thread_mdelay(50);
        if (dir)
        {
            pulse += 10000;      /* 从0值开始每次增加5000ns */
        }
        else
        {
            pulse -= 10000;      /* 从最大值开始每次减少5000ns */
        }
        if (pulse >= period)
        {
            dir = 0;
        }
        if (0 == pulse)
        {
            dir = 1;
        }
 
        /* 设置PWM周期和脉冲宽度 */
        rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
    }
}

static int pwm_test(int argc, char *argv[])
{
    /* step 1.1、查找 PWM 设备 */
    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME);
        return RT_ERROR;
    }

    /* step 1.2、设置 PWM 周期和脉冲宽度默认值 */
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
    /* step 1.3、使能 PWM 设备的输出通道 */
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);

    /* 创建线程，名称是 pwm_thread ，入口是 pwm_entry*/
    tid1 = rt_thread_create("pwm_thread",
                             pwm_entry,
                             RT_NULL,
                             THREAD_STACK_SIZE,
                             THREAD_PRIORITY,
                            THREAD_TIMESLICE);

    /* 如果获得线程控制块，启动这个线程 */
    if (tid1 != RT_NULL)rt_thread_startup(tid1);

    return RT_EOK;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(pwm_test, pwm sample);

/*
 * 程序清单：这是一个串口设备接收不定长数据的示例代码
 * 例程导出了 uart_dma_sample 命令到控制终端
 * 命令调用格式：uart_dma_sample uart2
 * 命令解释：命令第二个参数是要使用的串口设备名称，为空则使用默认的串口设备
 * 程序功能：通过串口 uart2 输出字符串"hello RT-Thread!"，并通过串口 uart2 输入一串字符（不定长），再通过数据解析后，使用控制台显示有效数据。
*/

#include <rtthread.h>

#define SAMPLE_UART_NAME                 "uart4"
#define DATA_CMD_END                     '\r'       /* 结束位设置为 \r，即回车符 */
#define ONE_DATA_MAXLEN                  20         /* 不定长数据的最大长度 */

/* 用于接收消息的信号量 */
static struct rt_semaphore rx_sem;
static rt_device_t serial;

/* 接收数据回调函数 */
static rt_err_t uart_rx_ind(rt_device_t dev, rt_size_t size)
{
    /* 串口接收到数据后产生中断，调用此回调函数，然后发送接收信号量 */
    if (size > 0)
    {
        rt_sem_release(&rx_sem);
    }
    return RT_EOK;
}

static char uart_sample_get_char(void)
{
    char ch;

    while (rt_device_read(serial, 0, &ch, 1) == 0)
    {
        rt_sem_control(&rx_sem, RT_IPC_CMD_RESET, RT_NULL);
        rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
    }
    return ch;
}

/* 数据解析线程 */
static void data_parsing(void)
{
    char ch;
    char data[ONE_DATA_MAXLEN];
    static char i = 0;

    while (1)
    {
        ch = uart_sample_get_char();
        rt_device_write(serial, 0, &ch, 1);
        if(ch == DATA_CMD_END)
        {
            data[i++] = '\0';
            rt_kprintf("data=%s\r\n",data);
            i = 0;
            continue;
        }
        i = (i >= ONE_DATA_MAXLEN-1) ? ONE_DATA_MAXLEN-1 : i;
        data[i++] = ch;
    }
}

static int uart_data_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    char uart_name[RT_NAME_MAX];
    char str[] = "hello RT-Thread!\r\n";

    if (argc == 2)
    {
        rt_strncpy(uart_name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(uart_name, SAMPLE_UART_NAME, RT_NAME_MAX);
    }

    /* 查找系统中的串口设备 */
    serial = rt_device_find(uart_name);
    if (!serial)
    {
        rt_kprintf("find %s failed!\n", uart_name);
        return RT_ERROR;
    }

    /* 初始化信号量 */
    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
    /* 以中断接收及轮询发送模式打开串口设备 */
    rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);
    /* 设置接收回调函数 */
    rt_device_set_rx_indicate(serial, uart_rx_ind);
    /* 发送字符串 */
    rt_device_write(serial, 0, str, (sizeof(str) - 1));

    /* 创建 serial 线程 */
    rt_thread_t thread = rt_thread_create("serial", (void (*)(void *parameter))data_parsing, RT_NULL, 1024, 25, 10);
    /* 创建成功则启动线程 */
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        ret = RT_ERROR;
    }

    return ret;
}

/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(uart_data_sample, uart device sample);