#include "global_variables.h"
#include "functions.h"

sCoord get_target()
{
    maze[target_point.ln][target_point.clmn].node.trgt = TARGET_POINT;
    print_maze();

    int key = 0;

    while (key != ENTER)
    {
        key = getch();

        if(key == UP)
        {
            if((target_point.ln) > 0)
            {
                maze[target_point.ln][target_point.clmn].node.trgt = NOT_A_TARGET_POINT;
                target_point.ln--;
                maze[target_point.ln][target_point.clmn].node.trgt = TARGET_POINT;
            }
        }
        if(key == RIGHT)
        {
            if((target_point.clmn) < MAP_SIZE - 1)
            {
                maze[target_point.ln][target_point.clmn].node.trgt = NOT_A_TARGET_POINT;
                target_point.clmn++;
                maze[target_point.ln][target_point.clmn].node.trgt = TARGET_POINT;
            }
        }
        if(key == DOWN)
        {
            if((target_point.ln) < MAP_SIZE - 1)
            {
                maze[target_point.ln][target_point.clmn].node.trgt = NOT_A_TARGET_POINT;
                target_point.ln++;
                maze[target_point.ln][target_point.clmn].node.trgt = TARGET_POINT;
            }
        }
        if(key == LEFT)
        {
            if((target_point.clmn) > 0)
            {
                maze[target_point.ln][target_point.clmn].node.trgt = NOT_A_TARGET_POINT;
                target_point.clmn--;
                maze[target_point.ln][target_point.clmn].node.trgt = TARGET_POINT;
            }
        }
        print_maze();
        maze[target_point.ln][target_point.clmn].node.trgt = NOT_A_TARGET_POINT;
    }
    return target_point;
}
