# Philosophers

This is a project that aims to teach the idea of threading and using mutual exclusion in order to avoid a deadlock and data races, using the well known example of the[ dining philosophers problem]([Dining philosophers problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)).

One or more philosophers sit at a table, there's one fork between each of them, one to their right and left. Each philosopher is thinking while they're awake, but they need to eat after a certain amount of time, otherwise they'll die. In order to eat, they need to pick up two forks, which makes it impossible for the philosophers to the right and left to eat. After eating, philosophers need to sleep for a certain amount of time before thinking again.

The goal of this program is to create an algorithm which prevents the philosophers from dying.

### Important point regarding leaks
When launching this program with only one thread, the single thread will be spun down using pthread_detach instead of pthread_join. This immediately detaches the thread from the main thread instead of waiting for the main thread to finish (see behaviour [described here](https://sites.ualberta.ca/dept/chemeng/AIX-43/share/man/info/C/a_doc_lib/libs/basetrf1/pthread_join.htm)). This will cause valgrind to show a possible leak, but in fact it's fine, as valgrind only operates until the main thread finishes (see [here](https://stackoverflow.com/questions/20893358/a-detached-pthread-causes-memory-leaks)). For debugging leaks in threads I found [this article](http://bl0rg.krunch.be/memleak-pthreads.html) regarding memcheck and [valgrind massif](https://valgrind.org/docs/manual/ms-manual.html) very helpful.

## General Rules

- No global variables

- the program needs to take four to five arguments
  
  - four arguments are mandatory
    
    - **number_of_philosophers**: needs to be at least 1
    
    - **time_to_die** (in milliseconds): a philosopher needs to eat at least once within this timeframe after the beginning of his last meal, otherwise they die
    
    - **time_to_eat** (in milliseconds): time it takes a philosopher to eat
    
    - **time_to_sleep** (in milliseconds): time a philosopher needs to sleep after a meal
  
  - the fifth argument is optional
    
    - **number_of_times_each_philosopher_must_eat**: optional end condition, if each philosopher has eaten this much, the simulation stops, otherwise it runs until all philosophers die

- all philosophers sit in a circle, therefore the first sits next to the last philosopher and so on (probably helpful to use circular linked list here)

- all activities need to be logged on the standard output in this format: timestamp_in_ms, philosopher by number and action. There's five actions in total
  
  - has taken a fork
  
  - is eating
  
  - is sleeping
  
  - is thinking
  
  - died

- There can't be any overlap on the messages, also messages need to be displayed quick after their occurrence (not more than 10 ms after actual death of philosopher)

## Mandatory rules

Additionally to the general rules, the mandatory part has a specific set of rules:

- each philosopher needs to be represented by a thread

- there is one fork between each pair of philosophers, therefore for one philosopher only one fork exists (and he'll quickly die, but you'll still need to create a thread and run the simulation)

- forks need to be protected by a mutex to avoid duplicate use by philosophers/threads

| function              | library    | description                                                                                                            | return value                                                  |
| --------------------- | ---------- | ---------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------- |
| printf                | stdio.h    | writes a string to stdout, handles different types                                                                     | int, number of characters printed, excluding null byte        |
| memset                | string.h   | fills the first n bytes of memory area with constant byte provided in arguments                                        | void pointer to the memory area set                           |
| malloc                | stdlib.h   | allocates number of bytes provided in the arguments                                                                    | void pointer to the memory allocated                          |
| free                  | stdlib.h   | frees a previously allocated memory space                                                                              | none                                                          |
| write                 | unistd.h   | writes to a fd from a buffer specified in arguments                                                                    | ssize_t, number of bytes written, -1 on failure, errno is set |
| usleep                | unistd.h   | suspends execution of program for specific time provided as microseconds in arguments                                  | int, 0 on success, -1 on failure, errno is set                |
| gettimeofday          | sys/time.h | gets the current time in seconds and microseconds and writes it to a timeval and timezone struct provided as arguments | int, 0 on success, -1 on failure, errno is set                |
| pthread_create        | pthread.h  | creates a new thread, allows to pass values to new thread                                                              | int, 0 on success, errno when error                           |
| pthread_detach        | pthread.h  | "detaches" thread, thread can't be joined, resources will be freed upon termination                                    | int, 0 on success, errno when error                           |
| pthread_join          | pthread.h  | waits for thread to finish, receives return values from thread                                                         | int, 0 on success, errno when error                           |
| pthread_mutex_init    | pthread.h  | initializes a **mut**ual **ex**clusion object                                                                          | int, 0 on success, errno when error                           |
| pthread_mutex_destroy | pthread.h  | destroys a mutex object and all associated resources, which needs to be unlocked before calling                        | int, 0 on success, errno when error                           |
| pthread_mutex_lock    | pthread.h  | locks a mutex object, therefore making it impossible for another thread to become active before it is unlocked         | int, 0 on success, errno when error                           |
| pthread_mutex_unlock  | pthread.h  | unlocks a mutex object                                                                                                 | int, 0 on success, errno when error                           |

### possible approach
[This user explained his approach very well](https://github.com/TommyJD93/Philosophers), step by step.

## Bonus rules

The bonus part works with the general rules as well, but adds a different concept to work with: semaphores ([good explanation on them here by Jacob Sorber](https://www.youtube.com/watch?v=ukM_zzrIeXs)). Specific changes to the rules:

- All forks are in the middle rather than next to the philosophers

- The forks have no state in the memory, but the number of them is managed through a semaphore

- Instead of threads, philosophers are represented by individual processes, but the main thread shouldn't be a philosopher

Also, there's different functions allowed:

| function       | library     | description                                                                                                            | return value                                                      |
| -------------- | ----------- | ---------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------- |
| printf         | stdio.h     | writes a string to stdout, handles different types                                                                     | int, number of characters printed, excluding null byte            |
| memset         | string.h    | fills the first n bytes of memory area with constant byte provided in arguments                                        | void pointer to the memory area set                               |
| malloc         | stdlib.h    | allocates number of bytes provided in the arguments                                                                    | void pointer to the memory allocated                              |
| free           | stdlib.h    | frees a previously allocated memory space                                                                              | none                                                              |
| write          | unistd.h    | writes to a fd from a buffer specified in arguments                                                                    | ssize_t, number of bytes written, -1 on failure, errno is set     |
| fork           | unistd.h    | duplicates the calling process                                                                                         | returns pid of new child process, -1 on failure                   |
| kill           | signal.h    | sends a signal to a specific process                                                                                   | 0 on success, -1 on failure, errno is set                         |
| exit           | stdlib.h    | terminates process normally, status code set as argument                                                               | none                                                              |
| usleep         | unistd.h    | suspends execution of program for specific time provided as microseconds in arguments                                  | int, 0 on success, -1 on failure, errno is set                    |
| gettimeofday   | sys/time.h  | gets the current time in seconds and microseconds and writes it to a timeval and timezone struct provided as arguments | int, 0 on success, -1 on failure, errno is set                    |
| pthread_create | pthread.h   | creates a new thread, allows to pass values to new thread                                                              | int, 0 on success, errno when error                               |
| pthread_detach | pthread.h   | "detaches" thread, thread can't be joined, resources will be freed upon termination                                    | int, 0 on success, errno when error                               |
| pthread_join   | pthread.h   | waits for thread to finish, receives return values from thread                                                         | int, 0 on success, errno when error                               |
| waitpid        | sys/types.h | waits for process to change, e.g. by termination, stop or resume                                                       | on success returns pid of process that has changed, -1 on failure |
| sem_open       | semaphore.h | opens existing or creates new semaphore                                                                                | address of semaphore                                              |
| sem_close      | semaphore.h | closes semaphore passed as argument                                                                                    | int, 0 on success, -1 on failure, errno set                       |
| sem_post       | semaphore.h | increments semaphore                                                                                                   | int, 0 on success, -1 on failure, errno set                       |
| sem_wait       | semaphore.h | decrements semaphore if larger than 0, otherwise blocks until semaphore is larger than 0                               | int, 0 on success, -1 on failure, errno set                       |
| sem_unlink     | semaphore.h | removes the semaphore after all processes close it                                                                     | int, 0 on success, -1 on failure, errno set                       |
