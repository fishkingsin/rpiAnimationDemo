#!/bin/bash
#crop
target="/Volumes/data_RAID/james.kong/of_v0073_osx_release/apps/myApps/rpiAnimationDemo/bin/data/yuco_christmas_lunch_panorama.JPG"
a=0
size=270
for y in $(seq 0 3)
do
	for x in $(seq 0 39)
	do
		new=$(printf "%04d.png" ${a}) 
		dx=$((x*size))
		dy=$((y*size))
		echo $dx $dy
		echo $new
		convert $target -crop 270X270+$dx+$dy  $new
		let a=a+1
	done
done
