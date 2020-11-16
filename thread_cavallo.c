//
// Created by annac on 16/11/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct{ //il tipo lo possiamo passare al parametro arg che vuole l'indirizzo di memoria
    int r;
    char c;
    }param;

char vincitore=0;

void *cavallo(void *arg){ //arg sono gli argomenti passati al thread

    int cl, rg;
    char ch;

    param *para;
    para=(param *) arg; //assegno arg verso p come indirizzo
    rg = para->r++;
    ch = para->c++;

    for(cl=0; cl<30; cl++){
        printf("\033[%d;%dH%c",rg,cl,ch); //rg=riga, ch=colonna
        fflush(stdout);
        sleep(rand()%2);
    }

    if(vincitore==0) vincitore=ch;
    pthread_exit(0);
}

int main(int argc, char **argv){
    pthread_t t[20];
    int i;
    param *p; //creo un puntatore param che punta a numero di byte della struttura e indicare dimensione memoria
    p=malloc(sizeof(param));
    p->r=1; //per dare valori ai parametri che sono nulli
    p->c='A';

    for (i=0; i<20; i++){
        pthread_create(&t[i],NULL,cavallo,p);
    }

    for (i=0; i<20; i++){
        pthread_join(t[i],NULL);
    }
    printf("vincitore : %c\n",vincitore);
    return 0;
}