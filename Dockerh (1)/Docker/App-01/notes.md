# Run a container with a specific name

sudo docker run -it --name <container_name> <imagename>

# Install Ping

 apt install iputils-ping

# How to start a container

sudo docker start <container_name/id>

# How to stop a container

 sudo docker stop <container_name/id>

# How to run command inside a running container

  sudo docker exec -it <command>

  Example:

      sudo docker exec -it b19dba550b68 bash

# How to create a image from a container

  sudo docker commit <c_name/cid> imagename:tag

  
# Save image for offline sharing

  sudo docker save -o ubuntunano.tar ubuntu:nano

# Load a docker image from a file (like ubuntunano.tar)

  sudo docker load -i <filename>

  Example:
         
         sudo docker load -i ubuntunano.tar


# How to push image to docker hub

   create image on docker-hub

  docker tag local-image:tagname new-repo:tagname

# Make sure docker is logged in, if not 

  docker push new-repo:tagname