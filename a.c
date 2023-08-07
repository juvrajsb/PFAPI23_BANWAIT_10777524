#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){    
    char input[1000];
    int i=0;
    
    while(fgets(input, sizeof(input), stdin))
    {
        i=strcmp(input,"aggiungi-stazione");
        //{
            
            printf("%d",i);
       // }
        printf("%s", input);
    }
     return 0;
}
   