//isim-soyisim : Cetin Tekin
//ogr no : 17011603
//ONEMLI NOT : Max line capacity degerinin maximum degerinin kac olacagi bilinmedigi icin spaceCost ve cost dizileri long olarak tanimlanmistir
//Tahmin edilen limitin yukarisinda sacma degerler uretilebilir
//Linux ortamında GNU GCC ile long boyutu 8 byte oldugu icin daha buyuk sayilari destekleyecektir



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define WORDCNT 300 //Max word count
#define M 15  //Line capacity



//Function prototypes
int take_pow(int s, int k );
void create_space_matrix(int space[WORDCNT+1][WORDCNT+1],char* words[WORDCNT],int word_cnt);
void create_spaceCost_matrix(long int spaceCost[WORDCNT+1][WORDCNT+1],int space[WORDCNT+1][WORDCNT+1],int word_cnt);
void calculate_costs(long int cost[WORDCNT+1],long int spaceCost[WORDCNT+1][WORDCNT+1],int i_values[WORDCNT+1],int word_cnt);
int calculate_line_adr(int i_values[WORDCNT+1],int lineAdr[WORDCNT+1],int word_cnt);
void print_lines(int lineAdr[WORDCNT+1],int line_cnt,char* words[WORDCNT],int word_cnt);
int tokenize_paragraph (char paragraph[1000],char* words[WORDCNT]);



//Calculates spaces left at the end of lines after the ith and jth word inserted
void create_space_matrix(int space[WORDCNT+1][WORDCNT+1],char* words[WORDCNT],int word_cnt) {

        int i,j,k;
        int length_sum;


        for (i = 1; i < word_cnt+1; i++) {
                //one word is written to the line
                space[i][i] = M - strlen(words[i-1]);
                for (j = i+1; j < word_cnt+1; j++) {
                        length_sum = 0;

                        for (k = i; k <= j ; k++) {
                                length_sum += strlen(words[k-1]);
                        }

                        space[i][j] = M - j + i - length_sum;
                }
        }

}


//Calculates space costs according to spaces left at the end of lines. Spaces weighted as space[i][j]^3
void create_spaceCost_matrix(long int spaceCost[WORDCNT+1][WORDCNT+1],int space[WORDCNT+1][WORDCNT+1],int word_cnt) {

        int i,j,dummy;

        for (i = 1; i < word_cnt+1; i++) {
                if (space[i][i] < 0)
                        spaceCost[i][i] = LONG_MAX;

                else
                        spaceCost[i][i] = take_pow(space[i][i],3);


                for (j = i+1; j < word_cnt+1; j++) {

                        if(space[i][j] < 0)
                                spaceCost[i][j] = LONG_MAX;

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
void calculate_costs(long int cost[WORDCNT+1],long int spaceCost[WORDCNT+1][WORDCNT+1],int i_values[WORDCNT+1],int word_cnt) {
        cost[0] = 0;
        int j,i;
        long int min_cost,temp;


        for (j = 1; j <= word_cnt; j++) {
                min_cost = spaceCost[1][j]; // cost[j] = cost[0] + spaceCost[1][j], cost[0] is zero
                i_values[j] = 1;

                for (i = 1; i <= j; i++) {

                        if ( spaceCost[i][j] != LONG_MAX ) {

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

//Calculates each line's beginning word's order in the words array by backtracking using i_values array that is formed in the calculate_cost function
int calculate_line_adr(int i_values[WORDCNT+1],int lineAdr[WORDCNT+1],int word_cnt) {

        int j = word_cnt;
        int i = i_values[j]; //holds the beginning of the last line
        int line_cnt = 0;

        // Loop continues until the first line is reached
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
void print_lines(int lineAdr[WORDCNT+1],int line_cnt,char* words[WORDCNT],int word_cnt) {
        int i,k,word_index;
        word_index = 0;

        for (i = line_cnt-1; i > 0; i--) {

                for (k = 0; k < lineAdr[i-1]-lineAdr[i]; k++) {
                        printf("%s ",words[word_index]);
                        word_index++;

                }
                printf("\n");
        }

        for (i = word_index; i < word_cnt; i++) {
                printf("%s ",words[i] );
        }

        printf("\n\n");

}

//Parses the paragraph that are given by user in the code into words and stores words in words array
int tokenize_paragraph (char paragraph[],char* words[WORDCNT]) {

        char* p;
        int i=0;
        int k,length;

        p=strtok(paragraph," ");

        while (p!=NULL) {
                length = strlen(p);
                words[i] = (char*)malloc(sizeof(char)*length);

                strcpy(words[i],p);
                p=strtok(NULL," ");
                i++;

        }


        printf("Words that will be processed :\n\n");

        for (k = 0; k < i; k++) {
                printf("%s\n",words[k] );
        }

        printf("\n");
        printf("-----------------------------------------------------------------\n");
        printf("\n");

        printf("Word count: %d",i );

        printf("\n");
        printf("-----------------------------------------------------------------\n");
        printf("\n");

        return i;
}




int main(int argc, char *argv[]) {

        char* words[WORDCNT];
        char paragraph[] = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. ";
        int space[WORDCNT+1][WORDCNT+1] = {0};
        long int spaceCost[WORDCNT+1][WORDCNT+1] = {0};
        long int cost[WORDCNT+1];
        int i_values[WORDCNT+1];  //Holds the line beginnings of lines for all combinations of j value(the ending word)
        int lineAdr[WORDCNT+1];  //Holds the line beginnings for used combinations of j value
        int i,j;
        int line_cnt; //Holds the total line count after inserted all words with minimum cost
        int word_cnt; //Total word count


        word_cnt = tokenize_paragraph (paragraph,words);
        create_space_matrix(space,words,word_cnt);
        create_spaceCost_matrix(spaceCost,space,word_cnt);
        calculate_costs(cost,spaceCost,i_values,word_cnt);
        line_cnt = calculate_line_adr(i_values,lineAdr,word_cnt);



        /*printf("space matrix: \n\n");
        for (i = 0; i < word_cnt+1; i++) {
                for (j = 0; j < word_cnt+1; j++) {
                        printf("%d ",space[i][j] );
                }
                printf("\n");
        }

        printf("\n");
        printf("-----------------------------------------------------------------\n");
        printf("\n");

       */

        /*
        printf("spaceCost matrix: \n\n");
        for (i = 0; i < word_cnt+1; i++) {
                for (j = 0; j < word_cnt+1; j++) {
                        printf("%ld ",spaceCost[i][j] );
                }
                printf("\n");
        }


        printf("\n");
        printf("-----------------------------------------------------------------\n");
        printf("\n");

        */

        printf("cost array: \n\n");
        for (i = 0; i < word_cnt+1; i++) {
                printf("%ld ",cost[i] );
        }

        printf("\n");
        printf("-----------------------------------------------------------------\n");
        printf("\n");

        printf("Minimum cost: %ld\n",cost[word_cnt] );

        printf("\n");
        printf("-----------------------------------------------------------------\n");
        printf("\n");

        printf("i_values array: \n\n");
        for (i = 0; i < word_cnt+1; i++) {
                printf("%d ",i_values[i] );

        }

        printf("\n");
        printf("-----------------------------------------------------------------\n");
        printf("\n");

        printf("lineAdr array: \n\n");
        for (i = line_cnt-1; i >= 0; i--) {
                printf("%d ",lineAdr[i] );
        }

        printf("\n");
        printf("-----------------------------------------------------------------\n");
        printf("\n");

        printf("Words inserted with min cost format:\n \n");
        print_lines(lineAdr,line_cnt,words,word_cnt);






	return 0;
}
