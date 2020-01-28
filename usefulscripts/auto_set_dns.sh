#! /bin/bash

function check_ips()
{
    cur_ip=`ip -4 a|grep inet|grep 192 |awk -F' ' '{print $2}'|awk -F/ '{print$1}'`
    echo "current ip addr:$cur_ip"

    old_ip=`grep 'server=192' /home/cooler/dnsmasq_docker/dnsmasq_basic.conf |awk -F= '{print$2}'|awk -F# '{print$1}'`
    #old_ip=`grep 'server=192' dnsmasq_basic.conf |awk -F= '{print$2}'|awk -F# '{print$1}'`
    echo "old ip addr:$old_ip"
    if [ $cur_ip == $old_ip ];then
   	echo "current ip and old ip are the same!"
	return 3
    fi
}

modify_dnsmasq_settings(){
    sed -i s#$old_ip#$cur_ip#g /home/cooler/dnsmasq_docker/dnsmasq_basic.conf
    if [ $? -eq 0 ]; then
	echo "set dnsmasq's cur_ip success."
	echo "# Current setting:"
	echo  `grep 'server=192.168' /home/cooler/dnsmasq_docker/dnsmasq_basic.conf`
	docker restart dnsmasq
    else
	echo "execute set cmd faild: $?"
	echo "# Current setting:"
	echo  `grep $old_ip /home/cooler/dnsmasq_docker/dnsmasq_basic.conf`
	return 1
    fi
}


modify_dnsscypt_proxy_settings(){
    sed -i s#$old_ip#$cur_ip#g /home/cooler/dnscrypt-proxy/example-dnscrypt-proxy.toml
    if [ $? -eq 0 ]; then
	echo "set dnscrypt-proxy cur_ip success."
	echo "# Current setting:"
	echo `grep $cur_ip /home/cooler/dnscrypt-proxy/example-dnscrypt-proxy.toml`
    else
	echo "execute set cmd faild: $?"
	echo "# Current setting:"
	echo `grep $old_ip /home/cooler/dnscrypt-proxy/example-dnscrypt-proxy.toml`
	return 1
    fi
}


main(){
    check_ips
    if [ $? -eq 3 ]; then
	echo "No differrences between ips, exit now!"
	exit 0
    fi

    modify_dnsmasq_settings
    if [ $? -eq 1 ]; then
	echo "Modify dnsmasq setting failed!"
	exit 1
    fi

    modify_dnsscypt_proxy_settings
    if [ $? -eq 1]; then
	echo "Modify dnscrypt proxy setting failed!"
	exit 1
    fi
}

main
