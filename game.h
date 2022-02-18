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
#include "player.h"
#include "object.h"

typedef struct _Game
{
  Player *player;//Id player_location;
  Object *object;//Id object_location;
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
  * @return NO_ID if theres no object located
  */
Id game_get_object_location(Game *game);

/**
  * @brief returns last cd_command
  * @author Profesores PPROG
  *
  * @param game a pointer to the game
  */
T_Command game_get_last_command(Game *game);

STATUS game_add_space(Game *game, Space *space);
STATUS game_add_player(Game *game, Player *player);
STATUS game_add_object(Game *game, Object *object);
Id game_get_space_id_at(Game *game, int position);
STATUS game_set_player_location(Game *game, Id id);
STATUS game_set_object_location(Game *game, Id id);

#endif