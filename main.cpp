#include <iostream>
#include"package.h"
#include"heap.h"
#include <fstream>
using namespace std;
queue1 *b=new queue1[20];
queue1 *red=new queue1[5];
queue1 *yellow=new queue1[5];
queue1 *green=new queue1[5];
void read_countfile(int &tr,int &ty,int &tg,int &ngquit,int&nyquit)
{   ifstream fin("zonescount.dat",ios::binary);
    if(fin)
    {   while(!fin.eof())
        {   fin.read((char*)&tr,sizeof(int));
            fin.read((char*)&ty,sizeof(int));
            fin.read((char*)&tg,sizeof(int));
            fin.read((char*)&ngquit,sizeof(int));
            fin.read((char*)&nyquit,sizeof(int));
        }
        cout<<"tr is:"<<tr<<","<<ty<<","<<tg<<","<<ngquit<<","<<nyquit;
        fin.close();
    }
}
void write_countfile(int tr,int ty,int tg,int ngquit,int nyquit)
{   ofstream fout("zonescount.dat",ios::binary|ios::app);
    fout.write((char*)&tr,sizeof(tr));
    fout.write((char*)&ty,sizeof(ty));
    fout.write((char*)&tg,sizeof(tg));
    fout.write((char*)&ngquit,sizeof(tg));
    fout.write((char*)&nyquit,sizeof(tg));
    fout.close();
}
void read_files(int &r,int &y,int &g,int &bq,int &ngwaiting,int &nywaiting)
{   queue1 E;
    ifstream fin1("red.dat",ios::binary);
    if(fin1)
    {
        while(fin1.read((char*)&E,sizeof(E)))
        {   red[r]=E;
            r++;
        }
        fin1.close();
    }
    ifstream fin2("yellow.dat",ios::binary);
    if(fin2)
    {   while(fin2.read((char*)&E,sizeof(E)))
        {   yellow[y]=E;
        y++;
        }
        fin2.close();
    }
    ifstream fin3("green.dat",ios::binary);
    if(fin3)
    {
        while(fin3.read((char*)&E,sizeof(E)))
        {   green[g]=E;
        g++;
        }
        fin3.close();
    }
    ifstream fin4("bqueue.dat",ios::binary);
    if(fin4)
    {   while(fin4.read((char*)&E,sizeof(E)))
        {   if(b[bq].key<=10)
                ngwaiting++;
            else
                nywaiting++;
            b[bq]=E;
            bq++;
        }
        fin4.close();
    }
}
void write_files(int r,int y,int g,int bq)
{   int X=0,Y=0,Z=0,W=0;
    if(r!=0)
    {   ofstream fout1("red.dat",ios::binary);
        while(X<r)
        {   fout1.write((char*)&red[X],sizeof(queue1));
            X++;
        }
        if(r!=0)
            fout1.close();
    }
    if(y!=0)
    {   ofstream fout2("yellow.dat",ios::binary);
        while(Y<y)
        {   fout2.write((char*)&yellow[Y],sizeof(queue1));
            Y++;
        }
        if(y!=0)
            fout2.close();
    }
    if(g!=0)
    {   ofstream fout3("green.dat",ios::binary);
        while(Z<g)
        {   fout3.write((char*)&green[Z],sizeof(queue1));
            Z++;
        }
        fout3.close();
    }
    if(bq!=0)
    {   ofstream fout4("bqueue.dat",ios::binary);
        while(W<bq)
        {   fout4.write((char*)&b[Z],sizeof(queue1));
            W++;
        }
        fout4.close();
    }
}
int releasered(int t,int tr,int &N)
{   ifstream fin("red.dat",ios::binary);
    if(fin)
    {   int n=0;
        queue1 E;
        while(N>0&&fin.read((char*)&E,sizeof(E)))
        {   if(t-E.Time>=tr)
            {   red=Delete(red,0,N);
                n++;
                N--;
            }
        }
        fin.close();
        return n;
    }
    return 0;
}
int releasegreen(int t,int tg,int &N)
{   ifstream fin("green.dat",ios::binary|ios::in);
    if(fin)
    {   int n=0;
        queue1 E;
        while(N>0&&fin.read((char*)&E,sizeof(E)))
        {   if(t-E.Time>=tg)
            {   green=Delete(green,0,N);
                n++;
                N--;
            }
        }
        fin.close();
        return n;
    }
    return 0;
}
int releaseyellow(int t,int ty,int &N)
{
    ifstream fin("yellow.dat",ios::binary);
    if(fin)
    {   int n=0;
        queue1 E;
        while(N>0&&fin.read((char*)&E,sizeof(E)))
        {   if(t-E.Time>=ty)
            {   red=Delete(red,0,N);
                n++;
                N--;
            }
        }
        fin.close();
        return n;
    }
    return 0;
}
void rebuildgreen(int n,int &N,int &bsize)//n-> no of patients to take inside,N-size of green,bsize size of barray
{   int temp=0,N1=N,temp1=0;
    while(temp<n&&temp1<bsize)
        {   if(b[temp1].key<10)
            {   equate_objects(green[N++],b[temp1]);
                b=Delete(b,temp1,bsize);
                bsize--;
                n--;
                temp++;

            }
            temp1++;

        }
        buildHeap(green,N);
}
void rebuildyellow(int n,int &N,int &bsize)
{
    int N1=N,temp=0,temp1=0;
    while(temp<n&&temp1<bsize)
    {
        if(b[temp1].key>10)
        {
            equate_objects(yellow[N++],b[temp1]);
            b=Delete(b,temp1,bsize);
            bsize--;
            n--;
            temp++;
        }
        temp1++;
    }
    buildHeap(yellow,N);
}
int main()
{
    int y=0,d=0,c=0,x=0,gc,z,z1,R,exit,p,time_now=0,nquit=0,tg=2,ngwaiting=0,time_prev,tr=5,a1,a2,a3,ty=3,quityellow=0,nywaiting=0;
    int totyellow=0,totred=0,totgreen=0;
    time_prev=0;
    //cout<<"hi";
    read_files(y,x,d,c,ngwaiting,nywaiting);
    //cout<<"hi2"<<endl;
    read_countfile(totred,totyellow,totgreen,nquit,quityellow);
    //cout<<"h3"<<endl;
    while(1)
    {
        cout<<"if you want to exit enter 0 else 1\n";
        cin>>exit;
        if(exit==0)
        {
            break;
        }
        else
        {
            cout<<"\n enter the time now:";
            cin>>time_now;
            a1=releasered(time_now,tr,y);
            //totred-=a1;
            a2=releasegreen(time_now,tg,d);
            nquit+=a2;
            printHeap(green,d);
            //totgreen-=a2;
            a3=releaseyellow(time_now,ty,x);
            printHeap(yellow,x);
            quityellow+=a3;
            //totyellow-=a3;
            rebuildgreen(a2,d,c);
            rebuildyellow(a3,x,c);
            int gc=getcritical();
            if(gc==0)
            {   if(y==5)
                    cout<<"Red zone full:Go to another place Quick!";
                else
                {   cout<<"hello red\n";
                    getdata(b[c]);
                    b[c].Time=time_now;
                    c++;
                    equate_objects(red[y++],b[c-1]);
                    totred++;
                    Delete(b,c-2,c-1);
                    c--;
                    //cout<<red[y-1]<<"\n";
                    buildHeap(red,y);
                }
            }
            else
            {   getdata(b[c]);
                b[c].Time=time_now;
                c++;
                if(b[c-1].key>10)
                {
                    //quityellow=time_now/ty;
                    cout<<"yellow\n";
                    totyellow++;
                    if(x<5)
                    {   cout<<"entering yellow:"<<endl;
                        equate_objects(yellow[x++],b[c-1]);
                        buildHeap(yellow,x);
                        printHeap(yellow,x);
                        b=Delete(b,c-1,c);
                        cout<<"check yellow again:";
                        printHeap(yellow,x);

                        c--;
                    }
                    else
                    {
                        R=(5-y)/(1-(ty/tr)+((ty*totred)/time_now));
                        if(R>0)
                        {
                            totred++;
                            totyellow--;
                            equate_objects(red[y++],b[c-1]);
                            buildHeap(red,y);
                            b=Delete(b,c-1,c);
                        }
                        else
                        {

                            if(nywaiting>1.5*quityellow)
                            {
                                cout<<"\n Queue is quite long.Take to another hospital:"<<endl;
                                Delete(b,c-1,c);
                                c--;
                                totyellow--;
                            }
                            else
                            {
                                nywaiting++;
                                //let him stay in the queue

                            }
                        }

                    }

                }
                else
                {
                    cout<<"green\n";
                    totgreen++;
                    if(d<5)
                    {
                        equate_objects(green[d++],b[c-1]);
                        buildHeap(green,d);
                        b=Delete(b,c-1,c);
                        //Delete(b,c-1,c-2);
                        c--;
                    }
                    else
                    {
                        z1=(5-x)/(1-(tg/ty)+((tg*totyellow)/time_now));
                        cout<<"upradation check:"<<z1<<endl;
                        if(z1>0)
                        {

                            equate_objects(yellow[x],b[c-1]);
                            x++;
                            totyellow++;
                            totgreen--;
                            buildHeap(yellow,x);
                            printHeap(yellow,x);
                            b=Delete(b,c-1,c);
                            c--;
                        }
                        else
                        {
                            if(ngwaiting>2*nquit)
                            {
                                cout<<"\n Queue is quite long.Take to another hospital:"<<endl;
                                Delete(b,c-1,c);
                                c--;
                                totgreen--;
                            }

                            else
                            {
                                ngwaiting++;
                                //let him stay in the queue

                            }
                        }
                    }
                }
            }

        }

        do{cout<<"if you want to print red queue enter 1\n";
        cout<<"else if you want to print green queue, enter 2\n";
        cout<<"else if you want to print yellow queue enter 3\n";
        cout<<"else if you want to print line queue enter 4\n";
        cout<<"else enter 0\n";
        cin>>p;
        if(p==1)
        {
            printHeap(red,y);
        }
        else if(p==2)
        {

            printHeap(green,d);
        }
        else if(p==3)
        {
            cout<<"y heap x:is"<<x<<endl;
            printHeap(yellow,5);

        }
        else if(p==4)
        {

            printHeap(b,c);

        }
        }while(p!=0);


        write_files(y,x,d,c);
        write_countfile(totred,totyellow,totgreen,nquit,quityellow);
    }

}

