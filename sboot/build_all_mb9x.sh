#!/bin/bash
clear
echo -e "\033[37;41;1mStart : $(date)\033[0m"
rm -rf bd_CUS08VL_17MB9*
color=44
config_file_prefix=.config.nugget.mb*

for config_file in $config_file_prefix
do
	echo -e "\033[37;${color};1m +++++ building ${config_file} +++++ \033[0m"

	# make clean & make config & make
	make -s clean
	cd ../u-boot-2011.06
	make -s clean
	cd ../sboot
	rm .config
	cp ${config_file} .config
	make -s silentoldconfig
	make -s

	# check mboot type
  if [[ "${config_file}" == *low* ]]; then
    islow=1
  else
    islow=0
  fi
  if [[ "${config_file}" == *97* ]]; then
    is97=1
  else
    is97=0
  fi
  if [[ "${config_file}" == *98* ]]; then
    is98=1
  else
    is98=0
  fi

  # create target folder
	if [ $is97 == 1 ]; then
	  target_folder="bd_CUS08VL_17MB97"
	fi
	if [ $is98 == 1 ]; then
	  target_folder="bd_CUS08VL_17MB98"
	fi
  if [ ! -d "$target_folder" ]; then
	  mkdir $target_folder
	fi

  if [ $is97 == 1 ]; then
    if [ $islow == 1 ]; then
      target_file="mboot_mb97_low.bin"
    else
      target_file="mboot_mb97.bin"
    fi
  elif [ $is98 == 1 ]; then
  	if [ $islow == 1 ]; then
      target_file="mboot_mb98_low.bin"
    else
      target_file="mboot_mb98.bin"
    fi
  else
  	target_file="mboot.bin"
  fi
  
  cp ./out/mboot.bin ./"$target_folder"/"$target_file"
  sleep 3
	echo -e "\033[37;${color};1m ----- $target_file copied to $target_folder ----- \033[0m"
	echo " "
done
echo -e "\033[37;41;1mEnd : $(date)\033[0m"
exit 0
