#Kohonen

It's simply realization of kohonen network.

##Providions

 * Calculate kohonen network
 * Create rindomized kohonen network in custumized field
 * Teach network (self organized map) without teacher
 * Teach network to hardset-classsification (teaching with teacher, it's able to continue it without teacher)
 * Vizualization tool

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

###Data file
This file contains array of vector.
```
(number of vectors) (dimentional)
(vector1)
...
(vectorN)
```

#Vizualization tool
This tool is using for vizualzation array of vectors. 

In console:
```
vizualaze file1.dat file2.dat
```

The tool *reuqeures the gnuplot*.

#Points round tool
It requires in instream: 
```
round_point
range_value
number of points you want
```

The out is an dat file with points.

#Up dimentional tool
It unite two .dat files to up a dimention.
```
./up_dim file1.dat file2.dat > file_out.dat
```
