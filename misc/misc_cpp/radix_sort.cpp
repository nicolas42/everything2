// tests show that it's slower than std::sort
// https://github.com/pirataspinhal/algorithms/blob/master/sorting/radix_sort/radix%20sort.cpp

#include <vector>
#include <iostream>
#include <algorithm>    // std::random_shuffle
 
using namespace std;
 
// Get maximum value from array.
int getMax(int arr[], int n)
{
	int max = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > max)
			max = arr[i];
	return max;
}
 
// Count sort of arr[].
void countSort(int arr[], int n, int exp)
{
	// Count[i] array will be counting the number of array values having that 'i' digit at their (exp)th place.  
	int *output = (int*)malloc(n * sizeof(int));
	int i, count[10] = {0};
 
	// Count the number of times each digit occurred at (exp)th place in every input.
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;
 
	// Calculating their cumulative count.
	for (i = 1; i < 10; i++)
		count[i] += count[i-1];
 
	// Inserting values according to the digit '(arr[i] / exp) % 10' fetched into count[(arr[i] / exp) % 10].
	for (i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}
 
	// Assigning the result to the arr pointer of main().
	for (i = 0; i < n; i++)
		arr[i] = output[i];
	
	free(output);
}
 
// Sort arr[] of size n using Radix Sort.
void radixsort(int arr[], int n)
{

	// for (int i = 0; i < n; i++) cout<< arr[i] << " ";  cout << endl;

	int exp, m;
	m = getMax(arr, n);
	// printf("max %d\n", m);
 
	// Calling countSort() for digit at (exp)th place in every input.
	for (exp = 1; m/exp > 0; exp *= 10){
		// printf("%d ", m/exp);
		countSort(arr, n, exp);
		// for (int i = 0; i < n; i++) cout<< arr[i] << " ";  cout << endl;
	}

}
 
// int original_radix_main()
// {
// 	int n, i;
// 	cout<<"\nEnter the number of data element to be sorted: ";
// 	cin>>n;
 
// 	int arr[n];
// 	for(i = 0; i < n; i++)
// 	{
// 		cout<<"Enter element "<<i+1<<": ";
// 		cin>>arr[i];
// 	}
 
// 	radixsort(arr, n);
 
// 	// Printing the sorted data.
// 	cout<<"\nSorted Data ";
// 	for (i = 0; i < n; i++)
// 		cout<<"->"<<arr[i];
// 	return 0;
// }


//   const int n = 25;
//   int arr[n] = {230,23,42,34,23,0,15,3541,43,123,41,34,123,41,234,12,35,1235,4123,41,234,1234,13,41,234};


void radix_sort_demo()
{

	int n = 200000000;
	vector<int> v(n);
	for (int i=0; i<n; i++) v[i] = i;
  	random_shuffle ( v.begin(), v.end() );
	for (int i=0; i<100; i++) cout << v[i] << " ";



	clock_t t;
	int f;
	t = clock();

	int *arr = v.data();
	radixsort(arr, n); 

	t = clock() - t;
	printf ("radix sort took %f seconds\n",((float)t)/CLOCKS_PER_SEC);



	for (int i=0; i<100; i++) cout << v[i] << " ";

}

void std_sort_demo()
{


	int n = 200000000;
	vector<int> v(n);
	for (int i=0; i<n; i++) v[i] = i;
  	random_shuffle ( v.begin(), v.end() );
	for (int i=0; i<100; i++) cout << v[i] << " ";



	clock_t t;
	int f;
	t = clock();

	sort (v.begin(), v.end());

	t = clock() - t;
	printf ("std sort took %f seconds\n", ((float)t)/CLOCKS_PER_SEC);



	for (int i=0; i<100; i++) cout << v[i] << " ";


}


int main()
{
	std_sort_demo();

	radix_sort_demo();

	return 0;
}