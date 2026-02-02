/*
Samsr version 0.0.4

A game about sim, or a simulation with random events, decisions, implications and karma.
A simplified, text based(prototype) sim just like sim minus the graphics but deeper and complex.
Created first in php (november 1, 2016), then in javascript (may 28, 2017), then currently in C ( nov. 26, 2017)
as a console game then will develop into a full-fledged 3d game using sdl or allegro. Purpose: learn c,
game programming, 3d, to play a non-addictive, satisfying, custom-made(d.i.y) game, and become a game dev!

creation date: 11/1/2016, current update: 12/11/2017, goal finish date: 12/24/2017, created by: radgast1010
1st stable build: samsr_v003.exe
2nd stable build: samsr_v004.exe with jobs, and longer narration
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

//global variables, defaults
char start;
char *specie[] = {"Human","Zoan","Insect","E.T.","Droid"};
char *specie_name[] = {"Dennis", "Brian","James","Grace","Dogon","Arakna","Linus","Boris","Cat","Leon", "Hakon", "Ash"};
int kp_score;
char *save_date;

//test variables
char *jobs[] = {"soldier","bum","healer","thief","worker","mobster","hunter","witch"};

//structs
typedef struct
{
    char *species;
    char *species_name;
    int kp;
} PlayerData;

typedef struct
{
    int id;
    char name[300];
    int kp_yes;
    int kp_no;
} LifeProcess;

//test structs here
typedef struct
{
    char real_name[6];
    char name[7];
    char specie[7];
    char date[7];
    int score;
} Highscores;


LifeProcess fates[9] =
{
    {1, "You were out on a bar with friends, and you saw a transvestite having difficulty breathing and is chocking! she asked you to do the heimlich maneuver, would u do it ?", 10, -5},
    {2, "You are in the office once again with your mundane cubicle tasks, and your cocky boss enters the room and comments about your timidness, would u mock him behind his back ?", -5, 5},
    {3, "At teenage life you were neglected by your drunkard father and a missing mother, and youre left with no provision, would u go out to find one ?", 20,  -20},
    {4, "A priest of some big worldwide religion are giving away pamphlets about your salvation as a sinner, telling u to renew your life. Suddenly he told u to give alms, give or not ?", 30, -15},
    {5, "You are a fan of gaming and tv drama, and likes to play videogames and watch tv on the weekend, you are exhausted from the weekday work and needs to cook, call the pizza instead?", -15, 10},
    {6, "You are one of the superstar tech developer at ur company, and your a-hole of a boss is a haskell guru, sometimes u wanna learn it, would u?", 17, -8},
    {7, "A biatch friend of yours is flamboyantly showing you her new ifone-8, and she still has another phone the ifone-7 which she left the restroom near the bowl, get her phone secretly? ", -26, 9},
    {8, "You were recently heartbroken because your partner is disloyal and you were just laid off, u have inventing skills, u could invent a device that is needed by your partner in his/her work, invent it?", 30, -10},
    {9, "You had your 10year reunion at highschool, and you are an accomplished national lawyer, but her comes Tom, he wears sandals and a hoodie, but later on he told u secretly that he's an international cia spy. he asked, are u just a lawyer?", 7, -7}
};

//struct declarations
Highscores hs;

//test struct declarations here





//function declarations
int rnd(int range);
void seedrnd(void);
void set_player_data();
void options();
int get_random_event(void);
void process_decision(int eventnum, PlayerData *pd1);
void save_game(const char * species_name, const char * species, int skp);
void display_end(int kp);
void play_again(PlayerData *pd1);
void insert_to_highscores(Highscores *hs, char *names, char *species, char *dates,  int hsscore);
void write_to_file_highscores(char *real_names, char *names, char *species, char *dates, int hsscore);
int count_lines(void);
char* record_date(void);
int compare(const void * a, const void * b);
void display_and_sort_highscores();

//test functions here
int random_job(void);
void job_factor(PlayerData *pd1);


int main()
{

    printf("Welcome to SAMSARHAH v.0.0.4 \nEnter y to start, h to view highscores or x to exit!\n");
    scanf(" %c",&start);
    //options
    options();


    while(start != 'y')
    {

        printf("enter y to start, h to view highscores or x to exit...\n");

        scanf(" %c",&start);

        if(start == 'h')
        {
            puts("displaying hisghscores...\n");
            display_and_sort_highscores();
        }

        if(start == 'x')
        {
            printf("closing...");
            system("exit");
            return 0;

        }

    }

    //intro
    printf("game is started...creating random specie and name\n");

    //set player
    PlayerData pd1;
    set_player_data(&pd1);

    //process decision, loop 3x, end with score display
    int life_cycle;
    for (life_cycle = 0; life_cycle <= 6; life_cycle++)
    {



        //get random job if cycle is 2 and 4
        if(life_cycle == 1)
        {
            job_factor(&pd1);
        }

        else if(life_cycle == 4)
        {
            job_factor(&pd1);
        }

        else
        {
            //get random event
            int event_num = get_random_event();
            process_decision(event_num, &pd1);

        }




    }

    /*test area

    */

    //save game
    char save;
    printf("save game?...y for yes, x for exit! \n");
    scanf(" %c", &save);
    if(save == 'y')
    {
        save_date = record_date();

        insert_to_highscores(&hs, pd1.species_name, pd1.species, save_date, pd1.kp);

        write_to_file_highscores(hs.real_name, hs.name, hs.specie, save_date, hs.score);

        display_and_sort_highscores();

        display_end(pd1.kp);


    }
    else
    {

        display_end(pd1.kp);


    }

    //play again? or exit
    play_again(&pd1);

    return 0;
}



