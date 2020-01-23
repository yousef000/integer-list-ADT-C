//-----------------------------------------------------------------------------------------
// Lex.c
// Yousef Dost
// ydost@ucsc.edu
// PA2
// A test client for the List ADT. It will take two command line arguments giving the names of an input file and an output file. The input can be any text file. The output file will contain the same lines as the input arranged in lexicographic (i.e. alphabetical) order. //-----------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include <string.h>
#define MAX_LEN 160

int main(int argc, char* argv[]){
   
    int SIZE = 0;
    FILE *in, *out;
    char line[MAX_LEN];
    
    // check command line for correct number of arguments
    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    
    // open files for reading and writing
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if( in==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if( out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    /* read each line of input file*/
    while( fgets(line, MAX_LEN, in) != NULL)  {
        SIZE++;
    }
    char A[SIZE][100];
    fclose(in);
    
    in = fopen(argv[1], "r");
    int i = 0;
    while(fgets(line, MAX_LEN,in) != NULL && i < SIZE){
        strcpy(A[i], line);
        i++;
    }
    
    fclose(in);
    
    List L = newList();
    for (int i = 0; i < SIZE; i++) {
        
        if(isEmpty(L) == 1){
            append(L, i);
            moveFront(L);
        }
        else{
            printf("%d ", i);
            printf("%d\n", strncmp(A[i], A[get(L)], 10));
            if(strncmp(A[i], A[get(L)], 10) < 0){
                insertBefore(L,i);
                moveFront(L);
            }
            else{
                for (moveFront(L); index(L) >= 0; moveNext(L)) {
                    if(strncmp(A[i], A[get(L)], 10) < 0){
                        insertBefore(L,i);
                        break;
                    }
                }
                //if cursor out of right bound means i > everything
                if(index(L) == -1)
                    append(L,i);
                moveFront(L);
                
            }
        }
    }
    for(moveFront(L); index(L) >= 0; moveNext(L)){
        fprintf(out, "%s\n", A[get(L)]);
    }
    
    freeList(&L);
    
    
    
}
