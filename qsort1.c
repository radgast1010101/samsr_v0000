/* qsort example */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{

    int id;
    //char *name;
    //char *specie;
    int score;
    //char *date;
    //char *time;

} HighscoreData;
HighscoreData list[10];

typedef struct
{
    char real_name[20];
    char name[20];
    char specie[20];
    char date[20];
    int hscore;

} Highscores;

typedef struct
{
    int hsscore;
    char real_name[20];
    char specie[20];

} Highscores2;

int i = 0;

int count_lines(void){

    FILE *fp;
    fp = fopen("highscores2.txt", "r");
    int ch=0, lines=0;

    while(!feof(fp))
    {
        ch = fgetc(fp);
        if(ch =='\n')
            {
               lines++;
            }
    }


  //printf("There are %d lines \n",lines);

  return lines;
}

int compare (const void * a, const void * b)
{

    HighscoreData *hsdA = (HighscoreData *)a;
    HighscoreData *hsdB = (HighscoreData *)b;

    return ( hsdB->score - hsdA->score );
}

int compare2 (const void * a, const void * b)
{

    Highscores *hsA = (Highscores *)a;
    Highscores *hsB = (Highscores *)b;

    return ( hsB->hscore - hsA->hscore );
}

int compare3(const void *a, const void *b)
{
    const Highscores *oa = a;
    const Highscores *ob = b;

    return  (oa->hscore < ob->hscore) - (oa->hscore > ob->hscore);
}


char* record_date(void);
void display_scores(void);
void tokenize(void);
void insert(HighscoreData *hsdata, int hsscore, int hsid)
{
    hsdata->id = hsid;
    hsdata->score = hsscore;
}

void write_to_file(int id, int score);
void display_and_sort_highscores();

int main ()
{
    srand ( time(NULL) );

    printf("Before sorting\n");
    for(i=0; i<10; i++)
    {
        list[i].score = rand()%10;
        list[i].id = i;
        printf ("hsd id = %d Score = %d \n",list[i].id, list[i].score);
        write_to_file(list[i].id, list[i].score);
    }

    //display_and_sort_highscores();

    // insert(&list[10], 11, 10);

count_lines();

    char *record;
    record = record_date();

    printf("%s",record);



    display_scores();

    // tokenize();

    /*printf("AFTER sorting\n");
    int n;
    qsort (list, 10, sizeof(HighscoreData), compare);
    for (n=0; n<10; n++)
         printf ("hsd id = %d Score = %d \n",list[n].id, list[n].score);*/
    return 0;
}

void write_to_file(int id, int score)
{

    FILE *file1 = fopen("qsort_file.txt", "a");
    if(file1 == NULL)
    {
        printf("Error in saving highscores!");
    }

    fprintf(file1, "%d\t%d\n", id, score);

    fclose(file1);
}



void display_and_sort_highscores()
{
    HighscoreData list2[20];
//display
    FILE *fileA = fopen("qsort_file.txt", "r");
    if(fileA == NULL)
    {
        printf("Error in displaying highscores!");
    }
    int n;
    printf("============== H I G H S C O R E S ====================\n");
    printf("id\tscore\n");
    for(n=0; n<20; n++)
    {
        fscanf(fileA, "%d\t%d\n", &list2[n].id, &list2[n].score); //list is the highscore list typedef struct

        printf ("%d\t%d\n",list2[n].id, list2[n].score);



        /*sort
        qsort (list, 10, sizeof(HighscoreData), compare);
        for (n=0; n<10; n++)
            printf ("%d\t%d\n",list[n].id, list[n].score);
        */
    }
    fclose(fileA);
}


void display_scores(void)
{
    int lines;
    lines = count_lines();

    Highscores hsd2[lines];
    FILE *file1 = fopen("highscores2.txt", "r");

    printf("============== H I G H S C O R E S ====================\n");
    printf("PLAYER\tALIAS\tSPECIE\tDATE\tKarma Points\n");

    int n;
    for(n=0; n<lines; n++)
    {
        fscanf(file1,"%s\t%s\t%s\t%s\t%d\n", hsd2[n].real_name, hsd2[n].name, hsd2[n].specie, hsd2[n].date, &hsd2[n].hscore); //hsd is the highscore arrays

        //printf("%s\t%s\t%s\t%s\t%d\n", hsd2[n].real_name, hsd2[n].name, hsd2[n].specie, hsd2[n].date, hsd2[n].hscore);
    }

    //sort
    qsort(hsd2, lines, sizeof(Highscores), compare2);
    for (n=0; n<lines; n++)
        printf("%s\t%s\t%s\t%s\t%d\n", hsd2[n].real_name, hsd2[n].name, hsd2[n].specie, hsd2[n].date, hsd2[n].hscore);


    fclose(file1);


}

void tokenize(void)
{
    FILE *fp;
    char *tok;
    char input[80];

    Highscores2 *pA[10];

    // pA[10] = &a[10];  //initialize struct

    fp = fopen("highscores3.txt", "r");  //open file (used #define, change path for your file)

    int n;
    for(n=0; n<10; n++)
    {
        fgets(input, 80, fp);
        tok = strtok(input, ", \t"); //You can also call strtok in loop if number of items unknown
        pA[n]->hsscore = atoi(input); //convert this string in to integer
        tok = strtok(NULL, ", \t");
        strcpy(pA[n]->real_name, tok); //copy next two strings into name variables
        tok = strtok(NULL, ", \t");
        strcpy(pA[n]->specie, tok);
        //note the format strings here for int, and char *
        printf("Karma points:%d\t Name: %s\t Specie: %s\n", pA[n]->hsscore, pA[n]->real_name, pA[n]->specie);

    }
    getchar();  //used so I can see output
    fclose(fp);

}

char* record_date(void)
{

    time_t now;
    time(&now);

    struct tm* now_tm;
    now_tm = localtime(&now);

    static char out[7];

    strftime(out, 7, "%m%d%y", now_tm);

    return out;

}
