// equation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdlib.h>
#include <stdio.h>
char* remove_space(char* p) {
    char* res = (char*)malloc(sizeof(char) * (strlen(p) + 1));
    int i = 0;
    while (*p != '\0') {
        if (*p != ' ')
            res[i++] = *p;
        p++;
    }
    res[i] = '\0';
    return res;
}
double* numbers(char* p, int* l) {
    double* res = NULL;
    int len = 0;;
    char num[20];
    int i;
    char* s;
    while (*p != '\0') {
        i = 0;
        while (*p != '\0' && !(*p >= '0' && *p <= '9' || *p == '.'))
            p++;
        while (*p >= '0' && *p <= '9' || *p == '.') {
            num[i++] = *p;
            p++;
        }
        num[i] = '\0';
        res = (double*)realloc(res, sizeof(double) * (++len));
        res[len - 1] = strtod(num, &s);
    }
    *l = len;
    return res;
}
char* operators(char* p, int* l) {
    char* res = NULL;
    int len = 0;
    while (*p != '\0') {
        switch (*p) {
        case '+':
        case '-':
        case '*':
        case '/':
            res = (char*)realloc(res, sizeof(char) * (++len));
            res[len - 1] = *p;
            break;
        }
        p++;
    }
    *l = len;
    return res;
}
void remove_oper(char** oper, int index, int* len) {
    int i;
    for (i = index; i < (*len) - 1; i++) {
        (*oper)[i] = (*oper)[i + 1];
    }
    (*len)--;
    *oper = (char*)realloc(*oper, sizeof(char) * (*len));
}
void remove_num(double** num, int index, int* len) {
    int i;
    for (i = index; i < (*len) - 1; i++) {
        (*num)[i] = (*num)[i + 1];
    }
    (*len)--;
    *num = (double*)realloc(*num, sizeof(double) * (*len));
}
int index_oper(char* p, int index) {
    int i;
    int count = -1;
    for (i = 0; i <= index; i++) {
        if (p[i] == '+' || p[i] == '-' || p[i] == '*' || p[i] == '/')
            count++;
    }
    return count;
}
char* remove_brackets(char* p, int s, int e) {
    char* res = (char*)malloc(sizeof(char) * (strlen(p) + 1));
    int i, index = 0;
    for (i = 0; i < s; i++)
        res[index++] = p[i];
    for (i = s + 1; i < e; i++)
        res[index++] = p[i];
    for (i = e + 1; p[i] != '\0'; i++)
        res[index++] = p[i];
    res[index] = '\0';
    return res;
}
char* remove_inside_brackets(char* p, int s, int e) {
    char* res = (char*)malloc(sizeof(char) * (strlen(p) + 1));
    int i, index = 0;
    for (i = 0; i < s; i++)
        res[index++] = p[i];
    for (i = e + 1; p[i] != '\0'; i++)
        res[index++] = p[i];
    res[index] = '\0';
    return res;
}
int* run(char* p) {
    int i, r;
    int* res = (int*)malloc(sizeof(int) * 2);
    for (i = 0; p[i] != ')' && p[i] != '\0'; i++);
    for (r = i - 1; r > 0 && p[r] != '('; r--);
    res[0] = r;
    res[1] = i;
    return res;
}
double calc(double a, double b, char ch) {
    switch (ch) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    }
    return a + b;
}
int index_num(char* p, int index) {
    int i;
    int count = -1;
    while (p[index] != '\0' && !(p[index] >= '0' && p[index] <= '9'))
        index++;
    for (i = 0; i <= index;) {
        if (p[i] >= '0' && p[i] <= '9')
            count++;
        while (p[i] >= '0' && p[i] <= '9' || p[i] == '.')
            i++;
        while (i <= index && !(p[i] >= '0' && p[i] <= '9' || p[i] == '.'))
            i++;
    }
    return count;
}
void print(double* p, int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%.2lf,", p[i]);
    putchar('\n');
}
char* add_zero(char* p, int index) {
    char* res = (char*)malloc(sizeof(char) * (strlen(p) + 2));
    int i;
    for (i = 0; i < index; i++)
        res[i] = p[i];
    res[i++] = '0';
    while (p[i - 1] != '\0') {
        res[i] = p[i - 1];
        i++;
    }
    return res;
}
char* add_brackets(char* p) {
    char* res = (char*)malloc(sizeof(char) * (strlen(p) + 3));
    res[0] = '(';
    int i = 1;
    while (p[i-1] != '\0') {
        res[i] = p[i - 1];
        i++;
    }
    res[i++] = ')';
    res[i] = '\0';
    return res;
 }
double calculate(const char* e) {
    int len_o, len_n, i, in, r = 0, in2;
    double* num;
    char* oper, * f;
    int* indexes;
    num = numbers(e, &len_n);
    oper = operators(e, &len_o);
    char* running = remove_space(e);
    while (*running != '\0') {
        r = 0;
        indexes = run(running);
        for (i = indexes[0]; i < indexes[1] - r; i++)
            if (running[i] == '-' && !(running[i - 1] >= '0' && running[i - 1] <= '9')) {
                in = index_oper(running, i);
                in2 = index_num(running, i);
                num[in2] *= -1;
                remove_oper(&oper, in, &len_o);
                f = running;
                running = remove_brackets(running, i, i);
                r++;
                free(f);
            }
        for (i = indexes[0]; i < indexes[1] - r; i++)
            if (running[i] == '*' || running[i] == '/') {
                in = index_oper(running, i);
                in2 = index_num(running, i);
                num[in2 - 1] = calc(num[in2 - 1], num[in2], running[i]);
                remove_oper(&oper, in, &len_o);
                remove_num(&num, in2, &len_n);
                f = running;
                running = remove_brackets(running, i, i);
                free(f);
                i--;
                r++;
            }
        for (i = indexes[0]; i < indexes[1] - r; i++)
            if (running[i] == '+' || running[i] == '-') {
                in = index_oper(running, i);
                in2 = index_num(running, i);
                num[in2 - 1] = calc(num[in2 - 1], num[in2], running[i]);
                remove_oper(&oper, in, &len_o);
                remove_num(&num, in2, &len_n);
                f = running;
                running = remove_brackets(running, i, i);
                free(f);
                i--;
                r++;
            }
        f = running;
        running = remove_inside_brackets(running, indexes[0], indexes[1] - r);
        free(f);
        if (*running != '\0') {
            f = running;
            running = add_zero(running, indexes[0]);
            free(f);
        }
        free(indexes);
    }
    return num[0];
}
int main() {
    char e[500];
    char ch;
    do {
        printf("Enter mathematic equation\n");
        gets(e);
        printf( "solution = %lf\n", calculate(add_brackets(e)) );
        printf("continue press c exit other\n");
        ch = getchar();
        while (getchar() != '\n');
    } while (ch == 'c');
}