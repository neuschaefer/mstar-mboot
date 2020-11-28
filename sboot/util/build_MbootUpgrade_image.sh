#!/bin/bash

FILE_PART_READ_CMD="filepartload"
CRC_BIN="./crc"
FULL_ERASE=0
FLASH_IS_EMMC=0
SCRIPT_SIZE=0x4000
SPILT_SIZE=16384
HASH0_SIZE=0x2800
CPU_IS_ARM=1

function func_init_env_for_mboot(){
	#==============init env for mboot================================
    if [ "$FLASH_IS_NAND" == "1" ] ; then
    INPUT_IMG="../out/RomBoot.bin"
    else    
    INPUT_IMG="../out/mboot.bin"
    fi
	SCRIPT_FILE="mboot_script.txt"
	OUTPUT_IMG="MbootUpgrade.bin"
    #==============init env for mboot done===========================
}

function func_init_env_for_sboot(){
    #==============init env for mboot================================
    INPUT_IMG="../out/sboot.bin"
	SCRIPT_FILE="sboot_script.txt"
	OUTPUT_IMG="SbootUpgrade.bin"
    #==============init env for mboot done===========================
}

function func_clean(){
if [ -f "$SCRIPT_FILE" ]; then
    rm -rf $SCRIPT_FILE;
    rm -rf $OUTPUT_IMG;
fi
}

function func_init_common_env(){
    #==============init common env================================
	test -f $INPUT_IMG
    if [ $? != 0 ];then
        echo "Please Build Mboot Firstly !"
        exit 0
    fi
    INPUT_IMG_SIZE=$(stat -c%s $INPUT_IMG )
    if [ "$CPU_IS_ARM" == "1" ] ; then
        DRAM_BUF_ADDR=0x45000000
	else
		#Why 0x80210000?? In PM51 booting mode, PM51 is always alive in 0x80200000, and the size of PM.bin is 0x10000
        DRAM_BUF_ADDR=0x80210000
    fi
    #==============init common env end============================	
}

function func_set_crc_to_image(){
    #Set Only-Script CRC1
    $CRC_BIN -a $SCRIPT_FILE
    split -d -a 2 -b $SPILT_SIZE $SCRIPT_FILE $SCRIPT_FILE.tmp.
    cat $SCRIPT_FILE.tmp.01 >> $OUTPUT_IMG
    #Set Full-Bin CRC2
    $CRC_BIN -a $OUTPUT_IMG
    rm $SCRIPT_FILE.*
}

function func_copy_first_16byte(){
    #==============copy the first 16 bytes to last =================================
    dd if=$OUTPUT_IMG of=out.bin bs=16 count=1;
    cat out.bin >>$OUTPUT_IMG
    rm -rf out.bin
    #==============copy the first 16 bytes to last end=================================
}

function func_pad_script(){
    #==============pad script===============================
    ./align $SCRIPT_FILE $SCRIPT_SIZE

    #==============Mboot Align 4byte =======================
    ./align $INPUT_IMG 0x4
}

function func_update_mboot(){
    #==================   env init  ==========================
    func_init_env_for_mboot;
	func_clean;
	func_init_common_env;
    #================= script content ========================
	printf "$FILE_PART_READ_CMD 0x%x \$(UpgradeImage) 0x%x 0x%x\n" $DRAM_BUF_ADDR $SCRIPT_SIZE $INPUT_IMG_SIZE >> $SCRIPT_FILE
    if [ "$FLASH_IS_NAND" == "1" ] ; then
        if [ "$FLASH_IS_NAND_WITH_SECURITY" == "1" ] ; then
            printf "$CMD_FLASH_WRITE 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n" $DRAM_BUF_ADDR $(($DRAM_BUF_ADDR+0x10000)) $(($DRAM_BUF_ADDR+0x20000)) $(($DRAM_BUF_ADDR+0x30000)) $HASH0_SIZE $(($DRAM_BUF_ADDR+0x30000+$HASH0_SIZE)) $INPUT_IMG_SIZE >> $SCRIPT_FILE   
        else            
            printf "$CMD_FLASH_WRITE 0x%x 0x%x 0x%x 0x%x 0x%x\n" $DRAM_BUF_ADDR $(($DRAM_BUF_ADDR+0x10000)) $(($DRAM_BUF_ADDR+0x20000)) $(($DRAM_BUF_ADDR+0x30000)) $INPUT_IMG_SIZE >> $SCRIPT_FILE
        fi   
         printf "setenv CISRefresh\n" >> $SCRIPT_FILE
         printf "saveenv\n" >> $SCRIPT_FILE
    else
        if [ "$FULL_ERASE" == "1" ] ; then
            printf "$CMD_FLASH_EA\n" >> $SCRIPT_FILE
        fi
        printf "$CMD_FLASH_WRITE 0x%x %s 0x%x\n" $DRAM_BUF_ADDR $WRITE_TARGET $INPUT_IMG_SIZE >> $SCRIPT_FILE
    fi
    #================= script content done ====================
	func_post_process;
}

