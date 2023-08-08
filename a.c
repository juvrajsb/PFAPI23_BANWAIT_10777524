#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){    
    char input[1000];
    char input_tagliato[20];
    int i=0,j=0,k=0,l=0,x=0;
    int distanza=0, num_auto=0, autonomia=0;
    while(fgets(input, sizeof(input), stdin))
    {
        printf("%s", input);
        sscanf(input,"%s",input_tagliato); //leggo l'input fino allo spazio (whitespace)
            if(strcmp(input_tagliato,"aggiungi-stazione")==0)
            {
                i++;
                //printf("aggiungi stazione %d \n",i);
                sscanf(input,"%*s %d %d %d", &distanza, &num_auto, &autonomia); //%*s salta la stringa, uso & perchè puntatore
                printf("Distanza %d \n", distanza);
                printf("Numero auto %d \n", num_auto);
                printf("Autonomia %d \n",autonomia);
            }
            if(strcmp(input_tagliato,"demolisci-stazione")==0)
            {
                j++;
                //printf("Demolisci: %d \n",j);
            }
            if(strcmp(input_tagliato,"aggiungi-auto")==0)
            {
                k++;
                //printf("aggiungi auto: %d \n",k);
            }
            if(strcmp(input_tagliato,"rottama-auto")==0)
            {
                l++;
                //printf("rottama: %d \n",l);
            }
            if(strcmp(input_tagliato,"pianifica-percorso")==0)
            {
                x++;
                //printf("pianifica: %d \n",x);
            }
                //printf("%s", input);

        }
    printf("aggiungi stazione %d \n",i);
    printf("Demolisci: %d \n",j);
    printf("aggiungi auto: %d \n",k);
    printf("rottama: %d \n",l);
    printf("pianifica: %d \n",x);

     return 0;
}  