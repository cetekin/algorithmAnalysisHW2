#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define WORDCNT 5
#define M 18

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void create_space_matrix(int space[WORDCNT+1][WORDCNT+1],char* words[WORDCNT]) {

        int i,j,k;
        int length_sum;


        for (i = 1; i < WORDCNT+1; i++) {
                space[i][i] = M - strlen(words[i])
                for (j = i+1; j < WORDCNT+1; j++) {
                        length_sum = 0;

                        for (k = i; k <= j ; k++) {
                                length_sum += strlen(words[k-1]);
                        }

                        space[i][j] = M - (j + i*length_sum)
                }
        }

}

int main(int argc, char *argv[]) {

        char* words[WORDCNT] = {"ali","veli","hasan","hüseyin","cemal"}
        int space[WORDCNT+1][WORDCNT+1] = {0};
        long int spaceCost[WORDCNT+1][WORDCNT+1];
        long int cost[WORDS+1];
        int i,j;

        for (i = 0; i < WORDCNT+1; i++) {
                for (j = 0; j < WORDCNT+1; j++) {
                        printf("%d ",space[i][j] );
                }
                printf("\n");
        }















	return 0;
}
