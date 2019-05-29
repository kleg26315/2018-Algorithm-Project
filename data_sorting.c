#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_INDEX 140000
#define MAX_LINE        300
#define TRUE            1
#define FALSE           0
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

typedef struct word_info {
	char id[100];
	char name[300];
	char year[100];
	char genre[100];
} word_info;

typedef word_info* element;
word_info list[MAX_INDEX];
word_info sorted[MAX_INDEX];
word_info* SSap = list;
word_info list2[MAX_INDEX];
word_info list3[MAX_INDEX];
word_info unsorted[MAX_INDEX];
word_info output[MAX_INDEX];

int l_count = 0;

typedef struct {
	element heap[MAX_INDEX + 1];
	int heap_size;
}heapType;

int getMax(word_info list[], int size)
{
	int mx = atoi(list[1].year);
	for (int i = 1; i < size; i++)
		if (atoi(list[i].year) > mx)
			mx = atoi(list[i].year);
	return mx;
}

void countSort(word_info list[], int size, int exp)
{
	int i = 0;
	int count[100] = { 0 };

	for (i = 0; i < size; i++)
		count[(atoi(list[i].year) / exp) % 10]++;

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (i = size - 1; i >= 0; i--)
	{
		output[count[(atoi(list[i].year) / exp) % 10] - 1] = list[i];
		count[(atoi(list[i].year) / exp) % 10]--;
	}

	for (i = 0; i < size; i++)
		list[i] = output[i];
}

void radixsort(word_info list[], int size)
{
	int m = getMax(list, size);
	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(list, size, exp);
}

void insertion_sort_name(word_info list[MAX_INDEX], int size)
{
	int i = 0, j = 0;
	word_info temp;

	for (i = 1; i < size; i++)
	{
		temp = list[i];
		for (j = i - 1; j >= 0 && strcmp(list[j].name, temp.name) > 0; j--)
		{

			list[j + 1] = list[j];
		}
		list[j + 1] = temp;
	}
}

void insertion_sort_year(word_info list[MAX_INDEX], int size)
{
	int i = 0, j = 0;
	word_info temp;

	for (i = 1; i < size; i++)
	{
		temp = list[i];
		for (j = i - 1; j >= 0 && strcmp(list[j].year, temp.year) > 0; j--)
		{

			list[j + 1] = list[j];
		}
		list[j + 1] = temp;
	}
}

int partition_year(word_info list[], int left, int right)
{
	char pivot[200];

	int low, high;
	word_info temp;

	low = left;
	high = right + 1;
	strcpy(pivot, list[left].year); 	/* 피벗 설정 */
	do {
		do
			low++;
		/* 왼쪽 리스트에서 피벗보다 큰 레코드 선택 */
		while (low <= right && strcmp(list[low].year, pivot) < 0);
		do
			high--;
		/* 오른쪽 리스트에서 피벗보다 작은 레코드 선택 */
		while (high >= left && strcmp(list[high].year, pivot) > 0);
		if (low < high) {
			SWAP(list[low], list[high], temp);
		}/* 선택된 두 레코드 교환 */
	} while (low < high);	  /* 인덱스 i,j가 엇갈리지 않는 한 반복 */
	SWAP(list[left], list[high], temp); /* 인텍스 j가 가리키는 레코드와 피벗 교환 */
	return high;
}


void quick_sort_year(word_info list[], int left, int right)
{
	if (left < right) {     /* 리스트에 2개 이상의 레코드가 있을 경우 */
		int q = partition_year(list, left, right);
		// print(list, 9);
		quick_sort_year(list, left, q - 1);         /* 왼쪽 부분리스트를 퀵정렬 */
		quick_sort_year(list, q + 1, right);       /* 오른쪽 부분리스트를 퀵정렬 */
	}
}

int partition_name(word_info list[], int left, int right)
{
	char pivot[200];

	int low, high;
	word_info temp;

	low = left;
	high = right + 1;
	strcpy(pivot, list[left].name); 	/* 피벗 설정 */
	do {
		do
			low++;
		/* 왼쪽 리스트에서 피벗보다 큰 레코드 선택 */
		while (low <= right && strcmp(list[low].name, pivot) < 0);
		do
			high--;
		/* 오른쪽 리스트에서 피벗보다 작은 레코드 선택 */
		while (high >= left && strcmp(list[high].name, pivot) > 0);
		if (low < high) {
			SWAP(list[low], list[high], temp);
		}/* 선택된 두 레코드 교환 */
	} while (low < high);	  /* 인덱스 i,j가 엇갈리지 않는 한 반복 */
	SWAP(list[left], list[high], temp); /* 인텍스 j가 가리키는 레코드와 피벗 교환 */
	return high;
}


