
//Enviar una instruccion http para generar nuestra página
//El envio se hace mediante el comando AT+CIPSEND = id_conexion,longitud_de_datos_a_enviar
//Esperar la respuesta de ">" envio y el "SEND OK" de envio correcto
//estos últimos dan un warning por un usar una comparación desaconsejada
void http(int ch_id, String output)
{
  wifiSerial.print("AT+CIPSEND=" + String(ch_id) + ",");
  wifiSerial.println(output.length());
  if (wifiSerial.find(">"))
  {
    wifiSerial.println(output);
    delay(10);
    while (wifiSerial.available() > 0)
    {
      if (wifiSerial.find("SEND OK"))break;
    }
  }
  else
  {
    dbg.println("no escrito");
  }
}

//Muestra la página web, lo que hace  es mandar la información para montar la página web
void webServer(int ch_id)
{//Nos crea el documento html
  http(ch_id, "<!DOCTYPE HTML>");
  http(ch_id, "<html>");
  http(ch_id, "<body><H1>Taller IOT- GAMAKER/Dlabs 2016</H1>");
  http(ch_id, "<head><title>www.dlabsZaragoza.com</title>");
  
  http(ch_id, "<form action=\"blanco\">");//definición del formulario 
  http(ch_id, "<input type=\"submit\" value=\"blanco\">");//creación de un botón con valor blanco
  http(ch_id, "</form>");
  
  http(ch_id, "<form action=\"verde\">");
  http(ch_id, "<input type=\"submit\" value=\"verde\">");
  http(ch_id, "</form>");

  http(ch_id, "<form action=\"amarillo\">");
  http(ch_id, "<input type=\"submit\" value=\"amarillo\">");
  http(ch_id, "</form>");
  
  http(ch_id, " <form action=\"rojo\">");
  http(ch_id, "<input type=\"submit\" value=\"rojo\">");
  http(ch_id, "</form>");
  
  http(ch_id, " <form action=\"azul\">");
  http(ch_id, "<input type=\"submit\" value=\"azul\">");
  http(ch_id, "</form>");
  http(ch_id, "</body>");//Cerrar la página
  delay(1);
  wifiSerial.println("AT+CIPCLOSE=" + String(ch_id));//cerrar la conexión para evitar dejar el wifi bloqueado y a la espera de timeout
}


