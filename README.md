# Philosophers
This project has been created as part of the 42 curriculum by vpogorel. 

# Description
![Philosophers Diagram](pictures/setting.jpg)

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

The philosphers dining problem refers to the classical synchronization problem in an operating system and illustrates the issue when mutiple threads or processes access shared resources in memory without coordination.

Without careful design, competing threads can fall into:
- deadlocks:  All threads wait forever for resources held by others.
- Racecondition: unpredictable behaviour of variables in common

This problem is a well-known synchronization challenge in concurrent programming, used to illustrate how multiple threads can share resources safely without conflicts.

## 📂 Project Structure
```
philosophers/
├─ Makefile
├─ README.md
├─ include/
│  └─ philo.h
├─ src/
│  ├─ free.c               // functions to free memory from heap
│  ├─ init.c               // allocates and initializes philos, mutex locks and threads
│  ├─ monitore.c           // monitores all simulation condition(death of philos, starvation) 
│  ├─ routine1.c           // grap forks
│  ├─ routine.c            // philosopher loop eat(), sleep_time(), thinking()
│  ├─ threads.c            // thread create/join
│  ├─ time.c               // time functions
│  └─ utils.c              // allocation, destroy, print message
└─ tests/
   └─ scenarios.sh        // quick runs for common/edge cases
|
└─ picures/
   └─ 0012.jpg
```
---
## Usage

```bash
./Philosophers n t_die t_eat t_sleep must_eat
```
### Arguments
- ```n```       number of philosophers and forks
- ```t_die```   time in ms that past after the last meal. After that duration a philospher will starve to death.
- ```t_eat```   time in ms that a philosopher needs during eating
- ```t_sleep``` time in ms that a philosopher needs during sleeping
- ```must_eat```number of times each philosopher should eat atleast

Output:
```
time_past | i-philosopher | state of a philosopher(thinking, eating, grabing or sleeping)
```
    
### Example
```./Philosophers 5 400 200 200```

Output:
```
0 0 is thinking
0 0 has taken a fork
0 0 has taken a fork
0 0 is eating
0 1 is thinking
0 1 has taken a fork
0 2 is thinking
0 3 is thinking
200 0 is sleeping
200 3 has taken a fork
200 3 has taken a fork
200 3 is eating
200 1 has taken a fork
200 1 is eating
401 0 is thinking
401 0 died
```
---
## How does it work

#### Resource‐Hierarchy Strategy

Number the spoons and philosophers from 0 through n – 1 clockwise.
Each Philosopher can reach two spoons: on the right or left side.
In order to avoid deadlocks each philosopher should grap opposite forks. 

A even numbered Philosopher should pick up the left spoon first, then the right spoon.
A odd numbered Philosopher should pick up the right speen first, then the left spoon.
If another philosopher is already holding the right or left spoon, he waits until it is available.

If the number of philosopher is even, the result will be that all even numbered philosophers will eat, then all odd numbered philosophers will eat, and so on. This way, no philosopher wait forever and the system will make progress. 
If the number of philosopher is odd, then result will be two groups of philosophers one will eat and the other one will wait.

In the following animation you will see 4 philosophers.

![4 Philosophers ](https://github.com/WaPoco/Philosophers/blob/main/philo-demo.gif)

#### How did I implement the strategy ?
One possible way to implement the solution is by using mutexes and threads from the library ```thread.h```.

A thread is the smallest execution unit which the CPU can process and would represent a philosopher.
On the other hand the spoons could be represented by mutexes which are kind of locks. When a philosopher graps a
fork no one can get access to the same object.
```
void	grap_forks(t_philosopher *p)
{
	if (p->id % 2 == 0)
	{
		grap_fork(p, p->rfork);
		grap_fork(p, p->lfork);
	}
	else
	{
		grap_fork(p, p->lfork);
		grap_fork(p, p->rfork);
	}
}
```

## Tests
1.Test: No dataraces, deadlocks
```valgrind --tool=helgrind ./Philosophers ...```

2.Test:

```./Philosophers 1 800 200 200```

# Instructions
Clone the repo:
```bash
git clone https://github.com/WaPoco/Philosophers
```
Change directory:
```
cd Philosophers
```
Create the binary:
```
make
```
Clean up at the end:
```
make fclean
```
---
# Resources
- [Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Dining Philosophers Problem - GeeksforGeeks](https://www.geeksforgeeks.org/dining-philosophers-problem/)
- [Dining Philosophers Problem - YouTube](https://www.youtube.com/watch?v=YtqNQYqJ8o)
- [Dining Philosophers Problem - StackOverflow](https://stackoverflow.com/questions/1918/dining-philosophers-problem)
- [Dining Philosophers Problem - 42 Cursus]
