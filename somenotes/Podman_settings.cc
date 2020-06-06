#### 目前要暴露1024以下端口的使用docker，（podman比较麻烦），其他都用podmand

# 用podman 替换docker， podman不再用root权限等提升较大
pacman -S podman
# 创建subuid, subgid
touch /etc/subuid
touch /etc/subgid
# 为要使用podman的用户添加namespace
# 最好设置大一点，否则可能出现id不够的情况 65535+
sudo usermod --add-subuids 12000-22100 --add-subgids 12000-22100 cooler
# rootless evn needed
sudo pacman -S slirp4netns fuse-overlayfs (may already provided)
#  需要保证/proc/sys/kernel/unprivileged_userns_clone 值为 1

# 一些rootless还在考虑、开发中，https://github.com/containers/libpod
#  目前修改过的
1.  <1024的端口绑定, 修改unprivileged_port 开始端口
sysctl net.ipv4.ip_unprivileged_port_start=53
2 . ping (net.ipv4.ping_group_range=0 $MAX_UID 即userid包含在0 - $MAX_UID)
sysctl -w "net.ipv4.ping_group_range=0 2000000"
3. 如果容器访问本地磁盘有问题，改变selinux权限（没这样用过）
chcon -Rt svirt_sandbox_file_t /xxx/yyyyyy/
# 关闭所有container（更新用户信息）
podman system migrate
# 检查podman
podman info
# 默认源（多个地址 dockerhub, fedora, quayio等，若要固定，修改配置）
# 在镜像前家源地址，也可指定源
/etc/containers/registries.conf
# images signature
/var/lib/containers
# containers path
~/.local/share/containers/
# 从docker 迁移镜像
# podman pull docker-daemon:postgres:12.3-alpine
docker images |awk '{print $1":"$2}' |grep -v REP | xargs -i{} podman pull docker-daemon:{}
