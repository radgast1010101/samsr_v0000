#include <stdio.h>

char start;

int main()
{



    printf("hello from c and powershell! start learning c now! \n press y to start x to exit\n");
    scanf("%c", &start);
    if(start == 'x')
    {
        printf("closing...");
        system("exit");
        return 0;

    }
    while(start != 'y')
    {

        printf("press y t start or x to exit!");
        scanf(" %c", &start);

        if(start == 'x')
        {
            printf("closing...");
            system("exit");
            return 0;

        }
    }

    printf("we'll be using windows os, first download minGw from www.mingw.com or google mingw\n");
    printf("then locate the directory add the bin folder to the environment variables, to use globally in console!\n");

    system("pause");

    return 0;

}
