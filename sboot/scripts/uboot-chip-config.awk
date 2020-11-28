# Copyright (c) 2008-2009 MStar Semiconductor, Inc.
# All rights reserved.

$2 == "ENABLE_MSTAR_TITANIA" { if($3==1) system("cd ../u-boot-1.1.6/;make titania_config;make -s")}
$2 == "ENABLE_MSTAR_TITANIA2" { if($3==1) system("cd ../u-boot-1.1.6/;make titania2_config;make -s")}
$2 == "ENABLE_MSTAR_TITANIA3" { if($3==1) system("cd ../u-boot-1.1.6/;make titania3_config;make -s")}
$2 == "ENABLE_MSTAR_EUCLID" { if($3==1) system("cd ../u-boot-1.1.6/;make euclid_config;make -s")}
$2 == "ENABLE_MSTAR_TITANIA4" { if($3==1) system("cd ../u-boot-1.1.6/;make titania4_config;make -s")}
$2 == "ENABLE_MSTAR_TITANIA7" { if($3==1) system("cd ../u-boot-1.1.6/;make titania7_config;make -s")}
$2 == "ENABLE_MSTAR_TITANIA8" { if($3==1) system("cd ../u-boot-1.1.6/;make titania8_config;make -s")}
$2 == "ENABLE_MSTAR_TITANIA12" { if($3==1) system("cd ../u-boot-1.1.6/;make titania12_config;make -s")}
$2 == "ENABLE_MSTAR_AMBER2" { if($3==1) system("cd ../u-boot-1.1.6/;make amber2_config;make -s")}
$2 == "ENABLE_MSTAR_AMBER3" { if($3==1) system("cd ../u-boot-2011.06/;make amber3_config;sh build.sh")}
$2 == "ENABLE_MSTAR_AGATE" { if($3==1) system("cd ../u-boot-2011.06/;make agate_config;sh build.sh")}
$2 == "ENABLE_MSTAR_AMBER5" { if($3==1) system("cd ../u-boot-2011.06/;make amber5_config;make -s")}
$2 == "ENABLE_MSTAR_TITANIA9" { if($3==1) system("cd ../u-boot-1.1.6/;make titania9_config;make -s")}
$2 == "ENABLE_MSTAR_TITANIA13" { if($3==1) system("cd ../u-boot-1.1.6/;make titania13_config;make -s")}
$2 == "ENABLE_MSTAR_AMBER1" { if($3==1) system("cd ../u-boot-1.1.6/;make amber1_config;make -s")}
$2 == "ENABLE_MSTAR_AMBER6" { if($3==1) system("cd ../u-boot-1.1.6/;make amber6_config;make -s")}
$2 == "ENABLE_MSTAR_AMBER7" { if($3==1) system("cd ../u-boot-1.1.6/;make amber7_config;make -s")}
$2 == "ENABLE_MSTAR_AMETHYST" { if($3==1) system("cd ../u-boot-2011.06/;make amethyst_config;make -s")}
$2 == "ENABLE_MSTAR_URANUS4" { if($3==1) system("cd ../u-boot-1.1.6/;make uranus4_config;make -s")}
#$2 == "ENABLE_MSTAR_JANUS" { if($3==1) system("cd ../u-boot-1.1.6/;make janus_config;make -s")}
$2 == "ENABLE_MSTAR_JANUS" { if($3==1) system("cd ../u-boot-1.1.6/;make janus_config;make -s")}
$2 == "ENABLE_MSTAR_JANUS2" { if($3==1) system("cd ../u-boot-1.1.6/;make janus2_config;make -s")}
$2 == "ENABLE_MSTAR_MARIA10" { if($3==1) system("cd ../u-boot-1.1.6/;make maria10_config;make -s")}
$2 == "ENABLE_MSTAR_KRONUS" { if($3==1) system("cd ../u-boot-2011.06/;make kronus_config;make -s")}
$2 == "ENABLE_MSTAR_KENYA" { if($3==1) system("cd ../u-boot-2011.06/;make kenya_config;make -s")}
$2 == "ENABLE_MSTAR_KAISERIN" { if($3==1) system("cd ../u-boot-2011.06/;make kaiserin_config;make -s")}
$2 == "ENABLE_MSTAR_KAISER" { if($3==1) system("cd ../u-boot-2011.06/;make kaiser_config;sh build.sh")}
$2 == "ENABLE_MSTAR_EAGLE" { if($3==1) system("cd ../u-boot-2011.06/;make eagle_config;sh build.sh")}
$2 == "ENABLE_MSTAR_EIFFEL" { if($3==1) system("cd ../u-boot-2011.06/;make eiffel_config;sh build.sh")}
$2 == "ENABLE_MSTAR_NIKE" { if($3==1) system("cd ../u-boot-2011.06/;make nike_config;sh build.sh")}
$2 == "ENABLE_MSTAR_MADISON" { if($3==1) system("cd ../u-boot-2011.06/;make madison_config;sh build.sh")}
$2 == "ENABLE_MSTAR_MONET" { if($3==1) system("cd ../u-boot-2011.06/;make monet_config;sh build.sh")}
$2 == "ENABLE_MSTAR_CLIPPERS" { if($3==1) system("cd ../u-boot-2011.06/;make clippers_config;sh build.sh")}
$2 == "ENABLE_MSTAR_MIAMI" { if($3==1) system("cd ../u-boot-2011.06/;make miami_config;sh build.sh")}
$2 == "ENABLE_MSTAR_NADAL" { if($3==1) system("cd ../u-boot-2011.06/;make nadal_config;sh build.sh")}
$2 == "ENABLE_MSTAR_EMERALD" { if($3==1) system("cd ../u-boot-2011.06/;make emerald_config;make -s")}
$2 == "ENABLE_MSTAR_NUGGET" { if($3==1) system("cd ../u-boot-2011.06/;make nugget_config;make -s")}
$2 == "ENABLE_MSTAR_NIKON" { if($3==1) system("cd ../u-boot-2011.06/;make nikon_config;make -s")}
$2 == "ENABLE_MSTAR_MILAN" { if($3==1) system("cd ../u-boot-2011.06/;make milan_config;make -s")}
$2 == "ENABLE_MSTAR_EDISON" { if($3==1) system("cd ../u-boot-2011.06/;make edison_config;make -s")}
$2 == "ENABLE_MSTAR_EINSTEIN" { if($3==1) system("cd ../u-boot-2011.06/;make einstein_config;make -s")}
$2 == "ENABLE_MSTAR_EINSTEIN3" { if($3==1) system("cd ../u-boot-2011.06/;make einstein3_config;make -s")}
$2 == "ENABLE_MSTAR_NAPOLI" { if($3==1) system("cd ../u-boot-2011.06/;make napoli_config;make -s")}
$2 == "ENABLE_MSTAR_MONACO" { if($3==1) system("cd ../u-boot-2011.06/;make monaco_config;sh build.sh")}
$2 == "ENABLE_MSTAR_MUJI" { if($3==1) system("cd ../u-boot-2011.06/;make muji_config;sh build.sh")}
$2 == "ENABLE_MSTAR_CELTICS" { if($3==1) system("cd ../u-boot-2011.06/;make celtics_config;sh build.sh")}
$2 == "ENABLE_MSTAR_KRITI" { if($3==1) system("cd ../u-boot-2011.06/;make kriti_config;make -s")}