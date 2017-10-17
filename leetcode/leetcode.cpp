
#include<vector>
#include<algorithm>
#include<iterator>
#include<iostream>
#include<string>
#include <limits.h>
#include <sstream>
#include <map>
#include <functional>
#include <numeric>
#include<bitset>
#include<limits>
#include<stack>

using namespace std;

/*
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.
*/
vector<int> twoSum(vector<int>& nums, int target) {
	vector<int>::iterator ta, tb;
	int i = 0, j = 0;
	vector<int> back;
	for (ta = nums.begin(); ta != nums.end() - 1; ++ta, ++i)
	{
		j = i + 1;
		for (tb = ta + 1; tb != nums.end(); ++tb, ++j)
		{
			if (*ta + *tb == target)
			{
				cout << i << '\t' << j << endl;
				back.push_back(i);
				back.push_back(j);
			}

		}
		
	}
	return back;
}

/*

The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

Given two integers x and y, calculate the Hamming distance.

*/
int hammingDistance(int x, int y) {
	int back = 0;
	int temp = x^y;
	while (temp) {
		if (temp & 1) {
			++back;
		}
		temp = temp >> 1;
	}
	return back;
}

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}

};

/*

Given two binary trees and imagine that when you put one of them to cover the other, some nodes of the two trees are overlapped while the others are not.

You need to merge them into a new binary tree. The merge rule is that if two nodes overlap, then sum node values up as the new value of the merged node. Otherwise, the NOT null node will be used as the node of new tree.

*/
TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
	TreeNode* back=new TreeNode(0);
	if (t1 != NULL&&t2 != NULL)
	{
		back->val = t1->val + t2->val;
		back->left = mergeTrees(t1->left, t2->left);
		back->right = mergeTrees(t1->right, t2->right);
	}
	else
		if (t1 != NULL)
		{
			back->val = t1->val;
			back->left = mergeTrees(t1->left, NULL);
			back->right = mergeTrees(t1->right, NULL);
		}
		else 
			if(t2!=NULL)
			{
				back->val = t2->val;
				back->left = mergeTrees(NULL, t2->left);
				back->right = mergeTrees(NULL, t2->right);
			}
	if (t1 == NULL&&t2 == NULL)
		return NULL;
	//[1,3,2,5]
	//[2, 1, 3, null, 4, null, 7]
	//[1, 2, null, 3]
	//[1, null, 2, null, 3]

	return back;
}

/*

Initially, there is a Robot at position (0, 0). Given a sequence of its moves, judge if this robot makes a circle, which means it moves back to the original place.

The move sequence is represented by a string. And each move is represent by a character. The valid robot moves are R (Right), L (Left), U (Up) and D (down). The output should be true or false representing whether the robot makes a circle.

*/
bool judgeCircle(string moves) {
	int upsign = 0, downsign = 0, leftsign = 0, rightsign = 0;
	for (auto a = moves.begin(); a != moves.end(); a++)
	{
		if (a[0] == 'U') 
		{
			++upsign;
			continue;
		}	
		if (a[0] == 'D')
		{
			++downsign;
			continue;
		}
		if (a[0] == 'R')
		{
			++rightsign;
			continue;
		}
		if (a[0] == 'L')
		{
			++leftsign;
			continue;
		}
	}	
	if (upsign == downsign&&rightsign == leftsign)
		return true;
	else
		return false;
}

/*

Given an array of 2n integers, your task is to group these integers into n pairs of integer, say (a1, b1), (a2, b2), ..., (an, bn) which makes sum of min(ai, bi) for all i from 1 to n as large as possible.

*/
int arrayPairSum(vector<int>& nums) {
	int sum = 0;
	sort(nums.begin(), nums.end());
	for (auto a = nums.begin(); a != nums.end(); ++++a)
	{
		sum += *a;
	}
	return sum;
}

/*

Given a positive integer, output its complement number. The complement strategy is to flip the bits of its binary representation.

*/
int findComplement(int num) {
	unsigned mask = ~0;
	while (num & mask) mask <<= 1;
	return ~mask & ~num;

}


/*

Given a List of words, return the words that can be typed using letters of alphabet on only one row's of American keyboard like the image below.

*/
vector<string> findWords(vector<string>& words) {
	vector<string> back;
	int tsign = 0;
	int sign = 1;
	int list[26] = { 2,3,3,2,1,2,2,2,1,2,2,2,3,3,1,1,1,1,2,1,1,3,1,3,1,3 };
	for (vector<string>::iterator a = words.begin(); a != words.end(); a++)
	{
		tsign = isupper(a[0][0]) ? list[(int)(a[0][0] - 'A')] : list[(int)(a[0][0] - 'a')];
		for (auto b = a->begin(); b != a->end(); b++)
		{
			if ((isupper(b[0]) ? list[(int)(b[0] - 'A')] : list[(int)(b[0] - 'a')]) != tsign)
			{
				sign = 0;
				break;
			}			
		}
		if (sign == 1)
		{
			back.push_back(*a);
		}
		tsign = 0;
		sign = 1;
	}
	return back;
}


