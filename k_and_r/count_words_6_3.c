#include <stdio.h>
#include <string.h>

#define MAXWORD 100

struct key {
        char *word;
        int count;        
    };

void updateKeytab(struct key *tab, int kCount, char *words[], int wCount) {
    for (int i=0; i<wCount; i++) {
        for (int j=0; j<kCount; j++) {
            if (strcmp(words[i], tab[j].word)==0)
                tab[j].count++;
        }
    }
    
}

int main(int argc, char *argv[]) {
    struct key keytab[] = {
        { "auto", 0 },
        { "break", 0 }, 
        { "case", 0 },
        { "char", 0 },
        { "const", 0 },
        { "continue", 0 },
        { "void", 0 }, 
        { "while", 0 }
    };

    int kCount = sizeof(keytab)/sizeof(struct key);

    char *words[] = { "break", "void", "break", "continue", "void", "break" };
    int wCount = 6;
    
    
    updateKeytab(keytab, kCount, words, wCount);

    for (int i=0; i<kCount; i++) {
        printf("keyword %s occured %d times.\n", keytab[i].word, keytab[i].count);
    }
}

