#include <stdio.h>
#include <string.h>

char save_name;

void save_game(void);

int main(){

  save_game();

}

void save_game(void){

   printf("whats your name?\n");
   scanf(" %s", &save_name);
   printf("saving your game ... %s\n", &save_name);

   FILE *fp;

   fp = fopen("highscores.txt","a");
   fprintf(fp, "\n");
   fprintf(fp, &save_name);//real name
   fprintf(fp,", ");
   fprintf(fp,"denis, human "); //name, specie
   fprintf(fp, "40, ");//karma points
   fprintf(fp, "12/02/2017");//date now function

   fclose(fp);

}
