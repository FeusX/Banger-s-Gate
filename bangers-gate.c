#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

struct Player
{
  char name[32];
  int mana;
  int attack;
  int health;
};

struct Enemy
{
  int mana;
  int attack;
  int health;
  int gold;
};

void enemyStatRandomizer(struct Enemy *enemy1) // randomizes enemy stats
{
  srand(time(NULL));

  enemy1->health = rand() % 25 + 90;
  enemy1->attack = rand() % 15 + 30;
  enemy1->gold = rand() % 100 + 300;
}

struct Ans // answers to questions like shop, class etc.
{
  char answer1[4];
  char answer2[20];
  char answer3[8];
  char answer4[32];
  char answer5[8];
};

struct Ans answers;
struct Player player1;
struct Enemy enemy1;

bool criticalHitRate() // special attack's 2x damage rate
{
  return rand() % 3 == 0; // 33%
}

void specialAttack(struct Player *player1, struct Enemy *enemy1) // i know it is so basic
{
    printf("\nYou have used your special attack!\n");
    player1->mana -= 40;
    if(criticalHitRate())
    {
      enemy1->health -= player1->attack * 2;
    }
    else
    {
      enemy1->health -= player1->attack * 1.4;
    }
    printf("\nEnemy health: %d\n", enemy1->health);
}

// simulating player attack
void playerAttack(struct Player *player1, struct Enemy *enemy1)
{
  printf("\nYou have attacked!\n");
  enemy1->health -= player1->attack;
  printf("\nEnemy health: %d\n", enemy1->health);
}

// simulating enemy attack
void enemyAttack(struct Player *player1, struct Enemy *enemy1)
{
  printf("\nEnemy have attacked!\n");
  player1->health -= enemy1->attack;
  printf("\nPlayer health: %d\n", player1->health);
}

/*bool enemyEscapeRate()
{
  return rand() % 13 == 0; // it is between 8% and 7%
}*/

bool enemyHealRate()
{
  return rand() % 3 == 0; // it is 33%
}

void enemyAction() // enemy action mechanic
{
  if(enemyHealRate())
  {
    enemy1.health += 30; // heals 30 dmg
    printf("\n>Enemy healed 30 hp!\n");
    sleep(2);
    printf("\n>Enemy health: %d", enemy1.health);
    sleep(2);
  }
  else
  {
    enemyAttack(&player1, &enemy1);
    sleep(2);
  }
}

void startMenu()
{
  printf("                                              ##                                            \n");
  printf(" ####     #    #  ##   ###   #####  ####     #     ###           ###     #   ######  ##### \n");
  printf(" ## ##   ###   ## ##  ## ##  ##     ## ##   #     ## ##         ## ##   ###    ##    ##    \n");
  printf(" ## ##  ## ##  #####  ##     ##     ## ##         ##            ##     ## ##   ##    ##  \n");
  printf(" ####   ## ##  #####  #####  ####   ####           ###          #####  ## ##   ##    ####  \n");
  printf(" ## ##  #####  #####  ## ##  ##     ###              ##         ## ##  #####   ##    ##    \n");
  printf(" ## ##  ## ##  ## ##  ## ##  ##     ####          ## ##         ## ##  ## ##   ##    ##   \n");
  printf(" ####   ## ##  ##  #   ####  #####  ## ##          ###           ####  ## ##   ##    ##### \n");
  printf("                                                                                           \n");

}

bool enemyEncounterRate()
{
  return rand() % 3 == 0;  // 33% rate
}
bool healthpot1 = false; // checks if health pot is purchased
bool manapot1 = false; // same with mana pot

int playerGold = 300;

void marketingSystem()
{
  sleep(3);
  printf("\n>Gold is currency in this game, what would you like to buy?\n");
  sleep(3);


  printf("\nHealth Potion: Restores 50 hp. (300G)\n");
  sleep(3);
  printf("\nAttack Enchant: Gives 10 more attack. (300G)\n");
  sleep(3);
  printf("\nMana Potion: Restores 40 mana. (300G)\n");
  sleep(3);

  printf("\nYou have only %dG", playerGold);

  while (1)
  {
    printf("\n>Which one would you like to buy (healthpot, attack, manapot) ? ");
    printf("\nIf you want to exit, type 'exit'\n");
    printf("\n>");
    scanf("%s", answers.answer2);

    if(strcmp(answers.answer2, "healthpot") == 0 && playerGold >= 300)
    {
      printf("\nYou have bought a Health Potion.\n");
      sleep(2);
      healthpot1 = true;
      playerGold -= 300;
      break;
    }
    else if(strcmp(answers.answer2, "attack") == 0 && playerGold >= 300)
    {
      printf("\nYou have bought Attack Enchant.\n");
      sleep(2);
      player1.attack += 10;
      playerGold -= 300;
    }
    else if(strcmp(answers.answer2, "manapot") == 0 && playerGold >= 300)
    {
      printf("\nYou have bought Mana Potion");
      sleep(2);
      manapot1 = true;
      playerGold -= 300;
      break;
    }
    else if(strcmp(answers.answer2, "exit") == 0)
    {
      break;
    }
    else
    {
      printf("\nInvalid answer.\n");
    }
  }
}

