

def solution(map):
  dx = [1, -1, 0, 0]
  dy = [0, 0, 1, -1]
  n=len(map)
  m=len(map[0])
  queue = []
  used = [[[0, 0] for _ in range(m)] for _ in range(n)]
  queue.append((0, 0, 0))
  used[0][0][0]=1
  while len(queue)!=0:
    (x, y, c) = queue.pop(0)
    if map[x][y]==1 and c==1 :
      continue
    for i in range(4):
      (nx, ny, nc)=(x+dx[i], y+dy[i], c+map[x][y])
      if nx<0 or ny<0 or n<=nx or m<=ny or used[nx][ny][nc]:
        continue
      used[nx][ny][nc]=used[x][y][c]+1
      queue.append((nx, ny, nc))

  if used[n-1][m-1][0]==0: 
    used[n-1][m-1][0]=1e9
  if used[n-1][m-1][1]==0: 
    used[n-1][m-1][1]=1e9
  return min(used[n-1][m-1][0], used[n-1][m-1][1])


