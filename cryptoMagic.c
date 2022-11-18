#include <stdio.h>
#include <string.h>

int StringToDec(char input){

    //Initializing the output integer
    int outputHex;

    //Directly translating the strings as a decimal:
    if (input == '0') {
        outputHex = 0;
    }

    else if (input == '1') {
        outputHex = 1;
    }

    else if (input == '2') {
        outputHex = 2;
    }

    else if (input == '3') {
        outputHex = 3;
    }

    else if (input == '4') {
        outputHex = 4;
    }

    else if (input == '5') {
        outputHex = 5;
    }

    else if (input == '6') {
        outputHex = 6;
    }

    else if (input == '7') {
        outputHex = 7;
    }

    else if (input == '8') {
        outputHex = 8;
    }

    else if (input == '9') {
        outputHex = 9;
    }

    else if (input == 'A') {
        outputHex = 10;
    }

    else if (input == 'B') {
        outputHex = 11;
    }

    else if (input == 'C') {
        outputHex = 12;
    }

    else if (input == 'D') {
        outputHex = 13;
    }

    else if (input == 'E') {
        outputHex = 14;
    }

    else if (input == 'F') {
        outputHex = 15;
    }

    else {
    }

    return outputHex;
}

int Encrypter(char *filename){

    //Initializing read file:    
    FILE *read_file;


    //Initializing variables for fgets and primary data organization:
    char buffer_data[120];
    char data[120] = {};
    char output[1024] = {};


    //Opening input file for reading:
    read_file = fopen(filename, "r");


    //Checking if file is opened correctly:
    if (read_file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }


    // Reading the file, storing into temporary buffer. Then transfering into data array:
    while (!feof(read_file)) {
        fgets(buffer_data, 120, read_file);
        strcat(data, buffer_data);
    }


    //Closing read file:
    fclose(read_file);


    //Initializing write file:
    FILE *write_file;


    //Opening or creating write file in txt format:
    write_file = fopen("outputFile.crp", "w");


    //Initializing variables for use in for loop and output:
    int i;
    int outChar;
    int length = strlen(data);


    //The for loop that iterates from 0 to the length of data file:
    for (i = 0; i < length; i++) {

        //Converting specific data character into ascii decimal
        int ascii = data[i];


        //If character is a tab then it will write 'TT' in the output file:
        if (ascii == 9) {
            fprintf(write_file, "%s", "TT");
        } 


        //If character is a carriage return or line feed, it will print a new line:
        else if (ascii == 13 || ascii == 10) {
            fprintf(write_file, "%s", "\n");
        }


        //Does calculations to create the encrypted character:
        else {
            outChar = ascii - 16;
      
            if (outChar < 32) {
                outChar = (outChar - 32) + 144;
        }
        
        //Writes the encrypted character to the output file:
        fprintf(write_file, "%X", outChar);
        }
    }
    

    //Closing write file after writing the output:
    fclose(write_file);
    return 0;
}

int Decrypter(char*filename){

    //Initializing read file:
    FILE *read_file;


    //Initializing variables for fgets and primary data organization:
    char buffer_data[255];
    char data[1024] = {};

    //Opening input file for reading:
    read_file = fopen(filename, "r");


    //Checking if file is opened correctly:
    if (read_file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }


    // Reading the file, storing into temporary buffer. Then transfering into data array:
    while (!feof(read_file)) {
        fgets(buffer_data, 255, read_file);
        strcat(data, buffer_data);
    }

    //Closing read file:
    fclose(read_file);


    //Initializing write file:
    FILE *write_file;


    //Opening or creating write file in txt format:
    write_file = fopen("outputFile.txt", "w");


    //Initializing variables for use in for loop and output:
    int i;
    int outChar;
    int length = strlen(data);


    //The for loop that iterates from 0 to the length of data file:
    for (i = 0; i < length; i += 2) {

        //Initializing tab character:
        char tab = 'T';


        //Looking for a new line in the input. Then printing a new line in the output file:
        if (data[i] == 10 || data[i + 1] == 10) {
            i--;
            fprintf(write_file, "%s", "\n");
        }


        //Looking for the tab character, and printing a tab in the output file:
        else if (data[i] == tab && data[i + 1] == tab) {
            fprintf(write_file, "%c", 9);
        }


        //Doing calculations for all other types of characters and printing to output file:
        else {
            int outChar;
            int hexindecimal1 = StringToDec(data[i]);
            int hexindecimal2 = StringToDec(data[i + 1]);

            outChar = ((hexindecimal1 * 16) + hexindecimal2) + 16;

            if (outChar > 127) {
            outChar = (outChar - 144) + 32;
            }

            fprintf(write_file, "%c", outChar);
        }
    }

    //Closing write file after writing the output:
    fclose(write_file);
    return 0;
}

int EorD(char* command, char*filename){

    //Comparing input command to known commands:
    int value1 = strcmp(command, "-E");
    int value2 = strcmp(command, "-D");


    //If input is '-E', then run the encrypter:
    if (value1 == 0){
        Encrypter(filename);
    }


    //If input is '-D', then run the decrypter:
    else if (value2 == 0){
        Decrypter(filename);
    }


    //Any other input will notify user as incorrect:
    else{
        printf("The command inputed is not valid! Enter '-E' or '-D'.");
        return 1;
    }
}

int main(int argc, char* argv[]){

    //If the length of command line input is two, always run the encrypter:
    if (argc == 2){
        char* filename = argv[1];
        Encrypter(filename);
    }


    //If the length of command line input is three, run the function that interprets command type:
    else if(argc == 3){
        char* command = argv[1];
        char* filename = argv[2];
        EorD(command, filename);
    }


    //If length of command line input is too high or too low, then it will notify user:
    else{
        printf("You have entered too many or too little arugments!\nEnter a command (-E, or -D), then a filename following.");
    }

    return 0;
}