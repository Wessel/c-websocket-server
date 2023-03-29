/* array.c */
#include <stdio.h>
#include <stdlib.h>

/** @brief Prints the values of `arr` into `STDOUT`
 *
 * C does not usually come with a way to print arrays,
 * this function makes that possible.
 *
 * @param arr The array to print
 * @param size The size of `arr`
 *
 * @returns void
 */
void print_array(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("Array[%d]\t= %d\n", i, arr[i]);
  }
}

/** @brief Find the key `index` of `needle` in `arr`
 *
 * In order to find a value's place in an array, we can
 * use the following function to find `needle` in `arr`.
 *
 * @param arr The array to look through
 * @param size The size of `arr`
 * @param needle The value to search for
 *
 * @returns index The index of `needle` if found, else `-1`
 */
int find_index(int arr[], int size, int needle) {
  for (int i = 0; i < size; i++) {
    if (arr[i] == needle) return i;
  }

  return -1;
}

/** @brief Find the highest three numbers in `arr`
 *
 * In order to find the highest three values in an array,
 * a loop and a set of if statements can be used.
 *
 * @param arr The array to look through
 * @param size The size of `arr`
 *
 * @returns max An array with the highest three numbers in `arr`
 */
int* largest_three(int arr[], int size) {
  int* max = malloc(3);
  max[0] = arr[0];
  max[1] = arr[1];
  max[2] = arr[2];

  for (int i = 0; i < size; i++) {
    if (arr[i] > max[0]) {
      max[2] = max[1];
      max[1] = max[0];
      max[0] = arr[i];
    }
    else if (arr[i] > max[1]) {
      max[2] = max[1];
      max[1] = arr[i];
    }
    else if (arr[i] > max[2]) {
      max[2] = arr[i];
    }
  }

  return max;
}

/** @brief Inverse the contents of `arr`
 *
 * This function will return the inversed version of `arr`.
 * This will mean that arr[last] = inversed_array[first].
 *
 * @param arr The array to inverse
 * @param size The size of `arr`
 *
 * @returns inversed_array An inversed version of `arr`
 */
int* inverse_array(int arr[], int size) {
  int* inversed_array = malloc(size);

  for (int i = size; i > 0; i--) {
    inversed_array[size - i] = arr[i - 1];
  }

  return inversed_array;
}

/** @brief Sorts `arr` alphabetically using bubble sorting
 *
 * In order to alphabetically sort `arr` filled with `char`,
 * the bubble sorting algorithm can be used.
 * (THIS FUNCTION OVERWRITES `arr`.)
 *
 * @param arr The array to sort
 * @param size The size of `arr`
 *
 * @returns void
 */
void sort_char_array(char arr[], int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i -1; j++) {
      if (arr[j] > arr[j + 1]) {
        char temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

/** @brief Filters out any non-lowercase characters from `arr`,
 * then passes it to `sort_char_array()`
 *
 * In order to filter out any non-lowercase characters and then
 * sort the array alphabetically, the function below is used.
 * It will loop through the array and check if the charcodes are inbetween
 * 'a' and 'z', if not removes them.
 *
 * @param arr The array to filter and sort
 * @param size The size of `arr`
 *
 * @returns void
 */
void filter_lowercase_and_sort(char arr[], int size) {
  int count = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] >= 'a' && arr[i] <= 'z') {
      arr[count++] = arr[i];
    }
  }

  sort_char_array(arr, count);
}

// void print_array(void *arr, int size, size_t elem_size, char *format) {
//   for (int i = 0; i < size; i++) {
//     printf("Array[%d] = ", i);
//     char *elem = (char *) arr + i * elem_size;
//     printf(format, *(int *) elem);
//     printf("\n");
//   }
// }