//function details
int rnd(int range)
{
    int r;
    r=rand()%range;
    return(r);
}
void seedrnd(void)
{
    srand((unsigned)time(NULL));
}

void set_player_data(PlayerData *samsaran)
{
    seedrnd();

    int name_size = NELEMS(specie_name);
    int specie_size = NELEMS(specie);

    (*samsaran).species_name = specie_name[rnd(name_size)];
    (*samsaran).species = specie[rnd(specie_size)];
    (*samsaran).kp = 0;

    printf("====================================\n");
    printf("* Player Data                       \n");
    printf("*  Specie: %s\n", (*samsaran).species);
    printf("*  Name: %s\n", (*samsaran).species_name);
    printf("*  Karma Points: %d\n", (*samsaran).kp);
    printf("====================================\n");

}

void options(void)
{
    if(start == 'x')
    {
        printf("closing...");
        system("exit");


    }
    if(start == 'h')
    {
        puts("displaying hisghscores...\n");
        display_and_sort_highscores();
    }
}

int get_random_event(void)
{
    int fates_arr_size = NELEMS(fates);
    seedrnd();
    int random_num = rnd(fates_arr_size);
    printf("====================================\n");
    printf("random event: %s\n", fates[random_num].name);
    int random_event = fates[random_num].id;
    return random_event;
}


void process_decision(int event_num, PlayerData *pd1)
{

    int eventnum = event_num - 1;
    char decision = '\0';

    printf("\tdecide y for yes and n for no: \n");
    scanf(" %c", &decision);

    if(decision == 'y')
    {
        printf("u decided yes.\t");
        //get the value of kpy base on the random event
        printf(" %d\n", fates[eventnum].kp_yes);
        //then add to player kp
        kp_score = fates[eventnum].kp_yes;
        pd1->kp += kp_score;
    }
    else
    {
        printf("u decided no.\t");
        //get the value of kpn base on the random event
        printf(" %d\n", fates[eventnum].kp_no);
        //then add to player kp
        kp_score = fates[eventnum].kp_no;
        pd1->kp += kp_score;

    }
    printf("karma points or score: %d \n", pd1->kp);

}


void save_game(const char * species_name, const char * species, int skp)
{


    FILE *fp;

    fp = fopen("highscores.txt","a");
    fprintf(fp, "\n");

    fprintf(fp,", ");
    fprintf(fp, species_name); //name
    fprintf(fp,", ");
    fprintf(fp, species);
    fprintf(fp,", ");
    fprintf(fp, "%d", skp);
    fprintf(fp,", ");
    fprintf(fp, __DATE__ );//date now function
    fprintf(fp," ");
    fprintf(fp, __TIME__ );//


    fclose(fp);

}

