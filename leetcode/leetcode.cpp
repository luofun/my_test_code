
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
#include<set>
#include <stdint.h>
#include<unordered_set>
#include<queue>
#include<unordered_map>

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

But for multiples of three it should output “Fizz” instead of the number and for the multiples of five output “Buzz”. For numbers which are multiples of both three and five output “FizzBuzz”.

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
}

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
	//char temp;
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

/*

Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.

If the last word does not exist, return 0.

*/
int lengthOfLastWord(string s) {
	if (s.length() == 0 )
		return 0;	
	if (s.find_last_of(' ') == -1)
		return s.length();
	if (s.find_last_of(' ') == s.length() - 1)
	{		
		int i = s.find_last_not_of(' ');
		string b = s.substr(0, i + 1);
		return lengthOfLastWord(b);
	}	
	return s.length() - s.find_last_of(' ') - 1;
}

/*

Given a non-negative integer represented as a non-empty array of digits, plus one to the integer.

You may assume the integer do not contain any leading zero, except the number 0 itself.

The digits are stored such that the most significant digit is at the head of the list.

*/
vector<int> plusOne(vector<int>& digits) {
	if (digits.size() == 1)
	{
		++digits[0];
	}
	else
	{
		for (int i = digits.size() - 1; i > 0; i--)
		{
			if (i == digits.size() - 1)
				++digits[i];
			if (digits[i] / 10 > 0)
			{
				digits[i - 1] += digits[i] / 10;
				digits[i] %= 10;
			}
		}
	}
	if (digits[0] == 10)
	{
		digits.insert(digits.begin(), 1);
		digits[1] = 0;
	}
	return digits;
}

/*

Given two binary strings, return their sum (also a binary string).

*/
string addBinary(string a, string b) {
	if (a.length() == 0 && b.length() == 0)
	{
		return "0";
	}
	if (a.length() > b.length())
	{
		b.insert(b.begin(), a.length() - b.length(), '0');
	}
	if (b.length() > a.length())
	{
		a.insert(a.begin(), b.length() - a.length(), '0');
	}
	for (int sa = a.length() - 1, sb = b.length() - 1; sa > 0 && sb > 0; sa--, sb--)
	{
		a[sa] = a[sa] + b[sb] - '0';
		if (a[sa] == '3')
		{
			a[sa - 1] += 1;
			a[sa] = '1';
		}
		if (a[sa] == '2')
		{
			a[sa - 1] += 1;
			a[sa] = '0';
		}
	}
	a[0] = a[0] + b[0] - '0';
	if (*a.begin() == '3')
	{
		a.insert(a.begin(), '1');
		a[1] = '1';
		return a;
	}
	if (*a.begin() == '2')
	{
		a.insert(a.begin(), '1');
		a[1] = '0';
		return a;
	}
	return a;
}

/*

You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

*/
int climbStairs(int n) {
	/*
	if (n > 2)
	return n == 1 ? 1 : (climbStairs(n - 1) + climbStairs(n - 2));
	else
	return n == 1 ? 1 : 2;
	*///runtime problem
	//DP
	int a = 1, b = 1;
	while (n--)
		a = (b += a) - a;
	return a;
}

/*

Given a sorted linked list, delete all duplicates such that each element appear only once.

*/
ListNode* deleteDuplicates(ListNode* head) {
	if (head == NULL)
		return head;
	ListNode* temp = head;
	while (temp->next != NULL)
	{
		if (temp->next->val == temp->val)
		{
			temp->next = temp->next->next;
		}
		else
		{
			temp = temp->next;
		}
	}
	return head;
}

/*

Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

*/
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
	nums1.resize(m);
	nums2.resize(n);
	nums1.insert(nums1.end(), nums2.begin(), nums2.end());
	sort(nums1.begin(), nums1.end());
	nums1.resize(m + n);
}

/*

Given two binary trees, write a function to check if they are equal or not.

Two binary trees are considered equal if they are structurally identical and the nodes have the same value.

*/
bool isSameTree(TreeNode* p, TreeNode* q) {
	if (p == NULL&&q == NULL)
		return true;
	if (p == NULL || q == NULL)
		return false;
	if (p->val == q->val)
	{
		if (!isSameTree(p->left, q->left))
		{
			return false;
		};
		if (!isSameTree(p->right, q->right))
		{
			return false;
		};
		return true;
	}

	return false;
}

/*

Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

*/
bool isSymmetric(TreeNode* root) {
	if (root == NULL)
		return true;
	if (root->left == NULL&&root->right == NULL)
		return true;
	if (root->left == NULL || root->right == NULL)
		return false;
	TreeNode* temp = new TreeNode(0);
	if (root->left->val == root->right->val)
	{
		temp->left = root->left->left;
		temp->right = root->right->right;
		if (!isSymmetric(temp))
			return false;
		temp->left = root->left->right;
		temp->right = root->right->left;
		if (!isSymmetric(temp))
			return false;
		return true;
	}
	return false;
}

/*

Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

*/
int maxDepth(TreeNode* root) {
	/*
	if (root == NULL)
	return 0;
	return maxDepth(root->left) > maxDepth(root->right) ? maxDepth(root->left) + 1 : maxDepth(root->right) + 1;
	*///runtime no meet
	if (root == NULL)
		return 0;
	int i = maxDepth(root->left) + 1;
	int k = maxDepth(root->right) + 1;
	return i > k ? i : k;
}

/*

Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

*/
vector<vector<int>> levelOrderBottom(TreeNode* root) {
	vector<vector<int>> back;
	stack<vector<int>> backtemp;
	deque<TreeNode*> sss;
	int count = 1;
	int swap = 1;
	TreeNode* temp;
	if (root == NULL)
		return back;
	sss.push_back(root);
	backtemp.push(vector<int>{root->val});
	while (!sss.empty())
	{
		vector<int> ttt;
		count = swap;
		swap = 0;
		for (int i = 0; i < count; i++)
		{
			temp = sss.front();
			if (temp->left != NULL)
			{
				sss.push_back(temp->left);
				swap++;
				ttt.push_back(temp->left->val);
			}
			if (temp->right != NULL)
			{
				sss.push_back(temp->right);
				swap++;
				ttt.push_back(temp->right->val);
			}
			sss.pop_front();		
		}
		if (!ttt.empty())
			backtemp.push(ttt);
	}
	while (!backtemp.empty())
	{
		back.push_back(backtemp.top());
		backtemp.pop();
	}
	return back;
}

/*

Given an array where elements are sorted in ascending order, convert it to a height balanced BST.

*/
TreeNode* sortedArrayToBST(vector<int>& nums) {
	TreeNode* back;
	if (nums.size() == 0)
		return NULL;
	if (nums.size() == 1)
	{
		back = new TreeNode(nums[0]);
		return back;
	}
	int mid = nums.size() / 2;
	back = new TreeNode(nums[mid]);
	vector<int> a;
	a.resize(mid);
	copy(nums.begin(), nums.begin() + mid, a.begin());
	back->left = sortedArrayToBST(a);
	if (nums.size() >= 2)
	{
		vector<int> b;
		b.resize(nums.size() - mid - 1);
		copy(nums.begin() + mid + 1, nums.end(), b.begin());
		back->right = sortedArrayToBST(b);
	}
	return back;
}

int dfsHeight(TreeNode *root) {
	if (root == NULL) return 0;

	int leftHeight = dfsHeight(root->left);
	if (leftHeight == -1) return -1;
	int rightHeight = dfsHeight(root->right);
	if (rightHeight == -1) return -1;

	if (abs(leftHeight - rightHeight) > 1)  return -1;
	return max(leftHeight, rightHeight) + 1;
}

/*

Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

*/
bool isBalanced(TreeNode* root) {
	return dfsHeight(root) != -1;
}

/*

Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

*/
int minDepth(TreeNode* root) {
	if (!root) return 0;
	int L = minDepth(root->left), R = minDepth(root->right);
	return 1 + (min(L, R) ? min(L, R) : max(L, R));//root dont see as a leafnode in this case
}

/*

Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.

*/
bool hasPathSum(TreeNode* root, int sum) {
	if (root == NULL) return false;
	if (root->val == sum && root->left == NULL && root->right == NULL) return true;
	return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
}

/*

Given numRows, generate the first numRows of Pascal's triangle.

*/
vector<vector<int>> generate(int numRows) {
	vector<vector<int>> back;
	if (numRows <= 0)
		return back;
	back.resize(numRows);
	for (int x = 0; x < back.size(); x++)
	{
		back[x].resize(x + 1);
	}
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < i + 1; j++)
		{
			if (i == 0)
			{
				back[0][0] = 1;
				continue;
			}
			if (j == 0 || j == i)
			{
				back[i][j] = 1;
				continue;
			}
			if (j <= i)
			{
				back[i][j] = back[i - 1][j - 1] + back[i - 1][j];
				continue;
			}
		}
	}
	return back;
}


/*

Given an index k, return the kth row of the Pascal's triangle.

*/
vector<int> getRow(int rowIndex) {
	vector<int> A(rowIndex + 1, 0);
	A[0] = 1;
	for (int i = 1; i<rowIndex + 1; i++)
		for (int j = i; j >= 1; j--)
			A[j] += A[j - 1];
	return A;
}

/*

Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.

*/
int maxProfit(vector<int>& prices) {
	/*
	int dif = 0;
	if (prices.size() == 0 || prices.size() == 1)
	return dif;
	for (int i = 0; i < prices.size() - 1; i++)
	{
	for (int j = i; j < prices.size() - 1; j++)
	{
	dif = (prices[j + 1] - prices[i] > dif ? prices[j + 1] - prices[i] : dif);
	}
	}
	return dif;
	*///o^2 runtime no meet
	int minprice = INT_MAX;
	int maxprofit = 0;
	for (int i = 0; i < prices.size(); i++) {
		if (prices[i] < minprice)
			minprice = prices[i];
		else if (prices[i] - minprice > maxprofit)
			maxprofit = prices[i] - minprice;
	}
	return maxprofit;
}

