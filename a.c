#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct veicolo
{
    int autonomia;
    struct veicolo *next;
};
struct stazioni
{
    int distanza;
    int num_auto;
    int somma;
    int strada;
    struct veicolo *veicoli;
    struct percorso *perco;
    struct stazioni *next;
    struct stazioni *prev;
};
struct reverse
{
    int distanza;
    int somma;
    struct reverse *next;
};

struct percorso
{
    struct stazioni *staz;
    struct reverse *nuo;
    struct percorso *next;
    struct percorso *prev;
};

struct reverse *rev=NULL;
struct stazioni *stazione=NULL;
struct percorso *perco=NULL;
struct percorso *reverseperco=NULL;

void aggiungi_stazione(int distanza, int num_auto, int *autonomie) 
{
    struct stazioni *questa=stazione;
    while (questa!=NULL)
    {
        if(questa->distanza==distanza)
        {
            printf("non aggiunta\n");
        }
        questa=questa->next;
    }
    struct stazioni *staz = (struct stazioni *)malloc(sizeof(struct stazioni));
    staz->distanza = distanza;
    staz->num_auto = num_auto;
    staz->veicoli=NULL;
    //staz->next = NULL;
    
    
    if (stazione == NULL || stazione->distanza > distanza) 
    {
        staz->next = stazione;
        stazione = staz;
        printf("aggiunta\n");
    } 
    else 
    {
        struct stazioni *stazi = stazione;
        while (stazi->next != NULL && stazi->next->distanza < distanza) 
        {
            stazi = stazi->next;
        }
        staz->next = stazi->next;
        stazi->next = staz;
        printf("aggiunta\n");
    }
    
    for(int d=1;d<=num_auto;d++)
    {
        struct veicolo *veic = (struct veicolo *)malloc(sizeof(struct veicolo));
        veic->autonomia = autonomie[d];
        veic->next=staz->veicoli;
        staz->veicoli=veic;
    }
}

void demolisci_stazione(int distanza)
{
    struct stazioni *prev=NULL;
    struct stazioni *staz = stazione;
    while(staz!=NULL)
    {
        if(staz->distanza==distanza)
        {
            if(prev!=NULL)
            {
                prev->next=staz->next;
            }
            else
            {
                staz=staz->next;
            }
            struct veicolo *veic = staz->veicoli;
            while(veic!=NULL)
            {
                
                free(veic);
                veic=veic->next;
            }
            free(staz);
            printf("demolita\n");
            return;
        }
        prev=staz;
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
            struct veicolo *prev=NULL;
            struct veicolo *veic = staz->veicoli;
            while(veic!=NULL)
            {
                if (veic->autonomia==autonomie)
                {
                    if(prev!=NULL)
                    {
                        prev->next=veic->next;
                    }
                    else
                    {
                        staz->veicoli=veic->next;
                    }
                    free(veic);
                    printf("rottamata\n");
                    return;
                }
                prev=veic;
                veic=veic->next;
            }
            printf("non rottamata\n");
            return;
        }
        staz=staz->next;
    }
    printf("non rottamata\n");
}


void percorso(int partenza, int arrivo,int arr)
{
    struct stazioni *staz = stazione;
    while(staz!=NULL)
    {   //trovo veicolo con autonomia massima in questa stazione
        struct veicolo *veic = staz->veicoli;
        int max=0;
        while (veic!=NULL)
        {
            if(veic->autonomia>max)
            {
                max=veic->autonomia;
            }
            
        veic=veic->next;
        }
        //printf("stazione: %d %d ",staz->distanza, max);
        staz->somma= staz->distanza + max;
        //printf("staz: %d somma: %d", staz->distanza, staz->somma);
        staz=staz->next;
    }

    staz=stazione;

    while (staz!=NULL)
    {
        printf("%d ", staz->distanza);
        if(staz->distanza>=partenza)
        {   
            //printf("a:%d\n",staz->distanza);
            if(staz->somma>=arrivo && staz->distanza <arrivo)
            {
                
                    struct percorso *per = (struct percorso *)malloc(sizeof(struct percorso));
                    per->staz = staz;
                    per->next = perco;
                    per->prev=NULL;
                    if(perco!=NULL)
                    {
                        perco->prev=per;
                    }
                    perco = per;
                    //printf("%d \n",staz->distanza);
                    percorso(partenza,staz->distanza, arr);
                    return; 
            }
        }  
        if(staz->somma==0)
        {
            return;
        }
        staz=staz->next;   
    }

    if(partenza==arrivo && arrivo !=arr)
    {
        struct percorso *per=perco;
        while(per!=NULL)
        {
            printf("%d ", per->staz->distanza);
            per=per->next;
        }
        printf("%d\n", arr);
        return;
    }
    else
    {
        printf("nessun percorso\n");
        struct percorso *per=perco;
        while(per!=NULL)
        {
            struct percorso *temp=per;
            per=per->next;
            free(temp);
        }
        perco=NULL;
        return;
    }
}

