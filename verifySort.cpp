//I certify that this program is my own original work. 
//I did not copy any part of this program from any other source. 
//I further certify that I typed each and every line of code in this program.
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

bool isSorted(int arr[],int max)
{
	for(int i=0; i < max;i++)
	{	if(!(arr[i+1] >= arr[i]))
		{
			cout << "ARRAY is UNSORTED with arr[i]:"<<arr[i]<<" and arr[i+1]:  "<<arr[i+1]<<" on line:"<<i <<endl;
			return false;
		}

	}
	return true;

}

int main(int argc,char* argv[])
{
	ofstream out;
	ifstream in;
	const int max=1000000;
	int arr[max];
	int count=0;
	int n;
	
	in.open(argv[1]);
	while(!in.eof())
	{
		in >> n;
		arr[count]=n;
		count++;
	}
	
	count=count-1;
	if(is_sorted(arr,arr+1))
	{	cout<<"SORTED\n";
	}
	else
	{
		cout<<"not\n";
	}
	if(isSorted(arr,count) == true){
		cout << "ARRAY IS SORTED: " << max << endl;
	}
	
	out.close();
	in.close();
	return 0;
}
