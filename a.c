#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stazioni {
        int distanza;
        int num_auto;
        int autonomia[100];
        //struct Staz *next;
}stazioni;

typedef struct nodo
{
    stazioni stazione;
    struct nodo *prima;
    struct nodo *dopo;
}nodo;

typedef struct lista
{
    nodo *head;
    nodo *tail;
}lista;
//struct Staz *head=NULL;

int o=0,k=0,l=0;
struct stazioni station[1000];

stazioni *nuova(int distanza, int num_auto, int *autonomia)
{
    stazioni *s = malloc(sizeof(stazioni));
    s->distanza=distanza;
    s->num_auto=num_auto;
    for(int d=0;d<num_auto;d++)
        {
            s->autonomia[d]=autonomia[d];
            //printf("%d %d \n", s->distanza,s->autonomia[d]);
        }
        return s;
}
/*
void aggiungi(lista *list, stazioni *stazione)
{
    nodo *nuovo=malloc(sizeof(nodo));
    if(nuovo!=NULL)
    {
        nuovo->stazione=*stazione;
        nuovo->prima=list->tail;
        nuovo->dopo=NULL;
        if(list->tail==NULL)
        {
            list->head=list->tail=nuovo;
           
        }
        
    }
}*/

void aggiungi_stazione(stazioni stazione[],int distanza, int num_auto, int autonomia[])
{
    if(stazione[distanza].distanza==0)
    {
        /*struct Staz *stat = malloc(sizeof(struct Staz));
        struct Staz *corrente=head;
        stat->distanza=distanza;
        stat->next=NULL;
        if(head==NULL)
        {
            head=stat;
        }
        else
        {
            
            while(corrente->next !=NULL)
            {
                corrente=corrente->next;
            }
            corrente->next=stat;
        }

        printf("%d\n ", corrente->distanza);*/
        stazione[distanza].distanza=distanza;
        stazione[distanza].num_auto=num_auto;
        //memcpy(stazione[distanza].autonomia, autonomia, num_auto * sizeof(int));
        for(int d=0;d<num_auto;d++)
        {
            stazione[distanza].autonomia[d]=autonomia[d];
            //printf("%d %d \n", stazione[distanza].distanza,stazione[distanza].autonomia[d]);
         }
        ///printf("aggiunta \n");
    }
    else
    {
        ///printf("non aggiunta\n");
    }
    ///printf("%d %d \n", stazione[distanza].distanza,stazione[distanza].autonomia[d]);
}

void demolisci_stazione(stazioni stazione[], int distanza, int num_auto)
{
    if(stazione[distanza].distanza!=0)
    {
        stazione[distanza].distanza=-1;
        stazione[distanza].num_auto=0;
        ///printf("demolita\n");
    }
    else
    {
        ///printf("non demolita\n");
    }
}

void aggiungi_auto(stazioni stazione[],int distanza, int num_auto, int autonomia)
{
    //stazione[distanza].autonomia[num_auto+1]=autonomia;
    int i=0; 
    while(i<sizeof(stazione[distanza].autonomia))
    {
        stazione[distanza].autonomia[i]=stazione[distanza].autonomia[i];
        i++;
    }
    stazione[distanza].autonomia[i+1]=autonomia;
    stazione[distanza].num_auto+=1;
    ///printf("aggiunto\n");
}

void rottama_auto(stazioni stazione[], int distanza, int num_auto, int autonomia[])
{
    for(int d=0;d<num_auto;d++)
    {
        if(stazione[distanza].autonomia[d]==autonomia[d])
        {
            stazione[distanza].autonomia[d]=-1;
            ///printf("%d %d \n", stazione[distanza].distanza,stazione[distanza].autonomia[d]);
            break;
        }
        else{
            //printf("non rottamato");
        }
       //printf("distanza %d  autonomia %d \n", stazione[distanza].distanza,stazione[distanza].autonomia[d]);
    }
    stazione[distanza].num_auto-=1;
    //printf("num auto %d \n", stazione[distanza].num_auto);
}

