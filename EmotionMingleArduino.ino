#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

//Inicializa el neopixel de la barra del arbol
Adafruit_NeoPixel stripBarra = Adafruit_NeoPixel(10, 4, NEO_GRB + NEO_KHZ800);

//Hojas
/*
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(4, 12, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(4, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(4, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(4, 11, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(4, 7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip6 = Adafruit_NeoPixel(4, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip7 = Adafruit_NeoPixel(4, 8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip8 = Adafruit_NeoPixel(4, 10, NEO_GRB + NEO_KHZ800);
*/

//Hojas
//Inicializa los neopixeles de las hojas del arbol
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(4, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(4, 11, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(4, 10, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(4, 12, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(4, 8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip6 = Adafruit_NeoPixel(4, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip7 = Adafruit_NeoPixel(4, 7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip8 = Adafruit_NeoPixel(4, 5, NEO_GRB + NEO_KHZ800);



//Inicializa la comunicacion serial para lograr la comunicacion con Gadgeteer
//Se utiliza los puertos 0 y 1 para establecer la comunicacion
SoftwareSerial mySerial(0, 1); // RX, TX

char inData[1000];
int index = 0;
//String inData = "";

//Inicializa un NeoPixel dejando los leds en off
void init(Adafruit_NeoPixel *strip)
{
  strip->begin();
  strip->show(); // Initialize all pixels to 'off'

}

//Recorre todos los leds del strip dado apagando cada uno de ellos
void turnOff(Adafruit_NeoPixel *strip){

  for(int i=0; i<strip->numPixels(); i++){
    strip->setPixelColor(i, 0);
  }

  //Muestra los colores fijados para este strip
  strip->show();

}

//Fija los primeros num_leds_on leds del strip usando el colo dado, el resto de los leds se apaga
void show(Adafruit_NeoPixel *strip, int num_leds_on, int color){

  for(int i=0; i<num_leds_on; i++){
    strip->setPixelColor(i, color);
  }

  for(int i=num_leds_on; i<strip->numPixels(); i++){
    strip->setPixelColor(i, 0);
  }

  strip->show();

}

//Genera un promedio de las emociones positivas y negativas para luego mostrar en la barra los porcentajes asociados
void scaleBar(Adafruit_NeoPixel *strip, int sad, int tired, int stressed, int angry, int happy, int energetic, int relaxed, int calmed)
{
  //Se obtiene la suma de las emociones positivas
  int totalPositivas = happy + energetic + relaxed + calmed;
  //Se obtiene la suma de las emociones negativas
  int totalNegativas = sad + tired + stressed + angry;

  int total = totalPositivas + totalNegativas;

  int ledAzules = (totalNegativas * 10)/total;
  int ledVerdes = strip->numPixels() - ledAzules;

  for(int i=0; i<ledVerdes; i++){
    strip->setPixelColor(i, strip->Color(0, 0, 255));
  }

  for(int i=ledVerdes; i<strip->numPixels(); i++){
    strip->setPixelColor(i, strip->Color(255, 128, 0));
  }

  strip->show();


}

//Define el color de una hoja de acuerdo al valor que se quiera representar
// Si el valor es menor que 2, el strip es blanco
// Si es menor que 4, es Naranjo
// Si es menor que 10, es Amarillo
// En cualquier otro caso, el color es verde
void scale(Adafruit_NeoPixel *strip, int value){

  if(value < 2){
    //Blanco no hay interaccion
    show(strip, 4, strip->Color(255, 255, 255));
  }
  else if(value < 4){
    //Naranjo 
    show(strip, 4, strip->Color(255, 128, 0));
  }
  else if(value < 10){
    //Amarillo
    show(strip, 4, strip->Color(255, 255, 0));
  }
  else{
    //Verde
    show(strip, 4, strip->Color(0, 100, 0));
  }

}


//Este metodo se llama al inicio de la ejecucion de Arduino
void setup() 
{
  //Se inicializa la comunicacion serial con la consola serial del software Arduino
  Serial.begin(9600);   

  Serial.println("Arduino Setup!!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);

  //Se inicializa la barra apagando los leds
  init(&stripBarra);

  //Se inicializan las hojas apagando los leds
  init(&strip1);
  init(&strip2);
  init(&strip3);
  init(&strip4);
  init(&strip5);
  init(&strip6);
  init(&strip7);
  init(&strip8);
  
  

}

//Esta funcion se llama de forma repetitiva 
void loop() 
{

  //Si hay data por leer la entrada serial la consumo hasta encontrar un caracter newline
  if (mySerial.available())
  {
    char in = mySerial.read();

    Serial.println(in);

    inData[index] = in;
    index++;

    if(in == '\n')
    {
      Serial.println(inData);

      char* operation;

      operation = strtok(inData,":");

      //De acuerdo al valor de operacion se decide si la operacion corresponde a una hoja, barra o off
      if (strcmp(operation, "hoja") == 0 )
      {

        int numHoja = atoi(strtok(NULL, ":"));
        int potenciaHoja = atoi(strtok(NULL, "\n"));
        
        //Se fija la potencia de la hoja numHoja
        switch(numHoja)
        {
        case 1:
          scale(&strip1, potenciaHoja);
          break;
        case 2:
          scale(&strip2, potenciaHoja);
          break;
        case 3:
          scale(&strip3, potenciaHoja);
          break;
        case 4:
          scale(&strip4, potenciaHoja);
          break;
        case 5:
          scale(&strip5, potenciaHoja);
          break;
        case 6:
          scale(&strip6, potenciaHoja);
          break;
        case 7:
          scale(&strip7, potenciaHoja);
          break;
        case 8:
          scale(&strip8, potenciaHoja);
          break;  

        }

      }
      else if (strcmp(operation, "barra") == 0)
      {
        //Se obtienen los valores a mostrar en la barra
        int sad = atoi(strtok(NULL, ":"));
        int tired = atoi(strtok(NULL, ":"));
        int stressed = atoi(strtok(NULL, ":"));
        int angry = atoi(strtok(NULL, ":"));
        int happy = atoi(strtok(NULL, ":"));
        int energetic = atoi(strtok(NULL, ":"));
        int relaxed = atoi(strtok(NULL, ":"));
        int calmed = atoi(strtok(NULL, "\n"));

        scaleBar(&stripBarra, sad, tired, stressed, angry, happy, energetic, relaxed, calmed);             


      }
      else if (strcmp(operation, "off") == 0)
      {
        //Si la operacion es off, se apagan las hojas y barra
        turnOff(&strip1);
        turnOff(&strip2);
        turnOff(&strip3);
        turnOff(&strip4);
        turnOff(&strip5);
        turnOff(&strip6);
        turnOff(&strip7);
        turnOff(&strip8);

        turnOff(&stripBarra);        

      }

      Serial.println(operation);
      //Serial.println(cmd[1]);
      //Serial.println(cmd[2]);

      index = 0;
      inData[0] = '\0';

    }

  }  


}









