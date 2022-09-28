// limit assumption
#define MAX_PLAN_SIZE 1000

#include <iostream>
#include <stdio.h>
#include <queue>

using namespace std;

// defined here to avoid stack warning
char room[MAX_PLAN_SIZE][MAX_PLAN_SIZE];

int main()
{   
    // read input
    FILE* fp_in;
    fopen_s(&fp_in, "in.txt", "r");
    if (fp_in == NULL)
    {
        printf("Input data not found");
        return -1;
    }

    char buff[MAX_PLAN_SIZE];
    int size_h = 0;
    while (fgets(buff, MAX_PLAN_SIZE, fp_in)) {
        strcpy_s(room[size_h], buff);
        size_h++;
        if (size_h >= MAX_PLAN_SIZE)
        {
			printf("Input data out of limit");
			return -1;
        }
    }
    fclose(fp_in);

    // mark the doors
    // '#' - wall, with two walls on NS or EW side - door
    for (int r = 0; r < size_h; r++)
    {
        int c = 0;
        while (room[r][c] != 0) 
        {
            if (room[r][c] == ' ')
            {
                if (c > 0 && room[r][c - 1] == '#' && room[r][c + 1] == '#' || // EW
                    r > 0 && r < size_h - 1 && room[r - 1][c] == '#' && room[r + 1][c] == '#') // NS
                {
                    // door
                    room[r][c] = 'd';
                }
            }
            c++;
        }
    }

    // find rooms with bfs
    int room_cnt = 0;
	for (int r = 0; r < size_h; r++)
	{
		int c = 0;
		while (room[r][c] != 0)
		{
			if (room[r][c] == ' ') // not visited room cell
			{
                // new room
                room_cnt ++;
                char mark = room_cnt + 0x30; // mark using '1', '2'
                room[r][c] = mark;

                // BFS
				queue<int> que;
				que.push(r * MAX_PLAN_SIZE + c);
                while (!que.empty())
                {
					int v = que.front();
					que.pop();

                    int cur_r = v / MAX_PLAN_SIZE, cur_c = v % MAX_PLAN_SIZE;

                    int dr[] = { -1, 0, 1, 0 }, dc[] = { 0, 1, 0, -1 };
                    for (int d = 0; d < 4; d++)
                    {
                        int nr = cur_r + dr[d], nc = cur_c + dc[d]; // neighbour
                        if(nr < 0 || nr >= MAX_PLAN_SIZE) continue;
                        if(nc < 0 || nc >= MAX_PLAN_SIZE) continue;
                        if (room[nr][nc] == ' ')
                        {
                            room[nr][nc] = mark;
                            que.push(nr * MAX_PLAN_SIZE + nc);
                        }
                    }
                }
			}
			c++;
		}
	}

    // output
    for (int r = 0; r < size_h; r++)
    {
        int c = 0;
        while (room[r][c] != 0)
        {
            if (room[r][c] == '#')
            {
                printf("\x1B[49m#");
            }
			else if (room[r][c] == 'd')
			{
                printf("\x1B[49m ");
			}
            else {
                int d = room[r][c] - 0x30;
                char color_s[32];
                sprintf_s(color_s, "\x1B[4%dm ", d % 8);
                printf(color_s);
            }
            c++;
        }
        printf("\n");
    }
        

    return 0;
}
