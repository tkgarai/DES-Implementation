#include<stdio.h>

void swap(unsigned char *, unsigned char *);
void i_perm(unsigned char *, unsigned char *, int *, int);
void feistel_structure(unsigned char *, int , unsigned char *);
void expand(unsigned char *, unsigned char *); 
void sbox(unsigned char *, unsigned char *);
void key_scheduling(unsigned char *, unsigned char *, int );

int IP[] = {
                    58, 50, 42, 34, 26, 18, 10, 2,
                    60, 52, 44, 36, 28, 20, 12, 4,
                    62, 54, 46, 38, 30, 22, 14, 6,
                    64, 56, 48, 40, 32, 24, 16, 8,
                    57, 49, 41, 33, 25, 17,  9, 1,
                    59, 51, 43, 35, 27, 19, 11, 3,
                    61, 53, 45, 37, 29, 21, 13, 5,
                    63, 55, 47, 39, 31, 23, 15, 7
                },
    IP_inv[] = {
                    40, 8, 48, 16, 56, 24, 64, 32,
                    39, 7, 47, 15, 55, 23, 63, 31,
                    38, 6, 46, 14, 54, 22, 62, 30,
                    37, 5, 45, 13, 53, 21, 61, 29,
                    36, 4, 44, 12, 52, 20, 60, 28,
                    35, 3, 43, 11, 51, 19, 59, 27,
                    34, 2, 42, 10, 50, 18, 58, 26,
                    33, 1, 41,  9, 49, 17, 57, 25
                },
	E[] = {
				32,  1,  2,  3,  4,  5,
    			 4,  5,  6,  7,  8,  9,
    			 8,  9, 10, 11, 12, 13,
    			12, 13, 14, 15, 16, 17,
 				16, 17, 18, 19, 20, 21,
  				20, 21, 22, 23, 24, 25,
    			24, 25, 26, 27, 28, 29,
    			28, 29, 30, 31, 32,  1	
			},
	s[8][4][16] =  {	{ 
						  14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                          0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                          4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                          15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 
						},
                        { 
						  15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                          3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                          0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                          13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 
						},
                        { 
						  10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                          13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                          13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                          1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 
						},
                        { 
						  7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                          13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                          10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                          3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 
						},
                        { 
						  2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                          14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                          4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                          11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 
						},
                        { 
						  12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                          10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                          9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                          4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 
						},
                        { 
						  4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                          13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                          1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                          6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 
						},
                        { 
						  13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                          1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                          7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                          2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 
						} 
					},
	f_perm[32] = {     16, 7, 20, 21,
                    29, 12, 28, 17,
                    1, 15, 23, 26,
                    5, 18, 31, 10,
                    2, 8, 24, 14,
                    32, 27, 3, 9,
                    19, 13, 30, 6,
                    22, 11, 4, 25 },
    PC1[56] = { 57, 49, 41, 33, 25, 17, 9,
                     1, 58, 50, 42, 34, 26, 18,
                     10, 2, 59, 51, 43, 35, 27,
                     19, 11, 3, 60, 52, 44, 36,
                     63, 55, 47, 39, 31, 23, 15,
                     7, 62, 54, 46, 38, 30, 22,
                     14, 6, 61, 53, 45, 37, 29,
                     21, 13, 5, 28, 20, 12, 4 },
    PC2[48] = { 14, 17, 11, 24, 1, 5,
                         3, 28, 15, 6, 21, 10,
                         23, 19, 12, 4, 26, 8,
                         16, 7, 27, 20, 13, 2,
                         41, 52, 31, 37, 47, 55,
                         30, 40, 51, 45, 33, 48,
                         44, 49, 39, 56, 34, 53,
                         46, 42, 50, 36, 29, 32 };

void main()
{
    unsigned char cipher_text[8] = {75, 170, 198, 164, 29, 45, 252, 178}, permuted_text[8] = {0}, plain_text[8] = {0}, super_key[8] = "Samapuki", key[7] = {0};
    int i, j, k;
    printf("plain text: ");
    for (i = 0; i < 8; i++)
        printf("%c", cipher_text[i]);
    i_perm(cipher_text, permuted_text, IP, 64);
    i_perm(super_key, key, PC1, 56);
    for (k = 0; k < 16; k++)
        feistel_structure(permuted_text, k, key);
    for (i = 0; i < 4; i++)
        swap(&permuted_text[i], &permuted_text[i + 4]);
    i_perm(permuted_text, plain_text, IP_inv, 64);
    printf("\ncipher text: ");
    for (i = 0; i < 8; i++)
        printf("%c", plain_text[i]);
    printf("\n");
}

void swap(unsigned char *p, unsigned char *q)
{
    unsigned char x = *p;
    *p = *q;
    *q = x;
}

void i_perm(unsigned char *a, unsigned char *b, int *perm, int perm_size)
{
    for (int i = 0; i < perm_size; i++)
        b[i >> 3] |= ((a[(perm[i] - 1) >> 3] >> ((perm[i] - 1) & 7)) & 1) << (i & 7);
}

