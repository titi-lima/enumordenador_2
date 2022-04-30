#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char data;
    struct Node* next;
};

typedef struct Node Node;

typedef struct {
    Node *head;
    Node *curr;
    Node *tail;
    char *nome;
} Link;

Link* create_list(Link *l) {
    static int cont = 0;
    l = (Link*)realloc(l, (cont+1)*sizeof(Link));
    l[cont].head = (Node*)malloc(sizeof(Node));
    l[cont].curr = (Node*)malloc(sizeof(Node));
    l[cont].tail = (Node*)malloc(sizeof(Node));
    l[cont].nome = NULL;
    l[cont].head->next = NULL;
    l[cont].curr = l[cont].head;
    l[cont].tail = l[cont].head;
    cont++;
    return l;
}

void insert(Link *l, char data, int s) { 
    Node* temp = NULL;
    temp = (Node*) malloc(sizeof(Node));
    temp->data = data;
    temp->next = l->curr->next;
    if(temp->next == NULL) {
        l->tail = temp;
    }
    l->curr->next = temp;
    l->curr = l->curr->next;
    if(s!=-1) {
        l->nome = (char*)realloc(l->nome, s*sizeof(char));
        l->nome[s-1] = data;
    }
}

void numerar(Link *l, int n) {
    for(int aux2=0; aux2<n; ++aux2) {
        static int cont=1;
        int aux = cont;
        char r;
        l[aux2].curr = l[aux2].head;
        insert(&l[aux2], '.', -1);
        insert(&l[aux2], ' ', -1);
        while(aux!=0) {
            l[aux2].curr = l[aux2].head;
            r=(aux%10)+48;
            insert(&l[aux2], r, -1);
            aux/=10;
        }
        l[aux2].curr = l[aux2].tail;
        ++cont;
    }
}

void swap(Link *ll, int i, int j) {
    Link temp;
    temp = ll[i];
    ll[i] = ll[j];
    ll[j] = temp;
}

int HoarePartition(Link *ll, int l, int r) {
    char p[10000];
    strcpy(p, ll[l].nome);
    int i = l;
    int j = r+1;
    do {
        do {
            ++i;
        } while(strcasecmp(p, ll[i].nome) > 0 && r > i);
        do {
            --j;
        } while(strcasecmp(p, ll[j].nome) < 0);
        swap(ll, i, j);
    } while(i<j);
    swap(ll, i, j);
    swap(ll, l, j);
    return j;
}

void Quicksort(Link *ll, int l, int r) {
    if(l<r) {
        int s = HoarePartition(ll, l, r);
        Quicksort(ll, l, s-1);
        Quicksort(ll, s+1, r);
    }
}

void ordenar(Link *l, int s) {
    Quicksort(l, 0, s);
}

void print(Link *l) {
    Node* temp = NULL;
    temp = l->head->next;
    while(temp->next!=NULL) {
        printf("%c", temp->data);
        temp = temp->next;
    }
    printf("%c\n", temp->data);
}

void clear(Link *l, int n) {
    for(int aux2=0; aux2<n; ++aux2) {
        Node *temp = NULL;
        Node *curr = l[aux2].head; 
        do {
            temp = curr->next;
            free(curr);
            curr = temp;
        } while(temp->next != NULL);
        free(l[aux2].nome);
        if(aux2==n-1) free(l);
    }
}

int main() {
    int k, tam, j;
    char c, str[10000];
    Link *l = NULL;
    for(j=0; scanf(" %[^\n]", str) != EOF && strcasecmp(str, "fim") != 0; ++j) {
        l = create_list(l);
        tam = strlen(str);
        for(k=0; k<tam; ++k) {
            insert(&l[j], str[k], k+1);
        }
    }
    ordenar(l, j-1);
    numerar(l, j);
    for(k=0; k<j; ++k) print(&l[k]);
    clear(l, j);
    return 0;
}