/*

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

*/
int maxProfit2(vector<int>& prices) {
	int total = 0;
	if (prices.size() == 0 || prices.size() == 1)
		return 0;
	for (int i = 0; i< prices.size() - 1; i++) {
		if (prices[i + 1]>prices[i]) total += prices[i + 1] - prices[i];
	}

	return total;
}

/*

Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

*/
bool isPalindrome(string s) {
	for (int i = 0, j = s.size() - 1; i < j; i++, j--) { // Move 2 pointers from each end until they collide
		while (isalnum(s[i]) == false && i < j) i++; // Increment left pointer if not alphanumeric
		while (isalnum(s[j]) == false && i < j) j--; // Decrement right pointer if no alphanumeric
		if (toupper(s[i]) != toupper(s[j])) return false; // Exit and return error if not match
	}

	return true;
}

/*

Given an array of integers, every element appears twice except for one. Find that single one.

*/
int singleNumber(vector<int>& nums) {
	int x = 0;
	for (int i = 0; i<nums.size(); i++)
		x ^= nums[i];
	return x;//a^a==0 a^0==a
}

/*

Given a linked list, determine if it has a cycle in it.

*/
bool hasCycle(ListNode *head) {
	if (head == NULL || head->next == NULL) {
		return false;
	}
	ListNode* slow = head;
	ListNode* fast = head->next;
	while (slow != fast) {
		if (fast == NULL || fast->next == NULL) {
			return false;
		}
		slow = slow->next;
		fast = fast->next->next;
	}
	return true;
}

/*

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.

*/
class MinStack {
public:
	/** initialize your data structure here. */
	stack<int> a, b;
	int min;
	MinStack() {
		min = INT_MAX;
	}

	void push(int x) {
		a.push(x);
		if (x < this->min)
			b.push(x);
		else
			b.push(min);
	}

	void pop() {
		a.pop();
		b.pop();
		if (b.size() == 0)
			min = INT_MAX;
		else
			min = b.top();
	}

	int top() {
		return a.top();
	}

	int getMin() {
		return b.top();
	}
};

/*

Write a program to find the node at which the intersection of two singly linked lists begins.

*/
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
	ListNode *cur1 = headA, *cur2 = headB;
	while (cur1 != cur2){
		cur1 = cur1 ? cur1->next : headB;
		cur2 = cur2 ? cur2->next : headA;
	}
	return cur1;
}


/*

Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution and you may not use the same element twice.

*/
vector<int> twoSum2(vector<int>& numbers, int target) {
	/*
	vector<int> back;
	for (int i = 0; i < numbers.size() - 1; i++)
	{
		for (int j = i + 1; j < numbers.size(); j++)
		{
			if (numbers[i] + numbers[j] == target)
			{
				back.push_back(i + 1);
				back.push_back(j + 1);
				return back;
			}
		}
	}
	return back;
	*///runtime no meet

	int lo = 0, hi = numbers.size() - 1;
	while (numbers[lo] + numbers[hi] != target){
		if (numbers[lo] + numbers[hi]<target){
			lo++;
		}
		else {
			hi--;
		}
	}
	return vector<int>({ lo + 1, hi + 1 });//O(n) lo-> <-hi

}

/*

Given a positive integer, return its corresponding column title as appear in an Excel sheet.

*/
string convertToTitle(int n) {
	string ans;
	while (n) {
		ans = char((n - 1) % 26 + 'A') + ans;
		n = (n - 1) / 26;
	}
	return ans;	
}

/*

Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist in the array.

*/
int majorityElement(vector<int>& nums) {
	sort(nums.begin(), nums.end());
	return nums[nums.size() / 2];
}

/*

Related to question Excel Sheet Column Title

Given a column title as appear in an Excel sheet, return its corresponding column number.

*/
int titleToNumber(string s) {
	int sum = 0;
	int tempsum = 0;
	if (s.length() == 0)
		return sum;
	for (int i = s.length() - 1; i >= 0; i--)
	{
		tempsum = s[i] - 'A' + 1;
		for (int j = 0; j < s.length() - 1 - i; j++)
		{
			tempsum *= 26;
		}
		sum += tempsum;
	}
	return sum;
}


/*

Rotate an array of n elements to the right by k steps.

For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4].

*/
void rotate(vector<int>& nums, int k) {
	if (k == 0)
		return;
	vector<int> temp = nums;
	for (int i = nums.size() - 1; i >= 0; i--)
	{
		nums[(i + k) % nums.size()] = temp[i];
	}
}

/*

Given an integer n, return the number of trailing zeroes in n!.

*/
int trailingZeroes(int n) {
	/*
	if (n < 5)
	return 0;
	int c2 = 0, c5 = 0, c10 = 0;
	int back = 0;
	int temp;
	for (int i = 1; i <= n; i++)
	{
	temp = i;
	while (temp%10==0)
	{
	++c10;
	temp /= 10;
	}

	while (temp % 2 == 0)
	{
	++c2;
	temp /= 2;
	}
	while (temp % 5 == 0)
	{
	++c5;
	temp /= 5;
	}
	}
	while (c2!=0&&c5!=0)
	{
	++back;
	--c2;
	--c5;
	}
	while (c10 != 0)
	{
	++back;
	--c10;
	}
	return back;
	*///runtime no meet
	return n == 0 ? 0 : n / 5 + trailingZeroes(n / 5);
}

/*

Reverse bits of a given 32 bits unsigned integer.

*/
uint32_t reverseBits(uint32_t n) {
	uint32_t m = 0;
	for (int i = 0; i < 32; i++, n >>= 1) {
		m <<= 1;
		m |= n & 1;
	}
	return m;
}

/*

Write a function that takes an unsigned integer and returns the number of ’1' bits it has (also known as the Hamming weight).

*/
int hammingWeight(uint32_t n) {
	uint32_t m = 1;
	int count = 0;
	while (n)
	{
		if (m&n)
			count++;
		n >>= 1;
	}
	return count;
}


/*

You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

*/
int rob(vector<int>& nums) {
	int rob = 0; //max monney can get if rob current house
	int notrob = 0; //max money can get if not rob current house
	for (int i = 0; i<nums.size(); i++) {
		int currob = notrob + nums[i]; //if rob current value, previous house must not be robbed
		notrob = max(notrob, rob); //if not rob ith house, take the max value of robbed (i-1)th house and not rob (i-1)th house
		rob = currob;
	}
	return max(rob, notrob);
}

/*

Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

*/
bool isHappy(int n) {
	set<int> inLoop;
	int squareSum, remain;
	while (inLoop.insert(n).second) {
		squareSum = 0;
		while (n > 0) {
			remain = n % 10;
			squareSum += remain*remain;
			n /= 10;
		}
		if (squareSum == 1)
			return true;
		else
			n = squareSum;

	}
	return false;
}
//another good answear(to justice the cycle)
/*

int digitSquareSum(int n) {
int sum = 0, tmp;
while (n) {
tmp = n % 10;
sum += tmp * tmp;
n /= 10;
}
return sum;
}

bool isHappy(int n) {
int slow, fast;
slow = fast = n;
do {
slow = digitSquareSum(slow);
fast = digitSquareSum(fast);
fast = digitSquareSum(fast);
} while(slow != fast);
if (slow == 1) return 1;
else return 0;
}

*/

