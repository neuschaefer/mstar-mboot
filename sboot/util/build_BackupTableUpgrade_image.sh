#!/bin/bash

BACKUP_TABLE_IMG=$1
SPI_OFFSET=$2
OUTPUT_IMG="MstarUpgrade.bin"
FILE_PART_READ_CMD="filepartload"
SCRIPT_FILE="upgrade_table_script.txt"
PADDED_BIN="Padd.bin"
NEW_MBOOT=1

function func_clean(){
if [ -f "$SCRIPT_FILE" ]; then
	rm $SCRIPT_FILE;
	rm $OUTPUT_IMG;
fi
}
function func_set_dont_overwrite(){
	printf "dont_overwrite_init\n"  >$SCRIPT_FILE
}
function func_init_env_for_backup_table(){
    #==============init env for backup_table================================
	test -f $BACKUP_TABLE_IMG
	if [ $? != 0 ];then 
		echo "Please Build Mboot Firstly !"
		exit 0
	fi
    BACKUP_TABLE_IMG_SIZE=$(stat -c%s $BACKUP_TABLE_IMG )
	printf "BACKUP_TABLE_IMG_SIZE=$BACKUP_TABLE_IMG_SIZE\n"
    if [ "$NEW_MBOOT" == "1" ] ; then
        DRAM_BUF_ADDR=0x45000000
    else
        DRAM_BUF_ADDR=0x80000000
    fi
	SCRIPT_SIZE=0x4000
	SPILT_SIZE=16384 #depand on SCRIPT_SIZE
	DRAM_BUF_ADDR=$(($DRAM_BUF_ADDR+$SCRIPT_SIZE))
	printf "DRAM_BUF_ADDR=0x%x\n" $DRAM_BUF_ADDR
    #==============init env for backup table done===========================
}

function func_post_process(){
    #================Post-process=====================================
	CRC_BIN=$(find -name crc | sed '2,$d')
	

	cp $SCRIPT_FILE $SCRIPT_FILE.temp
	CRC_VALUE=`$CRC_BIN -a $SCRIPT_FILE.temp | grep "CRC32" | awk '{print $3;}'`
	split -d -a 2 -b $SPILT_SIZE $SCRIPT_FILE.temp $SCRIPT_FILE.temp.
	printf "script file crc %s\n" $CRC_VALUE
	cat $SCRIPT_FILE.temp.01 >> $OUTPUT_IMG
	rm $SCRIPT_FILE.temp
	rm $SCRIPT_FILE.temp.00
	rm $SCRIPT_FILE.temp.01
	
	CRC_BIN=$(find -name crc | sed '2,$d')
    $CRC_BIN -a $OUTPUT_IMG

    # Add dummy 4 bytes to keep 8-byte alignment
    if [ "$CHIP" == "u4" ] || [ "$CHIP" == "k1" ] ; then
        $CRC_BIN -a $OUTPUT_IMG
    fi
	
    printf "\033[0;31m$USB_IMG\033[0m done\n"
    #================Post-process done================================
}

function func_pad_script(){
    #==============pad script===============================
    SCRIPT_FILE_SIZE=$(stat -c%s $SCRIPT_FILE)
    PADDED_SIZE=$(($SCRIPT_SIZE-$SCRIPT_FILE_SIZE))
	printf "PADDED_SIZE=0x%x\n" $PADDED_SIZE
    
	if [ $PADDED_SIZE != 0 ]; then
        printf "\xff" >$PADDED_BIN
        for ((i=1; i<$PADDED_SIZE; i++))
        do
            printf "\xff" >>$PADDED_BIN
        done
    cat $PADDED_BIN >>$SCRIPT_FILE
    rm $PADDED_BIN
    fi
    #==============pad script done==========================
}
function func_update_mips_backup_table(){
    #==============update backup table===============================
	func_init_env_for_backup_table;
	func_clean;
	#func_set_dont_overwrite;
    #printf "$FILE_PART_READ_CMD %x $OUTPUT_IMG %x %x\n" $DRAM_BUF_ADDR $SCRIPT_SIZE $BACKUP_TABLE_IMG_SIZE >> $SCRIPT_FILE
	printf "spi_wp 0 \n" >> $SCRIPT_FILE
	printf "spi_eb %x %x\n" $SPI_OFFSET $(($SPI_OFFSET+0xFFFF))>> $SCRIPT_FILE
	printf "spi_wp 1 \n" >> $SCRIPT_FILE
	printf "spi_wrc %x %x %x\n" $DRAM_BUF_ADDR $SPI_OFFSET $BACKUP_TABLE_IMG_SIZE >> $SCRIPT_FILE
	printf "reset\n" >> $SCRIPT_FILE
    echo "% <- this is end of file symbol " >> $SCRIPT_FILE
	func_pad_script;
	
	cp $SCRIPT_FILE $OUTPUT_IMG
	./MergeBin.exe $BACKUP_TABLE_IMG $OUTPUT_IMG $SCRIPT_SIZE
	cp $OUTPUT_IMG ../out/
	
	
	func_post_process;
    #==============copy the first 16 bytes to last =================================
    dd if=$OUTPUT_IMG of=./out.bin bs=16 count=1;
    cat ./out.bin >>$OUTPUT_IMG
    rm -rf out.bin
    #==============update backup table done==========================	
}

function func_update_arm_backup_table(){
    #==============update backup table===============================
	func_init_env_for_mboot;
	func_clean;
	func_set_dont_overwrite;
    printf "$FILE_PART_READ_CMD %x $OUTPUT_IMG %x %x\n" $DRAM_BUF_ADDR $SCRIPT_SIZE $BACKUP_TABLE_IMG_SIZE >> $SCRIPT_FILE
	printf "spi wrc %x %x %x\n" $DRAM_BUF_ADDR $SPI_OFFSET $BACKUP_TABLE_IMG_SIZE >> $SCRIPT_FILE
	printf "reset\n" >> $SCRIPT_FILE
    echo "% <- this is end of file symbol" >> $SCRIPT_FILE
	func_pad_script;
	
	cp $SCRIPT_FILE $OUTPUT_IMG
	./MergeBin.exe $BACKUP_TABLE_IMG $OUTPUT_IMG $SCRIPT_SIZE
	cp $OUTPUT_IMG ../out/
	func_post_process;
    #==============copy the first 16 bytes to last =================================
    dd if=$OUTPUT_IMG of=./out.bin bs=16 count=1;
    cat ./out.bin >>$OUTPUT_IMG
    rm -rf out.bin
    #==============update backup table done==========================		
}

function func_prompt(){
    #================prompt question==========================
printf "\033[0;31mIs u-boot-2011.06 ? (Y/n)\033[0m"
read temp
if [ "$temp" == "N" ] || [ "$temp" == "n" ]; then
	NEW_MBOOT=0
fi
}

#=========== main() Start Upgrade ===============
if [ $# != 2 ];then
	printf "[SYNOPSIS]./build_BackUpTableUpgrade_image.sh [Input file] [SPI Offset]\n"
	printf "Input file: Your backup table image\n"
	printf "SPI Offset: backup table image location on your SPI\n"
	exit
fi

func_prompt;
if [ "$NEW_MBOOT" == "1" ] ; then
    func_update_arm_backup_table;
else
    func_update_mips_backup_table;
fi
PWD=`pwd`
echo "Build "$PWD/$OUTPUT_IMG" Successful !!"
exit 0
#================= End Upgrade ==================
