## Philosophers problem

This project is about implementing a solution to the classic philoshers dining problem.
We have n philosophers sitting around a circular table.
Between each pair of philosophers lies a spoon.
To eat, a philosopher must hold two spoons — one in each hand.

### The challenge:

How can we schedule spoon usage so that no philosopher starves?

The key to solving the Dining Philosophers so that no one starves is to ensure two properties simultaneously:

- No deadlock (every system of requests eventually makes progress)
- No starvation (every philosopher who wants to eat eventually gets to eat)

## Solution  

1. Resource‐Hierarchy (Numbering) Strategy

Number the spoons from 0 through n–1 (in a circle).
Always pick up the lower‐numbered spoon first, then the higher‐numbered one.
Philosopher i sees two spoons: spoon i (on the right) and spoon (i+1)%n on the left.
- If i < (i+1)%n he grabs spoon i first;
- otherwise he grabs spoon (i+1)%n first.
  
## 📚 Table of Contents
- [Project Structure](#-project-structure)
- [Installation](#-installation)
- [Usage](#-usage)
- [Tests](#-Tests)
- [Requirements](#-requirements)
