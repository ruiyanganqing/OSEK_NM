基于OsekNM 2.5.3协议实现的OsekNM，跨平台的结构，目前只实现了STM32F407ZGT6平台的驱动。
1. 目录结构
1.1 App目录是一个keil5工程，App/keil/Objects/OsekNM.hex是一个可以直接在STM32F407ZGT6平台运    行的hex文件。
1.2 Driver目录包含了stm32f407子目录和Win7子目录，stm32f407目录下就是实现的STM32F407ZGT6平台的底层驱动，包括定时器和CAN模块的驱动，以及Stm32标准库的东西；Win7子目录是在windows7平台下执行的一些文件；Driver_Common.c是一些公用的驱动，由OsekNM_core统一调用。

1.3 OsekNM_core实现了OsekNM 2.5.3协议的核心逻辑，OsekNM.c实现了对各个节点各状态的处理，OsekNMServer.c实现了OsekNM 2.5.3协议提供给应用程序的API。

2. 移植
2.1 在Driver目录新建文件夹，保存新平台的驱动程序，新的平台下需要实现CAN模块和定时器及中断的驱动程序。
2.2 修改Driver_Common.c文件，修改TX_CAN_Transmit()函数，调用新平台发送CAN报文的CAN模块驱动程序，修改InitPlatform()函数，调用新平台初始化CAN模块和定时器的函数；Recv_EveryMessage()被CAN接受报文中断服务函数调用。
2.3 修改Driver_Common.h文件，#define 新的平台，并包含驱动相关的头文件，#define NMID 新的网络管理报文ID，#define ADDR_SELF 新的节点源地址。
2.4 可以参考stm32f407的例子来实现自己平台的移植。

3. 附注
整个代码移植到我的开发板，并且在CANoe平台验证过。
专门在Vspy平台实现了虚拟的网络管理节点，需要的朋友可以联系。
如果在移植过程遇到问题，可以联系我。
微信：ys18908109394
qq: 1175818152