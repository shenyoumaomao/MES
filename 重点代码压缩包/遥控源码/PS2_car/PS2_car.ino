
#include <PS2X_lib.h>  //PS2的库文件，需先添加到Arduino IDE的库文件
//PS2引脚定义
#define PS2_DAT_PIN        A1  //MOS
#define PS2_CMD_PIN        A0  //MIS
#define PS2_SEL_PIN        A2  //CS
#define PS2_CLK_PIN        A3  //SCK

#define pressures   true  //按键模式
#define rumble      true  //振动模式

//PS2设置
PS2X ps2x;                //定义ps2x为PS2X类变量
int error = 0;
byte type = 0;
byte vibrate = 0;
//小车运行状态枚举
enum {
  enSTOP = 1,
  enRUN,
  enBACK,
  enLEFT,
  enRIGHT,
  enUPLEFT,
  enUPRIGHT,
  enDOWNLEFT,
  enDOWNRIGHT
} enCarState;

//蜂鸣器引脚设置
int buzzer = 2;          //设置控制蜂鸣器引脚为2

//小车初始速度控制
int CarSpeedControl = 150;

//小车运动状态和舵机运动状态标志
int g_CarState = enSTOP;  //1前2后3左4右0停止
int g_ServoState = 0;     //1左摇 2 右摇

//设置舵机驱动引脚
int ServoPin = 9;

//RGBLED引脚设置
int LED_R = 11;           //LED_R接在arduino上的数字11口
int LED_G = 12;           //LED_G接在arduino上的数字12口
int LED_B = 13;            //LED_B接在arduino上的数字13口

//初始化配置
void setup()
{
  //串口波特率设置
  Serial.begin(9600);
  //初始化蜂鸣器IO为输出方式
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH);

  //初始化舵机引脚为输出模式
  pinMode(ServoPin, OUTPUT);
  //电机输出模式
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
  //初始化RGB三色LED的IO口为输出方式，并初始化
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);

  //在配置无线PS2模块之前，延时300ms以便于配置生效
  delay(300);

  /*PS2初始化*/
  error = ps2x.config_gamepad(PS2_CLK_PIN, PS2_CMD_PIN, PS2_SEL_PIN, PS2_DAT_PIN, pressures, rumble);
  if (error == 0)
  {
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
    if (pressures)
    {
      Serial.println("true ");
    }
    else
    {
      Serial.println("false");
    }
    Serial.print("rumble = ");
    if (rumble)
    {
      Serial.println("true)");
    }
    else
    {
      Serial.println("false");
    }
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }
  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  //获取手柄类型
  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
    case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
  }
}


//小车前进函数
void run()
{
  analogWrite(5,150);
  digitalWrite(7,HIGH);
  analogWrite(6,150);
  digitalWrite(4,HIGH); 
}
//小车停车
void brake()
{
  analogWrite(5,0);
  digitalWrite(7,HIGH);
  analogWrite(6,0);
  digitalWrite(4,HIGH);
}

//小车左转(左轮不动,右轮前进)
void left()
{
  analogWrite(5,0);
  digitalWrite(7,HIGH);
  analogWrite(6,150);
  digitalWrite(4,HIGH);
}


//小车沿左前轮前进(左轮前进,右轮前进，两者有差速) 4轮小车并联方式驱动

void upleft()
{
  analogWrite(5,150);
  digitalWrite(7,HIGH);
  analogWrite(6,150);
  digitalWrite(4,HIGH);
}


//小车沿左后方后退(左轮后退,右轮后退，两者有差速) 4轮小车并联方式驱动

void downleft()
{
  analogWrite(5,150);
  digitalWrite(7,LOW);
  analogWrite(6,150);
  digitalWrite(4,LOW);
}


//小车原地左转(左轮后退，右轮前进)

void spin_left()
{
  analogWrite(5,150);
  digitalWrite(7,LOW);
  analogWrite(6,150);
  digitalWrite(4,HIGH);
}

//小车右转(左轮前进,右轮不动)
void right()
{
  analogWrite(5,150);
  digitalWrite(7,HIGH);
  analogWrite(6,0);
  digitalWrite(4,LOW);
}


//小车沿右上方前进 (左轮前进,右轮前进，两者有差速)

void upright()
{
  analogWrite(5,150);
  digitalWrite(7,HIGH);
  analogWrite(6,150);
  digitalWrite(4,HIGH);
}

//小车沿右下方后退(左轮后退,右轮后退，两者有差速)

void downright()
{
  analogWrite(5,150);
  digitalWrite(7,LOW);
  analogWrite(6,150);
  digitalWrite(4,LOW);
}


