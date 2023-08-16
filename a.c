#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct veicolo
{
    int autonomia;
    //int strada;
    struct veicolo *next;
};
struct stazioni
{
    int distanza;
    int num_auto;
    int somma;
    int strada;
    struct veicolo *veicoli;
    struct stazioni *next;
};

struct percorso
{
    int percorsi;
    //int strada;
    struct percorso *next;
};


struct stazioni *stazione=NULL;
struct percorso *perco=NULL;

void aggiungi_stazione(int distanza, int num_auto, int *autonomie)
{
    struct stazioni *staz = stazione;
    while(staz!=NULL)
    {
        if(staz->distanza==distanza)
        {
            printf("non aggiunta\n");
            return;
        }
        staz=staz->next;
    }
    staz=(struct stazioni *)malloc(sizeof(struct stazioni));
    staz->distanza=distanza;
    staz->num_auto=num_auto;
    staz->veicoli=NULL;
    staz->next=stazione;
    stazione=staz;

    for(int d=0;d<num_auto;d++)
    {
        struct veicolo *veic = (struct veicolo *)malloc(sizeof(struct veicolo));
        veic->autonomia = autonomie[d];
        veic->next=staz->veicoli;
        staz->veicoli=veic;
    }
    printf("aggiunta\n");
    /*while(staz!=NULL)
    {
        printf("\nStazione:%d\n", staz->distanza);
        struct veicolo *veic = staz->veicoli;
        printf("Autonomie: \n");
        while(veic!=NULL)
        {
            printf("%d ", veic->autonomia);
            veic=veic->next;
        }
        staz=staz->next;
    }*/
}

void demolisci_stazione(int distanza)
{
    struct stazioni *staz = stazione;
    while(staz!=NULL)
    {
        if(staz->distanza==distanza)
        {
            struct veicolo *veic = staz->veicoli;
            while(veic!=NULL)
            {
                struct veicolo *nextv=veic->next;
                free(veic);
                veic=nextv;
            }
            free(staz);
            printf("demolita\n");
            return;
        }
        staz=staz->next;
    }
    printf("non demolita\n");
}

void aggiungi_auto(int distanza, int num_auto, int autonomia)
{
    struct stazioni *staz = stazione;
    while(staz!=NULL)
    {
        if(staz->distanza==distanza)
        {
            {
            struct veicolo *veic = (struct veicolo *)malloc(sizeof(struct veicolo));
            veic->autonomia = autonomia;
            veic->next=staz->veicoli;
            staz->veicoli=veic;
            printf("aggiunta\n");
            return;
            //potrei aumentare num_auto pero non so se mi serve
            }
        }
        staz=staz->next;
    }
    printf("non aggiunta\n");
}

void rottama_auto(int distanza, int autonomie)
{
    struct stazioni *staz = stazione;
    while(staz!=NULL)
    {
        if(staz->distanza==distanza)
        {
            struct veicolo *veic = staz->veicoli;
            while(veic!=NULL)
            {
                if (veic->autonomia==autonomie)
                {
                    staz->veicoli=veic->next;
                    free(veic);
                    printf("rottamata\n");
                    return;
                }
                veic=veic->next;
            }
            printf("non rottamata\n");
            return;
        }
        staz=staz->next;
    }
    printf("non rottamata\n");
}
void trova_max_autonomia()
{
    int max=0;
    struct stazioni *staz = stazione;
    while(staz!=NULL)
    {   //trovo veicolo con autonomia massima in questa stazione
        struct veicolo *veic = staz->veicoli;
        while (veic!=NULL)
        {
            if(veic->autonomia>max)
            {
                max=veic->autonomia;
            }
            
        veic=veic->next;
        }
        staz->somma= staz->distanza + max;
        printf("staz: %d somma: %d", staz->distanza, staz->somma);
        staz=staz->next;
    }
}
void percorso(int partenza, int arrivo)
{
    int  min=99999999;
    struct stazioni *staz = stazione;
    if(partenza==arrivo)
    {
        return;
    }
    if(staz->somma!=0)
    {
        printf("%d ",staz->somma);
    }
    else
    {
        trova_max_autonomia();
    }
    while (staz!=NULL)
    {
        if(staz->somma>=arrivo && staz->distanza <arrivo && staz->distanza>=partenza)
            {
                if(staz->distanza < min)
                {
                    min= staz->distanza;
                    staz->strada=min;
                }
                printf("\n min: %d \n",min);
                    //rottama_auto(min, max);
                    //per->next=perco;
                    //perco=per;

                /*{
                    struct percorso *per = (struct percorso *)malloc(sizeof(struct percorso));
                    //per=;
                    
                    per->percorsi=staz->distanza;
                    while (per!=NULL)
                    {
                        if(per->percorsi<min)
                        {
                            min= per->percorsi;
                            
                            per->strada=min;
                        }
                        per=per->next;
                    }
                    printf("\n min: %d \n",min);
                    rottama_auto(min, max);
                    //per->next=perco;
                    //perco=per;
                    if (min>=partenza)
                    {
                        percorso(partenza,min);
                    }
                    
                }*/
        }   
        if(staz->somma==0)
        {
            return;
        }
        staz=staz->next;   
    }
    staz=stazione;
    
    while (staz!=NULL)
    {
        //printf("%d ", min );
        if (min>=partenza)
            {
                percorso(partenza,min);
            }
        else {return;}
        staz=staz->next;
    }
    printf("nessun percorso\n");
    
}

void analisi_input(char *input)
{
    char input_tagliato[200];
    int distanza=0, num_auto=0, autonomie[1000];
    int partenza, arrivo;
        sscanf(input,"%s", input_tagliato); //leggo l'input fino allo spazio (whitespace)
            if(strcmp(input_tagliato,"aggiungi-stazione")==0)
            {
                sscanf(input,"%*s %d %d", &distanza, &num_auto); 
                //%*s ignora la stringa, uso & perchè puntatore
                for(int d=0; d<num_auto;d++)
                {
                    sscanf(input,"%*s %*d %*d %d", &autonomie[d]);
                    //%*d ignora l'intero
                    input=strchr(input+1, ' '); 
                    //strchr() la uso per trovare il prossimo spazio in input, cosicche input poi punta allo spazio appena trovato
                }
               aggiungi_stazione(distanza, num_auto, autonomie);
            }
            else if(strcmp(input_tagliato,"demolisci-stazione")==0)
            {
                sscanf(input, "%*s %d", &distanza);
                demolisci_stazione(distanza);
            }
            else if(strcmp(input_tagliato,"aggiungi-auto")==0)
            {
                sscanf(input,"%*s %d %d", &distanza, &*autonomie);
                aggiungi_auto(distanza, num_auto, *autonomie);
            }
            
            else if(strcmp(input_tagliato,"rottama-auto")==0)
            {
                sscanf(input,"%*s %d %d", &distanza, &*autonomie);
                rottama_auto(distanza, *autonomie);
            }
            
            else if(strcmp(input_tagliato,"pianifica-percorso")==0)
            {
                sscanf(input, "%*s %d %d", &partenza, &arrivo);
                percorso(partenza,arrivo);
            }
}

int main(){    
    char input[100000];

    while(fgets(input, sizeof(input), stdin)!=NULL)
    {
        analisi_input(input);
    }
    
    struct stazioni *staz= stazione; 
                
    while (staz!=NULL)
    {
        //printf("test");   
        printf("%d ",staz->strada);
    staz=staz->next;
    }
     return 0;
}  