#!/bin/csh
echo "Sboot Releaser '"$0"'"

function printUsage(){
 echo "Please use '$0 [janus|titania4|titania7|titania8|titania9|titania12|titania13|uranus4|janus2|maria10|amber1|amber2|nasa]'"
}

EN_1=0
EN_2=0
EN_3=0
EN_4=0
EN_5=0
EN_6=0
EN_7=0
EN_8=0
EN_9=0
EN_10=0
EN_11=0
EN_12=0
EN_13=0
case $1 in
 "janus")
  EN_1=1
 ;;
 "titania4")
  EN_2=1
 ;;
 "titania7")
  EN_3=1
 ;;
 "titania8")
  EN_4=1
 ;;
 "titania9")
  EN_5=1
 ;;
 "uranus4")
  EN_6=1
 ;;
 "janus2")
  EN_7=1
 ;;
 "titania13")
  EN_8=1
 ;;
 "maria10")
  EN_9=1
 ;;
 "titania12")
  EN_10=1
 ;;
 "amber1")
  EN_11=1
 ;;
 "amber2")
  EN_12=1
 ;;
 "nasa")
  EN_13=1
 ;; 
 *)
  printUsage;
  exit 1;
 ;;
esac

echo "Compress source files for '"$1"'"
#ALL_F=`find . | xargs | sed 's/^\.\{1\} //g'`
ALL_F=`find . -type f -print | xargs | sed 's/^\.\{1\} //g'`
if [ "$EN_1" != "1" ]; then
 F1=`echo $ALL_F | sed s/[[:alnum:]/_-.]*janus[[:alnum:]/_-{}.]*//g`
else
 F1=$ALL_F
fi
if [ "$EN_2" != "1" ]; then
 F2=`echo $F1 | sed s/[[:alnum:]/_-.]*titania4[[:alnum:]/_-.]*//g`
else
 F2=$F1
fi
if [ "$EN_3" != "1" ]; then
 F3=`echo $F2 | sed s/[[:alnum:]/_-.]*titania7[[:alnum:]/_-.]*//g`
else
 F3=$F2
fi
if [ "$EN_4" != "1" ]; then
 F4=`echo $F3 | sed s/[[:alnum:]/_-.]*titania8[[:alnum:]/_-.]*//g`
else
 F4=$F3
fi
if [ "$EN_5" != "1" ]; then
 F5=`echo $F4 | sed s/[[:alnum:]/_-.]*titania9[[:alnum:]/_-.]*//g`
else
 F5=$F4
fi
if [ "$EN_6" != "1" ]; then
 F6=`echo $F5 | sed s/[[:alnum:]/_-.]*uranus4[[:alnum:]/_-.]*//g`
else
 F6=$F5
fi
if [ "$EN_7" != "1" ]; then
 F7=`echo $F6 | sed s/[[:alnum:]/_-.]*janus2[[:alnum:]/_-{}.]*//g`
else
 F7=$F6
fi
if [ "$EN_8" != "1" ]; then
 F8=`echo $F7 | sed s/[[:alnum:]/_-.]*titania13[[:alnum:]/_-.]*//g`
else
 F8=$F7
fi
if [ "$EN_9" != "1" ]; then
 F9=`echo $F8 | sed s/[[:alnum:]/_-.]*maria10[[:alnum:]/_-.]*//g`
else
 F9=$F8
fi
if [ "$EN_10" != "1" ]; then
 F10=`echo $F9 | sed s/[[:alnum:]/_-.]*titania12[[:alnum:]/_-.]*//g`
else
 F10=$F9
fi
if [ "$EN_11" != "1" ]; then
 F11=`echo $F10 | sed s/[[:alnum:]/_-.]*amber1[[:alnum:]/_-.]*//g`
else
 F11=$F10
fi
if [ "$EN_12" != "1" ]; then
 F12=`echo $F11 | sed s/[[:alnum:]/_-.]*amber2[[:alnum:]/_-.]*//g`
else
 F12=$F11
fi
if [ "$EN_13" != "1" ]; then
 F13=`echo $F12 | sed s/[[:alnum:]/_-.]*nasa[[:alnum:]/_-.]*//g`
else
 F13=$F12
fi
ALL_FILES=$F13
echo $ALL_FILES
O_FILE=../sboot_$1.tar.gz
tar -czvf $O_FILE $ALL_FILES
echo "Compress files done. Please see '"$O_FILE"'"
