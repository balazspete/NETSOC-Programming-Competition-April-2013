#include<stdio.h>
int main()
{
  int c1, c2, i, j, curr, prev, amount, total;
  int list[21];
  char result[2][20001];
  scanf("%d", &c1);


  while(c1--)
  {
    scanf("%d", &c2);
    scanf("%d", &amount);
    curr = 0;
    prev = 1;
    for(i=1; i<=c2; i++)
    {
      scanf("%d", &list[i]);
    }
    for(i=0; i<=c2; i++)
    {
      curr = curr + prev;
      prev = curr - prev;
      curr = curr - prev;
      for(j=0; j<=amount; j++)
      {
        if(i==0 && j==0)
         result[curr][0] = 'y';
        else if(i==0)
         result[curr][j] = 'x';
        else
         result[curr][j] = result[prev][j] == 'y' || ((j-list[i]) >=0 && result[prev][j-list[i]] == 'y') ? 'y' : 'x';
      }
    }
    if(result[curr][amount] == 'y')
      printf("Yes\n");
    else
      printf("No\n");
  }
  return 0;
}