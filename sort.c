/**
* ------------------------------------------------------------------------------
* MIT License
* 
* Copyright (c) 2018 CHARLOT Servan
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* ------------------------------------------------------------------------------
*/

/**
* @file sort.c
* @brief This file contains differents sort functions and a way to
*        display the array while it's being sorted.
* @author CHARLOT Servan 
*         and the original authors of the sorts algorithms.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
* @def I
* @brief Constant that sets the highest number in the array we want to sort
*        and also the number of lines there will be on the plot.
* @require Must be smaller or equal to the number of lines of the terminal.
*/
#define I 55
/**
* @def J
* @brief Constant that sets the number of values to sort and also the number 
*        of column there will be on the plot.
* @require Must be smaller or equal to the number of column of the terminal.
*/
#define J 200
/**
* @def DISPLAY_COLOR
* @brief Constant used to choose if the plot is displayed with colors or with caracters.
*        Set it to 0 to display caracters and to 1 to display colors.
*/
#define DISPLAY_COLOR 1

int alea(int a, int b);
void init_tab(int tab[J]);
void display_axis(int tab[J], char *sort);
void swap(int tab[J], int i, int j);
void copy_array(int A[J], int iBegin, int iEnd, int B[J]);

void bubble_sort(int tab[J]);

void insertion_sort(int tab[J]);

void cocktail_shaker_sort(int tab[J]);

void topDownMergeSort(int A[J]);
void topDownSplitMerge(int B[J], int iBegin, int iEnd, int A[J]);
void topDownMerge(int A[J], int iBegin, int iMiddle, int iEnd, int B[J]);

/*
* Global useful tools
*/

/**
* @fn int alea(int a, int b)
* @brief Return a random number between a (included) and b (included).
* @param[in] a Lower bound.
* @param[in] b Upper bound.
* @return A random number between a and b (included).
*/
int alea(int a, int b)
{
    return (rand()%(b-a+1)+a);
}

/**
* @fn void init_tab(int tab[J])
* @brief Fill the array given in parameter with a random number between 0 and I (constant).
* @param[in, out] tab[J] The array to fill.
*/
void init_tab(int tab[J]){
	int i;
	for(i = 0; i < J; i++){
		tab[i] = alea(0,I-1);
		// tab[i] = I - i -1;
	}
}

/**
* @fn void display_axis(int tab[J], char *sort)
* @brief Displays the plot in the terminal. The size of the axis are set by the constants.
* @param[in, out] tab[J] The array to plot.
*/
void display_axis(int tab[J], char *sort){
	int i,j;
	char axis[I][J];
	system("clear");
	printf("%s\n", sort);
	for(i = 0; i < I; i++){
		for(j = 0; j < J; j++){
			axis[i][j] = ' ';
		}
	}

	for(j = 0; j < J; j++){
		axis[tab[j]][j] = 'o';
		for(i = tab[j]-1; i >= 0; i--){
			axis[i][j] = '|';
		}
	}

	for(i = I-1; i >= 0; i--){
		for(j = 0; j < J; j++){
#if DISPLAY_COLOR			
			if(axis[i][j] == '|'){
				printf("\033[7m \033[0m");
			} else if (axis[i][j] == 'o'){
				printf("\033[41m \033[0m");
			} else {
				printf(" ");
			}
#else
			// printf("%c", axis[i][j]);
			if(axis[i][j] == 'o'){
				printf("o");
			} else {
				printf(" ");
			}
#endif
		}
		printf("\n");
	}
	system("sleep 0.1");

}

/**
* @fn void swap(int tab[J], int i, int j)
* @brief Swap two elements in the array.
* @param[in] i Index of the first element to swap. {Require : i < J}
* @param[in] j Index of the second element to swap. {Require : j < J}
* @param[in, out] tab[J] Array where the swap takes place.
*/
void swap(int tab[J], int i, int j){
	int temp;
	temp = tab[i];
	tab[i] = tab[j];
	tab[j] = temp;
}

/**
* @fn void copy_array(int A[J], int iBegin, int iEnd, int B[J])
* @brief Copy a segement of the array A into the array B.
* @param[in, out] A[J] Array containing the data to copy.
* @param[in] iBegin Begining index of the segement (included).
* @param[in] iEnd End index of the segement (not included).
* @param[in, out] B[J] Array where the data have to be copied.
*/
void copy_array(int A[J], int iBegin, int iEnd, int B[J])
{
	int k;
    for(k = iBegin; k < iEnd; k++)
        B[k] = A[k];
}

/*
* Bubble Sort
*/

/**
* @fn void bubble_sort(int tab[J])
* @brief Bubble sort algorithm. More information here : https://en.wikipedia.org/wiki/Bubble_sort
* @param[in, out] tab[J] Array to sort.
*/
void bubble_sort(int tab[J]){
	int sorted;
	int i,j;
	i = J-1;
	while(i > 0 && !sorted){
		sorted = 1;
		for(j = 0; j < i; j++){
			if(tab[j] > tab[j+1]){
				swap(tab, j, j+1);
				sorted = 0;
			}
		}
		display_axis(tab, "Bubble Sort");
		i--;
	}
}

/*
* Insertion Sort
*/

/**
* @fn void insertion_sort(int tab[J])
* @brief Insertion sort algorithm. More information here : https://en.wikipedia.org/wiki/Insertion_sort
* @param[in, out] tab[J] Array to sort.
*/
void insertion_sort(int tab[J]){
	int i,j,x;
	for(i = 1; i < J; i++){
		x = tab[i];
		j = i;
		while(j > 0 && tab[j-1] > x){
			tab[j] = tab[j-1];
			j--;
		}
		tab[j] = x;
		display_axis(tab, "Insertion Sort");
	}
}

