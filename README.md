# SimpleNeuralNetwork


This is a very simple Neural Network based off of the video by Matt Miller

Link is Here: https://www.youtube.com/watch?v=KkwX7FkLfug

The neural network is being trained to be able to determine values of two inputs to the XOR function 

Playing with eta and alpha values, and playing with the number of hidden layers and playing with the number of neurons in those hidden layers,
I was able to get something where the values for the target result 0 were significantly less than the target value of 1

The back propogation function doesnt use the sigmoid function, but rather the derative of tanh^2(x) as its function

The other portion of the project I am currently working on is using the UCI Letter data in order to determine what the letter is
I am havng problems with how the sum of squared errors is being passed to the back propogation function, in this case tanh^2(x)



To see the results of the code, simply use the "make" command and open "out.txt"
