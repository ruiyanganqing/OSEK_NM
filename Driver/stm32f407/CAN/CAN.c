#include "CAN.h"
#include "stm32f4xx.h"
/*初始化CAN1模块*/
void STM32_CAN1_Init(void)
{
    CAN_InitTypeDef CAN_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	  GPIO_InitTypeDef GPIO_InitStructure;
	  
	  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
  	/*1.使能CAN1时钟*/
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);  ///使能CAN1时钟
	 /*2.配置GPIO*/
	 /*2.1 使能GPIO时钟*/
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能PORTA时钟	
	 /*2.2 选择GPIO引脚*/
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_12;
	 /*2.3 配置GPIO为复用*/
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	 /*2.4 配置GPIO为推挽输出*/
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	 /*2.5 配置GPIO速率*/
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;//25MHz
	 /*2.6 使能上拉*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化PA11,PA12
	//引脚复用映射配置                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
	  GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_CAN1); //GPIOA11复用为CAN1
	  GPIO_PinAFConfig(GPIOA,GPIO_PinSource12,GPIO_AF_CAN1); //GPIOA12复用为CAN1
	 /*3.配置CAN控制器*/
	  CAN_InitStructure.CAN_TTCM=DISABLE;	//非时间触发通信模式   
  	CAN_InitStructure.CAN_ABOM=ENABLE;	//硬件自动离线管理	  
  	CAN_InitStructure.CAN_AWUM=ENABLE;  //睡眠模式通过硬件唤醒(清除CAN->MCR的SLEEP位)
  	CAN_InitStructure.CAN_NART=ENABLE;	//禁止报文自动传送 
  	CAN_InitStructure.CAN_RFLM=DISABLE;	//报文不锁定,新的覆盖旧的  
  	CAN_InitStructure.CAN_TXFP=DISABLE;	//优先级由报文标识符决定 
  	CAN_InitStructure.CAN_Mode= CAN_Mode_Normal;//CAN_Mode_LoopBack;//CAN_Mode_Normal;	 //模式设置-环回模式 
		/*初始化为500K的波特率*/
  	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;	//重新同步跳跃宽度(Tsjw)为tsjw+1个时间单位 CAN_SJW_1tq~CAN_SJW_4tq
  	CAN_InitStructure.CAN_BS1=CAN_BS1_7tq;  //Tbs1范围CAN_BS1_1tq ~CAN_BS1_16tq
  	CAN_InitStructure.CAN_BS2=CAN_BS2_6tq;  //Tbs2范围CAN_BS2_1tq ~	CAN_BS2_8tq
  	CAN_InitStructure.CAN_Prescaler=6;      //分频系数(Fdiv)为brp+1	
  	CAN_Init(CAN1, &CAN_InitStructure);     // 初始化CAN1 
    
		//配置过滤器
 	  CAN_FilterInitStructure.CAN_FilterNumber=0;	  //过滤器0
  	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 
  	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; //32位 
  	CAN_FilterInitStructure.CAN_FilterIdHigh=0x18FF; //32位ID
  	CAN_FilterInitStructure.CAN_FilterIdLow=0xA000;
  	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//32位MASK
  	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
   	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;//过滤器0关联到FIFO0
  	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //激活过滤器0
  	CAN_FilterInit(&CAN_FilterInitStructure);//滤波器初始化
	 /*4.使能中断*/
	  CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);//FIFO0消息挂号中断允许.		    
  	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     // 主优先级为1
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // 次优先级为0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
		
}
/*发送报文到总线
* 成功：返回 1
*/
int STM32_TX_CAN_Transmit(NMPDU_t* NMPDU)
{
  NMTypeU8_t mbox;  //报文放入的邮箱号
  int i=0;
  CanTxMsg TxMessage;
  //TxMessage.StdId=0x12;	 // 标准标识符为0
  TxMessage.ExtId = NMPDU->MsgID;	 // 设置扩展标示符（29位）
  TxMessage.IDE = CAN_ID_EXT;		  // 使用扩展标识符
  TxMessage.RTR = 0;		  // 消息类型为数据帧，一帧8位
  TxMessage.DLC = OSEKNM_DLC;  
	TxMessage.Data[0] = NMPDU->MsgDA;
	TxMessage.Data[1] = NMPDU->MsgCtl;
  for(i=2;i<OSEKNM_DLC;i++)
    TxMessage.Data[i]=NMPDU->MsgData[i-2];				 // 第一帧信息          
  mbox = CAN_Transmit(CAN1, &TxMessage);   
  i=0;
  while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))
		i++;	//等待发送结束
  if(i >= 0XFFF)
		return 0;
  return 1;
}

//中断服务函数			    
void CAN1_RX0_IRQHandler(void)
{
  CanRxMsg RxMessage;
	NMPDU_t NMPDU;
	int i=0;
	static unsigned int j = 0;
	j++;
  CAN_Receive(CAN1, 0, &RxMessage);
	/*初始化NMPDU*/
	NMPDU.MsgCtl = RxMessage.Data[1];
	NMPDU.MsgDA = RxMessage.Data[0];
	NMPDU.MsgID = RxMessage.ExtId;
	for(i=2;i<8;i++)
	{
	    NMPDU.MsgData[i-2] = RxMessage.Data[i];
	}
	//将报文放入缓冲区
	Recv_EveryMessage(&NMPDU);
	/*LED0灯光闪*/
	GPIO_WriteBit(GPIOE,GPIO_Pin_3,(j%2)?Bit_SET:Bit_RESET);//GPIOE3
	//GPIO_ResetBits(GPIOE,GPIO_Pin_3);
	//printf("NMID:%lx D0:%x D1:%x\n",NMPDU.MsgID,NMPDU.MsgDA,NMPDU.MsgCtl);
}
