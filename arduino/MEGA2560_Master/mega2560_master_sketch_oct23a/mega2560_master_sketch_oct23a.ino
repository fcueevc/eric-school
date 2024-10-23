#define LED_ON  HIGH
#define LED_OFF LOW

#define GPIO_PRESS LOW

// Pin define configuration
// 按鍵腳位
// 第一題設定答案腳位&LED
#define gpioA_Answer1 2
#define gpioA_Answer2 4
#define gpioA_Answer3 6

#define gpioA_LED1    3
#define gpioA_LED2    5
#define gpioA_LED3    7

// 第二題設定答案腳位&LED
#define gpioB_Answer1 8
#define gpioB_Answer2 10
#define gpioB_Answer3 12

#define gpioB_LED1    9
#define gpioB_LED2    11
#define gpioB_LED3    13

// 第三題設定答案腳位&LED
#define gpioC_Answer1 14
#define gpioC_Answer2 16
#define gpioC_Answer3 18

#define gpioC_LED1    15
#define gpioC_LED2    17
#define gpioC_LED3    19

// 第四題設定答案腳位&LED
#define gpioD_Answer1 20
#define gpioD_Answer2 22
#define gpioD_Answer3 24

#define gpioD_LED1    21
#define gpioD_LED2    23
#define gpioD_LED3    25

// 第五題設定答案腳位&LED
#define gpioE_Answer1 26
#define gpioE_Answer2 28
#define gpioE_Answer3 30

#define gpioE_LED1    27
#define gpioE_LED2    29
#define gpioE_LED3    31

// 設定腳位&LED
#define gpio_set      32
#define gpio_set_LED  33
#define gpio_reset    34

// 按鍵偵測時間
const int detectDelay   = 200;     
int  detectTime         = 0;

// UART configuration
#define speed       115200 // bps
#define uart_delayTime   500   // Unit: ms
byte uart_string[10];
int  setStatus = 0;
byte led_A =0;
byte led_B =0;
byte led_C =0;
byte led_D =0;
byte led_E =0;

int buttonState;

// 答案
byte answerBuf[5] = {1,2,2,1,3};   // 預設假答案
byte answer[5];        
String strRESET = "AT+RESET\r";
String strOK = "OK+(";
String strTemp = "";
String strEND = ")\r\n";
String strERROR = "ERROR+(";

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(speed);

  pinMode(gpioA_Answer1, INPUT_PULLUP);
  pinMode(gpioA_Answer2, INPUT_PULLUP);
  pinMode(gpioA_Answer3, INPUT_PULLUP);

  pinMode(gpioB_Answer1, INPUT_PULLUP);
  pinMode(gpioB_Answer2, INPUT_PULLUP);
  pinMode(gpioB_Answer3, INPUT_PULLUP);

  pinMode(gpioC_Answer1, INPUT_PULLUP);
  pinMode(gpioC_Answer2, INPUT_PULLUP);
  pinMode(gpioC_Answer3, INPUT_PULLUP);

  pinMode(gpioD_Answer1, INPUT_PULLUP);
  pinMode(gpioD_Answer2, INPUT_PULLUP);
  pinMode(gpioD_Answer3, INPUT_PULLUP);

  pinMode(gpioE_Answer1, INPUT_PULLUP);
  pinMode(gpioE_Answer2, INPUT_PULLUP);
  pinMode(gpioE_Answer3, INPUT_PULLUP);

  pinMode(gpio_set, INPUT_PULLUP);
  pinMode(gpio_reset, INPUT_PULLUP);

  // 設定燈號, 預設皆為OFF
  pinMode(gpioA_LED1, OUTPUT);
  pinMode(gpioA_LED2, OUTPUT);
  pinMode(gpioA_LED3, OUTPUT);
  
  digitalWrite(gpioA_LED1, LED_OFF);
  digitalWrite(gpioA_LED2, LED_OFF);
  digitalWrite(gpioA_LED3, LED_OFF);

  pinMode(gpioB_LED1, OUTPUT);
  pinMode(gpioB_LED2, OUTPUT);
  pinMode(gpioB_LED3, OUTPUT);
  
  digitalWrite(gpioB_LED1, LED_OFF);
  digitalWrite(gpioB_LED2, LED_OFF);
  digitalWrite(gpioB_LED3, LED_OFF);

  pinMode(gpioC_LED1, OUTPUT);
  pinMode(gpioC_LED2, OUTPUT);
  pinMode(gpioC_LED3, OUTPUT);
  
  digitalWrite(gpioC_LED1, LED_OFF);
  digitalWrite(gpioC_LED2, LED_OFF);
  digitalWrite(gpioC_LED3, LED_OFF);

  pinMode(gpioD_LED1, OUTPUT);
  pinMode(gpioD_LED2, OUTPUT);
  pinMode(gpioD_LED3, OUTPUT);
  
  digitalWrite(gpioD_LED1, LED_OFF);
  digitalWrite(gpioD_LED2, LED_OFF);
  digitalWrite(gpioD_LED3, LED_OFF);

  pinMode(gpioE_LED1, OUTPUT);
  pinMode(gpioE_LED2, OUTPUT);
  pinMode(gpioE_LED3, OUTPUT);
  
  digitalWrite(gpioE_LED1, LED_OFF);
  digitalWrite(gpioE_LED2, LED_OFF);
  digitalWrite(gpioE_LED3, LED_OFF);

  pinMode(gpio_set_LED, OUTPUT);
  
  digitalWrite(gpio_set_LED, LED_OFF);

}

