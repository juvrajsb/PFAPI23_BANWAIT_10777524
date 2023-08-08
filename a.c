#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){    
    char input[1000];
    char input_tagliato[20];
    int i=0;
    while(fgets(input, sizeof(input), stdin))
    {
        //printf("%s", input);
        sscanf(input,"%s",input_tagliato); //leggo l'input fino allo spazio (whitespace)
            if(strcmp(input_tagliato,"aggiungi-stazione")==0)
            {
                i++;
                printf("%d \t",i);
            }
                printf("%s", input);

        }
        
    
    
     return 0;
}  