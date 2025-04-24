Philosophers problem
This project is about the concept of parallel threading. So we have n philoshers and spoons located around a table. Each philosopher wants to eat and has to use on both hands spoons in order to eat. How should we time the order to avoid starvation?
The key to solving the Dining Philosophers so that no one starves is to ensure two properties simultaneously:
-No deadlock (every system of requests eventually makes progress)
-No starvation (every philosopher who wants to eat eventually gets to eat)

Below are three classic strategies—each avoids deadlock, and with a small tweak can also guarantee no one waits forever.  

1. Resource‐Hierarchy (Numbering) Strategy

Number the spoons from 0 through n–1 (in a circle).
Always pick up the lower‐numbered spoon first, then the higher‐numbered one.
Philosopher i sees two spoons: spoon i (on the right) and spoon (i+1)%n on the left.
If i < (i+1)%n he grabs spoon i first; otherwise he grabs spoon (i+1)%n first.