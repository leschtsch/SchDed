#include <stdio.h>
#include <stdlib.h>

int is_number(char s[])
{
    char *p;
    strtod(s, &p);
    return *p == '\0';
}

int main()
{
    printf("%d\n", is_number(""));
}