/*

Remove all elements from a linked list of integers that have value val.

*/
ListNode* removeElements(ListNode* head, int val) {
	if (head == NULL)
		return NULL;
	ListNode* temp1 = head;
	while (temp1->val == val && temp1 != NULL)
		temp1 = temp1->next;
	ListNode*back = temp1, *temp2 = temp1;
	if (back == NULL)
		return NULL;
	temp1 = temp1->next;
	while (temp1 != NULL)
	{
		if (temp1->val == val)
		{
			temp2->next = temp1->next;
			temp1 = temp1->next;
		}
		else
		{
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
	}
	return back;
}

/*

Count the number of prime numbers less than a non-negative number, n.

*/
int countPrimes(int n) {
	bool* notPrime = new bool[n] {false};
	int count = 0;
	for (int i = 2; i < n; i++) {
		if (notPrime[i] == false) {
			count++;
			for (int j = 2; i*j < n; j++) {
				notPrime[i*j] = true;
			}
		}
	}
	delete notPrime;
	return count;
}

/*

Given two strings s and t, determine if they are isomorphic.

Two strings are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.

*/
bool isIsomorphic(string s, string t) {
	int m1[256] = { 0 }, m2[256] = { 0 };
	for (int i = 0; i < s.size(); ++i)
	{
		if (m1[s[i]] != m2[t[i]]) return false;
		m1[s[i]] = i + 1;
		m2[t[i]] = i + 1;
	}
	return true;
}

/*

Reverse a singly linked list.

*/
ListNode* reverseList(ListNode* head) {
	ListNode* prev = NULL;
	ListNode* curr = head;
	while (curr != NULL) {
		ListNode* nextTemp = curr->next;
		curr->next = prev;
		prev = curr;
		curr = nextTemp;
	}
	return prev;
}

/*

Given an array of integers, find if the array contains any duplicates. Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct.

*/
bool containsDuplicate(vector<int>& nums) {
	if (nums.size() <= 1)
		return false;
	set<int> ttt;
	int i = 0;
	while (ttt.insert(nums[i]).second && i < nums.size())
		i++;
	if (i == nums.size())
		return false;
	return true;
}

/*

Given an array of integers and an integer k, find out whether there are two distinct indices i and j in the array such that nums[i] = nums[j] and the absolute difference between i and j is at most k.

*/
bool containsNearbyDuplicate(vector<int>& nums, int k) {
	/*
	for (int i = 0; i < nums.size(); i++)
	for (int j = i + 1; j <= i + k; j++)
	if (nums[i] == nums[j])
	return true;
	return false;
	*///runtime no meet
	unordered_set<int> s;
	if (k <= 0) return false;
	if (k >= nums.size()) k = nums.size() - 1;

	for (int i = 0; i < nums.size(); i++)
	{
		if (i > k) s.erase(nums[i - k - 1]);
		if (s.find(nums[i]) != s.end()) return true;
		s.insert(nums[i]);
	}
	return false;
}

/*

Implement the following operations of a stack using queues.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
empty() -- Return whether the stack is empty.

*/
class MyStack {
public:
	/** Initialize your data structure here. */
	queue<int> ttt;
	MyStack() {

	}

	/** Push element x onto stack. */
	void push(int x) {
		ttt.push(x);
	}

	/** Removes the element on top of the stack and returns that element. */
	int pop() {
		for (int i = 1; i < ttt.size(); i++)
		{
			int temp = ttt.front();
			ttt.pop();
			ttt.push(temp);
		}
		int back = ttt.front();
		ttt.pop();
		return back;
	}

	/** Get the top element. */
	int top() {
		int temp;
		for (int i = 0; i < ttt.size(); i++)
		{
			temp = ttt.front();
			ttt.pop();
			ttt.push(temp);
		}
		return temp;
	}

	/** Returns whether the stack is empty. */
	bool empty() {
		return ttt.empty();
	}
};

/**
* Your MyStack object will be instantiated and called as such:
* MyStack obj = new MyStack();
* obj.push(x);
* int param_2 = obj.pop();
* int param_3 = obj.top();
* bool param_4 = obj.empty();
*/

/*

Invert a binary tree

*/
TreeNode* invertTree(TreeNode* root) {
	if (root == NULL)
		return root;
	TreeNode*temp;
	temp = root->left;
	root->left = root->right;
	root->right = temp;
	invertTree(root->left);
	invertTree(root->right);
	return root;
}

/*

Given an integer, write a function to determine if it is a power of two.

*/
bool isPowerOfTwo(int n) {
	if (n > 0 && (n&(n - 1)) == 0)
		return true;
	return false;
}

/*

Implement the following operations of a queue using stacks.

push(x) -- Push element x to the back of queue.
pop() -- Removes the element from in front of queue.
peek() -- Get the front element.
empty() -- Return whether the queue is empty.

*/
class MyQueue {

public:
	stack<int> input, output;
	void push(int x) {
		input.push(x);
	}

	int pop(void) {
		int back = peek();
		output.pop();
		return back;
	}

	int peek(void) {
		if (output.empty())
			while (input.size())
				output.push(input.top()), input.pop();
		return output.top();
	}

	bool empty(void) {
		return input.empty() && output.empty();
	}
};

/**
* Your MyQueue object will be instantiated and called as such:
* MyQueue obj = new MyQueue();
* obj.push(x);
* int param_2 = obj.pop();
* int param_3 = obj.peek();
* bool param_4 = obj.empty();
*/

/*

Given a singly linked list, determine if it is a palindrome.

*/
bool isPalindrome(ListNode* head) {
	if (head == NULL || head->next == NULL)
		return true;
	ListNode* slow = head;
	ListNode* fast = head;
	while (fast->next != NULL&&fast->next->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
	}
	slow->next = reverseList(slow->next);
	slow = slow->next;
	while (slow != NULL) {
		if (head->val != slow->val)
			return false;
		head = head->next;
		slow = slow->next;
	}
	return true;
}

/*

Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.

*/
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	vector<TreeNode*> a, b;
	TreeNode* temp = root;
	a.push_back(temp);
	while (temp != p)
	{
		if (temp->val > p->val)
		{
			temp = temp->left;
			a.push_back(temp);
		}
		else
		{
			temp = temp->right;
			a.push_back(temp);
		}
	}
	temp = root;
	b.push_back(temp);
	while (temp != q)
	{
		if (temp->val > q->val)
		{
			temp = temp->left;
			b.push_back(temp);
		}
		else
		{
			temp = temp->right;
			b.push_back(temp);
		}
	}
	int i = 0;
	while (i < a.size() && i < b.size() && a[i] == b[i])
		i++;
	return a[i - 1];
}

/*

Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.

*/
void deleteNode(ListNode* node) {
	*node = *node->next;
}

/*

Given two strings s and t, write a function to determine if t is an anagram of s.

*/
bool isAnagram(string s, string t) {
	if (s.length() != t.length())
		return false;
	unordered_map<char, int> counts;
	for (int i = 0; i < s.length(); i++)
	{
		counts[s[i]]++;
		counts[t[i]]--;
	}
	for (auto x : counts)
		if (x.second != 0)
			return false;
	return true;
}

void binaryTreePaths(vector<string>& result, TreeNode* root, string t) {
	if (!root->left && !root->right) {
		result.push_back(t);
		return;
	}

	if (root->left) binaryTreePaths(result, root->left, t + "->" + to_string(root->left->val));
	if (root->right) binaryTreePaths(result, root->right, t + "->" + to_string(root->right->val));
}


/*

Given a binary tree, return all root-to-leaf paths.

*/
vector<string> binaryTreePaths(TreeNode* root) {
	vector<string> result;
	if (!root) return result;

	binaryTreePaths(result, root, to_string(root->val));
	return result;
}

/*

Given a non-negative integer num, repeatedly add all its digits until the result has only one digit.

*/
int addDigits(int num) {
	int sum = 0;
	do {
		sum = 0;
		while (num > 0)
		{
			sum += num % 10;
			num /= 10;
		}
		num = sum;
	} while (sum >= 10);
	return sum;
}//return 1 + (num - 1) % 9;

/*

Write a program to check whether a given number is an ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 6, 8 are ugly while 14 is not ugly since it includes another prime factor 7.

Note that 1 is typically treated as an ugly number.

*/
bool isUgly(int num) {
	for (int i = 2; i<6 && num; i++)
		while (num % i == 0)
			num /= i;
	return num == 1;
}

/*

Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.

*/
int missingNumber(vector<int>& nums) {
	int x = 0;
	int i = 0;
	for (i = 0; i < nums.size(); i++) {
		x = x ^ i ^ nums[i];
	}
	return x ^ i;
}

bool isBadVersion(int version) {
	return true;
};

/*

You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.

Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.

You are given an API bool isBadVersion(version) which will return whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.

*/
int firstBadVersion(int n) {
	int lower = 1, upper = n, mid;
	while (lower < upper) {
		mid = lower + (upper - lower) / 2;
		if (!isBadVersion(mid)) lower = mid + 1;
		else upper = mid;
	}
	return lower;
}

/*

Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

For example, given nums = [0, 1, 0, 3, 12], after calling your function, nums should be [1, 3, 12, 0, 0].

*/
void moveZeroes(vector<int>& nums) {
	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] == 0)
		{
			for (int j = i + 1; j < nums.size(); j++)
			{
				if (nums[j] != 0)
				{
					nums[i] = nums[j];
					nums[j] = 0;
					break;
				}
				if (j == nums.size() - 1)
					return;
			}
		}
	}
}

/*

Given an integer (signed 32 bits), write a function to check whether it is a power of 4.

*/
bool isPowerOfFour(int num) {
	return num>0 ? (num&(num - 1)) == 0 ? (num & 0x55555555) == num ? true : false : false : false;
}

/*

Given an integer, write a function to determine if it is a power of three.

*/
bool isPowerOfThree(int n) {
	return n>0 ? 1162261467 % n == 0 ? true : false : false;
}

/*



*/

/*

Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.

*/
bool wordPattern(string pattern, string str) {
	if (pattern.length() == 0 || str.length() == 0)
		return false;
	string temp;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] != ' ')
		{
			temp.push_back(str[i]);
			i++;
		}
		while (str[i] != ' '&&i < str.length())
		{
			i++;
		}
	}
	if (temp.length() != pattern.length())
		return false;
	int ttt1[26] = { 0 }, ttt2[26] = { 0 };
	for (int i = 0; i<pattern.length(); i++)
	{
		if (ttt1[temp[i] - 'a'] == 0 && ttt2[pattern[i] - 'a'] == 0)
		{
			ttt1[temp[i] - 'a'] = pattern[i];
			ttt2[pattern[i] - 'a'] = temp[i];
		}
		else
			if (ttt1[temp[i] - 'a'] != pattern[i] || ttt2[pattern[i] - 'a'] != temp[i])
				return false;
	}
	return true;
}

/*

You are playing the following Nim Game with your friend: There is a heap of stones on the table, each time one of you take turns to remove 1 to 3 stones. The one who removes the last stone will be the winner. You will take the first turn to remove the stones.

Both of you are very clever and have optimal strategies for the game. Write a function to determine whether you can win the game given the number of stones in the heap.

For example, if there are 4 stones in the heap, then you will never win the game: no matter 1, 2, or 3 stones you remove, the last stone will always be removed by your friend.

*/
bool canWinNim(int n) {
	return n % 4 != 0;
}

/*

Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

*/
class NumArray {
public:
	vector<int> inside;
	NumArray(vector<int> nums) {
		inside = nums;
	}

	int sumRange(int i, int j) {
		int sum = 0;
		for (int x = i; x <= j; x++)
		{
			sum += inside[x];
		}
		return sum;
	}
};

/*

Write a function that takes a string as input and reverse only the vowels of a string.

*/
string reverseVowels(string s) {
	int i = 0, j = s.size() - 1;
	while (i < j) {
		i = s.find_first_of("aeiouAEIOU", i);
		j = s.find_last_of("aeiouAEIOU", j);
		if (i < j) {
			swap(s[i++], s[j--]);
		}
	}
	return s;
}

/*

Given two arrays, write a function to compute their intersection.

*/
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
	set<int> s(nums1.begin(), nums1.end());
	vector<int> out;
	for (int x : nums2)
		if (s.erase(x))
			out.push_back(x);
	return out;
}

/*

Given two arrays, write a function to compute their intersection.

*/
vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
	unordered_map<int, int> dict;
	vector<int> res;
	for (int i = 0; i < (int)nums1.size(); i++) dict[nums1[i]]++;
	for (int i = 0; i < (int)nums2.size(); i++)
		if (dict.find(nums2[i]) != dict.end() && --dict[nums2[i]] >= 0) res.push_back(nums2[i]);
	return res;
}

