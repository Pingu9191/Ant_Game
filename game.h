/** 
 * @brief It defines the game interface
 * 
 * @file game.h
 * @author Profesores PPROG
 * @version 2.0 
 * @date 29-11-2021 
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "types.h"

typedef struct _Game
{
  Id player_location;
  Id object_location;
  Space *spaces[MAX_SPACES];
  T_Command last_cmd;
} Game;

/**
  * @brief Creates the base of a new game
  * @author Profesores PPROG
  *
  * Sets to NO_ID all ids for he game
  * @param game a pointer to the game
  * @return allways Ok
  */
STATUS game_create(Game *game);

/**
  * @brief Creates the game from a file
  * @author Profesores PPROG
  *
  * Sets the game with the info of the filename
  * @param game a pointer to the game
  * @param filename exact name of the file 
  * @return ERROR if no game or no filename
  * 
  */
STATUS game_create_from_file(Game *game, char *filename);

/**
  * @brief Updates the game
  * @author Profesores PPROG
  *
  * 
  * @param game a pointer to the game
  * @param cmd the cmd 
  * @return allways Ok
  */
STATUS game_update(Game *game, T_Command cmd);

/**
  * @brief Removes all the info of the game
  * @author Profesores PPROG
  *
  * Sets all spaces to NULL
  * @param game a pointer to the game
  * @return allways Ok
  */
STATUS game_destroy(Game *game);

/**
  * @brief Finish the game
  * @author Profesores PPROG
  *
  * @param game a pointer to the game
  * @return allways FALSE
  */
BOOL game_is_over(Game *game);

/**
  * @brief Prints useful info about
  * the game
  * @author Profesores PPROG
  *
  * @param game a pointer to the game
  */
void game_print_data(Game *game);

/**
  * @brief returns the space by its id
  * @author Profesores PPROG
  *
  * @param game a pointer to the game
  * @param id the id of the space
  * @returns ERROR if no id
  */
Space *game_get_space(Game *game, Id id);

/**
  * @brief returns player-location id
  * @author Profesores PPROG
  *
  * @param game a pointer to the game
  */
Id game_get_player_location(Game *game);

/**
  * @brief returns object-location id
  * @author Profesores PPROG
  *
  * @param game a pointer to the game
  */
Id game_get_object_location(Game *game);

/**
  * @brief returns last cd_command
  * @author Profesores PPROG
  *
  * @param game a pointer to the game
  */
T_Command game_get_last_command(Game *game);
#endif
