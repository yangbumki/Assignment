#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define LAMB_MONEY          12000
#define DRINK_MONEY         2000

int solution(int n, int k) {

    unsigned int serviceCnt = n >= 10 ? n / 10 : 0;

    int answer = LAMB_MONEY * n + DRINK_MONEY * (k - serviceCnt);

    return answer;
}