/*

Given a positive integer num, write a function which returns True if num is a perfect square else False.

*/
bool isPerfectSquare(int num) {
	int i = 1;
	while (num > 0) {
		num -= i;
		i += 2;
	}
	return num == 0;
}

/*

Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

*/
int getSum(int a, int b) {
	int sum = a;
	while (b != 0)
	{
		sum = a ^ b;//calculate sum of a and b without thinking the carry 
		b = (a & b) << 1;//calculate the carry
		a = sum;//add sum(without carry) and carry
	}
	return sum;
}

int guess(int num)
{
	int test = 2147483647;
	if (num > test)
		return -1;
	if (num < test)
		return 1;
	return 0;

}

/*

We are playing the Guess Game. The game is as follows:

I pick a number from 1 to n. You have to guess which number I picked.

Every time you guess wrong, I'll tell you whether the number is higher or lower.

You call a pre-defined API guess(int num) which returns 3 possible results (-1, 1, or 0):

*/
int guessNumber(int n) {
	int l = 1, h = n;
	int temp = h / 2;
	int s = guess(temp);
	while (s != 0)
	{
		if (s == 1)
			l = temp + 1;
		if (s == -1)
			h = temp - 1;
		temp = l + (h - l) / 2;
		s = guess(temp);
	}
	return temp;
}

/*

Given an arbitrary ransom note string and another string containing letters from all the magazines, write a function that will return true if the ransom note can be constructed from the magazines ; otherwise, it will return false.

Each letter in the magazine string can only be used once in your ransom note.

*/
bool canConstruct(string ransomNote, string magazine) {
	if (ransomNote.length() > magazine.length())
		return false;
	unordered_map<char, int> dict;
	for (int i = 0; i < magazine.length(); i++)
		dict[magazine[i]]++;
	for (int i = 0; i < ransomNote.length(); i++)
		if (--dict[ransomNote[i]] < 0)
			return false;
	return true;
}

/*

Given a string, find the first non-repeating character in it and return it's index. If it doesn't exist, return -1.

*/
int firstUniqChar(string s) {
	if (s.length() == 0)
		return -1;
	int table[26] = { 0 }, back[26];
	for (int i = 0; i < 26; i++)
	{
		back[i] = INT_MAX;
	}
	for (int i = 0; i < s.length(); i++)
	{
		table[s[i] - 'a']++;
		if (table[s[i] - 'a'] == 1)
			back[s[i] - 'a'] = i;
		if (table[s[i] - 'a'] > 1)
			back[s[i] - 'a'] = INT_MAX;
	}
	int* x = min_element(back, back + 26);
	if (*x == INT_MAX)
		return -1;
	return back[x - back];
}

/*

Given two strings s and t which consist of only lowercase letters.

String t is generated by random shuffling string s and then add one more letter at a random position.

Find the letter that was added in t.

*/
char findTheDifference(string s, string t) {
	char r = 0;
	for (char c : s) r ^= c;
	for (char c : t) r ^= c;
	return r;
}

/*

Find the nth digit of the infinite integer sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...

*/
int findNthDigit(int n) {
	int w10 = 1;
	int time10 = 1;
	while ((n - 1) / (9 * time10) >= w10)
	{
		n -= 9 * w10 * time10;
		w10 *= 10;
		time10++;
	}
	int wei = n%time10 == 0 ? time10 : n%time10;
	int back10 = 1;
	for (int i = 1; i < time10; i++)
		back10 *= 10;
	back10 += (n - 1)/time10;
	int back = 0;
	for (int i = wei; i < time10; i++)
	{
		back10 /= 10;
	}
	back = back10 % 10;
	return back;
}

/*

Given two strings s and t which consist of only lowercase letters.

String t is generated by random shuffling string s and then add one more letter at a random position.

Find the letter that was added in t.

*/
char findTheDifference2(string s, string t) {
	char r = 0;
	for (char c : s) r ^= c;
	for (char c : t) r ^= c;
	return r;
}

/*

A binary watch has 4 LEDs on the top which represent the hours (0-11), and the 6 LEDs on the bottom represent the minutes (0-59).

Each LED represents a zero or one, with the least significant bit on the right.

*/
vector<string> readBinaryWatch(int num) {
	vector<string> rs;
	for (int h = 0; h < 12; h++)
		for (int m = 0; m < 60; m++)
			if (bitset<10>(h << 6 | m).count() == num)
				rs.emplace_back(to_string(h) + (m < 10 ? ":0" : ":") + to_string(m));
	return rs;
}

/*

Find the sum of all left leaves in a given binary tree.

*/
int sumOfLeftLeaves(TreeNode* root) {
	if (!root) return 0;
	if (root->left && !root->left->left && !root->left->right) return root->left->val + sumOfLeftLeaves(root->right);
	return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);

}

/*

Given an integer, write an algorithm to convert it to hexadecimal. For negative integer, two’s complement method is used.

*/
string toHex(int num) {
	string back;
	unsigned int unum = num;
	if (unum == 0)
		back.push_back('0');
	while (unum> 0)
	{
		int res = unum % 16;
		if (res < 10)
			back.push_back(res + '0');
		if (res >= 10)
			back.push_back(res - 10 + 'a');
		unum = unum / 16;
	}
	reverse(back.begin(), back.end());
	return back;
}

/*

Given a string which consists of lowercase or uppercase letters, find the length of the longest palindromes that can be built with those letters.

*/
int longestPalindrome(string s) {
	int back = 0;
	int sscount = 0;
	unordered_map<char, int> ttt;
	for (int i = 0; i < s.length(); i++)
		ttt[s[i]]++;
	for (auto x = ttt.begin(); x != ttt.end(); x++)
	{
		if ((*x).second % 2 == 0)
		{
			back += (*x).second;
			continue;
		}
		if ((*x).second > 2)
		{
			if (sscount == 0)
				back += (*x).second;
			else
				back += (*x).second - 1;
			sscount = 1;
			continue;
		}
		if ((*x).second == 1)
		{
			if (sscount == 0)
				back++;
			sscount = 1;
		}
	}
	return back;
}

/*

Given a non-empty array of integers, return the third maximum number in this array. If it does not exist, return the maximum number. The time complexity must be in O(n).

*/
int thirdMax(vector<int>& nums) {
	/*
	int max1 = INT_MIN;
	int max2 = INT_MIN;
	int max3 = INT_MIN;
	for (int n : nums) {
	if(n!=INT_MIN)
	if (n == max1 || n == max2 || n == max3) continue;
	if (max1 == INT_MIN || n > max1) {
	max3 = max2;
	max2 = max1;
	max1 = n;
	}
	else if (max2 == INT_MIN || n > max2) {
	max3 = max2;
	max2 = n;
	}
	else if (max3 == INT_MIN || n > max3) {
	max3 = n;
	}
	}
	return max3 == INT_MIN ? max1 : max3;
	*///problem at INT_MIN
	//change the int to int * can solve
	set<int> top3;
	for (int num : nums)
		if (top3.insert(num).second && top3.size() > 3)
			top3.erase(top3.begin());
	return top3.size() == 3 ? *top3.begin() : *top3.rbegin();//min heap
}

/*

Given two non-negative integers num1 and num2 represented as string, return the sum of num1 and num2.

*/
string addStrings(string num1, string num2) {
	int i1 = num1.size() - 1;
	int i2 = num2.size() - 1;
	int carry = 0;
	int sum = 0;
	string back;
	while (i1 >= 0 || i2 >= 0 || carry > 0)
	{
		sum = 0;
		if (i1 >= 0)
		{
			sum += num1[i1] - '0';
			i1--;
		}
		if (i2 >= 0)
		{
			sum += num2[i2] - '0';
			i2--;
		}
		sum += carry;
		carry = sum / 10;
		back.push_back(sum % 10 + '0');
	}
	reverse(back.begin(), back.end());
	return back;
}

/*

Count the number of segments in a string, where a segment is defined to be a contiguous sequence of non-space characters.

Please note that the string does not contain any non-printable characters.

*/
int countSegments(string s) {
	int back = 0;
	for (int i = 0; i < s.length();)
	{
		if (s[i] != ' ')
		{
			back++;
			while (s[i] != ' '&&i < s.length())
				i++;
		}
		else
			i++;
	}
	return back;
}

void helper(TreeNode *p, int cur, int sum, int &total, unordered_map<int, int> &m) {
	if (!p) return;
	cur += p->val;
	if (m.find(cur - sum) != m.end()) total += m[cur - sum];
	m[cur]++;
	helper(p->left, cur, sum, total, m);
	helper(p->right, cur, sum, total, m);
	m[cur]--;
}
/*

You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

*/
int pathSum(TreeNode* root, int sum) {
	unordered_map<int, int> m;
	m[0]++;
	int total = 0;
	helper(root, 0, sum, total, m);
	return total;
}

/*

Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p will not be larger than 20,100.

The order of output does not matter.

*/
vector<int> findAnagrams(string s, string p) {
	vector<int> pv(26, 0), sv(26, 0), res;
	if (s.size() < p.size())
		return res;
	for (int i = 0; i < p.size(); ++i)
	{
		++pv[p[i] - 'a'];
		++sv[s[i] - 'a'];
	}
	if (pv == sv)
		res.push_back(0);
	for (int i = p.size(); i < s.size(); ++i)
	{
		++sv[s[i] - 'a'];
		--sv[s[i - p.size()] - 'a'];
		if (pv == sv)
			res.push_back(i - p.size() + 1);
	}
	return res;
}

/*

You have a total of n coins that you want to form in a staircase shape, where every k-th row must have exactly k coins.

Given n, find the total number of full staircase rows that can be formed.

n is a non-negative integer and fits within the range of a 32-bit signed integer.

*/
int arrangeCoins(int n) {
	return floor(-0.5 + sqrt((double)2 * n + 0.25));
}

