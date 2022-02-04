## Short Descripion
---
- Having this ecuation: 
<img src="https://latex.codecogs.com/svg.image?a_{1}&space;*&space;x_{1}^{3}&space;&plus;&space;a_{2}&space;*&space;x_{2}^{3}&space;&plus;&space;a_{3}&space;*&space;x_{3}^{3}&space;&plus;&space;a_{4}&space;*&space;x_{4}^{3}&space;&plus;&space;a_{5}&space;*&space;x_{5}^{3}&space;=&space;0" title="a_{1} * x_{1}^{3} + a_{2} * x_{2}^{3} + a_{3} * x_{3}^{3} + a_{4} * x_{4}^{3} + a_{5} * x_{5}^{3} = 0" />

- We can let first 3 terms on the left and move the others on the right.Therefore, we will have only 50^3 possibilies that we will save in a possible solutions vector.

- After that we calculate the other 50^2 possibilities on the right and have a counter which increase with:
        
- value = <img src="https://latex.codecogs.com/svg.image?&space;-a_{4}&space;*&space;x_{4}^{3}&space;-&space;a_{5}&space;*&space;x_{5}^{3}" title=" -a_{4} * x_{4}^{3} - a_{5} * x_{5}^{3}" />
```c++
    std::higher_bound(possible_solutions, value) -             std::lower_bound(possible_solutions, value)

    // higher_bound - last position where we meet value
    // lower_bound - first position where we meet value
    // higher_bound - lower_bound = how many times we encounter value
 ```
 - This is a binary search for the value, but we can have multiple terms with the same value, therefore we increase the counter by the how many times we encounter this value 
## Link for the problem
---
https://www.infoarena.ro/problema/eqs