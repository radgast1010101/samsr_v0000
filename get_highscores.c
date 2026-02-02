#include <stdio.h>
main()
{
    /*FILE *fp;
    char buff[255];

    fp = fopen("highscores.txt", "r");

    fscanf(fp, "%s", buff);
    printf("1 : %s\n", buff );

    fgets(buff, 255, (FILE*)fp);
    printf("2: %s\n", buff );

    fgets(buff, 255, (FILE*)fp);
    printf("3: %s\n", buff );
    fclose(fp);*/

    //type 2 - works
    int c;
    FILE *file;
    file = fopen("highscores.txt", "r");
    if (file)
    {
        while ((c = getc(file)) != EOF)
            putchar(c);
        fclose(file);
    }

}
