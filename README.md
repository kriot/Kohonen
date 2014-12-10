#Kohonen

It's simply realization of kohonen network.

##Providions

 * Calculate kohonen network
 * Create rindomized kohonen network in custumized field
 * Teach network (self organized map) without teacher
 * Teach network to hardset-classsification (teaching with teacher, it's able to continue it without teacher)

##File types
This interface uses two types of files.

###Network file
This file (`*.net`) contains the information about network. It's all you need to calculate network by in-vector.

```
(number of outs) (number of ins)
(vector of the 1st out. The size is equal to number of ins)
...
(vector of the Nth out)
```

###Teach file

This file (`*.teach`) contains information about set of data for teaching and information about field of in-vector (allowed values for each coordinate of in-vector)

```
(volume of data) (nuber of ins)
(vector of max values for each cord. It sets field)
(in-vector of sample)
...
(in-vector of sample)
```
