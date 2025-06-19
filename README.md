# 🧠 Philosophers - 42 Project

Welcome to the Dining Philosophers simulation — a classic concurrency problem solved using POSIX threads, mutexes, and optionally processes and semaphores for bonus points.

This project focuses on multithreaded and multiprocess synchronization, avoiding deadlocks, and ensuring thread-safe access to shared resources (forks). Implemented in pure C without any global variables.

---

## 📁 Project Structure

```
philo/
├── Makefile
├── philo.h
├── *.c

philo_bonus/
├── Makefile
├── philo_bonus.h
├── *.c
```

---

## 🚀 Getting Started

### ✅ Mandatory Part (`philo/`)

- Each philosopher is a thread.
- Forks are protected with mutexes to ensure exclusive access.

```sh
make -C philo
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### ✅ Bonus Part (`philo_bonus/`)

- Each philosopher is a process.
- Fork access is managed via POSIX semaphores.

```sh
make -C philo_bonus
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

---

## 🧠 Problem Overview

- Philosophers are seated at a **round table** with a **fork between each pair**.
- To **eat**, a philosopher needs **two forks** — one on the left and one on the right.
- Philosophers **alternate** between:
  - 🧠 Thinking
  - 🍝 Eating
  - 😴 Sleeping
- If a philosopher does **not eat within `time_to_die` milliseconds**, they **die**.
- The simulation ends when:
  - A philosopher **dies of starvation**, or
  - *(Optional)* All philosophers have eaten at least `number_of_times_each_philosopher_must_eat` times.

---

## 🛠 Allowed Functions

### Mandatory Part

- `pthread_create`
- `pthread_join`
- `pthread_detach`
- `pthread_mutex_init`
- `pthread_mutex_destroy`
- `pthread_mutex_lock`
- `pthread_mutex_unlock`
- `gettimeofday`
- `usleep`
- `write`
- `malloc`
- `free`
- `printf`

---

## 📝 Logging Format

Output is **timestamped** and **thread-safe**:

```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

- `X` is the **philosopher number** (starting from 1).
- `timestamp_in_ms` is the **time elapsed** since the simulation start in **milliseconds**.
- The message for a philosopher's **death must be printed within 10 ms** of their actual time of death.

---

## 💡 Key Concepts & Requirements

- 🧵 **Threads (mandatory):** One thread per philosopher, with one mutex per fork.
- 🧪 **Race Conditions:** Must be avoided through proper mutex locking.
- 💀 **Starvation:** Philosophers must not starve (unless it ends the simulation).
- 🔒 **Thread-Safety:** Logs and shared data must be synchronized.
- ⚙️ **Semaphores (bonus):** A single semaphore manages all forks.
- 📦 **No global variables allowed**.

---

## ✅ Makefile Targets

- `make` / `make all` — Compile the program.
- `make clean` — Remove object (`.o`) files.
- `make fclean` — Remove all binaries and object files.
- `make re` — Clean and rebuild the project.

---

## 📚 Resources

- [Dining Philosophers Problem – Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads (pthreads)](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- [POSIX Semaphores](https://man7.org/linux/man-pages/man7/sem_overview.7.html)

---

## 🔒 License

This project is part of the **42 Curriculum** and is provided for **educational purposes only**. Please **do not plagiarize**.

---

## ✨ Author

> Built by a 42 student A. Obshatko.
