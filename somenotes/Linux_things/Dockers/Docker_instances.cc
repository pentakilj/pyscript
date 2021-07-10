=========================== most useed Docker Instances ===========================
1. dnsmasq  local dns
      build yourself
2. nextcloud see below
3. diygod local rss
  docker pull diygod/rsshub
  docker run -d --name rsshub -p 1200:1200 diygod/rsshub
  http://127.0.0.1:1200/
3.  163proxy unlock 163 music
  docker pull nondanee/unblockneteasemusic
	# add -p t expose port 8080 to host mathine
	docker  run -p 8080:8080 -p 8081:8081 nondanee/unblockneteasemusic
4. numdup trans NCM to mp3
      forked
=========================== detail Docker Instances ===========================
 ################ 1. Mysql     ################
    # host client: mysql-clients
    # https://hub.docker.com/_/mysql/
    # https://github.com/datacharmer/test_db  employees
    docker pull mysql:5.7
    docker run --name mysql5.7 \
              # explode to host or other app, default port 3306
              -p 3306:3306 \
              -e MYSQL_ROOT_PASSWORD=123456 \
              # host dir to storage mysql data: ~/mysql_data
              -v ~/mysql_data:/var/lib/mysql \
              -d mysql:5.7
    # Import testdb
    mysql -h 192.168.1.108 -u root -p < employees.sql
    # test
    mysql -h 192.168.1.108 -u root -p -t  < test_employees_md5/sha.sql
    # API for python connecting mysql
    pip install mysql-connector
  ################ 2. Owncloud with Docker   ################
    mkdir owncloud
    cd owncloud/
    docker volume create owncloud_redis
    # port 6379
    docker run -d \
      --name redis \
      -e REDIS_DATABASES=1 \
      --volume owncloud_redis:/var/lib/redis \
      webhippie/redis:latest
    ## mkdir mysql
    docker volume create owncloud_mysql
    docker volume create owncloud_backup
    # port 3306
    docker run -d name mariadb \
          -e MARIADB_ROOT_PASSWORD=owncloud \
          -e MARIADB_USERNAME=owncloud \
          -e MARIADB_PASSWORD=owncloud \
          -e MARIADB_DATABASE=owncloud \
          --volume owncloud_mysql:/var/lib/mysql \
          --volume owncloud_backup:/var/lib/backup webhippie/mariadb:latest
          ## 1 copy file to storage via Backgroud
          ## Recommended:
          ## docker exec -ti container_name occ files: scan --all
          ## OR:
          ## login mysql, and truncate table oc_ilecache which will auto update.
          ## truncate oc_filecache;
          ## 2.easy to check logs or docker logs id
          ##--volume ~/owncloud/mysql:/var/lib/mysql

          ##  3 can't open owncloud
          ##  maybe fresh install then check github issue.
    # Owncloud
    sudo docker pull owncloud/server
    sudo docker pull webhippie/redis
    sudo docker pull webhippie/mariadb
    docker volume create owncloud_files
    # run and set host localhost, other client visit via local mathine's ip addr
    docker run -d \
          --name owncloud   \
          --link mariadb:db   \
          --link redis:redis   \
          -p 80:80   \
          -p 443:443   \
          -e OWNCLOUD_DOMAIN=localhost   \
          -e OWNCLOUD_DB_TYPE=mysql   \
          -e OWNCLOUD_DB_NAME=owncloud   \
          -e OWNCLOUD_DB_USERNAME=owncloud   \
          -e OWNCLOUD_DB_PASSWORD=owncloud   \
          -e OWNCLOUD_DB_HOST=db   \
          -e OWNCLOUD_ADMIN_USERNAME=admin   \
          -e OWNCLOUD_ADMIN_PASSWORD=123   \
          -e OWNCLOUD_REDIS_ENABLED=true   \
          -e OWNCLOUD_REDIS_HOST=redis   \
          --volume owncloud_files:/mnt/data   \
          owncloud/server:10.0.7
    # template
    docker run -d   \
      --name owncloud  \
      --link mariadb:db   \
      --link redis:redis   \
      -p 80:80   \
      -p 443:443   \
      -e OWNCLOUD_DOMAIN=${OWNCLOUD_DOMAIN}   \
      -e OWNCLOUD_DB_TYPE=mysql   \
      -e OWNCLOUD_DB_NAME=owncloud   \
      -e OWNCLOUD_DB_USERNAME=owncloud   \
      -e OWNCLOUD_DB_PASSWORD=owncloud   \
      -e OWNCLOUD_DB_HOST=db   \
      -e OWNCLOUD_ADMIN_USERNAME=${OWNCLOUD_ADMIN_USERNAME}   \
      -e OWNCLOUD_ADMIN_PASSWORD=${OWNCLOUD_ADMIN_PASSWORD}   \
      -e OWNCLOUD_REDIS_ENABLED=true   \
      -e OWNCLOUD_REDIS_HOST=redis   \
      --volume owncloud_files:/mnt/data   \
      # specified owncloud/server:latest
      owncloud/server:${OWNCLOUD_VERSION}
        # tem
        export OWNCLOUD_VERSION=10.0
        export OWNCLOUD_ADMIN_USERNAME=admin
        export OWNCLOUD_ADMIN_PASSWORD=admin
        export OWNCLOUD_DOMAIN=localhost
        export OWNCLOUD_HTTP_PORT=80
        export OWNCLOUD_HTTPS_PORT=443
  ################ 3. Nextcloud with Docker   ################
    直接使用nextcloud:latest 内部打包了数据库和apache
    docker pull nextcloud
    docker run -d -p 8080:80 nextcloud  #启动到本地服务器
    # nextcloud命令, container_id 完成的ID或前3位
    docker  exec --user www-data container_id php occ  xx_cmd
    #  docker exec --user www-data 753 php occ

    # 创卷，数据放本地， 备份
    docker volume create nextcloud_mysql
    docker volume create nextcloud_data
    docker volume create nextcloud_backup
    # 准备Mariadb
    docker pull mariadb
    # 启动db
    # mariadb add new user, only have grant user@localhost
    # access denied: need add %(wildchar通配符), user@`%` means any ip can connect
    # or creat new database,
    # port 3306
    docker run -d \
          --name mariadb \
          -e MYSQL_ROOT_PASSWORD=admin \
          -e MYSQL_USER=admin \
          -e MYSQL_PASSWORD=nextcloud \
          -e MYSQL_DATABASE=nextcloud \
          --volume nextcloud_mysql:/var/lib/mysql \
          --volume nextcloud_backup:/var/lib/backup \
          --restart unless-stopped \
          mariadb:latest

    docker run -d \
          --name nextcloud \
          --link mariadb:db \
          -e DB_HOST=db \
          -e DB_TYPE=mysql \
          -e DB_NAME=nextcloud \
          -e DB_USER=nextcloud \
          -e DB_PASSWORD=nextcloud \
          -e NEXTCLOUD_ADMIN_USER=admin \
          -e NEXTCLOUD_ADMIN_PASSWORD=123456 \
          -e DOMAIN=localhost \
          -v nextcloud_data:/var/www/html \
          --restart unless-stopped \
          nextcloud:18-fpm-alpine
     # nginx配置: https://github.com/nextcloud/docker/blob/master/.examples/docker-compose/insecure/mariadb/fpm/web/nginx.conf
     docker run -d \
          -p 8080:80 \
          --name nginx \
          --link nextcloud:app \
          --link mariadb:db \
          -v /home/cooler/nginx.conf:/etc/nginx/nginx.conf:ro \
          --volumes-from nextcloud \
          --restart unless-stopped \
          nginx:latest

    # this version include apache
    docker pull nextcloud:latest
    docker run -d \
          -p 8080:80 \
          --name nextcloud \
          --link mariadb:db \
          -e DB_HOST=db \
          -e DB_TYPE=mysql \
          -e DB_NAME=nextcloud \
          -e DB_USER=nextcloud \
          -e DB_PASSWORD=nextcloud \
          -e NEXTCLOUD_ADMIN_USER=admin \
          -e NEXTCLOUD_ADMIN_PASSWORD=123 \
          -e DOMAIN=localhost \
          -v nextcloud_data:/var/www/html \
          nextcloud:latest
        #  another version :nextcloud:fpm
          # virsion:13
    # when first run, database host is db, not localhost
   ################  4. PostgreSQL ################
    docker pull postgres:12.3-alpine
    docker run --name test_postgres -e POSTGRES_PASSWORD=mypw -d postgres:12.3-alpine
    docker exec -it test_postgres psql -U postgres


=========================== 2. Dock GUI Instances ===========================
  GUI: ## jessfraz @ github
    Chrome:
      ## RUN
      sudo docker run -it --rm \
              -e 'LANG=C.UTF-8'  \
              --net host --cpuset-cpus 0 \
              --memory 512mb \
              -v /tmp/.X11-unix:/tmp/.X11-unix \
              -e DISPLAY=unix$DISPLAY \
              -v $HOME/Downloads:/root/Downloads \
              --security-opt seccomp=$HOME/chrome.json \
              --device /dev/snd \
              --device /dev/dri \
              -v /dev/shm:/dev/shm \
              --name chrome \
              jess/chrome \
              # avoid error: Operation not permitted, cmd for chrome self
              --privileged \
              --no-sandbox \
              --user-data-dir