void display_end(int score)
{

    if(score < 0)
    {

        printf("            _____________________________________________________         \n");
        printf("          /                                                      \\       \n");

        printf("          |                 Ha ha, you're one hell of a scourge!  |       \n");

        printf("           \\ _____             __________________________________/       \n");

        printf("                   \\          /     __---------__                        \n");

        printf("                     \\      /      /              \\                     \n");

        printf("                      \\    /      /                 \\                   \n");

        printf("                       |  /       | _    _\\           \\                 \n");

        printf("                       | |       / /\\  /\\ |            \\               \n");

        printf("                       | |       ||  |  | | |            |                \n");

        printf("                       | |       |\\ / \\ / |             |               \n");

        printf("                       | |       |_| (||)   |_______|   |                 \n");

        printf("                       | |         |  ||     | _  / /   |                 \n");

        printf("                       \\ \\       |_________| \\/ /   /                  \n");

        printf("                         \\ \\      |_|_|_|_|/|  _/___/                   \n");

        printf("                           \\ _>      _ _/_ _ /  |                        \n");

        printf("                                     |_|_|_|_|  |                         \n");

        printf("                                    |__________/                          \n");



    }
    else
    {


        printf("            ____________________________________________________          \n");
        printf("          /                                                      \\       \n");

        printf("         |           Ha ha, you're one hell of an angel!          |       \n");

        printf("          \\ _____              __________________________________/       \n");

        printf("                   \\          __/    ___---------__                      \n");

        printf("                    \\      _/      /               \\                    \n");

        printf("                     \\    /   ---------------------------                \n");

        printf("                       |  /       | _    _ \\         \\                  \n");

        printf("                       | |        / @    @   |          \\                \n");

        printf("                       | |        |         ||           |                \n");

        printf("                       | |        |    /    |           |                 \n");

        printf("                       | |        |    |    |         |                   \n");

        printf("                       | |         |        |        |                    \n");

        printf("                        \\ \\      /_________||      /                    \n");

        printf("                         \\ \\           /    |     |                     \n");

        printf("                           \\ _>       /       |    |                     \n");

        printf("                                    |________|   |  |                     \n");

        printf("                                    |___________/                         \n");




    }


}

//play again? view highscores, or exit
void play_again(PlayerData *pd)
{

    char repeat;
    printf("play again?...y for yes, h for highscores, x for exit! \n");
    scanf(" %c", &repeat);
    if(repeat == 'y')
    {
        //reset kp, name, etc, set to 0
       // free(pd);
        PlayerData pd1;
        set_player_data(&pd1);

        //process decision, loop 3x, end with score display
        int life_cycle;
        for (life_cycle = 0; life_cycle <= 6; life_cycle++)
        {



            //get random job if cycle is 2 and 4
            if(life_cycle == 1)
            {
                job_factor(&pd1);
            }

            else if(life_cycle == 4)
            {
                job_factor(&pd1);
            }

            else
            {
                //get random event
                int event_num = get_random_event();
                process_decision(event_num, &pd1);

            }




        }



        //save game
        char save;
        printf("save game?...y for yes, x for exit! \n");
        scanf(" %c", &save);
        if(save == 'y')
        {
            //save_game(pd1.species_name, pd1.species, pd1.kp);

            save_date = record_date();

            insert_to_highscores(&hs, pd1.species_name, pd1.species, save_date, pd1.kp);

            write_to_file_highscores(hs.real_name, hs.name, hs.specie, save_date, hs.score);

            display_and_sort_highscores();

            display_end(pd1.kp);
        }




        else
        {

            display_end(pd1.kp);
            system("exit");
        }



        //play again? or exit
        play_again(&pd1);

    }
    else if(repeat == 'h')
    {

        puts("displaying highscores and exiting...\n");
        display_and_sort_highscores();
        system("pause");


    }

    else
    {
        system("exit");
    }


}

//display highscores, descending sort ,highest to lowest
void insert_to_highscores(Highscores *hs, char *names, char *species, char *dates,  int hsscore)
{

    char save_name[6];
    printf("whats your name? (pls input 5 characters)\n");
    scanf(" %s", &save_name);


    strcpy(hs->real_name, save_name);

    strcpy(hs->name, names);
    strcpy(hs->specie, species);
    strcpy(hs->date, dates);

    hs->score = hsscore;

    //test
    //printf( "%s\t%s\t%s\t%s\t%d\n", hs->real_name, hs->name, hs->specie, hs->date, hs->score);

}

