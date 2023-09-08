#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct veicolo
{
    int autonomia;
};

struct stazione
{
    int distanza;
    int num_auto;
    int somma;
    int num_tappe;
    struct veicolo *veicoli;
    struct stazione *next;
};

struct percorso
{
    int strada;
    int num_staz;
    struct stazione *staz;
    struct percorso *next;
    struct percorso *prev;
};
struct reverse
{
    int distanza;
    int somma;
    struct reverse *next;
};

struct stazione *stazione = NULL;
struct percorso *perco = NULL;
struct reverse *rev=NULL;

void aggiungi_stazione(int distanza, int num_auto, int *autonomie)
{
    struct stazione *questa = stazione;
    while (questa != NULL)
    {
        if (questa->distanza == distanza)
        {
            printf("non aggiunta\n");
            return;
        }
        questa = questa->next;
    }
    struct stazione *staz = (struct stazione *)malloc(sizeof(struct stazione));
    staz->distanza = distanza;
    staz->num_auto = num_auto;
    staz->veicoli = (struct veicolo *)malloc(num_auto * sizeof(struct veicolo));
    staz->next = stazione;

    if (stazione == NULL || stazione->distanza > distanza)
    {
        stazione = staz;
        printf("aggiunta\n");
    }
    else
    {
        struct stazione *stazi = stazione;
        while (stazi->next != NULL && stazi->next->distanza < distanza)
        {
            stazi = stazi->next;
        }
        staz->next = stazi->next;
        stazi->next = staz;
        printf("aggiunta\n");
    }

    for (int d = 0; d < num_auto; d++)
    {
        staz->veicoli[d].autonomia = autonomie[d];
    }
}

void demolisci_stazione(int distanza)
{
    struct stazione *prev = NULL;
    struct stazione *staz = stazione;
    while (staz != NULL)
    {
        if (staz->distanza == distanza)
        {
            if (prev != NULL)
            {
                prev->next = staz->next;
            }
            else
            {
                stazione = staz->next;
            }
            free(staz->veicoli);
            free(staz);
            printf("demolita\n");
            return;
        }
        prev = staz;
        staz = staz->next;
    }
    printf("non demolita\n");
}

void aggiungi_auto(int distanza, int num_auto, int autonomia)
{
    struct stazione *staz = stazione;
    while (staz != NULL)
    {
        if (staz->distanza == distanza)
        {
            staz->num_auto++;
            staz->veicoli = (struct veicolo *)realloc(staz->veicoli, staz->num_auto * sizeof(struct veicolo));
            staz->veicoli[staz->num_auto - 1].autonomia = autonomia;
            printf("aggiunta\n");
            return;
        }
        staz = staz->next;
    }
    printf("non aggiunta\n");
}

void rottama_auto(int distanza, int autonomia)
{
    struct stazione *staz = stazione;
    while (staz != NULL)
    {
        if (staz->distanza == distanza)
        {
            int found = 0;
            for (int i = 0; i < staz->num_auto; i++)
            {
                if (staz->veicoli[i].autonomia == autonomia)
                {
                    found = 1;
                    for (int j = i; j < staz->num_auto - 1; j++)
                    {
                        staz->veicoli[j] = staz->veicoli[j + 1];
                    }
                    staz->num_auto--;
                    staz->veicoli = (struct veicolo *)realloc(staz->veicoli, staz->num_auto * sizeof(struct veicolo));
                    printf("rottamata\n");
                    return;
                }
            }
            if (!found)
            {
                printf("non rottamata\n");
            }
            return;
        }
        staz = staz->next;
    }
    printf("non rottamata\n");
}

void somma() {
    struct stazione *staz = stazione;
    while (staz != NULL) {
        int max = 0;
        for (int i = 0; i < staz->num_auto; i++) {
            if (staz->veicoli[i].autonomia > max) {
                max = staz->veicoli[i].autonomia;
            }
        }
        staz->somma = staz->distanza + max;
        staz = staz->next;
    }
}
void somma1() {
    struct stazione *staz = stazione;
    while (staz != NULL) {
        int max = 0;
        for (int i = 0; i < staz->num_auto; i++) {
            if (staz->veicoli[i].autonomia > max) {
                max = staz->veicoli[i].autonomia;
            }
        }
        staz->somma = staz->distanza - max;
        staz = staz->next;
    }
}

