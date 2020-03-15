################################ VirtualBOX 安装Archlinux ################################
#  设置两张网卡 一张 NAT,访问外网； 一张Host-Only，访问宿主机， 使用putty 或git bash访问
#  当前用途： 1,2,3 based on docker
#	1. neteasemusic  unlock  ----done by:
#			pacman -S docker
#			docker pull nondanee/unblockneteasemusic
#			# add -p t expose port 8080 to host mathine
#			docker  run -p 8080:8080 -p 8081:8081 nondanee/unblockneteasemusic
#	2. dnscrypt-proxy -- to be done
#			downloading
#   3. dnsmasq -- to be done
#			odocker pull your repo ()
#			or built it : touch Dockerfile
#			docker build -t dnsmasq3 .
#			# create setting files, mkdir dnsmasq_docker
#   4. github -- to be done
#			pacman -S git
#	5. python env - - to be done
#			pacman -S python2
#  遗留问题：(windows环境）
#  1. 当前还有范围时偶尔被拒绝的问题，待处理， 可用faillog -r  暂时解决下
#  2. sftp访问不了？ （git bash sftp可以访问）， 似乎跟问题1有联系， 前面几次会报错，但没锁，等一段时间能登陆上

################################  开始 ################################
# 确定系统启动方式， 无efi目录则是BIOS
ls /sys/firmware
# 查看并创建 sda1 磁盘，
# 以LVM方式安装系统/boot需要先分区并设置磁盘类型 8e （LVM)，才能正常安装grub引导
# 同时第一个分区前最后空出2M空间，grub会放置core.img，用于引导启动， 即新建第一个分区时，开始扇区加4096K，即从6144开始
fdisk -l
fdisk /dev/sda
> t
> 8e
# 查看可以用于创建LVM的盘
lvmdiskscan
#  LVM流程， 先创建物理盘PV（对应实际的硬盘分区）， 将PV组成卷组VG（相当于创建一个大的盘用来创建分区），
#  在VG中创建逻辑卷LV（实际使用的分区）
#  创建PV
pvcreate /dev/sda1
pvdisplay
pvscan
# 创建VG
vgcreate VG /dev/sda1
vgdisplay
#  创建LV
lvcreate -L 512M VG -n lvol_boot  # 521M
lvcreate -L 512M VG -n lvol_swap
lvcreate -l 100%FREE VG -n lvol_root  # 全部可用空间
lvdisplay
lvdisplay | grep -iE 'path|size'
# 激活VG（当前只是确认已激活）
vgchange -ay
# 创建并打开交换分区
mkswap /dev/VG/lvol_swap
swapon /dev/VG/lvol_swap
# 挂载目录，先挂载/ , 在挂载其他目录
mkfs.ext4 /dev/VG/lvol_root
mkfs.ext4 /dev/VG/lvol_boot
# 挂载 /
mount /dev/VG/lvol_root /mnt
# 在 /中创建/boot
mkdir -p /mnt/boot
# 挂载 /boot
mount /dev/VG/lvol_boot /mnt/boot
# 设置镜像源 （ 中间会有多余 --- )
cp /etc/pacman.d/mirrorlist .
grep 'China' -A 1 mirrorlist > chinamirror
cat chinamirror > /etc/pacman.d/mirrorlist
# 安装系统到/,  如果使用了LVM，则需要安装lvm2， 后续在/etc/mkinitcpio.conf 中要加入lvm2，否则系统无法启动
# 在此处最好也安装 文本编辑器，man, info帮助
# dhcpcd,dhclient 可以进入系统后安装，不过最好检查下，安装完成的系统是否包含dhcp，，否则安装完成后无法使用网络
pacstrap /mnt base linux linux-firmware lvm2   > pacstrap.log &
tail -f pacstrap.log
# 设置系统卷标（系统启动是挂载盘), 设置后最好确认下
genfstab -U /mnt >> /mnt/etc/fstab
cat /mnt/etc/fstab
########################## 切换到新安装的系统
arch-chroot /mnt
########################## 新系统设置
# 时区
ln -sf /usr/share/zoneinfo/Asia/Chongqing /etc/localtime
# UTC时间
hwclock --systohc
# 本地化编码 zh_CN.UTF-8, en_US.UTF-8
vim /etc/locale.gen
locale-gen
# 设置网络相关， 主要是 主机名 和hosts
echo "Archer" > /etc/hostname
vim /etc/hosts    如下：
127.0.0.1       localhost
::1             localhost
127.0.0.1       Archer.localdomain      Archer
# 检查
ping archer
# 配置 lvm 并重新生成Initramfs
vim /etc/mkinitcpio.conf    如下，在block 和filesystem 中间加上lvm2：
HOOKS=(base udev autodetect modconf block lvm2 filesystems keyboard fsck)
# 重新生成Initramfs
mkinitcpio -P
# 设置root用户密码
passwd
# 安装grub,并配置引导
pacman -S grub
# 安装引导，最好使用整个盘sda，而不是某个分区（磁盘类型一定要匹配 linux lvm）
grub-install --target=i386-pc /dev/sda
# 生成配置文件，grub启动时会加载（之前多次忘记配置，系统无法启动）
grub-mkconfig -o /boot/grub/grub.cfg
# 添加普通用户，生成主目录，默认bash,配置密码
useradd -m -G wheel -s /bin/bash archer
passwd archer
# 检查新系统中是否有dhcp服务， 执行dhcp 看是否有命令， 否则重启进入新系统无法使用网络
# 当然也可用镜像重新进入,挂载后使用chroot再次安装
# 安装 dhcp
pacman -S dhcpcd dhclient
# 可后续在新系统中安装，不过最好先把VIM安装了，方便使用
# 主要是 vim 和  ntfs， ext2,ext4 的文件系统， 以及 man 和 info d的帮助信息， 默认bash的补全
pacman -S vim ntfs-3g e2fsprogs man-db man-pages texinfo  bash-completion
# 退出新系统
exit
###########  如果需要可以创建一个备份目录用于备份镜像中一些不错的配置
cp -rfp . /mnt/home/bk
cp -rfp .* /mnt/home/bk
############## 安装完成，解挂载，重启进入新系统
umount -R /mnt
reboot
################################  完成 ################################

################################  问题 ################################
1. faillog 报 /var/log/faillog 不存在（  faillog  和之前用的faillock 相似，查看登陆失败信息，解锁等）, bug: 使用tallylog
	创建一个 touch /var/log/faillog, chmod 600 /var/log/faillog , 目前就这样，似乎时 /etc/pam.d/system-login 中pam_tally2.so存放
	失败记录， 和 /var/log/talllylog 似乎相同，目前只使用tallylog， pam_tally.so似乎问题更多,
