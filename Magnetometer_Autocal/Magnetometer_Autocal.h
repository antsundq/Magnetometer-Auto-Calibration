/*
 * MIT License
 * Copyright (c) 2021 Anton Sundqvist
 */
#ifndef GD_AUTOCAL_H
#define GD_AUTOCAL_H
#include <arduino.h>
#define VECTOR_DIM 3

class MAGAC{
  private:
    const float learningRate = 0.002;   //Learning rate
    float m[VECTOR_DIM];                //Magnetic north vector
    float a[VECTOR_DIM];                //Bias distortion of the sensor
    float b[VECTOR_DIM];                //Offset of sensor reading from origo
    float xInvNorm = 1.0;               //Normalization factor, measured on first iteration
    bool firstIteration = true;
    short learn(float* rawData);
    short predict(float* rawData);
    float calcNorm(float* vec);
    
  public:
    MAGAC();
    short begin();
    short autoCal(float* data);         //High level function which updates and overwrites the input with the corrected data
    short update(float* rawData);       //Calculate the correction and adjust the learned distortions. Input data is not overwritten
    short read(float* mOut);            //Writes the current estimate of the m-vector to mOut. Requires that the update method has been called prior to calling.
    short setBias(float* aNew);         //Used to initialize the bias factors
    short setOffset(float* bNew);       //Used to initialize the offset terms
    short getBias(float* aOut);         //Getter method for bias.
    short getOffset(float* bOut);       //Getter method for offset.
};
#endif
