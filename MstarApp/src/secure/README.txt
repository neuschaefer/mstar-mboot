//------------------------------------------
//   cryptest
//   generate private_key, public_key, signature
//------------------------------------------
1. cryptest552.exe g 

	Key length in bits: 2048
	Save private key to file: t_private
	Save public key to file: t_public
	Random Seed: 17

	// get private key and public key



2. cryptest552.exe na_sign t_private t_public u-boot.bin t_signature

	//generate signature
	

ps: You can replace u-boot.bin to your test file



//--------------------------------------------------
//   parser public_key_E and public_key_N from t_public
//--------------------------------------------------

    Please reference to 'parse_public_key' to get public_key_E and public_key_N

  

  

//--------------------------------------------------
//   transfer public_key_E, public_key_N, signature to Array
//--------------------------------------------------

    tool: 
  	./hex2Array  t_signature >> signature.h
         
	.....


//---------------------------------------------------
//                 Secure Boot
//---------------------------------------------------

To test secure boot function

input: public_key_E, public_key_N, signature, unathorized file

output: valid or invalid

1. 'usb start' (or 'usb start 1')

2. 'tftp a0000000 u-boot.bin' //download unauthorized file to a0000000

3. 'secure' 

4. 'showmem 5000000'  and 'showmem 6000000' 
//You can check the SHA256 and RSA result in address 0x85000000 and 0x86000000