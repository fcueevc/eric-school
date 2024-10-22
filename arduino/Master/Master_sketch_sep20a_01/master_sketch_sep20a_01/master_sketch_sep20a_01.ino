// 按鍵掃描程式
// --------------------------------------------------------
// Reference: https://swf.com.tw/?p=917 

#include <Keypad.h>    // 引用Keypad程式庫

#define KEY_ROWS 4     // 按鍵模組的列數
#define KEY_COLS 4     // 按鍵模組的行數

// 依照行、列排列的按鍵字元（二維陣列）
char keymap[KEY_ROWS][KEY_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte colPins[KEY_COLS] = {9, 8, 7, 6};	   // 按鍵模組，行1~4接腳。
byte rowPins[KEY_ROWS] = {13, 12, 11, 10}; // 按鍵模組，列1~4接腳。

// 初始化Keypad物件
// 語法：Keypad(makeKeymap(按鍵字元的二維陣列), 模組列接腳, 模組行接腳, 模組列數, 模組行數)
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, KEY_ROWS, KEY_COLS);

// --------------------------------------------------------

// Pin define configuration
// 按鍵腳位
#define gpio_input1 2
#define gpio_input2 3 
#define gpio_input3 4 
#define gpio_input4 5 

#define gpio_set    15
#define gpio_reset  14

// 燈號腳位
#define gpio_led 1 

const int detectDelay   = 200;     // 按鍵偵測時間
int  detectTime         = 0;

// UART configuration
#define speed       115200 // bps
#define uart_delayTime   500   // Unit: ms
byte uart_string[10];
int  setStatus = 0;
unsigned int  leds = 0x0000;

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
  Serial.begin(speed);

  //set pins to output because they are addressed in the main loop
  pinMode(gpio_input1, INPUT_PULLUP);
  pinMode(gpio_input2, INPUT_PULLUP);
  pinMode(gpio_input3, INPUT_PULLUP);
  pinMode(gpio_input4, INPUT_PULLUP);

  pinMode(gpio_set, INPUT_PULLUP);
  pinMode(gpio_reset, INPUT_PULLUP);

  // 設定燈號, 預設皆為OFF
  pinMode(gpio_led, OUTPUT);
  digitalWrite(gpio_led, HIGH);

  Serial.print(strRESET);
}

void loop() {
  
  char i;
/*
  // 設定答案
  while(digitalRead(gpio_input1)==LOW)
  {
     delay(detectDelay);
     detectTime++;

     if(detectTime>5)   // 超過1秒
     {
         answerBuf[0] = 1;
     }
  }

  detectTime = 0;
  
  // Set腳位偵測
  while(digitalRead(gpio_set)==LOW)
  {
    
     delay(detectDelay);
     detectTime++;

     if(detectTime>15)   // 超過3秒
     {
        setStatus = !setStatus;
        
        if(setStatus==1)
        {
          Serial.println("Set and lock");
          digitalWrite(gpio_led, LOW);
        }   
        else
        {
          Serial.println("unlock");
          digitalWrite(gpio_led, HIGH);
        }
        break;
      }
  }

  detectTime = 0;
  
  // Reset腳位偵測
  while(digitalRead(gpio_reset)==LOW)
  {
    delay(detectDelay);
    detectTime++;

    if(detectTime>15)   // 超過3秒
    {
       Serial.print(strRESET);
       break;
    }
  }

  detectTime = 0;
 */ 

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

  // 透過Keypad物件的getKey()方法讀取按鍵的字元
  char key = myKeypad.getKey();

  if ((key=='1'||key=='2'||key=='3')&&(setStatus==0)){  // 若有按鍵被按下…
    
    leds = leds & 0x7FF8;    // Clear led

    if(key=='1')
    {
      answerBuf[0] = 1;  
      leds = leds | 0x0001;
    }
    else if(key=='2')
    {
      answerBuf[0] = 2;
      leds = leds | 0x0002;
    }
    else if(key=='3')
    {
      answerBuf[0] = 3;
      leds = leds | 0x0004;
    }
    Serial.println(answerBuf[0]);  // 顯示按鍵的字元
    LED_control(leds);  // 顯示按鍵的字元
  }
  else if ((key=='4'||key=='5'||key=='6')&&(setStatus==0)){  // 若有按鍵被按下…
    
    leds = leds & 0x7FC7;    // Clear led

    if(key=='4')
    {
      answerBuf[1] = 1;  
      leds = leds | 0x0008;
    }
    else if(key=='5')
    {
      answerBuf[1] = 2;
      leds = leds | 0x0010;
    }
    else if(key=='6')
    {
      answerBuf[1] = 3;
      leds = leds | 0x0020;
    }
    Serial.println(answerBuf[1]);  // 顯示按鍵的字元
    LED_control(leds);  // 顯示按鍵的字元
  }
  else if ((key=='7'||key=='8'||key=='9')&&(setStatus==0)){  // 若有按鍵被按下…
    
    leds = leds & 0x7E3F;    // Clear led

    if(key=='7')
    {
      answerBuf[2] = 1;  
      leds = leds | 0x0040;
    }
    else if(key=='8')
    {
      answerBuf[2] = 2;
      leds = leds | 0x0080;
    }
    else if(key=='9')
    {
      answerBuf[2] = 3;
      leds = leds | 0x0100;
    }
    Serial.println(answerBuf[2]);  // 顯示按鍵的字元
    LED_control(leds);  // 顯示按鍵的字元
  }
  else if ((key=='*'||key=='0'||key=='#')&&(setStatus==0)){  // 若有按鍵被按下…
    
    leds = leds & 0x71FF;    // Clear led

    if(key=='*')
    {
      answerBuf[3] = 1;  
      leds = leds | 0x0200;
    }
    else if(key=='0')
    {
      answerBuf[3] = 2;
      leds = leds | 0x0400;
    }
    else if(key=='#')
    {
      answerBuf[3] = 3;
      leds = leds | 0x0800;
    }
    Serial.println(answerBuf[3]);  // 顯示按鍵的字元
    LED_control(leds);  // 顯示按鍵的字元
  }
  else if ((key=='A'||key=='B'||key=='C')&&(setStatus==0)){  // 若有按鍵被按下…
    
    leds = leds & 0x0FFF;    // Clear led

    if(key=='A')
    {
      answerBuf[4] = 1;  
      leds = leds | 0x1000;
    }
    else if(key=='B')
    {
      answerBuf[4] = 2;
      leds = leds | 0x2000;
    }
    else if(key=='C')
    {
      answerBuf[4] = 3;
      leds = leds | 0x4000;
    }
    Serial.println(answerBuf[4]);  // 顯示按鍵的字元
    LED_control(leds);  // 顯示按鍵的字元
  }
  
  // 設定
  if(key=='D')
  {
    key = 0;
    
    if(setStatus==0)                // 設定答案 lock
    {
      for(i=0;i<5;i++)
      {
        answer[i] = answerBuf[i];
        Serial.println(answer[i]);
      } 

      setStatus = 1;
      Serial.println("Lock");
      leds = leds & 0x7FFF; 

      for(i=0;i<5;i++)
      {
        if(answer[i]==0)
          setStatus = 0;
      }
    }
    else
    {
      for(i=0;i<5;i++)            // 解鎖 unlock 
      {
        answerBuf[i] = 0;
        answer[i] = 0;
      }

      setStatus = 0;
      Serial.print(strRESET);
      leds = leds & 0x0000;
      leds = leds | 0x8000; 
    }

    LED_control(leds);  
  }
  
}

void LED_control(unsigned int leds)
{
    Serial.println(leds);  // 顯示按鍵的字元
}
