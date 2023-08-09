#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i=0,j=0,k=0,l=0,x=0; //li uso per testare


void aggiungi_stazione(int distanza, int num_auto, int autonomia[], int d)
{
    struct {
        int distanza;
        int num_auto;
        int autonomia[100];
    }stazione;
    stazione.distanza=distanza;
    stazione.num_auto=num_auto;
    stazione.autonomia[d]=autonomia[d];
    printf("%d %d %d \n", stazione.distanza,stazione.num_auto,stazione.autonomia[d]);
}
void analisi_input(char *input)
{
    char input_tagliato[20];
    int distanza=0, num_auto=0, autonomia[100];
    int partenza, arrivo;
    //printf("%s", input);
        sscanf(input,"%s", input_tagliato); //leggo l'input fino allo spazio (whitespace)
            if(strcmp(input_tagliato,"aggiungi-stazione")==0)
            {
                i++;
                //printf("aggiungi stazione %d \n",i);
                sscanf(input,"%*s %d %d", &distanza, &num_auto); 
                //%*s ignora la stringa, uso & perchè puntatore
                //printf("Autonomia: ");
                for(int d=0; d<num_auto;d++)
                {
                    sscanf(input,"%*s %*d %*d %d", &autonomia[d]);
                    //%*d ignora l'intero
                    input=strchr(input+1, ' '); 
                    //strchr() la uso per trovare il prossimo spazio in input, cosicche input poi punta allo spazio appena trovato
                    //printf("%d ",autonomia[d]);
                    aggiungi_stazione(distanza, num_auto, autonomia, d);
                }
                //printf("Distanza %d \n", distanza);
                //printf("Numero auto %d \n", num_auto);
               
            }
            if(strcmp(input_tagliato,"demolisci-stazione")==0)
            {
                j++;
                //printf("Demolisci: %d \n",j);
                sscanf(input, "%*s %d", &distanza);
                ///funzione che toglie la stazione
            }
            if(strcmp(input_tagliato,"aggiungi-auto")==0)
            {
                k++;
                //printf("aggiungi auto: %d \n",k);
                sscanf(input,"%*s %d %d", &distanza, &autonomia[k]);
                /// funzione controlla se la stazione esiste e la aggiunge
            }
            if(strcmp(input_tagliato,"rottama-auto")==0)
            {
                l++;
                //printf("rottama: %d \n",l);
                sscanf(input,"%*s %d %d", &distanza, &autonomia[l]);
                /// funzione controlla se la stazione esiste e la aggiunge e controlla se esiste almeno un'auto con autonomia 
                }
            if(strcmp(input_tagliato,"pianifica-percorso")==0)
            {
                x++;
                //printf("pianifica: %d \n",x);
                sscanf(input, "%*s %d %d", &partenza, &arrivo);
            }
                //printf("%s", input);
                //printf("aggiungi stazione %d \n",i);
    

}
int main(){    
    char input[1000];
    
    while(fgets(input, sizeof(input), stdin)!=NULL)
    {
        analisi_input(input);
    }
    /*printf("Demolisci: %d \n",j);
    printf("aggiungi auto: %d \n",k);
    printf("rottama: %d \n",l);
    printf("pianifica: %d \n",x);*/

     return 0;
}  