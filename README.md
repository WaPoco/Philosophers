## Philosophers dining problem

This project is about implementing a solution to the classic philosphers dining problem.
We have a few philosophers sitting around a circular table.
Between each pair of philosophers lies a spoon.
To eat, a philosopher must hold two spoons — one in each hand.
In the middle of the table is the shared limited food.

#### How can we schedule spoon usage so that no philosopher starves?

The key to solving the Dining Philosophers is to ensure two properties simultaneously:

- No deadlock: the system always makes progress — no philosopher is stuck forever waiting.
- No starvation: every philosopher who wants to eat will eventually get a turn.

### Why this matters

The philosphers dining problem refers to the classical synchronization problem in an operating system. If we have more than one thread or process and shared memory the synchronization problem arises. The philosophers dining problem illustrates the issue when mutiple threads or processes access shared resources in memory without coordination.

Without careful design, competing threads can fall into:
- deadlocks:  All threads wait forever for resources held by others.
- Racecondition: unpredictable behaviour of variables in common

This problem is a well-known synchronization challenge in concurrent programming, used to illustrate how multiple threads can share resources safely without conflicts.

## 📚 Table of Contents
- [Project Structure](#-project-structure)
- [Installation](#-Installation)
- [Usage](#-usage)
- [How does it work](#-How-does-it-work)
- [Tests](#-Tests)

## 📂 Project Structure
src/
  - free.c – Cleanup and resource deallocation

  - init.c – Initializes data structures, mutexes, and state

  - main.c – Program entry point

  - monitore.c – Monitors philosopher states (e.g., starvation, death)

  - routine.c – Main philosopher loop (think → eat → sleep)

  - routine1.c – Additional/helper routines

  - threads.c – Thread creation, joining, and synchronization

  - time.c – Time utilities (timestamps, delays)

  - utilis.c – General helper functions
  
include/
  -philo.h - Header file with constants, structures, and function prototypes
## Installation
Get repo
```bash
git clone https://github.com/WaPoco/Philosophers
```
Change directory
```
cd Philosophers
```
Create Philosophers binary
```
make
```

## Usage

```bash
./Philosophers n t_die t_sleep
```
## How does it work

1. Resource‐Hierarchy (Numbering) Strategy

Number the spoons from 0 through n–1 (in a circle).
Always pick up the lower‐numbered spoon first, then the higher‐numbered one.
Philosopher i sees two spoons: spoon i (on the right) and spoon (i+1)%n on the left.
- If i < (i+1)%n he grabs spoon i first;
- otherwise he grabs spoon (i+1)%n first.
