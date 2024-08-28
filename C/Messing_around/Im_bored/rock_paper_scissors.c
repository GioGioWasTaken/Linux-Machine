#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define CHOICES_COUNT 3
#define ROCK 0
#define PAPER 1
#define SCISSORS 2

int main(int argc, char **argv) {
  int i;
  const char *Choices[3] = {"Rock", "Paper", "Scissors"};
  char *choice = argv[1]; 
  int player_choice = -1;

  if (argc < 2) {
    printf("You must provide your choice\n");
    return 1; // Exit the program
  }

  for (i = 0; i < CHOICES_COUNT; i++) {
    if (strcmp(choice, Choices[i]) == 0) {
      player_choice = i;
      break; // Exit the loop as soon as we find the match
    }
  }

  if (player_choice == -1) {
    printf("Your choice must be either Rock, Paper, or Scissors.\n");
    return 1; // Exit the program if the choice is invalid
  }

  srand(time(NULL));
  int computer_choice = rand() % CHOICES_COUNT;

  if (computer_choice == ROCK && player_choice == PAPER) {
    printf("You win! Computer chose Rock.\n");
  } else if (computer_choice == ROCK && player_choice!=ROCK) {
    printf("You Lose! Computer chose Rock.\n");
  } else if (computer_choice == PAPER && player_choice == SCISSORS) {
    printf("You win! Computer chose Paper.\n");
  } else if (computer_choice == PAPER && player_choice!=PAPER) {
    printf("You Lose! Computer chose Paper.\n");
  } else if (computer_choice == SCISSORS && player_choice == ROCK) {
    printf("You win! Computer chose Scissors.\n");
  } else if(computer_choice == SCISSORS && player_choice != SCISSORS){
    printf("You Lose! Computer chose Scissors.\n");
  } else{
    printf("Draw! Another!\n");
  }

  return 0;
}
