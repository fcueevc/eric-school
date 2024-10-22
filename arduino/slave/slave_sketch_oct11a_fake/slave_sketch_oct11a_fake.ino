// Pin define configuration
#define gpio_input1 5 
#define gpio_input2 6 
#define gpio_input3 7 
#define gpio_set 8

#define gpio_led1 9 
#define gpio_led2 10 
#define gpio_led3 11 
#define gpio_led4 12

#define gpio_K1 2 
#define gpio_K2 3 
#define gpio_K3 4 
#define gpio_K4 13

#define LED_ON   HIGH
#define LED_OFF  LOW

#define K_ON   HIGH
#define K_OFF  LOW

#define GPIO_PRESS LOW

// UART configuration
#define speed       115200
#define uart_delayTime   500   // Unit: ms

int val1, val2, val3;
byte leds =0;
byte set_flag=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(gpio_input1, INPUT_PULLUP);
  pinMode(gpio_input2, INPUT_PULLUP);
  pinMode(gpio_input3, INPUT_PULLUP);

  pinMode(gpio_set, INPUT_PULLUP);

  pinMode(gpio_led1, OUTPUT);
  pinMode(gpio_led2, OUTPUT);
  pinMode(gpio_led3, OUTPUT);
  pinMode(gpio_led4, OUTPUT);
  
  pinMode(gpio_K1, OUTPUT);
  pinMode(gpio_K2, OUTPUT);
  pinMode(gpio_K3, OUTPUT);
  pinMode(gpio_K4, OUTPUT);
  
  digitalWrite(gpio_led1, LED_OFF);    // 開機設定為LOW
  digitalWrite(gpio_led2, LED_OFF);    // 開機設定為LOW
  digitalWrite(gpio_led3, LED_OFF);    // 開機設定為LOW
  digitalWrite(gpio_led4, LED_OFF);    // 開機設定為LOW
  
  digitalWrite(gpio_K1, K_OFF);    // 開機設定為LOW
  digitalWrite(gpio_K2, K_OFF);    // 開機設定為LOW
  digitalWrite(gpio_K3, K_OFF);    // 開機設定為LOW
  digitalWrite(gpio_K4, K_OFF);    // 開機設定為LOW
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if((digitalRead(gpio_input1)==GPIO_PRESS)&&(leds!=1)&&(set_flag==0))
  {
     leds = 1;
     digitalWrite(gpio_led1, LED_ON);
     digitalWrite(gpio_led2, LED_OFF);
     digitalWrite(gpio_led3, LED_OFF);

     while(digitalRead(gpio_input1)==GPIO_PRESS);
  }

  if((digitalRead(gpio_input2)==GPIO_PRESS)&&(leds!=2)&&(set_flag==0))
  {
     leds = 2;
     digitalWrite(gpio_led1, LED_OFF);
     digitalWrite(gpio_led2, LED_ON);
     digitalWrite(gpio_led3, LED_OFF);
     while(digitalRead(gpio_input2)==GPIO_PRESS);
  }

  if((digitalRead(gpio_input3)==GPIO_PRESS)&&(leds!=3)&&(set_flag==0))
  {
     leds = 3;
     digitalWrite(gpio_led1, LED_OFF);
     digitalWrite(gpio_led2, LED_OFF);
     digitalWrite(gpio_led3, LED_ON);
     while(digitalRead(gpio_input3)==GPIO_PRESS);
  }

  if((digitalRead(gpio_set)==GPIO_PRESS)&&(set_flag==0))
  {
     set_flag=1;
     digitalWrite(gpio_led4, LED_ON);
     digitalWrite(gpio_K4,K_ON);
     delay(500);
     digitalWrite(gpio_led4, LED_OFF);  // For Test
     digitalWrite(gpio_K4,K_OFF);
     while(digitalRead(gpio_set)==GPIO_PRESS);
     delay(100);
  }
  else if((digitalRead(gpio_set)==GPIO_PRESS)&&(set_flag==1))
  {
     set_flag=0;
     leds = 0;

     digitalWrite(gpio_led1, LED_OFF);
     digitalWrite(gpio_led2, LED_OFF);
     digitalWrite(gpio_led3, LED_OFF);
     digitalWrite(gpio_led4, LED_OFF);   
     delay(500);
     while(digitalRead(gpio_set)==GPIO_PRESS);
     delay(100);
  }
}
