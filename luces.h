//Definimos la posición de los leds
#define LED_BLANCO 8
#define LED_VERDE 9
#define LED_AMARILLO 10 
#define LED_ROJO 11
#define LED_AZUL 12



void apagar(int pin)
{//Al ser circuito con lógica negativa para apagarlo
  //se pone a HIGH el pin
  digitalWrite(pin,HIGH);
}

void configurarLuces()
{
  //Estamos usando lógica negativa para la conexión de los LEDS
  pinMode(LED_BLANCO,OUTPUT);
  pinMode(LED_VERDE,OUTPUT);
  pinMode(LED_AMARILLO,OUTPUT);
  pinMode(LED_ROJO,OUTPUT);
  pinMode(LED_AZUL,OUTPUT);
  //Al ser circuito con lógica negativa  para apagarlo se pone en mod HIGH
  apagar(LED_BLANCO);
  apagar(LED_VERDE);
  apagar(LED_AMARILLO);
  apagar(LED_ROJO);
  apagar(LED_AZUL);
}



void switchLed(int pin)
{//Conmuta el LED encendido/apagado
  digitalWrite(pin,!digitalRead(pin));
}

