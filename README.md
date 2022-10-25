The folder contains the DES decryption and encryption program named des_enc.c and des-dec.c which is hardcoded. You just need to run the c file.


Another two file named ofb_des_enc.c and ofb_des_dec.c are the implementation of OFB mode using DES as building block. You have to give a file name tk.txt as input to run the ofb_des_enc.c. After run it will create a file named encrypted, which will contain the ciphertext. Then run ofb_des_dec.c with input the file encrypted. It will create a file name decrypted, which will contain the plaintext.
