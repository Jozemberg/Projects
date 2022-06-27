#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char* reverse(const char* text){
    if(text == NULL)return NULL;
    size_t comparingVarForStrlen;
    size_t j = strlen(text)-1;

    char *rev_pointer = calloc (strlen (text)+1, sizeof(*text));

    for (comparingVarForStrlen = 0; comparingVarForStrlen < strlen(text); comparingVarForStrlen++, j--) {
        rev_pointer[comparingVarForStrlen] = (char)toupper(text[j]);
    }

    return rev_pointer;
}
char* vigenere_encrypt(const char* key, const char* text){
    if(text == NULL)return NULL;
    if(key == NULL)return NULL;
    size_t nulovaVelkostStringu = 0;
    size_t isAlphaControl;
    if(strlen(key) == nulovaVelkostStringu && strlen(text) == nulovaVelkostStringu)return NULL;
    if((key[0] == ' ' || text[0] == ' ') && (key[1] == ' ' || text[1] == ' '))return NULL;

    for (isAlphaControl = 0; isAlphaControl < strlen(key); ++isAlphaControl) {
        if(isalpha(key[isAlphaControl]) == 0) return NULL;
    }

    char *vig_pointer = calloc ((2*strlen (text)), sizeof(*text));
    char *pure_key = calloc (strlen(key)+1, sizeof (char));
    int *process = calloc ((2*strlen (text)), sizeof(int));

    for (int i = 0; key[i] != '\0' ; ++i) {
        pure_key[i] = (char)toupper(key[i]);
    }

    for (int i = 0; text[i] != '\0'; ++i) {
        process[i] = toupper(text[i]);
    }
    for (int i = 0, j = 0; process[i] != '\0' ; ++i) {
        if(j == (int)(strlen(pure_key)))j = 0;
        if(process[i] != 32 && process[i] != 33 && process[i] != 46 && process[i] != 44 && process[i] != 63 && process[i] != 64){
            if((process[i] - 64) + (pure_key[j] - 64) > 27) {
                process[i] = (((process[i] - 64) + (pure_key[j] - 64)) % 26);
            }else{
                process[i] = (((process[i] - 64) + (pure_key[j] - 64)));
            }
            process[i] += 63;
            j++;
        }
    }
    for (int i = 0; i < strlen(text); ++i) {
        vig_pointer[i] = (char)process[i];
    }
    free(process);
    free(pure_key);
    return vig_pointer;
}
char* vigenere_decrypt(const char* key, const char* text){
    if(text == NULL)return NULL;
    if(key == NULL)return NULL;
    size_t nulovaVelkostStringu = 0;
    size_t isAlphaControl;
    if(strlen(key) == nulovaVelkostStringu && strlen(text) == nulovaVelkostStringu)return NULL;
    if((key[0] == ' ' || text[0] == ' ') && (key[1] == ' ' || text[1] == ' '))return NULL;

    for (isAlphaControl = 0; isAlphaControl < strlen(key); ++isAlphaControl) {
        if(isalpha(key[isAlphaControl]) == 0)return NULL;
    }

    char *decvig_pointer = calloc ((2*strlen (text)), sizeof(*text));
    char *pure_key = calloc (strlen(key)+1, sizeof (char));
    int *process = calloc ((2*strlen (text)), sizeof(int));

    for (int i = 0; key[i] != '\0' ; ++i) {
        pure_key[i] = (char)toupper(key[i]);
    }

    for (int i = 0; text[i] != '\0'; ++i) {
        process[i] = toupper(text[i]);
    }
    for (int i = 0, j = 0; process[i] != '\0' ; ++i) {
        if(j == (int)(strlen(pure_key)))j = 0;
        if(process[i] != 32 && process[i] != 33 && process[i] != 46 && process[i] != 44 && process[i] != 63 && process[i] != 64){
            process[i] = (((process[i] - 64) - (pure_key[j] - 64)) % 26);
            if(process[i] < 0)process[i] = 26 - abs(process[i]);
            process[i] += 65;
            j++;
        }
    }
    for (int i = 0; i < strlen(text); ++i) {
        decvig_pointer[i] = (char)process[i];
    }

    free(process);
    free(pure_key);

    return decvig_pointer;

}
unsigned char* bit_encrypt(const char* text){
    if(text == NULL)return NULL;
    unsigned char *enc_bitchaos = calloc ((2*strlen (text)), sizeof(*text));
    int chaosed_letter = 0;
    const int bit_calc[8] = {128,64,32,16,8,4,2,1,};
    int bit_letter_array[8];
    int letter, cup, loop = 0;
    
    while(text[loop] != '\0'){
        letter = (int)text[loop];
        for (int i = 0; i < 8; ++i) {
            if(letter < bit_calc[i]){
                bit_letter_array[i] = 0;
            }else{
                bit_letter_array[i] = 1;
                letter -= bit_calc[i];
            }
        }

        cup = bit_letter_array[0];
        bit_letter_array[0] = bit_letter_array[1];
        bit_letter_array[1] = cup;

        cup = bit_letter_array[2];
        bit_letter_array[2] = bit_letter_array[3];
        bit_letter_array[3] = cup;

        for (int i = 0, j = 4; i < 4; ++i, ++j) {
            if(bit_letter_array[i] == 1 && bit_letter_array[j] == 1)bit_letter_array[j] = 0;
            else if(bit_letter_array[i] == 0 && bit_letter_array[j] == 0)bit_letter_array[j] = 0;
            else if(bit_letter_array[i] == 1 && bit_letter_array[j] == 0)bit_letter_array[j] = 1;
            else if(bit_letter_array[i] == 0 && bit_letter_array[j] == 1)bit_letter_array[j] = 1;
        }

        for (int i = 0; i < 8; ++i) {
            if(bit_letter_array[i] == 1)chaosed_letter += bit_calc[i];
        }

        enc_bitchaos[loop] = (unsigned char)chaosed_letter;
        chaosed_letter = 0;
        loop++;
    }
    return enc_bitchaos;
}
char* bit_decrypt(const unsigned char* text){
    if(text == NULL)return NULL;
    int length = 0;
    while (text[length] != '\0'){
        length++;
    }
    //if(text[0] == ' ')return NULL;

    char *dec_bitchaos = calloc ((2*length), sizeof(*text));
    const int bit_calc[8] = {128,64,32,16,8,4,2,1};
    int bit_letter_array[8];
    int cup, hex, loop = 0, chaosed_letter = 0;
    while(text[loop] != '\0'){
        hex = text[loop];
        for (int i = 0; i < 8; ++i) {
            if(hex < bit_calc[i]){
                bit_letter_array[i] = 0;
            }else{
                bit_letter_array[i] = 1;
                hex -= bit_calc[i];
            }
        }

        for (int i = 0, j = 4; i < 4; ++i, ++j) {
            if(bit_letter_array[i] == 1 && bit_letter_array[j] == 1)bit_letter_array[j] = 0;
            else if(bit_letter_array[i] == 0 && bit_letter_array[j] == 0)bit_letter_array[j] = 0;
            else if(bit_letter_array[i] == 1 && bit_letter_array[j] == 0)bit_letter_array[j] = 1;
            else if(bit_letter_array[i] == 0 && bit_letter_array[j] == 1)bit_letter_array[j] = 1;
        }

        cup = bit_letter_array[0];
        bit_letter_array[0] = bit_letter_array[1];
        bit_letter_array[1] = cup;

        cup = bit_letter_array[2];
        bit_letter_array[2] = bit_letter_array[3];
        bit_letter_array[3] = cup;

        for (int i = 0; i < 8; ++i) {
            if(bit_letter_array[i] == 1)chaosed_letter += bit_calc[i];
        }

        dec_bitchaos[loop] = (char)chaosed_letter;
        chaosed_letter = 0;
        loop++;
    }

    return dec_bitchaos;
}
unsigned char* bmp_encrypt(const char* key, const char* text){
    if(text == NULL)return NULL;
    if(key == NULL)return NULL;
    size_t nulovaVelkostStringu = 0;
    size_t isAlphaControl;
    if(strlen(key) == nulovaVelkostStringu && strlen(text) == nulovaVelkostStringu)return NULL;
    if((key[0] == ' ' || text[0] == ' ') && (key[1] == ' ' || text[1] == ' '))return NULL;

    for (isAlphaControl = 0; isAlphaControl < strlen(key); ++isAlphaControl) {
        if(isalpha(key[isAlphaControl]) == 0) return NULL;
    }

    char *purified_key = calloc ((2*strlen (key)), sizeof (char));
    unsigned char *bmp_pointer;
    char *bmp_signed_pointer;

    for (int i = 0; key[i] != '\0' ; ++i) {
        purified_key[i] = (char)toupper(key[i]);
    }

    bmp_signed_pointer = reverse(text);
    bmp_signed_pointer = vigenere_encrypt(purified_key,bmp_signed_pointer);
    bmp_pointer = bit_encrypt(bmp_signed_pointer);

    free(bmp_signed_pointer);
    free(purified_key);
    return bmp_pointer;
}
char* bmp_decrypt(const char* key, const unsigned char* text){
    if(text == NULL)return NULL;
    if(key == NULL)return NULL;
    if((key[0] == ' ' || text[0] == ' ') && (key[1] == ' ' || text[1] == ' '))return NULL;
    size_t nulovaVelkostStringu = 0;
    size_t isAlphaControl;
    for (isAlphaControl = 0; isAlphaControl < strlen(key); ++isAlphaControl) {
        if(isalpha(key[isAlphaControl]) == 0) return NULL;
    }

    int length = 0;
    while (text[length] != '\0'){
        length++;
    }
    if(strlen(key) == nulovaVelkostStringu && length == 0)return NULL;

    char *pure_key = calloc (strlen(key)+1, sizeof (char));
    char *bmp_signed_pointer;

    for (int i = 0; key[i] != '\0' ; ++i) {
        pure_key[i] = (char)toupper(key[i]);
    }

    bmp_signed_pointer = bit_decrypt(text);
    bmp_signed_pointer = vigenere_decrypt(pure_key,bmp_signed_pointer);
    bmp_signed_pointer = reverse(bmp_signed_pointer);

    free(pure_key);
    return bmp_signed_pointer;
}
/*int main(){
    char *fixing;
    char *fix;
    fixing = bmp_encrypt("pulsations","Obsadol na tom istom hostinci kde predtym a spytal sa co tam maju za novinu");
    fix = bmp_decrypt("pulsations",fixing);
    printf("%s ",fixing);
    printf("%s",fix);
    return 0;
}*/