/*
* Cocktail Shaker Sort
*/

/**
* @fn void cocktail_shaker_sort(int tab[J])
* @brief void Cocktailshaker sort algorithm. More information here : https://en.wikipedia.org/wiki/Cocktail_shaker_sort
* @param[in, out] tab[J] Array to sort.
*/
void cocktail_shaker_sort(int tab[J]){
	int i;
	int start = 0;
	int swaped = 1; //True
	int end = J-2;

	while(swaped){
		swaped = 0;
		for(i = start; i <= end; i++){
			if(tab[i] > tab[i+1]){
				swap(tab, i, i+1);
				swaped = 1;
			}
		}
		end--;
		for(i = end; i >= start; i--){
			if(tab[i] > tab[i+1]){
				swap(tab, i, i+1);
				swaped = 1;
			}
		}
		start++;
		display_axis(tab, "Cocktail Shaker Sort");
	}
}

/*
* Odd Even Transposition Sort
*/

/**
* @fn void odd_even_transposition_sort(int tab[J])
* @brief void Odd-even transposition sort algorithm. More information here : https://en.wikipedia.org/wiki/Odd-even_sort
* @param[in, out] tab[J] Array to sort.
*/
void odd_even_transposition_sort(int tab[J]){
	int i;
	int sorted = 0;
	while(!sorted){
		sorted = 1;
		for(i = 1; i < J-1; i +=2){
			if(tab[i] > tab[i+1]){
				swap(tab, i, i+1);
				sorted = 0;
			}
		}
		for(i = 0; i < J-1; i +=2){
			if(tab[i] > tab[i+1]){
				swap(tab, i, i+1);
				sorted = 0;
			}
		}
		display_axis(tab, "Odd-Even Transposition Sort");
	}
}

/*
* Top Down Merge Sort
*/

/**
* @fn void topDownMergeSort(int A[J])
* @brief Merge sort algorithm. More information here : https://en.wikipedia.org/wiki/Merge_sort
* @param[in, out] A[J] Array to sort.
*/
void topDownMergeSort(int A[J]){
	//Array A[] has the items to sort; array B[] is a work array.
	int B[J];
	// duplicate array A[] into B[]
    copy_array(A, 0, J, B);
    // sort data from B[] into A[]
    topDownSplitMerge(B, 0, J, A);
}

/**
* @fn void topDownSplitMerge(int B[J], int iBegin, int iEnd, int A[J])
* @brief Sort the given run of array A[J] using array B[J] as a source.
* @param[in, out] B[J] Source array where the data to sort are taken.
* @param[in] iBegin Begining index of the segement (included).
* @param[in] iEnd End index of the segement (not included).
* @param[in, out] A[J] Destination array where the sorted data ends.
*/
void topDownSplitMerge(int B[J], int iBegin, int iEnd, int A[J]){
    int iMiddle;
    // if run size == 1
    if(iEnd - iBegin < 2)
        // consider it sorted
        return;
    
    // split the run longer than 1 item into halves
    // iMiddle = mid point
    iMiddle = (iEnd + iBegin) / 2;
    // recursively sort both runs from array A[] into B[]
    // sort the left  run
    topDownSplitMerge(A, iBegin,  iMiddle, B);
    // sort the right run
    topDownSplitMerge(A, iMiddle,    iEnd, B);
    // merge the resulting runs from array B[] into A[]
    topDownMerge(B, iBegin, iMiddle, iEnd, A);
    display_axis(A, "Merge Sort");
}

/**
* @fn void topDownMerge(int A[J], int iBegin, int iMiddle, int iEnd, int B[J])
* @brief Merges array A[J] and array B[J]. Left source half is A[iBegin:iMiddle-1], 
*        right source half is A[iMiddle:iEnd-1], result is B[iBegin:iEnd-1].
* @param[in, out] A[J] Source array where the data to merge are taken.
* @param[in] iBegin Begining index of the segement (included).
* @param[in] iMiddle Middle index of the segement.
* @param[in] iEnd End index of the segement (not included).
* @param[in, out] B[J] Source/Destination array where the merged data ends.
*/
void topDownMerge(int A[J], int iBegin, int iMiddle, int iEnd, int B[J]){
    int i = iBegin, j = iMiddle;
    int k;
 
    // While there are elements in the left or right runs...
    for (k = iBegin; k < iEnd; k++) {
        // If left run head exists and is <= existing right run head.
        if (i < iMiddle && (j >= iEnd || A[i] <= A[j])) {
            B[k] = A[i];
            i = i + 1;
        } else {
            B[k] = A[j];
            j = j + 1;
        }
    }
}

/*
* Main Function
*/

/**
* @fn int main(int argc, char const *argv[])
* @brief Initialize an array and sort it in different ways.
* @param argc Unused.
* @param argv Unused.
*/
int	main(int argc, char const *argv[])
{
	int tab[J];
	srand(time(NULL));

	init_tab(tab);
	bubble_sort(tab);
	init_tab(tab);
	insertion_sort(tab);
	init_tab(tab);
	cocktail_shaker_sort(tab);
	init_tab(tab);
	odd_even_transposition_sort(tab);
	init_tab(tab);
	topDownMergeSort(tab);

	system("clear");

	// for(int i = 0; i < J ; i++){
	// 	printf("%d ", tab[i]);
	// }
	// printf("\n");
	return 0;
}