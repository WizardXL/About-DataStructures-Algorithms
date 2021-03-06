#include <stdio.h>
#include <math.h>
#include <string.h>

//定义多项式的一项 
typedef struct {
	double coefficient;   //系数 
	int index;            //指数 
} Item, USER_TYPE;

#include "oneWayLinkedList.h"

static boolean first = FALSE;  

boolean inputItem(Item *item); 
void printOneItem(Item item); 
boolean comparaTo(Item one, Item two);
void  polynomialAddition(LinkedList aPoly, LinkedList bPoly, LinkedList *result);

/*
 多项式相加
 aPoly、bPoly: 待相加的目标多项式 
 *result:结果多项式 
*/ 
void  polynomialAddition(LinkedList aPoly, LinkedList bPoly, LinkedList *result) {
	Item copiedItem, comparaedItem;
	LinkedList copiedPoly, comparaedPoly;
	int comparaedPolyLen;                                      //comparaedPoly的长度 
	int copiedIndex = 0;                                       //copidedIndex所拷贝的目标链表的下标 
	int comparaedIndex = 0;                                    //comparaedIndex指示待比较的目标链表的下标          
	int resultIndex = 0;                                       //resultIndex指示结果链表的下一个插入或修改位置 
	
	bubbleSortList(aPoly, TRUE, comparaTo);                    //先对目标多项式升序 
	bubbleSortList(bPoly, TRUE, comparaTo);	
	getValueByIndex(aPoly, &copiedItem, getLength(aPoly)-1);   //得到目标多项式指数最大的一项 
	getValueByIndex(bPoly, &comparaedItem, getLength(bPoly)-1);
	copiedPoly = (copiedItem.index > comparaedItem.index ? aPoly : bPoly);     //选择出待相加的两个多项式中指数最大的 
	comparaedPoly = (copiedPoly == aPoly ? bPoly : aPoly);
	comparaedPolyLen = getLength(comparaedPoly);
	linkedListCopy(copiedPoly, result);                         //拷贝指数最大的目标链表为结果链表 
	
	while (comparaedIndex < comparaedPolyLen) {                 //循环比较多项式元素 
		getValueByIndex(copiedPoly, &copiedItem, copiedIndex);	
		getValueByIndex(comparaedPoly, &comparaedItem, comparaedIndex);
		
		if (copiedItem.index > comparaedItem.index) {
			insertNode(result, comparaedItem, resultIndex);
			comparaedIndex++;
		} else if (copiedItem.index < comparaedItem.index) {
			copiedIndex++;
		} else if (copiedItem.index == comparaedItem.index) {
			copiedItem.coefficient += comparaedItem.coefficient;		
			modifyNodeByIndex(*result, copiedItem, resultIndex);
			copiedIndex++;
			comparaedIndex++;
		}
		resultIndex++;
	}
}

boolean comparaTo(Item one, Item two) {
	return one.index > two.index;
}

void printOneItem(Item item) {		
	if (first == TRUE) {                                   //因为第一项为正无需+号，分开处理 
		puts("多项式如下:"); 
		if (fabs(item.coefficient+1) < 1e-6) {             //系数为-1
	 		printf("%s", "-");
		} else if (fabs(item.coefficient-1) > 1e-6) {      //系数不为1 
			printf("%.2lf", item.coefficient);
		}    
	}
	
	if (first == FALSE) {
		if (item.coefficient > 1e-6) {                      //正数都加上+号 
			printf("%c", '+');
		}
		if (fabs(item.coefficient+1) < 1e-6) {              //系数为-1 
			printf("%c", '-');
		} else if (fabs(item.coefficient-1) > 1e-6) {   	//系数不为1
			printf("%.2lf", item.coefficient);
		}	
	}

	if (item.index == 1) {  					            //输出指数 
		printf("%c", 'x');
 	} else if (item.index != 0) {
		printf("%c^%d", 'x', item.index);
	}
	first = FALSE;
}

boolean inputItem(Item *item) {
	printf("输入一项,如(3.14(系数), 1(指数)),Ctrl+Z或者系数为0结束:");
	return 2 == scanf("%lf%d", &(item->coefficient), &(item->index)) && fabs(item->coefficient) > 1e-6;
}

//-1 -1 -1 7 5 0
int main(void) {
	LinkedList poly1 = NULL;
	LinkedList poly2 = NULL;
	LinkedList result = NULL;
	
	first = TRUE;
	printf("\n%s\n", "--------------多项式1--------------");
	initLinkedList(&poly1, inputItem);
	iterator(poly1, printOneItem);

	first = TRUE;
	printf("\n%s\n", "--------------多项式2--------------");
	initLinkedList(&poly2, inputItem);
	iterator(poly2, printOneItem);

	first = TRUE; 
	printf("\n%s\n", "--------------相加结果-------------");
	polynomialAddition(poly1, poly2, &result);
	iterator(result, printOneItem);
	
	destoryLinkedList(&result);
	destoryLinkedList(&poly2);
	destoryLinkedList(&poly1);
	return 0;
}