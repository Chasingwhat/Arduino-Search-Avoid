//---------------红外寻线传感器采集-------------------------//
#define  r1  digitalRead(11)//定义右侧避障接口
#define  m1  digitalRead(12)//定义中间避障接口
#define  l1  digitalRead(3)//定义左侧避障接口
//---------------红外蔽障传感器采集-------------------------//
#define  r   digitalRead(2)//定义右侧避障接口
#define  m   digitalRead(1)//定义中间避障接口
#define  l   digitalRead(0)//定义左侧避障接口
//---------------------电机输出方向-------------------------//
#define Stop       0//停止
#define Forward    1//向前
#define Backward   2//向后
#define TurnLeft   3//左转
#define TurnRight  4//右转
//----------------------全局变量----------------------------//
int count;      //蔽障进入死区

//*********************主程序入口***************************//
void loop()
{
   Xun_Ji();
//  if (l1 == LOW && m1 == LOW && r1 == LOW)//寻线传感器未检测到黑线时
//  {
//    Bi_Zhang();
//  }
//  else if (l == HIGH && m == HIGH && r == HIGH)//蔽障传感器未检测到障碍时
//  {
//    Xun_Ji();
//  }
}

void Bi_Zhang()
{
  if (l == LOW || m == LOW || r == LOW) //当三个全部检测到障碍时
  {
    count++;
    if (l == LOW && m == LOW && r == LOW) //当左边右边和中间的检测到障碍时执行后退
    {
      Motor(Backward, 200);
      delay(40);
      Motor(TurnRight, 500);
      delay(40);
    }
    if (l == LOW && m == HIGH && r == HIGH)
    {
      Motor(Stop, 0);
      delay(40);
      Motor(TurnRight, 500);
      delay(60);
      if (count = 5)
      { Motor(Backward, 200); delay(40);
        Motor(TurnRight, 500); delay(80);
      }
    }
    if (l == LOW && m == LOW && r == HIGH)
    {
      Motor(Stop, 0);
      delay(40);
      Motor(TurnRight, 500);
      delay(60);
    }
    if (l == HIGH && m == HIGH && r == LOW)
    {
      Motor(Stop, 0);
      delay(40);
      Motor(TurnLeft, 500);
      delay(60);
      if (count = 5)
      { Motor(Backward, 200); delay(40);
        Motor(TurnLeft, 500); delay(80);
      }
    }

    if (l == HIGH && m == LOW && r == LOW)
    { Motor(Stop, 0);
      delay(40);
      Motor(TurnLeft, 500);
      delay(60);
    }

  }
  else if (l == HIGH && m == HIGH && r == HIGH)
  {
    Motor(Forward, 200);
    count = 0;
  }
}

void Xun_Ji(void)
{
  //-------------------------红外寻线传感器数据测试---------------------------
  //  Serial.print("l1:");
  //  Serial.println(l1);
  //  delay(500);
  //
  //  Serial.print("m1:");
  //  Serial.println(m1);
  //  delay(500);
  //
  //  Serial.print("r1:");
  //  Serial.println(r1);
  //  delay(500);
  //-------------------------------------------------------------------------

  if (l1 == LOW || m1 == LOW || r1 == LOW) //当三个有一个检测到障碍时
  {
    if (m1 == HIGH && l1 == LOW && r1 == HIGH)
    {
      Motor(Forward, 200);
    }
    if (l1 == HIGH && m1 == HIGH && r1 == LOW)
    {
      Motor(Stop, 0);
      delay(20);
      Motor(TurnLeft, 500);
      delay(90);
      while ( l1 == HIGH && m1 == HIGH)
      { Motor(Stop, 0);
        delay(20);
        Motor(TurnLeft, 500);
        delay(100);
      }
    }

    if (l1 == LOW && m1 == HIGH && r1 == HIGH)
    {
      Motor(Stop, 0);
      delay(20);
      Motor(TurnRight, 500);
      delay(90);
      while (m1 == HIGH && r1 == HIGH)
      { Motor(Stop, 0);
        delay(20);
        Motor(TurnRight, 500);
        delay(90);
      }
    }
    if (l1 == HIGH && m1 == LOW && r1 == LOW)
    {
      Motor(Stop, 0);
      delay(20);
      Motor(TurnLeft, 500);
      delay(100);
    }
    if (l1 == LOW && m1 == LOW && r1 == HIGH)
    {
      Motor(Stop, 0);
      delay(20);
      Motor(TurnRight, 500);
      delay(90);
    }
    else
    {
      Motor(Stop, 0);
      delay(20);
      Motor(Forward, 180);
      delay(20);
    }
  }
}
//-------------------------初始化------------------//
void setup()
{
  //电机
  pinMode(5, OUTPUT); //Eb
  pinMode(6, OUTPUT); //I4
  pinMode(7, OUTPUT); //I3

  pinMode(8, OUTPUT); //I1
  pinMode(9, OUTPUT); //I2
  pinMode(10, OUTPUT); //EA

  //避障模块
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);

  //寻迹
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(3, INPUT);
  //串口
  Serial.begin(9600);
}

//---------------------电机输出---------------------//
/***************************************************
   参数：dir：输出方向
   a：占空比
 ***************************************************/
void Motor(int dir, int a)
{
  switch (dir)
  {
    case Stop:
      {
        digitalWrite(10, 0);
        digitalWrite(5, 0);
      }; break;

    case Forward:
      {
        analogWrite(10, a); //输入数字量进行设定速度
        analogWrite(5, a);

        digitalWrite(9, HIGH); //使直流电机（右）顺时针转
        digitalWrite(8, LOW);
        digitalWrite(7, HIGH); //使直流电机（左）顺时针转
        digitalWrite(6, LOW);
      }; break;

    case Backward:
      {
        analogWrite(10, a); //输入模拟值进行设定速度
        analogWrite(5, a);

        digitalWrite(9, LOW); //使直流电机（右）逆时针转
        digitalWrite(8, HIGH);
        digitalWrite(7, LOW); //使直流电机（左）顺时针转
        digitalWrite(6, HIGH);
      } ; break;

    case TurnLeft:
      {
        analogWrite(10, a); //输入数字量进行设定速度
        analogWrite(5,  a);

        digitalWrite(9, HIGH); //使直流电机（右）顺时针转
        digitalWrite(8, LOW);
        digitalWrite(7, LOW); //使直流电机（左）不转
        digitalWrite(6, HIGH);
      } ; break;

    case TurnRight:
      {
        analogWrite(10, a); //输入数字量进行设定速度
        analogWrite(5, a);

        digitalWrite(9, LOW); //使直流电机（右）不转
        digitalWrite(8, HIGH);
        digitalWrite(7, HIGH); //使直流电机（左）顺时针转
        digitalWrite(6, LOW);
      } ; break;

    default: break;
  }

}




