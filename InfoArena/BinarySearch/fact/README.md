# Important things learnt here

## How to find number of digits for a factorial number

---
```C++
    // Let's supose we have a number n
    int calc_digits_for_factorial(int n) {
        double digits = 0;
         for(int i = 2; i <=n; ++i)
            digits += log10(i);
        return floor(digits) + 1;
    }

    // This fucntion wil return return indeed the number of digits of the factorial
    // because we are calculation log10(n!) [ log10(2) + log10(3) + ... + log10(n) == log10(n!)]
    // log10(a) + log10(b) = log10(ab)

```
---

## How to find trailing zeros for a factorial number

```c++
    A number that is divisible with 10 will also be divisible with 2 & 5
    Therefore, it will be enough to calculate the power of 5 in order to find
    the trailing zeros.

    For example:  We have 17230000 = 1723 * 10 ^ 4 = 1723 * 2 ^ 4 * 2 ^ 5
    Observation: In a factorial, we will always have more powers of 2 than powers of 5
```
---
## Link for the problem

https://www.infoarena.ro/problema/fact