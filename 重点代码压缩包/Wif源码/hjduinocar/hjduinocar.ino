//硬件平台：基于慧净电子R3-L293D/298P驱动板智能小车
//电机接线：左电机接口为驱动板的M1，右电机为M2（写入本程序后再调整全部电机转动方向为前进状态即可）
//左电机：M1由数字引脚5控制PWM调速，7控制电机正反转（高电平前进，低电平后退）
//右电机：M2由数字引脚6控制PWM调速，4控制电机正反转（高电平前进，低电平后退）
//红外传感器接线：左循迹传感器接AO，右循迹传感器接A1；左避障传感器接A4,右避障传感器接A5
//超声波接线：驱动板URF，vcc接VCC,Trig接A2，Echo接A3，GND接GND
//红外接收模块：数字引脚2
//舵机：数字引脚9和10，接线注意正负极，橙色-信号，红色-VCC正，褐色-GND负。
//wifi接线：wifi供电线为XH2.54插头，插入驱动板对应白色5V供电座子，信号线接入驱动板TTL排针接口，注意线序，黑线为GND，其余两根按顺序接；（注意wifi和蓝牙无法共用）
//实验结果：本实验利用安卓手机APP或PC端上位机软件控制小车前进、后退、左转、右转四个方向运行和摄像头云台转动。

#include<Servo.h>  //舵机控制函数
#include "MsTimer2.h" //中断处理函数
#include "interface.h" //接口文件定义函数 

int buffer[3];  //存储指令 将外设送来的数据暂时存放 控制电机0 1 2 3 4指令 ，控制舵机0-180转角指令
int i; //变量函数i

//变量定义
int timer_count;
unsigned int speed_count;//占空比计数器 50次一周期
char front_left_speed_duty;      
char front_right_speed_duty;
char behind_left_speed_duty;
char behind_right_speed_duty;
unsigned int tick_5ms = 0;//5ms计数器，作为主函数的基本周期
unsigned int tick_1ms = 0;//1ms计数器，作为电机的基本计数器
unsigned int tick_500ms = 0;
unsigned int tick_3s = 0;//3s定时器，作为心跳包发送周期
unsigned int switch_flag = 0;

int ctrl_comm;//控制指令
unsigned int continue_time = 0;
int rec_flag=0;
unsigned char serial_data=0;
long int Costtime=0;//串口指令接收时间标志位
Servo myservo;   //定义舵机2变量名  接9脚
Servo myservo2; //定义舵机1变量名   接10脚

//函数声明
void goAhead();
void goBack();
void Left();
void Right();
void stop();
void  communication_decode();
void get_uartdate();
void UartTimeoutCheck();

#if 1

void goAhead() //前进函数，修改5和6两个引脚的PWM值，可以改变电机速度，最小为0，最大为255，一般设定为100-150之间
{
  analogWrite(5,150);
  digitalWrite(7,HIGH);
  analogWrite(6,150);
  digitalWrite(4,HIGH);
}

void goBack() //后退函数，修改5和6两个引脚的PWM值，可以改变电机速度，最小为0，最大为255，一般设定为100-150之间
{
  analogWrite(5,150);
  digitalWrite(7,LOW);
  analogWrite(6,150);
  digitalWrite(4,LOW);
}

void Left() //左转函数，修改5和6两个引脚的PWM值，可以改变电机速度，最小为0，最大为255，一般设定为100-150之间
{
  analogWrite(5,0);
  digitalWrite(7,HIGH);
  analogWrite(6,150);
  digitalWrite(4,HIGH);
}

void Right() //右转函数，修改5和6两个引脚的PWM值，可以改变电机速度，最小为0，最大为255，一般设定为100-150之间
{
  analogWrite(5,150);
  digitalWrite(7,HIGH);
  analogWrite(6,0);
  digitalWrite(4,HIGH);
}

void stop() //停止函数，修改5和6两个引脚的PWM值为0类似于直接赋值低电平
{
  analogWrite(5,0);
  digitalWrite(7,HIGH);
  analogWrite(6,0);
  digitalWrite(4,HIGH);
}

#endif

