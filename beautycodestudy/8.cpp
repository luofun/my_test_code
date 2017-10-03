#include<stdio.h>
#include<assert.h>

class CPrefixSorting{
public:
	CPrefixSorting(){
		m_nCakeCnt = 0;
		m_nMaxSwap = 0;
	}
	void Run(int* pCakeArray, int nCakecnt)
	{
		Init(pCakeArray, nCakecnt);
		m_nSearch = 0;
		Search(0);
	}
	void Output(){
		for (int i = 0; i < m_nMaxSwap; i++)
		{
			printf("%d ", m_SwapArray[i]);
		}
		printf("\n |Search Times| : %d\n", m_nSearch);
		printf("Total Swap times = %d\n", m_nMaxSwap);
	}
private:
	void  Init(int* pCakeArray, int n)
	{
		assert(pCakeArray != NULL);
		assert(n > 0);
		
		m_nCakeCnt = n;
		m_nMaxSwap = UpBound(m_nCakeCnt);
		m_CakeArray = new int[m_nCakeCnt];
		assert(m_CakeArray != NULL);
		for (int i = 0; i < m_nCakeCnt; i++)
		{
			m_CakeArray[i] = pCakeArray[i];
		}
		m_ReverseCakeArray = new int[m_nCakeCnt];
		assert(m_ReverseCakeArray != NULL);
		for (int i = 0; i < m_nCakeCnt; i++)
		{
			m_ReverseCakeArray[i] = m_CakeArray[i];
		}
		m_ReverseCakeArraySwap = new int[m_nMaxSwap];
		m_SwapArray = new int[m_nMaxSwap];
	}

	int UpBound(int nCakeCnt)
	{
		return nCakeCnt * 2;
	}

	int LowerBound(int* pCakeArray, int nCakeCnt)
	{
		int t, ret = 0;
		for (int i = 1; i < nCakeCnt; i++)
		{
			t = pCakeArray[i] - pCakeArray[i - 1];
			if ((t == 1) || (t == -1))
			{
			}
			else
			{
				ret++;
			}
		}
		return ret;
	}

	void Search(int step)
	{
		int i, nEstimate;
		m_nSearch++;
		nEstimate = LowerBound(m_ReverseCakeArray, m_nCakeCnt);
		if (step + nEstimate > m_nMaxSwap)
			return;
		if (IsSorted(m_ReverseCakeArray, m_nCakeCnt))
		{
			if (step < m_nMaxSwap)
			{
				m_nMaxSwap = step;
				for (i = 0; i < m_nMaxSwap; i++)
				{
					m_SwapArray[i] = m_ReverseCakeArraySwap[i];
				}
			}
			return;
		}
		for (i = 1; i < m_nCakeCnt; i++)
		{
			Revert(0, i);
			m_ReverseCakeArraySwap[step] = i;
			Search(step + 1);
			Revert(0, i);
		}
	}

	bool IsSorted(int* pCakeArray, int nCakeCnt)
	{
		for (int i = 1; i < nCakeCnt; i++)
		{
			if (pCakeArray[i - 1] > pCakeArray[i])
			{
				return false;
			}
			
		}
		return true;
	}

	void Revert(int nBegin, int nEnd)
	{
		assert(nEnd > nBegin);
		int i, j, t;
		for (i = nBegin, j = nEnd; i < j; i++, j--)
		{
			t = m_ReverseCakeArray[i];
			m_ReverseCakeArray[i] = m_ReverseCakeArray[j];
			m_ReverseCakeArray[j] = t;
		}
	}
private:
	int* m_CakeArray;
	int m_nCakeCnt;
	int m_nMaxSwap;
	int* m_SwapArray;
	int* m_ReverseCakeArray;
	int* m_ReverseCakeArraySwap;
	int m_nSearch;
};

void main(){
	CPrefixSorting* test = new CPrefixSorting;
	int num = 10;
	int nump[] = { 3, 2, 1, 6, 5, 4, 9, 8, 7, 0 };
	
	
	test->Run(nump, num);
	test->Output();

}