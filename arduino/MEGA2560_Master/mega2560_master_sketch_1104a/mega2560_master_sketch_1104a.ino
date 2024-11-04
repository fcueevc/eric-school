#define LED_ON  HIGH
#define LED_OFF LOW

#define GPIO_PRESS LOW

// Pin define configuration
// 按鍵腳位
// 第一題設定答案腳位&LED
#define gpioA_Answer1 3
#define gpioA_Answer2 5
#define gpioA_Answer3 7

#define gpioA_LED1    2
#define gpioA_LED2    4
#define gpioA_LED3    6

// 第二題設定答案腳位&LED
#define gpioB_Answer1 9   
#define gpioB_Answer2 11   
#define gpioB_Answer3 12   

#define gpioB_LED1    8   
#define gpioB_LED2    10   
#define gpioB_LED3    13   

// 第三題設定答案腳位&LED
#define gpioC_Answer1 15
#define gpioC_Answer2 17
#define gpioC_Answer3 19

#define gpioC_LED1    14
#define gpioC_LED2    16
#define gpioC_LED3    18

// 第四題設定答案腳位&LED
#define gpioD_Answer1 21
#define gpioD_Answer2 23
#define gpioD_Answer3 25

#define gpioD_LED1    20
#define gpioD_LED2    22
#define gpioD_LED3    24

// 第五題設定答案腳位&LED
#define gpioE_Answer1 27
#define gpioE_Answer2 29
#define gpioE_Answer3 31

#define gpioE_LED1    26
#define gpioE_LED2    28
#define gpioE_LED3    30

// 設定腳位&LED
#define gpio_set      32
#define gpio_set_LED  33

#define gpio_AllPASS  36      // All Pass 音效
#define gpio_AllPASS_LED  46  // LED爆閃

const int detectDelay   = 200;     
int  detectTime         = 0;

// UART configuration
#define speed       115200 // bps
#define uart_delayTime   500   // Unit: ms
byte uart_string[10];

// 2024.10.30 Owen add
// 確認接收比數, 滿5筆進行比對. 
// 0表示未接收(預設)_
// 1表示已接收, 答案正確
// 2表示已接收, 答案錯誤
byte answerConfirm[5] = {0,0,0,0,0}; 

// setStatus: 設定按鍵的狀態
// 0表示unlock(預設)
// 1表示lock
int  setStatus = 0;     
byte led_A =0;
byte led_B =0;
byte led_C =0;
byte led_D =0;
byte led_E =0;

int buttonState = 0;  // variable for reading the pushbutton status

// 答案
byte answerBuf[5] = {0,0,0,0,0};   
byte answer[5];        
String strRESET = "AT+RESET\r";
String strOK = "OK+(";
String strRQA = "AT+RQA(";
String strTemp = "";
String strAns = "";
String strEND = ")\r\n";
String strERROR = "ERROR+(";

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(speed);

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

  pinMode(gpio_AllPASS, OUTPUT);  
  digitalWrite(gpio_AllPASS, LOW);
  
  pinMode(gpio_AllPASS_LED, OUTPUT);  
  digitalWrite(gpio_AllPASS_LED, LOW);
  
  // Only for debug
  //Serial.println("TEST");  

}

