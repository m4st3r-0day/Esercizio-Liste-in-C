#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID_LUN 16
#define FIELD_LUN 32


struct input {
    char nome[FIELD_LUN], cognome[FIELD_LUN], id[ID_LUN];
    int anno;
};

struct nodo {
    struct input data;
    struct nodo* next;
};

struct input dataInput ();
struct nodo* inserimento_in_testa(struct nodo* list, struct input newData);
struct nodo* inserimento_in_coda(struct nodo* list, struct input newData);
struct nodo* cancellazione_in_testa(struct nodo* list);
struct nodo* cancellazione_in_coda(struct nodo* list);
struct nodo* cancellazione_lista(struct nodo* list);
int lunghezza(struct nodo* list);
int ricerca_cognome(struct nodo* list, const char search[FIELD_LUN]);
void stampa(struct nodo* list);

int main()
{
    int datas;
    struct nodo* list = NULL;
    do {
        printf("1 - Inserimento in testa:\n2 - Inserimento in coda:\n3 - Cancellazione in testa:\n4 - Cancellazione in coda:\n5 - Cerca una persona dal cognome:\n6 - Quante persone ci sono nella lista:\n7 - Visualizzazione di tutti i dati:\n\nScegli: ");
        scanf("%d", &datas);
        switch(datas)
        {
            case 1:
                list = inserimento_in_testa(list, dataInput());
                break;
            case 2:
                list = inserimento_in_coda(list, dataInput());
                break;
            case 3:
                list = cancellazione_in_testa(list);
                break;
            case 4:
                list = cancellazione_in_coda(list);
                break;
            case 5: ;
                char search[FIELD_LUN];
                printf("Inserisci il cognome della persona che vuoi cercare: ");
                scanf("%s", search);
                int k = ricerca_cognome(list, search);
                if (k == -1){
                printf("Non e stato trovato nessuno con questo cognome.\n");
                break;
                }
                printf("E stato trovato la persona con cognome %s, alla posizione: %d.\n\n\n", search, k);
                break;
            case 6:
                printf("Ci sono %d persone in questa lista.\n\n\n", lunghezza(list));
                break;
            case 7:
                stampa(list);
                break;
            default: break;
        }
    } while(datas>0 && datas<8);
    list = cancellazione_lista(list);
return 0;
}

struct input dataInput (){
    struct input tmp;
    printf("Inserisci il Nome: ");
    scanf("%s", tmp.nome);
    printf("Inserisci il Cognome: ");
    scanf("%s", tmp.cognome);
    printf("Inserisci l'Anno di nascita: ");
    scanf("%d", &tmp.anno);
    printf("Inserisci il codice fiscale: ");
    scanf("%s", &tmp.id);
return tmp;
}

struct nodo* inserimento_in_testa(struct nodo* list, struct input newData)
{
    struct nodo* nuovo = (struct nodo*)malloc(sizeof(struct nodo));
    if (nuovo == NULL)
return NULL;
    strcpy(nuovo->data.nome, newData.nome);
    strcpy(nuovo->data.cognome, newData.cognome);
    nuovo->data.anno = newData.anno;
    strcpy(nuovo->data.id, newData.id);
    nuovo->next = list;
return nuovo;
}

struct nodo* inserimento_in_coda(struct nodo* list, struct input newData)
{
    struct nodo* nuovo = list;
    if (nuovo == NULL)
return inserimento_in_testa(list, newData);
    while (nuovo->next != NULL)
    nuovo = nuovo->next;
    nuovo->next = (struct nodo*) malloc(sizeof(struct nodo));
    if (nuovo->next == NULL) return NULL;
    nuovo = nuovo->next;
    strcpy(nuovo->data.nome, newData.nome);
    strcpy(nuovo->data.cognome, newData.cognome);
    nuovo->data.anno = newData.anno;
    strcpy(nuovo->data.id, newData.id);
    nuovo->next = NULL;
return list;
}

struct nodo* cancellazione_lista(struct nodo* list)
{
    if (list == NULL) return NULL;
    struct nodo* prev = list;
    while (list != NULL)
    {
        prev = list;
        list = list->next;
        free(prev);
    }
    return NULL;
}

struct nodo* cancellazione_in_testa(struct nodo* list)
{
    if (list == NULL) return NULL;

    struct nodo* del = list;
    list = list->next;
    free(del);
    return list;
}

struct nodo* cancellazione_in_coda(struct nodo* list)
{
    if (list == NULL) return NULL;
    if (list->next == NULL)
    return cancellazione_in_testa(list);
    struct nodo* copy = list, *prev = NULL;
    while (copy->next != NULL)
    {
        prev = copy;
        copy = copy->next;
    }
    prev->next = NULL;
    free(copy);
    return list;
}

int lunghezza(struct nodo* list)
{
    int lun = 0;
    while (list != NULL) {
        list = list->next;
        lun++;
    }
    return lun;
}

int ricerca_cognome(struct nodo* list, const char search[FIELD_LUN])
{
    if (list == NULL) return -1;
    int i = 0;
    while(list != NULL)
    {
        i++;
        if ( strcmp(list->data.cognome, search) == 0 )
    return i;
        list = list->next;
    }
    return -1;
}

void stampa(struct nodo* list)
{
    printf("Visualizzazione di tutte le persone.\n");
    int i=0;
    while(list != NULL)
    {
        i++;
        printf("[%d] Address: %p  -->  Nome: %s  Cognome: %s  Anno di nascita: %d  ID: %s \n", i, list, list->data.nome, list->data.cognome, list->data.anno, list->data.id);
        list = list->next;
    }
    printf("\n\n");
}
