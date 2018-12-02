#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define WORDCNT 5
#define M 12
#define MAXVAL 2147483647


//function prototypes
int take_pow(int s, int k );
void create_space_matrix(int space[WORDCNT+1][WORDCNT+1],char* words[WORDCNT]);
void create_spaceCost_matrix(long int spaceCost[WORDCNT+1][WORDCNT+1],int space[WORDCNT+1][WORDCNT+1]);
void calculate_costs(long int cost[WORDCNT+1],long int spaceCost[WORDCNT+1][WORDCNT+1],int i_values[WORDCNT+1]);
int calculate_line_adr(int i_values[WORDCNT+1],int lineAdr[WORDCNT+1]);
void print_lines(int lineAdr[WORDCNT+1],int line_cnt,char* words[WORDCNT]);



//Calculates spaces left at the end of lines after the ith and jth word inserted
void create_space_matrix(int space[WORDCNT+1][WORDCNT+1],char* words[WORDCNT]) {

        int i,j,k;
        int length_sum;


        for (i = 1; i < WORDCNT+1; i++) {
                //one word is written to the line
                space[i][i] = M - strlen(words[i-1]);
                for (j = i+1; j < WORDCNT+1; j++) {
                        length_sum = 0;

                        for (k = i; k <= j ; k++) {
                                length_sum += strlen(words[k-1]);
                        }

                        space[i][j] = M - j + i - length_sum;
                }
        }

}


//Calculates space costs according to spaces left at the end of lines. Spaces weighted as space[i][j]^3
void create_spaceCost_matrix(long int spaceCost[WORDCNT+1][WORDCNT+1],int space[WORDCNT+1][WORDCNT+1]) {

        int i,j,dummy;

        for (i = 1; i < WORDCNT+1; i++) {
                if (space[i][i] < 0)
                        spaceCost[i][i] = MAXVAL;

                else
                        spaceCost[i][i] = take_pow(space[i][i],3);


                for (j = i+1; j < WORDCNT+1; j++) {

                        if(space[i][j] < 0)
                                spaceCost[i][j] = MAXVAL;

                        else
                                spaceCost[i][j] = take_pow(space[i][j],3);



                }

        }

}


//Taking kth power of s
int take_pow(int s, int k ) {

        int i;
        int mul = 1;

        for (i = 0; i < k; i++) {
                mul *= s;
        }

        return mul;

}


//Calculates cost for each 0<j<=WORDCNT. cost[j] stands for the minimum cost after inserted 1 to jth words
void calculate_costs(long int cost[WORDCNT+1],long int spaceCost[WORDCNT+1][WORDCNT+1],int i_values[WORDCNT+1]) {
        cost[0] = 0;
        int j,i;
        long int min_cost,temp;


        for (j = 1; j <= WORDCNT; j++) {
                min_cost = spaceCost[1][j]; // cost[j] = cost[0] + spaceCost[1][j], cost[0] is zero
                i_values[j] = 1;

                for (i = 1; i <= WORDCNT; i++) {

                        if (spaceCost[i][j] != MAXVAL) {

                                temp = cost[i-1] + spaceCost[i][j];

                                if (temp < min_cost) {
                                        min_cost = temp;
                                        i_values[j] = i;
                                }

                        }

                }
                cost[j] = min_cost;
        }
}

//Calculates each line's beginning word's order in the words array
int calculate_line_adr(int i_values[WORDCNT+1],int lineAdr[WORDCNT+1]) {

        int j = WORDCNT;
        int i = i_values[j]; //holds the beginning of the last line
        int line_cnt = 0;


        while ( i != 1 ) {

                lineAdr[line_cnt] = i;
                line_cnt++;
                j = i-1;
                i = i_values[j];


        }
        lineAdr[line_cnt] = 1; //first line begins with first word
        line_cnt++;
        return line_cnt;

}

//Prints words inserted with min cost format
void print_lines(int lineAdr[WORDCNT+1],int line_cnt,char* words[WORDCNT]) {
        int i,k,word_index;
        word_index = 0;

        for (i = line_cnt-1; i > 0; i--) {

                for (k = 0; k < lineAdr[i-1]-lineAdr[i]; k++) {
                        printf("%s ",words[word_index]);
                        word_index++;

                }
                printf("\n");
        }

        for (i = word_index; i < WORDCNT; i++) {
                printf("%s ",words[i] );
        }

        printf("\n\n");

}




int main(int argc, char *argv[]) {

        char* words[WORDCNT] = {"ali","veli","hasan","huseyin","cemal"};
        int space[WORDCNT+1][WORDCNT+1] = {0};
        long int spaceCost[WORDCNT+1][WORDCNT+1] = {0};
        long int cost[WORDCNT+1];
        int i_values[WORDCNT+1];  //holds the line beginnings for all combinations of j value
        int lineAdr[WORDCNT+1];  //holds the line beginnings for used combinations of j value
        int i,j;
        int line_cnt; //holds the total line count after inserted all words with minimum cost



        create_space_matrix(space,words);
        create_spaceCost_matrix(spaceCost,space);
        calculate_costs(cost,spaceCost,i_values);
        line_cnt = calculate_line_adr(i_values,lineAdr);



        printf("space matrix: \n\n");
        for (i = 0; i < WORDCNT+1; i++) {
                for (j = 0; j < WORDCNT+1; j++) {
                        printf("%d ",space[i][j] );
                }
                printf("\n");
        }

        printf("\n\n\n");



        printf("spaceCost matrix: \n\n");
        for (i = 0; i < WORDCNT+1; i++) {
                for (j = 0; j < WORDCNT+1; j++) {
                        printf("%ld ",spaceCost[i][j] );
                }
                printf("\n");
        }


        printf("\n\n\n");

        printf("cost array: \n\n");
        for (i = 0; i < WORDCNT+1; i++) {
                printf("%ld ",cost[i] );
        }

        printf("\n\n\n");

        printf("i_values array: \n\n");
        for (i = 0; i < WORDCNT+1; i++) {
                printf("%d ",i_values[i] );

        }

        printf("\n\n\n");

        printf("lineAdr array: \n\n");
        for (i = line_cnt-1; i >= 0; i--) {
                printf("%d ",lineAdr[i] );
        }

        printf("\n\n\n");

        printf("Words inserted with min cost format:\n \n");
        print_lines(lineAdr,line_cnt,words);









	return 0;
}
