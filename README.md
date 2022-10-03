# Shared Memory Messenger

A quick implementation of a messenger applied through shared memory objects.

## Using the code

To run compile the code you just need to run:

``` Shell
make
```

Once you have the executable version run it with:

``` Shell
./game.exe ${BUFFER_SIZE}
```

Here the `${BUFFER_SIZE}` parameter represents the maximum size any given message can have. The src files are spread all over the place to follow a modular architecture and follow what I—up till now—consider best practices.