int main()
{

  srand(time(NULL)); // seed randomizer
  enemyStatRandomizer(&enemy1);
  criticalHitRate(&player1);
  enemyHealRate(&enemy1);

  startMenu();

  printf("\nEnter your name, player: ");
  scanf("%s", player1.name);

  printf("\nWelcome, %s\n", player1.name);
  sleep(1.5);

  printf("\n>Choose your class: "); // i didn't make the class selection as a separate function because you choose just one time
  sleep(1);
    
  printf("\n>A note to player: You must use lowercase letters when answering. \n");
  sleep(2);
    
  printf("\n>Knight: More health and attack but less mana.\n");
  sleep(3);

  printf("\n>Wizard: More mana and attack but slightly less health.\n");
  sleep(3);

  printf("\n>Assassin: More attack but less health and slightly less mana.\n");
  

  while (1)
  {
    printf("\n>Which one do you choose (assassin, wizard, knight): ");
    scanf("%s", answers.answer1);

    if(strcmp(answers.answer1, "assassin") == 0)
    {
      player1.attack = 40;
      player1.health = 60;
      player1.mana = 70;

      printf("\nYour stats are like these: \n");
      sleep(2);

      printf("\nAttack: %d\n", player1.attack);
      sleep(1);
      printf("\nHealth: %d\n", player1.health);
      sleep(1);
      printf("\nMana: %d\n", player1.mana);
      sleep(1);
      break;
    }
    else if(strcmp(answers.answer1, "wizard") == 0)
    {
      player1.attack = 35;
      player1.health = 50;
      player1.mana = 130;

      printf("\nYour stats are like these: \n");
      sleep(2);

      printf("\nAttack: %d\n", player1.attack);
      sleep(1);
      printf("\nHealth: %d\n", player1.health);
      sleep(1);
      printf("\nMana: %d\n", player1.mana);
      sleep(1);
      break;
    }
    else if(strcmp(answers.answer1, "knight") == 0)
    {
      player1.attack = 25;
      player1.health = 90;
      player1.mana = 50;

      printf("\nYour stats are like these: \n");
      sleep(2);

      printf("\nAttack: %d\n", player1.attack);
      sleep(1);
      printf("\nHealth: %d\n", player1.health);
      sleep(1);
      printf("\nMana: %d\n", player1.mana);
      sleep(1);
      break;
    }
    else
    {
      printf("\nInvalid answer.\n");
    }
    
  }

  marketingSystem();

  sleep(3);
  printf("\nSo you seem you are done, lets play.\n");
  sleep (5);

  printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  
  printf("\n>Basic controls: attack/escape/hpboost/special/manaboost\n");
  printf("\n>Special deals x2 damage of your attack and costs 40 mana.\n");
  printf("\n>Don't forget, you must answer in lowercase letters.\n");

  printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");


  while (1)
  {
    printf("\nexplore/shop/exit: ");
    scanf("%s", answers.answer3);

    if(strcmp(answers.answer3, "explore") == 0)
    {
      if(enemyEncounterRate())
      {
        printf("\n>You have encountered an enemy!\n");
        sleep(3);

        printf("\nEnemy stats\n");
        sleep(2);
        printf("\nAttack: %d\n", enemy1.attack);
        sleep(1);
        printf("\nHealth: %d\n", enemy1.health);
        sleep(1);
        printf("\nGold: %d\n", enemy1.gold);

        bool playerTurn = true; // there is the boolean that checks if is it player turn

        while (player1.health > 0 && enemy1.health > 0)
        {
          if(playerTurn)
          {
            printf("\n>Your turn (attack/escape/hpboost/special/manaboost): ");
            scanf("%s", answers.answer4);

            if(strcmp(answers.answer4, "attack") == 0)
            {
              playerAttack(&player1, &enemy1);
              sleep(2);
            }
            else if(strcmp(answers.answer4, "escape") == 0)
            {
              printf("\nYou have escaped.\n");
              enemyStatRandomizer(&enemy1);
              break;
            }
            else if(strcmp(answers.answer4, "hpboost") == 0 && healthpot1 == true)
            {
              player1.health += 50;
              printf("\nYour hp is restored to %d.\n", player1.health);
            }
            else if(strcmp(answers.answer4, "manaboost") == 0 && manapot1 == true)
            {
              player1.mana += 40;
              printf("\nYour mana is restored to %d.\n", player1.mana);
            }
            else if(strcmp(answers.answer4, "special") == 0 && player1.mana >= 40) // special (!) attack casts 40 mana
            {
              specialAttack(&player1, &enemy1);
              sleep(3);
            }
            else
            {
              printf("\nInvalid input.\n");
            }
          }
          else
          {
            printf("\n>Enemy's turn.\n");
            if(enemy1.health > 0)
            {
              enemyAction(&player1, &enemy1);
            }
          }
            playerTurn = !playerTurn;

            if(enemy1.health <= 0)
            {
              printf("\nEnemy defeated!\n");
              playerGold += enemy1.gold; // if enemy dies, you get the gold
              enemyStatRandomizer(&enemy1); // if enemy dies, his stats randomizes
              break;
            }

            if(player1.health <= 0)
            {
              printf("\nYou are dead, game over!\n");
              sleep(5);
              return 0;
              break;
            }
}
      }
      else
      {
        printf("\nYou haven't encountered an enemy yet!\n");
      }
    }
    else if(strcmp(answers.answer3, "exit") == 0)
    {
      sleep(3);
      printf("\n>Exiting the game, good bye...\n");
      break;
    }
    else if(strcmp(answers.answer3, "shop") == 0)
    {
      marketingSystem();
    }
    else
    {
      printf("\nInvalid option.\n");
    }
  }

  //system("pause"); // that is essential when you compile as .exe

  return 0;
}
