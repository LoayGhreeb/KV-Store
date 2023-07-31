#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    int k;
    char* val;
    struct Node* next;
};

struct Node* root= NULL;
struct Node* last = NULL;
FILE *database;

struct Node* getNewNode(int k, char *val);
void addNode(int k, char *val);
void print();
void readDatabase();

int main(int argc, char *argv[]) {
    readDatabase();
    print();
}

void readDatabase(){
    database = fopen("database.txt", "r");
    if (!database) {
        perror("file not found!\n");
        exit(EXIT_FAILURE);
    }

    char *line;
    size_t len = 0;

    while(getline(&line, &len, database) != -1){
        int k = atoi(strsep(&line, ","));
        addNode(k, line);
    }
    fclose(database);
}

struct Node* getNewNode(int k, char *val){
    struct Node* node = malloc(sizeof (struct Node));
    node->k = k;
    node->val = malloc(strlen(val) + 1);
    strcpy(node->val, val);
    node->next = NULL;
    return node;
}

void addNode(int k, char *val){
    struct Node *newNode = getNewNode(k, val);
    if(!root) {
        root = newNode;
        last = root;
        return;
    }
    last->next = newNode;
    last = newNode;
}

void print(){
    struct Node* iterator = root;
    while(iterator) {
        printf("K: %d\tValue : %s", iterator-> k, iterator->val);
        iterator= iterator->next;
    }
}