/*

You're now a baseball game point recorder.

Given a list of strings, each string can be one of the 4 following types:

Integer (one round's score): Directly represents the number of points you get in this round.
"+" (one round's score): Represents that the points you get in this round are the sum of the last two valid round's points.
"D" (one round's score): Represents that the points you get in this round are the doubled data of the last valid round's points.
"C" (an operation, which isn't a round's score): Represents the last valid round's points you get were invalid and should be removed.
Each round's operation is permanent and could have an impact on the round before and the round after.

You need to return the sum of the points you could get in all the rounds.

*/
int calPoints(vector<string>& ops) {
	vector<int> r{};
	for (string& op : ops){
		if (op == "C"){ r.pop_back(); }
		else if (op == "D"){ r.push_back(2 * r.back()); }
		else if (op == "+"){ r.push_back(r.end()[-2] + r.end()[-1]); }
		else             { r.push_back(stoi(op)); }
	}
	return accumulate(r.begin(), r.end(), 0);
}

/*

Write a function that takes a string as input and returns the string reversed.

*/
string reverseString(string s) {
	string back = s;
	for (int i = 0; i < s.length(); i++)
	{
		back[i] = s[s.length() - 1 - i];
	}
	return back;
}

/*

Given a string, you need to reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.

*/
string reverseWords(string s) {
	string back = s;
	int i = 0, j = 0;
	for (i = 0;; i++)
	{
		for (j = 0;; j++, i++)
		{
			if (s.c_str()[i] == ' ' || s.c_str()[i] == '\0')
				break;
		}
		for (int temp = 0; temp < j; temp++)
		{
			back[temp + i - j] = s[i - 1 - temp];
		}
		if (s.c_str()[i] == '\0')
			break;
	}
	return back;
}

/*

Given an integer array with even length, where different numbers in this array represent different kinds of candies. Each number means one candy of the corresponding kind. You need to distribute these candies equally in number to brother and sister. Return the maximum number of kinds of candies the sister could gain.

*/
int distributeCandies(vector<int>& candies) {
	bitset<200001> hash;
	int count = 0;
	for (int i : candies) {
		if (!hash.test(i + 100000)) {
			count++;
			hash.set(i + 100000);
		}
	}
	int n = candies.size();
	return min(count, n / 2);
}

/*

Write a program that outputs the string representation of numbers from 1 to n.

But for multiples of three it should output ¡°Fizz¡± instead of the number and for the multiples of five output ¡°Buzz¡±. For numbers which are multiples of both three and five output ¡°FizzBuzz¡±.

*/
vector<string> fizzBuzz(int n) {
	vector<string> back;
	for (int i = 1; i <= n; i++)
	{
		if (i % 3 == 0 && i % 5 == 0)
		{
			back.push_back("FizzBuzz");
			continue;
		}
		if (i % 3 == 0)
		{
			back.push_back("Fizz");
			continue;
		}
		if (i % 5 == 0)
		{
			back.push_back("Buzz");
			continue;
		}
		back.push_back(to_string(i));
	}
	return back;
}

