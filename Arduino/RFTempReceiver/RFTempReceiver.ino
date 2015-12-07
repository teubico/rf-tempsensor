#include <RH_ASK.h>
#include <SPI.h>
#define BUFF_SIZE 3
#define RX_PIN 6
/* Quita el comentario para habilitar la salida a LCD 16x2 */
//#define ENABLE_LCD
#define ENABLE_SERIAL
#ifdef ENABLE_LCD
#include <LiquidCrystal.h>
#endif

int8_t data[BUFF_SIZE];
uint8_t buffsize = BUFF_SIZE*sizeof(int8_t);

RH_ASK driver;

#ifdef ENABLE_LCD
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
#endif

void setup() {
#ifdef ENABLE_LCD
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Esperando datos");
#endif

#ifdef ENABLE_SERIAL
  Serial.begin(9600);
  if(!driver.init())
    Serial.println("init failed");
#else
  driver.init();
#endif

}

void loop() {
  /*
   * Esperar por datos del enlace inalambrico.
   */
  if(driver.recv((uint8_t*)data,&buffsize)) {
    /*
     * Imprimir estado según estatus del DHT11
     */
    switch(data[0]) {
      case 0:
#ifdef ENABLE_LCD
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("TMP: ");
        lcd.print(data[1], DEC);
        lcd.setCursor(0,1);
        lcd.print("HUM: ");
        lcd.print(data[2], DEC);
#endif
#ifdef ENABLE_SERIAL
        Serial.print("TMP: ");
        Serial.println(data[1], DEC);
        Serial.print("HUM: ");
        Serial.println(data[2], DEC);
#endif
        break;
      case -1:
#ifdef ENABLE_LCD
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ERR CHKSUM");
#endif
#ifdef ENABLE_SERIAL
        Serial.println("ERR CHKSUM");
#endif
        break;
      case -2:
#ifdef ENABLE_LCD
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ERR TIMEOUT");
#endif
#ifdef ENABLE_SERIAL
        Serial.println("ERR TIMEOUT");
#endif
        break;
      default:
#ifdef ENABLE_LCD
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("WRNG PAKT");
#endif
#ifdef ENABLE_SERIAL
        Serial.println("WRNG PAKT");
#endif
    }
  }
}

