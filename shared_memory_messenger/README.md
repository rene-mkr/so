# Shared Memory Messenger

A quick implementation of a messenger applied through shared memory objects.

## Using the code

To run compile the code you just need to run:

``` Shell
make
```

Once you have the executable version run it with:

``` Shell
./messenger.exe ${BUFFER_SIZE}
```

Here the `${BUFFER_SIZE}` parameter represents the maximum size any given message can have. The src files are spread all over the place to follow a modular architecture and follow what I—up till now—consider best practices.

## Teacher instructions

A small message service should be done using shared memory using shared memory objects.

- The name of the object is the conversation.
- The program should ask whether to read or write a message (or you can have a program for each thing).
- You must keep track of the messages read (which free memory) and
messages left (consuming memory).
- To access shared memory, semaphores must be used.