=========================== 1. Installations  ===========================
  ## Install arch
    sudo pacman -Syy
    sudo pacman -S docker
  ## Set normal docker group user to use
    sudo groupadd docker
    sudo usermod -aG docker $USER
    ## relogin
  ## Clean and restart if can not start docker daemon after installation
  ## /var/lib/docker  or check if kernel support docker
    sudo systemctl start docker
  ## Check docker info
    docker info [-h]

=========================== 2. Docker Introdutions ===========================
  ## Pull images from Docker Hub
  ## Costumlized images of ownloud
  ## if download speed is freaking slow, set dns to 1.1.1.1
  ## server=/registry-1.docker.io/1.1.1.1 or 8.8.8.8
  ## 实在觉得慢，最好白天下载，不确定是否是docker官方服务器做了限制
  ################ 1 . Basic Operations ################
    docker pull 拉取镜像
    docker exec 容器中执行命令
    docker inspect 查看镜像信息
  ################ 2. Build Images   ################
    ## 最好单独建一个目录
    ## Build with [-t tag, '.' current dir] Dockerfile
    docker build -t .
  ################ 3. List Image ################
    ## List images
    docker images / sudo docker image ls [-h]
        ## Format : Go languages tamplate grammer
        docker image ls --format "table {{.Repository}}\t:  {{.Size}}"
  ################  4. Docker system   ################
    ##Disk usage of Images, Containers, Volume
    docker system df [-h]
  ################ 5. Run a container from image   ################
    ## Run container, use command  'bash' to match -it
    ##  -it interactive terminal
    ##  --rm delete after quit container
    docker pull ubuntu:18.04
    docker run -it --rm ubuntu:18.04 bash
    ## Delete image
    docker image rm [ repository/id( 3 char at least ) ]
    ## link
    -- link a_container: as_tag
  ################ 2 .  Containers   ################
    docker container rm/ls/stop/log [-h]
    ## Backgroud: -d, attach/exec
    ## # backgroud-run container, id:123
    docker run -it -d unbunt:18.04
    ##frontgrout container
      # if exit, will eixt container
    docker attach 123
      # run command in a running container in
      docker exec container_name cmd
   ##################  3. Volume  ################
    # create
    docker  volume create myvol
    #  list &etc
    docker volume ls/rm [-h]
    # mount
    docker run -dit -P \
          --name web \
          -v myvol:/mnt/data \
          # --mount sourece=myvol,target=/mnt/data \
          ubuntu:18.04  bash