void loop() {
  // put your main code here, to run repeatedly:
  char i;

  digitalWrite(gpio_set_LED, LED_ON);

  buttonState = digitalRead(gpioA_Answer1);

/*
  //wait for data available
  if(Serial.available() >0)
  {
      //read until timeout
            String teststr = Serial.readString();
      // remove any \r \n whitespace at the end of the String
      teststr.trim();

      // 比對答案
      if(teststr=="AT+RQA(1)")
      {
        strTemp = strOK + "1," + answerBuf[0] + strEND;
      }
      else if (teststr=="AT+RQA(2)")
      {
        strTemp = strOK + "2," + answerBuf[1] + strEND;
      }
      else if (teststr=="AT+RQA(3)")
      {
        strTemp = strOK + "3," + answerBuf[2] + strEND;
      }
      else if (teststr=="AT+RQA(4)")
      {
        strTemp = strOK + "4," + answerBuf[3] + strEND;
      }
      else if (teststr=="AT+RQA(5)")
      {
        strTemp = strOK + "5," + answerBuf[4] + strEND;
      }

      Serial.print(strTemp);
  }
*/
  // 讀取第一題按鍵
  if(buttonState==GPIO_PRESS)
  {
     led_A = 1;
     answerBuf[0] = 1;

     digitalWrite(gpioA_LED1, LED_ON);
     digitalWrite(gpioA_LED2, LED_OFF);
     digitalWrite(gpioA_LED3, LED_OFF);

     digitalWrite(gpio_set_LED, LED_ON);

     delay(100);
     while(digitalRead(gpioA_Answer1)==GPIO_PRESS);
  }
  
  if(digitalRead(gpioA_Answer2)==GPIO_PRESS)
  {
     led_A = 2;
     answerBuf[0] = 2;

     digitalWrite(gpioA_LED1, LED_OFF);
     digitalWrite(gpioA_LED2, LED_ON);
     digitalWrite(gpioA_LED3, LED_OFF);

     digitalWrite(gpio_set_LED, LED_ON);

     delay(100);
     while(digitalRead(gpioA_Answer2)==GPIO_PRESS);
  }

  if(digitalRead(gpioA_Answer3)==GPIO_PRESS)
  {
     led_A = 3;
     answerBuf[0] = 3;

     digitalWrite(gpioA_LED1, LED_OFF);
     digitalWrite(gpioA_LED2, LED_OFF);
     digitalWrite(gpioA_LED3, LED_ON);

     digitalWrite(gpio_set_LED, LED_ON);

     delay(100);
     while(digitalRead(gpioA_Answer3)==GPIO_PRESS);
  }

  digitalWrite(gpio_set_LED, LED_OFF);

  // 讀取第二題按鍵
  if((digitalRead(gpioB_Answer1)==GPIO_PRESS)&&(led_B!=1)&&(setStatus==0))
  {
     led_B = 1;
     answerBuf[1] = 1;

     digitalWrite(gpioB_LED1, LED_ON);
     digitalWrite(gpioB_LED2, LED_OFF);
     digitalWrite(gpioB_LED3, LED_OFF);

     delay(100);
     while(digitalRead(gpioB_Answer1)==GPIO_PRESS);
  }
  else if((digitalRead(gpioB_Answer2)==GPIO_PRESS)&&(led_B!=2)&&(setStatus==0))
  {
     led_B = 2;
     answerBuf[1] = 2;

     digitalWrite(gpioB_LED1, LED_OFF);
     digitalWrite(gpioB_LED2, LED_ON);
     digitalWrite(gpioB_LED3, LED_OFF);

     delay(100);
     while(digitalRead(gpioB_Answer2)==GPIO_PRESS);
  }
  else if((digitalRead(gpioB_Answer3)==GPIO_PRESS)&&(led_B!=3)&&(setStatus==0))
  {
     led_B = 3;
     answerBuf[1] = 3;

     digitalWrite(gpioB_LED1, LED_OFF);
     digitalWrite(gpioB_LED2, LED_OFF);
     digitalWrite(gpioB_LED3, LED_ON);

     delay(100);
     while(digitalRead(gpioB_Answer3)==GPIO_PRESS);
  }

  // 讀取第三題按鍵
  if((digitalRead(gpioC_Answer1)==GPIO_PRESS)&&(led_C!=1)&&(setStatus==0))
  {
     led_C = 1;
     answerBuf[2] = 1;

     digitalWrite(gpioC_LED1, LED_ON);
     digitalWrite(gpioC_LED2, LED_OFF);
     digitalWrite(gpioC_LED3, LED_OFF);

     delay(100);
     while(digitalRead(gpioC_Answer1)==GPIO_PRESS);
  }
  else if((digitalRead(gpioC_Answer2)==GPIO_PRESS)&&(led_C!=2)&&(setStatus==0))
  {
     led_C = 2;
     answerBuf[2] = 2;

     digitalWrite(gpioC_LED1, LED_OFF);
     digitalWrite(gpioC_LED2, LED_ON);
     digitalWrite(gpioC_LED3, LED_OFF);

     delay(100);
     while(digitalRead(gpioC_Answer2)==GPIO_PRESS);
  }
  else if((digitalRead(gpioC_Answer3)==GPIO_PRESS)&&(led_C!=3)&&(setStatus==0))
  {
     led_C = 3;
     answerBuf[2] = 3;

     digitalWrite(gpioC_LED1, LED_OFF);
     digitalWrite(gpioC_LED2, LED_OFF);
     digitalWrite(gpioC_LED3, LED_ON);

     delay(100);
     while(digitalRead(gpioC_Answer3)==GPIO_PRESS);
  }

  // 讀取第四題按鍵
  if((digitalRead(gpioD_Answer1)==GPIO_PRESS)&&(led_D!=1)&&(setStatus==0))
  {
     led_D = 1;
     answerBuf[3] = 1;

     digitalWrite(gpioD_LED1, LED_ON);
     digitalWrite(gpioD_LED2, LED_OFF);
     digitalWrite(gpioD_LED3, LED_OFF);

     delay(100);
     while(digitalRead(gpioD_Answer1)==GPIO_PRESS);
  }
  else if((digitalRead(gpioD_Answer2)==GPIO_PRESS)&&(led_D!=2)&&(setStatus==0))
  {
     led_D = 2;
     answerBuf[3] = 2;

     digitalWrite(gpioD_LED1, LED_OFF);
     digitalWrite(gpioD_LED2, LED_ON);
     digitalWrite(gpioD_LED3, LED_OFF);

     delay(100);
     while(digitalRead(gpioD_Answer2)==GPIO_PRESS);
  }
  else if((digitalRead(gpioD_Answer3)==GPIO_PRESS)&&(led_D!=3)&&(setStatus==0))
  {
     led_D = 3;
     answerBuf[3] = 3;

     digitalWrite(gpioD_LED1, LED_OFF);
     digitalWrite(gpioD_LED2, LED_OFF);
     digitalWrite(gpioD_LED3, LED_ON);

     delay(100);
     while(digitalRead(gpioD_Answer3)==GPIO_PRESS);
  }

  // 讀取第五題按鍵
  if((digitalRead(gpioE_Answer1)==GPIO_PRESS)&&(led_E!=1)&&(setStatus==0))
  {
     led_E = 1;
     answerBuf[4] = 1;

     digitalWrite(gpioE_LED1, LED_ON);
     digitalWrite(gpioE_LED2, LED_OFF);
     digitalWrite(gpioE_LED3, LED_OFF);

     delay(100);
     while(digitalRead(gpioE_Answer1)==GPIO_PRESS);
  }
  else if((digitalRead(gpioE_Answer2)==GPIO_PRESS)&&(led_E!=2)&&(setStatus==0))
  {
     led_E = 2;
     answerBuf[4] = 2;

     digitalWrite(gpioE_LED1, LED_OFF);
     digitalWrite(gpioE_LED2, LED_ON);
     digitalWrite(gpioE_LED3, LED_OFF);

     delay(100);
     while(digitalRead(gpioE_Answer2)==GPIO_PRESS);
  }
  else if((digitalRead(gpioE_Answer3)==GPIO_PRESS)&&(led_E!=3)&&(setStatus==0))
  {
     led_E = 3;
     answerBuf[4] = 3;

     digitalWrite(gpioE_LED1, LED_OFF);
     digitalWrite(gpioE_LED2, LED_OFF);
     digitalWrite(gpioE_LED3, LED_ON);

     delay(100);
     while(digitalRead(gpioE_Answer3)==GPIO_PRESS);
  }

  // 設定
  if((digitalRead(gpio_set)==GPIO_PRESS)&&(setStatus==0)&&(led_A!=0)&&(led_B!=0)&&(led_C!=0)&&(led_D!=0)&&(led_E!=0))
  {
      for(i=0;i<5;i++)
      {
        answer[i] = answerBuf[i];
        //Serial.println(answer[i]);
      } 

      setStatus = 1;
      //Serial.println("Lock");

      //複查答案內容, 應不可等於0
      for(i=0;i<5;i++)
      {
        if(answer[i]==0)
          setStatus = 0;
      }

      if(setStatus==1)
      {
        digitalWrite(gpio_set_LED, LED_ON);    // 答案全部設定,SET LED ON
      } 
      else                                     // 答案未全部設定,SET LED 閃爍
      {
        digitalWrite(gpio_set_LED, LED_ON);
        delay(500);
        digitalWrite(gpio_set_LED, LED_OFF);
        delay(500);
        digitalWrite(gpio_set_LED, LED_ON);
        delay(500);
        digitalWrite(gpio_set_LED, LED_OFF);
        delay(500);
        digitalWrite(gpio_set_LED, LED_ON);
        delay(500);
        digitalWrite(gpio_set_LED, LED_OFF);          
      }

      delay(100);
      while(digitalRead(gpio_set)==GPIO_PRESS);
   }
   else if((digitalRead(gpio_set)==GPIO_PRESS)&&(setStatus==1))   // 清除狀態, 重設答案
   { 
      // 設定LED OFF
      digitalWrite(gpio_set_LED, LED_OFF);

      // 答案清零
      for(i=0;i<5;i++)            // 解鎖 unlock 
      {
        answerBuf[i] = 0;
        answer[i] = 0;
      }

      led_A = 0;
      led_B = 0;
      led_C = 0;
      led_D = 0;
      led_E = 0;

      // All LED OFF
      //digitalWrite(gpioA_LED1, LED_OFF);
      //digitalWrite(gpioA_LED2, LED_OFF);
      //digitalWrite(gpioA_LED3, LED_OFF);
      
     // digitalWrite(gpioB_LED1, LED_OFF);
     // digitalWrite(gpioB_LED2, LED_OFF);
      //digitalWrite(gpioB_LED3, LED_OFF);
      
      //digitalWrite(gpioC_LED1, LED_OFF);
     // digitalWrite(gpioC_LED2, LED_OFF);
     // digitalWrite(gpioC_LED3, LED_OFF);
      
      //digitalWrite(gpioD_LED1, LED_OFF);
     // digitalWrite(gpioD_LED2, LED_OFF);
      //digitalWrite(gpioD_LED3, LED_OFF);
      
      //digitalWrite(gpioE_LED1, LED_OFF);
     // digitalWrite(gpioE_LED2, LED_OFF);
      //digitalWrite(gpioE_LED3, LED_OFF);

      setStatus = 0;
      //Serial.print(strRESET);   

      delay(100);
      while(digitalRead(gpio_set)==GPIO_PRESS);
  }

  // 清除學習站答案RESET(僅下指令給學習站, 清除學習站答案, 以利下一組作答)
  if(digitalRead(gpio_reset)==GPIO_PRESS)
  {
     //Serial.print(strRESET);  
     delay(100);
     while(digitalRead(gpio_reset)==GPIO_PRESS);
  }
}
