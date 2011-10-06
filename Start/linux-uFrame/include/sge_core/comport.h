/*****************************************************************************
	许继电气股份有限公司			版权：2008-2015

	本源代码及其相关文档为河南许昌许继电气股份有限公司独家所有，未经明文许
	可不得擅自修改或发布，否则将追究相关的法律责任。

						河南许昌许继股份有限公司
						www.xjgc.com
						(0374) 321 2924
*****************************************************************************/


/******************************************************************************
	项目名称	：  SGE800计量智能终端平台
	文件		：  comport.h
	描述		：  本文件定义了串口模块接口
	版本		：  0.1
	作者		：  路冉冉
	创建日期	：  2009.09
******************************************************************************/

#ifndef _COMPORT_H
#define _COMPORT_H

#include "typedef.h"
/*************************************************
  宏定义
*************************************************/
//串口端口号
#define COMPORT0				0		//端口0
#define COMPORT1				1		//端口1
#define COMPORT2				2		//端口2
#define COMPORT3				3		//端口3
#define COMPORT4				4		//端口4
#define COMPORT5				5		//端口5
#define COMPORT6				6		//端口6
#define COMPORTUSB				7		//USB转串口端口号

//串口操作模式
#define COMPORT_MODE_NORMAL	0			//正常模式
#define COMPORT_MODE_485		1			//485模式
//校验方式
#define COMPORT_VERIFY_NO		0			//无校验
#define COMPORT_VERIFY_EVEN	1			//偶校验
#define COMPORT_VERIFY_ODD	2			//奇校验
//清缓冲区模式
#define COMPORT_FLUSH_ALL		0			//清读写缓冲区
#define COMPORT_FLUSH_RD		1			//清读缓冲区
#define COMPORT_FLUSH_WR		2			//清写缓冲区
//RTSCTS流控应用模式
#define COMPORT_RTSCTS_DISABLE	0		//不应用
#define COMPORT_RTSCTS_ENABLE		1		//应用



/*************************************************
  结构类型定义
*************************************************/
typedef struct {
	u8		verify;			//校验方式
	u8		ndata;			//数据位位数
	u8		nstop;			//停止位位数
	u8		timeout;		//超时时间（单位100ms，为0时永久阻塞，0xff不阻塞）
	u32		baud;			//波特率
	u8		rtscts;			//是否使用rtscts流控信号线
} comport_config_t;

/*************************************************
  API
*************************************************/
/******************************************************************************
*	函数:	comport_init
*	功能:	打开并初始化串口
*	参数:	port			-	串口端口号
			mode			-	串口操作模式
*	返回:	0				-	成功
			-ESYS			-	错误
			-ERR_INVAL		-	参数错误
			-ERR_BUSY		-	已经打开
*	说明:	无
 ******************************************************************************/
int comport_init (u8 port, u8 mode);


/******************************************************************************
*	函数:	comport_setconfig
*	功能:	配置串口
*	参数:	port			-	串口端口号
			cfg				-	配置项（数据传入）
*	返回:	0				-	成功
			-ESYS			-	系统错误
			-ERR_INVAL		-	参数无效
			-ERR_NOINIT		-	没有初始化
*	说明:	本串口支持的波特率为 50，110，150，300，600，1200，2400，4800，9600
 			115200，460800，4000000
 ******************************************************************************/
int comport_setconfig (u8 port, comport_config_t *cfg);


/******************************************************************************
*	函数:	comport_getconfig
*	功能:	获取串口配置
*	参数:	port			-	串口端口号
			cfg				-	配置项（数据传出）
*	返回:	0				-	成功
			-ERR_INVAL		-	参数无效
			-ERR_NOINIT		-	没有初始化
*	说明:	无
 ******************************************************************************/
int comport_getconfig (u8 port, comport_config_t *cfg);


/******************************************************************************
*	函数:	comport_send
*	功能:	串口发送
*	参数:	port			-	串口端口号
			buf				-	数据缓冲区（数据传入）
			count			-	请求字节数
*	返回:	>=0				-	发送成功的字节数
			-ESYS			-	系统错误
			-ERR_INVAL		-	参数无效
			-ERR_NOINIT		-	没有初始化
*	说明:	无
 ******************************************************************************/
int comport_send (u8 port, u8 *buf, u32 count);


/******************************************************************************
*	函数:	comport_recv
*	功能:	串口接收
*	参数:	port			-	串口端口号
			buf				-	数据缓冲区（数据传出）
			count			-	请求字节数
*	返回:	>=0				-	接收成功的字节数
			-ERR_SYS		-	错误
			-ERR_INVAL		-	参数无效
			-ERR_NOINIT		-	没有初始化
*	说明:	无
 ******************************************************************************/
int comport_recv (u8 port, u8 *buf, u32 count);


/******************************************************************************
*	函数:	comport_flush
*	功能:	清串口缓冲区
*	参数:	port			-	串口端口号
			mode			-	清缓冲区模式
*	返回:	0				-	成功
			-ERR_INVAL		-	参数无效
			-ERR_NOINIT		-	没有初始化
*	说明:	无
 ******************************************************************************/
int comport_flush (u8 port, u8 mode);
	

/******************************************************************************
*	函数:	comport_close
*	功能:	关闭串口
*	参数:	port			-	串口端口号
*	返回:	0				-	成功
			-ERR_SYS		-	错误
			-ERR_INVAL		-	参数无效
			-ERR_NOINIT		-	没有初始化
*	说明:	无
 ******************************************************************************/
int comport_close (u8 port);


#endif                                                                                                     
