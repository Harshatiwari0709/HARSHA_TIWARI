FROM gcc:latest
LABEL dveloper = "harsha_gcc"

# Set working directory in container

WORKDIR /c_code

# Copy code from host to container

COPY sum.cpp .

RUN g++ sum.cpp -o sum.out

CMD ["./sum.out"]

