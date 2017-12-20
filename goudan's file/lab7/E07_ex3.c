#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/syscall.h>
#include "Stack.h"

typedef struct ttree{
    int deep;
    pthread_t tid;
    struct ttree *left;
    struct ttree *right;
}ttree,*Tree;

int n;

void * thread_handler(void *);
Tree creat_item(Tree, int);
void creat_tree(Tree, int);
void print_tree(Tree, SqStack *);
void destroy_tree(Tree);

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("the number of args is wrong!\n");
        return -1;
    }
    
    n = atoi(argv[1]);
    Tree root;
    creat_tree(root,n);
    root->tid = pthread_self();
    
    if (n>0) {
        root->left->deep=n-1;
        pthread_create(&root->left->tid, NULL, thread_handler, root->left);
        root->right->deep=n-1;
        pthread_create(&root->right->tid, NULL, thread_handler, root->right);
    }
    
    SqStack *s;
    s = InitStack(s);
    print_tree(root,s);
    destroy_tree(root);
    
    return 0;
}

void *thread_handler(void *args){
    Tree t = (Tree)args;
    if(t->deep == 0)
    {   t->left = NULL;
        t->right = NULL;
        exit(0);
    }else{
        pthread_create(&t->left->tid, NULL, thread_handler, t->left);
        pthread_create(&t->right->tid, NULL, thread_handler, t->right);
    }
    return NULL;
}

void creat_tree(Tree t,int n){
    if (n==0) {
        t = creat_item(t,n);
        return ;
    }else{
        creat_item(t,n);
        creat_tree(t->left,n-1);
        creat_tree(t->right,n-1);
    }
    return;
}

Tree creat_item(Tree t,int n){
    t = (Tree)malloc(sizeof(ttree));
    t->deep = n;
    t->tid = 0;
    t->left = NULL;
    t->right = NULL;
    return t;
}

void print_tree(Tree t, SqStack *s){
    if(t)
    {
        Push(s,t->tid);
        if(!t->left&&!t->right)
            print(s);
        else
        {
            print_tree(t->left,s);
            print_tree(t->right,s);
        }
        Pop(s);
    }
}

void destroy_tree(Tree t){
    if (t==NULL) {
        return;
    }
    destroy_tree(t->left);
    destroy_tree(t->right);
    free(t);
}

