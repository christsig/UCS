#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct searchState{
    char *state;
    int flag;
    float g;
    float h;
    struct searchState *next;
    struct searchState *prev;
};

char **states;

int L=-1,M=-1,d=-1,N=-1,ak=-1,tk1=-1,tk2=-1;

void init(){
    int i,j,flag;

    for(i=0;i<N;i++){
        states[i] = (char *)malloc((d+1)*sizeof(char));
        if(states[i] == NULL){
            exit(0);
        }
    }
    i=0;
    do{
        for(j=0;j<d/2;j++){
            states[i][j] = 'A' + rand()%L;
        }
        for(j=d/2;j<d;j++){
            states[i][j] = '0' + rand()%M;
        }
        states[i][d] = '\0';

        flag = 1;
        for(j=0;j<i;j++){
            if(strcmp(states[i],states[j]) == 0){
                flag = 0;
                break;
            }
        }
        if(flag == 1){
            i++;
        }
    }while(i<N);

    /*for(i=0;i<N;i++){
        printf("%s\n",states[i]);
    }*/
}

void ucs(){
    struct searchState *metopo;

    struct searchState *temp, *nextState, *last;
    int counter, statesCounter = 0;
    float g;

    int i,j;
    metopo = (struct searchState *)malloc(sizeof(struct searchState));
    if(metopo == NULL){
        exit(0);
    }
    metopo->g = 0;
    metopo->state = states[ak-1];
    metopo->flag = 0;
    metopo->next = NULL;
    metopo->prev = NULL;

    last = metopo;
    nextState = metopo;
    while(nextState != NULL){
        nextState = metopo;
        if(metopo->flag==1){
            while(nextState!=NULL && nextState->flag == 1){
                nextState = nextState->next;
            }
        }
        if(nextState == NULL){
            printf("Den yparxei lysh\n");
            printf("Komvoi = %d\n",statesCounter);
            break;
        }
        temp = nextState->next;
        while(temp!=NULL){
            if(temp->flag == 0 ){
                if(temp->g < nextState->g){
                    nextState = temp;
                }
            }
            temp = temp->next;
        }

        statesCounter ++;
        nextState->flag = 1;
        if(strcmp(states[tk1-1], nextState->state) == 0 || strcmp(states[tk2-1], nextState->state) == 0 ){
            printf("Vrika lysh\n");
            printf("Komvoi = %d\n",statesCounter);
            temp = nextState;
            while(temp!=NULL){
                printf("%s, %f\n",temp->state,temp->g);
                temp = temp->prev;
            }
            break;
        }
        for(i=0;i<N;i++){
            counter = 0;
            g = 0;

            for(j=0;j<d;j++){
                if(nextState->state[j] != states[i][j]){
                    counter++;
                    if(j<d/2){
                        g+=1;
                    }
                    else{
                        g+=0.5;
                    }
                }
            }
            if(counter==1){
                temp = metopo;

                while(temp != NULL){
                    if(strcmp(temp->state,states[i]) == 0 && temp->flag == 1){
                        break;
                    }
                    temp = temp->next;
                }
                if(temp == NULL){
                    temp = (struct searchState *)malloc(sizeof(struct searchState));
                    if(temp == NULL){
                        exit(0);
                    }
                    temp->g = nextState->g + g;
                    temp->state = states[i];
                    temp->flag = 0;
                    temp->next = NULL;
                    temp->prev = nextState;

                    last->next = temp;
                    last = temp;
                }
            }
        }
    }
}

void astar(){
    struct searchState *metopo;

    struct searchState *temp, *nextState, *last;
    int counter, statesCounter = 0;
    float g, h1, h2;

    int i,j;
    metopo = (struct searchState *)malloc(sizeof(struct searchState));
    if(metopo == NULL){
        exit(0);
    }
    metopo->g = 0;
    metopo->h = 0;
    metopo->state = states[ak-1];
    metopo->flag = 0;
    metopo->next = NULL;
    metopo->prev = NULL;

    last = metopo;
    nextState = metopo;
    while(nextState != NULL){
       
        nextState = metopo;
        if(metopo->flag==1){
            
            while(nextState!=NULL && nextState->flag == 1){
                nextState = nextState->next;
            }
        }
        if(nextState == NULL){
            printf("Den yparxei lysh\n");
            printf("Komvoi = %d\n",statesCounter);
            break;
        }
        temp = nextState->next;
        while(temp!=NULL){
            if(temp->flag == 0 ){
                if(temp->g + temp->h < nextState->g + nextState->h){
                    nextState = temp;
                }
            }
            temp = temp->next;
        }

        statesCounter ++;
        

        nextState->flag = 1;
      
        if(strcmp(states[tk1-1], nextState->state) == 0 || strcmp(states[tk2-1], nextState->state) == 0 ){
            printf("Vrika lysh\n");
            printf("Komvoi = %d\n",statesCounter);
            temp = nextState;
            while(temp!=NULL){
                printf("%s, %f\n",temp->state,temp->g);
                temp = temp->prev;
            }
            break;
        }
        for(i=0;i<N;i++){
            counter = 0;
            g = 0;

            for(j=0;j<d;j++){
                if(nextState->state[j] != states[i][j]){
                    counter++;
                    if(j<d/2){
                        g+=1;
                    }
                    else{
                        g+=0.5;
                    }
                }
            }
            if(counter==1){
                temp = metopo;

                while(temp != NULL){
                    if(strcmp(temp->state,states[i]) == 0 && temp->flag == 1){
                        break;
                    }
                    temp = temp->next;
                }
                if(temp == NULL){
                    temp = (struct searchState *)malloc(sizeof(struct searchState));
                    if(temp == NULL){
                        exit(0);
                    }
                    temp->g = nextState->g + g;

                    h1 = 0;
                    h2 = 0;
                    for(j=0;j<d;j++){
                        if(states[tk1-1][j] != states[i][j]){
                            if(j<d/2){
                                h1+=1;
                            }
                            else{
                                h1+=0.5;
                            }
                        }

                        if(states[tk2-1][j] != states[i][j]){
                            if(j<d/2){
                                h2+=1;
                            }
                            else{
                                h2+=0.5;
                            }
                        }
                    }
                    if(h1 < h2){
                        temp->h = h1;
                    }
                    else{
                        temp->h = h2;
                    }
                    temp->state = states[i];
                    temp->flag = 0;
                    temp->next = NULL;
                    temp->prev = nextState;

                    last->next = temp;
                    last = temp;
                }
            }
        }
    }
}

int main(){
    srand(100);

    while(L<1 || L>=10){
        printf("Dwse L: ");
        scanf("%d",&L);
    }

    while(M<1 || M>=10){
        printf("Dwse M: ");
        scanf("%d",&M);
    }

    while(d<=0 || d%2==1){
        printf("Dwse d: ");
        scanf("%d",&d);
    }

    while( N<=0){
        printf("Dwse N: ");
        scanf("%d",&N);
    }

    while(ak<=0 || ak>N){
        printf("Dwse ak: ");
        scanf("%d",&ak);
    }

    while(tk1<=0 || tk1>N){
        printf("Dwse tk1: ");
        scanf("%d",&tk1);
    }

    while(tk2<=0 || tk2>N || tk2 == tk1){
        printf("Dwse tk2: ");
        scanf("%d",&tk2);
    }

    states = (char **)malloc(N*sizeof(char *));
    if(states == NULL){
        exit(0);
    }

    init();
    printf("ak: %s\n", states[ak-1]);
    printf("tk1: %s\n", states[tk1-1]);
    printf("tk2: %s\n", states[tk2-1]);


    ucs();
    astar();
}
