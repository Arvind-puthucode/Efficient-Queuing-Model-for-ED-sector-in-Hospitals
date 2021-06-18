#include<bits/stdc++.h>
using namespace std;
void heapify(struct queue1 arr[], int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l].key > arr[largest].key)
        largest = l;
    if (r < n && arr[r].key > arr[largest].key)
        largest = r;
    if (largest != i) {
        swap(arr[i].key, arr[largest].key);

        //cout<<arr[i].key<<" "<<arr[largest].key<<"\n";
        heapify(arr, n, largest);
    }
}
void buildHeap(struct queue1 arr[], int n)
{
    int startIdx = (n / 2) - 1;
    for (int i = startIdx; i >= 0; i--)
    {
        heapify(arr, n, i);
    }
}
void printHeap(struct queue1 arr[], int n)
{
    cout << "Array representation of Heap is:\n";

    for (int i = 0; i < n; ++i)
        cout << arr[i].key << " ";
    cout << "\n";
}
queue1* Delete(queue1 arr[],int i,int n)
{   if(n>0)
    {   int k=0;
        for(int j=i;j<n-1;j++)
        {   if(j!=i)
            {   arr[i+1]=arr[i];
            }
        }
        return arr;

        //delete []newdata;
    }
}
