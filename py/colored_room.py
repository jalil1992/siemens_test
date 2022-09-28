MAX_PLAN_SIZE = 1000
MARK_WALL = -2
MARK_DOOR = -1
MARK_ROOM = 0

room = []

# input
with open('in.txt') as file:
    for line in file:
        room.append([])
        for x in line.strip():
            if x == '#':
                room[-1].append(MARK_WALL) # wall
            else:
                room[-1].append(MARK_ROOM) # room


# mark the doors
# with two walls on NS or EW side - door
for r, row in enumerate(room):
    for c, x in enumerate(row):
        if x == MARK_ROOM:
            if c > 0 and c < len(row) and room[r][c - 1] == MARK_WALL and room[r][c + 1] == MARK_WALL: # EW
                room[r][c] = MARK_DOOR
            elif r > 0 and r < len(room) - 1 and room[r - 1][c] == MARK_WALL and room[r + 1][c] == MARK_WALL: # NS
                room[r][c] = MARK_DOOR
            
# find rooms with bfs
dr = ( -1, 0, 1, 0)
dc = ( 0, 1, 0, -1 )

room_cnt = 0
for r, row in enumerate(room):
    for c, x in enumerate(row):
        if x == MARK_ROOM:
            # new room
            room_cnt += 1
            room[r][c] = room_cnt

            # BFS
            que = [r * MAX_PLAN_SIZE + c]
            while len(que) > 0:
                v = que.pop(0)
                cur_r = v // MAX_PLAN_SIZE
                cur_c = v % MAX_PLAN_SIZE
                
                for d in range(4):
                    nr = cur_r + dr[d]
                    nc = cur_c + dc[d]
                    if nr < 0 or nr >= len(room):
                        continue
                    if nc < 0 or nc >= len(room[nr]):
                        continue

                    if room[nr][nc] == MARK_ROOM:
                        room[nr][nc] = room_cnt
                        que.append(nr * MAX_PLAN_SIZE + nc)

# output
for row in room:
    for x in row:
        if x == MARK_WALL:
            print('#', end='')
        elif x == MARK_DOOR:
            print(' ', end='')
        else:
            print(f'\x1b[0;;4{x%8}m \x1b[0m', end='')
    print('')
