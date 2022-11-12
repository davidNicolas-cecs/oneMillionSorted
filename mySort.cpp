//David Nicolas Garcia
#include<thread>
#include<iostream>
#include<fstream>
using namespace std;
void merge(int *arr1,int *arr2,int max,int arr3[])
{
	int i=0;
	int j=0;
	int k=0;
	while(i < max && j < max) // MAIN LOOP
	{	if(arr1[i] < arr2[j])
		{	arr3[k++]=arr1[i++];
		}
		else
		{
			arr3[k++] = arr2[j++];
		}
	}
	while (i < max)
	{	arr3[k++]=arr1[i++];
	}	
	while(j < max)
	{	arr3[k++]=arr2[j++];
	}
}
void insertionSort(int *arr,int max)
{
	int temp;
	int j;
	cout<< "Starting Array Insertion sort with "<<max<<" items\n";		
	for(int i = 1; i<max;i++)
	{
		temp=arr[i];
		j=i-1;
		while(temp<arr[j] && j >= 0)
		{
			arr[j+1]=arr[j];
			j=j-1;
		}
		arr[j+1]=temp;

	}
	cout << "Ending Insertion sort\n";
}

int main(int argc,char* argv[])
{
	if(argc< 3)
	{
		cout << "Please include input and output filename\n";
		cout << "Example:\n 	mySort numbers.txt mySorted.txt\n";
		exit(0);
	}
	const int max = 1000000;
	ofstream out;
	ifstream in;
	int arr[max];//numbers.txt array goes here
	int n;
	int count=0;
	in.open(argv[1]);
	while(!in.eof())
	{
		in >> n;
	       	arr[count]=n;
		count++;	
	}
	//one array will be from 0-125000;125000-250000;250000+375000;375000-500000;500000-625000;
	//		625000-750000;750000-875000;875000-1000000
	//creating 8 arrays to be independently sorted
	int x = max/8; //x/8 1000000 / 125000
	int tmp = 0;
	thread thread0(insertionSort,&arr[tmp],x);//0-125000
	thread thread1(insertionSort,&arr[tmp += x],x);//125000-25000   
	thread thread2(insertionSort,&arr[tmp += x],x);//25000-375000
	thread thread3(insertionSort,&arr[tmp += x],x);//37500-50000
	thread thread4(insertionSort,&arr[tmp += x],x);//50000-62500
	thread thread5(insertionSort,&arr[tmp += x],x);//625000-725000-
	thread thread6(insertionSort,&arr[tmp += x],x);//72500-82500
	thread thread7(insertionSort,&arr[tmp += x],x);//82500-100000
	
	thread0.join();
	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();
	thread5.join();
	thread6.join();
	thread7.join();	
	//now we first merge them together
	int tmparr1[x*2];//2500000
	int tmparr2[x*2];
	int tmparr3[x*2];
	int tmparr4[x*2];

	merge(&arr[0],&arr[125000],125000,tmparr1);//first two sorted 0 -250000 now sort 
	merge(&arr[250000],&arr[375000],125000,tmparr2);
	merge(&arr[500000],&arr[625000],125000,tmparr3);
	merge(&arr[750000],&arr[875000],125000,tmparr4);
		
	int tmparr5[x*4];
	int tmparr6[x*4];
	merge(&tmparr1[0],&tmparr2[0],250000,tmparr5);
	merge(&tmparr3[0],&tmparr4[0],250000,tmparr6);

	int finalArr[x*8];
	merge(&tmparr5[0],&tmparr6[0],500000,finalArr);

	out.open(argv[2], ios::out | ios::trunc);
	for(int i =0; i < count-1; i++) //count -1
		out << finalArr[i] << endl;

	out.close();
	in.close();
	return 0;

}