/*

In MATLAB, there is a very useful function called 'reshape', which can reshape a matrix into a new one with different size but keep its original data.

You're given a matrix represented by a two-dimensional array, and two positive integers r and c representing the row number and column number of the wanted reshaped matrix, respectively.

The reshaped matrix need to be filled with all the elements of the original matrix in the same row-traversing order as they were.

If the 'reshape' operation with given parameters is possible and legal, output the new reshaped matrix; Otherwise, output the original matrix.

*/
vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {
	if (nums.size()*nums[0].size() != r*c || (nums.size() == r&&nums[0].size() == c))
		return nums;
	vector<vector<int>> back;
	int count = 0;
	back.resize(r);
	for (auto x = back.begin(); x != back.end(); x++)
		(*x).resize(c);
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			back[i][j] = nums[count / nums[0].size()][count%nums[0].size()];
			count++;
		}
	}
	return back;
}

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}

};
/*

You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

*/
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	/*
	Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
	Output: 7 -> 0 -> 8
	*/
	ListNode* back = new ListNode(0);
	
	back->val = l1->val + l2->val;
	if (back->val / 10 > 0)
	{
		back->val -= 10;
		if (l1->next == NULL&&l2->next == NULL)
		{
			ListNode* temp = new ListNode(1);
			back->next = temp;
			return back;
		}
		if (l1->next != NULL&&l2->next != NULL)
		{
			l1->next->val += 1;
			back->next = addTwoNumbers(l1->next, l2->next);
		}
		else 
			if (l1->next==NULL)
			{
				back->next = addTwoNumbers(new ListNode(1), l2->next);
			}
			else 
				if (l2->next == NULL)
				{
					back->next = addTwoNumbers(l1->next, new ListNode(1));
				}
	}
	else
	{
		if (l1->next == NULL&&l2->next == NULL)
		{
			return back;
		}
		if (l1->next != NULL&&l2->next != NULL)
		{
			back->next = addTwoNumbers(l1->next, l2->next);
		}
		else
			if (l1->next == NULL)
			{
				back->next = addTwoNumbers(new ListNode(0), l2->next);
			}
			else
				if (l2->next == NULL)
				{
					back->next = addTwoNumbers(l1->next, new ListNode(0));
				}
	}
	return back;	
}

/*

Reverse digits of an integer.

Example1: x = 123, return 321
Example2: x = -123, return -321

*/
int reverse(int x) {
	if (x >= INT_MAX)
		return 0;
	string temp,temp2;
	temp = to_string(x);
	temp2 = temp;
	if (temp[0] != '-')
	{
		for (int i = 0; i < temp.length(); i++)
		{
			temp[i] = temp2[temp.length() - 1 - i];
		}
	}
	else
	{
		for (int i = 1; i < temp.length(); i++)
		{
			temp[i] = temp2[temp.length() - i];
		}
	}
	int xa;
	try
	{
		xa = stoi(temp);
	}
	catch (...)
	{
		xa = 0;
	}
	return xa;
}

/*

Determine whether an integer is a palindrome. Do this without extra space.

*/
bool isPalindrome(int x) {
	if (x<0 || (x != 0 && x % 10 == 0)) return false;
	int sum = 0;
	while (x>sum)
	{
		sum = sum * 10 + x % 10;
		x = x / 10;
	}
	return (x == sum) || (x == sum / 10);
}

/*

Given a roman numeral, convert it to an integer.

Input is guaranteed to be within the range from 1 to 3999.


*/
int romanToInt(string s) {
	map<char, int> T = { { 'I', 1 },
	{ 'V', 5 },
	{ 'X', 10 },
	{ 'L', 50 },
	{ 'C', 100 },
	{ 'D', 500 },
	{ 'M', 1000 } };

	int sum = T[s.back()];
	for (int i = s.length() - 2; i >= 0; --i)
	{
		if (T[s[i]] < T[s[i + 1]])
		{
			sum -= T[s[i]];
		}
		else
		{
			sum += T[s[i]];
		}
	}

	return sum;
}

/*

Given a binary search tree and the lowest and highest boundaries as L and R, trim the tree so that all its elements lies in [L, R] (R >= L). You might need to change the root of the tree, so the result should return the new root of the trimmed binary search tree.

*/
TreeNode* trimBST(TreeNode* root, int L, int R) {
	if (root == NULL)
		return NULL;
	TreeNode* back = new TreeNode(-1);
	if (R == L)
	{
		while (root->val != L)
		{
			if (root->val > L)
				root = root->left;
			if (root->val < R)
				root = root->right;
		}
		back = root;
		back->left = NULL;
		back->right = NULL;
		return back;
	}
	else
	{
		if (root->val < L)
		{
			//back = root->right;
			back=trimBST(root->right, L, R);
		}
		else
			if (root->val > R)
			{
				//back = root->left;
				back=trimBST(root->left, L, R);
			}
			else
			{
				if (root->val == L)
				{
					back = root;
					back->left = NULL;
					back->right = trimBST(root->right, L, R);
				}
				else
					if (root->val == R)
					{
						back = root;
						back->right = NULL;
						back->left = trimBST(root->left, L, R);
					}
					else
					{
						back = root;
						back->left = trimBST(root->left, L, R);
						back->right = trimBST(root->right, L, R);
					}
			}
	}
	return back;
}//[3,0,4,null,2,null,null,1]  || [3,2,null,1]

/*

Write a function to find the longest common prefix string amongst an array of strings.

*/
string longestCommonPrefix(vector<string>& strs) {
	string back = "";
	int x = 0;
	int i = 0;
	int sign = 0;
	if (strs.size() == 0)
		return back;
	for (; i < strs[0].length(); i++)
	{
		for (; x < strs.size(); x++)
		{
			if (strs[x][i] != strs[0][i])
			{
				sign = 1; 
				break;
			}
		}
		if (sign == 0)
		{
			back.push_back(strs[0][i]);
			x = 0;
		}
		else
		{
			break;
		}
	}
	return back;
}

