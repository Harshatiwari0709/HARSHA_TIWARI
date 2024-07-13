Step : 01
    Create the Docker file

Step : 02
    Create the Docker image
    docker build -t <image_name>:tag(version) <path_of_the_Dockerfile>

    Examples:
            sudo docker build -t ubuntu:diot240322.04 .

Step : 03
        Check created Image

        sudo docker images
        sudo docker image ls

Step : 04

        Run Image as container

        sudo docker run -it <imagename> #it interactive mode

        sudo docker run -it ubuntu:diot240322.04

Step : 05
        
        Check the running container

        sudo docker ps

        sudo docker container ls

Step : 06

        Check all the containers (running/exited/stopped)

        sudo docker ps -a

        sudo docker container ls -a