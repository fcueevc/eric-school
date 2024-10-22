// Pin define configuration
// 按鍵腳位
#define gpio_input1 8
#define gpio_input2 9 
#define gpio_input3 10 
#define gpio_input4 11 

#define gpio_set    15
#define gpio_reset  14

// 燈號腳位
#define gpio_led 13 

const int detectDelay   = 200;     // 按鍵偵測時間
int  detectTime         = 0;

// UART configuration
#define speed       115200 // bps
#define uart_delayTime   500   // Unit: ms
byte uart_string[10];
int  setStatus = 0;

// 答案
byte answerBuf[5];
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

  answerBuf[0] = 2;
  answerBuf[1] = 1;
  answerBuf[2] = 1;
  answerBuf[3] = 3;
  answerBuf[4] = 2;

  Serial.print(strRESET);

}

void loop() {
  
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
}
