## Short description
---
- First of all, we read all the points and save them in a sorted array
- We are using a rotational matrix, with the particular case of 60 degrees

![image](https://bobobobo.files.wordpress.com/2009/06/4.png?w=510)

- We are creating all the possible pairs of 2 points
- After that we rotate the second point(if we rotate the first one we might get 0 0 which won't be ok) with 60 degrees clock wise, respectively 60 degress counter clock wise
- Then, we use binary search to check if the rotate points exist in the array of points starting from the point j + 1, which means that we skip duplicates
- We count each time when binary search returns true and return the final counter
## Link for the problem
---
https://www.infoarena.ro/problema/triang

## Note 
---
- The problem states that all the points are unique, we do not have duplicates