/*

Given an array of characters, compress it in-place.

The length after compression must always be smaller than or equal to the original array.

Every element of the array should be a character (not int) of length 1.

After you are done modifying the input array in-place, return the new length of the array.

*/
int compress(vector<char>& chars) {
	int count = 1;
	int len = 0;
	vector<char>::iterator a, b;
	a = chars.begin();
	b = chars.begin();
	while (a != chars.end())
	{
		count = 1;
		while (a != chars.end() - 1 && (*a) == (*(a + 1)))
		{
			a++;
			count++;
		}
		*b = *a;
		len++;
		int w10 = 1;
		int tempc = count;
		if (count != 1)
		{
			while (tempc /= 10)
				w10 *= 10;
			while (w10 > 0)
			{
				b++;
				int res = count / w10;
				count %= w10;
				w10 /= 10;
				len++;
				*b = res + '0';
			}
		}
		a++;
		b++;
	}
	return len;
}

/*

Given n points in the plane that are all pairwise distinct, a "boomerang" is a tuple of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).

*/
int numberOfBoomerangs(vector<pair<int, int>>& points) {
	int res = 0;
	unordered_map<int,int> map;
	for (int i = 0; i<points.size(); i++) 
	{
		for (int j = 0; j<points.size(); j++) 
		{
			if (i == j)
				continue;
			int dx = points[i].first - points[j].first;
			int dy = points[i].second - points[j].second;
			int d = dx*dx + dy*dy;
			map[d]++;
		}

		for (auto val : map) 
		{
			res += val.second * (val.second - 1);
		}
		map.clear();
	}
	return res;
}

/*

Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.

Find all the elements of [1, n] inclusive that do not appear in this array.

*/
vector<int> findDisappearedNumbers(vector<int>& nums) {
	int len = nums.size();
	for (int i = 0; i<len; i++) {
		int m = abs(nums[i]) - 1; // index start from 0
		nums[m] = nums[m]>0 ? -nums[m] : nums[m];
	}
	vector<int> res;
	for (int i = 0; i<len; i++) {
		if (nums[i] > 0) res.push_back(i + 1);
	}
	return res;
}

/*

Given a non-empty integer array of size n, find the minimum number of moves required to make all array elements equal, where a move is incrementing n - 1 elements by 1.

*/
int minMoves(vector<int>& nums) {
	auto a = min_element(nums.begin(), nums.end());
	int tm = *a;
	int back = 0;
	for (int i = 0; i < nums.size(); i++)
	{
		nums[i] -= tm;
		back += nums[i];
	}
	return back;
}

/*

Assume you are an awesome parent and want to give your children some cookies. But, you should give each child at most one cookie. Each child i has a greed factor gi, which is the minimum size of a cookie that the child will be content with; and each cookie j has a size sj. If sj >= gi, we can assign the cookie j to the child i, and the child i will be content. Your goal is to maximize the number of your content children and output the maximum number.

Note:

*/
int findContentChildren(vector<int>& g, vector<int>& s) {
	int count = 0;
	sort(g.begin(), g.end());
	for (int i = g.size() - 1; i >= 0; i--)
	{
		for (int j = 0; j < s.size(); j++)
		{
			if (g[i] <= s[j])
			{
				s[j] = 0;
				count++;
				break;
			}
		}
	}
	return count;
}

/*

There are 1000 buckets, one and only one of them contains poison, the rest are filled with water. They all look the same. If a pig drinks that poison it will die within 15 minutes. What is the minimum amount of pigs you need to figure out which bucket contains the poison within one hour.

*/
int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
	int p = 0;
	while (pow((minutesToTest / minutesToDie + 1), p) < buckets)
		++p;
	return p;
}

/*

Given a non-empty string check if it can be constructed by taking a substring of it and appending multiple copies of the substring together. You may assume the given string consists of lowercase English letters only and its length will not exceed 10000.

*/
bool repeatedSubstringPattern(string s) {
	if (s.length() == 0)
		return false;
	string ss = s + s;
	string s2 = ss;
	s2.erase(s2.begin());
	s2.erase(s2.end() - 1);
	return s2.find(s) != string::npos;
}

/*

You are given a map in form of a two-dimensional integer grid where 1 represents land and 0 represents water. Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells). The island doesn't have "lakes" (water inside that isn't connected to the water around the island). One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.

*/
int islandPerimeter(vector<vector<int>>& grid) {
	int count = 0;
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			if (grid[i][j] == 0)
			{
				if (i > 0 && grid[i - 1][j] == 1)
					count++;
				if (i < grid.size() - 1 && grid[i + 1][j] == 1)
					count++;
				if (j > 0 && grid[i][j - 1] == 1)
					count++;
				if (j < grid[i].size() - 1 && grid[i][j + 1] == 1)
					count++;
			}
			else
			{
				if (j == 0)
					count++;
				if (j == grid[i].size() - 1)
					count++;
				if (i == 0)
					count++;
				if (i == grid.size() - 1)
					count++;
			}
		}
	}
	return count;
}

/*

Winter is coming! Your first job during the contest is to design a standard heater with fixed warm radius to warm all the houses.

Now, you are given positions of houses and heaters on a horizontal line, find out minimum radius of heaters so that all houses could be covered by those heaters.

So, your input will be the positions of houses and heaters seperately, and your expected output will be the minimum radius standard of heaters.

*/
int findRadius(vector<int>& houses, vector<int>& heaters) {
	if (heaters.size() == 0) {
		return 0;
	}
	sort(houses.begin(), houses.end());
	sort(heaters.begin(), heaters.end());
	int radius = 0;
	int index = 0;
	for (int i = 0; i < houses.size(); i++) {
		while (index + 1 < heaters.size() && (abs(heaters[index + 1] - houses[i]) <= abs(heaters[index] - houses[i]))) {
			index++;
		}
		radius = max(radius, abs(heaters[index] - houses[i]));
	}
	return radius;
}

/*

Find the largest palindrome made from the product of two n-digit numbers.

Since the result could be very large, you should return the largest palindrome mod 1337.

*/
int largestPalindrome(int n) {
	if (n == 1) return 9;
	if (n == 2) return 987;
	if (n == 3) return 123;
	if (n == 4) return 597;
	if (n == 5) return 677;
	if (n == 6) return 1218;
	if (n == 7) return 877;
	if (n == 8) return 475;
	return -1;
}

int result = 0;
int postOrder(TreeNode* root) {
	if (root == NULL) return 0;
	int left = postOrder(root->left);
	int right = postOrder(root->right);
	result += abs(left - right);
	return left + right + root->val;
}
/*

Given a binary tree, return the tilt of the whole tree.

The tilt of a tree node is defined as the absolute difference between the sum of all left subtree node values and the sum of all right subtree node values. Null node has tilt 0.

The tilt of the whole tree is defined as the sum of all nodes' tilt.

*/
int findTilt(TreeNode* root) {
	postOrder(root);
	return result;
}

/*

You are given two arrays (without duplicates) nums1 and nums2 where nums1’s elements are subset of nums2. Find all the next greater numbers for nums1's elements in the corresponding places of nums2.

The Next Greater Number of a number x in nums1 is the first greater number to its right in nums2. If it does not exist, output -1 for this number.

*/
vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
	stack<int> s;
	unordered_map<int, int> m;
	for (int n : nums) {
		while (s.size() && s.top() < n) {
			m[s.top()] = n;
			s.pop();
		}
		s.push(n);
	}
	vector<int> ans;
	for (int n : findNums) ans.push_back(m.count(n) ? m[n] : -1);
	return ans;
}

/*

For a web developer, it is very important to know how to design a web page's size. So, given a specific rectangular web page’s area, your job by now is to design a rectangular web page, whose length L and width W satisfy the following requirements:

*/
vector<int> constructRectangle(int area) {
	int mid = sqrt(area);
	int x = mid, y = mid;
	while (x*y != area)
	{
		if (x*y > area)
			y--;
		if (x*y < area)
			x++;
	}
	return vector<int>{x, y};
}

/*

Given a binary array, find the maximum number of consecutive 1s in this array.

*/
int findMaxConsecutiveOnes(vector<int>& nums) {
	int back = 0;
	for (int i = 0; i < nums.size();)
	{
		int count = 0;
		while (i < nums.size() && nums[i] == 0)
			i++;
		if (i == nums.size() - 1 && nums[i] == 0)
			break;
		while (i < nums.size() && nums[i] != 0)
		{
			count++;
			i++;
		}
		i++;
		back = max(back, count);
	}
	return back;
}

/*

Given an integer, return its base 7 string representation.

*/
string convertToBase7(int num) {
	string back;
	int anum = abs(num);
	if (num == 0)
		back.push_back('0');
	while (anum)
	{
		back.push_back(anum % 7 + '0');
		anum /= 7;
	}
	if (num < 0)
		back.push_back('-');
	reverse(back.begin(), back.end());
	return back;
}

vector<int> modes;
void getMaxFreq(TreeNode* r, int& mfq, int& pre, int& cnt) {
	if (!r) return;
	getMaxFreq(r->left, mfq, pre, cnt);
	getMaxFreq(r->right, mfq = max(mfq, cnt), pre = r->val, ++(cnt *= (r->val == pre)));
}

void getMode(TreeNode* r, const int mfq, int& pre, int& cnt) {
	if (!r) return;
	getMode(r->left, mfq, pre, cnt);
	if (mfq == ++(cnt *= (r->val == pre))) modes.push_back(r->val);
	getMode(r->right, mfq, pre = r->val, cnt);
}
/*

Given a binary search tree (BST) with duplicates, find all the mode(s) (the most frequently occurred element) in the given BST.

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than or equal to the node's key.
The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
Both the left and right subtrees must also be binary search trees.

*/
vector<int> findMode(TreeNode* r) {
	int mfq/*max freq*/, pre/*previous val*/, cnt/*duplicates count*/;
	getMaxFreq(r, mfq = 0, pre, cnt = 0); // in-order traversal to get max frequency
	getMode(r, mfq, pre, cnt = 0);      // in-order traversal to get all modes
	return modes;
}

