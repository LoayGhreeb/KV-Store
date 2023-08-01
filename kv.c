#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>


struct Node{
    int k;
    char* val;
    struct Node* next;
};

struct Node* root= NULL;
FILE *database;


void readDatabase();
void storeDatabase();
bool validCommand(char * command);
void badCommand();
struct Node* newNode(int k, char *val);
void put(int k, char *val);
void get(int k);
void delete(int k);
void clear();
void printAll();


int main(int argc, char *argv[]) {
    readDatabase();
    for(int i= 1; i < argc ; i++){
        char *command = argv[i];

        if(validCommand(command)){

            char *op = strtok(command, ",");
            char *k = strtok(NULL, ",");
            char *val = strtok(NULL, ",");

            if(strcmp(op, "p") == 0){
                asprintf(&val, "%s%s", val, "\n");
                put(atoi(k), val);
            }
            else if(strcmp(op, "g") == 0){
                get(atoi(k));
            }
            else if(strcmp(op, "d") == 0){
                delete(atoi(k));
            }
            else if(strcmp(op, "c") == 0){
                clear();
            }
            else if(strcmp(op, "a") == 0){
                printAll();
            }
        }
        else
            badCommand();
    }
    storeDatabase();
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
        put(k, line);
    }
    fclose(database);
}

void storeDatabase(){
    database = fopen("database.txt", "w");
    if(!database){
        perror("file not found!\n");
        exit(EXIT_FAILURE);
    }
    struct Node* iterator = root;
    while(iterator){
        fprintf(database, "%d,%s", iterator->k, iterator->val);
        iterator= iterator->next;
    }
}

bool validCommand(char * command){
    char *valid = "^(a|c|p,[0-9]+,[a-zA-Z0-9]+|(d|g),[0-9]+)$";
    regex_t regex;
    int result = regcomp(&regex, valid, REG_EXTENDED);
    result = regexec(&regex, command, 0, NULL, 0);
    if (result == 0)  return true;
    else return false;
}

void badCommand(){
    printf("%s\n", "bad command");
}

struct Node* newNode(int k, char *val){
    struct Node* node = malloc(sizeof (struct Node));
    node->k = k;
    node->val = malloc(strlen(val) + 1);
    strcpy(node->val, val);
    node->next = NULL;
    return node;
}

void put(int k, char *val){
    struct Node *node = newNode(k, val);
    if(!root) {
        root = node;
        return;
    }
    struct Node *iterator = root;
    while(iterator->next || iterator->k == k){
        if(iterator->k == k){
            iterator->val = node->val;
            free(node);
            return;
        }
        iterator = iterator->next;
    }
    iterator-> next = node;
}

void get(int k){
    struct Node* iterator = root;
    while(iterator){
        if(iterator-> k == k)  {
            printf("%d,%s", k, iterator->val);
            return;
        }
        iterator = iterator->next;
    }
    printf("%d %s\n", k, "not found");
}

void delete(int k){
    struct Node* iterator = root, *prev;
    if(iterator && iterator-> k  == k){
        root = root->next;
        free(iterator);
        return;
    }
    while(iterator && iterator -> k != k){
        prev = iterator;
        iterator = iterator-> next;
    }
    if(!iterator){
        printf("%d %s\n", k, "not found");
        return;
    }
    prev-> next = iterator-> next;
    free(iterator);
}

void clear(){
    struct Node* iterator = root, *temp;
    while(iterator && iterator->next){
        temp = iterator->next;
        free(iterator);
        iterator = temp;
    }
    root = NULL;
}

void printAll(){
    struct Node* iterator = root;
    while(iterator) {
        printf("K: %d\tValue : %s", iterator-> k, iterator->val);
        iterator= iterator->next;
    }
}
