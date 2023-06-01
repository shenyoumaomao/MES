#ifndef __INTERFACE_H_
#define __INTERFACE_H_

#include <Arduino.h>
//IO 接口定义

//用户LED
int USER_PIN = 11;
#define LED_ON digitalWrite(USER_PIN , LOW)
#define LED_OFF digitalWrite(USER_PIN , HIGH)
//用户KEY
//int KEY_L = 12;
//int KEY_H = 13;
#define KEY_L_BIT digitalRead(KEY_L)
#define KEY_H_BIT digitalRead(KEY_H)

#define KEY_L_DOWN 0
#define KEY_H_DOWN 1
//蓝牙
//int Rx = 0;
//int Tx= 1;

//红外遥控
int IRIN = 2;

//超声波模块
int Echo = 17;  //A3
int Trig = 16; //A2

//电机驱动


//红外循迹
int SEARCH_M_IO = 16;//中间循迹IO
int SEARCH_R_IO = 15;//右循迹IO
int SEARCH_L_IO = 14;//左循迹IO
#define BLACK_AREA 1
#define WHITE_AREA 0
#define SEARCH_M_BIT digitalRead(SEARCH_M_IO)
#define SEARCH_R_BIT digitalRead(SEARCH_R_IO)
#define SEARCH_L_BIT digitalRead(SEARCH_L_IO)

//循迹避障
int VOID_R_PIN = 19;
int VOID_L_PIN = 18;
#define VOID_R_BIT digitalRead(VOID_R_PIN)
#define VOID_L_BIT digitalRead(VOID_L_PIN)
#define BARRIER_Y 0 //有障碍物
#define BARRIER_N 1  //无障碍物

//舵机IO
int DUOJI_IO = 9; //左右转
int DUOJI_IO2=10; //上下动
//速度码盘反馈
int FRONT_RIGHT_S_IO =  13; //右前前进IO
int FRONT_LEFT_S_IO =  12; //左前前进IO
#define FRONT_RIGHT_S_BIT digitalRead(FRONT_RIGHT_S_IO)
#define FRONT_LEFT_S_BIT digitalRead(FRONT_LEFT_S_IO)

//电机运动控制



#define SPEED_DUTY 40//默认占空比 按1ms最小分辨率 周期50ms计算 40 /50  80%

//指令定义
//#define COMM_STOP  0x02//停止
//#define COMM_UP    0x62//前进
//#define COMM_DOWN  0xA8//后退
//#define COMM_RIGHT 0xC2//右转
//#define COMM_LEFT  0x22//左转

#define COMM_STOP  'I'//停止
#define COMM_UP    'A'//前进
#define COMM_DOWN  'B'//后退
#define COMM_RIGHT 'D'//右转
#define COMM_LEFT  'C'//左转

#endif