/*

We define the Perfect Number is a positive integer that is equal to the sum of all its positive divisors except itself.

Now, given an integer n, write a function that returns true when it is a perfect number and false when it is not.

*/
bool checkPerfectNumber(int num) {
	static unordered_set<int> n = { 6, 28, 496, 8128, 33550336 };
	return n.count(num);
}

/*

Given scores of N athletes, find their relative ranks and the people with the top three highest scores, who will be awarded medals: "Gold Medal", "Silver Medal" and "Bronze Medal".

*/
vector<string> findRelativeRanks(vector<int>& nums) {
	priority_queue<pair<int, int> > pq;
	for (int i = 0; i<nums.size(); i++)
	{
		pq.push(make_pair(nums[i], i));
	}
	vector<string> res(nums.size(), "");
	int count = 1;
	for (int i = 0; i<nums.size(); i++)
	{
		if (count == 1) { res[pq.top().second] = "Gold Medal"; count++; }
		else if (count == 2) { res[pq.top().second] = "Silver Medal"; count++; }
		else if (count == 3) { res[pq.top().second] = "Bronze Medal"; count++; }
		else { res[pq.top().second] = to_string(count); count++; }
		pq.pop();
	}
	return res;
}

/*

Given a word, you need to judge whether the usage of capitals in it is right or not.

We define the usage of capitals in a word to be right when one of the following cases holds:

All letters in this word are capitals, like "USA".
All letters in this word are not capitals, like "leetcode".
Only the first letter in this word is capital if it has more than one letter, like "Google".
Otherwise, we define that this word doesn't use capitals in a right way.

*/
bool detectCapitalUse(string word) {
	if (word.length() < 2)
		return true;
	bool sign = (word[0] - 'A') > 25;
	bool sign2 = (word[1] - 'A') > 25;
	if (sign)
	{
		for (int i = 1; i < word.length(); i++)
		{
			if (word[i] - 'A' < 26)
				return false;
		}
	}
	else
	{
		if (sign2)
		{
			for (int i = 2; i < word.length(); i++)
				if (word[i] - 'A' < 26)
					return false;
		}
		else
		{
			for (int i = 2; i < word.length(); i++)
				if (word[i] - 'A' > 25)
					return false;
		}
	}
	return true;
}

/*

You are given a string representing an attendance record for a student. The record only contains the following three characters:

'A' : Absent.
'L' : Late.
'P' : Present.
A student could be rewarded if his attendance record doesn't contain more than one 'A' (absent) or more than two continuous 'L' (late).

You need to return whether the student could be rewarded according to his attendance record.

*/
bool checkRecord(string s) {
	unordered_map<char, int> map;
	for (int i = 0; i < s.length(); i++)
		map[s[i]]++;
	if (map['A'] > 1 || map['L'] > 2)
		return false;
	return true;
}

int dmax = 0;
int maxDepth2(TreeNode* root) {
	if (root == NULL) return 0;
	int left = maxDepth2(root->left);
	int right = maxDepth2(root->right);
	dmax = max(dmax, left + right);
	return max(left, right) + 1;
}
/*

Given a binary tree, you need to compute the length of the diameter of the tree. The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.

*/
int diameterOfBinaryTree(TreeNode* root) {
	maxDepth2(root);
	return dmax;
}

/*

Given a string and an integer k, you need to reverse the first k characters for every 2k characters counting from the start of the string. If there are less than k characters left, reverse all of them. If there are less than 2k but greater than or equal to k characters, then reverse the first k characters and left the other as original.

*/
string reverseStr(string s, int k) {
	for (int i = 0; i < s.size(); i += 2 * k) reverse(s.begin() + i, min(s.begin() + i + k, s.end()));
	return s;
}

/*

Given a group of two strings, you need to find the longest uncommon subsequence of this group of two strings. The longest uncommon subsequence is defined as the longest subsequence of one of these strings and this subsequence should not be any subsequence of the other strings.

A subsequence is a sequence that can be derived from one sequence by deleting some characters without changing the order of the remaining elements. Trivially, any string is a subsequence of itself and an empty string is a subsequence of any string.

The input will be two strings, and the output needs to be the length of the longest uncommon subsequence. If the longest uncommon subsequence doesn't exist, return -1.

*/
int findLUSlength(string a, string b) {
	return a == b ? -1 : max(a.length(), b.length());
}

int min_dif = INT_MAX, val = -1;
/*

Given a binary search tree with non-negative values, find the minimum absolute difference between values of any two nodes.

*/
int getMinimumDifference(TreeNode* root) {
	if (root->left != NULL) getMinimumDifference(root->left);
	if (val >= 0) min_dif = min(min_dif, root->val - val);
	val = root->val;
	if (root->right != NULL) getMinimumDifference(root->right);
	return min_dif;
}

/*

Given a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus sum of all keys greater than the original key in BST.

*/
TreeNode* convertBST(TreeNode* root) {
	int sum = 0;
	TreeNode* node = root;
	stack<TreeNode*> stack;
	while (!stack.empty() || node != NULL) {
		while (node != NULL) {
			stack.push(node);
			node = node->right;
		}
		node = stack.top();
		stack.pop();
		sum += node->val;
		node->val = sum;
		node = node->left;
	}
	return root;
}

/*

Given an array of integers and an integer k, you need to find the number of unique k-diff pairs in the array. Here a k-diff pair is defined as an integer pair (i, j), where i and j are both numbers in the array and their absolute difference is k.

*/
int findPairs(vector<int>& nums, int k) {
	if (nums.size() == 0 || k < 0)   return 0;
	map<int, int> mmap;
	int count = 0;
	for (int i : nums) {
		mmap[i]++;
	}
	for (auto entry : mmap) {
		if (k == 0) {
			if (entry.second >= 2) {
				count++;
			}
		}
		else {
			if (mmap.find(entry.first + k) != mmap.end()) {
				count++;
			}
		}
	}
	return count;
}

/*

Given a 2D integer matrix M representing the gray scale of an image, you need to design a smoother to make the gray scale of each cell becomes the average gray scale (rounding down) of all the 8 surrounding cells and itself. If a cell has less than 8 surrounding cells, then use as many as you can.

*/
vector<vector<int>> imageSmoother(vector<vector<int>>& M) {
	/*<vector<int>> B = M;
	for (int i = 0; i < M.size(); i++)
	{
	for (int j = 0; j < M[i].size(); j++)
	{
	if (i == 0 && j == 0)
	{
	B[i][j] = M[i][j] + M[i + 1][j + 1] + M[i + 1][j] + M[i][j + 1];
	B[i][j] /= 4;
	continue;//d4
	}
	if (i == M.size() - 1&& j == M[i].size() - 1)
	{
	B[i][j] = M[i][j] + M[i - 1][j - 1] + M[i - 1][j] + M[i][j - 1];
	B[i][j] /= 4;
	continue;//d4
	}
	if (i == 0 && j == M[i].size() - 1)
	{
	B[i][j] = M[i][j] + M[i + 1][j - 1] + M[i + 1][j] + M[i][j - 1];
	B[i][j] /= 4;
	continue;//d4
	}
	if (i == M.size() - 1 && j == 0)
	{
	B[i][j] = M[i][j] + M[i - 1][j + 1] + M[i - 1][j] + M[i][j + 1];
	B[i][j] /= 4;
	continue;//d4
	}
	if (i == 0)
	{
	B[i][j] = M[i][j] + M[i + 1][j] + M[i + 1][j + 1] + M[i][j - 1] + M[i][j + 1] + M[i + 1][j - 1];
	B[i][j] /= 6;
	continue;//d6
	}
	if (i == M.size() - 1)
	{
	B[i][j] = M[i][j] + M[i - 1][j] + M[i - 1][j + 1] + M[i][j - 1] + M[i][j - 1] + M[i - 1][j - 1];
	B[i][j] /= 6;
	continue;//d6
	}
	if (j==0)
	{
	B[i][j] = M[i][j] + M[i][j + 1] + M[i - 1][j] + M[i + 1][j] + M[i + 1][j + 1] + M[i - 1][j + 1];
	B[i][j] /= 6;
	continue;//d6
	}
	if (j == M[i].size() - 1)
	{
	B[i][j] = M[i][j] + M[i][j - 1] + M[i - 1][j] + M[i + 1][j] + M[i + 1][j - 1] + M[i - 1][j - 1];
	B[i][j] /= 6;
	continue;//d6
	}
	//others d9
	B[i][j] = M[i][j] + M[i - 1][j] + M[i + 1][j] + M[i][j - 1] + M[i][j + 1] + M[i - 1][j - 1] + M[i + 1][j + 1] + M[i + 1][j - 1] + M[i - 1][j + 1];
	B[i][j] /= 9;
	}
	}
	return B;*/
	int m = M.size(), n = M[0].size();
	if (m == 0 || n == 0) return{ {} };
	vector<vector<int>> dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 }, { -1, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 } };
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			int sum = M[i][j], cnt = 1;
			for (int k = 0; k < dirs.size(); k++) {
				int x = i + dirs[k][0], y = j + dirs[k][1];
				if (x < 0 || x > m - 1 || y < 0 || y > n - 1) continue;
				sum += (M[x][y] & 0xFF);
				cnt++;
			}
			M[i][j] |= ((sum / cnt) << 8);
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			M[i][j] >>= 8;
		}
	}
	return M;
}

