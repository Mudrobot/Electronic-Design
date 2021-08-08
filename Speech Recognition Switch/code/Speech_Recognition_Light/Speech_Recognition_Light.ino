#include <SoftwareSerial.h>    //需要调用这个库实现串口通讯
#include <Servo.h>

Servo myservo;//create servo object to control a servo
SoftwareSerial softSerial(3,2); //新建一个softSerial对象，rx:3,tx:2
int a;                         //接收串口的值
int buzzerPin = 4;//the pin of the active buzzer attach to pin1
int angl=25,mid=54;

void setup() {
  pinMode(buzzerPin,OUTPUT);//set the buzzer as as OUTPUT
  digitalWrite(buzzerPin,HIGH);//initialize the buzzerPin as LOW level

  myservo.attach(9);//attachs the servo on pin 9 to servo object
  myservo.write(mid);//back to 0 degrees 
  
  pinMode(13,OUTPUT);        //设置IO口13为输出模式
  Serial.begin(9600);
  softSerial.begin(9600);   //初始化软串口通信；
  digitalWrite(13,LOW);     //给13口低电平
  delay(3000);
}
void BEEP(){
  digitalWrite(buzzerPin,LOW);
  delay(1000);
  digitalWrite(buzzerPin,HIGH);
}
void loop() {
  a=softSerial.read();      //读取串行端口的值
  if(a==0){
    Serial.println("Hello");
    BEEP();
  }
  if(a==1){
    Serial.println("The Light is on");
    myservo.write(mid+angl+10);
    BEEP();
    myservo.write(mid);
  }
  if(a==2){
    Serial.println("The Light is off");
    myservo.write(mid-angl);
    BEEP();
    myservo.write(mid);
  }
  /*switch(a)
  {
    case 1:          //前面提到的读取到1表示开灯
      digitalWrite(13,HIGH);//当喊“开灯”时，可以看到Arduino上的LED亮起
      break;
    case 2:
      digitalWrite(13,LOW);//当喊“关灯”时，可以看到Arduino上的LED熄灭
      break;
    default:
      break;
  }*/
}
//看上去还ok