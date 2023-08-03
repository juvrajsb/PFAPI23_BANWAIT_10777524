#include <stdio.h>
#include <stdlib.h>

int main(){    
    char input[1000];
    
    while(fgets(input, sizeof(input), stdin))
    {
    printf("%s", input);
    }
    return 0;
}