#include <stdio.h>
#include <stdlib.h>
int* pointer[10];
int cards[10][10001]={0};
int start = 0;
int print_counter=0;
void print(){ //OK
    //print_counter++;
    //printf("print_counter = %d\n", print_counter);
    for(int i=0;i<10;i++){
        printf("%d:",i);
        int j=0;
        if(*pointer[i] == 0) printf(" No card");
        else{
            while(*(pointer[i]+j)!=0){
                printf(" %d",*(pointer[i]+j));
                j++;
            }
        }
        printf("\n");
    }
}

void place(){ //OK
    int table,len;
    scanf("%d %d",&table,&len);
    for(int i=0;i<10001;i++){
        *(pointer[table]+i) = NULL;
    }
    for(int i=0;i<len;i++){
        int num;
        scanf("%d",&num);
        *(pointer[table]+i) = num;
    }
}

void all(){ //OK
    int a,b;
    scanf("%d %d",&a,&b);
    for(int i=0;i<10;i++){
        for(int j=0;j<10001;j++){
            cards[i][j]=0;
        }
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<b;j++)
            cards[i][j]=a;
    }
}

void clear(){
    for(int i=0;i<10;i++){
        for(int j=0;j<10001;j++)
            cards[i][j]=0;
    }
}

void swap(){ //OK
    int a,b;
    scanf("%d %d",&a,&b);
    int *temp;
    temp = pointer[a];
    pointer[a] = pointer[b];
    pointer[b] = temp;
}

void shiftleft(){
    if(start == 0) start=9;
    else start--;
    //printf("start=%d\n",start);
    int counter=0;
    int mem = start;
    while(counter<10){
        pointer[mem] = &cards[counter][0];
        mem++;
        counter++;
        if(mem==10) mem=0;
    }
}

void shiftright(){
    if(start == 9) start = 0;
    else start++;
    //printf("start=%d\n",start);
    int counter=0;
    int mem = start;
    while(counter<10){
        pointer[mem] = &cards[counter][0];
        mem++;
        counter++;
        if(mem==10) mem=0;
    }
}

int main()
{
    for(int i=0;i<10;i++){
        pointer[i] = &cards[i][0];
    } //initialize
    char s[11];
    while(1){
        scanf("%s",s);
        if(s[0]=='e')
            break;
        if(s[0]=='p'){
            if(s[1]=='r') print();
            else if(s[1]=='l') place();
        }
        if(s[0]=='a') all();
        if(s[0]=='c') clear();
        if(s[0]=='s'){
            if(s[1]=='w') swap();
            else{
                if(s[5]=='l') shiftleft();
                else if(s[5]=='r')shiftright();
            }
        }
    }
    return 0;
}
