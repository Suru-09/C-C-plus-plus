# Index File System

## B-Tree Structure

  We have a B-Tree node having following the things:
  ```
        -the minimum degree of the tree(int)
        -a keysize(which is an int)
        -an array of keys(sizeof(keysize))
        -an array of values for the keys (uint64)
        -an array of Node pointers (the children)
        -a bool for checking whether the node is a leaf or not
        -n which is the numbers of nodes (int)
  ```

  Information about the size of the attributes within a node:
  
   -the arrays of keys has maximum: ```2 * t - 1 elements ```
                                    ```and sizeof(keysize)```
                                    
   -the values for each key will have maximum: ```8 bytes(64 bits)```
   
   -all ints will have of course ```4 bytes```
   
   
   
                               
 
    