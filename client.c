#include <stdio.h>

int main(void)
{
    int foo;
    scanf("%d\n", &foo);
    FILE *fp = fopen("client.log", "w");

    fprintf(fp, "%d\n", foo);
    return 0;
}
