#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int str_dlinauz(char* str){
    int i = 0;
    while(str[i++]);

    return i - 1;
}

void my_strkopirovaniyauz(char* dest, char* source){
    for(int i = 0; i < str_dlinauz(source); i++){
        dest[i] = source[i];
    }
}

int str_char_function(char* str, char numb){
    for(int i = 0; i < str_dlinauz(str); i++){
        if(str[i] == numb) return 1;
    }
    return 0;
}


char* rand_generovaniya(){
    char* rand_code = calloc(5, sizeof(char));
    int i = 0;
    char temp;
    srand(time(0));


    while(i < 4){
        temp = rand() %9 +48;

        if(str_char_function(rand_code, temp) == 0){
            rand_code[i] = temp;
            i++;
        }
    }
    return rand_code;
}

char* my_skanirovaniye(){
    char n = '>';
    write(1, &n, 1);
    fflush(stdout);
    char* user_input = calloc(100, sizeof(char));
    int i = 0;
    char temp;

    while(read(0, &temp, 1)){
        if(temp == '\n'){
            return user_input;
        }
        user_input[i] = temp;
        i++;
    }
    return NULL;
}

int proverka_bukv(char* user_input){
    for(int i = 0; i < str_dlinauz(user_input); i++){
        if(!(user_input[i] >= 48 && user_input[i] <= 56)) return 0;
    }

    return 1;
}

int proverka_duplikatov(char* user_input){
    for(int i = 0; i < str_dlinauz(user_input); i++){
        for(int j = i+1; j <= str_dlinauz(user_input); j++){
            if(user_input[i] == user_input[j]) return 0;
        }
    }
    return 1;
}

int pravilniye_sifri(char* sc_code, char* user_code){
    int counter = 0;
    for(int i = 0; i < str_dlinauz(sc_code); i++){
        if(sc_code[i] == user_code[i]) counter++;
    }
    return counter;

}

int nepravilnix_sifr(char* sc_code, char* user_code){
    int counter = 0;
    for(int i = 0; i <str_dlinauz(sc_code); i++){
        for(int j = 0; j < str_dlinauz(user_code); j++){
            if(sc_code[i] == user_code[j] && i != j) counter++;
        }
    }
    return counter;
}

int check_function(char* user_input){
    if(str_dlinauz(user_input) != 4) return 0;
    if(proverka_bukv(user_input) == 0) return 0;
    if(proverka_duplikatov(user_input) == 0) return 0;

    return 1;
}

void funktiya_igri(int attempts, char* sc_code){
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    char* user_input;
    for(int i = 0; i < attempts; i++){
        printf("---\nRound %d\n", i);
        user_input = my_skanirovaniye();
        if(user_input == NULL) return;
        while (check_function(user_input) == 0){
            free(user_input);
            printf("Wrong input!\n");
            user_input = my_skanirovaniye();}
        int well = pravilniye_sifri(sc_code, user_input);
        if(well == 4){
            free(user_input);
            printf("Congratz! You did it!\n");
            return;}
        else {
            printf("Well placed pieces: %d\n", well);
            printf("Misplaced pieces: %d\n", nepravilnix_sifr(sc_code, user_input));}}}

int main(int argc, char** argv){
    int i = 0;
    char* secred_code = NULL;
    int attempts = 10;
    while(i < argc){
        if(strcmp(argv[i], "-c") == 0){
            i++;
            secred_code = malloc(sizeof(char) * 5);
            my_strkopirovaniyauz(secred_code, argv[i]);}
        else if (strcmp(argv[i], "-t") == 0){
            i++;
            attempts = atoi(argv[i]);}
        i++;}
    if(secred_code == NULL){
        secred_code = rand_generovaniya();}
    funktiya_igri(attempts, secred_code);
    free(secred_code);
    return 0;}