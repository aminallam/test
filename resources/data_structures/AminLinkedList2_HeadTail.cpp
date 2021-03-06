// Author:  Amin Allam
// Program: Linked list with head and tail

#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////

typedef int Data;

///////////////////////////////////////////////////////////////////////////////////////////////

struct Node
{
	Data	data;
	Node*	next;	// link to the next node, contains the address of the next node
};

///////////////////////////////////////////////////////////////////////////////////////////////

class List
{
	Node* head;
	Node* tail;
public:
	List();
	void InsertFirst(Data d);		// Insert at first
	void InsertLast(Data d);		// Insert at Last
	void InsertAt(int i, Data d);	// Insert at index i (where i=0 is first)
	void InsertOrdered(Data d);		// Insert in its order
	void Delete(Data d);			// Delete element d
	void Print();					// Print list elements
	void Destroy();					// Destroy list
	~List();
};

///////////////////////////////////////////////////////////////////////////////////////////////

// List a
// List:
// a.InsertFirst(3)
// List: 3
// a.InsertLast(7)
// List: 3 7
// a.InsertAt(1, 4)
// List: 3 4 7
// a.InsertOrdered(5)
// List: 3 4 5 7
// a.Delete(6)
// List: 3 4 5 7
// a.Delete(4)
// List: 3 5 7
// a.Destroy()
// List:

///////////////////////////////////////////////////////////////////////////////////////////////

List::List()
{
	head = 0;		// 0 is the same as NULL
	tail = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void List::InsertFirst(Data d)		// Insert at first
{
	Node* node = new Node;
	node->data = d;

	node->next = head;
	head = node;

	if(node->next == 0)
		tail = node;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void List::InsertLast(Data d)		// Insert at last
{
	Node* node = new Node;
	node->data = d;
	node->next = 0;

	if(head == 0)
	{
		head = node;
		tail = node;
		return;
	}

	tail->next = node;
	tail = node;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void List::InsertAt(int i, Data d)	// Insert at index i (where i=0 is first)
{
	if(i<0) return;

	if(i==0)
	{
		InsertFirst(d);
		return;
	}

	// Initially we are at node head (the node whose address is in head), which is at index 0 (first node)

	int j=0;
	Node* cur = head;

	// Move cur until it contains the address of the node at index i-1

	while(j!=i-1 && cur != 0)
	{
		cur = cur->next;
		j++;
	}

	// Here, cur contains the address of the node at index i-1
	//  which is the node before the location where we want to insert
	// So, cur is the node before which we want to insert (or cur=0 if i is too large)

	if(cur != 0)
	{
		Node* node = new Node;
		node->data = d;

		node->next = cur->next;
		cur->next = node;

		if(node->next == 0)
			tail = node;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void List::InsertOrdered(Data d)		// Insert in its order
{
	Node* node = new Node;
	node->data = d;

	if(head==0 || head->data > d)
	{
		node->next = head;
		head = node;

		if(node->next == 0)
			tail = node;

		return;
	}

	Node* prev = head;
	Node* cur = head->next;

	// Move prev until it reaches the node before the location where we want to insert

	while(cur != 0 && cur->data <= d)
	{
		prev = cur;
		cur = cur->next;
	}

	// Here, cur contains the address of the node whose data > d (or cur=0)
	// Here, prev contains the address of the node before cur (or prev=address of last node)

	node->next = cur;
	prev->next = node;

	if(node->next == 0)
		tail = node;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void List::Delete(Data d)				// Delete element d
{
	if(head==0)
		return;

	if(head->data == d)
	{
		Node* temp = head;
		head = head->next;
		delete temp;

		if(head == 0 || head->next == 0)
			tail = head;

		return;
	}

	// Move prev until it reaches the node before the node we want to delete

	Node* prev = head;
	Node* cur = head->next;

	while(cur != 0 && cur->data != d)
	{
		prev = cur;
		cur = cur->next;
	}

	// Here, cur contains the address of the node whose data == d (or cur=0)
	// Here, prev contains the address of the node before cur (or prev=address of last node)

	if(cur != 0)
	{
		prev->next = cur->next;
		delete cur;

		if(prev->next == 0)
			tail = prev;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void List::Print()					// Print list elements
{
	cout << "List: ";

	Node* cur = head;

	while(cur != 0)
	{
		cout << cur->data << " ";
		cur = cur->next;
	}

	cout << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void List::Destroy()
{
	Node* cur = head;

	while(cur != 0)
	{
		Node* temp = cur->next;
		delete cur;
		cur = temp;
	}

	head = 0;
	tail = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////

List::~List()
{
	Destroy();
}

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	cout<<"List a"<<endl;
	List a;
	a.Print();

	cout<<"a.InsertFirst(3)"<<endl;
	a.InsertFirst(3);
	a.Print();

	cout<<"a.InsertLast(7)"<<endl;
	a.InsertLast(7);
	a.Print();

	cout<<"a.InsertAt(1, 4)"<<endl;
	a.InsertAt(1, 4);
	a.Print();

	cout<<"a.InsertOrdered(5)"<<endl;
	a.InsertOrdered(5);
	a.Print();

	cout<<"a.Delete(6)"<<endl;
	a.Delete(6);
	a.Print();

	cout<<"a.Delete(4)"<<endl;
	a.Delete(4);
	a.Print();

	cout<<"a.Destroy()"<<endl;
	a.Destroy();
	a.Print();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////
