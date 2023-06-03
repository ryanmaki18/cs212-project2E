#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void IssueBadInputError(){
    printf("You must input a file followed by atleast one search word.\nShould look like:\n./project2E filename word1 word2 word3 ....\n");
    exit(EXIT_FAILURE);
}

void IssueBadFileError(){
    printf("Unable to open the file provided\n");
    exit(EXIT_FAILURE);
}

void IssueMemoryError(){
    printf("Failed to allocate memory\n");
    exit(EXIT_FAILURE);
}

int SearchForWord(char *txt, int wordLen, char *searchWord){
    int match_count = 0;
    while(*txt != '\0'){
        //if current char is equal to first letter of searchWord and previous char is anything except a valid letter
        if ((*txt == searchWord[0]) && (!(((*(txt - 1) >= 'A') && (*(txt - 1) <= 'Z')) || ((*(txt - 1) >= 'a') && (*(txt - 1) <= 'z'))))){
            // if character after word is not a character then check if word == searchWord
            if (!((*(txt + wordLen) >= 'A') && (*(txt + wordLen) <= 'Z')) || ((*(txt + wordLen) >= 'a') && (*(txt + wordLen) <= 'z'))){
                if (strncmp(txt, searchWord, wordLen) == 0){
                    match_count++;
                }
            }
        }
        txt++;
    }
    return match_count;
}

int main(int argc, char *argv[]){
    //Input must be atleast 3
    if (argc < 3) {
        IssueBadInputError();
    }

    //Opening file
    FILE *input_file = fopen(argv[1], "r");
    //printf("This is the file: \n%s", input_file);
    if (input_file == NULL) {
        IssueBadFileError();
    }

    //Getting size of file 
    fseek(input_file, 0, SEEK_END);
    int file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);
    //printf("%d\n", file_size);   //Uncomment to print out file_size

    //Make buffer from file
    char *buffer = malloc(file_size);
    fread(buffer, 1, file_size, input_file);
    if (input_file == NULL) {
        IssueMemoryError();
    }
    //printf("%s\n", buffer);   //Uncomment to print out buffer

    //Each time through the loop, we look for a new word
    for (int i = 2; i < argc; i++){
        int WordLen = strlen(argv[i]);
        int match_count = SearchForWord(buffer, WordLen, argv[i]);
        printf("The word \"%s\" occurs %d times.\n", argv[i], match_count);
    }

    free(buffer);
    fclose(input_file);
    return EXIT_SUCCESS;
}
