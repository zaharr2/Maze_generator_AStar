#include "global_variables.h"
#include "functions.h"



//**************************************************************************************************************************************
int main()
{
    SFML_start();
    return 0;
}
//**************************************************************************************************************************************
/* A* */
void shortest_path_search()
{
    float current_farme = 0;

    while(maze[exit_from.ln][exit_from.clmn].node.crnt != CURRENT_POINT)
    {
        is_search = true;
        current_farme += 0.08;
        if(current_farme > 10) current_farme -= 10;
        sprite.setTextureRect(sf::IntRect(int(current_farme) * 101, 0, 101, 82));

        maze[current.ln][current.clmn].node.crnt = NOT_CURRENT_POINT;

        open_list_head = open_list_sort();

        if(open_list_head != NULL)
            current = open_list_pop(&open_list_head)->value.node.node_coord;
        else
        {
            cant_found_path = true;
            return;
        }
        maze[current.ln][current.clmn].node.crnt = CURRENT_POINT;
        maze[current.ln][current.clmn].node.opn_lst = NOT_IN_THE_OPEN_LIST;
        maze[current.ln][current.clmn].node.clsd_lst = IN_THE_CLOSED_LIST;

        search_for_neighboring_cells();
        SFML_redraw_maze();
    }
    is_search = false;
}
//**************************************************************************************************************************************
void find_way(sCoord way)
{
    if(open_list_head == NULL) return;

    SFML_draw_way_to_the_exit_from_maze();
    maze[way.ln][way.clmn].node.path = WAY;

    if((maze[way.ln][way.clmn].prnt_cell.ln == start.ln) && (maze[way.ln][way.clmn].prnt_cell.clmn == start.clmn))
        return;

    find_way(maze[way.ln][way.clmn].prnt_cell);
}
//**************************************************************************************************************************************
void SFML_draw_way_to_the_exit_from_maze()
{
    for(int i = 0; i < MAP_SIZE; ++i)
        for(int j = 0; j < MAP_SIZE; ++j)
        {
            if     (maze[i][j].node.strt    == STARTING_POINT)   rectangle.setFillColor(sf::Color(165,42,42));   // S - start point, brown
            else if(maze[i][j].node.ext     == EXIT_POINT)       rectangle.setFillColor(sf::Color::Cyan);        // E - exit
            else if(maze[i][j].node.path    == WAY)              rectangle.setFillColor(sf::Color::Yellow);      // V - current way to exit
            //else if(maze[i][i].node.crnt    == CURRENT_POINT)    rectangle.setFillColor(sf::Color::Blue);        // C - current point
            //else if(maze[i][j].node.opn_lst == IN_THE_OPEN_LIST) rectangle.setFillColor(sf::Color::Blue);        // O - at the open list, gray
            else if(maze[i][j].node.wall    == 0)                rectangle.setFillColor(sf::Color::Black);       // W - wall
            else if(maze[i][j].node.wall    > 0  && maze[i][j].node.wall <= 10) rectangle.setFillColor(sf::Color(0, 200, 0));   // P - passable section
            else if(maze[i][j].node.wall    > 10 && maze[i][j].node.wall <= 20) rectangle.setFillColor(sf::Color(0, 180, 0));
            else if(maze[i][j].node.wall    > 20 && maze[i][j].node.wall <= 30) rectangle.setFillColor(sf::Color(0, 160, 0));
            else if(maze[i][j].node.wall    > 30 && maze[i][j].node.wall <= 40) rectangle.setFillColor(sf::Color(0, 140, 0));
            else if(maze[i][j].node.wall    > 40 && maze[i][j].node.wall <= 50) rectangle.setFillColor(sf::Color(0, 120, 0));
            else if(maze[i][j].node.wall    > 50 && maze[i][j].node.wall <= 60) rectangle.setFillColor(sf::Color(0, 100, 0));
            else if(maze[i][j].node.wall    > 60 && maze[i][j].node.wall <= 70) rectangle.setFillColor(sf::Color(0, 80, 0));
            else if(maze[i][j].node.wall    > 70 && maze[i][j].node.wall <= 80) rectangle.setFillColor(sf::Color(0, 60, 0));
            else if(maze[i][j].node.wall    > 80 && maze[i][j].node.wall <= 90) rectangle.setFillColor(sf::Color(0, 40, 0));
            else if(maze[i][j].node.wall    > 90 && maze[i][j].node.wall <= 99) rectangle.setFillColor(sf::Color(0, 20, 0));
            rectangle.setPosition(j * TEXTURE_LENGTH, i * TEXTURE_LENGTH);

            window.draw(rectangle);
        }
    SFML_rectangle_abou_draw();
    if(maze[exit_from.ln][exit_from.clmn].node.crnt == CURRENT_POINT)
        window.draw(text_path_is_foun);
    window.draw(text);
    window.display();
}
//**************************************************************************************************************************************
int H_calc(int dis_cal_line, int dis_cal_column)
{
    return (abs(dis_cal_line - exit_from.ln) + abs(dis_cal_column - exit_from.clmn)) * 10;
}
//**************************************************************************************************************************************
int G_calc(int dis_cal_line, int dis_cal_column)
{
    if((dis_cal_line == current.ln) || (dis_cal_column == current.clmn))
         return maze[current.ln][current.clmn].pth_lngth.G + ORTHOGONALLY;
    else return maze[current.ln][current.clmn].pth_lngth.G + DIAGONALLY;
}
//**************************************************************************************************************************************
void Path_length_calc(int dis_cal_line, int dis_cal_column)
{
    maze[dis_cal_line][dis_cal_column].pth_lngth.H = H_calc(dis_cal_line, dis_cal_column);
    maze[dis_cal_line][dis_cal_column].pth_lngth.G = maze[dis_cal_line][dis_cal_column].node.wall + G_calc(dis_cal_line, dis_cal_column);
    maze[dis_cal_line][dis_cal_column].pth_lngth.F = /*maze[dis_cal_line][dis_cal_column].node.wall + */maze[dis_cal_line][dis_cal_column].pth_lngth.G + maze[dis_cal_line][dis_cal_column].pth_lngth.H;
}
//**************************************************************************************************************************************
int location_relative_to_current(int dis_cal_line, int dis_cal_column)
{
    if((dis_cal_line == current.ln) || (dis_cal_column == current.clmn)) return ORTHOGONALLY;
    else return DIAGONALLY;
}
//**************************************************************************************************************************************
void distance_calculation(int dis_cal_line, int dis_cal_column)
{
    if(maze[dis_cal_line][dis_cal_column].node.opn_lst == NOT_IN_THE_OPEN_LIST)
    {
        maze[dis_cal_line][dis_cal_column].node.opn_lst = IN_THE_OPEN_LIST;
        maze[dis_cal_line][dis_cal_column].prnt_cell = current;
        Path_length_calc(dis_cal_line, dis_cal_column);
        open_list_push(&open_list_head, maze[dis_cal_line][dis_cal_column]);
        open_list_head = open_list_sort();
    }
    else if((maze[dis_cal_line][dis_cal_column].node.opn_lst == IN_THE_OPEN_LIST) && (maze[dis_cal_line][dis_cal_column].pth_lngth.G > maze[current.ln][current.clmn].pth_lngth.G + location_relative_to_current(dis_cal_line, dis_cal_column)))
    {
        maze[dis_cal_line][dis_cal_column].prnt_cell = current;
        maze[dis_cal_line][dis_cal_column].pth_lngth.G = G_calc(dis_cal_line, dis_cal_column);
        maze[dis_cal_line][dis_cal_column].pth_lngth.F = maze[dis_cal_line][dis_cal_column].pth_lngth.G + maze[dis_cal_line][dis_cal_column].pth_lngth.H;
        open_list_head = open_list_sort();
    }
}
//**************************************************************************************************************************************
void search_for_neighboring_cells()
{
    if((current.ln == MAP_SIZE - 1) && (current.clmn > 0) && (current.clmn < MAP_SIZE - 1))
    {
        if((maze[current.ln][current.clmn - 1].node.wall > 0) && (maze[current.ln][current.clmn - 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln, current.clmn - 1);
        if((maze[current.ln - 1][current.clmn - 1].node.wall > 0) && (maze[current.ln - 1][current.clmn - 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln - 1, current.clmn - 1);
        if((maze[current.ln - 1][current.clmn].node.wall > 0) && (maze[current.ln - 1][current.clmn].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln - 1, current.clmn);
        if((maze[current.ln - 1][current.clmn + 1].node.wall > 0) && (maze[current.ln - 1][current.clmn + 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln - 1, current.clmn + 1);
        if((maze[current.ln][current.clmn + 1].node.wall > 0) && (maze[current.ln][current.clmn + 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln, current.clmn - 1);
    }
    if((current.ln == 0) && (current.clmn > 0) && (current.clmn < MAP_SIZE - 1))
    {
        if((maze[current.ln][current.clmn - 1].node.wall > 0) && (maze[current.ln][current.clmn - 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln, current.clmn - 1);
        if((maze[current.ln + 1][current.clmn - 1].node.wall > 0) && (maze[current.ln + 1][current.clmn - 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln + 1, current.clmn - 1);
        if((maze[current.ln + 1][current.clmn].node.wall > 0) && (maze[current.ln + 1][current.clmn].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln + 1, current.clmn);
        if((maze[current.ln + 1][current.clmn + 1].node.wall > 0) && (maze[current.ln + 1][current.clmn + 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln + 1, current.clmn + 1);
        if((maze[current.ln][current.clmn + 1].node.wall > 0) && (maze[current.ln][current.clmn + 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln, current.clmn - 1);
    }
    if((current.ln > 0) && (current.ln < MAP_SIZE - 1) && (current.clmn == MAP_SIZE - 1))
    {
        if((maze[current.ln - 1][current.clmn].node.wall > 0) && (maze[current.ln - 1][current.clmn].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln - 1, current.clmn);
        if((maze[current.ln - 1][current.clmn - 1].node.wall > 0) && (maze[current.ln - 1][current.clmn - 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln - 1, current.clmn - 1);
        if((maze[current.ln][current.clmn - 1].node.wall > 0) && (maze[current.ln][current.clmn - 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln, current.clmn - 1);
        if((maze[current.ln + 1][current.clmn - 1].node.wall > 0) && (maze[current.ln + 1][current.clmn - 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln + 1, current.clmn - 1);
        if((maze[current.ln + 1][current.clmn].node.wall > 0) && (maze[current.ln + 1][current.clmn].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln + 1, current.clmn);
    }
    if((current.ln > 0) && (current.ln < MAP_SIZE - 1) && (current.clmn == 0))
    {
        if((maze[current.ln - 1][current.clmn].node.wall > 0) && (maze[current.ln - 1][current.clmn].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln - 1, current.clmn);
        if((maze[current.ln - 1][current.clmn + 1].node.wall > 0) && (maze[current.ln - 1][current.clmn + 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln - 1, current.clmn + 1);
        if((maze[current.ln][current.clmn + 1].node.wall > 0) && (maze[current.ln][current.clmn + 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln, current.clmn + 1);
        if((maze[current.ln + 1][current.clmn + 1].node.wall > 0) && (maze[current.ln + 1][current.clmn + 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln + 1, current.clmn + 1);
        if((maze[current.ln + 1][current.clmn].node.wall > 0) && (maze[current.ln + 1][current.clmn].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln + 1, current.clmn);
    }
    if((current.ln > 0) && (current.ln < MAP_SIZE - 1) && (current.clmn > 0) && (current.clmn < MAP_SIZE - 1))
    {
        if((maze[current.ln - 1][current.clmn - 1].node.wall > 0) && (maze[current.ln - 1][current.clmn - 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln - 1, current.clmn - 1);
        if((maze[current.ln - 1][current.clmn].node.wall > 0) && (maze[current.ln - 1][current.clmn].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln - 1, current.clmn);
        if((maze[current.ln - 1][current.clmn + 1].node.wall > 0) && (maze[current.ln - 1][current.clmn + 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln - 1, current.clmn + 1);
        if((maze[current.ln][current.clmn - 1].node.wall > 0) && (maze[current.ln][current.clmn - 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln, current.clmn - 1);
        if((maze[current.ln][current.clmn + 1].node.wall > 0) && (maze[current.ln][current.clmn + 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln, current.clmn + 1);
        if((maze[current.ln + 1][current.clmn - 1].node.wall > 0) && (maze[current.ln + 1][current.clmn - 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln + 1, current.clmn - 1);
        if((maze[current.ln + 1][current.clmn].node.wall > 0) && (maze[current.ln + 1][current.clmn].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln + 1, current.clmn);
        if((maze[current.ln + 1][current.clmn + 1].node.wall > 0) && (maze[current.ln + 1][current.clmn + 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln + 1, current.clmn + 1);
    }
    if((current.ln == 0) && (current.clmn == 0))
    {
        if((maze[current.ln][current.clmn + 1].node.wall > 0) && (maze[current.ln][current.clmn + 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln, current.clmn + 1);
        if((maze[current.ln + 1][current.clmn].node.wall > 0) && (maze[current.ln + 1][current.clmn].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln + 1, current.clmn);
        if((maze[current.ln + 1][current.clmn + 1].node.wall > 0) && (maze[current.ln + 1][current.clmn + 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln + 1, current.clmn + 1);
    }
    if((current.ln == 0) && (current.clmn == MAP_SIZE -1))
    {
        if((maze[current.ln][current.clmn - 1].node.wall > 0) && (maze[current.ln][current.clmn - 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln, current.clmn - 1);
        if((maze[current.ln + 1][current.clmn - 1].node.wall > 0) && (maze[current.ln + 1][current.clmn - 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln + 1, current.clmn - 1);
        if((maze[current.ln - 1][current.clmn].node.wall > 0) && (maze[current.ln - 1][current.clmn].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln - 1, current.clmn);
    }
    if((current.ln == MAP_SIZE -1) && (current.clmn == 0))
    {
        if((maze[current.ln - 1][current.clmn].node.wall > 0) && (maze[current.ln - 1][current.clmn].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln - 1, current.clmn);
        if((maze[current.ln - 1][current.clmn + 1].node.wall > 0) && (maze[current.ln - 1][current.clmn + 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln - 1, current.clmn + 1);
        if((maze[current.ln][current.clmn + 1].node.wall > 0) && (maze[current.ln][current.clmn + 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln, current.clmn + 1);
    }
    if((current.ln == MAP_SIZE -1) && (current.clmn == MAP_SIZE -1))
    {
        if((maze[current.ln - 1][current.clmn - 1].node.wall > 0) && (maze[current.ln - 1][current.clmn - 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln - 1, current.clmn - 1);
        if((maze[current.ln - 1][current.clmn].node.wall > 0) && (maze[current.ln - 1][current.clmn].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln - 1, current.clmn);
        if((maze[current.ln][current.clmn - 1].node.wall > 0) && (maze[current.ln][current.clmn - 1].node.clsd_lst == NOT_IN_THE_CLOSED_LIST))
            distance_calculation(current.ln, current.clmn - 1);
    }
}
//**************************************************************************************************************************************
void SFML_redraw_maze()
{
    window.clear(sf::Color(200,150,0));

    for(int i = 0; i < MAP_SIZE; ++i)
        for(int j = 0; j < MAP_SIZE; ++j)
        {
            if     (maze[i][j].node.strt    == STARTING_POINT)   rectangle.setFillColor(sf::Color(165,42,42));   // S - start point, brown
            //else if(maze[i][j].node.trgt    == TARGET_POINT)     rectangle.setFillColor(sf::Color::Green);       // T - target point, purple
            else if(maze[i][j].node.ext     == EXIT_POINT)       rectangle.setFillColor(sf::Color::Cyan);        // E - exit
            else if(maze[i][j].node.path    == WAY)              rectangle.setFillColor(sf::Color::Yellow);      // V - current way to exit
            //else if(maze[i][i].node.crnt    == CURRENT_POINT)    rectangle.setFillColor(sf::Color::Magenta);        // C - current point
            else if(maze[i][j].node.opn_lst == IN_THE_OPEN_LIST) rectangle.setFillColor(sf::Color::Blue);        // O - at the open list, gray
            else if(maze[i][j].node.wall    == 0)                rectangle.setFillColor(sf::Color::Black);       // W - wall
            else if(maze[i][j].node.wall > 0  && maze[i][j].node.wall <= 10) rectangle.setFillColor(sf::Color(0, 200, 0));   // passable section
            else if(maze[i][j].node.wall > 10 && maze[i][j].node.wall <= 20) rectangle.setFillColor(sf::Color(0, 180, 0));
            else if(maze[i][j].node.wall > 20 && maze[i][j].node.wall <= 30) rectangle.setFillColor(sf::Color(0, 160, 0));
            else if(maze[i][j].node.wall > 30 && maze[i][j].node.wall <= 40) rectangle.setFillColor(sf::Color(0, 140, 0));
            else if(maze[i][j].node.wall > 40 && maze[i][j].node.wall <= 50) rectangle.setFillColor(sf::Color(0, 120, 0));
            else if(maze[i][j].node.wall > 50 && maze[i][j].node.wall <= 60) rectangle.setFillColor(sf::Color(0, 100, 0));
            else if(maze[i][j].node.wall > 60 && maze[i][j].node.wall <= 70) rectangle.setFillColor(sf::Color(0, 80, 0));
            else if(maze[i][j].node.wall > 70 && maze[i][j].node.wall <= 80) rectangle.setFillColor(sf::Color(0, 60, 0));
            else if(maze[i][j].node.wall > 80 && maze[i][j].node.wall <= 90) rectangle.setFillColor(sf::Color(0, 40, 0));
            else if(maze[i][j].node.wall > 90 && maze[i][j].node.wall <= 99) rectangle.setFillColor(sf::Color(0, 20, 0));
            rectangle.setPosition(j * TEXTURE_LENGTH, i * TEXTURE_LENGTH);
            //rectangle.setOutlineThickness(1);
            //rectangle.setOutlineColor(sf::Color::White);

            window.draw(rectangle);
        }
    SFML_rectangle_abou_draw();

    if(!mode && !from_file) window.draw(text_mode_map);
    else if (mode && !from_file) window.draw(text_mode_maze);
    else if (!mode && from_file) window.draw(text_mode_from_file);

    if(show_info == true) window.draw(sprite_scroll);

    if(is_search && !cant_found_path)
        window.draw(sprite);
    if(cant_found_path)
        window.draw(text_no_path);
    if(maze[exit_from.ln][exit_from.clmn].node.crnt == CURRENT_POINT)
        window.draw(text_path_is_foun);
    window.draw(text);
    window.draw(text_scale_of_path);
    window.draw(text_passable_areas);
    window.draw(text_impassable_areas);
    window.draw(text_key_assignment);
    window.draw(text_bind_key);
    window.draw(text_bind_key_info);
    window.display();
}
//**************************************************************************************************************************************
void SFML_rectangle_abou_init()
{
    rectangle_abou_200.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 10, -35);
    rectangle_abou_180.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 10, -35 - TEXTURE_LENGTH_FOR_INFO / 5);
    rectangle_abou_160.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 10, -35 - TEXTURE_LENGTH_FOR_INFO / 5 * 2);
    rectangle_abou_140.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 10, -35 - TEXTURE_LENGTH_FOR_INFO / 5 * 3);
    rectangle_abou_120.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 10, -35 - TEXTURE_LENGTH_FOR_INFO / 5 * 4);
    rectangle_abou_100.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 10, -35 - TEXTURE_LENGTH_FOR_INFO / 5 * 5);
    rectangle_abou_80.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 10, -35 - TEXTURE_LENGTH_FOR_INFO / 5 * 6);
    rectangle_abou_60.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 10, -35 - TEXTURE_LENGTH_FOR_INFO / 5 * 7);
    rectangle_abou_40.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 10, -35 - TEXTURE_LENGTH_FOR_INFO / 5 * 8);
    rectangle_abou_20.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 10, -35 - TEXTURE_LENGTH_FOR_INFO / 5 * 9);
    rectangle_abou_WALL.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 10, -105);
    rectangle_abou_200.setFillColor(sf::Color(0, 200, 0));
    rectangle_abou_180.setFillColor(sf::Color(0, 180, 0));
    rectangle_abou_160.setFillColor(sf::Color(0, 160, 0));
    rectangle_abou_140.setFillColor(sf::Color(0, 140, 0));
    rectangle_abou_120.setFillColor(sf::Color(0, 120, 0));
    rectangle_abou_100.setFillColor(sf::Color(0, 100, 0));
    rectangle_abou_80.setFillColor(sf::Color(0, 80, 0));
    rectangle_abou_60.setFillColor(sf::Color(0, 60, 0));
    rectangle_abou_40.setFillColor(sf::Color(0, 40, 0));
    rectangle_abou_20.setFillColor(sf::Color(0, 20, 0));
    rectangle_abou_WALL.setFillColor(sf::Color::Black);
}

void SFML_rectangle_abou_draw()
{
    window.draw(rectangle_abou_200);
    window.draw(rectangle_abou_180);
    window.draw(rectangle_abou_160);
    window.draw(rectangle_abou_140);
    window.draw(rectangle_abou_120);
    window.draw(rectangle_abou_100);
    window.draw(rectangle_abou_80);
    window.draw(rectangle_abou_60);
    window.draw(rectangle_abou_40);
    window.draw(rectangle_abou_20);
    window.draw(rectangle_abou_WALL);
}
//**************************************************************************************************************************************
void SFML_start()
{
    window.setVerticalSyncEnabled(true);

    //create_maze();
    //init_map();

    SFML_rectangle_abou_init();

    font.loadFromFile("consola.ttf");

    texture.loadFromFile("D:/GoogleDrive/Kursovoi_Proekt_1/aStar_proekt_stack_on_list/search1.png");
    sprite.setTexture(texture);
    sprite.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 175, -45);

    scroll.loadFromFile("D:/GoogleDrive/Kursovoi_Proekt_1/aStar_proekt_stack_on_list/scroll2.png");
    sprite_scroll.setTexture(scroll);
    sprite_scroll.setOrigin(-65, -75);

    text_mode_maze.setFont(font);
    text_mode_maze.setFillColor(sf::Color::Black);
    text_mode_maze.setCharacterSize(28);
    text_mode_maze.setString("MODE: MAZE");
    text_mode_maze.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 20, -337);

    text_mode_map.setFont(font);
    text_mode_map.setFillColor(sf::Color::Black);
    text_mode_map.setCharacterSize(28);
    text_mode_map.setString("MODE: MAP");
    text_mode_map.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 20, -337);

    text_mode_from_file.setFont(font);
    text_mode_from_file.setFillColor(sf::Color::Black);
    text_mode_from_file.setCharacterSize(28);
    text_mode_from_file.setString("MODE: FROM FILE");
    text_mode_from_file.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 20, -337);

    text_no_path.setFont(font);
    text_no_path.setFillColor(sf::Color::Red);
    text_no_path.setCharacterSize(20);
    text_no_path.setString("!!! IS NO PATH FOUND !!!\n"
                           "press  r key for restart\n"
                           "    or ESC for exit");
    text_no_path.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 20, -372);

    text_path_is_foun.setFont(font);
    text_path_is_foun.setFillColor(sf::Color::Green);
    text_path_is_foun.setCharacterSize(35);
    text_path_is_foun.setString("PATH IS FOUND\n");
    text_path_is_foun.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 8, -367);

    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(20);
    text.setString("INFO about map");
    text.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 20, -8);
    text.setStyle(sf::Text::Bold);

    text_scale_of_path.setFont(font);
    text_scale_of_path.setFillColor(sf::Color::Black);
    text_scale_of_path.setCharacterSize(9);
    text_scale_of_path.setString(" 1\n\n50\n\n99");
    text_scale_of_path.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 61, -32);

    text_passable_areas.setFont(font);
    text_passable_areas.setFillColor(sf::Color::Black);
    text_passable_areas.setCharacterSize(17);
    text_passable_areas.setString("passable\n areas");
    text_passable_areas.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 80, -33);
    text_passable_areas.setStyle(sf::Text::Italic);

    text_impassable_areas.setFont(font);
    text_impassable_areas.setFillColor(sf::Color::Black);
    text_impassable_areas.setCharacterSize(17);
    text_impassable_areas.setString("impassable\n  areas");
    text_impassable_areas.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 75, -95);
    text_impassable_areas.setStyle(sf::Text::Italic);

    text_key_assignment.setFont(font);
    text_key_assignment.setFillColor(sf::Color::Black);
    text_key_assignment.setCharacterSize(20);
    text_key_assignment.setString("Key assignment:");
    text_key_assignment.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 20, -140);
    text_key_assignment.setStyle(sf::Text::Bold);

    text_bind_key.setFont(font);
    text_bind_key.setFillColor(sf::Color::Black);
    text_bind_key.setCharacterSize(14);
    text_bind_key.setString("LAlt   + MouseMoved\n"
                            "LCtrl  + MouseMoved\n"
                            "LShift + MouseMoved\n"
                            "LeftClick\n"
                            "RightClick\n"
                            "Space\n"
                            "m\n"
                            "i\n"
                            "r\n"
                            "ESC\n"
                            "F1");
    text_bind_key.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 10, -165);
    text_bind_key.setStyle(sf::Text::Underlined);

    text_bind_key_info.setFont(font);
    text_bind_key_info.setFillColor(sf::Color::Black);
    text_bind_key_info.setCharacterSize(14);
    text_bind_key_info.setString("                    - improve\n"
                                 "                    - aggravate\n"
                                 "                    - make wall\n"
                                 "           - make EXIT  Point\n"
                                 "           - make START Point\n"
                                 "      - starting the search\n"
                                 "  - change MODE\n"
                                 "  - reinit maze\n"
                                 "  - restart\n"
                                 "    - exit\n"
                                 "   - more info");
    text_bind_key_info.setOrigin(-(MAP_SIZE * TEXTURE_LENGTH) - 10, -165);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) window.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) show_info = true;
            else show_info = false;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.type == sf::Event::MouseMoved) // срабатывает при перемещении мышм внутри окна
            {
                if(mode == false)
                {
                    for(int i = -2; i < 3; ++i)
                        for(int j = -2; j < 3; ++j)
                            if(maze[event.mouseMove.y / TEXTURE_LENGTH + i][event.mouseMove.x / TEXTURE_LENGTH + j].node.wall <= 1)
                                maze[event.mouseMove.y / TEXTURE_LENGTH + i][event.mouseMove.x / TEXTURE_LENGTH + j].node.wall = 1;
                            else maze[event.mouseMove.y / TEXTURE_LENGTH + i][event.mouseMove.x / TEXTURE_LENGTH + j].node.wall -= 10;
                }
                else
                {
                    if(maze[event.mouseMove.y / TEXTURE_LENGTH][event.mouseMove.x / TEXTURE_LENGTH].node.wall <= 1)
                        maze[event.mouseMove.y / TEXTURE_LENGTH][event.mouseMove.x / TEXTURE_LENGTH].node.wall = 1;
                    else maze[event.mouseMove.y / TEXTURE_LENGTH][event.mouseMove.x / TEXTURE_LENGTH].node.wall -= 10;
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && event.type == sf::Event::MouseMoved)
            {
                if(mode == false)
                {
                    for(int i = -2; i < 3; ++i)
                        for(int j = -2; j < 3; ++j)
                            if(maze[event.mouseMove.y / TEXTURE_LENGTH + i][event.mouseMove.x / TEXTURE_LENGTH + j].node.wall >= 99)
                                maze[event.mouseMove.y / TEXTURE_LENGTH + i][event.mouseMove.x / TEXTURE_LENGTH + j].node.wall = 99;
                            else maze[event.mouseMove.y / TEXTURE_LENGTH + i][event.mouseMove.x / TEXTURE_LENGTH + j].node.wall += 10;
                }
                else
                {
                    if(maze[event.mouseMove.y / TEXTURE_LENGTH][event.mouseMove.x / TEXTURE_LENGTH].node.wall >= 99)
                        maze[event.mouseMove.y / TEXTURE_LENGTH][event.mouseMove.x / TEXTURE_LENGTH].node.wall = 99;
                    else maze[event.mouseMove.y / TEXTURE_LENGTH][event.mouseMove.x / TEXTURE_LENGTH].node.wall += 10;
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && event.type == sf::Event::MouseMoved)
            {
                if(mode == false)
                    for(int i = -2; i < 3; ++i)
                        for(int j = -2; j < 3; ++j)
                            maze[event.mouseMove.y / TEXTURE_LENGTH + i][event.mouseMove.x / TEXTURE_LENGTH + j].node.wall = 0;
                else maze[event.mouseMove.y / TEXTURE_LENGTH][event.mouseMove.x / TEXTURE_LENGTH].node.wall = 0;
            }
            if(event.type == sf::Event::MouseButtonPressed)
            {
                if(event.mouseButton.button == sf::Mouse::Right)
                {
                    for(int i = 0; i < MAP_SIZE; ++i)
                        for(int j = 0; j < MAP_SIZE; ++j)
                            maze[i][j].node.strt = NOT_A_STARTING_POINT;
                    open_list_head = NULL;
                    start = {event.mouseButton.y / TEXTURE_LENGTH, event.mouseButton.x / TEXTURE_LENGTH};
                    maze[event.mouseButton.y / TEXTURE_LENGTH][event.mouseButton.x / TEXTURE_LENGTH].node.strt = STARTING_POINT;
                    maze[event.mouseButton.y / TEXTURE_LENGTH][event.mouseButton.x / TEXTURE_LENGTH].prnt_cell = maze[event.mouseButton.y / TEXTURE_LENGTH][event.mouseButton.x / TEXTURE_LENGTH].node.node_coord;
                    open_list_push(&open_list_head, maze[event.mouseButton.y / TEXTURE_LENGTH][event.mouseButton.x / TEXTURE_LENGTH]);
                }
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    for(int i = 0; i < MAP_SIZE; ++i)
                        for(int j = 0; j < MAP_SIZE; ++j)
                            maze[i][j].node.ext = NOT_AN_EXIT_POINT;
                    exit_from = {event.mouseButton.y / TEXTURE_LENGTH, event.mouseButton.x / TEXTURE_LENGTH};
                    maze[event.mouseButton.y / TEXTURE_LENGTH][event.mouseButton.x / TEXTURE_LENGTH].node.ext = EXIT_POINT;
                    break;
                }
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                shortest_path_search();
                change_node_status();
                find_way(exit_from);
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) reinit_maze();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I)
            {
                if(mode == false && from_file == false) init_map();
                else if(mode == true && from_file == false) create_maze();
                else if(mode == false && from_file == true) init_maze_from_file();
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M)
            {
                if(mode == false && from_file == false) {mode = true; from_file = false; reinit_maze();}
                else if(mode == true && from_file == false) {mode = false; from_file = true; reinit_maze();}
                else if(mode == false && from_file == true) {mode = false; from_file = false; reinit_maze();}
            }
            //if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F) init_maze_from_file();
        }
        SFML_redraw_maze();
    }
}
//**************************************************************************************************************************************
void init_maze_from_file()
{
    FILE *map = fopen("D:\\GoogleDrive\\Kursovoi_Proekt_1\\aStar_proekt_stack_on_list\\map1.txt", "r");
    //FILE *map = fopen("D:\\GoogleDrive\\Kursovoi_Proekt_1\\aStar_proekt_stack_on_list\\map2.txt", "r");
    //FILE *map = fopen("D:\\GoogleDrive\\Kursovoi_Proekt_1\\aStar_proekt_stack_on_list\\map3.txt", "r");
    //FILE *map = fopen("D:\\GoogleDrive\\Kursovoi_Proekt_1\\aStar_proekt_stack_on_list\\map4.txt", "r");

    if(!map)
        printf("Error!\n");
    else
    {
        for(int i = 0; i < MAP_SIZE; ++i)
            for(int j = 0; j < MAP_SIZE; ++j)
            {
                fscanf(map, "%i", &maze[i][j].node.wall);
                maze[i][j].node.path     = NOT_A_WAY;
                maze[i][j].node.visit    = UNVISITED;
                maze[i][j].node.clsd_lst = NOT_IN_THE_CLOSED_LIST;
                maze[i][j].node.opn_lst  = NOT_IN_THE_OPEN_LIST;
                maze[i][j].node.ext      = NOT_AN_EXIT_POINT;
                maze[i][j].node.crnt     = NOT_CURRENT_POINT;
                maze[i][j].node.strt     = NOT_A_STARTING_POINT;
                maze[i][j].pth_lngth.G   = 0;
                maze[i][j].pth_lngth.H   = 0;
                maze[i][j].pth_lngth.F   = 0;
                maze[i][j].node.node_coord.ln   = i;
                maze[i][j].node.node_coord.clmn = j;
            }
        fclose(map);
    }
}
//**************************************************************************************************************************************
void init_map()
{
    srand(time(0));

    //FILE *map = fopen("D:\\GoogleDrive\\Kursovoi_Proekt_1\\aStar_proekt_stack_on_list\\map1.txt", "r");
    //FILE *map = fopen("D:\\GoogleDrive\\Kursovoi_Proekt_1\\aStar_proekt_stack_on_list\\map2.txt", "r");
    //FILE *map = fopen("D:\\GoogleDrive\\Kursovoi_Proekt_1\\aStar_proekt_stack_on_list\\map3.txt", "r");
    //FILE *map = fopen("D:\\GoogleDrive\\Kursovoi_Proekt_1\\aStar_proekt_stack_on_list\\map4.txt", "r");

 /*   if(!map)
        printf("Error!\n");
    else
    {*/
        for(int i = 0; i < MAP_SIZE; ++i)
            for(int j = 0; j < MAP_SIZE; ++j)
            {
                //fscanf(map, "%i", &maze[i][j].node.wall);
                maze[i][j].node.wall = rand() % 98;
                maze[i][j].node.path     = NOT_A_WAY;
                maze[i][j].node.visit    = UNVISITED;
                maze[i][j].node.clsd_lst = NOT_IN_THE_CLOSED_LIST;
                maze[i][j].node.opn_lst  = NOT_IN_THE_OPEN_LIST;
                maze[i][j].node.ext      = NOT_AN_EXIT_POINT;
                maze[i][j].node.crnt     = NOT_CURRENT_POINT;
                maze[i][j].node.strt     = NOT_A_STARTING_POINT;
                maze[i][j].pth_lngth.G   = 0;
                maze[i][j].pth_lngth.H   = 0;
                maze[i][j].pth_lngth.F   = 0;
                maze[i][j].node.node_coord.ln   = i;
                maze[i][j].node.node_coord.clmn = j;
            }
     /*   fclose(map);
        for(int i = 0; i < MAP_SIZE; ++i)
            for(int j = 0; j < MAP_SIZE; ++j)
                if(maze[i][j].node.wall > 0)
                    maze[i][j].node.wall = rand() % 98;
    }*/
}
//**************************************************************************************************************************************
void change_node_status()
{
    for(int i = 0; i < MAP_SIZE; ++i)
        for(int j = 0; j < MAP_SIZE; ++j)
            maze[i][j].node.opn_lst  = NOT_IN_THE_OPEN_LIST;
}
//**************************************************************************************************************************************
void reinit_maze()
{
    cant_found_path = false;

    for(int i = 0; i < MAP_SIZE; ++i)
        for(int j = 0; j < MAP_SIZE; ++j)
        {
            maze[i][j].node.path     = NOT_A_WAY;
            maze[i][j].node.visit    = UNVISITED;
            maze[i][j].node.clsd_lst = NOT_IN_THE_CLOSED_LIST;
            maze[i][j].node.opn_lst  = NOT_IN_THE_OPEN_LIST;
            maze[i][j].node.ext      = NOT_AN_EXIT_POINT;
            maze[i][j].node.crnt     = NOT_CURRENT_POINT;
            maze[i][j].node.strt     = NOT_A_STARTING_POINT;
        }
}
//**************************************************************************************************************************************
void open_list_push(sOPENlist **open_list_head, sCell data)
{
    sOPENlist *open_list_tmp = (sOPENlist*)malloc(sizeof(sOPENlist));

    if (open_list_tmp == NULL)
        exit(STACK_OVERFLOW);
    open_list_tmp->value = data;
    open_list_tmp->next = *open_list_head;
    *open_list_head = open_list_tmp;
}
//**************************************************************************************************************************************
sOPENlist *open_list_pop(sOPENlist **open_list_head)
{
    sOPENlist *open_list_out;
/*
    if ((*open_list_head) == NULL)
    {
       // printf("\n.------------------------------------------------------."
       //        "\n| The path between the specified points does not exist |"
       //        "\n.------------------------------------------------------.\n");
        return open_list_out;//exit(STACK_UNDERFLOW);
    }
    else
    {*/
        open_list_out  = *open_list_head;
        *open_list_head = (*open_list_head)->next;

        return open_list_out;
    //}
}
//**************************************************************************************************************************************
sOPENlist *open_list_sort()
{
    sOPENlist *temp, *out = NULL, *curr, *previous;
    while (open_list_head != NULL)
    {
        temp = open_list_head;
        open_list_head = open_list_head->next;
        for(curr = out, previous = NULL; curr != NULL && temp->value.pth_lngth.F > curr->value.pth_lngth.F; previous = curr, curr = curr->next);
            if(previous == NULL)
            {
                temp->next = out;
                out = temp;
            }
            else
            {
                temp->next = curr;
                previous->next = temp;
            }
    }
    return out;
}
//***************************************************************************************************************************************
//************************** MAZE GENERATOR ************************** MAZE GENERATOR ************************** MAZE GENERATOR *********
//***** MAZE GENERATOR ************************** MAZE GENERATOR ************************** MAZE GENERATOR ******************************
//************************** MAZE GENERATOR ************************** MAZE GENERATOR ************************** MAZE GENERATOR *********
//***************************************************************************************************************************************
/*
void show_maze()
{
    system("cls");

    for(int i = 0; i < MAP_SIZE; ++i)
    {
        for(int j = 0; j < MAP_SIZE; ++j)
            if(maze[i][j].node.wall == 0)
                printf("\033[41;31m%2i\033[0m", maze[i][j].node.wall);
            else
                printf("\033[30m%2i\033[0m", maze[i][j].node.wall);
        printf("\n");
    }
}*/
//*************************************************************************************
void push_stack_for_maze_creation(pStack **stack_for_maze_creation, sCell data)
{
    pStack *tmp = (pStack*) malloc(sizeof(pStack));

    if (tmp == NULL)
        exit(STACK_OVERFLOW);
    tmp->value = data;
    tmp->next = (*stack_for_maze_creation);
    (*stack_for_maze_creation) = tmp;
}
//*************************************************************************************
pStack* pop_stack_for_maze_creation(pStack **stack_for_maze_creation)
{
    pStack *out;
    if ((*stack_for_maze_creation) == NULL)
        exit(STACK_UNDERFLOW);

    out = *stack_for_maze_creation;
    *stack_for_maze_creation = (*stack_for_maze_creation)->next;

    return out;
}
//*************************************************************************************
sCoord next_cell_coord(sCoord current_cell)
{
    int tmp = rand() % 4;

    switch (tmp)
    {
    case 0: start0 :
              if (((current_cell.ln + 2) < MAP_SIZE) && (maze[current_cell.ln + 2][current_cell.clmn].node.visit == UNVISITED))
                    return maze[current_cell.ln + 2][current_cell.clmn].node.node_coord;
              goto start1;
              break;
    case 1: start1 :
              if (((current_cell.clmn + 2) < MAP_SIZE) && (maze[current_cell.ln][current_cell.clmn + 2].node.visit == UNVISITED))
                    return maze[current_cell.ln][current_cell.clmn + 2].node.node_coord;
              goto start2;
              break;
    case 2: start2 :
              if (((current_cell.ln - 2) > 0) && (maze[current_cell.ln - 2][current_cell.clmn].node.visit == UNVISITED))
                    return maze[current_cell.ln - 2][current_cell.clmn].node.node_coord;
              goto start3;
              break;
    case 3: start3 :
              if (((current_cell.clmn - 2) > 0) && (maze[current_cell.ln][current_cell.clmn - 2].node.visit == UNVISITED))
                    return maze[current_cell.ln][current_cell.clmn - 2].node.node_coord;
              goto start0;
              break;
    }
}
//*************************************************************************************
int have_unvisited_neighbors(sCoord current_cell)
{
    int count_unvis_neighbours = 0;

    if (((current_cell.ln + 2)   < MAP_SIZE) && (maze[current_cell.ln + 2][current_cell.clmn].node.visit == UNVISITED)) count_unvis_neighbours++;
    if (((current_cell.clmn + 2) < MAP_SIZE) && (maze[current_cell.ln][current_cell.clmn + 2].node.visit == UNVISITED)) count_unvis_neighbours++;
    if (((current_cell.ln - 2)   > 0) && (maze[current_cell.ln - 2][current_cell.clmn].node.visit        == UNVISITED)) count_unvis_neighbours++;
    if (((current_cell.clmn - 2) > 0) && (maze[current_cell.ln][current_cell.clmn - 2].node.visit        == UNVISITED)) count_unvis_neighbours++;

    return count_unvis_neighbours;
}
//*************************************************************************************
int unvis_neighbours_in_cell()
{
    int count = 0;

    for(int i = 1; i < MAP_SIZE; i += 2)
        for(int j = 1 ; j < MAP_SIZE; j += 2)
            if(maze[i][j].node.visit == UNVISITED) count++;
    return count;
}
//*************************************************************************************
void create_maze()
{
    srand(time(NULL));

    for(int i = 0; i < MAP_SIZE; ++i)
        for(int j = 0; j < MAP_SIZE; ++j)
        {
            maze[i][j].node.visit = UNVISITED;
            maze[i][j].node.ext   = NOT_AN_EXIT_POINT;
            maze[i][j].node.strt  = NOT_A_STARTING_POINT;
            maze[i][j].node.node_coord.ln      = i;
            maze[i][j].node.node_coord.clmn    = j;
            if (((i % 2 != 0) && (j % 2 != 0)) && ((i < MAP_SIZE - 1) && (j < MAP_SIZE - 1)))
                 maze[i][j].node.wall = 1;
            else maze[i][j].node.wall = 0;
        }

    sCoord current_cell = {1, 1};
    sCoord next_cell;
    sCoord wall;

    while(unvis_neighbours_in_cell() > 0)
    {
        int count_unvis_neib = have_unvisited_neighbors (current_cell);

        if(count_unvis_neib != 0)
        {
            maze[current_cell.ln][current_cell.clmn].node.visit = VISITED;

            push_stack_for_maze_creation(&stack_for_maze_creation, maze[current_cell.ln][current_cell.clmn]);

            next_cell = next_cell_coord (current_cell);

            wall.ln = (current_cell.ln + next_cell.ln) / 2;
            wall.clmn = (current_cell.clmn + next_cell.clmn) / 2;
            maze[wall.ln][wall.clmn].node.wall  = 1;
            maze[wall.ln][wall.clmn].node.visit = VISITED;

            current_cell = next_cell;

            maze[wall.ln][wall.clmn].node.wall = 1;
            maze[current_cell.ln][current_cell.clmn].node.visit = VISITED;
        }
        else
            current_cell = pop_stack_for_maze_creation(&stack_for_maze_creation)->value.node.node_coord;
    }
    smash_a_random_wall();
    //show_maze();
}
void smash_a_random_wall()
{
    for(int i = 1; i < MAP_SIZE - 1; ++i)
        for(int j = 1; j < MAP_SIZE - 1; ++j)
            if(maze[i][j].node.wall == 0 && maze[i - 1][j].node.wall == 0 && maze[i + 1][j].node.wall == 0 && maze[i][j - 1].node.wall > 0 && maze[i][j + 1].node.wall > 0)
                {maze[i][j].node.wall = 1; ++j; ++i;}
            else if(maze[i][j].node.wall == 0 && maze[i - 1][j].node.wall > 0 && maze[i + 1][j].node.wall > 0 && maze[i][j - 1].node.wall == 0 && maze[i][j + 1].node.wall == 0)
                {maze[i][j].node.wall = 1; ++j; ++i;}
}
