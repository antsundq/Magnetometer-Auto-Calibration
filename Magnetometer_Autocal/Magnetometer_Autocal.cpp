/*
 * MIT License
 * Copyright (c) 2021 Anton Sundqvist
 */
#include "Magnetometer_Autocal.h"
/*************************************************************************************
   Begin: Magnetometer_Autocal
**************************************************************************************/
MAGAC::MAGAC() {
}

short MAGAC::begin() {
  this->firstIteration = true;
  this->a[0] = 1.f;
  this->a[1] = 1.f;
  this->a[2] = 1.f;
  this->b[0] = 0.f;
  this->b[1] = 0.f;
  this->b[2] = 0.f;
  return 0;
}

short MAGAC::setBias(float* aNew){
  for(int i=0;i<VECTOR_DIM;i++)
    this->a[i]=aNew[i];
  return 0;
}

short MAGAC::setOffset(float* bNew){
  for(int i=0;i<VECTOR_DIM;i++)
    this->b[i]=bNew[i];
  return 0;
}

short MAGAC::getBias(float* aOut){
  for(int i=0;i<VECTOR_DIM;i++)
    aOut[i]=this->a[i];
  return 0;
}

short MAGAC::getOffset(float* bOut){
  for(int i=0;i<VECTOR_DIM;i++)
    bOut[i]=this->b[i];
  return 0;
}

short MAGAC::read(float* mCorr){
  for(int i=0;i<VECTOR_DIM;i++)
    mCorr[i]=this->m[i];
  return 0;
}

short MAGAC::update(float* rawData) {
  short result = 0;
  //On the first iteration we take the norm of the measured vector and use this to normalize all data subsequently.
  if (this->firstIteration) {
    this->xInvNorm = calcNorm(rawData);
    if(xInvNorm<=0)
      return -1;
    this->firstIteration = false;
    this->xInvNorm=1/this->xInvNorm;
  }
  result |= predict(rawData);
  result |= learn(rawData);
  return result;
}

short MAGAC::predict(float* rawData) {
  for(int i = 0; i<VECTOR_DIM; i++)
    this->m[i]=this->a[i]*rawData[i]*this->xInvNorm+this->b[i];
  return 0;
}

short MAGAC::learn(float* rawData) {
  float mInvNorm=calcNorm(this->m);
  if(mInvNorm<=0)
    return -1;
  mInvNorm=1/mInvNorm;
  for(int i = 0; i <VECTOR_DIM; i++){
    this->a[i]-=this->learningRate*2*(1-mInvNorm)*this->m[i]*rawData[i]*this->xInvNorm;
    this->b[i]-=this->learningRate*2*(1-mInvNorm)*this->m[i];
  }
  return 0;
}

float MAGAC::calcNorm(float vec[]){
  float sum=0;
  for(int i = 0; i<VECTOR_DIM;i++)
    sum+=vec[i]*vec[i];
  return sqrt(sum);
}
/*************************************************************************************
   End: Magnetometer_Autocal
**************************************************************************************/