void quick_sort_name(word_info list[], int left, int right)
{
	int l;
	if (left < right) {     /* 리스트에 2개 이상의 레코드가 있을 경우 */
		int q = partition_name(list, left, right);
		// print(list, 9);
		quick_sort_name(list, left, q - 1);         /* 왼쪽 부분리스트를 퀵정렬 */
		quick_sort_name(list, q + 1, right);       /* 오른쪽 부분리스트를 퀵정렬 */
	}

}

void merge_name(word_info list[], int left, int mid, int right)
{
	int i, j, k, l;
	i = left; j = mid + 1; k = left;
	while (i <= mid && j <= right) {
		if (strcmp(list[i].name, list[j].name) > 0)
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}
	if (i > mid)
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];
	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}

void merge_sort_name(word_info list[], int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;
		merge_sort_name(list, left, mid);
		merge_sort_name(list, mid + 1, right);
		merge_name(list, left, mid, right);
	}
}

void merge_year(word_info list[], int left, int mid, int right)
{
	int i, j, k, l;
	i = left; j = mid + 1; k = left;
	while (i <= mid && j <= right) {
		if (strcmp(list[i].year, list[j].year) < 0)
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}
	if (i > mid)
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];
	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}

void merge_sort_year(word_info list[], int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;
		merge_sort_year(list, left, mid);
		merge_sort_year(list, mid + 1, right);
		merge_year(list, left, mid, right);
	}
}

void init(heapType * h)
{
	h->heap_size = 0;
}

void insert_max_heap(heapType * h, element item)
{
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && strcmp(item->year, h->heap[i / 2]->year) < 0)
	{
		h->heap[i] = h->heap[i / 2];
		i = i / 2;
	}                   // 부모 노드와 비교
	h->heap[i] = item;  // 새로운 노드를 삽입
}

void name_insert_max_heap(heapType * h, element item)
{
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && strcmp(item->name, h->heap[i / 2]->name) < 0)
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}                   // 부모 노드와 비교
	h->heap[i] = item;  // 새로운 노드를 삽입
}