/*

Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.

*/
bool isValid(string s) {
	stack<char> a;
	char temp;
	for (auto x = s.begin(); x != s.end(); x++)
	{
		if (*x == '(' || *x == '{' || *x == '[')
		{
			a.push(*x);
			continue;
		}
		if (*x == ')')
		{
			if ((a.size() > 0) && (a.top() == '('))
			{
				a.pop();
				continue;
			}
			else
				return false;
		}
		if (*x == ']')
		{
			if ((a.size() > 0) && (a.top() == '['))
			{
				a.pop();
				continue;
			}
			else
				return false;
		}
		if (*x == '}')
		{
			if ((a.size() > 0) && (a.top() == '{'))
			{
				a.pop();
				continue;
			}
			else
				return false;
		}
	}
	if (a.size() > 0)
	{
		return false;
	}
	return true;
}

/*

Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

*/
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
	ListNode dummy(INT_MIN);
	ListNode *tail = &dummy;

	while (l1 && l2) {
		if (l1->val < l2->val) {
			tail->next = l1;
			l1 = l1->next;
		}
		else {
			tail->next = l2;
			l2 = l2->next;
		}
		tail = tail->next;
	}

	tail->next = l1 ? l1 : l2;
	return dummy.next;
}

/*

Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

For example,
Given input array nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively. It doesn't matter what you leave beyond the new length.

*/
int removeDuplicates(vector<int>& nums) {
	for (auto x = nums.begin(); x != nums.end(); x++)
	{
		for (auto y = x + 1; y != nums.end();)
		{
			if (*x == *y)
			{
				y = nums.erase(y);
				continue;
			}
			break;
		}
	}
	return 0;
}

/*

Given an array and a value, remove all instances of that value in place and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

The order of elements can be changed. It doesn't matter what you leave beyond the new length.

*/
int removeElement(vector<int>& nums, int val) {
	for (auto x = nums.begin(); x != nums.end();)
	{
		if (*x == val)
		{
			x = nums.erase(x);
			continue;
		}
		x++;
	}
	return nums.size();
}

/*

Implement strStr().

Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

*/
int strStr(string haystack, string needle) {
	if (needle.length() > haystack.length())
		return -1;
	if (haystack.length() == 0 || needle.length() == 0)
		return 0;
	int count = 0;
	for (int i = 0; i < haystack.length() - needle.length() + 1; i++)
	{
		count = 0;
		for (int j = 0; j < needle.length(); j++)
		{
			if (haystack[i + j] != needle[j])
			{
				if (count == needle.length())
					return i;
				break;
			}
			count++;
			if (count == needle.length())
				return i;
		}
	}
	return -1;
}

/*

Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

*/
int searchInsert(vector<int>& nums, int target) {
	int i = 0;
	for (i = 0; i < nums.size(); i++)
	{
		if (nums[i] == target)
			return i;
		if (nums[i] > target)
			break;
	}
	if (i != nums.size() - 1)
		return i;
	else
	{
		if (target > nums[i])
			return i + 1;
		else
			return i;
	}
}

/*

The count-and-say sequence is the sequence of integers with the first five terms as following:

*/
string countAndSay(int n) {
	if (n == 0) return "";
	string res = "1";
	while (--n) {
		string cur = "";
		for (int i = 0; i < res.size(); i++) {
			int count = 1;
			while ((i + 1 < res.size()) && (res[i] == res[i + 1])) {
				count++;
				i++;
			}
			cur += to_string(count) + res[i];
		}
		res = cur;
	}
	return res;
}


/*

Find the contiguous subarray within an array (containing at least one number) which has the largest sum.

For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
the contiguous subarray [4,-1,2,1] has the largest sum = 6.

*/
int maxSubArray(vector<int>& nums) {
	int max = INT_MIN, sum = 0;
	for (auto i = nums.begin(); i != nums.end(); i++)
	{
		sum = 0;
		for (auto j = i; j != nums.end(); j++)
		{
			sum += *j;
			if (sum > max)
				max = sum;
			if (sum <= 0)
				break;
		}
	}
	return max;
}

int main()
{
	ListNode aa1[] = { { 2 }, { 3 }, { 4 } };
	ListNode aa2[] = { { 0 }, { 2 }, { 3 } };
	ListNode* ttt = mergeTwoLists(aa1, aa2);

    return 0;
}

