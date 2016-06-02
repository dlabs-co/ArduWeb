//Comandos at para la conexión de la wifi
String comandosAT[]={
  "AT",
  "AT+CWMODE=1",
  "AT+CWJAP=\"mi_SSID\",\"MI_PASSWORD\"",
  "AT+CIPSTA=\"192.168.1.30\",\"191.168.1.1.\",\"255.255.255.0\"",//Poner la IP en el dispositivo
  "AT+CIFSR",//Comprobar la IP
  "AT+CIPMUX=1",//Poner en modo servidor
  "AT+CIPSERVER=1,80",//Crear el servidor
  "AT+CIPSTO=5",//Timeout
 "END"

};


String getLineWifi()
{
  String s;
  if (wifiSerial.available())
  {
    char c= wifiSerial.read();
    while (c!='\n')
    {
      if (c>32 && c <126)//leer carácteres imprimibles de la tabla ASCII
      {
      s+=c;
      //delay(25);
      }
      c=wifiSerial.read();
    }
    return s;
  }
}


void rx_empty(void) 
{//función para vaciar el buffer de los comandos serie
    while(wifiSerial.available() > 0)
    {
        wifiSerial.read();
    }
}


int configurarWifi(String *ordenes,long timeOut)
{
  int i=0;
  while (ordenes[i]!="END")
  {
    rx_empty();
    wifiSerial.println(ordenes[i++]);
    long flag=millis();
    while (true)
    {
      String s= getLineWifi();
      if (s!="")Serial.println(s);
      if (s.startsWith("no change"))  {break;}
      if (s.startsWith("OK")){break;}
      if (s.startsWith("ready")){break;}
      if (s.startsWith("+CIFSR")){break;}
      if ((millis() - flag) > timeOut) //control del timeout
      {
        dbg.println("TIEMPO");
        break;   
      }
    }
    rx_empty();
    dbg.println("..........................");
  }
}