element delete_max_heap(heapType * h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		if ((child < h->heap_size) && strcmp(h->heap[child]->year, h->heap[child + 1]->year) > 0)
			child++;
		if (strcmp(temp->year, h->heap[child]->year) <= 0) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
element name_delete_max_heap(heapType * h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		if ((child < h->heap_size) && strcmp(h->heap[child]->name, h->heap[child + 1]->name) > 0)
			child++;
		if (strcmp(temp->name, h->heap[child]->name) <= 0) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

int main(int argc, char* argv[])
{
	FILE* fp;
	heapType heap;
	int i;
	char buffer[300];
	char buffer2[300];
	char title[300];
	char* storge1[20];
	char* storge2[20];
	char* token;
	int t_count = 0;
	int sel = 0;
	int sel2 = 0;
	int input_amount = 0;
	double start, end;

	if ((fp = fopen("c://movies.txt", "r")) == NULL) {
		fprintf(stderr, "파일을 열 수 없습니다.\n");
		exit(1);
	}


	while (!feof(fp) != NULL) {
		fgets(buffer, sizeof(buffer), fp);
		storge1[0] = " ";	//id저장
		strcpy(title, " "); //title 저장
		storge1[2] = " ";   //년도 저장
		storge1[3] = " ";   //장르 저장

		if (l_count == 0)
		{
			l_count++;
		}
		else
		{
			strcpy(buffer2, buffer);
			token = strtok(buffer, "\"");
			if (strcmp(token, buffer2) == 0) {			//큰따옴표로 .안. 짤렸을때
				token = strtok(buffer2, ",");
				storge1[0] = token;
				while (token != NULL)			//제목에 괄호 하나도 없을시 t_count =4, 제목에 괄호 하나라도 있을 시 t_count=6,8*
				{
					token = strtok(NULL, "(),\n");
					t_count++;
					if (t_count == 1)
						storge2[0] = token;		//Revolution~Utena,	toy stroy
					else if (t_count == 2)
						storge2[1] = token;		//a.k.a Movie	//19995
					else if (t_count == 3)
						storge2[2] = token;		//" ", 장르
					else if (t_count == 4)
						storge2[3] = token;		//Shoujo, t_count==5 " " t_count=6 "1999" t_count=7 "장르"
					else if (t_count == 5)
						storge2[4] = token;
					else if (t_count == 6)
						storge2[5] = token;
					else if (t_count == 7)
						storge2[6] = token;
					else if (t_count == 8)
						storge2[7] = token;
					else if (t_count == 9)
						storge2[8] = token;
					else if (t_count == 10)
						storge2[9] = token;
				}
				if (t_count == 4)
				{
					strcpy(title, storge2[0]);
					storge1[2] = storge2[1];	//년도삽입
					storge1[3] = storge2[2];	//장르삽입
				}
				else if (t_count == 5)
				{
					strcpy(title, storge2[0]);
					storge1[2] = storge2[1];
					storge1[3] = storge2[3];
				}
				else if (t_count == 6)
				{
					strcat(storge2[0], storge2[1]);
					strcat(storge2[0], storge2[2]);
					strcpy(title, storge2[0]);
					storge1[2] = storge2[3];
					storge1[3] = storge2[4];
				}
				else if (t_count == 8)
				{
					strcat(storge2[0], storge2[1]);
					strcat(storge2[0], storge2[2]);
					strcat(storge2[0], storge2[3]);
					strcat(storge2[0], storge2[4]);
					strcpy(title, storge2[0]);
					storge1[2] = storge2[5];
					storge1[3] = storge2[6];
				}
				strcpy(list[l_count].id, storge1[0]);
				strcpy(list[l_count].name, title);
				strcpy(list[l_count].year, storge1[2]);
				strcpy(list[l_count].genre, storge1[3]);

				if (t_count == 3)
					l_count = l_count - 1;

				if (!strncmp(list[l_count].year, "19", 2) || !strncmp(list[l_count].year, "20", 2))
				{
				}
				else
					l_count = l_count - 1;

				t_count = 0;
			}
			else {							//큰따옴표로 짤렸을때
				/*l_count = l_count - 1;*/
				token = strtok(buffer2, ",");
				storge1[0] = token;
				while (token != NULL)			//제목에 괄호 하나도 없을시 t_count =4, 제목에 괄호 하나라도 있을 시 t_count=6,8*
				{
					token = strtok(NULL, "(),\n\\\"");
					t_count++;
					if (t_count == 1)
						storge2[0] = token;		//title
					else if (t_count == 2)
						storge2[1] = token;		//the
					else if (t_count == 3)
						storge2[2] = token;		//괄호 안에 제목
					else if (t_count == 4)
						storge2[3] = token;		//" "
					else if (t_count == 5)
						storge2[4] = token;		//년도
					else if (t_count == 6)
						storge2[5] = token;		//장르
				}
				if (t_count == 5)			//여기서부터 하자 순서확인해서.
				{
					strcat(storge2[0], storge2[1]);
					strcpy(title, storge2[0]);
					storge1[2] = storge2[2];	//년도삽입
					storge1[3] = storge2[3];	//장르삽입
				}
				else if (t_count == 7)
				{
					strcat(storge2[0], storge2[1]);
					strcat(storge2[0], storge2[2]);
					strcat(storge2[0], storge2[3]);
					strcpy(title, storge2[0]);
					storge1[2] = storge2[4];
					storge1[3] = storge2[5];
				}
				strcpy(list[l_count].id, storge1[0]);
				strcpy(list[l_count].name, title);
				strcpy(list[l_count].year, storge1[2]);
				strcpy(list[l_count].genre, storge1[3]);

				if (t_count == 3)
					l_count = l_count - 1;

				if (!strncmp(list[l_count].year, "19", 2) || !strncmp(list[l_count].year, "20", 2))
				{
				}
				else
					l_count = l_count - 1;

				t_count = 0;
			}
			/*if (l_count == 501)
				break;
			if (l_count == 1001)
				break;
			if (l_count == 5001)
				break;
			if (l_count == 10001)
				break;
			if (l_count == 20001)
				break;*/
			l_count++;
		}


	}
	while (1) {
		printf("=====정렬프로그램입니다=====\n");
		printf("     1. 모든 데이터 \n");
		printf("     2. 20,000개\n");
		printf("     3. 10,000개\n");
		printf("     4. 5,000개\n");
		printf("     5. 1,000개\n");
		printf("     6. 500개\n");
		printf("     0. 종료\n");
		printf("개수를 선택하십시오 ->");
		scanf("%d", &sel);
		if (!sel) break;
		switch (sel)
		{
		case 1:
			input_amount = l_count;
			break;
		case 2:
			input_amount = 20000;
			break;
		case 3:
			input_amount = 10000;
			break;
		case 4:
			input_amount = 5000;
			break;
		case 5:
			input_amount = 1000;
			break;
		case 6:
			input_amount = 500;
			break;
		default:
			printf("잘못 입력하셨습니다. \n");
			continue;
		}
		for (i = 1; i < input_amount + 1; i++) {
			strcpy(unsorted[0].id, "");
			strcpy(unsorted[0].name, "");
			strcpy(unsorted[0].year, "");
			strcpy(unsorted[0].genre, "");
			unsorted[i] = list[i];
		}
		for (i = 1; i < input_amount + 1; i++) {
			strcpy(list2[0].id, "");
			strcpy(list2[0].name, "");
			strcpy(list2[0].year, "");
			strcpy(list2[0].genre, "");
			list2[i] = list[i];
		}
		for (i = 1; i < input_amount + 1; i++) {
			strcpy(list3[0].id, "");
			strcpy(list3[0].name, "");
			strcpy(list3[0].year, "");
			strcpy(list3[0].genre, "");
			list3[i] = list[i];
		}
		start = 0;
		end = 0;
		printf("=====정렬프로그램입니다=====\n");
		printf("     1. 삽입 정렬 \n");
		printf("     2. 합병 정렬\n");
		printf("     3. 힙 정렬\n");
		printf("     4. 퀵 정렬\n");
		printf("     5. 기수 정렬\n");
		printf("     0. 종료\n");
		printf("정렬을 선택하십시오 ->");
		scanf("%d", &sel2);
		if (!sel2) break;
		start = (double)clock();
		switch (sel2)
		{
		case 1:
			insertion_sort_name(unsorted, input_amount);
			insertion_sort_year(unsorted, input_amount);
			for (i = 0; i < input_amount; i++)
			{
				printf("%-10s %-70s %-10s %-10s \n", unsorted[i].id, unsorted[i].name, unsorted[i].year, unsorted[i].genre);
			}
			printf("삽입정렬 ");
			break;
		case 2:
			merge_sort_name(unsorted, 0, input_amount);
			merge_sort_year(unsorted, 0, input_amount);
			for (i = 1; i < input_amount + 1; i++)
			{
				printf("%-10s %-70s %-10s %-10s \n", unsorted[i].id, unsorted[i].name, unsorted[i].year, unsorted[i].genre);
			}
			printf("합병정렬 ");
			break;
		case 3:
			SSap = list2;
			init(&heap);
			for (i = 1; i < input_amount + 1; i++)
			{
				name_insert_max_heap(&heap, SSap);
				SSap++;
			}
			word_info* temp;
			for (i = 0; i < input_amount + 1; i++)
			{
				temp = name_delete_max_heap(&heap);
				strcpy(list3[i].id, temp->id);
				strcpy(list3[i].name, temp->name);
				strcpy(list3[i].year, temp->year);
				strcpy(list3[i].genre, temp->genre);
			}
			SSap = list3;
			init(&heap);
			for (i = 1; i < input_amount + 1; i++)
			{
				insert_max_heap(&heap, SSap);
				SSap++;
			}
			word_info* temp2;
			for (i = 1; i < input_amount + 1; i++)
			{
				temp2 = delete_max_heap(&heap);
				printf("%-10s %-70s %-10s %-10s\n", temp2->id, temp2->name, temp2->year, temp2->genre);
			}
			printf("힙정렬 ");
			break;
		case 4:
			quick_sort_name(unsorted, 0, input_amount);
			quick_sort_year(unsorted, 0, input_amount);
			for (i = 1; i < input_amount + 1; i++)
			{
				printf("%-10s %-70s %-10s %-10s \n", unsorted[i].id, unsorted[i].name, unsorted[i].year, unsorted[i].genre);
			}
			printf("퀵정렬 ");
			break;
		case 5:
			radixsort(unsorted, input_amount);
			for (i = 1; i < input_amount; i++)
			{
				printf("%-10s %-70s %-10s %-10s \n", unsorted[i].id, unsorted[i].name, unsorted[i].year, unsorted[i].genre);
			}
			printf("기수정렬 ");
			break;
		default:
			printf("잘못 입력하셨습니다. \n");
			continue;
		}
		end = (double)clock();

		printf("수행시간 : %lf(sec)\n\n", (end - start) / 1000);
	}

}