//小车原地右转 原地右转(右轮后退，左轮前进)

void spin_right()
{
  analogWrite(5,150);
  digitalWrite(7,HIGH);
  analogWrite(6,150);
  digitalWrite(4,LOW);
}


//小车后退
void back()
{
  analogWrite(5,150);
  digitalWrite(7,LOW);
  analogWrite(6,150);
  digitalWrite(4,LOW);
}

//小车鸣笛

void whistle()
{
  digitalWrite(buzzer, LOW);   //发声音
  delay(100);                  //延时100ms
  digitalWrite(buzzer, HIGH);  //不发声音
  delay(1);                    //延时1ms

  digitalWrite(buzzer, LOW);   //发声音
  delay(200);                  //延时200ms
  digitalWrite(buzzer, HIGH);  //不发声音
  delay(2);                    //延时2ms
}


//定义一个脉冲函数，用来模拟方式产生PWM值
// 时基脉冲为20ms,该脉冲高电平部分在0.5-2.5ms
//控制0-180度
//ServPin:舵机控制引脚
// myangle:舵机转动指定的角度

void servo_pulse(int ServoPin, int myangle)
{
  int PulseWidth;                    //定义脉宽变量
  PulseWidth = (myangle * 11) + 500; //将角度转化为500-2480 的脉宽值
  digitalWrite(ServoPin, HIGH);      //将舵机接口电平置高
  delayMicroseconds(PulseWidth);     //延时脉宽值的微秒数
  digitalWrite(ServoPin, LOW);       //将舵机接口电平置低
  delay(20 - PulseWidth / 1000);     //延时周期内剩余时间
  return;
}


//舵机旋转到指定角度
//pos：指定的角度

void servo_appointed_detection(int pos)
{
  int i = 0;
  for (i = 0; i <= 15; i++)    //产生PWM个数，等效延时以保证能转到响应角度
  {
    servo_pulse(ServoPin, pos); //模拟产生PWM
  }
}


// 七彩灯亮指定的颜色
// v_iRed:指定的颜色值（0-255）
// v_iGreen:指定的颜色值（0-255）
// v_iBlue:指定的颜色值（0-255）

void color_led_pwm(int v_iRed, int v_iGreen, int v_iBlue)
{
  analogWrite(LED_R, v_iRed);
  analogWrite(LED_G, v_iGreen);
  analogWrite(LED_B, v_iBlue);
  return;
}