void feistel_structure(unsigned char *permuted_text, int k, unsigned char * key)
{
    unsigned char left_permuted_text[4] = {permuted_text[0], permuted_text[1], permuted_text[2], permuted_text[3]}, right_permuted_text[4] = {permuted_text[4], permuted_text[5], permuted_text[6], permuted_text[7]}, expanded_right_permuted_text[8] = {0}, sbox_output[4] = {0}, fies_perm_output[4] = {0}, subkey[8] = {0};
    int i;
    expand(right_permuted_text, expanded_right_permuted_text);
    key_scheduling(key, subkey, k);
    for(i = 0; i < 8; i++)
        expanded_right_permuted_text[i] |= subkey[i];
    sbox(expanded_right_permuted_text, sbox_output);
    i_perm(sbox_output, fies_perm_output, f_perm, 32);
    for (i = 0; i < 4; i++)
    {
        permuted_text[i] ^= fies_perm_output[i];
        swap(&permuted_text[i], &permuted_text[i + 4]);
    }
}

void expand(unsigned char *a, unsigned char *c)
{
    unsigned char b[6] = {0};
    int i, j;
    i_perm(a, b, E, 48);
    for (i = 0, j = 0; i <= 4, j <= 3; i += 4, j += 3)
    {
        c[i] = b[j] & 0x3f;
        c[i + 1] = b[j] >> 6;
        c[i + 1] |= (b[j + 1] & 0xf) << 2;
        c[i + 2] = b[j + 1] >> 4;
        c[i + 2] |= b[j + 2] & 0x3;
        c[i + 3] = b[j + 2] >> 2;
    }
}

void sbox(unsigned char *c, unsigned char *e)
{
    unsigned char d[8] = { 0 };
    int i;
    for (i = 0; i < 8; i++)
        d[i] = s[i][((c[i] >> 5) << 1) + (c[i] & 1)][(c[i] >> 1) & 0xf];
    for (i = 0; i < 4; i++)
        e[i] = d[i << 1] | (d[(i << 1) + 1] << 4);
}

void key_scheduling(unsigned char *key, unsigned char *subkey, int k)
{
    unsigned char lkey[7] = {0}, rkey[7] = {0}, subkey_8bit[6] = {0}, new_rkey[7] = {0}, new_lkey[7] = {0};
    int i, j;
    lkey[0] = key[0] & 0xf;
    lkey[1] = key[0] >> 4;
    lkey[2] = key[1] & 0xf;
    lkey[3] = key[1] >> 4;
    lkey[4] = key[2] & 0xf;
    lkey[5] = key[2] >> 4;
    lkey[6] = key[3] & 0xf;
    rkey[0] = key[3] >> 4;
    rkey[1] = key[4] & 0xf;
    rkey[2] = key[4] >> 4;
    rkey[3] = key[5] & 0xf;
    rkey[4] = key[5] >> 4;
    rkey[5] = key[6] & 0xf;
    rkey[6] = key[6] >> 4;
    if (k == 0)
    {
        for (i = 0; i < 7; i++)
        {
            new_lkey[i] = lkey[i];
            new_rkey[i] = rkey[i];
        }
    }
    else if (k == 1 || k == 8 | k == 15 | k == 16)
    {
        for (i = 0; i < 7; i++)
        {
            new_lkey[i] = ((lkey[i] << 1) | ((lkey[(i + 6) % 7] >> 3) & 0x1)) & 0xf;
            new_rkey[i] = ((rkey[i] << 1) | ((rkey[(i + 6) % 7] >> 3) & 0x1)) & 0xf;
        }
    }
    else
    {
        for (i = 0; i < 7; i++)
        {
            new_lkey[i] = ((lkey[i] << 2) | ((lkey[(i + 6) % 7] >> 2) & 0x3)) & 0xf;
            new_rkey[i] = ((rkey[i] << 2) | ((rkey[(i + 6) % 7] >> 2) & 0x3)) & 0xf;
        }
    }
    key[0] = new_lkey[0] | (new_lkey[1] << 4);
    key[1] = new_lkey[2] | (new_lkey[3] << 4);
    key[2] = new_lkey[4] | (new_lkey[5] << 4);
    key[3] = new_lkey[6] | (new_rkey[0] << 4);
    key[4] = new_rkey[1] | (new_rkey[2] << 4);
    key[5] = new_rkey[3] | (new_rkey[4] << 4);
    key[6] = new_rkey[5] | (new_rkey[6] << 4);
    i_perm(key, subkey_8bit, PC2, 48);
    for (i = 0, j = 0; i <= 4, j <= 3; i += 4, j += 3)
    {
        subkey[i] = subkey_8bit[j] & 0x3f;
        subkey[i + 1] = subkey_8bit[j] >> 6;
        subkey[i + 1] |= (subkey_8bit[j + 1] & 0xf) << 2;
        subkey[i + 2] = subkey_8bit[j + 1] >> 4;
        subkey[i + 2] |= subkey_8bit[j + 2] & 0x3;
        subkey[i + 3] = subkey_8bit[j + 2] >> 2;
    }
}