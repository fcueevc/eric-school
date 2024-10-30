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
#define slaveID  1     

const int detectDelay   = 200;     // 按鍵偵測時間
int  detectTime         = 0;

// UART configuration
#define speed       115200 // bps
#define uart_delayTime   500   // Unit: ms
byte uart_string[10];
int  setStatus = 0;

// 答案
byte answerBuf = 1;
String strRQA = "AT+RQA(";
String strOK = "OK+(";
String strTemp = "";
String strEND = ")\r";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(speed);

  //set pins to output because they are addressed in the main loop
  pinMode(gpio_input1, INPUT_PULLUP);
  pinMode(gpio_input2, INPUT_PULLUP);
  pinMode(gpio_input3, INPUT_PULLUP);
  pinMode(gpio_input4, INPUT_PULLUP);

  pinMode(gpio_set, INPUT_PULLUP);

  // 設定燈號, 預設皆為OFF
  pinMode(gpio_led, OUTPUT);
  digitalWrite(gpio_led, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
   // 選擇答案
  while(digitalRead(gpio_input1)==LOW)
  {
     delay(detectDelay);
     detectTime++;

     if(detectTime>5)   // 超過1秒
     {
        answerBuf = 2;
        break;
     }
  }

  detectTime = 0;

  // Set腳位偵測
  while(digitalRead(gpio_set)==LOW)
  {
     delay(detectDelay);
     detectTime++;

     if(detectTime>10)   // 超過2秒
     {        
        strTemp = strRQA + slaveID + strEND;
        Serial.print(strTemp);
        digitalWrite(gpio_led, LOW);
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
      //teststr.trim();

      strTemp = strOK + "1," + answerBuf + strEND;

      // 比對答案
      if(teststr==strTemp)
      {
        Serial.println("OK");
      }
      else
      {
        Serial.println("NG");
      }

      Serial.print(strTemp);
  }

}
