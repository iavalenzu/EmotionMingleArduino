#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

//Barra
Adafruit_NeoPixel stripBarra = Adafruit_NeoPixel(10, 4, NEO_GRB + NEO_KHZ800);

//Hojas
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(4, 12, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(4, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(4, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(4, 11, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(4, 7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip6 = Adafruit_NeoPixel(4, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip7 = Adafruit_NeoPixel(4, 8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip8 = Adafruit_NeoPixel(4, 10, NEO_GRB + NEO_KHZ800);


SoftwareSerial mySerial(0, 1); // RX, TX

char inData[1000];
int index = 0;
//String inData = "";


void init(Adafruit_NeoPixel *strip)
{
  strip->begin();
  strip->show(); // Initialize all pixels to 'off'

}

void turnOff(Adafruit_NeoPixel *strip){

  for(int i=0; i<strip->numPixels(); i++){
    strip->setPixelColor(i, 0);
  }

  strip->show();

}

void show(Adafruit_NeoPixel *strip, int num_leds_on, int color){

  for(int i=0; i<num_leds_on; i++){
    strip->setPixelColor(i, color);
  }

  for(int i=num_leds_on; i<strip->numPixels(); i++){
    strip->setPixelColor(i, 0);
  }

  strip->show();

}

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
    strip->setPixelColor(i, strip->Color(0, 100, 0));
  }

  for(int i=ledVerdes; i<strip->numPixels(); i++){
    strip->setPixelColor(i, strip->Color(0, 0, 100));
  }

  strip->show();


}

void scale(Adafruit_NeoPixel *strip, int value){

  if(value < 2){
    //Blanco no hay interaccion
    show(strip, value, strip->Color(255, 255, 255));
  }
  else if(value < 4){
    //Naranjo 
    show(strip, value, strip->Color(255, 128, 0));
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



void setup() 
{
  Serial.begin(9600);   

  Serial.println("Arduino Setup!!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);


  init(&stripBarra);

  init(&strip1);
  init(&strip2);
  init(&strip3);
  init(&strip4);
  init(&strip5);
  init(&strip6);
  init(&strip7);
  init(&strip8);
  

}

void loop() 
{

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

      if (strcmp(operation, "hoja") == 0 )
      {

        int numHoja = atoi(strtok(NULL, ":"));
        int potenciaHoja = atoi(strtok(NULL, "\n"));

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









