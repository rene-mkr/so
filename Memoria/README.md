# Pequeño servicio de mensajes

Se debe hacer un pequeño servicio de mensajes usando memoria compartida
utilizando objetos de memoria compartida

El nombre del objeto es la conversación

El programa debe preguntar si se va a leer o escribir un mensaje
(o se pueden tener un programa para cada cosa)

Se debe llevar cuenta de los mensajes leidos (que liberan memoria) y
mensajes guardados (que consumen memoria)

Para acceder a memora compartida se deben utilizar cerraduras de archivos.

## Para compilar

get.c y set.c

gcc -o set set.c
