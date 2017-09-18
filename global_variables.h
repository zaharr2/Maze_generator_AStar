#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>

//**************************************************************************************************************************************
#define ORTHOGONALLY    10
#define DIAGONALLY      14
//**************************************************************************************************************************************
#define MAP_SIZE        81//10
#define TEXTURE_LENGTH  8//25
#define TEXTURE_LENGTH_FOR_INFO  25
//**************************************************************************************************************************************
#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY   -102
#define WAY_FOUND       -103
//**************************************************************************************************************************************
#define ENTER           13
#define SPACE           32
#define UP              72
#define RIGHT           77
#define LEFT            75
#define DOWN            80
//**************************************************************************************************************************************
typedef enum
{
    NOT_IN_THE_OPEN_LIST = 0
   ,IN_THE_OPEN_LIST
}eOPENlist;

typedef enum
{
    NOT_IN_THE_CLOSED_LIST = 0
   ,IN_THE_CLOSED_LIST
}eCLOSEDlist;

typedef enum
{
    NOT_A_STARTING_POINT = 0
   ,STARTING_POINT
}eStart;

typedef enum
{
    UNVISITED = 0
   ,VISITED
}sVisitation;

typedef enum
{
    NOT_AN_EXIT_POINT = 0
   ,EXIT_POINT
}eExit;

typedef enum
{
    NOT_CURRENT_POINT = 0
   ,CURRENT_POINT
}eCurrent;

typedef enum
{
    NOT_A_WAY = 0
   ,WAY
}eWay;

typedef int isWall;
typedef int Line;
typedef int Column;

typedef struct Coord
{
    Line   ln;
    Column clmn;
}sCoord;

typedef struct Path_length
{
    int G; // from start to current
    int H; // from current to exit_from by manhattan
    int F; // summary
}sPath_length;

typedef struct Node
{
    eWay         path;
    sCoord       node_coord;
    isWall       wall;
    eStart       strt;
    eExit        ext;
    sVisitation  visit;
    eCurrent     crnt;
    eOPENlist    opn_lst;
    eCLOSEDlist  clsd_lst;
}sNode;

typedef struct Cell
{
    sCoord        prnt_cell;
    sNode         node;
    sPath_length  pth_lngth;
}sCell;
//**************************************************************************************************************************************
typedef struct List
{
    sCell        value;
    struct List *next;
}sOPENlist, sCLOSEDlist;

typedef struct Stack
{
    sCell value;
    struct Stack *next;
}pStack;
//**************************************************************************************************************************************
sCell maze[MAP_SIZE][MAP_SIZE];

sCoord start;
sCoord exit_from;
sCoord current;
sCoord new_wall;
sCoord target_point = {(MAP_SIZE - 1) / 2, (MAP_SIZE - 1) / 2};

int dis_cal_line;
int dis_cal_column;

sf::RenderWindow window(sf::VideoMode(MAP_SIZE * TEXTURE_LENGTH + 300, MAP_SIZE * TEXTURE_LENGTH), "AStar", sf::Style::Titlebar | sf::Style::Close);
sf::RectangleShape rectangle(sf::Vector2f(TEXTURE_LENGTH, TEXTURE_LENGTH));
sf::RectangleShape rectangle_abou_200(sf::Vector2f(TEXTURE_LENGTH_FOR_INFO * 2, TEXTURE_LENGTH_FOR_INFO / 5));
sf::RectangleShape rectangle_abou_180(sf::Vector2f(TEXTURE_LENGTH_FOR_INFO * 2, TEXTURE_LENGTH_FOR_INFO / 5));
sf::RectangleShape rectangle_abou_160(sf::Vector2f(TEXTURE_LENGTH_FOR_INFO * 2, TEXTURE_LENGTH_FOR_INFO / 5));
sf::RectangleShape rectangle_abou_140(sf::Vector2f(TEXTURE_LENGTH_FOR_INFO * 2, TEXTURE_LENGTH_FOR_INFO / 5));
sf::RectangleShape rectangle_abou_120(sf::Vector2f(TEXTURE_LENGTH_FOR_INFO * 2, TEXTURE_LENGTH_FOR_INFO / 5));
sf::RectangleShape rectangle_abou_100(sf::Vector2f(TEXTURE_LENGTH_FOR_INFO * 2, TEXTURE_LENGTH_FOR_INFO / 5));
sf::RectangleShape rectangle_abou_80(sf::Vector2f(TEXTURE_LENGTH_FOR_INFO * 2, TEXTURE_LENGTH_FOR_INFO / 5));
sf::RectangleShape rectangle_abou_60(sf::Vector2f(TEXTURE_LENGTH_FOR_INFO * 2, TEXTURE_LENGTH_FOR_INFO / 5));
sf::RectangleShape rectangle_abou_40(sf::Vector2f(TEXTURE_LENGTH_FOR_INFO * 2, TEXTURE_LENGTH_FOR_INFO / 5));
sf::RectangleShape rectangle_abou_20(sf::Vector2f(TEXTURE_LENGTH_FOR_INFO * 2, TEXTURE_LENGTH_FOR_INFO / 5));
sf::RectangleShape rectangle_abou_WALL(sf::Vector2f(TEXTURE_LENGTH_FOR_INFO * 2, TEXTURE_LENGTH_FOR_INFO));
sf::Font font;
sf::Text text;
sf::Text text_no_path;
sf::Text text_path_is_foun;
sf::Text text_scale_of_path;
sf::Text text_passable_areas;
sf::Text text_impassable_areas;
sf::Text text_key_assignment;
sf::Text text_bind_key;
sf::Text text_bind_key_info;
sf::Text text_mode_maze;
sf::Text text_mode_map;
sf::Text text_mode_from_file;
sf::Texture texture;
sf::Texture scroll;
sf::Sprite sprite;
sf::Sprite sprite_scroll;

bool is_search = false;
bool cant_found_path = false;
bool mode = false;
bool from_file = false;
bool show_info = false;

sOPENlist *open_list_head = NULL;
pStack *stack_for_maze_creation = NULL;

#endif // GLOBAL_VARIABLES_H
