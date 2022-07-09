#include <iostream>
using namespace std;


double npv(double r,double tnum,int t) //净现因子
{ 
    return tnum / pow(1 + r, t);
}
double irr() //内部回报率
{
    return 0;
}



int main()
{
    double project1[] = { 10000,10000,10000,20000,100000 };
    double project2[] = { 200000,200000,200000,200000,300000 };
    double project3[] = { 30000,30000 ,30000 ,30000 ,30000 };
    double project4[] = { 30000 ,30000 ,30000 ,30000 ,75000 };
    double npv1 = -100000; //净现值
    double npv2 = -1000000;
    double npv3 = -100000;
    double npv4 = -120000;
    
    for (int i = 0; i < 5; i++) {
        npv1 += npv(0.08, project1[i], i + 1);
        npv2 += npv(0.08, project2[i], i + 1);
        npv3 += npv(0.08, project3[i], i + 1);
        npv4 += npv(0.08, project4[i], i + 1);
    }
    cout << "净现值(贴现率r=8%):" << endl;
    cout << "  项目1:" << npv1 << endl;
    cout << "  项目2:" << npv2 << endl;
    cout << "  项目3:" << npv3 << endl;
    cout << "  项目4:" << npv4 << endl;

    npv1 = -100000;
    npv2 = -1000000;
    npv3 = -100000;
    npv4 = -120000;
    for (int i = 0; i < 5; i++) {
        npv1 += npv(0.12, project1[i], i + 1);
        npv2 += npv(0.12, project2[i], i + 1);
        npv3 += npv(0.12, project3[i], i + 1);
        npv4 += npv(0.12, project4[i], i + 1);
    }
    cout << "净现值(贴现率r=12%):" << endl;
    cout << "  项目1:" << npv1 << endl;
    cout << "  项目2:" << npv2 << endl;
    cout << "  项目3:" << npv3 << endl;
    cout << "  项目4:" << npv4 << endl;


    npv1 = -100000;
    npv2 = -1000000;
    npv3 = -100000;
    npv4 = -120000;
    double irr1=0;
    double irr2=0;
    double irr3=0;
    double irr4=0;
    
    cout << "内部回报率:" << endl;

    double npv0 = 0;
   
    for (int r = 0.01;; r+=0.01){
        for (int i = 0; i < 5; i++) {
            npv0 += npv((r/100), project1[i], i + 1);
        }
        if (npv0<1) {
            irr1 = r;
            break;
        }
    }
    cout << irr1 << "%";

    return 0;
}
