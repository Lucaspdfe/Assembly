# BSOS Project

Hi, i was not expecting anyone here but okay?
This is my project, i'm just making this for fun. (Forked from: https://github.com/davidcallanan/os-series)
There's nothing else to say, just that i'm planning to do a linux-like kernel with networking capabilities.
Note: this kernel is not supposed to be linux compatible, just alike the linux kernel. (but maybe i will do a syscall-only compatible version.)

## How to build:

To build, you need to have docker and qemu.

To make the docker container, you need to run this command:
 - `docker build buildenv -t os-name`

Note: "os-name" should be your name of choice for the container.

To enter the docker container:
 - Linux or MacOS: `docker run --rm -it -v "$(pwd)":/root/env os-name`
 - Windows (CMD): `docker run --rm -it -v "%cd%":/root/env os-name`
 - Windows (PowerShell): `docker run --rm -it -v "${pwd}:/root/env" os-name`
 - Please use the linux command if you are using `WSL`, `msys2` or `git bash`

To build, run:
 - `make build-arch`

Note: "arch" is the architecture you want and it needs to be one of the supported architectures. And you want to run the command in the docker container. (if not it will cause errors)

## How to enter:

To enter, you just need to execute this command (While not on the docker container): 
 - `qemu-system-x86_64 -cdrom dist/x86_64/BSOS.iso`
