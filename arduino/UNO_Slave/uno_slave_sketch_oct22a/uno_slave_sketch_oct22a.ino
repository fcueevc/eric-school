#define SLAVE_ID    1

// Pin define configuration
// 答案按鍵
#define gpio_input1 5 
#define gpio_input2 6 
#define gpio_input3 7 

// 設定按鍵
#define gpio_set 8

// LED燈號
#define gpio_led1 9 
#define gpio_led2 10 
#define gpio_led3 11 
#define gpio_led4 12

// 音效燈號
#define gpio_K1 2     // 答對音效腳
#define gpio_K2 3     // 答錯音效腳
#define gpio_K3 4     // 達錯LED腳位
#define gpio_K4 13    // 設定音效腳

// LED狀態
#define LED_ON   HIGH
#define LED_OFF  LOW

// 音效燈號
#define K_ON   HIGH
#define K_OFF  LOW

#define GPIO_PRESS LOW

// UART configuration
#define speed            115200
#define uart_delayTime   500   // Unit: ms
byte uart_string[10];
int  setStatus = 0;

int val1, val2, val3;
byte leds =0;
byte set_flag=0;

// 答案
byte answerbuf, answer;
String strOK = "OK+(";
String strEND = ")\r";
String strRQA = "AT+RQA(";
String strTemp = "";

void setup() {
  
  Serial.begin(speed);

  // put your setup code here, to run once:
  // 按鍵設定(輸入)
  pinMode(gpio_input1, INPUT_PULLUP);
  pinMode(gpio_input2, INPUT_PULLUP);
  pinMode(gpio_input3, INPUT_PULLUP);

  pinMode(gpio_set, INPUT_PULLUP);

  // LED腳位(輸出)
  pinMode(gpio_led1, OUTPUT);
  pinMode(gpio_led2, OUTPUT);
  pinMode(gpio_led3, OUTPUT);
  pinMode(gpio_led4, OUTPUT);

  digitalWrite(gpio_led1, LED_OFF);    // 開機設定為LOW
  digitalWrite(gpio_led2, LED_OFF);    // 開機設定為LOW
  digitalWrite(gpio_led3, LED_OFF);    // 開機設定為LOW
  digitalWrite(gpio_led4, LED_OFF);    // 開機設定為LOW

  // 音效腳位(輸出)
  pinMode(gpio_K1, OUTPUT);
  pinMode(gpio_K2, OUTPUT);
  pinMode(gpio_K3, OUTPUT);
  pinMode(gpio_K4, OUTPUT);  
  
  digitalWrite(gpio_K1, K_OFF);    // 開機設定為LOW
  digitalWrite(gpio_K2, K_OFF);    // 開機設定為LOW
  digitalWrite(gpio_K3, K_OFF);    // 開機設定為LOW
  digitalWrite(gpio_K4, K_OFF);    // 開機設定為LOW
}

void loop() {
  // put your main code here, to run repeatedly:
  // wait for data available
  // 接收答案
  if(Serial.available() >0)
  {
     //read until timeout
     String teststr = Serial.readString();

     // remove any \r \n whitespace at the end of the String
      teststr.trim();

      strTemp  = strOK + SLAVE_ID + "," + answerbuf+")";
      //Serial.println(strTemp);

      // 比對答案
      if(teststr==strTemp)
      {
        Serial.println(strTemp);
        Serial.println("Correct");
        digitalWrite(gpio_K3, K_ON);     // 答題LED(HIGH)
        digitalWrite(gpio_K1, K_ON);     // 音效腳
        delay(500);
        digitalWrite(gpio_K1, K_OFF);    // 音效腳

      }
      else if(teststr=="AT+RESET")
      {
        set_flag=0;
        leds = 0;
        answerbuf = 0;
        answer = 0;

        Serial.println("RESET");

        digitalWrite(gpio_led1, LED_OFF);
        digitalWrite(gpio_led2, LED_OFF);
        digitalWrite(gpio_led3, LED_OFF);
        digitalWrite(gpio_led4, LED_OFF);
        digitalWrite(gpio_K3, K_OFF);     

      }
      else
      {
        Serial.println(strTemp);
        Serial.println("Wrong answer");
        digitalWrite(gpio_K3, K_ON);     // 答題LED(HIGH)
        digitalWrite(gpio_K2, K_ON);     // 音效腳
        delay(500);
        digitalWrite(gpio_K3, K_OFF);    // 答題LED(HIGH)
        digitalWrite(gpio_K2, K_OFF);    // 音效腳

        delay(500);
        digitalWrite(gpio_K3, K_ON);     // 答題LED(HIGH)
        delay(500);
        digitalWrite(gpio_K2, K_OFF);    // 音效腳
        delay(500);
        digitalWrite(gpio_K3, K_ON);     // 答題LED(HIGH)
        delay(500);
        digitalWrite(gpio_K2, K_OFF);    // 音效腳
      }
  }
  
  if((digitalRead(gpio_input1)==GPIO_PRESS)&&(leds!=1)&&(set_flag==0))
  {
     leds = 1;
     answerbuf = 1;
     digitalWrite(gpio_led1, LED_ON);
     digitalWrite(gpio_led2, LED_OFF);
     digitalWrite(gpio_led3, LED_OFF);

     while(digitalRead(gpio_input1)==GPIO_PRESS);
  }

  if((digitalRead(gpio_input2)==GPIO_PRESS)&&(leds!=2)&&(set_flag==0))
  {
     leds = 2;
     answerbuf = 2;
     digitalWrite(gpio_led1, LED_OFF);
     digitalWrite(gpio_led2, LED_ON);
     digitalWrite(gpio_led3, LED_OFF);
     while(digitalRead(gpio_input2)==GPIO_PRESS);
  }

  if((digitalRead(gpio_input3)==GPIO_PRESS)&&(leds!=3)&&(set_flag==0))
  {
     leds = 3;
     answerbuf = 3;
     digitalWrite(gpio_led1, LED_OFF);
     digitalWrite(gpio_led2, LED_OFF);
     digitalWrite(gpio_led3, LED_ON);
     while(digitalRead(gpio_input3)==GPIO_PRESS);
  }

  if((digitalRead(gpio_set)==GPIO_PRESS)&&(set_flag==0)&&(leds!=0))
  {
     set_flag=1;
     digitalWrite(gpio_led4, LED_ON);
     digitalWrite(gpio_K4,K_ON);
     delay(500);
     digitalWrite(gpio_K4,K_OFF);
     while(digitalRead(gpio_set)==GPIO_PRESS);
     delay(100);
     
     // 詢問答案
     Serial.print(strRQA);   
     Serial.print(SLAVE_ID);
     Serial.print(strEND);
  }
  else if((digitalRead(gpio_set)==GPIO_PRESS)&&(set_flag==1))
  {
     set_flag=0;
     leds = 0;
     answerbuf = 0;
     answer = 0;

     digitalWrite(gpio_led1, LED_OFF);
     digitalWrite(gpio_led2, LED_OFF);
     digitalWrite(gpio_led3, LED_OFF);
     digitalWrite(gpio_led4, LED_OFF);
     digitalWrite(gpio_K3, K_OFF);     // 答題LED OFF(LOW) 
     delay(500);
     while(digitalRead(gpio_set)==GPIO_PRESS);
     delay(100);
  }
}
