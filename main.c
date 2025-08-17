#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Pokedex
{
  struct PokemonNode *PokemonListHeader; // Pointer to the header of the Pokemon List
  struct PlayerNode *PlayerListHeader; // Pointer to the header of the Player List
} Pokedex;

typedef struct PokemonNode
{
  char Name[50];
  char Type[50];
  char PrimaryAbility[100];

  struct PokemonNode *next; // Pointer to the next Pokemon Node
} PokemonNode;

typedef struct PlayerNode
{
  char Name[50];
  int PokemonOwned;
  PokemonNode* PokemonArray[20]; //Stores pointers to the nodes in the Pokemon list that the player has captured
  struct PlayerNode *next; // Pointer to the next Player Node
} PlayerNode;

Pokedex *CreatePokedex(PokemonNode *FirstPokemon,  PlayerNode *FirstPlayer)
{
  Pokedex *NewPokedex = calloc(1,sizeof(struct Pokedex)); // Allocate memory the size of a Pokedex Struct
  NewPokedex->PokemonListHeader=FirstPokemon; // Point to the first Pokemon in the list
  NewPokedex->PlayerListHeader=FirstPlayer; // Point to the first Player in the list
  return NewPokedex;
}

PokemonNode* NewPokemonNode(char Name[50], char Type[50], char PrimaryAbility[100])
{ 
  PokemonNode *new_pokemon_node = calloc(1,sizeof(struct PokemonNode)); // Allocate memory the size of a Pokemon Struct
  strcpy(new_pokemon_node->Name, Name); // Copy the user defined value for the Pokemon Name into the new node.
  strcpy(new_pokemon_node->Type, Type); // Copy the user defined value for the Pokemon Type into the new node.
  strcpy(new_pokemon_node->PrimaryAbility, PrimaryAbility); // Copy the user defined value for the Pokemon Ability into the new node.
  new_pokemon_node->next = NULL;
  return new_pokemon_node; // Return the pointer address to new_pokemon_node
}

PokemonNode* FindPokemon(Pokedex *pokedex, char Name[50])
{
  PokemonNode *temp = pokedex->PokemonListHeader; // Create a pointer to the first Pokemon Node
  PokemonNode *Output = NULL;
  int NameCheck;
  while (1)
  {
    NameCheck = strcmp(temp->Name, Name); // Compare the name in the Pokemon Node to the name provided by the user
    if (NameCheck != 0) // If the provided name is not the same as the one in the current node.
    {
      if (temp->next == NULL) // And we have reached the last node
      {
        break; // 
      }
      else // And we have not reached the last node
      {
        temp = temp->next;
      }
    }
    else
    {
      Output = temp; // Set the Output Pointer to the Pokemon Node with the requested name
      break;
    }
  }
  return Output; // Return the pointer to the Pokemon Node with the requested Name
}

void addPokemonToList(Pokedex *pokedex, char Name[50], char Type[50], char PrimaryAbility[100])
{
  if(FindPokemon(pokedex,Name) == NULL) // If the Pokemon does not exist in the Pokedex
  {
    PokemonNode *temp = pokedex->PokemonListHeader; // Create a pointer to the First Pokemon in the Pokedex
    while (1)
    {
      if (temp->next == NULL) // And we have reached the last node
      {
	      temp->next = NewPokemonNode(Name, Type, PrimaryAbility);
        break;
      }
      else // And we have not reached the last node
      {
        temp = temp->next; // Move onto the next Pokemon
      }
    }
    
  }
}

void DisplayPokemonDetails(Pokedex *pokedex, char Name[50])
{
  PokemonNode *temp = FindPokemon(pokedex,Name); // Search the Pokedex for the Pokemon
  if (temp != NULL) // If the Pokemon exists in the Pokedex, print the details of the Pokemon
  {
      printf("%s Details:\n",temp->Name);
      printf("  Pokemon Type: %s\n",temp->Type);
      printf("  Pokemon Primary Ability: %s\n",temp->PrimaryAbility);
  }
}

void ListPokemon(Pokedex *pokedex)
{
  PokemonNode *temp = pokedex->PokemonListHeader; // Create a pointer to the First Pokemon in the Pokedex
  while(1)
  {
    if(temp->next == NULL) // If we have reached the last node
    {
      printf("%s\n",temp->Name); //Print the Pokemon Name and break the while loop
      break;
    }
    else // If we have not reached the last node
    {
      printf("%s\n",temp->Name); //Print the Pokemon Name
      temp = temp->next; // Move onto the next node
    }
  }
}



PlayerNode* NewPlayerNode(char Name[50]) // Creates a new node and returns a pointer to that node - FINISHED
{
  PlayerNode *new_player_node = calloc(1,sizeof(struct PlayerNode)); // Allocate memory the size of a Player Struct
  strcpy(new_player_node->Name, Name); // Copy the user defined value for the Player Name into the new node.
  new_player_node->PokemonOwned = 0; // Set the value of Pokemon Owned in the new Player Node to 0
  new_player_node->next = NULL; // Set the next pointer to NULL because it is the last node in the list
  return new_player_node; // Return the pointer address
}

