/***
permutation(全排列)
假设有字符串 'abc' 则找出所有组成字符串的字符的全排列，即：abc acb bac bca cab cba
这样的排列的个数就是字符串字符数的阶乘
下面的算法核心思想是借鉴 C++ STL (Standard Template Library) 中的 next_permutaion 函数
假设现在有一个排列是按照字典序排好的递增顺序的排列，next_permutaion 函数的目的是找到该排列的下一个排列
分为3步：
1. 从最后一个字符往前查找直到相邻的两个字符假设分别为 S[i] 和 S[i+1] 满足 S[i] < S[i+1]
2. 此时，在 S[i+1] 一直到字符串末尾的位置查找所有比 S[i] 大的字符中的最小的字符，假设该字符为 S[min]，然后交换 S[i] 和 S[min] 的位置
   (此时涵盖 S[i+1] 就是字符串末尾字符的情况，即找到的字符就是 S[i+1])
3. 最后将 S[i+1] 以及直至字符串末尾的位置逆序，这样得到的 S 就是下一个排列
同理，prev_permutation 函数负责找到输入字符串的上一个排列，其逻辑也是从字符串末尾开始查找，但是操作逻辑和 next_permutation 完全相反
****/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool prev_permutation(char s[], int length);
bool next_permutation(char s[], int length);
bool reverse(char s[], int start, int end);
bool swap(char s[], int i, int j);
int get_min_greater(char s[], char c, int start, int end);
int get_max_lesser(char s[], char c, int start, int end);

int main(int argc, char *argv[])
{
    char str[] = "abcdef";
    int length = strlen(str);

    printf("%s\n", str);
    // test swap
    // swap(str, 2, 4);
    // printf("%s\n", str);
    // test reverse
    // reverse(str, 0, 6);
    // printf("%s\n", str);
    // test get_min_greater
    // printf("min is %d\n", get_min_greater(str, 'f', 0, 12));

    int total = 1; // 当前字符串本身也是一个排列
    // 找到当前字符串的下一个排列字符串
    while(next_permutation(str, length)) { // 当字符串已经全部逆序排列时 终止循环 已经找到所有排列
        total++;
        printf("%s\n", str);
    }
    // 示例字符串是完全升序字符串，所以运行到这里已经是遍历到了所有的排列了
    // 如果字符串并不是完全升序排列的话，可以把当前字符串复制一份，然后执行 prev_permutation 函数，依次找到它前面的所有排列
    // while(prev_permutation(str, length)) {
    //    total++;
    //    printf("%s\n", str);
    // }

    printf("total is %d\n", total); // 总共有多少个排列

    return 0;
}
// find next permutaion for string s
bool next_permutation(char s[], int length)
{
    int i, min;
    for(i = length - 1; i > 0; i--) {
        if(s[i-1] < s[i]) { // find first ascending order s[i-1] < s[i]
            min = get_min_greater(s, s[i-1], i, length - 1); // find fist element greater than s[i-1] after i-1
            swap(s, i-1, min); // exchange s[i] and s[min]
            reverse(s, i, length - 1); // reverse all element after i then the string s become next permutation of the former string it was
            return true;
        }
    }

    return false;
}

// 寻找字符串s的前面的排列，直至所有字符完全降序
bool prev_permutation(char s[], int length)
{
    int i, max;
    for(i = length - 1; i > 0; i--) {
        if(s[i-1] > s[i]) {
            max = get_max_lesser(s, s[i-1], i, length - 1);
            swap(s, i-1, max);
            reverse(s, i, length - 1);
            return true;
        }
    }

    return false;
}
// 找到字符串s中从start到end中的所有比c小的字符的最大的那个，返回字符的位置，如果没找到返回 -1
int get_max_lesser(char s[], char c, int start, int end)
{
    int i;
    int max = -1; // not found
    for(i = start; i <= end; i++) {
        if(s[i] < c) {
            if(max == -1) {
                max = i;
            }
            if(s[i] > s[max]) {
                max = i;
            }
        }
    }

    return max;
}
// 找到字符串s中从start到end中的所有比c大的字符的最小的那个，返回字符的位置，如果没找到返回 -1
int get_min_greater(char s[], char c, int start, int end)
{
    int i;
    int min = -1; // not found
    for(i = start; i <= end; i++) {
        if(s[i] > c) {
            if(min == -1) { // first greater
                min = i;
            }
            if((s[i] < s[min])) {
                min = i;
            }
        }
    }

    return min;
}
// 字符串逆序 这里也可以调用  swap 方法
bool reverse(char s[], int start, int end)
{
    char tmp;

    while(start < end) {
        tmp = s[start];
        s[start] = s[end];
        s[end] = tmp;

        start++;
        end--;
    }

    return true;
}
// 降两个位置的字符串交换位置
bool swap(char s[], int i, int j)
{
    char tmp;
    tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;

    return true;
}
