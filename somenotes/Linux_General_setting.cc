Attack: mdk3

Manjaro( Arch ):
  # verify ISO
  gpg  --verify *.sig *

  ## Use Arch linux mirrors to install brand new packages
  ## Manjaro mirrors to upgrade system

  ## systemd默认的时间工具
  ## 设置 系统时间, windows 使用的localtime, MAC, linux都是UTC(与格林威时间大致相同)
  ## 直接开启ntp同步时间就行， 待确定如何修改同步服务器
  ## 不需要再执行 hwclock --systohc， 也不会和windows时间冲突？？
  timesynctl set-ntp true
  ##  是否启用localtime
  ## timedatectl set-local-rtc true/false/0/1
  ## 查看系统时间同步状态
  ## timedatectl timesync-status
  ## timedatectl show
  ## timedatectl status

  ## python3 has been used , do not link /usr/bin/python to python2
  ## use 'ls -l /usr/bin/python' to check

  ## 自动选出国内源
  sudo pacman-mirrors -i -c China -m rank
  sudo pacman -Syyu
  ## 手动
  ## USTC
  # Arch linux mirror
  Server = https://mirrors.ustc.edu.cn/archlinux/$repo/os/$arch
  # Arch linux cn mirrors
  # add two lines blow to  /etc/pacman.conf
  [archlinuxcn]
  Server = https://mirrors.ustc.edu.cn/archlinuxcn/$arch
  # then install archlinuxcn-keyring to import GPG key
  sudo pacman -Sy archlinuxcn-keyring

  ## VirtualBox
  ## make sure BIOS-setting is ok,the kernel should use what 'uname -r' shows
  ## not use *manjaro* kernel, but a version-clearly kernal
  sudo pacman -S virtualbox
  sudo modprobe vboxdrv
  sudo pacman -Sc
  ## docker sources
  dnsmasq
        build yourself
  nextcloud
  diygod
        docker pull diygod/rsshub
        docker run -d --name rsshub -p 1200:1200 diygod/rsshub
        http://127.0.0.1:1200/
  numdup
        forked
  163proxy
        forked
  ## Manjaro conflict
  sudo rm -rf chrome/chromium/firefox
  #sudo rm  /usr/lib/firefox/distribution/distribution.ini
  #sudo mv /etc/lsb-release backup/lsb-release.from_etc
  # in gnome desktop , not needed
  sudo pacman -R firefox empathy  evolution steam-manjaro transmission-gtk uget
  ## 选择最小包 minmal包没下面的问题
  ## some default setting from manjaro community
  ## sudo rm -rf /usr/lib/chrome/chromium/firefox
  ## sudo rm -rf /usr/lib/chrome/master_preferences
  ## sudo rm -rf /usr/lib/chromium/bookmarks.html
  ## sudo rm -rf /usr/lib/chromium/master_preferences
  cat /etc/lsb-release
  ## sudo rm -rf  /usr/lib/chrome/bookmarks.html
  #sudo pacman -R firefox-i18n-zh-cn firefox-i18n-en-us thunderbird-i18n-en-us thunderbird-i18n-zh-cn npapi-vlc vlc-nightly
  #sudo pacman -R firefox thunderbird transmission-gtk

  # 中文配置， 得先安装字体
  sudo pacman -S ttf-roboto noto-fonts ttf-dejavu
  # 文泉驿
  sudo pacman -S wqy-bitmapfont wqy-microhei wqy-microhei-lite wqy-zenhei
  # 思源字体 及 abobe开源
  sudo pacman -S noto-fonts-cjk adobe-source-han-sans-cn-fonts adobe-source-han-serif-cn-fonts
  ##  mkdir .config/fontconfig
  # 自动微调 微调 抗锯齿 内嵌点阵字体
  vim .config/fontconfig/fonts.conf  增加字体配置文件，更好看，不虚化，参加其他配置文件

  # 主要软件， 不要 pepper-flash flashplugin gedit ， virtualbox根据内核单独配置， office, meld (diff GUI), brige: qv2ray and it's core
  sudo pacman -S arc-gtk-theme  vlc vim audacity audacious inkscape bleachbit stellarium git nmap screenfetch tree xed docker firefox chromium transmission-gtk thunderbird atom curl redshift fcitx fcitx-googlepinyin fcitx-gtk3 fcitx-configtool bash-completion virtualbox libreoffice-still meld
  # 增加docker 用户
  sudo groupadd docker
  sudo usermod -aG docker $USER

  ## Some packages , Sublime-Style-Column-Selection for atom
  # tools http-api test, download
  sudo pacman -S httpie aria2 curl uget
  # others : gnome map, redshift, net-tools for ifconfig and route, bind-tools(dnsutils) for dig and nslookup

  # night light, ~/.config/redshift.conf
  sudo pacman -S redshift python-xdg (for redshift) #Okular(PDF)

  ## fcitx 单独配置部分参数
  ## sudo pacman -S fcitx fcitx-googlepinyin fcitx-gtk3 fcitx-configtool (fcitx-im)
  ## add script to ~/.xprofile starts when booting to make variables effective
  export GTK_IM_MODULE=fcitx
  export QT_IM_MODULE=fcitx
  export XMODIFIERS=@im=fcitx

  ## Netease-cloud-music 安装中文源后，网易云
  ## download official .deb packages from music.163.com is much better
  ## replace all packs after install via pacman
  sudo pacman -S netease-cloud-music

  ## 使用LVM管理 home 及swap, 先在界面创建，免得操作失误
      ## lsblk
      ## fdisk /dev/sdb1  or parted -l
      # PV
      pvcreate /dev/sdb1
      pvdisplay
      pvscan
      # VG
      vgcreate VG /dev/sdb1
      vgdisplay
      # LV
      lvcreate -L 112G VG -n lvol_home
      lvcreate -l 100%FREE VG -n lvol_swap
      lvdisplay
      lvdisplay | grep -iE 'path|size'
      vgchange -ay
      # 格式化并备份挂载home
      mkf.ext4 /dev/VG/lvol_home
      /bin/cp -rfp /home /home.bk
      mount /dev/VG/lvol_home /home
      /bin/cp -rfp /home.bk/* /home
      # 启用swap
      mkswap /dev/VG/lvol_swap
      swapon /dev/VG/lvol_swap
      # 查看UUID， 并在fstab中设置启动挂载
      blkid /dev/VG/lvol_home
      blkid /dev/VG/lvol_swap
      vim /etc/fstab
      # 查看内存是否有swap

  ## Python2.7 && packages
  sudo pacman -S python2-pip
  sudo ln -sf /usr/bin/pip2 /usr/bin/pip
  ## all pack are install to ~/.local/ , need to add ~/.local/bin to env path
  pip install --user ipython virtalenv(?)

  # PATH : get settings from linuxmint 18.2 Sonya, set in ~/.profile
  # set PATH so it includes user's private bin directories
  PATH="$HOME/bin:$HOME/.local/bin:$PATH"
  source .profile

  ## Some problems may meet:
    # database lock
    sudo rm /var/lib/pacman/db.lck
    # GPG keys
    sudo rm -r /etc/pacman.d/gnupg
    sudo pacman -Sy gnupg archlinux-keyring manjaro-keyring
    sudo pacman-key --init
    sudo pacman-key --populate archlinux manjaro #load keys
    sudo pacman-key --refresh-keys # refresh
    sudo pacman -Sc
    # VLC start no GUI interface, pacman -Qi packagename
    VLC media player 2.2.6 Umbrella (revision 2.2.6-0-g1aae78981c)
    # [00005639c0cd63a8] core libvlc: 正在以默认界面运行 vlc。使用“cvlc”可以无界面模式使用 vlc。
    # [00005639c0e252b8] skins2 interface error: no suitable dialogs provider found (hint: compile the qt4 plugin, and make sure it is loaded properly)
    # [00005639c0e252b8] skins2 interface error: cannot instantiate qt4 dialogs provider
    # [00005639c0e252b8] [cli] lua interface: Listening on host "*console".
    # VLC media player 2.2.6 Umbrella
    sudo pacman -S qt4

Linux mint:
  ## Remove official slow mirrors
  sudo vi /etc/apt/sources.list.d/official-package-repositories.list
  sudo apt-get update && sudo apt-get upgrade -y
  sudo systemctl reboot

  ## Some useful packages
  ## autoconf automake fakeroot gdb gdb-doc cgdb
  sudo apt-get update && sudo apt-get install chromium-browser chromium-browser-l10n vim vlc gparted filezilla audacity audacious inkscape bleachbit gcc openssh-server wireshark remmina* stellarium cheese shutter gedit git nmap screenfetch fcitx fcitx-config-gtk fcitx-frontend-all fcitx-module-dbus fcitx-libpinyin fcitx-sunpinyin fcitx-pinyin fcitx-ui-classic tree
  ## Fcitx config
  im-config #  start fcitx

  ## Flashplugin for chromium
  sudo apt-get install pepperflashplugin-nonfree
  sudo update-pepperflashplugin-nonfree --install

  ## hosts file: https://github.com/googlehosts/hosts/tree/master/hosts-files
  sudo gedit /etc/hosts

  ## some zh-CN language packs
  sudo apt-get install language-pack-zh-hans language-pack-gnome-zh-hans firefox-locale-zh-hans thunderbird-locale-zh-hans libreoffice-l10n-zh-cn

  ## Python2.7
  ## better not use sudo to pip installation
  sudo apt-get install python-pip
  pip install --user setuptools virtualenv
  mkdir ...
  virtualenv venv
  source venv/bin/activate
  sudo apt-get install python-pip
  pip install --user setuptools
  pip install --user --upgrade pip
  pip install --user scrapy scapy requests lxml selenium
  pip install --user matplotlib (sudo aptget install python-dev)
  pip install ipython
  deactivate
  ## Mongo linux version

Fedora26: (install sqlite to completion)
	yum clean all
	yum makecache
	yum upgrade -y
	systemctl reboot

  ## rmpfusion : 3rd part packages
  ## sudo dnf install https://download1.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm https://download1.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
	sudo dnf install https://mirrors.ustc.edu.cn/rpmfusion/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm https://mirrors.ustc.edu.cn/rpmfusion/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm

  ## choose fastest mirrors for yum
  yum install sqlite yum-plugin-fastestmirror

  ## VirtualBox
  # disable Secure Boot
	# first (for start virtualmathines error, /sbin/vbconfig)

  ## Some useful packages
  dnf install vim gparted filezilla audacity audacious stellarium cheese gedit git nmap screenfetch tree chromium gnome-tweak-tool inkscape openssh-server wireshark nano kate fcitx fcitx-pinyin im-chooser fcitx-configtool thunderbird gimp libreoffice-langpack-zh-Han* bleachbit vlc gconf-editor unrar

  ## Fcitx config
  im-chooser

  ## Chromium
  # Install chrome is much better for no considering of flashplugins
  #sudo tar -zxvf flash_player_ppapi_linux.x86_64.tar.gz -C /usr/lib64/chromium-browser/PepperFlash/

  ## Remove some packs
  sudo dnf remove evolution rhythmbox

  ## Hostname
  hostnamectl status
  hostnamectl set-hostname --static 'Color'

  ## Python2.7
  pip install --user requests lxml selenium scapy
  # one of them or all of them
  # libxslt-devel
  sudo dnf install python-devel libslz-devel redhat-rpm-config
  # for matplotlibsss
  sudo dnf install python2-tkinter
  pip install --user ipython scrapy matplotlib


  ## netease-cloud-music
  sudo mv data/usr/lib/netease-cloud-music /usr/lib
  sudo mv data/usr/share/applications/netease-cloud-music.desktop /usr/share/applications/
  sudo mv data/usr/share/doc/netease-cloud-music /usr/share/doc/
  sudo mv data/usr/share/icons/hicolor/scalable/apps/netease-cloud-music.svg /usr/share/icons/hicolor/scalable/apps/
  sudo vim /usr/share/applications/netease-cloud-music.desktop
	Icon=/usr/share/icons/hicolor/scalable/apps/netease-cloud-music.svg