PlayerNode* FindPlayer(Pokedex *pokedex, char Name[50])
{
  PlayerNode *temp = pokedex->PlayerListHeader; // Create a pointer to the first Player Node
  PlayerNode *Output = NULL;
  int NameCheck;
  while (1)
  {
    NameCheck = strcmp(temp->Name, Name); // Compare the name in the Player Node to the name provided by the user
    if (NameCheck != 0) // If the provided name is not the same as the one in the current node.
    {
      if (temp->next == NULL) // And we have reached the last node
      {
        break; // Break out of the while loop
      }
      else // And we have not reached the last node
      {
        temp = temp->next; // Move onto the next Player Node
      }
    }
    else
    {
      Output = temp; // Set the Output Pointer to the Player Node with the requested name
      break;
    }
  }
  return Output; // Return the pointer to the Player Node with the requested Name
}

void addPlayerToList(Pokedex *pokedex, char Name[50])
{
  if(FindPlayer(pokedex,Name) == NULL)  // If the Player does not exist in the Pokedex
  {
    PlayerNode *temp = pokedex->PlayerListHeader; // Create a pointer to the First Player in the Pokedex
    while (1)
    {
      if (temp->next == NULL) // If we have reached the last node
      {
	      temp->next = NewPlayerNode(Name); //Add the new Player Node to the end of the Player List and break the while loop
        break;
      }
      else // And we have not reached the last node
      {
        temp = temp->next; // Move onto the next Player Node
      }
    }
  }
}

void ListPlayers(Pokedex *pokedex)
{
  PlayerNode *temp = pokedex->PlayerListHeader; // Create a pointer to the First Player  in the Pokedex
  while(1)
  {
    if(temp->next == NULL) // If we have reached the last node
    {
      printf("%s\n",temp->Name); //Print the player name and break the while loop
      break;
    }
    else // If we have not reached the end of the list of Players
    {
      printf("%s\n",temp->Name); // Print the player name
      temp = temp->next; //Move onto the next player
    }
  }
}

void DisplayPlayerDetails(Pokedex *pokedex, char Name[50])
{
  PlayerNode *temp = FindPlayer(pokedex,Name); // Search the Pokedex for the Player
  if (temp != NULL)
  {
      printf("%s Details:\n",temp->Name);
      printf("  Amount Of Pokemon Owned: %d\n",temp->PokemonOwned); // Prints the amount of Pokemon Owned by the Player
      for (int i = 0; i < temp->PokemonOwned; i++) //Loops through all the Pokemon owned by the player and Outputs the Pokemons Names
      {
            printf("- %s \n" , temp->PokemonArray[i]->Name);
      }
  }
}


void AddPokemonToPlayer(Pokedex *pokedex, char PlayerName[50], char PokemonName[50])
{
  PlayerNode *temp = FindPlayer(pokedex,PlayerName); //Grab the Player Node that includes the name of the player requested by the user
  PokemonNode *temp2 = FindPokemon(pokedex,PokemonName); // Grab the Pokemon Node that includes the name of the pokemon requested by the user
  if(temp != NULL && temp2 != NULL) //If both of the Nodes exist
  {
    for(int i = 0; i < 20; i++)
    {
      if(temp->PokemonArray[i] == NULL) // If the pokemon is not in the Array
      {
        temp->PokemonArray[i] = temp2; // Add the Pokemon to the list of Owned Pokemon
        temp->PokemonOwned++; // Increment the Owned Pokemon Count for the player
        break;
      }
      else if(temp->PokemonArray[i] == temp2) //If the pokemon is in the Array, do nothing
      {
        break;
      }
    }
  }
}



int main()
{
    struct PokemonNode *FirstPokemon = NewPokemonNode("Bulbasaur", "Grass", "Overgrow"); // Create the first Pokemon Node
    struct PlayerNode *FirstPlayer = NewPlayerNode("Lui"); // Create the first Player Node
    struct Pokedex *pokedex = CreatePokedex(FirstPokemon,FirstPlayer); // Create the Pokedex and link it to the First Pokemon Node and First Player Node
    addPokemonToList(pokedex, "Charmander", "Fire", "Blaze");
    addPokemonToList(pokedex, "Squirtle", "Water", "Torrent");
    addPokemonToList(pokedex, "Butterfree", "Bug", "Compound Eyes");
    addPokemonToList(pokedex, "Pikipek", "Normal", "Keen Eye");
    addPokemonToList(pokedex, "Venomoth", "Bug", "Shield Dust");
    addPokemonToList(pokedex, "Piplup", "Water", "Torrent");
    addPokemonToList(pokedex, "Ducklett", "Water", "Keen Eye");
    AddPokemonToPlayer(pokedex, "Lui", "Charmander");
    AddPokemonToPlayer(pokedex, "Lui", "Squirtle");
    AddPokemonToPlayer(pokedex, "Lui", "Butterfree");
    DisplayPokemonDetails(pokedex, "Charmander");
    DisplayPlayerDetails(pokedex, "Lui");
    ListPokemon(pokedex);
    ListPlayers(pokedex);
}
