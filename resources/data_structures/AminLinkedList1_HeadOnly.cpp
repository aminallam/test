// Author:  Amin Allam
// Program: Linked list with head only

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
public:
	List();

	void InsertFirst(Data d);		// Insert at first
	void InsertLast(Data d);		// Insert at Last
	void InsertAt(int i, Data d);	// Insert at index i (where i=0 is first)
	void InsertOrdered1(Data d);	// Insert in its order
	void InsertOrdered2(Data d);	// Insert in its order
	void Delete(Data d);			// Delete element d

	Node* Find1(Data d);				// Return first node containing d
	static Node* Find2(Data d, Node*);  // Return first node containing d starting from a specific node
	Node* Find2(Data d);			// Return first node containing d (uses the above function)

	void Reverse1();				// Reverse list
	void Reverse2();				// Reverse list
	static Node* Reverse3(Node*);	// Reverse list starting from a specific node and return new head
	void Reverse3();				// Reverse list (uses the above function)

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
// a.InsertAt(3, 9)
// List: 3 4 7 9
// a.InsertAt(5, 10)
// List: 3 4 7 9
// a.InsertOrdered1(5)
// List: 3 4 5 7 9
// a.InsertOrdered2(8)
// List: 3 4 5 7 8 9
// a.Find1(5)
// Found 5
// a.Find1(6)
// a.Find2(5)
// Found 5
// a.Find2(6)
// a.Reverse1()
// List: 9 8 7 5 4 3
// a.Reverse2()
// List: 3 4 5 7 8 9
// a.Reverse3()
// List: 9 8 7 5 4 3
// a.Delete(6)
// List: 9 8 7 5 4 3
// a.Delete(4)
// List: 9 8 7 5 3
// a.Destroy()
// List:

///////////////////////////////////////////////////////////////////////////////////////////////

List::List()
{
	head=0;		// 0 is the same as NULL
}

///////////////////////////////////////////////////////////////////////////////////////////////

void List::InsertFirst(Data d)		// Insert at first
{
	Node* node = new Node;
	node->data = d;
	node->next = head;
	head = node;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void List::InsertLast(Data d)		// Insert at last
{
	Node* node = new Node;
	node->data = d;
	node->next = 0;

	if(head==0)
	{
		head=node;
		return;
	}

	Node* cur = head;

	while(cur->next != 0)
		cur = cur->next;

	// Here, cur contains the address of the last node

	cur->next = node;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void List::InsertAt(int i, Data d)	// Insert at index i (where i=0 is first)
{
	if(i<0)
		return;

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
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void List::InsertOrdered1(Data d)		// Insert in its order
{
	Node* node = new Node;
	node->data = d;

	if(head==0 || head->data > d)
	{
		node->next = head;
		head = node;

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
}

///////////////////////////////////////////////////////////////////////////////////////////////

void List::InsertOrdered2(Data d)		// Insert in its order (another implementation)
{
	Node* node = new Node;
	node->data = d;

	if(head==0 || head->data > d)
	{
		node->next = head;
		head = node;

		return;
	}

	Node* prev = head;

	// Move prev until it reaches the node before the location where we want to insert

	while(prev->next != 0 && prev->next->data <= d)
	{
		prev = prev->next;
	}

	// Here, prev contains the address of the node before the node whose data > d
	//      (or prev=address of last node)
	// So, we need to insert our node after the prev node (the node whose address in prev)

	node->next = prev->next;
	prev->next = node;
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
}

///////////////////////////////////////////////////////////////////////////////////////////////

Node* List::Find1(Data d)			// Return first node containing d
{
	if(head == 0)
		return 0;

	Node* cur = head;

	while(cur != 0)
	{
		if(cur->data == d)
			return cur;

		cur = cur->next;
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////

Node* List::Find2(Data d, Node* head)	// Return first node containing d starting from a specific node
{
	if(head == 0)
		return 0;

	if(head->data == d)
		return head;

	return Find2(d, head->next);
}

///////////////////////////////////////////////////////////////////////////////////////////////

Node* List::Find2(Data d)		// Return first node containing d (uses the above function)
{
	return Find2(d, head);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void List::Reverse1()					// Reverse list
{
	if(head == 0)
		return;

	Node* prev = head;
	Node* cur = head->next;

	while(cur != 0)
	{
		Node* next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}

	head->next = 0;
	head = prev;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void List::Reverse2()					// Reverse list
{
	if(head == 0)
		return;

	Node* prev = 0;
	Node* cur = head;

	while(cur != 0)
	{
		Node* next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}

	head = prev;
}

///////////////////////////////////////////////////////////////////////////////////////////////

Node* List::Reverse3(Node* head)	// Reverse list starting from a specific node and return new head
{
	if(head->next == 0)
		return head;

	Node* new_head=Reverse3(head->next);

	head->next->next = head;
	head->next = 0;

	return new_head;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void List::Reverse3()					// Reverse list
{
	if(head == 0)
		return;

	head = Reverse3(head);
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

	cout<<"a.InsertAt(3, 9)"<<endl;
	a.InsertAt(3, 9);
	a.Print();

	cout<<"a.InsertAt(5, 10)"<<endl;
	a.InsertAt(5, 10);
	a.Print();

	cout<<"a.InsertOrdered1(5)"<<endl;
	a.InsertOrdered1(5);
	a.Print();

	cout<<"a.InsertOrdered2(8)"<<endl;
	a.InsertOrdered2(8);
	a.Print();

	cout<<"a.Find1(5)"<<endl;
	if(a.Find1(5)) cout<<"Found 5"<<endl;

	cout<<"a.Find1(6)"<<endl;
	if(a.Find1(6)) cout<<"Found 6"<<endl;

	cout<<"a.Find2(5)"<<endl;
	if(a.Find2(5)) cout<<"Found 5"<<endl;

	cout<<"a.Find2(6)"<<endl;
	if(a.Find2(6)) cout<<"Found 6"<<endl;

	cout<<"a.Reverse1()"<<endl;
	a.Reverse1();
	a.Print();

	cout<<"a.Reverse2()"<<endl;
	a.Reverse2();
	a.Print();

	cout<<"a.Reverse3()"<<endl;
	a.Reverse3();
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
