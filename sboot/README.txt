[[How to make]]
	1. make menuconfig
		$ cd sboot
		$ make menuconfig
	2. make
	3. use out/mboot.bin

[[Verbose mode]]
    1. KBUILD_VERBOSE=1 make

[[Add new project]]
	1. Add options to Config.in
	2. put source files into src/$chip inc/$chip
	3. write src/$chip/Kbuild
	

[[Change tool chain]]
	1. make menuconfig -> Build Options
