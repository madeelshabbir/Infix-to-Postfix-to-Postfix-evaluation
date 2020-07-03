#include<iostream>
#include<string>
using namespace std;
template <typename Object>
class StackADT
{
public:
	virtual bool isEmpty() const = 0;
	virtual long sSize() const = 0;
	virtual Object peek() const = 0;
	virtual void push(const Object &) = 0;
	virtual Object pop() = 0;
};
template <typename Object>
class StackL : public StackADT<Object>
{
private:
	class ListNode
	{
	public:
		Object data;
		ListNode* next;
		ListNode(Object d)
		{
			data = d;
			next = NULL;
		}
	};
	ListNode* head;
	long top;
public:
	StackL()
	{
		head = NULL;
		top = 0;
	}
	~StackL()
	{
		while (head != NULL)
		{
			ListNode *junk = head;
			head = head->next;
			delete junk;
		}
		head = NULL;
	}
	bool isEmpty() const
	{
		return (head == NULL);
	}
	long sSize() const
	{
		return top;
	}
	Object peek() const
	{
		if (isEmpty())
		{
			return 'n';
		}
		return head->data;
	}
	void push(const Object &d)
	{
		top++;
		if (isEmpty())
		{
			head = new ListNode(d);
			return;
		}
		ListNode* tmp = new ListNode(d);
		tmp->next = head;
		head = tmp;
	}
	Object pop()
	{
		if (isEmpty())
		{
			throw 0;
		}
		ListNode* tmp = head;
		head = head->next;
		Object o = tmp->data;
		delete tmp;
		top--;
		return o;
	}
};
bool isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c== '^' || c == '(' || c == ')')
		return true;
	return false;
}
int preceDence(char op)
{
	if (op == '+' || op == '-')
		return 1;
	else if (op == '*' || op == '/')
		return 2;
	else if (op == '^')
		return 3;
	else
		return -1;
}
void infixToPostfix(const char* inFix, char* postFix)
{
	int k = 0;
	StackADT<char> *s = new StackL<char>;
	for(int i = 0; i<strlen(inFix); i++)
	{
		if(!isOperator(inFix[i]))
		{
			postFix[k++] = inFix[i];
		}
		else
		{
			if (preceDence(s->peek()) > preceDence(inFix[i]) && preceDence(inFix[i]) != -1)
			{
				postFix[k++] = s->pop();
				s->push(inFix[i]);
			}
			else
			{
				if (inFix[i] == ')')
				{
					while (s->peek() != '(')
					{
						postFix[k++] = s->pop();
					}
					s->pop();
				}
				else
				{
					s->push(inFix[i]);
				}
			}
		}
	}
	while (!s->isEmpty())
	{
		if (s->peek() != '(' || s->peek() != ')')
			postFix[k++] = s->pop();
		else
			s->pop();
	}
	postFix[k] = '\0';
}
double opeRation(double op1, double op2, char opr)
{
	if (opr == '+')
		return op1 + op2;
	else if (opr == '-')
		return op1 - op2;
	else if (opr == '*')
		return op1 * op2;
	else if (opr == '/')
	{
		if (opr == 0)
			throw 0;
		return op1 / op2;
	}
	else if (opr == '^')
		return pow(op1, op2);
	else
		throw 0;
}
double evaluatePostfix(const char* postFix)
{
	StackADT<int> *s = new StackL<int>;
	for (int i = 0; i<strlen(postFix); i++)
	{
		if (!isOperator(postFix[i]))
		{
			s->push(int(postFix[i]) - 48);
		}
		else
		{
			int op2 = s->pop(), op1 = s->pop();
			s->push(opeRation(op1, op2, postFix[i]));
		}
	}
	return s->pop();
}
int main()
{
	string s = "1+2*3";
	char *s2 = new char[s.length()];
	infixToPostfix(s.c_str(), s2);
	cout << s2 << endl;
	cout << evaluatePostfix(s2) << endl;
	system("pause");
}