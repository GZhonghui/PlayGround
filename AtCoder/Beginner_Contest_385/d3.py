def count_vertices_visited(data):
    lines = data.strip().split('\n')
    n, m, x, y = map(int, lines[0].split())
    vertices = set(tuple(map(int, line.split())) for line in lines[1:n + 1])
    movements = lines[n + 1:]
    
    visited = set()
    current_x, current_y = x, y
    
    for move in movements:
        direction = move[0]
        distance = int(move[1:])
        dx, dy = 0, 0
        
        if direction == 'U':  # Up
            dy = 1
        elif direction == 'D':  # Down
            dy = -1
        elif direction == 'L':  # Left
            dx = -1
        elif direction == 'R':  # Right
            dx = 1
        
        # Simulate the movement
        for _ in range(distance):
            current_x += dx
            current_y += dy
            if (current_x, current_y) in vertices:
                visited.add((current_x, current_y))
    
    return visited


# 解析用户输入
input_data = """100 100 46 -34
-55 -79
-13 -42
-62 -95
-81 -43
30 -60
83 -20
-90 -13
4 -33
69 21
-72 73
-1 -12
32 -85
65 -1
63 36
-3 44
63 94
-68 8
-72 -33
-86 23
-96 11
-38 50
20 1
14 69
-91 92
-65 -65
-97 61
-39 25
-30 -84
99 28
43 40
34 9
-91 59
-6 -43
57 -17
-27 -6
57 -2
35 -34
-62 15
-92 11
-39 -34
-72 3
43 -11
-20 39
-8 -3
8 23
79 -23
-45 95
2 -13
-52 27
84 -35
-31 -16
61 5
26 -81
-18 75
88 -36
81 21
2 90
89 -59
45 -19
-90 0
-50 -15
68 78
63 -44
-98 -53
-8 44
21 65
83 69
-13 -72
-29 48
-45 42
-91 -88
-69 -92
-16 -52
-15 -71
-46 67
18 -54
53 96
21 10
47 55
-49 -23
-10 -21
76 -60
25 32
-84 27
63 34
35 30
-48 94
58 -26
73 66
30 35
66 47
84 -49
-5 1
-49 -46
85 -76
68 -30
-94 -6
63 10
21 81
0 -76
P 9
L 10
R 49
L 82
L 56
U 59
P 17
R 82
R 70
U 4
U 34
P 31
U 70
U 36
R 70
L 49
L 67
R 83
R 3
R 41
L 62
L 42
P 47
L 34
L 95
R 48
U 84
L 73
R 25
R 88
P 38
U 3
L 22
R 61
P 2
U 37
R 47
P 70
R 77
P 17
P 5
P 27
P 16
U 27
P 91
R 100
L 6
L 71
P 16
L 82
P 94
U 25
U 32
P 70
R 9
L 94
R 36
P 67
L 30
P 90
P 75
P 60
P 15
U 76
R 66
U 90
L 89
R 53
L 18
U 45
U 18
R 87
R 87
L 79
R 10
U 96
L 75
P 17
U 41
U 68
P 88
U 88
R 46
P 71
U 29
U 72
P 28
P 83
U 100
R 15
R 67
L 31
U 51
R 51
L 46
R 6
P 58
R 34
L 15
U 50"""

# 输出经过的顶点
visited_vertices = count_vertices_visited(input_data)
print("访问过的顶点:")
for vertex in visited_vertices:
    print(vertex)