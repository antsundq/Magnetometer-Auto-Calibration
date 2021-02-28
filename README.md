# Magnetometer Auto Calibration
This repository contains an algorithm that models and learns the inherent offsets and biases from empirical magnetometer measurement data.
The measured data is assumed to have a linear first order perturbation, or in other words there is a bias factor and an offset term.
The algorithm takes the raw data from the sensor and returns an estimation of the unit magnetic vector without perturbations.

The only parameter which should be adjusted is the learning rate of the algorithm. 
The optimal value depends on the actual data from the hardware, but the default value should work well in many cases. 

To use the algorithm, one will need to integrate a magnetometer into the main sketch, read the values and pass them into the model.
An Arduino sketch is provided as starting point for this in "Magnetometer_Autocal".

## Background
There is a few algorithms and examples available for compensating magnetometer measurements to get rid of the biases inherent to most, if not all, magnetometers. 
The algorithms I have seen are based around the idea of finding the maximum reading for each axis and using these values to compensate the bias and offset. 
This works to some extent, but there is a few drawbacks which I have struggled with in my past projects.
1. To find the maximums you have to turn the magnetometer so that the magnetic field is aligned perfectly with the axis
1. There is a manual step, where you configure the biases and offsets
1. If the errors are not completely static, there is a need for recalibrating
1. If there are outliers in the gathered data this can completely mess up the calibration
1. Calibration is difficult to do manually on an embedded system with a limited UI

When I studied neural networks, I thought that this might be an interesting model system to apply some machine learning on. 
The idea being that one wants to train a neural network and learn the correct weights for compensating for the biases and offsets. 
Since the assumptions implies that there is a linear solution, everything simplifies and there is no need for fancy neural networks.
The proposed solution is in essence a neural network with one layer and a linear activation function and the loss function is defined as the error in the magnitude of the magnetic field vector.
It is however easier to describe the problem as a simple optimization problem which is solve using gradient descent.

## Implementation
To explain the implementation, the model is documented under "Algorithm Development" in the Jupyter notebook called "Gradient Descent Magnetometer auto-calibration.ipynb".
To view this you will need a Jupyter installation and an easy way to install it is by installing Anaconda.
