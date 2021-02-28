#include "Magnetometer_Autocal.h"
#define DECPOINTS 5
MAGAC model= MAGAC();

float corrData[3]; //Variable to hold corrected data

void setup() {
  Serial.begin(115200);
  model.begin();
  
  //If you have a pre-trained model, you can initialize the parameters after calling model.begin().
  //model.setOffset()
  //model.setBias()
}

void loop() {
  //#CodeNeeded
  //Read most recent values from hardware into a three-element array.
  float rawData[]={20.76537, 10.92914, 60.09272};  //This is just some dummy data

  model.update(rawData);
  model.read(corrData);
  
  Serial.print(rawData[0],DECPOINTS);Serial.print("\t");
  Serial.print(rawData[1],DECPOINTS);Serial.print("\t");
  Serial.print(rawData[2],DECPOINTS);Serial.print("\t");
  Serial.print(corrData[0],DECPOINTS);Serial.print("\t");
  Serial.print(corrData[1],DECPOINTS);Serial.print("\t");
  Serial.print(corrData[2],DECPOINTS);Serial.println("");
  
  delay(10);
}