function func_update_sboot_emmc(){
    #==================   env init  ==========================
    func_init_env_for_sboot;
	func_clean;
	func_init_common_env;
    #================= script content ========================
	printf "$FILE_PART_READ_CMD 0x%x \$(UpgradeImage) 0x%x 0x%x\n" $DRAM_BUF_ADDR $SCRIPT_SIZE $INPUT_IMG_SIZE >> $SCRIPT_FILE
	if [ "$FULL_ERASE" == "1" ] ; then
	   printf "mmc erase.boot 1\n" >> $SCRIPT_FILE
	fi  
	printf "mmc write.boot 1 0x%x 0 0x%x\n" $DRAM_BUF_ADDR $INPUT_IMG_SIZE >> $SCRIPT_FILE
    #================= script content done ====================
	func_post_process;
}

function func_post_process(){
    echo "reset" >>$SCRIPT_FILE
	echo "% <- this is end of file symbol" >> $SCRIPT_FILE
    func_pad_script; # padding to $SCRIPT_SIZE(0x4000), and Mboot.bin align 4byte.
    cat $SCRIPT_FILE >> $OUTPUT_IMG
    cat $INPUT_IMG >> $OUTPUT_IMG
    func_set_crc_to_image;
    func_copy_first_16byte;
    cp $OUTPUT_IMG ../out/
}

function func_prompt(){
    #================prompt question==========================

printf "\033[0;31mIs ARM platform (Y/n)\033[0m"
read temp	
if [ "$temp" == "N" ] || [ "$temp" == "n" ]; then
	CPU_IS_ARM=0
fi	

printf "\033[0;31mMBoot Burn in Emmc ? (y/N)\033[0m"
read temp	
if [ "$temp" == "Y" ] || [ "$temp" == "y" ]; then
	FLASH_IS_EMMC=1
fi	

if [ "$FLASH_IS_EMMC" != "1" ]; then
    printf "\033[0;31mMBoot Burn in Nand ? (y/N)\033[0m"
    read temp
    if [ "$temp" == "Y" ] || [ "$temp" == "y" ]; then
        FLASH_IS_NAND=1
        printf "\033[0;31mSecure Rom boot ? (y/N)\033[0m"
        read temp
        if [ "$temp" == "Y" ] || [ "$temp" == "y" ]; then
            FLASH_IS_NAND_WITH_SECURITY=1
        fi    
    fi
fi

printf "\033[0;31mFully Erase ? (y/N)\033[0m"
read temp
if [ "$temp" == "Y" ] || [ "$temp" == "y" ]; then
    FULL_ERASE=1
fi
    #================prompt question end======================
}

function func_cmd_init(){
   #================cmd init==========================
if [ "$FLASH_IS_EMMC" == "1" ] ; then
    WRITE_TARGET="MBOOT"
    CMD_FLASH_EA="mmc erase.p MBOOT" 
    CMD_FLASH_WRITE="mmc write.p"
elif [ "$FLASH_IS_NAND" == "1" ] ; then
    WRITE_TARGET=""
    CMD_FLASH_EA=""
    if [ "$FLASH_IS_NAND_WITH_SECURITY" == "1" ] ; then 
        CMD_FLASH_WRITE="ncishash"
    else
        CMD_FLASH_WRITE="ncisbl"
    fi
else
   WRITE_TARGET="0"
   CMD_FLASH_EA="spi wp 0;spi ea;spi wp1"
   CMD_FLASH_WRITE="spi wrc"
fi
  #================cmd init end======================= 
}

#=========== main() Start Upgrade ===============
func_prompt;
func_cmd_init;
if [ "$FLASH_IS_EMMC" == "1" ] ; then
	func_update_sboot_emmc;
	echo "Build "$OUTPUT_IMG" Successful !!"
fi
	func_update_mboot;
echo "Build "$OUTPUT_IMG" Successful !!"
exit 0
#================= End Upgrade ==================
