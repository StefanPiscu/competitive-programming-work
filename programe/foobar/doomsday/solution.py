from fractions import Fraction

def gcd(x, y):
   while(y):
       x, y = y, x % y
   return x

def initMatrice(n, m):
  return [[0 for _ in range(m)] for _ in range(n)]

def addLines(matrice, l1, l2, mul):
  for i in range(len(matrice[0])):
    matrice[l1][i]+=matrice[l2][i]*mul
  
def mulLine(matrice, l, mul):
  for i in range(len(matrice[l])):
    matrice[l][i]=matrice[l][i]*mul

def getInverseOfMatrix(matrice):
  n=len(matrice)
  identitate = initMatrice(n, n)
  for i in range(n):
    identitate[i][i]=1
  for j in range(n):
    i=0
    for _i in range(j, n):
      if matrice[_i][j]!=0:
        i=_i
        break
    matrice[i], matrice[j] = matrice[j], matrice[i]
    identitate[i], identitate[j] = identitate[j], identitate[i]
    i=j
    for i2 in range(n):
      if i==i2:
        continue
      addLines(identitate, i2, i, -matrice[i2][j]/float(matrice[i][j]))
      addLines(matrice, i2, i, -matrice[i2][j]/float(matrice[i][j]))
  for i in range(n):
    mulLine(identitate, i, 1/float(matrice[i][i]))
    mulLine(matrice, i, 1/float(matrice[i][i]))
  return identitate

def multiplyMatrix(a, b):
  c=initMatrice(len(a), len(b[0]))
  for i in range(len(a)):
    for k in range(len(b)):
      for j in range(len(b[0])):
        c[i][j]+=a[i][k]*b[k][j]
  return c



def solution(matrice):
  sol=[]

  #get terminal states
  isterm=[False for _ in matrice]
  for i in range(len(matrice)):
    sum=0
    for j in matrice[i]:
      sum+=j
    if sum==0:
      isterm[i]=True
      
  #add self loops in markov chain
  for i in range(len(matrice)):
    matrice[i][i]=1

  #get probability matrix
  for i in range(len(matrice)):
    sum=0
    for j in matrice[i]:
      sum+=j
    for j in range(len(matrice[i])):
      matrice[i][j]=matrice[i][j]/float(sum)
    sol.append(matrice[i])

  #rapidly exponentiate the matrix with 2^30 (can set larger for better precision if need be)
  for i in range(30):
    sol=multiplyMatrix(sol, sol)

  #compute the fraction solutions
  finsol = [] 
  for i in range(len(sol[0])):
    if isterm[i]:
      finsol.append(Fraction(sol[0][i]).limit_denominator())

  #get lcm of denominators
  lcm=1
  for i in finsol:
    a=lcm
    b=i.denominator
    c=int(gcd(lcm, i.denominator))
    lcm=a*b//c


  #get answer
  ans = [0 for _ in finsol]
  for i in range(len(finsol)):
    ans[i] = finsol[i].numerator*lcm//finsol[i].denominator

  # add common denominator
  ans.append(lcm)

  return ans

  
# this can be solved with the fundamental matrix of absorbing markov chains but getting the limit of the state transitions as you do a very large number of transitions works aswell

print(solution([[0, 1, 0, 0, 0, 1], [4, 0, 0, 3, 2, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0]]))