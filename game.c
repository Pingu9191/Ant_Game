/** 
 * @brief It implements the game interface and all the associated calls
 * for each command
 * 
 * @file game.c
 * @author Profesores PPROG
 * @version 2.0 
 * @date 29-11-2021 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

STATUS game_load_spaces(Game *game, char *filename);
STATUS game_add_space(Game *game, Space *space);
Id game_get_space_id_at(Game *game, int position);
STATUS game_set_player_location(Game *game, Id id);
STATUS game_set_object_location(Game *game, Id id);

void game_command_unknown(Game *game);
void game_command_exit(Game *game);
void game_command_next(Game *game);
void game_command_back(Game *game);

/**
   Game interface implementation
*/
STATUS game_create(Game *game)
{
  int i;

  for (i = 0; i < MAX_SPACES; i++)
  {
    game->spaces[i] = NULL;
  }

  game->player_location = NO_ID;
  game->object_location = NO_ID;
  game->last_cmd = NO_CMD;

  return OK;
}

 /**
 * Creates a new game from and loads the spaces from a file
 * Returns status expressions ERROR in case something goes wrong or OK if succesful
 */
STATUS game_create_from_file(Game *game, char *filename)
{
  /*Error control and creates the game*/
  if (game_create(game) == ERROR)
    return ERROR;

/*Error control and laod the spaces into the game from a file*/
  if (game_load_spaces(game, filename) == ERROR)
    return ERROR;

  /* The player and the object are located in the first space */
  game_set_player_location(game, game_get_space_id_at(game, 0));
  game_set_object_location(game, game_get_space_id_at(game, 0));

  return OK;
}

/*
* Destroys the game and all its spaces, returning OK when done
*/
STATUS game_destroy(Game *game)
{
  int i = 0;

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    space_destroy(game->spaces[i]);
  }

  return OK;
}

/*
*Adds a space to the game in the first available space position, and if there is none it returns ERROR
*/
STATUS game_add_space(Game *game, Space *space)
{
  int i = 0;

  /*Error control*/
  if (space == NULL)
  {
    return ERROR;
  }

  /*Searches the first space position available*/
  while (i < MAX_SPACES && game->spaces[i] != NULL)
  {
    i++;
  }

  /*Error control (if there is no space position left)*/
  if (i >= MAX_SPACES)
  {
    return ERROR;
  }

  game->spaces[i] = space;

  return OK;
}

  /*
  * Gets the id of a space, searching by its position
  */
Id game_get_space_id_at(Game *game, int position)
{

  /*Error control*/
  if (position < 0 || position >= MAX_SPACES)
  {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

/*
* Returns the space that coincides with the given id
*/
Space *game_get_space(Game *game, Id id)
{
  int i = 0;

  /*Error control*/
  if (id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    if (id == space_get_id(game->spaces[i]))
    {
      return game->spaces[i];
    }
  }

  return NULL;
}

/*
*Moves the player to the space of the given id 
*/
STATUS game_set_player_location(Game *game, Id id)
{

  /*Error control*/
  if (id == NO_ID)
  {
    return ERROR;
  }

  game->player_location = id;
}

/*
* Places an object in the space of the given id
*/
STATUS game_set_object_location(Game *game, Id id)
{

  int i = 0;

  /*Error control*/
  if (id == NO_ID)
  {
    return ERROR;
  }

  game->object_location = id;

  return OK;
}

/*
* Gets the location of the player
*/
Id game_get_player_location(Game *game)
{
  return game->player_location;
}

/*
* Gets the location of an object
*/
Id game_get_object_location(Game *game)
{
  return game->object_location;
}

/*
* Gets a command and depending of which one it is, it executes one of the following functions
*/
STATUS game_update(Game *game, T_Command cmd)
{
  game->last_cmd = cmd;
  
  switch (cmd)
  {
    case UNKNOWN:
      game_command_unknown(game);
      break;

    case EXIT:
      game_command_exit(game);
      break;

    case NEXT:
      game_command_next(game);
      break;

    case BACK:
      game_command_back(game);
      break;

    default:
      break;
  }

  return OK;
}

/*
* Gets the last command that has been used
*/
T_Command game_get_last_command(Game *game)
{
  return game->last_cmd;
}

/*
* Prints all the information in the struct game (Spaces, oject location, player location)
*/
void game_print_data(Game *game)
{
  int i = 0;

  printf("\n\n-------------\n\n");

  /*1. Prints the spaces and the information of each one*/
  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    space_print(game->spaces[i]);
  }

  /*2. Printf the object loaction*/
  printf("=> Object location: %d\n", (int)game->object_location);

  /*3. Printf the player loaction*/
  printf("=> Player location: %d\n", (int)game->player_location);
}

/*
* Finishes the game
*/
BOOL game_is_over(Game *game)
{
  return FALSE;
}

/**
   Calls implementation for each action 
*/
void game_command_unknown(Game *game)
{

}

void game_command_exit(Game *game)
{
  
}

/*
* Command that moves the player one space position to thes south, in case there is one.
* If not it doesnt move the player
*/
void game_command_next(Game *game)
{
  /*Initializes the private variables current_id and space_id*/
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  /*Saves the current location of the player in space_id*/
  space_id = game_get_player_location(game);

  /*Error control. Checks if the id of the space of the player is correctly saved*/
  if (space_id == NO_ID)
  {
    return;
  }

  /*Searches if there is a space at the south of the space of the player, and in case there is one, it moves the player to that space*/
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_south(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
      }
      return;
    }
  }
}

/*
* Command that moves the player one space position to thes north, in case there is one.
* If not it doesnt move the player
*/
void game_command_back(Game *game)
{

    /*Initializes the private variables current_id and space_id*/
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  /*Saves the current location of the player in space_id*/
  space_id = game_get_player_location(game);

  /*Error control. Checks if the id of the space of the player is correctly saved*/
  if (NO_ID == space_id)
  {
    return;
  }

/*Searches if there is a space at the north of the space of the player, and in case there is one, it moves the player to that space*/
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_north(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
      }
      return;
    }
  }
}

/*
* Loads the spaces and the information of each from a given file
* In case debug is being used it prints the information of each space that is loaded
* If anything has gonne wrong while using the file, it while change the exit status from OK to ERROR
*/
STATUS game_load_spaces(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space *space = NULL;
  STATUS status = OK;

  /*Error control*/
  if (!filename)
  {
    return ERROR;
  }

  file = fopen(filename, "r");

  /*Error control*/
  if (file == NULL)
  {
    return ERROR;
  }

  /*
  * While the loop reads information in the current line from the file: "hormiguero.dat", it divides that line in smaller tokens.
  * Each token has a piece of information, in the following order:
  * ID of the space, name, space at north, at east, at south, and at west.
  */
  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#s:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);
    /*If debug is being used, it will print all the information from the current space that is being loaded*/
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif

  /*Defines a private variable called "space" and saves a pointer to space with the given id in it*/
      space = space_create(id);

  /*Error control, and in case everything is fine, it saves the information gotten in the prior loop in the newly created space*/
      if (space != NULL)
      {
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        game_add_space(game, space);
      }
    }
  }

  /*Error control, if it has given an error at any moment while using the file, ferror while make the if condition be true.
   This will change the private status variable declared at the beggining of the function from OK to ERROR. */
  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}
