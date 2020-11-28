#!/bin/bash
CHIP=$1

if [ "$1" == "" ]; then
    echo "Warning, please input the argument!"
	echo "ex: sh genlink.sh a3"
    exit 1
fi

test -d ./u-boot-2011.06/include/mstar
if [ $? != 0 ]
then
	mkdir ./u-boot-2011.06/include/mstar
	echo "mkdir ./u-boot-2011.06/include/mstar"
fi

test -d ./u-boot-2011.06/include/mstar/core
if [ $? != 0 ]
then
	mkdir ./u-boot-2011.06/include/mstar/core
	#echo "mkdir ./u-boot-2011.06/include/mstar/core"
fi

test -L ./u-boot-2011.06/lib/mstar
if [ $? != 0 ]
then
# link MstarCore
ln -fs ../../MstarCore/bsp/$CHIP/lib/ ./u-boot-2011.06/lib/mstar
ls MstarCore/bsp/$CHIP/include/* | xargs -I FILES ln -s ../../../../FILES ./u-boot-2011.06/include/mstar/core/ 
ls MstarCore/include/* | xargs -I FILES ln -s ../../../../FILES ./u-boot-2011.06/include/mstar/core/
ln -fs ../../MstarCore/board/ ./u-boot-2011.06/board/mstar
ln -fs ../../MstarCore/src/drivers/ ./u-boot-2011.06/drivers/mstar

echo "-- Construct symbolic link OK --"
else
echo "-- already link --"
fi