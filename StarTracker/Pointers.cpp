#include <iostream>
#include <vector>
#include <array>

using namespace std;

vector <array<double,2> > vect;
vector <array<double,2> > vect2;

int main()
{
    int arr[] = { 3, 5, 6, 7, 9 };
    int *p = arr;
    int (*ptr)[5] = &arr;
    double arrdouble[4][2] = {{1.7,2.3},{7.6,4.5},{12.3,65.22},{2.4,6.5}};
    double (*ptr2)[2] = arrdouble;

    int size = sizeof(arr)/sizeof(arr[0]);
    int size2 = sizeof(arrdouble)/sizeof(arrdouble[0]);

    //printf("p = %p, ptr = %p\n", p, ptr);
    //printf("*p = %d, *ptr = %p\n", p[4], *ptr);

    //printf("sizeof(p) = %lu, sizeof(*p) = %lu\n", sizeof(p), sizeof(*p));
    //printf("sizeof(ptr) = %lu, sizeof(*ptr) = %lu\n", sizeof(ptr), sizeof(*ptr));

    cout << *(arrdouble[0] +1) << endl;
    cout << *(ptr2[1] +0) << endl;
    cout << size << endl;
    cout << size2 << endl;
    cout << sizeof(*ptr)/sizeof(ptr[0]) << endl;

    vect.push_back({2,8});
    vect.push_back({1.2,3.5});
    vect.push_back({6,395});
    cout << vect.size() << endl;
    cout << vect.at(2)[0] << endl << endl;

    copy(vect.begin(),vect.end(),back_inserter(vect2));
    cout << vect2.size() << endl;
    cout << vect.at(1)[0] << endl;
    return 0;
}
