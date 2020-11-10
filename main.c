#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct expo Exponent;
struct expo {
    char tag;
    int ex;
    int ey;
    int ez;
};

typedef struct node Node;
struct node {
    Exponent EXPO;
    int COEF;
    Node *LINK;
};

typedef struct poly Polynomial;
struct poly {
    Node Term;
    Node *l;
    char *name;
};

bool expGreaterThan(Exponent alpha, Exponent beta);

bool expEquals(Exponent alpha, Exponent beta);

void POLYREAD(Polynomial *P, char **name);

void ZEROPOLY(Polynomial *P, char **name);

void POLYADD(Polynomial *P, Polynomial*Q, char **name);

int main() {
    char *name_1 = "addend_1";
    char *name_2 = "addend_2";
    char *name_sum = "sum";
    Polynomial *P = malloc(sizeof(Polynomial));
    Polynomial *Q = malloc(sizeof(Polynomial));
    POLYREAD(P, &name_1);
    POLYREAD(Q, &name_2);
    POLYADD(P,Q, &name_sum);
    return 0;
}

void POLYREAD(Polynomial *P, char **name) {
    int number_of_input, ex, ey, ez, coef;
    char buffer[1028];
    ZEROPOLY(P, name);
    scanf("%d\n", &number_of_input);
    for (int i = 0; i < number_of_input; ++i) {
        sscanf(fgets(buffer, 1027, stdin), "%d %d %d %d\n", &ex, &ey, &ez, &coef);
        Node *v = malloc(sizeof(Node));
        v->EXPO.tag = '+';
        v->EXPO.ex = ex;
        v->EXPO.ey = ey;
        v->EXPO.ez = ez;
        v->COEF = coef;
        Node *beta = P->l;
        Node *alpha = beta->LINK;
        while (expGreaterThan(alpha->EXPO, v->EXPO)) {
            beta = alpha;
            alpha = alpha->LINK;
        }
        beta->LINK = v;
        v->LINK = alpha;
    }
}

void ZEROPOLY(Polynomial *P, char **name) {
    Node *t = malloc(sizeof(Node));
    P->l = t;
    P->name = *name;
    t->EXPO.tag = '-';
    t->EXPO.ex = 0;
    t->EXPO.ey = 0;
    t->EXPO.ez = 1;
    t->LINK = t;
}

void POLYADD(Polynomial *P, Polynomial*Q, char **name) {
    Node *alpha = P->l->LINK;
    Node *beta = Q->l->LINK;
    Node *sigma = Q->l;
    while (true) {
        if (expEquals(alpha->EXPO, beta->EXPO)) {
            if (alpha->EXPO.tag == '-') {
                Q->name = *name;
                return;
            } else {
                beta->COEF += alpha->COEF;
                if (beta->COEF == 0) {
                    Node *t = beta;
                    sigma->LINK = beta->LINK;
                    beta = beta->LINK;
                    free(t);
                } else {
                    sigma = beta;
                    beta = beta->LINK;
                }
            }
            alpha = alpha->LINK;
        } else if (expGreaterThan(alpha->EXPO,beta->EXPO)) {
            Node *t = malloc(sizeof(Node));
            t->COEF = alpha->COEF;
            t->EXPO = alpha->EXPO;
            sigma->LINK = t;
            t->LINK = beta;
            sigma = t;
            alpha = alpha->LINK;
        } else {
            sigma = beta;
            beta = beta->LINK;
        }
    }
}

bool expGreaterThan(Exponent alpha, Exponent beta) {
    if (alpha.ex > beta.ex) {
        return true;
    } else if (alpha.ex == beta.ex) {
        if (alpha.ey > beta.ey) {
            return true;
        } else if (alpha.ey == beta.ey) {
            if (alpha.ez > beta.ez) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool expEquals(Exponent alpha, Exponent beta) {
    if (alpha.ex == beta.ex && alpha.ey == beta.ey && alpha.ez == beta.ez) {
        return true;
    } else {
        return false;
    }
}