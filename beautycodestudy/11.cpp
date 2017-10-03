#define TREELEN 6
#include<stdio.h>
struct NODE
{
	NODE* pLeft;
	NODE* pRight;
	char chValue;
};

void ReBuild(char* pPreOrder, char* pInOrder, int nTreeLen, NODE** pRoot)
{
	if (pPreOrder == NULL || pInOrder == NULL)
	{
		return;
	}
	NODE* pTemp = new NODE;
	pTemp->chValue = *pPreOrder;
	pTemp->pLeft = NULL;
	pTemp->pRight = NULL;
	if (*pRoot == NULL)
	{
		*pRoot = pTemp;
	}
	if (nTreeLen == 1)
	{
		return;
	}
	char* pOrgInOrder = pInOrder;
	char* pLeftEnd = pInOrder;
	int nTempLen = 0;

	while (*pPreOrder != *pLeftEnd)
	{
		if (pPreOrder == NULL || pLeftEnd == NULL)
		{
			return;
		}
		nTempLen++;
		if (nTempLen > nTreeLen)
		{
			break;
		}
		pLeftEnd++;
	}
	int nLeftLen = 0;
	nLeftLen = (int)(pLeftEnd - pOrgInOrder);
	int nRightLen = 0;
	nRightLen = nTreeLen - nLeftLen - 1;
	if (nLeftLen > 0)
	{
		ReBuild(pPreOrder + 1, pInOrder, nLeftLen, &((*pRoot)->pLeft));
	}
	if (nRightLen > 0)
	{
		ReBuild(pPreOrder + nLeftLen + 1, pInOrder + nLeftLen + 1, nRightLen, &((*pRoot)->pRight));

	}

}

int main()
{
	char sz1[TREELEN] = { 'a', 'b', 'd', 'c', 'e', 'f' };
	char sz2[TREELEN] = { 'd', 'b', 'a', 'e', 'c', 'f' };
	NODE* pRoot = NULL;
	ReBuild(sz1, sz2, TREELEN, &pRoot);
	return 0;
}