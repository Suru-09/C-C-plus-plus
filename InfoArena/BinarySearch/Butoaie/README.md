## Steps
---
- We use a base(the basic spray), we substract 
base * nr_days from each room
- Whenever bugs[i] - base * days > 0 it means that we didn't eradicate all the bugs from that room in the required days, but we still have the upgrades left (the
enhanced spray), therefore nr_upgrades = (nr_extra * days)
- If during this process, we used all our upgrades and we need more it means that
the given days weren't enough(we return false) and we will use binary search to find another 
possible value, otherwise we return true
- We will save the best value found and return it at the end

## Link for the problem
---
https://www.infoarena.ro/problema/butoaie