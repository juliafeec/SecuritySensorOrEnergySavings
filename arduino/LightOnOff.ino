/*
  Hello World.ino
  2013 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:Loovee
  2013-9-18

  Grove - Serial LCD RGB Backlight demo.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <string.h>

// Define the pin to which the temperature sensor is connected.
const int pinTemp = A0;

//Botao
const int pinButton = 3;

//Led
const int pinLed    = 13;

//Sensor 1
const int sensorEntrada  = 2;

//Sensor 1
const int sensorSaida  = 4;


int contaSensorEntrada = 0;
int contaSensorSaida = 0;

//Estado Luz
int luzOn=0;

// Define the B-value of the thermistor.
// This value is a property of the thermistor used in the Grove - Temperature Sensor,
// and used to convert from the analog value it measures and a temperature value.
const int B = 3975;


void inicializaSensorTemperatura() {
    //Inicializa sensor temperatura
    Serial.begin(9600);    
}
void inicializaLed() {
    // Configure the LED's pin for output.
    pinMode(pinLed, OUTPUT);
}

void inicializaButton() {
  //Inicializa touch button
    pinMode(pinButton, INPUT);
}

void inicializaSensores() {
  //Inicializa touch button
  pinMode(sensorEntrada, INPUT);
  pinMode(sensorSaida, INPUT);    
}

void setup() 
{
  inicializaSensorTemperatura();
  inicializaLed();
  inicializaButton();
  inicializaSensores();
  system("rm ~/arduino_comm");
}

void ligaLuz() {

}

float obterTemperatura() {
    // Get the (raw) value of the temperature sensor.
    int val = analogRead(pinTemp);

    // Determine the current resistance of the thermistor based on the sensor value.
    float resistance = (float)(1023-val)*10000/val;

    // Calculate the temperature based on the resistance value.
    return 1/(log(resistance/10000)/B+1/298.15)-273.15;
}


void enviaDados(int luz, int pessoas, float temp) {
  if (luz) {
    system("printf \"luz_on\n\" >> ~/arduino_comm");
  } else {
    system("printf \"luz_off\n\" >> ~/arduino_comm");  
  }

  char msg1[100];
  char msg2[100];

  sprintf(msg1,"printf \"pessoas_%d\n\" >> ~/arduino_comm\0",pessoas);
  
  
  system(msg1);

  sprintf(msg2,"printf \"temperatura_%f\n\" >> ~/arduino_comm\0",temp);

  system(msg2);  
}

void loop() 
{
    int estadoSensorEntrada = digitalRead(sensorEntrada);
    int estadoSensorSaida = digitalRead(sensorSaida);

    Serial.println("Estado Sensores");
    Serial.print(estadoSensorEntrada);
    Serial.print(" - ");
    Serial.println(estadoSensorSaida);   

    if (estadoSensorEntrada == 0) {
      contaSensorEntrada++;
    }

    Serial.print("Temperatura: ");
    Serial.print(obterTemperatura());

    Serial.print("Entrada: ");
    float temperatura = obterTemperatura();
    Serial.print(temperatura);

    int valor = digitalRead(pinButton);
    delay(250);

   Serial.print("Pessoas: ");
   Serial.print(contaSensorEntrada);

    luzOn = contaSensorEntrada % 2;

   
    Serial.print("Luz: ");
    Serial.println(luzOn);      

    if (luzOn) {
      digitalWrite(pinLed, HIGH); 
    } else {
      digitalWrite(pinLed, LOW); 
    }

    enviaDados(luzOn, contaSensorEntrada/2, temperatura);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
