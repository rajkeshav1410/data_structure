#include<stdio.h>
#include<stdlib.h>
#define MAX_ITEM 20

typedef struct {
	int row, col, data;
} Item;

typedef struct {
	Item item[MAX_ITEM];
	int row, col, nz_item;
} SMatrix;

SMatrix *create() {
	int row, col;
	SMatrix *mat=(SMatrix *)malloc(sizeof(SMatrix));
	printf("Enter row and column of matrix : ");
	scanf("%d%d", &row, &col);
	*mat=(SMatrix){.row=row, .col=col, .nz_item=0};
	return mat;
}

void read(SMatrix *mat, char *mesg) {
	int i, j, data;
	printf("%s\n", mesg);
	for(i=0;i<mat->row;i++)
		for(j=0;j<mat->col;j++) {
			scanf("%d", &data);
			if(data==0) continue;
			mat->item[mat->nz_item++]=(Item){i, j, data};
		}
}

void print(SMatrix *mat, char *mesg) {
	int i, j, k=0;
	printf("%s\n", mesg);
	for(i=0;i<mat->row;i++) {
		for(j=0;j<mat->col;j++) {
			Item curr=mat->item[k];
			printf("%d ", (curr.row==i&&curr.col==j)?
			       mat->item[k++].data:0);
		}
		printf("\n");
	}
}

Item search(SMatrix *mat, int x) {
	int i;
	for(i=0;i<mat->nz_item;i++)
		if(mat->item[i].data==x) return mat->item[i];
	return (Item){.row=-1, .col=-1};
}

int main() {
	SMatrix *mat=create();
	read(mat, "Enter elements of the matrix");
	print(mat, "Elements of matrix are");

	int x;
	printf("Enter item to be searched : ");
	scanf("%d", &x);
	Item item=search(mat, x);
	printf("Item found at row : %d, col : %d", item.row, item.col);
	return 0;
}