//PS2控制小车
void PS2_control(void)
{
  //摇杆方向值变量的定义
  int X1, Y1, X2, Y2;
  //如果手柄初始化失败或者手柄类型没找到,则返回
  if (error == 1)           //skip loop if no controller found
    return;
  if (type != 1)            //skip loop if no controller found
    return;
    
  //DualShock Controller
  ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed

  //手柄上的START键按下
  if (ps2x.Button(PSB_START))        //will be TRUE as long as button is pressed
    Serial.println("Start is being held");

  //手柄上的SELECT键按下
  if (ps2x.Button(PSB_SELECT))
    Serial.println("Select is being held");

  //手柄上的方向键上按下
  if (ps2x.Button(PSB_PAD_UP))      //will be TRUE as long as button is pressed
  {
    Serial.print("Up held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
    g_CarState = enRUN;
  }
  //手柄上的方向键右按下
  else if (ps2x.Button(PSB_PAD_RIGHT))
  {
    Serial.print("Right held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
    g_CarState = enRIGHT;
  }
  //手柄上的方向键左按下
  else if (ps2x.Button(PSB_PAD_LEFT))
  {
    Serial.print("LEFT held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
    g_CarState = enLEFT;
  }
  //手柄上的方向键下按下
  else if (ps2x.Button(PSB_PAD_DOWN))
  {
    Serial.print("DOWN held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    g_CarState = enBACK;
  }
  else
  {
    g_CarState = enSTOP;
  }

  //this will set the large motor vibrate speed based on how hard you press the blue (X) button
  vibrate = ps2x.Analog(PSAB_CROSS);

  //L3即左侧的摇杆按下小车停止
  if (ps2x.Button(PSB_L3))
  {
    g_CarState = enSTOP;
    Serial.println("L3 pressed");
  }
  //R3即右侧的摇杆按下小车舵机复位
  if (ps2x.Button(PSB_R3))
  {
    servo_appointed_detection(90);
    Serial.println("R3 pressed");
  }
  //L2即手柄左侧前方下面的按键按下即小车加速
  if (ps2x.Button(PSB_L2))
  {
    Serial.println("L2 pressed");
    CarSpeedControl += 50;
    if (CarSpeedControl > 255)
    {
      CarSpeedControl = 255;
    }
  }
  //R2即手柄右侧前方下面的按键按下即小车减速
  if (ps2x.Button(PSB_R2))
  {
    Serial.println("R2 pressed");
    CarSpeedControl -= 50;
    if (CarSpeedControl < 50)
    {
      CarSpeedControl = 100;
    }
  }

  //手柄右侧的方形按下时亮红灯
  if (ps2x.Button(PSB_SQUARE))
  {
    Serial.println("Square pressed");
    color_led_pwm(255, 0, 0);
    delay(500);
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
  }
  //手柄右侧的三角形按下时亮绿灯
  if (ps2x.Button(PSB_TRIANGLE))
  {
    Serial.println("Triangle pressed");
    color_led_pwm(0, 255, 0);
    delay(500);
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
  }

  //手柄右侧的圆形按下时亮蓝灯
  if (ps2x.Button(PSB_CIRCLE))
  {
    Serial.println("Circle pressed");
    color_led_pwm(0, 0, 255);
    delay(500);
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
  }

  //手柄右侧的×形按下或松开时鸣笛
  if (ps2x.NewButtonState(PSB_CROSS))    //will be TRUE if button was JUST pressed OR released
  {
    Serial.println("X just changed");
    whistle();
  }
  //当手柄左侧前方上面或右侧前方上面的按键按下时读取摇杆数据
  if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1))
  {
    //print stick values if either is TRUE
    Serial.print("Stick Values:");
    Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_LX), DEC);
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_RY), DEC);
    Serial.print(",");
    Serial.println(ps2x.Analog(PSS_RX), DEC);

    //读取摇杆的数据
    Y1 = ps2x.Analog(PSS_LY);
    X1 = ps2x.Analog(PSS_LX);
    Y2 = ps2x.Analog(PSS_RY);
    X2 = ps2x.Analog(PSS_RX);

    /*左摇杆控制小车运动状态程序*/
    if (Y1 < 5 && X1 > 80 && X1 < 180)         //上
    {
      g_CarState = enRUN;
    }
    else if (Y1 > 230 && X1 > 80 && X1 < 180) //下
    {
      g_CarState = enBACK;
    }
    else if (X1 < 5 && Y1 > 80 && Y1 < 180)   //左
    {
      g_CarState = enLEFT;
    }
    else if (Y1 > 80 && Y1 < 180 && X1 > 230) //右
    {
      g_CarState = enRIGHT;
    }
    else if (Y1 <= 80 && X1 <= 80)           //左上
    {
      g_CarState = enUPLEFT;
    }
    else if (Y1 <= 80 && X1 >= 180)          //右上
    {
      g_CarState = enUPRIGHT;
    }
    else if (X1 <= 80 && Y1 >= 180)          //左下
    {
      g_CarState = enDOWNLEFT;
    }
    else if (Y1 >= 180 && X1 >= 180)        //右下
    {
      g_CarState = enDOWNRIGHT;
    }
    else                                    //停
    {
      g_CarState = enSTOP;
    }

    /*右摇杆控制舵机运动状态*/
    if (X2 < 5 && Y2 > 110 && Y2 < 150)    //左
    {
      g_ServoState = 1;
    }
    else if (Y2 > 110 && Y2 < 150 && X2 > 230)//右
    {
      g_ServoState = 2;
    }
    else                                   //归位
    {
      g_ServoState = 0;
    }
  }
}



//循环接受手柄发过来的指令,并执行相应的动作

void loop()
{
  //状态标识
  int flag = 0;
  PS2_control();
  switch (g_CarState)
  {
    case enSTOP: brake(); break;
    case enRUN: run();  break;
    case enLEFT: left();  break;
    case enRIGHT: right(); break;
    case enBACK: back(); break;
    case enUPLEFT: upleft();  break;
    case enUPRIGHT: upright(); break;
    case enDOWNLEFT: downleft();  break;
    case enDOWNRIGHT: downright(); break;
    default: break;
  }
  switch (g_ServoState)
  {
    case 0: if (flag != 0) {
        flag = 0;
        servo_appointed_detection(90);
      } break;
    case 1: if (flag != 1) {
        flag = 1;
        servo_appointed_detection(180);
      } break;
    case 2: if (flag != 2) {
        flag = 2;
        servo_appointed_detection(0);
      } break;
    default: break;
  }
 
  delay(50);//加延时,主要是避免过于频繁的发送手柄指令造成的重启
}