class Employee {
public:
	// It's the unique ID of each node.
	// unique id of this employee
	int id;
	// the importance value of this employee
	int importance;
	// the id of direct subordinates
	vector<int> subordinates;
};
/*

You are given a data structure of employee information, which includes the employee's unique id, his importance value and his direct subordinates' id.

For example, employee 1 is the leader of employee 2, and employee 2 is the leader of employee 3. They have importance value 15, 10 and 5, respectively. Then employee 1 has a data structure like [1, 15, [2]], and employee 2 has [2, 10, [3]], and employee 3 has [3, 5, []]. Note that although employee 3 is also a subordinate of employee 1, the relationship is not direct.

Now given the employee information of a company, and an employee id, you need to return the total importance value of this employee and all his subordinates.

*/
int getImportance(vector<Employee*> employees, int id) {
	map<int, Employee> mmm;
	for (int i = 0; i < employees.size(); i++)
		mmm[employees[i]->id] = *employees[i];
	int sum = 0;
	queue<Employee> vvv;
	vvv.push(mmm[id]);
	while (!vvv.empty())
	{
		sum += vvv.front().importance;
		if (!vvv.front().subordinates.empty())
			for (int i = 0; i < vvv.front().subordinates.size(); i++)
				vvv.push(mmm[vvv.front().subordinates[i]]);
		vvv.pop();
	}
	return sum;
}

/*

Given a list of strings words representing an English Dictionary, find the longest word in words that can be built one character at a time by other words in words. If there is more than one possible answer, return the longest word with the smallest lexicographical order.

If there is no answer, return the empty string.

*/
string longestWord(vector<string>& words) {
	sort(words.begin(), words.end());
	unordered_set<string> built;
	string res;
	for (string w : words) {
		if (w.size() == 1 || built.count(w.substr(0, w.size() - 1))) {
			res = w.size() > res.size() ? w : res;
			built.insert(w);
		}
	}
	return res;
}

/*

We have two special characters. The first character can be represented by one bit 0. The second character can be represented by two bits (10 or 11).

Now given a string represented by several bits. Return whether the last character must be a one-bit character or not. The given string will always end with a zero.

*/
bool isOneBitCharacter(vector<int>& bits) {
	int i = 0;
	while (i < bits.size() - 1) {
		i += bits[i] + 1;
	}
	return i == bits.size() - 1;
}

/*

Given a non-empty array of non-negative integers nums, the degree of this array is defined as the maximum frequency of any one of its elements.

Your task is to find the smallest possible length of a (contiguous) subarray of nums, that has the same degree as nums.

*/
int findShortestSubArray(vector<int>& nums) {
	map<int, int> mmm;
	for (int i = 0; i < nums.size(); i++)
		mmm[nums[i]]++;
	int dmax = 0;
	for (auto i = mmm.begin(); i != mmm.end(); i++)
		dmax = max(dmax, (*i).second);
	int count = INT_MAX;
	for (auto i = mmm.begin(); i != mmm.end(); i++)
	{
		if ((*i).second == dmax)
		{
			int j = 0;
			while (nums[j] != (*i).first)
				j++;
			int ccc = 0;
			int tempconut = 0;
			for (; j < nums.size(); j++)
			{
				if (nums[j] == (*i).first)
					ccc++;
				tempconut++;
				if (ccc == (*i).second)
					break;
			}
			count = min(count, tempconut);
		}
	}
	return count;
}

/*

Give a string s, count the number of non-empty (contiguous) substrings that have the same number of 0's and 1's, and all the 0's and all the 1's in these substrings are grouped consecutively.

Substrings that occur multiple times are counted the number of times they occur.

*/
int countBinarySubstrings(string s) {
	int* groups = new int[s.length()];
	int t = 0;
	groups[0] = 1;
	for (int i = 1; i < s.length(); i++) {
		if (s[i - 1] != s[i]) {
			groups[++t] = 1;
		}
		else {
			groups[t]++;
		}
	}
	int ans = 0;
	for (int i = 1; i <= t; i++) {
		ans += min(groups[i - 1], groups[i]);
	}
	return ans;
}

/*

Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

Find the maximum area of an island in the given 2D array. (If there is no island, the maximum area is 0.)

*/
int maxAreaOfIsland(vector<vector<int>>& grid) {
	int maxa = 0;
	queue<pair<int, int>> qqq;
	map<pair<int, int>, int> mmm;
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			if (!mmm.count({ i, j }) && grid[i][j] == 1)
			{
				mmm.erase(mmm.begin(), mmm.end());
				qqq.push({ i, j });
				mmm[{i, j}]++;
				int am = 0;
				int x = -1;
				int y = -1;
				while (!qqq.empty())
				{
					am++;
					x = qqq.front().first;
					y = qqq.front().second;
					if (x > 0 && grid[x - 1][y] == 1 && !mmm.count({ x - 1, y }))
					{
						qqq.push({ x - 1, y });
						mmm[{x - 1, y}]++;
					}
					if (x < grid.size() - 1 && grid[x + 1][y] == 1 && !mmm.count({ x + 1, y }))
					{
						qqq.push({ x + 1, y });
						mmm[{x + 1, y}]++;
					}
					if (y > 0 && grid[x][y - 1] == 1 && !mmm.count({ x, y - 1 }))
					{
						qqq.push({ x, y - 1 });
						mmm[{x, y - 1}]++;
					}
					if (y < grid[x].size() - 1 && grid[x][y + 1] == 1 && !mmm.count({ x, y + 1 }))
					{
						qqq.push({ x, y + 1 });
						mmm[{x, y + 1}]++;
					}
					qqq.pop();
				}
				maxa = max(maxa, am);
			}
		}
	}
	return maxa;
}

/*

Given a positive integer, check whether it has alternating bits: namely, if two adjacent bits will always have different values.

*/
bool hasAlternatingBits(int n) {
	return !((n ^= n / 2) & n + 1);
}

/*

Given an array of integers nums, write a method that returns the "pivot" index of this array.

We define the pivot index as the index where the sum of the numbers to the left of the index is equal to the sum of the numbers to the right of the index.

If no such index exists, we should return -1. If there are multiple pivot indexes, you should return the left-most pivot index.

*/
int pivotIndex(vector<int>& nums) {
	if (nums.size() < 3)
		return -1;
	int sumtotal = 0;
	for (int i = 0; i < nums.size(); i++)
		sumtotal += nums[i];
	int sum1 = 0;
	int sum2 = sumtotal;
	int x;
	for (x = 0; x < nums.size(); x++)
	{
		sum2 -= nums[x];
		sum1 = sumtotal - nums[x] - sum2;
		if (sum1 == sum2)
			return x;
	}
	return -1;
}

int ans;
int arrowLength(TreeNode* node) {
	if (node == NULL) return 0;
	int left = arrowLength(node->left);
	int right = arrowLength(node->right);
	int arrowLeft = 0, arrowRight = 0;
	if (node->left != NULL && node->left->val == node->val) {
		arrowLeft += left + 1;
	}
	if (node->right != NULL && node->right->val == node->val) {
		arrowRight += right + 1;
	}
	ans = max(ans, arrowLeft + arrowRight);
	return max(arrowLeft, arrowRight);
}
/*

Given a binary tree, find the length of the longest path where each node in the path has the same value. This path may or may not pass through the root.

*/
int longestUnivaluePath(TreeNode* root) {
	ans = 0;
	arrowLength(root);
	return ans;
}

/*

Given two strings A and B, find the minimum number of times A has to be repeated such that B is a substring of it. If no such solution, return -1.

For example, with A = "abcd" and B = "cdabcdab".

Return 3, because by repeating A three times (“abcdabcdabcd”), B is a substring of it; and B is not a substring of A repeated two times ("abcdabcd").

*/
int repeatedStringMatch(string A, string B) {
	vector<int> prefTable(B.size() + 1); // 1-based to avoid extra checks.
	for (auto sp = 1, pp = 0; sp < B.size(); prefTable[++sp] = pp) {
		pp = B[pp] == B[sp] ? pp + 1 : prefTable[pp];
	}
	for (auto i = 0, j = 0; i < A.size(); i += max(1, j - prefTable[j]), j = prefTable[j]) {
		while (j < B.size() && A[(i + j) % A.size()] == B[j]) ++j;
		if (j == B.size()) return (i + j) / A.size() + ((i + j) % A.size() != 0 ? 1 : 0);
	}
	return -1;
}

/*

Given an array with n integers, your task is to check if it could become non-decreasing by modifying at most 1 element.

We define an array is non-decreasing if array[i] <= array[i + 1] holds for every i (1 <= i < n).

*/
bool checkPossibility(vector<int>& nums) {
	int cnt = 0;
	for (int i = 1; i < nums.size() && cnt <= 1; i++) {
		if (nums[i - 1] > nums[i]) {
			cnt++;
			if (i - 2<0 || nums[i - 2] <= nums[i])
				nums[i - 1] = nums[i];
			else nums[i] = nums[i - 1];
		}
	}
	return cnt <= 1;
}

int minval(TreeNode* p, int first) {
	if (p == nullptr) return -1;
	if (p->val != first) return p->val;
	int left = minval(p->left, first), right = minval(p->right, first);
	// if all nodes of a subtree = root->val, 
	// there is no second minimum value, return -1
	if (left == -1) return right;
	if (right == -1) return left;
	return min(left, right);
}
/*

Given a non-empty special binary tree consisting of nodes with the non-negative value, where each node in this tree has exactly two or zero sub-node. If the node has two sub-nodes, then this node's value is the smaller value among its two sub-nodes.

Given such a binary tree, you need to output the second minimum value in the set made of all the nodes' value in the whole tree.

If no such second minimum value exists, output -1 instead.

*/
int findSecondMinimumValue(TreeNode* root) {
	if (!root) return -1;
	int ans = minval(root, root->val);
	return ans;
}

/*

Given an unsorted array of integers, find the length of longest continuous increasing subsequence.

*/
int findLengthOfLCIS(vector<int>& nums) {
	int res = 0, cnt = 0;
	for (int i = 0; i < nums.size(); i++) {
		if (i == 0 || nums[i - 1] < nums[i]) res = max(res, ++cnt);
		else cnt = 1;
	}
	return res;
}

bool isPalindromic(string s, int l, int r) {
	while (++l < --r)
		if (s[l] != s[r]) return false;
	return true;
}
/*

Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome.

*/
bool validPalindrome(string s) {
	int l = -1, r = s.length();
	while (++l < --r)
		if (s[l] != s[r]) return isPalindromic(s, l, r + 1) || isPalindromic(s, l - 1, r);
	return true;
}