void loop() {
  // put your main code here, to run repeatedly:
  char i;
  
  //wait for data available
  if(Serial1.available() >0)
  {
      //read until timeout
//      digitalWrite(gpioE_LED3, LED_ON);
//      digitalWrite(gpioD_LED3, LED_ON);

      String teststr = Serial1.readString();
      // remove any \r \n whitespace at the end of the String
      teststr.trim();

      //Serial.println(teststr);  
 
      // 比對答案
      if((teststr==("AT+RQA(1,1)"))||(teststr==("AT+RQA(1,2)"))||(teststr==("AT+RQA(1,3)")))
      {
        // 設定Response
        strTemp = strOK + "1," + answerBuf[0] + strEND;
        strAns = strRQA + "1," + answerBuf[0] +")";
        
        // 比對答案
        if(teststr==strAns)
        {
          //Serial.println("Correct");
          answerConfirm[0] = 1;    // 答案正確
        }
        else
        {
          //Serial.println("Wrong");
          answerConfirm[0] = 2;    // 答案錯誤
        }

        strAns ="";  // 清空Buffer
      }
      else if ((teststr==("AT+RQA(2,1)"))||(teststr==("AT+RQA(2,2)"))||(teststr==("AT+RQA(2,3)")))
      {
        // 設定Response
        strTemp = strOK + "2," + answerBuf[1] + strEND;
        strAns = strRQA + "2," + answerBuf[1] +")";

        // 比對答案
        if(teststr==strAns)
        {
          //Serial.println("Correct");
          answerConfirm[1] = 1;    // 答案正確
        }
        else
        {
          //Serial.println("Wrong");
          answerConfirm[1] = 2;    // 答案錯誤
        }

        strAns ="";  // 清空Buffer
      }
      else if ((teststr==("AT+RQA(3,1)"))||(teststr==("AT+RQA(3,2)"))||(teststr==("AT+RQA(3,3)")))
      {
        // 設定Response
        strTemp = strOK + "3," + answerBuf[2] + strEND;
        strAns = strRQA + "3," + answerBuf[2] +")";

        // 比對答案
        if(teststr==strAns)
        {
          //Serial.println("Correct");
          answerConfirm[2] = 1;    // 答案正確
        }
        else
        {
          //Serial.println("Wrong");
          answerConfirm[2] = 2;    // 答案錯誤
        }

        strAns ="";  // 清空Buffer
      }
      else if ((teststr==("AT+RQA(4,1)"))||(teststr==("AT+RQA(4,2)"))||(teststr==("AT+RQA(4,3)")))
      {
        // 設定Response
        strTemp = strOK + "4," + answerBuf[3] + strEND;
        strAns = strRQA + "4," + answerBuf[3] +")";

        // 比對答案
        if(teststr==strAns)
        {
          //Serial.println("Correct");
          answerConfirm[3] = 1;    // 答案正確
        }
        else
        {
          //Serial.println("Wrong");
          answerConfirm[3] = 2;    // 答案錯誤
        }

        strAns ="";  // 清空Buffer
      }
      else if ((teststr==("AT+RQA(5,1)"))||(teststr==("AT+RQA(5,2)"))||(teststr==("AT+RQA(5,3)")))
      {
        // 設定Response
        strTemp = strOK + "5," + answerBuf[4] + strEND;
        strAns = strRQA + "5," + answerBuf[4] +")";

        // 比對答案
        if(teststr==strAns)
        {
          //Serial.println("Correct");
          answerConfirm[4] = 1;    // 答案正確
        }
        else
        {
          //Serial.println("Wrong");
          answerConfirm[4] = 2;    // 答案錯誤
        }

        strAns ="";  // 清空Buffer
      }
      
      // Response
      Serial1.print(strTemp);  
      
      // Only for debug
      //for(i=0;i<5;i++)
      //{
        //Serial.println(answerConfirm[i]);
     // } 

      if((answerConfirm[0]==0)||((answerConfirm[1])==0)||((answerConfirm[2])==0)||((answerConfirm[3])==0)||((answerConfirm[4])==0))   // 等待作答
      {
        //Serial.println("Wait for Answer");
        // Do nothing
      }
      else if((answerConfirm[0]==1)&&((answerConfirm[1])==1)&&((answerConfirm[2])==1)&&((answerConfirm[3])==1)&&((answerConfirm[4])==1))  // 答案全對
      {
        //Serial.println("All Pass!!");
        digitalWrite(gpio_AllPASS, HIGH);
        digitalWrite(gpio_AllPASS_LED, HIGH);
        delay(500);

        digitalWrite(gpio_AllPASS, LOW);

        delay(3000);

        //digitalWrite(gpio_AllPASS_LED, LOW);

      }
      else if((answerConfirm[0]==2)||((answerConfirm[1])==2)||((answerConfirm[2])==2)||((answerConfirm[3])==2)||((answerConfirm[4])==2))  // 任一答案錯誤
      {
        //Serial.println("Some errors!");

        // 要設定錯誤音效腳(這邊還沒設)
      }
  }

  //buttonState = digitalRead(gpioA_Answer1);
  // 讀取第一題按鍵
  if((digitalRead(gpioA_Answer1)==GPIO_PRESS)&&(led_A!=1)&&(setStatus==0))
  {
     led_A = 1;
     answerBuf[0] = 1;

     digitalWrite(gpioA_LED1, LED_ON);
     digitalWrite(gpioA_LED2, LED_OFF);
     digitalWrite(gpioA_LED3, LED_OFF);

     delay(50);
     while(digitalRead(gpioA_Answer1)==GPIO_PRESS);
  }
  
  if((digitalRead(gpioA_Answer2)==GPIO_PRESS)&&(led_A!=2)&&(setStatus==0))
  {
     led_A = 2;
     answerBuf[0] = 2;

     digitalWrite(gpioA_LED1, LED_OFF);
     digitalWrite(gpioA_LED2, LED_ON);
     digitalWrite(gpioA_LED3, LED_OFF);

     delay(50);
     while(digitalRead(gpioA_Answer2)==GPIO_PRESS);
  }
  
  if((digitalRead(gpioA_Answer3)==GPIO_PRESS)&&(led_A!=3)&&(setStatus==0))
  {
     led_A = 3;
     answerBuf[0] = 3;

     digitalWrite(gpioA_LED1, LED_OFF);
     digitalWrite(gpioA_LED2, LED_OFF);
     digitalWrite(gpioA_LED3, LED_ON);
     
     delay(50);
     while(digitalRead(gpioA_Answer3)==GPIO_PRESS);
  }
  
  // 讀取第二題按鍵
  if((digitalRead(gpioB_Answer1)==GPIO_PRESS)&&(led_B!=1)&&(setStatus==0))
  {
     led_B = 1;
     answerBuf[1] = 1;

     digitalWrite(gpioB_LED1, LED_ON);
     digitalWrite(gpioB_LED2, LED_OFF);
     digitalWrite(gpioB_LED3, LED_OFF);

     delay(50);
     while(digitalRead(gpioB_Answer1)==GPIO_PRESS);
  }
  
  if((digitalRead(gpioB_Answer2)==GPIO_PRESS)&&(led_B!=2)&&(setStatus==0))
  {
     led_B = 2;
     answerBuf[1] = 2;

     digitalWrite(gpioB_LED1, LED_OFF);
     digitalWrite(gpioB_LED2, LED_ON);
     digitalWrite(gpioB_LED3, LED_OFF);

     delay(50);
     while(digitalRead(gpioB_Answer2)==GPIO_PRESS);
  }
  
  if((digitalRead(gpioB_Answer3)==GPIO_PRESS)&&(led_B!=3)&&(setStatus==0))
  {
     led_B = 3;
     answerBuf[1] = 3;

     digitalWrite(gpioB_LED1, LED_OFF);
     digitalWrite(gpioB_LED2, LED_OFF);
     digitalWrite(gpioB_LED3, LED_ON);

     delay(50);
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

     delay(50);
     while(digitalRead(gpioC_Answer1)==GPIO_PRESS);
  }
  
  if((digitalRead(gpioC_Answer2)==GPIO_PRESS)&&(led_C!=2)&&(setStatus==0))
  {
     led_C = 2;
     answerBuf[2] = 2;

     digitalWrite(gpioC_LED1, LED_OFF);
     digitalWrite(gpioC_LED2, LED_ON);
     digitalWrite(gpioC_LED3, LED_OFF);

     delay(50);
     while(digitalRead(gpioC_Answer2)==GPIO_PRESS);
  }
  
  if((digitalRead(gpioC_Answer3)==GPIO_PRESS)&&(led_C!=3)&&(setStatus==0))
  {
     led_C = 3;
     answerBuf[2] = 3;

     digitalWrite(gpioC_LED1, LED_OFF);
     digitalWrite(gpioC_LED2, LED_OFF);
     digitalWrite(gpioC_LED3, LED_ON);

     delay(50);
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

     delay(50);
     while(digitalRead(gpioD_Answer1)==GPIO_PRESS);
  }
  
  if((digitalRead(gpioD_Answer2)==GPIO_PRESS)&&(led_D!=2)&&(setStatus==0))
  {
     led_D = 2;
     answerBuf[3] = 2;

     digitalWrite(gpioD_LED1, LED_OFF);
     digitalWrite(gpioD_LED2, LED_ON);
     digitalWrite(gpioD_LED3, LED_OFF);

     delay(50);
     while(digitalRead(gpioD_Answer2)==GPIO_PRESS);
  }
  
  if((digitalRead(gpioD_Answer3)==GPIO_PRESS)&&(led_D!=3)&&(setStatus==0))
  {
     led_D = 3;
     answerBuf[3] = 3;

     digitalWrite(gpioD_LED1, LED_OFF);
     digitalWrite(gpioD_LED2, LED_OFF);
     digitalWrite(gpioD_LED3, LED_ON);
     delay(50);
     
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

     delay(50);
     while(digitalRead(gpioE_Answer1)==GPIO_PRESS);
  }
  
  if((digitalRead(gpioE_Answer2)==GPIO_PRESS)&&(led_E!=2)&&(setStatus==0))
  {
     led_E = 2;
     answerBuf[4] = 2;

     digitalWrite(gpioE_LED1, LED_OFF);
     digitalWrite(gpioE_LED2, LED_ON);
     digitalWrite(gpioE_LED3, LED_OFF);

     while(digitalRead(gpioE_Answer2)==GPIO_PRESS);
  }
  
  if((digitalRead(gpioE_Answer3)==GPIO_PRESS)&&(led_E!=3)&&(setStatus==0))
  {
     led_E = 3;
     answerBuf[4] = 3;

     digitalWrite(gpioE_LED1, LED_OFF);
     digitalWrite(gpioE_LED2, LED_OFF);
     digitalWrite(gpioE_LED3, LED_ON);
     
     delay(50);
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
      digitalWrite(gpio_set_LED, LED_ON);     

      delay(500);
      while(digitalRead(gpio_set)==GPIO_PRESS);
   }
   else if((digitalRead(gpio_set)==GPIO_PRESS)&&(setStatus==1))   // 清除狀態, 重設答案
   { 
      // 設定LED OFF
      digitalWrite(gpio_set_LED, LED_OFF);
      digitalWrite(gpio_AllPASS_LED, LOW);

      // 答案清零
      for(i=0;i<5;i++)            // 解鎖 unlock 
      {
        answerBuf[i] = 0;
        answer[i] = 0;
        answerConfirm[i] = 0;
      }

      led_A = 0;
      led_B = 0;
      led_C = 0;
      led_D = 0;
      led_E = 0;

      // All LED OFF
      digitalWrite(gpioA_LED1, LED_OFF);
      digitalWrite(gpioA_LED2, LED_OFF);
      digitalWrite(gpioA_LED3, LED_OFF);
      
      digitalWrite(gpioB_LED1, LED_OFF);
      digitalWrite(gpioB_LED2, LED_OFF);
      digitalWrite(gpioB_LED3, LED_OFF);
      
      digitalWrite(gpioC_LED1, LED_OFF);
      digitalWrite(gpioC_LED2, LED_OFF);
      digitalWrite(gpioC_LED3, LED_OFF);
      
      digitalWrite(gpioD_LED1, LED_OFF);
      digitalWrite(gpioD_LED2, LED_OFF);
      digitalWrite(gpioD_LED3, LED_OFF);
      
      digitalWrite(gpioE_LED1, LED_OFF);
      digitalWrite(gpioE_LED2, LED_OFF);
      digitalWrite(gpioE_LED3, LED_OFF);

      setStatus = 0;
      Serial1.print(strRESET);   

      delay(500);
      while(digitalRead(gpio_set)==GPIO_PRESS);
  }
  else if((digitalRead(gpio_set)==GPIO_PRESS)&&(setStatus==0)&&((led_A==0)||(led_B==0)||(led_C==0)||(led_D==0)||(led_E==0)))
  {
    //Serial.println("Set Button");

    //複查答案內容, 應不可等於0
    //for(i=0;i<5;i++)
    //{
      //Serial.println(answerBuf[i]);   
   // }
        
    digitalWrite(gpio_set_LED, LED_ON);
    delay(100);
    digitalWrite(gpio_set_LED, LED_OFF);
    delay(100);
    digitalWrite(gpio_set_LED, LED_ON);
    delay(100);
    digitalWrite(gpio_set_LED, LED_OFF);
    delay(100);
    digitalWrite(gpio_set_LED, LED_ON);
    delay(100);
    digitalWrite(gpio_set_LED, LED_OFF);          
     
  }

  //Serial.println("TEST1"); 
  
}
