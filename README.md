filters
=======
A demo repo for implementing practice versions of various low-pass filters such as Simple Moving Average (SMA), Exponential Moving Average (EMA) and possibly more.

The main objective is to find a very simple implementation of an EMA that can work on a variable dataset (2^N samples) where N can be 1 to 4 or 5.  It will also explore how the size of a dataset affects the responsiveness of the input sample for different scenarios.  For example, when sampling voltage from a current sense resistor in a power supply, what's the ideal data set to work with?  Or, when sampling an accelerometer or temperature sensor?


### Sources
http://bleaklow.com/2012/06/20/sensor_smoothing_and_optimised_maths_on_the_arduino.html

http://electronics.stackexchange.com/questions/42734/fastest-moving-averaging-techniques-with-minimum-footprint

