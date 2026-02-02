#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

//global variables
char start;
char *specie[] = {"Humans","Animals","Insects","Aliens"};
char *specie_name[] = {"Dennis","James","Grace","Dogon","Arachnid","Linus","Bear","Cat","Leon"};
int kp_score;

//structs
struct player_data
{

    char *species;
    char *species_name;
    int kp;

};

struct life_events
{
    int id;
    char name[50];
    int kp_yes;
    int kp_no;
};

 struct life_events arr_events[] =
    {
        {1, "help elderly!", 10, -5},
        {2, "mock the boss!", 0, 5},
        {3, "study hard!", 20,  -20},
        {4, "give to the poor", 30, -15},
        {5, "work hard", 15, -10},
        {6, "develop talent", 17, -8}
    };

//functions
int rnd(int range);
void seedrnd(void);
void set_player_data(int kp);
void rand_loop(void);
void options(void);
const char * get_event_name(void);
int get_event_num(void);


int main()
{

    printf("Welcome to SAMSARA v.0.0.2 \n enter y to start, h to view highscores or x to exit!\n");
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
        }

        if(start == 'x')
        {
            printf("closing...");
            system("exit");
            return 0;

        }

    }

    printf("game is started...creating random specie and name\n");

    //rand_loop();
    set_player_data(0);

    //sample life events
    int event_num = get_event_num();
    printf("event #: %d\n", event_num);

    char decision = '\0';
    printf("decide y for yes and n for no: \n");
    scanf(" %c", &decision);
    if(decision == 'y'){
    printf("u decided yes.\t");
    //get the value of kpy base on the random event
    printf(" %d\n", arr_events[event_num-1].kp_yes);
    //then add to player kp
    kp_score = arr_events[event_num-1].kp_yes;
    struct player_data pd1;
    pd1.kp = 0;
    pd1.kp += kp_score;
    }
    else{printf("u decided no.\t");
    //get the value of kpn base on the random event
    printf(" %d\n", arr_events[event_num-1].kp_no);
    //then add to player kp
    kp_score = arr_events[event_num-1].kp_no;
    struct player_data pd1;
    pd1.kp = 0;
    pd1.kp += kp_score;

    }

    printf("karma points or score: %d \n", kp_score);

    return 0;



}

//function supplements
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

void set_player_data(int kp)
{
    seedrnd();

    struct player_data pd1;
    pd1.species_name = specie_name[rnd(sizeof(&specie_name))];
    pd1.species = specie[rnd(sizeof(&specie))];
    pd1.kp = kp;

    printf("====================================\n");
    printf("* player data                       \n");
    printf("*  specie: %s\n", pd1.species);
    printf("*  specie_name: %s\n", pd1.species_name);
    printf("*  kp: %d\n", pd1.kp);
    printf("====================================\n");

}

void rand_loop(void)
{
    seedrnd();
    printf("you are reborn as %s\n", specie_name[rnd(sizeof(&specie_name))]);
    printf("in the family of the great...%s\n", specie[rnd(sizeof(&specie))]);

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
    }
}

const char * get_event_name(void)
{
    //sample life events
    printf("*******************\n");
    printf("sample life events!\n");
    struct life_events arr_events[] =
    {
        {1, "help elderly!", 10, -5},
        {2, "mock the boss!", 0, 5},
        {3, "study hard!", 20,  -20},
        {4, "give to the poor", 30, -15},
        {5, "work hard", 15, -10},
        {6, "develop talent", 17, -8}
    };

    //get random event
    seedrnd();
    int arr_size = NELEMS(arr_events);
    int r = rnd(arr_size);
    printf("random #: %d\t", r);
    //printf("random event: %d\n", arr_events[r].id);

    const char *fate = arr_events[r].name;

    return fate;
}

int get_event_num(void)
{
    //sample life events
    printf("*******************\n");
    printf("sample life events!\n");
    struct life_events arr_events[] =
    {
        {1, "help elderly!", 10, -5},
        {2, "mock the boss!", 0, 5},
        {3, "study hard!", 20,  -20},
        {4, "give to the poor", 30, -15},
        {5, "work hard", 15, -10},
        {6, "develop talent", 17, -8}
    };

    //get random event
    seedrnd();
    int arr_size = NELEMS(arr_events);
    int r = rnd(arr_size);
    printf("random #: %d\t", r);
    printf("random event: %s\n", arr_events[r].name);

    int event_num = arr_events[r].id;

    return event_num;
}










