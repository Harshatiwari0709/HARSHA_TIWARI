FROM openjdk:latest
LABEL developer: "harsha_java"

# Set working directory in container

WORKDIR /java_app

# Copy code form container

COPY hello.java .

RUN javac hello.java

CMD ["java","hello"]

