# Number of valid triangles

```c++
    We are calculating the best value
    possible for the three triangle 
    sides, after that we know that 
    every value from that index to j 
    will be a valid triangle. 

    if (a + b > max_value) 
        then a + b > (min_value > b)
    
    Generating all possible values
    with 2 for's
```