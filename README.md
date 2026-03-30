# boot_mem_management

The purpose of this repository is to provide a docker configuration for executing the exercices of the *Memory Management* course from [boot.dev](http://boot.dev) platform.

For building the container use the command:
`docker buildx build --platform linux/386 -t c32-munit --load .`

For running the container use:
`docker run --rm -it -v "$PWD":/work c32-munit`

## Running tests for C code

For building and running the tests on the running container:
1. Go to the lesson folder
2. Create a `build` folder and go inside
3. Run `cmake ..` command
4. Run `make && ./test` command


> **Note:**
> For the the tests where the freed memory management is tested [boot.dev](https://boot.dev) platform use their own memory allocation and free functions, which allow them to check when the memory is freed or not, currently we have just commented those assertions, until we create our own allocation functions.