void IOInit()
{
  //用户LED
  pinMode(USER_PIN, OUTPUT);
  //舵机
  pinMode(DUOJI_IO, OUTPUT);   //定义舵机2接口
  pinMode(DUOJI_IO2, OUTPUT);  //定义舵机1接口
  pinMode(7, OUTPUT); //定义数字引脚7为左电机方向控制脚
  pinMode(4, OUTPUT); //定义数字引脚4为右电机方向控制脚

}

//中断处理函数
void flash()
{
  speed_count++;
  if (speed_count >= 50) //50ms周期 
  {
    speed_count = 0;
  }

}
//解析指令
 void  communication_decode()
 {  
  //执行部分
       if(buffer[0]== 0)
      {
               //类型位0X00，表明是控制数据包，进入控制数据case
               switch(buffer[1])  //根据数据位的值来进行选择执行不同的动作
                           {
                             case 0: stop();break; //执行停止函数  
                             case 1: goAhead(); break; //执行前进函数  
                             case 2: goBack();break; //执行后退函数  
                             case 3: Left();break; //执行左转函数  
                             case 4: Right();break; //执行右转函数  
      	                     default :  break;
                           }
      } 
    if(buffer[0] == 1)  
     {
        switch(buffer[1])
          {
              case 1: myservo2.write(buffer[2]); break;     // 输入对应的角度值,舵机1控制上下舵机会转到此位置;
              case 2: myservo.write(buffer[2]);  break;    // 输入对应的角度值, 舵机2控制左右会转到此位置       
              default :  break;
           }
           delay(100);//延时100ms
     }  
}
 
//串口接收指令
void get_uartdate()
{
     if(Serial.available() > 0) 
 {     
        serial_data=Serial.read();
       if(rec_flag==0)
       {
        if(serial_data==0xff)
        {   
                 rec_flag=1;
                 i=0;
                 Costtime=0; 
        }
     }
     else
    {
        if(serial_data==0xff)
       {
         rec_flag=0;
        if(i==3)
        {
              communication_decode();          //解析指令 
              i=0;  
        }
       }   
        else 
      {
         buffer[i]=serial_data;
         i++;
      }
       
    }

    }

}
//检测串口是否接收超时的函数
void UartTimeoutCheck(void)
{
    if(rec_flag == 1)
    {
       //Nowtime = millis(); 
       Costtime++;  
      if(Costtime == 100000)
      {
           rec_flag = 0;
           Costtime=0; 
      }
    }
}

void setup()
{
  IOInit();
  LED_ON;
  Serial.begin(9600);//更改波特率到9600
  myservo.attach(DUOJI_IO);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(DUOJI_IO2);  // attaches the servo on pin 10 to the servo object
  MsTimer2::set(1, flash);   // 中断设置函数，每 1ms 进入一次中断
  MsTimer2::start();   //开始计时
  stop();
  myservo.write(90); //舵机默认上电在90度位置   9  左右舵机
  myservo2.write(9); //舵机默认上电在9度位置  10  上下舵机
}

void loop() 
{
  delay(15000);//上电延时15s，防止wifi视频模块初始化干扰
  while(1)
{
   get_uartdate();//指令接收部分
   UartTimeoutCheck();    //检测串口是否接收超时的函数
  }
}

/**********************************************************************************************
*协议规定：
包头  类型位  数据位 数据位   结束位
0XFF   0X**   OX**   0X**      0XFF

各命令说明：
类型位   数据位    数据位  功能
0X00       0X01     0X00    前进
0X00       0X02      0X00    后退
0X00       0X03      0X00    左转
0X00       0X04      0X00    右转
0X00       0X00      0X00    停止
0X00       0X05      0X00    左前
0X00       0X06      0X00    右前
0X00       0X07      0X00    左后
0X00       0X08      0X00    右后

0X01       0X01      角度    舵机1
0X01       0X02       .      舵机2
0X01       0X03       .      舵机3
0X01       0X04       .      舵机4
0X01       0X05       .      舵机5
0X01       0X06       .      舵机6


0X02       0X00      0X00    车灯亮
0X02       0X01      0X00    车灯灭

0X03       0X00      0X00   喇叭开
0X03       0X01      0X00   喇叭关

0X04       0X00      0X00   自定义开
0X04       0X01      0X00   自定义关
****************************************************************************************************/