void percorso(int partenza, int arrivo,int arr)
{
    
    struct stazione *staz = stazione;
    while (staz!=NULL)
    {
        //printf("%d \n", staz->distanza);
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
        per=perco;
        while(per!=NULL)
        {
            struct percorso *temp=per;
            per=per->next;
            free(temp);
        }
        perco=NULL;
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

void dirpercorso(int partenza, int arrivo)
{
    somma();
    percorso(partenza, arrivo, arrivo);
}
int percorso2(int partenza, int arrivo, int conta)
{

    struct reverse *nuov=NULL;
    struct stazione *staz = stazione;
    while(staz!=NULL)
    {
        //printf("s: %d %d\n", staz->somma, staz->distanza);
        struct reverse *newn = (struct reverse *)malloc(sizeof(struct reverse));
        newn->distanza = staz->distanza;
        newn->somma = staz->somma;
        newn->next=nuov;
        nuov=newn;

        staz=staz->next;
    }

    rev=nuov;
    struct reverse *nuo = rev;

    while (nuo!=NULL)
    {
        //printf("s: %d \n",nuo->distanza);
        if(nuo->distanza<=partenza)
        {   
            //printf("test: %d somma: %d\n", nuo->distanza,nuo->somma);
            if(nuo->somma<=arrivo && nuo->distanza>arrivo)
            {
                    
                    //printf("counts %d",count);
                    struct reverse *newn;
                    while (nuov != NULL) {
                        //printf("nuov: %d\n",nuov->distanza);
                        newn = nuov;
                        nuov = nuov->next;
                        free(newn);
                    }
                    conta=percorso2(partenza,nuo->distanza, conta+1);
                    return conta;
            }
        }    
        nuo=nuo->next;   
    }
   struct reverse *newn;
    while (nuov != NULL) {
        //printf("nuov: %d\n",nuov->distanza);
        newn = nuov;
        nuov = nuov->next;
        free(newn);
    }

//printf("conta1: %d\n",conta);
return conta;
}

void revpercorso(int partenza, int arrivo) {
    somma1();
    
    struct stazione *staz = stazione;
    int min = 10000, stazion=0;
    

    while (staz != NULL) {
        //printf("al: %d %d\n", staz->distanza, staz->somma);
        if (staz->distanza < partenza && staz->distanza >= arrivo) {
            //printf("b: %d\n", staz->distanza);
            int conta = 0;
            conta = percorso2(partenza, staz->distanza, conta); 
            //printf("c: %d\n", conta);
            staz->num_tappe = conta;
            //printf("d: %d %d\n", staz->distanza, staz->num_tappe);
            if (staz->somma <= arrivo) {
                //printf("t: %d %d\n", staz->distanza, staz->num_tappe);
                
                if (staz->num_tappe < min) {
                    min = staz->num_tappe;
                    stazion=staz->distanza;
                    //printf("min: %d %d\n", min, staz->distanza);
                }
            }
            
        }
        staz = staz->next;
    }
    staz = stazione;
    
    struct stazione *filtr = NULL;

    struct stazione *temp = (struct stazione *)malloc(sizeof(struct stazione));
    temp->distanza = stazion;
    temp->next = filtr;
    filtr = temp;

    min=min-1;
    //struct stazione *stack=NULL;
    while (staz!=NULL)
    {
        //printf("staz: %d %d\n", staz->distanza, staz->num_tappe);

        if(staz->num_tappe==min)
        {
            struct stazione *temp = (struct stazione *)malloc(sizeof(struct stazione));
            if(min==0)
            {
                temp->distanza = partenza;
                temp->next = filtr;
                filtr = temp;
                break;
            }
            //printf("d: %d %d\n",staz->distanza, staz->num_tappe);
            
            temp->distanza = staz->distanza;
            temp->next = filtr;
            filtr = temp;

            min=min-1;
        }
        else if(staz->distanza<=partenza && staz->distanza>arrivo && staz->num_tappe==0 && staz->distanza!=arrivo)
        {
            printf("nessun percorso\n");
            return;
        }
        staz=staz->next;
    }
while(filtr!=NULL)
{
    printf("%d ",filtr->distanza);
    struct stazione *temp=filtr;
    filtr=filtr->next;
    free(temp);
}
printf("%d\n",arrivo);

}

void analisi_input(char *input)
{
    char input_tagliato[200];
    int distanza=0, num_auto=0, partenza, arrivo;
    int* autonomie=NULL;
    int autonomia=0;
        sscanf(input,"%s", input_tagliato); //leggo l'input fino allo spazio (whitespace)
            if(strcmp(input_tagliato,"aggiungi-stazione")==0)
            {
                // Parse station data
                sscanf(input, "%*s %d %d", &distanza, &num_auto);
                autonomie = (int*)malloc(num_auto * sizeof(int));
                for (int d = 0; d < num_auto; d++) {
                    sscanf(input, "%*s %*d %*d %d", &autonomie[d]);
                    input = strchr(input + 1, ' ');
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
                sscanf(input,"%*s %d %d", &distanza, &autonomia);
                aggiungi_auto(distanza, 1, autonomia);
            }
            
            else if(strcmp(input_tagliato,"rottama-auto")==0)
            {
                sscanf(input,"%*s %d %d", &distanza, &autonomia);
                rottama_auto(distanza, autonomia);
            }
            
            else if(strcmp(input_tagliato,"pianifica-percorso")==0)
            {
                sscanf(input, "%*s %d %d", &partenza, &arrivo);
                if(partenza>arrivo)
                {
                    //percorso1(partenza,arrivo,arrivo,arrivo);
                    revpercorso(partenza,arrivo);
                }
                else
                {
                    dirpercorso(partenza,arrivo);
                }
                //printf("%d ",arrivo);
                
            }
            free(autonomie);
            return;
}

int main() {
    char input[10000];

    while (fgets(input, sizeof(input), stdin) != NULL) {
        analisi_input(input);
    }


    struct stazione *current = stazione;
    while (current != NULL) {
        free(current->veicoli);
        struct stazione *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}