void percorso1(int partenza, int arrivo, int arr)
{
    struct stazioni *staz = stazione;
    while(staz!=NULL)
    {   //trovo veicolo con autonomia massima in questa stazione
        struct veicolo *veic = staz->veicoli;
        int max=0;
        while (veic!=NULL)
        {
            if(veic->autonomia>max)
            {
                max=veic->autonomia;
            }
            
        veic=veic->next;
        }
        //printf("stazione: %d %d ",staz->distanza, max);
        staz->somma= staz->distanza + max;
        //printf("staz: %d somma: %d", staz->distanza, staz->somma);
        staz=staz->next;
    }
    struct reverse *nuov=NULL;
    struct reverse *prevn=NULL;

    staz=stazione;
    while(staz!=NULL)
    {
        struct reverse *newn = (struct reverse *)malloc(sizeof(struct reverse));
        newn->distanza = staz->distanza;
        newn->somma = staz->somma;
        newn->next=NULL;
        if(nuov==NULL)
        {
            nuov=newn;
        }
        else
        {
            prevn->next=newn;
        }
        prevn=newn;
        
        staz=staz->next;
    }

    rev=nuov;
    struct reverse *nuo = rev;

    while (nuo!=NULL)
    {
        printf("test: %d ", nuo->distanza);
        if(nuo->distanza<=partenza)
        {   
            //printf("a:%d\n",staz->distanza);
            if(nuo->somma<=arrivo && nuo->distanza >arrivo)
            {
                
                    struct percorso *per = (struct percorso *)malloc(sizeof(struct percorso));
                    per->nuo = nuo;
                    per->next = perco;
                    per->prev=NULL;
                    if(perco!=NULL)
                    {
                        perco->prev=per;
                    }
                    perco = per;
                    //printf("%d \n",staz->distanza);
                    percorso(partenza,nuo->distanza, arr);
                    return; 
            }
        }    
        nuo=nuo->next;   
    }

    if(partenza==arrivo && arrivo !=arr)
    {
        struct percorso *per=perco;
        while(per!=NULL)
        {
            printf("%d ", per->nuo->distanza);
            per=per->next;
        }
        printf("%d\n", arr);
        return;
    }
    else
    {
        //printf("arrivo: %d", arrivo);
        printf("nessun percorso\n");
        struct percorso *per=perco;
        while(per!=NULL)
        {
            struct percorso *temp=per;
            per=per->next;
            free(temp);
        }
        perco=NULL;
        return;
    }
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
                if(partenza>arrivo)
                {
                    percorso1(partenza,arrivo,arrivo);
                }
                else
                {
                    percorso(partenza,arrivo, arrivo);
                }
                //printf("%d ",arrivo);
                return;
            }
}

int main(){    
    char input[100000];

    while(fgets(input, sizeof(input), stdin)!=NULL)
    {
        analisi_input(input);
    }
    
    struct stazioni *staz= stazione; 
    //struct percorso *per=perco;
    while (staz!=NULL)
    {
        //printf("test");   
        printf("%d ",staz->distanza);
        staz=staz->next;
    }    
        //while(per!=NULL)
        {
            //printf("%d ", per->staz->distanza);
            //per=per->next;
        }
        //printf("%d\n", arr);

    free(staz);

    return 0;

}