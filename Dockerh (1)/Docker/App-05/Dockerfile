# https://hub.docker.com/_/gcc
FROM gcc:latest
LABEL dveloper = "Harsha_gcc"

# Set working directory in container

WORKDIR /c_code

# Copy code from host to container

COPY sum.c .

RUN gcc sum.c -o sum.out

CMD ["./sum.out"]