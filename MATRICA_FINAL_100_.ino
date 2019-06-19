
#include "PxMatrix.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <Hash.h>
#include "GyverButton.h"
#include "secret.h"

#include <Ticker.h>

#define ELEMENTS(x)   (sizeof(x) / sizeof(x[0]))

Ticker display_ticker;

#define P_LAT 16
#define P_A 5
#define P_B 4
#define P_C 15
#define P_OE 2
#define P_D 12
//#define P_E 0


//PxMATRIX display(64,32,P_LAT, P_OE,P_A,P_B,P_C,P_D);
PxMATRIX display(64,64,P_LAT, P_OE,P_A,P_B,P_C,P_D);

//PxMATRIX display(64, 32, P_LAT, P_OE, P_A, P_B, P_C, P_D, P_E);

//------- Replace the following! ------
char ssid[] = WIFI_NAME;       // your network SSID (name)
char password[] = WIFI_PASS;  // your network key

WebSocketsServer webSocket = WebSocketsServer(81);


char textStr[] = "Hello, World!!!";
char textStr1[] = "LUKE, I AM YOUR FATHER!";
 //char STR[] = "Hello!!!!!";
 //char textStr[] = "Hello, World!";
int textX = display.width();
int textMin = sizeof(textStr) * -12;
unsigned long var = 0;
unsigned long var1 = 0;
unsigned long var2 = 0;
int k =0;


uint16_t myRED = display.color565(255, 0, 0);
uint16_t myGREEN = display.color565(0, 255, 0);
uint16_t myBLUE = display.color565(0, 0, 255);
uint16_t myWHITE = display.color565(255, 255, 255);
uint16_t myYELLOW = display.color565(255, 255, 0);
uint16_t myCYAN = display.color565(0, 255, 255);
uint16_t myMAGENTA = display.color565(255, 0, 255);
uint16_t myBLACK = display.color565(0, 0, 0);

uint16 myCOLORS[8] = {myRED, myGREEN, myBLUE, myWHITE, myYELLOW, myCYAN, myMAGENTA, myBLACK};


GButton Button1 (0, HIGH_PULL, NORM_OPEN);

void(* resetFunc) (void) = 0; // Reset MC function

void display_updater()
{

  display.display(60);

}
void clearDisplay(){
  for(int i = 0; i < 64; i++){
    for(int j = 0; j < 32; j++){
      display.drawPixel(i , j, 0x0000);
    }
  }
}

void setup()
{
  Serial.begin(115200);
  display.begin(16);
  display_ticker.attach(0.002, display_updater);
  yield();
  Button1.setTickMode(AUTO);


  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
   
  //randomSeed();
  display.setTextWrap(false);  // отключаем перенос текста на следующую строку
  display.setTextSize(1); // устанавливаем размер текста


  startFunc();
}

void loop()
{
  Button1.tick();
   if (Button1.isHolded()){ 
    Serial.println("B1 Holded");
      startFunc();
   }
  if (Button1.hasClicks()){
    byte clicks = Button1.getClicks();
    switch(clicks) {  
      case 1: Serial.println("B1 click");
        do {
          if (Button1.isHolded()){ 
    break;
           }
          var++;
      runningString();
        } while ( var != 0);
      startFunc();
    break;

    case 2: Serial.println("B1 2clicks");
    
    do {
      if (Button1.isHolded()){ 
    break;
           }
      var1++;
      runningString1();
        } while ( var1 != 0);
        startFunc();   
    break;

    case 3: Serial.println("B1 3clicks");
    drawImage(16,0);
    break;

    case 4: Serial.println("B1 4clicks");
    drawMario(0,0);
    break;

    case 5: Serial.println("B1 5clicks"); 
    clearDisplay();
    do {
      if (Button1.isHolded()){ 
    break;
      }
      var2++;
      webSocket.loop();
    } while (var2 != 0);
    startFunc();
    break;
  }
 }
}


int startFunc(){
   display.clearDisplay();
  // выставляем курсор (10,0)
  display.setCursor(0, 0);
  // печатаем первую строку
  display.println("Platonov");
  display.setCursor(26, 9);
  display.println("KS-41");
  // выставляем курсор
  display.setCursor(0, 20);
  // выводимая вторая строка
  char strText[] = "LED MATRIX!";
  // перебираем по очереди каждый символ
  for (int i = 0; i < strlen(strText); i++) {
    // генерируем случайное число от 0 до 1536
    int hue = random(0, 255);
    int hue1 = random(0, 255);
    int hue2 = random(0, 255);
    // устанавливаем случайный цвет по шкале «HSV»
    display.setTextColor(display.color565(hue, hue1, hue2));
    // печатаем символ текущего цикла
    display.print(strText[i]);
  }
  display.swapBuffers();
}
