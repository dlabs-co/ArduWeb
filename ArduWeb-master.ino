#include <SoftwareSerial.h>

#define RXPIN 2
#define TXPIN 3
#define LEDPIN 13

#define dbg Serial

SoftwareSerial wifiSerial(RXPIN,TXPIN);

#include "wifi.h"
#include "webServer.h"
#include "luces.h"


void setup() 
{
  Serial.begin(9600);
  wifiSerial.begin(9600);

  configurarWifi(comandosAT,10000);
  configurarLuces();
}

#define BUFFER_SIZE 64
char buffer[BUFFER_SIZE]={};

bool cargar = true;

void loop() 
{
  int8_t chId;
  int16_t packetLen;
  char c;
  int i=0;
  float tiempo;  
  //comprobamos si hay datos disponibles 
  if (wifiSerial.available())
  {
    //Leemos en modo carácter
    c= wifiSerial.read();
    while(c!='\n')//mientras el caracter no sea un final de carro
    {
      if (c >32 && c<126)//El carácter ASCII esta entre el "espacio" y la "~"
      {
        buffer[i]=c;//lo añadimos a nuestros datos recibidos
        i++;
      }
      c=wifiSerial.read();//continuamos leyendo
      
    }
    buffer[i]='\0';//añadimos un cero terminador a nuestra cadena
    Serial.println(buffer);//Nos muestra el buffer recibido
  }
  if  (strncmp(buffer,"+IPD,",5)==0)//Comprobamos que el mensaje recibido que nos interesa es el de la página web
  {
    sscanf(buffer+5,"%dm%d",&chId,&packetLen);//Sacamos el identificador de mensaje
    Serial.println("ID:"+String(chId)+":"+String(packetLen)); //Mostramos la comunicación y el tamaño
     String strAux=String(buffer);
     Serial.println("STR_AUX:"+strAux);
     if (strAux.indexOf("blanco")!=-1) 
     {
      switchLed(LED_BLANCO); //Enciende o apaga
     }
     if (strAux.indexOf("verde")!=-1)
     {
      switchLed(LED_VERDE);
     }
     if (strAux.indexOf("amarillo")!=-1)
     {
      switchLed(LED_AMARILLO);
     }
     if (strAux.indexOf("rojo")!=-1)
     {
      switchLed(LED_ROJO);
     }
     if (strAux.indexOf("azul")!=-1)
     {
      switchLed(LED_AZUL);
     }
     rx_empty();//vacia el buffer de datos que no, nos interesan
     webServer(chId); //muestra la página web.
  }
}
