// Author:  Amin Allam
// Program: Linked list with head, tail, and dummy node

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
// a.InsertAt(0, 2)
// List: 2 3 7
// a.InsertAt(2, 4)
// List: 2 3 4 7
// a.InsertOrdered(5)
// List: 2 3 4 5 7
// a.Delete(6)
// List: 2 3 4 5 7
// a.Delete(4)
// List: 2 3 5 7
// a.Destroy()
// List:

///////////////////////////////////////////////////////////////////////////////////////////////

List::List()
{
	// The dummy node is always the first node
	// The dummy node does not contain any valid data (dummy->data is never used)
	// The dummy node acts as a "sentinel": something to simplify writing the code
	// head always contains the address of the dummy node
	// tail contains the address of the dummy node only if the list is empty

	Node* dummy = new Node;
	dummy->next = 0;

	head = dummy;
	tail = dummy;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void List::InsertFirst(Data d)		// Insert at first (immediately after dummy node)
{
	Node* node = new Node;
	node->data = d;

	node->next = head->next;
	head->next = node;

	if(node->next == 0)
		tail = node;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void List::InsertLast(Data d)		// Insert at last
{
	Node* node = new Node;
	node->data = d;
	node->next = 0;

	// tail can never be 0

	tail->next = node;
	tail = node;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void List::InsertAt(int i, Data d)	// Insert at index i (where i=0 is first)
{
	if(i<0) return;

	// No special case for i==0

	// Initially we are at node head (the node whose address is in head), which is at index -1 (before first node)

	int j=-1;
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

	if(cur == 0)
		return;

	Node* node = new Node;
	node->data = d;

	node->next = cur->next;
	cur->next = node;

	if(node->next == 0)
		tail = node;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void List::InsertOrdered(Data d)		// Insert in its order
{
	// No special case for  if(head==0 || head->data > d)

	Node* node = new Node;
	node->data = d;

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
	// No special case for head == 0 or head->data == d

	Node* prev = head;
	Node* cur = head->next;

	// Move prev until it reaches the node before the node we want to delete

	while(cur != 0 && cur->data != d)
	{
		prev = cur;
		cur = cur->next;
	}

	// Here, cur contains the address of the first node whose data == d (or cur=0)
	// Here, prev contains the address of the node before cur (or prev=address of last node)

	if(cur == 0)
		return;

	prev->next = cur->next;
	delete cur;

	if(prev->next == 0)
		tail = prev;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void List::Print()					// Print list elements
{
	cout << "List: ";

	// Skip printing dummy node
	Node* cur = head->next;

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
	// Do not destroy the dummy node
	Node* cur = head->next;

	while(cur != 0)
	{
		Node* temp = cur->next;
		delete cur;
		cur = temp;
	}

	// Let tail contains the address of the dummy node
	tail = head;
	tail->next = 0; // Important
}

///////////////////////////////////////////////////////////////////////////////////////////////

List::~List()
{
	Destroy();

	// Destroy the dummy node
	delete head;
	head = tail = 0;
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

	cout<<"a.InsertAt(0, 2)"<<endl;
	a.InsertAt(0, 2);
	a.Print();

	cout<<"a.InsertAt(2, 4)"<<endl;
	a.InsertAt(2, 4);
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
