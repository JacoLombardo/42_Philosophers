# Philosophers

Philosophers is a 42 School project based on the classic Dining Philosophers problem. It introduces multithreading and synchronization in C using pthreads and mutexes to avoid deadlocks and starvation.

## Overview

Philosophers sit around a table, each needing two forks to eat. With one fork between each pair of neighbors, the challenge is to coordinate them so they can eat without deadlocking. The program simulates this with configurable timing and optional meal limits.

## Composition

- **philo/** — main program
  - `philo.c` — entry point, argument parsing, initialization
  - `source/routine.c`, `routine_utils.c` — philosopher behavior (think, eat, sleep)
  - `source/threads.c` — thread creation and management
  - `source/utils.c` — timing, printing, cleanup
  - `philo.h` — shared structures and declarations

## Features

- **Multithreading** — one thread per philosopher
- **Mutexes** — fork locks and shared state protection
- **Configurable timings** — time to die, eat, sleep
- **Optional meal limit** — stop after each philosopher has eaten N times
- **Structured logging** — timestamped status messages

## Technology

- C (C99)
- POSIX threads (pthreads)
- Mutexes (pthread_mutex_t)
- `usleep`, `gettimeofday`

## Setup

Build (from `philo/`):

```bash
cd philo
make
```

Usage:

```bash
./philo <num_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [num_times_each_must_eat]
```

Example:

```bash
./philo 5 800 200 200
./philo 4 410 200 200 7
```

## Notes

- Arguments: number of philosophers, time to die (ms), time to eat (ms), time to sleep (ms), optional meal count
- Subject: `Philosophers_subject.pdf`
- Bonus often uses processes and semaphores instead of threads
