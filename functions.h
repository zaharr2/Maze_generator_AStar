#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "global_variables.h"

//**************************************************************************************************
void open_list_push(sOPENlist **open_list_head, sCell data);
sOPENlist *open_list_pop(sOPENlist **open_list_head);
sOPENlist *open_list_sort();
//**************************************************************************************************
sCoord get_start_poing();
sCoord get_exit_point();
sCoord get_target();
//**************************************************************************************************
void search_for_neighboring_cells();
void distance_calculation();
void shortest_path_search();
void find_way(sCoord exit_from);
void print_way();
void print_maze();
void change_node_status();
void SFML_start();
void SFML_redraw_maze();
void SFML_rectangle_abou_draw();
void SFML_rectangle_abou_init();
void SFML_draw_way_to_the_exit_from_maze();
void init_map();
void reinit_maze();
void init_maze_from_file();
//**************************************************************************************************
int G_calc(int dis_cal_line, int dis_cal_column);
int H_calc(int dis_cal_line, int dis_cal_column);
void Path_length_calc(int dis_cal_line, int dis_cal_column);
int location_relative_to_current(int dis_cal_line, int dis_cal_column);
//**************************************************************************************************
/* MAZE GENERATOR*/
void create_maze();
int unvis_neighbours_in_cell();
int have_unvisited_neighbors(sCoord current_cell);
sCoord next_cell_coord(sCoord current_cell);
pStack* pop_stack_for_maze_creation(pStack **stack_for_maze_creation);
void push_stack_for_maze_creation(pStack **stack_for_maze_creation, sCell data);
void smash_a_random_wall();

#endif // FUNCTIONS_H
