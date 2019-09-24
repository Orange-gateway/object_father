#!/system/bin/sh
mount -o remount /system
num=0
while [ 1 ]
do
	flag=$(ps | grep gateway | grep -v "grep" | wc -l)
	if [ $flag -ne 0 ]; then
		num=0
		sleep 5
	else
		let num+=1
		if [ $num = 5 ]; then
			rm /system/bin/gateway
			cp /system/bin/gateway_first /system/bin/gateway
			/system/bin/gateway /dev/ttyS2 &
			sleep 1
		else
			/system/bin/gateway /dev/ttyS2 &
			sleep 1
		fi
	fi
done
