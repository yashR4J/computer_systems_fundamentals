#include <stdio.h>
#include <stdlib.h>

int isIdent(int N, int m[N][N]) {
   for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
         if ((i == j && m[i][j] != 1)
             || ((i != j && m[i][j] != 0)))
            return 0;
      }
   }
   return 1;
}

int main(int argc, char  *argv[])
{
    int size;
    printf("Please enter the matrix size: ");
    scanf("%d", &size);

    printf("Draw it now!\n");
    int m[size][size];
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        scanf("%d", &(m[i][j]));
      }
    }
    if (isIdent(size, m)) {
        printf("This is an Identity Matrix!\n");
    } else {
        printf("You're incorrect!\n");
    }

    return 0;
}