bool equals(TreeNode* x, TreeNode* y)
{
	if (x == NULL && y == NULL)
		return true;
	if (x == NULL || y == NULL)
		return false;
	return x->val == y->val && equals(x->left, y->left) && equals(x->right, y->right);
}
bool traverse(TreeNode* s, TreeNode* t)
{
	return  s != NULL && (equals(s, t) || traverse(s->left, t) || traverse(s->right, t));
}
/*

Given two non-empty binary trees s and t, check whether tree t has exactly the same structure and node values with a subtree of s. A subtree of s is a tree consists of a node in s and all of this node's descendants. The tree s could also be considered as a subtree of itself.

*/
bool isSubtree(TreeNode* s, TreeNode* t) {
	return traverse(s, t);
}

/*

Given an integer array, you need to find one continuous subarray that if you only sort this subarray in ascending order, then the whole array will be sorted in ascending order, too.

You need to find the shortest such subarray and output its length.

*/
int findUnsortedSubarray(vector<int>& nums) {
	int minn = INT_MAX, maxn = INT_MIN;
	bool flag = false;
	for (int i = 1; i < nums.size(); i++) {
		if (nums[i] < nums[i - 1])
			flag = true;
		if (flag)
			minn = min(minn, nums[i]);
	}
	flag = false;
	for (int i = nums.size() - 2; i >= 0; i--) {
		if (nums[i] > nums[i + 1])
			flag = true;
		if (flag)
			maxn = max(maxn, nums[i]);
	}
	int l, r;
	for (l = 0; l < nums.size(); l++) {
		if (minn < nums[l])
			break;
	}
	for (r = nums.size() - 1; r >= 0; r--) {
		if (maxn > nums[r])
			break;
	}
	return r - l < 0 ? 0 : r - l + 1;
}

/*

We define a harmonious array is an array where the difference between its maximum value and its minimum value is exactly 1.

Now, given an integer array, you need to find the length of its longest harmonious subsequence among all its possible subsequences.

*/
int findLHS(vector<int>& nums) {
	map<int, int> mmm;
	int back = 0;
	for (int i = 0; i < nums.size(); i++)
		mmm[nums[i]]++;
	for (auto a = mmm.begin(); a != mmm.end(); a++)
		if (mmm.count((*a).first + 1))
			back = max(back, (*a).second + mmm[(*a).first + 1]);
	return back;
}

string tb;
/*

You need to construct a string consists of parenthesis and integers from a binary tree with the preorder traversing way.

The null node needs to be represented by empty parenthesis pair "()". And you need to omit all the empty parenthesis pairs that don't affect the one-to-one mapping relationship between the string and the original binary tree.

*/
string tree2str(TreeNode* t) {
	if (t == NULL)
		return "";
	stack<TreeNode*> stack;
	stack.push(t);
	unordered_set<TreeNode*> visited;
	string s;
	while (!stack.empty()) {
		t = stack.top();
		if (visited.count(t)) {
			stack.pop();
			s.append(")");
		}
		else {
			visited.insert(t);
			s.append("(" + to_string(t->val));
			if (t->left == NULL && t->right != NULL)
				s.append("()");
			if (t->right != NULL)
				stack.push(t->right);
			if (t->left != NULL)
				stack.push(t->left);
		}
	}
	return s.substr(1, s.length() - 2);
}

/*

You need to construct a string consists of parenthesis and integers from a binary tree with the preorder traversing way.

The null node needs to be represented by empty parenthesis pair "()". And you need to omit all the empty parenthesis pairs that don't affect the one-to-one mapping relationship between the string and the original binary tree.

*/
string tree2str2(TreeNode* t) {
	if (t == NULL)
		return "";
	stack<TreeNode*> stack;
	stack.push(t);
	unordered_set<TreeNode*> visited;
	string s;
	while (!stack.empty()) {
		t = stack.top();
		if (visited.count(t)) {
			stack.pop();
			s.append(")");
		}
		else {
			visited.insert(t);
			s.append("(" + to_string(t->val));
			if (t->left == NULL && t->right != NULL)
				s.append("()");
			if (t->right != NULL)
				stack.push(t->right);
			if (t->left != NULL)
				stack.push(t->left);
		}
	}
	return s.substr(1, s.length() - 2);
}

vector<int> vvvi;
void findtargetson(TreeNode* root) {
	if (root == NULL)
		return;
	vvvi.push_back(root->val);
	findtargetson(root->left);
	findtargetson(root->right);
}
/*

Given a Binary Search Tree and a target number, return true if there exist two elements in the BST such that their sum is equal to the given target.

*/
bool findTarget(TreeNode* root, int k) {
	findtargetson(root);
	for (int i = 0; i < vvvi.size() - 1; i++)
	{
		for (int j = i + 1; j < vvvi.size(); j++)
		{
			if (vvvi[i] + vvvi[j] == k)
				return true;
		}
	}
	return false;
}

/*

The set S originally contains numbers from 1 to n. But unfortunately, due to the data error, one of the numbers in the set got duplicated to another number in the set, which results in repetition of one number and loss of another number.

Given an array nums representing the data status of this set after the error. Your task is to firstly find the number occurs twice and then find the number that is missing. Return them in the form of an array.

*/
vector<int> findErrorNums(vector<int>& nums) {
	map<int, int> mmm;
	int dup = -1, missing = 1;
	for (int n : nums) {
		mmm[n]++;
	}
	for (int i = 1; i <= nums.size(); i++) {
		if (mmm.count(i)) {
			if (mmm[i] == 2)
				dup = i;
		}
		else
			missing = i;
	}
	return vector<int>{dup, missing};
}

/*

Given an array consisting of n integers, find the contiguous subarray of given length k that has the maximum average value. And you need to output the maximum average value.

*/
double findMaxAverage(vector<int>& nums, int k) {
	double back = INT_MIN;
	for (int i = 0; i < nums.size() - k + 1; i++)
	{
		double sum = 0;
		for (int j = i; j < i + k; j++)
		{
			sum += nums[j];
		}
		back = max(back, sum / k);
	}
	return back;
}

/*

Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.

*/
vector<double> averageOfLevels(TreeNode* root) {
	if (root == NULL)
		return vector<double>{};
	queue<TreeNode*> qqq;
	vector<double> back;
	int thisround = 1;
	int nextround = 0;
	qqq.push(root);
	while (!qqq.empty())
	{
		double tempsum = 0;
		for (int i = 0; i < thisround; i++)
		{
			TreeNode* tempt;
			tempt = qqq.front();
			if (tempt->left != NULL)
			{
				qqq.push(tempt->left);
				nextround++;
			}
			if (tempt->right != NULL)
			{
				qqq.push(tempt->right);
				nextround++;
			}
			tempsum += tempt->val;
			qqq.pop();

		}
		back.push_back(tempsum / thisround);
		thisround = nextround;
		nextround = 0;
	}
	return back;
}

/*

Given a non-negative integer c, your task is to decide whether there're two integers a and b such that a2 + b2 = c.

*/
bool judgeSquareSum(int c) {
	for (long a = 0; a * a <= c; a++) {
		double b = sqrt(c - a * a);
		if (b == (int)b)
			return true;
	}
	return false;
}

/*

Given an integer array, find three numbers whose product is maximum and output the maximum product.

*/
int maximumProduct(vector<int>& nums) {
	sort(nums.begin(), nums.end());
	int n = nums.size();
	int temp1 = nums[n - 1] * nums[n - 2] * nums[n - 3];
	int temp2 = nums[0] * nums[1] * nums[n - 1];
	return temp1>temp2 ? temp1 : temp2;
}

/*

Suppose you have a long flowerbed in which some of the plots are planted and some are not. However, flowers cannot be planted in adjacent plots - they would compete for water and both would die.

Given a flowerbed (represented as an array containing 0 and 1, where 0 means empty and 1 means not empty), and a number n, return if n new flowers can be planted in it without violating the no-adjacent-flowers rule.

*/
bool canPlaceFlowers(vector<int>& flowerbed, int n) {
	int templen;
	int count = 0;
	if (flowerbed[0] == 1)
		templen = 0;
	else
		templen = 1;
	for (int i = 0; i < flowerbed.size(); i++)
	{
		if (flowerbed[i] == 1)
		{
			count += (int)(((float)(templen - 2)) / 2 + 0.5);
			templen = 0;
			continue;
		}
		templen++;
		if (i == flowerbed.size() - 1)
			count += (int)(((float)(templen - 1)) / 2 + 0.5);
	}

	if (count >= n)
		return true;
	return false;
}

/*

Suppose Andy and Doris want to choose a restaurant for dinner, and they both have a list of favorite restaurants represented by strings.

You need to help them find out their common interest with the least list index sum. If there is a choice tie between answers, output all of them with no order requirement. You could assume there always exists an answer.

*/
vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
	vector<string> back;
	int sumnow = INT_MAX;
	for (int i = 0; i < list1.size(); i++)
	{
		for (int j = 0; j < list2.size(); j++)
		{
			if (list1[i] == list2[j])
			{
				if (i + j == sumnow)
					back.push_back(list2[j]);
				if (i + j < sumnow)
				{
					back.erase(back.begin(), back.end());
					back.push_back(list2[j]);
					sumnow = i + j;
				}
			}
		}
	}
	return back;
}

/*

Given an m * n matrix M initialized with all 0's and several update operations.

Operations are represented by a 2D array, and each operation is represented by an array with two positive integers a and b, which means M[i][j] should be added by one for all 0 <= i < a and 0 <= j < b.

*/
int maxCount(int m, int n, vector<vector<int>>& ops) {
	for (int i = 0; i < ops.size(); ++i) {
		m = min(m, ops[i][0]);
		n = min(n, ops[i][1]);
	}
	return m*n;
}

/*



*/













int main()
{
	vector<string> xxx1 = { "Shogun", "Tapioca Express", "Burger King", "KFC"};
	vector<string> xxx2 = { "KFC", "Shogun", "Burger King" };
	findRestaurant(xxx1, xxx2);
    return 0;
}

