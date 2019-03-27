#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

template <typename T>
void quick_sort_recursive(T arr[],int start, int end)
{
    if (start >= end)
        return;
	T pivot = arr[end];
	int left = start, right = end -1;
	while(left < right)//在整個範圍內搜尋比樞紐元值小或大的元素，然後將左側元素與右側元素交換
	{
		while(arr[left] < pivot && left < right)//試圖在左側找到一個比樞紐元更大的元素
			left++;
			
		while(arr[right] >= pivot && left < right)//試圖在右側找到一個比樞紐元更小的元素
			right--;			

		std::swap(arr[left],arr[right]);
	}

	if(arr[left] >= arr[end])
		std::swap(arr[left],arr[end]);
	else
		left++;

	quick_sort_recursive(arr,start,left - 1);
	quick_sort_recursive(arr,left + 1 ,end);	
	
}

template <typename T>//整數或浮點數皆可使用,若要使用物件(class)時必須設定"小於"(<)、"大於"(>)、"不小於"(>=)的運算子功能
void quick_sort(T arr[], int len) {
    quick_sort_recursive(arr, 0, len - 1);
}

template <typename T>
void bubble_sort(T arr[],int len)
{
	for(int i = 0;i < len; i++ )
	{		
		int cmp = i;
		for(int j = i + 1;j < len; j++)
		{
			if(arr[j] < arr[cmp])
			{
				cmp = j;
			}		
		}	
		if(cmp != i)
		{
			swap(arr[cmp], arr [i]);		
		}
	}
}


void max_heapify(int arr[],int start,int end)
{
	// 建立父節點指標和子節點指標
	int dad = start;
	int son = dad * 2 +1;
	while(son <= end)// 若子節點指標在範圍內才做比較
	{
		if(son + 1 <= end && arr[son] < arr[son + 1])// 先比較兩個子節點大小，選擇最大的
		{
			son++;
		}
		if(arr[dad] > arr[son])// 如果父節點大於子節點代表調整完畢，直接跳出函數
			return;
		else// 否則交換父子內容再繼續子節點和孫節點比較
		{
			swap(arr[dad],arr[son]);
			dad = son;
			son = dad * 2 +1;		
		}	
	}
}

void heap_sort(int arr[],int len)
{
	// 初始化，i從最後一個父節點開始調整
	for(int i = len / 2 - 1; i >= 0; i--)
	{
		max_heapify(arr,i,len -1);	
	}
	// 先將第一個元素和已经排好的元素前一位做交換，再從新調整(刚调整的元素之前的元素)，直到排序完畢
	for(int i = len - 1; i > 0; i--)
	{
		swap(arr[0],arr[i]);
		max_heapify(arr, 0, i - 1);
	}

}


int main (int argc,char *argv[])
{
	int arr[] = { 3, 5, 3, 0, 8, 6, 1, 5, 8, 6, 2, 4, 9, 4, 7, 0, 1, 8, 9, 7, 3, 1, 2, 5, 9, 7, 4, 0, 2, 6 };
    int len = (int) sizeof(arr) / sizeof(*arr);
	
	//quick_sort(arr,len);
	heap_sort(arr,len);
	//bubble_sort(arr,len);
	vector <int> b;
	b.insert(b.begin(), arr, arr + len);
	for_each(b.begin(),b.end(),[](int a){ cout << a << endl;});

	auto it = max_element(b.begin(),b.end());
	int x;
	cin >> x;
}