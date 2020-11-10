
#include <stdio.h>

int InputArray(int process, int resource, int arr[10][10])
{
	for (int i = 0; i < process; i++)
	{
		printf("\nFor process %d : ", i + 1);
		for (int j = 0; j < resource; j++)
			scanf("%d", &arr[i][j]);
	}
	
}

int PrintArray(int process, int resource, int arr[10][10])
{
	for (int i = 0; i < process; i++)
	{
		for (int j = 0; j < resource; j++)
			{
				printf("%d  ", arr[i][j]);
			}
			printf("\n");
		}
}

int main()
{
	int Max[10][10], need[10][10], alloc[10][10], avail[10], completed[10], safeSequence[10];//순서
	int p, r, i, j, process, count;
	count = 0;

	printf("Enter the no of processes : ");
	scanf("%d", &p);

	for (i = 0; i < p; i++)
		completed[i] = 0;

	printf("\n\nEnter the no of resources : ");
	scanf("%d", &r);

	printf("\n\nEnter the Max Matrix for each process : ");
	InputArray(p, r, Max);
		
	printf("\n\nEnter the allocation for each process : ");
	InputArray(p, r, alloc);

	printf("\n\nEnter the Available Resources : ");
	for (i = 0; i < r; i++)
		scanf("%d", &avail[i]);

	//Need Matrix
	for (i = 0; i < p; i++)
		for (j = 0; j < r; j++)
			need[i][j] = Max[i][j] - alloc[i][j];

	do
	{
		printf("\n Max matrix:\tAllocation matrix:\tNeed matrix\n");
		for (i = 0; i < p; i++)
		{
			for (j = 0; j < r; j++)
			{
				printf("%d  ", Max[i][j]);
			}
			printf("\t\t");
			for (j = 0; j < r; j++)
			{
				printf("%d  ", alloc[i][j]);
			}
			printf("\t\t");
			for (j = 0; j< r; j++)
			{
				printf("%d ", need[i][j]);
			}
			printf("\n");
		}
		printf("Available : ");
		for(i =0; i< r ; i++)
			printf("%d ", avail[i]);

		process = -1;

		for (i = 0; i < p; i++)
		{
			if (completed[i] == 0)//if not completed
			{
				process = i;
				for (j = 0; j < r; j++)
				{
					if (avail[j] < need[i][j])
					{
						process = -1;
						break;
					}
				}
			}
			if (process != -1)
				break;
		}

		if (process != -1)
		{
			printf("\nProcess %d runs to completion!", process + 1);
			safeSequence[count] = process + 1;
			count++;
			for (j = 0; j < r; j++)
			{
				avail[j] += alloc[process][j];
				alloc[process][j] = 0;
				Max[process][j] = 0;
				completed[process] = 1;
				need[process][j] = 0;
			}
		}
	} while (count != p && process != -1);

	if (count == p)
	{
		printf("\nThe system is in a safe state!!\n");
		printf("Safe Sequence : < ");
		for (i = 0; i < p; i++)
			printf("%d  ", safeSequence[i]);	
		printf(">\n");
		printf("Last available resource\n");
		for(i =0; i< r ; i++)
			printf("%d ", avail[i]);			
	}
	else
	{
		printf("\nThe system is in an unsafe state!!\n<");
		for (i = 0; i < count; i++)
			printf("%d  ", safeSequence[i]);
		printf(">\n");
		printf("Last available resource\n");
		for(i =0; i< r ; i++)
			printf("%d ", avail[i]);			
	}
	return 0;
}