void percorso(stazioni stazione[], int distanza, int num_auto, int autonomia[], int partenza, int arrivo)
{
    int max;
    for(int d=0;d<sizeof(stazione[distanza]);d++)
                    {
                            for(int y=0;y<sizeof(stazione[distanza].autonomia);y++)
                        {
                            if(max>=stazione[d].autonomia[y])
                            {
                                max=stazione[d].autonomia[y];
                               //printf("%d ", max);
                            }
                        }
                        }
                        
                        //printf("%d ", station[o]);
                       
    //printf("arrivo -1: %d ", max);
}

void analisi_input(char *input, stazioni stazione[])
{
    char input_tagliato[20];
    //stazioni *stazione[1000];
    //int num_staz=0;
    
    int distanza=0, num_auto=0, autonomia[100],autonom;
    int partenza, arrivo;
        sscanf(input,"%s", input_tagliato); //leggo l'input fino allo spazio (whitespace)
            if(strcmp(input_tagliato,"aggiungi-stazione")==0)
            {
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
               //aggiungi_stazione(stazione,distanza, num_auto, autonomia);
               //stazione[num_staz++]=
               nuova(distanza, num_auto,autonomia);

            }
            else if(strcmp(input_tagliato,"demolisci-stazione")==0)
            {
                sscanf(input, "%*s %d", &distanza);
                //demolisci_stazione(stazione,distanza, num_auto);

            }
            else if(strcmp(input_tagliato,"aggiungi-auto")==0)
            {
                sscanf(input,"%*s %d %d", &distanza, &autonom);
                //aggiungi_auto(stazione,distanza, num_auto, autonom);
            }
            else if(strcmp(input_tagliato,"rottama-auto")==0)
            {
                l++;
                sscanf(input,"%*s %d %d", &distanza, &autonomia[l]);
                //rottama_auto(stazione,distanza, num_auto, autonomia);
                }
            else if(strcmp(input_tagliato,"pianifica-percorso")==0)
            {
                sscanf(input, "%*s %d %d", &partenza, &arrivo);
                
                
                /*for(int d=0;d<sizeof(stazione[distanza]);d++)
                    {
                        if(stazione[d].distanza!=0)
                        {
                            printf("\nstazione: %d ", stazione[d].distanza);
                            
                            station[o].distanza=stazione[d].distanza;
                            o++;
                            //printf("%d ", station[o]);
                            printf("\nautonomia: ");
                            for(int y=0;y<sizeof(stazione[distanza].autonomia);y++)
                        {
                            if(stazione[d].autonomia[y]!=0)
                            {
                                
                                printf("%d ", stazione[d].autonomia[y]);
                            }
                        }
                        }
                        
                        //printf("%d ", station[o]);
                    }   */
                //for(int p=0; p<sizeof(station[distanza].distanza);p++)
                {
                    //printf("%d ", station[p].distanza);
                }
                //printf("\n %lu", sizeof(station[o]));
                //percorso(stazione,distanza,num_auto,autonomia,partenza,arrivo);
            }
                //printf("%s", input);
                //printf("aggiungi stazione %d \n",i);
    
            //printf("%d ", stazione[distanza].distanza);
            
}
void stampa(stazioni *stazione[])
{
    /*int distanza=0;
    for(int d=0;d<sizeof(stazione[distanza]);d++)
                    {
                        if(stazione[d].distanza!=0)
                        {
                            printf("\nstazione: %d ", stazione[d].distanza);
                            
                            //station[o].distanza=stazione[d].distanza;
                            //o++;
                            //printf("%d ", station[o]);
                            printf("\nautonomia: ");
                            for(int y=0;y<sizeof(stazione[d].autonomia);y++)
                        {
                            //if(stazione[d].autonomia[y]!=0)
                            //{
                                printf("%d ", stazione[d].autonomia[y]);
                            //}
                        }
                        }
                        
                        //printf("%d ", station[o]);
                    } */
for(int d=0;d<sizeof(stazioni);d++)
        {
            printf("%d %d \n", stazione[d]->distanza,stazione[d]->autonomia[d]);
        }
}

int main(){    
    char input[1000];
    stazioni stazione[1000];

    while(fgets(input, sizeof(input), stdin)!=NULL)
    {
        analisi_input(input, stazione);
    }
    stampa(stazione);
     return 0;
}  