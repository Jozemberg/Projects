#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* left;
    struct node* right;
};
struct node* newNode(int data){
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->left  = NULL;
    node->right = NULL;
    node->data  = data;
    return(node);
}

int nodeComparison(struct node* a, struct node* b){
    if(a == NULL && b == NULL)return 1;
    if(a != NULL && b != NULL)return (nodeComparison(a->left, b->left) && nodeComparison(a->right, b->right));
    return 0;
}

struct node* insert(struct node* root,int data){

    if (root == NULL) {
        struct node* temp = newNode(data);
        return temp;
    }

    if (root->data < data) {
        root->right = insert(root->right, data);
    }else{
        root->left = insert(root->left, data);
    }

    return root;
}

int main (){
    int number_of_trees = 0;
    int number_of_isolations;
    int number_of_layers;
    int var,succ,charon,k = 0,sum;
    char sum_for_array[10];

    for (int l = 0; l < 7; ++l) {
        sum_for_array[l] = 0;
    }

    //------------number of isolations----------
    charon = getc(stdin);
    if(charon == 10)charon = getc(stdin);
    while(charon != 32 && charon != 10){
        sum_for_array[k] = charon;
        charon = getc(stdin);
        k++;
    }
    k = 0;
    number_of_isolations = atoi(sum_for_array);
    for (int l = 0; l < 10; ++l) {
        sum_for_array[l] = 0;
    }
    //-------number of layers-------------
    charon = getc(stdin);
    if(charon == 10)charon = getc(stdin);
    while(charon != 32 && charon != 10){
        sum_for_array[k] = charon;
        charon = getc(stdin);
        k++;
    }
    k = 0;
    number_of_layers = atoi(sum_for_array);
    for (int l = 0; l < 10; ++l) {
        sum_for_array[l] = 0;
    }


    struct node* nodeArrray[number_of_isolations];
    for (int i = 0; i < number_of_isolations; ++i) {
        nodeArrray[i] = NULL;
    }

    int array[number_of_isolations][number_of_layers];
//-----------------Inicializacia-Pola----------------------

    for (int i = 0; i < number_of_isolations; ++i) {
        for (int j = 0; j < number_of_layers; ++j) {
            charon = getc(stdin);
            if(charon == 10)charon = getc(stdin);
            while(charon != 32 && charon != 10){
                sum_for_array[k] = charon;
                charon = getc(stdin);
                k++;
            }
            k = 0;
            sum = atoi(sum_for_array);
            array[i][j] = sum;
            for (int l = 0; l < 10; ++l) {
                sum_for_array[l] = 0;
            }
        }
    }


//-----------------Insertovanie-Hodnot-do-Nodov------------
    for (int i = 0; i < number_of_isolations; ++i) {
        for (int j = 0; j < number_of_layers; ++j) {
            nodeArrray[i] = insert(nodeArrray[i], array[i][j]);
        }
    }
//----------------Porovnavanie-Nodov-----------------------
    for (int i = 0; i < number_of_isolations; ++i) {
        for (int j = 0; j < number_of_isolations; ++j) {
            if(i == j)j++;
            if(j >= number_of_isolations)break;
            while(nodeArrray[i] == NULL)i++;
            if(i >= number_of_isolations)break;
            succ = 1;
            var = nodeComparison(nodeArrray[i], nodeArrray[j]);
            if(var == 1)nodeArrray[j] = NULL;
        }
        if(succ == 1)number_of_trees++;
        succ = 0;
    }
   /*printf("\n");
    for (int i = 0; i < number_of_isolations; ++i) {
        for (int j = 0; j < number_of_layers; ++j) {
            printf("%d ",array[i][j]);
        }
        printf("\n");
    }
    printf("\n");*/
    printf("%d\n", number_of_trees);
    return 0;
}