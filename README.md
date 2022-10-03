# Operating Systems

Programs made for the Operating Systems course I took with [Dr. René Mac Kinney Romero](https://github.com/rene-mkr) at Universidad Iberoamericana. This repo contains some low-level C programs that help you manage different things in an operating system; while taking this course my operating system was **MacOS Monterey Version 12.5.1**, but everything should work on Linux machines as well.

> Give me some time and I'll make a container to provide a stable development environment.

## What projects are there?
Inside this repository you'll find a couple of interesting projects which I think are awesome!

### [Threads VS Forks](./threads_vs_forks)
This program let's you compare the speed between running a sorting algorithm with threads and running this same algorithm with forks.

### [Shared Memory Messenger](./shared_memory_messenger/)
This program allows you to simulate a messenger through the use of a shared memory objects. In Linux machines this objects are found in the `/dev/shmem` directory, but in MacOS no such file exists. 

> To understand how shared memory is managed in MacOS read through the manual entry for `shm_open`, there they state: "There is no visible entry in the file system for the created object in this implementation."

## How to run this things?
Instructions for running each program can be found in the README.md file of each project.


