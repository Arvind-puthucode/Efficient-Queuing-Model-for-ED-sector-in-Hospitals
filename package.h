#include<bits/stdc++.h>
using namespace std;
struct queue1
{
    char reg_no[20];
    char name[50];
    int age,Time;
    int temperature;
    int blood_pressure;
    int f1,f2,f3;
    int key;
};
int getcritical()
{

    char a[4];
    cout<<"if the patient is critical, if he needs immidiate address enter yes"<<"\n"<< "else enter no\n";
    cin>>a;
    if(strcmp(a,"yes")==0)
    {

        return 0;
    }
    else
    return 1;

}
void getdata(struct queue1 &a)
{
    cout<<"enter your name\n";
    cin.ignore();
    gets(a.name);
    cout<<"enter your restration number\n";
    cin>>a.reg_no;
    cout<<"enter the age\n";
    cin>>a.age;
    cout<<"enter the body temperature\n";
    cin>>a.temperature;
    cout<<"enter the blood pressure\n";
    cin>>a.blood_pressure;
    cout<<"enter the factor 1,factor 2,factor 3\n";
    cin>>a.f1>>a.f2>>a.f3;
    cout<<"enter the key\n";
    cin>>a.key;

}
void equate_objects(queue1 &a,queue1 &b)
{   strcpy(a.name,b.name);
    strcpy(a.reg_no,b.reg_no);
    a.age=b.age;
    a.blood_pressure=b.age;
    a.f1=b.f1;
    a.f2=b.f2;
    a.f3=b.f3;
    a.key=b.key;
    a.Time=b.Time;
}

