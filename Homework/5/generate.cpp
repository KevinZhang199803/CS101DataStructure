#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <string>

using namespace std;
int main()
{
    srand((unsigned)time(NULL));
    int n = rand()%1000;
    int m = rand()%1000;
    int k = rand()%1000;
    printf("%d\n%d\n%d\n",n,m,k);

    for(int i=0; i<m; i++){
        int city_1 = -1;
        int city_2 = -1;
        while (city_1 == city_2){
            city_1 = rand()%n;
            city_2 = rand()%n;           
        }
        int dis = rand()%10;
        while(dis == 0){
            dis = rand()%10;
        }
        printf("%d %d %d\n", city_1, city_2, dis);
    }
    return 0;
}