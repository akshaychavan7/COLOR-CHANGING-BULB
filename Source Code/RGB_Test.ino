#include "Arduino.h"


String mainString;
byte redLed=9;
byte greenLed=10;
byte blueLed=11;

int sensorPin = 13; // select the input pin for LDR 
int sensorValue = 0; // variable to store the value coming from the sensor  
 
void setup()
{ 
  Serial.begin(9600);
}

void loop()
{
  sensorValue = analogRead(sensorPin); // read the value from the sensor 
  //Serial.println(sensorValue); //prints the values coming from the sensor on the screen
  if(sensorValue>=400)
  {
    Serial.print("LIGHTS OFF");  
  }
  if(sensorValue<400)          //if intensity of light is <400 ie. Threshold value
  {
      if(Serial.available()>0)                  //take input from bluetooth
      {
        mainString=Serial.readString();       //read input from bluetooth
    
        Serial.println("\n Simple String");
        Serial.println(mainString);
        
        //Reverse the input string
        int len = 0;
        while (mainString[len])
            len++;
    
        int down = 0;
        int up = len - 1;
    
        while (up > down)
        {
            char c = mainString[down];
            mainString[down++] = mainString[up];
            mainString[up--] = c;
        }
        
        Serial.println("\nReverse");
        Serial.println(mainString);
    
        
        
        //Split upto brackets
        byte firstBracketIndex = mainString.indexOf(')');
        byte secondBracketIndex = mainString.indexOf(')',firstBracketIndex +1);
        String colorsCode=mainString.substring(firstBracketIndex +1 ,secondBracketIndex);
        Serial.println("\nSplitted Part");
        Serial.println(colorsCode);
    
        //reverse the colorsCode
    
        //Reverse the input string
        len = 0;
        while (colorsCode[len])
            len++;
    
        down = 0;
        up = len - 1;
    
        while (up > down)
        {
           char c = colorsCode[down];
            colorsCode[down++] = colorsCode[up];
            colorsCode[up--] = c;
        }
    
    
    
    
        
        byte firstCommaIndex = colorsCode.indexOf('.');
        byte secondCommaIndex = colorsCode.indexOf('.',firstCommaIndex +1);
         String red=colorsCode.substring(0,firstCommaIndex);
        String green=colorsCode.substring(firstCommaIndex +1 ,secondCommaIndex);
        String blue=colorsCode.substring(secondCommaIndex +1);
    
        int r= red.toInt();
        int g= green.toInt();
        int b= blue.toInt();
        Serial.print("\nRed:");
        Serial.print(r,DEC);
        Serial.print("\nGreen:");
        Serial.print(g,DEC);
        Serial.print("\nBlue:");
        Serial.print(b,DEC);
      
        analogWrite(redLed,255-r);
        analogWrite(greenLed,255-g);
        analogWrite(blueLed,255-b);

      }
  }
}

