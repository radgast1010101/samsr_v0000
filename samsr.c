#include <stdio.h>

int main(){

//variables 
char m,f;//gender
char *m_names[3];//male names in array
m_names[0] = "Adam";
m_names[1] = "Ben";
m_names[2] = "Charlie";


char *f_names[3];//female names in array
f_names[0] = "Aubrey";
f_names[1] = "Brigitte";
f_names[2] = "Cindy";

  //start game, if ok or entered y give random gender and name
  //if entered h, display highscore

char start;

 printf("hello and welcome to samsr game! \n enter y to start, h to view highscores and x to exit!");

scanf(" %c",&start);

while(start != 'y'){
	printf("enter y to start or h to view highscores...\n");
	
	scanf(" %c",&start);
if(start == 'h'){puts("displaying hisghscores...\n");}

}
	printf("game is started...giving random gender and name");

//code to give random gender, then name here..


 return 0;




}
