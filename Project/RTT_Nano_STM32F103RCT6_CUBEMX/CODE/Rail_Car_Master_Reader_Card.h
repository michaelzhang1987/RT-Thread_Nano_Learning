#ifndef __Rail_Car_Master_Reader_Card_H
#define __Rail_Car_Master_Reader_Card_H

#define  Reader_Card_UART               huart5
#define  ReaderCardID_AndUploading      1 //读卡号并上传
#define  ReaderCardBlock_AndUploading   2 //读块号并上传

//*****************结构体*******************************//
typedef struct
{
  unsigned char Real_time_CARD_ID[4];    //实时卡号
  unsigned char Binding_CARD_ID[4];      //绑定卡号
  unsigned char Block_Data[16];          //块数据

  union
  {
    volatile unsigned char Byte;
    struct
    {
      unsigned char slot_card      :1;   // 刷卡标志
      unsigned char Block_Card     :1;   // 读块标志
      unsigned char Need_InitMod   :1;   // 需要初始化
      unsigned char Enable         :1;   // 使能读卡器
    };
  }Flag;

  union
  {
    volatile unsigned char Byte;
    struct
    {
      unsigned char COMM_OK       :1;   // 读卡器通信正常
    };
  }Err;
}Reader_Card_Struct;

//******************声明外部变量************************//
extern MGQ_UART Reader_Card_UART_Ctrl;
extern Reader_Card_Struct Reader_Card_Ctrl;

//*****************函数原型****************************//
void Set_Reader_Card_Work_Pattern(unsigned char mode,unsigned char Mode_Data);
void SetTheReaderSensitivity(unsigned char data);
void Init_Reader_Card_Struct(void);
void Reader_Card_COMM_Dispose(unsigned char data);
unsigned char ComputedCheckSum(unsigned char *pBuffer,unsigned char lenght);
void SetTheReaderOnlyONE(void);
void SetTheReaderONEbyONE(void);
void Read_Reader_Word_MODE(void);
void Init_Reader_Word_MODE(void);
void SetTheReaderBaudRate(uint8_t baud);
#endif  //Battery_Car_Reader_Card.h