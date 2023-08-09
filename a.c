#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i=0,j=0,k=0,l=0,x=0; //li uso per testare
typedef struct {
        int distanza;
        int num_auto;
        int autonomia[100];
}stazioni;
void aggiungi_stazione(stazioni stazione[],int distanza, int num_auto, int autonomia[])
{
    if(stazione[distanza].distanza==0)
    {
    stazione[distanza].distanza=distanza;
    stazione[distanza].num_auto=num_auto;
    for(int d=0;d<num_auto;d++)
    {
        stazione[distanza].autonomia[d]=autonomia[d];
        //printf("%d %d \n", stazione[distanza].distanza,stazione[distanza].autonomia[d]);
    }
    printf("aggiunta \n");
    }
    else
    {
        printf("non aggiunta\n");
    }
    ///printf("%d %d \n", stazione[distanza].distanza,stazione[distanza].autonomia[d]);
    
}
void demolisci_stazione(stazioni stazione[], int distanza, int num_auto)
{
    if(stazione[distanza].distanza!=0)
    {
        stazione[distanza].distanza=-1;
        stazione[distanza].num_auto=0;
        printf("demolita\n");
    }
    else
    {
        printf("non demolita\n");
    }
    
}
void aggiungi_auto(stazioni stazione[],int distanza, int num_auto, int autonomia[])
{
    stazione[distanza].num_auto+=1;
    stazione[distanza].autonomia[num_auto+1]=autonomia[num_auto+1];
    printf("aggiunto\n");
}
void rottama_auto(stazioni stazione[], int distanza, int num_auto, int autonomia[])
{
    for(int d=0;d<num_auto;d++)
    {
        if(stazione[distanza].autonomia[d]==autonomia[d])
        {
            stazione[distanza].autonomia[d]=-1;
            printf("%d %d \n", stazione[distanza].distanza,stazione[distanza].autonomia[d]);
            break;
        }
        else{
            printf("non rottamato");
        }
        printf("distanza %d  autonomia %d \n", stazione[distanza].distanza,stazione[distanza].autonomia[d]);
    }
    stazione[distanza].num_auto-=1;
    printf("num auto %d \n", stazione[distanza].num_auto);
}
void percorso(stazioni stazione[], int distanza, int num_auto, int autonomia[], int partenza, int arrivo)
{
    int max, num_stazione=1;
    while(num_stazione!=0)
    {
        if(stazione[distanza].distanza<arrivo)
        {
            max=stazione[distanza].distanza;
        }
    }
    if(max==99)
    {
        printf("ciao");
    }
    
}
void analisi_input(char *input, stazioni stazione[])
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
                    
                }
                //printf("Distanza %d \n", distanza);
                //printf("Numero auto %d \n", num_auto);
               aggiungi_stazione(stazione,distanza, num_auto, autonomia);
               
            }
            if(strcmp(input_tagliato,"demolisci-stazione")==0)
            {
                j++;
                //printf("Demolisci: %d \n",j);
                sscanf(input, "%*s %d", &distanza);
                demolisci_stazione(stazione,distanza, num_auto);

            }
            if(strcmp(input_tagliato,"aggiungi-auto")==0)
            {
                k++;
                //printf("aggiungi auto: %d \n",k);
                sscanf(input,"%*s %d %d", &distanza, &autonomia[k]);
                aggiungi_auto(stazione,distanza, num_auto, autonomia);
            }
            if(strcmp(input_tagliato,"rottama-auto")==0)
            {
                l++;
                //printf("rottama: %d \n",l);
                sscanf(input,"%*s %d %d", &distanza, &autonomia[l]);
                rottama_auto(stazione,distanza, num_auto, autonomia);
                }
            if(strcmp(input_tagliato,"pianifica-percorso")==0)
            {
                x++;
                //printf("pianifica: %d \n",x);
                sscanf(input, "%*s %d %d", &partenza, &arrivo);
                //percorso(stazione,distanza,num_auto,autonomia,partenza,arrivo);
                
                for(int d=0;d<sizeof(stazione[distanza]);d++)
                    {
                        if(stazione[d].distanza!=0)
                        {
                            printf("%d ", stazione[d].distanza);
                        }
                            
                    }   
                    
                    

            }
                //printf("%s", input);
                //printf("aggiungi stazione %d \n",i);
    
            //printf("%d ", stazione[distanza].distanza);
}

int main(){    
    char input[1000];
    stazioni stazione[1000];
    //int distanza=91;
    while(fgets(input, sizeof(input), stdin)!=NULL)
    {
        analisi_input(input, stazione);
    }
    //printf("%d ", stazione[distanza].distanza);
    /*printf("Demolisci: %d \n",j);
    printf("aggiungi auto: %d \n",k);
    printf("rottama: %d \n",l);
    printf("pianifica: %d \n",x);*/

     return 0;
}  