FROM --platform=linux/386 debian:bookworm

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        build-essential \
        gcc \
        gdb \
        make \
        cmake \
        pkg-config \
        libc6-dev \
        file && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /work

CMD ["/bin/bash"]

# BUILD --> docker buildx build --platform linux/386 -t c32-munit --load .
# RUN --> docker run --rm -it -v "$PWD":/work c32-munit