void write_to_file_highscores(char *real_names, char *names, char *species, char *dates, int hsscore)
{

    FILE *file = fopen("highscores2.txt", "a");
    if(file == NULL)
    {
        printf("Error in saving highscores!");
    }

    fprintf(file, "%s\t%s\t%s\t%s\t%d\n", real_names, names, species, dates, hsscore);

    fclose(file);

}

int count_lines(void)
{

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

void display_and_sort_highscores()
{

    int lines;
    lines = count_lines();

    Highscores hsd2[lines];
    FILE *file1 = fopen("highscores2.txt", "r+");
    if(file1 == NULL)
    {
        printf("null highscores!");

    }

    printf("============== H I G H S C O R E S ====================\n");
    printf("PLAYER\tALIAS\tSPECIE\tDATE\tKarma Points\n");

    int n;
    for(n=0; n<lines; n++)
    {
        fscanf(file1,"%s\t%s\t%s\t%s\t%d\n", hsd2[n].real_name, hsd2[n].name, hsd2[n].specie, hsd2[n].date, &hsd2[n].score); //hsd is the highscore arrays

        //printf("%s\t%s\t%s\t%s\t%d\n", hsd2[n].real_name, hsd2[n].name, hsd2[n].specie, hsd2[n].date, hsd2[n].hscore);
    }

    //sort
    qsort(hsd2, lines, sizeof(Highscores), compare);
    for (n=0; n<lines; n++)
        printf("%s\t%s\t%s\t%s\t%d\n", hsd2[n].real_name, hsd2[n].name, hsd2[n].specie, hsd2[n].date, hsd2[n].score);


    fclose(file1);;

}

int compare (const void * a, const void * b)
{

    Highscores *hsA = (Highscores *)a;
    Highscores *hsB = (Highscores *)b;

    return ( hsB->score - hsA->score );
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


int random_job(void)
{
    //get job
    seedrnd();
    int jobnum = NELEMS(jobs);
    static char *jobname;
    jobname = jobs[rnd(jobnum)];
    printf("You found a job as a... \n");
    return rnd(jobnum);
}


void job_factor(PlayerData *pd1)
{
    switch(random_job())
    {
    case 0:
        pd1->kp += 6;
        printf("Job: Soldier\t Job effect to karma points: %d ,\n \'Old soldiers never die, they just fade away.\' -Macarthur\n", pd1->kp);
        break;
    case 1:
        pd1->kp -= 5;
        printf("Job: Bum\t Job effect to karma points: %d ,\n \'What is honour, my dear, when you have nothing to eat?\' -Dostoyevsky\n", pd1->kp);
        break;
    case 2:
        pd1->kp += 7;
        printf("Job: Healer\t Job effect to karma points: %d ,\n \'The life so short, the craft so long to learn.\' -Hippocrates\n", pd1->kp);
        break;
    case 3:
        pd1->kp -= 6;
        printf("Job: Thief\t Job effect to karma points: %d ,\n \'Wake early, take more!\' -Landry\n", pd1->kp);
        break;
    case 4:
        pd1->kp += 6;
        printf("Job: Worker\t Job effect to karma points: %d ,\n \'Do what ought to be done, here and now, to get you somewhere   anywhere.\' -Eriksson\n", pd1->kp);
        break;
    case 5:
        pd1->kp -= 7;
        printf("Job: Mobster\t Job effect to karma points: %d ,\n \'You can get much further with a kind word and a gun then you can with a kind word alone.\' -Capone\n", pd1->kp);
        break;
    case 6:
        pd1->kp += 5;
        printf("Job: Hunter\t Job effect to karma points: %d ,\n \'If we act like prey, theyll act like predators.\' -Harvey\n", pd1->kp);
        break;
    case 7:
        pd1->kp -= 6;
        printf("Job: Hexer\t Job effect to karma points: %d ,\n \'In Witchcraft, each of us must reveal our own truth.\' -STARHAWK\n", pd1->kp);
        break;

    }
}





