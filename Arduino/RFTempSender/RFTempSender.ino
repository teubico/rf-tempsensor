/*
 * Transmisor Wireless para el KIT del medidor
 * de temperatura y humedad programable para
 * arduino de TeUbi.co
 * 
 * Este transmisor lee los datos de temperatura
 * y humedad del sensor DHT11 y luego los envía
 * utilizando un enlace inalambrico sencillo
 * con modulación ASK.
 * 
 * El dato de salida se envía como un arreglo de
 * tres enteros con signo de la siguiente forma:
 * {RESULTADO, TEMPERATURA, HUMEDAD}
 * 
 * RESULTADO puede tomar los siguientes valores:
 *  0: Lectura exitosa.
 * -1: Error en la suma de verificación.
 * -2: Tiempo agotado.
 */

#include <RH_ASK.h>
#include "dht11.h"
#define TX_PIN PB0
#define DHT11PIN PB1
#define BUFF_SIZE 3

RH_ASK driver(2000,PB2,PB0);

dht11 DHT11;

int8_t data[BUFF_SIZE] = {0,0,0};

void setup() {
  driver.init();
}

void loop() {
  // Almacenar los valores en el arreglo
  data[0] = DHT11.read(DHT11PIN);
  data[1] = DHT11.temperature;
  data[2] = DHT11.humidity;
  // Se serializan los datos como un arreglo de enteros
  // sin signo y se convierte al tipo correcto en el
  // lado del receptor.
  driver.send((uint8_t*)data, BUFF_SIZE*sizeof(int8_t));
  delay(5000);
}
