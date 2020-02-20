#include <cstdlib>
#include <cstdio>
#include <vector>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////

// Change this line to the path containing the file frag_1.fastq
#define DIR "F:/Working/Working16/BIO456/"

/////////////////////////////////////////////////////////////////////////////////////////////

int CharToInt[256];
char IntToChar[4];
int Complement[4];

void InitializeTables()
{
	CharToInt['A']=0;
	IntToChar[0]='A';

	CharToInt['C']=1;
	IntToChar[1]='C';

	CharToInt['G']=2;
	IntToChar[2]='G';

	CharToInt['T']=3;
	IntToChar[3]='T';

	Complement[0]=3; // T is complement of A
	Complement[3]=0; // A is complement of T
	Complement[1]=2; // G is complement of C
	Complement[2]=1; // C is complement of G
}

/////////////////////////////////////////////////////////////////////////////////////////////

bool IsValidChar(char c)
{
	return (c=='A'||c=='C'||c=='G'||c=='T');
}

/////////////////////////////////////////////////////////////////////////////////////////////

struct Node
{
	Node* Child[4];
	vector<int> id; // read ids of reads ending at this location
};

Node* root;

/////////////////////////////////////////////////////////////////////////////////////////////

Node* CreateTrieNode() // Create and Initialize Trie Node
{
	Node* node=new Node;
	int i; for(i=0;i<4;i++) node->Child[i]=0;
	return node;
}

void InitializeTrie()
{
	root=CreateTrieNode();
}

void DeleteTrie(Node* node)
{
	int i;
	for(i=0;i<4;i++) if(node->Child[i]) DeleteTrie(node->Child[i]);
	delete node;
}

void DeleteTrie()
{
	DeleteTrie(root);
}

void InsertTrieRead(int* r, int n, int id) // Insert Read r with length n with its id in trie
{
	int i;
	//printf("%d ", n); fflush(NULL);
	//for(i=0;i<n;i++) printf("%d ", r[i]); printf("\n");

	Node* cur_node=root;
	for(i=0;i<n;i++)
	{
		if(!cur_node->Child[r[i]]) cur_node->Child[r[i]]=CreateTrieNode();
		cur_node=cur_node->Child[r[i]];
	}

	cur_node->id.push_back(id);
}

void QueryTrieRead(int* r, int n) // Find Read r with length n in the trie
{
	int i;

	Node* cur_node=root;
	for(i=0;i<n;i++)
	{
		if(!cur_node->Child[r[i]]) return;
		cur_node=cur_node->Child[r[i]];
	}

	for(i=0;i<(int)cur_node->id.size();i++) printf("%d ", cur_node->id[i]); printf("\n");
}

bool InsertRead(char* read, int id) // Insert read (with id) and its complement (with id+1)
{
	int i, n=0; // Ignore reads which contain invalid characters
	for(i=0;read[i];i++) {if(!IsValidChar(read[i])) return false; n++;}
	printf("%s\n", read); fflush(NULL);

	int r[1000]; // Convert characters to integers
	for(i=0;i<n;i++) r[i]=CharToInt[(int)read[i]];

	int c[1000]; // Get read reverse complement
	for(i=0;i<n;i++) c[i]=Complement[r[n-1-i]];

	InsertTrieRead(r, n, id); // Insert read (even id)
	InsertTrieRead(c, n, id+1); // Insert read reverse complement (odd id)

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void Compute()
{
	InitializeTables();
	InitializeTrie();

	char buf[1000];
	FILE* file=fopen(DIR "frag_1.fastq", "r");

	int num_reads=0;
	while(num_reads<20) // Insert the first 20 reads which do not contain invalid characters
	{
		buf[0]=0; fscanf(file, "%[^\n\r] ", buf); // Ignore this line
		buf[0]=0; fscanf(file, "%[^\n\r] ", buf);

		if(InsertRead(buf, num_reads)) num_reads+=2;

		buf[0]=0; fscanf(file, "%[^\n\r] ", buf); // Ignore this line
		buf[0]=0; fscanf(file, "%[^\n\r] ", buf); // Ignore this line
	}

	fclose(file);


	// Search for read q in trie

	//char q[]="TAAGATACTGTATCAATTCCGCTGCAATTCAATTTATTCCATATGAAAAGTTAGAAGAATTGGGCTATGGCGATTTAATATCACATTTTGATAAGTAGGAG";
	char q[]="ACCCTTCCCTCTATCGTAATTGGTTGTGAACTTTCGTAACGAAACATATTTAAAGCACTAAAATAAACAGGTATCTTTATTTGTTGTGTTTCACGTTCGTA";

	int r[1000], i, n=0;
	for(i=0;q[i];i++) {r[i]=CharToInt[(int)q[i]]; n++;}

	QueryTrieRead(r, n);

	DeleteTrie();
}

/////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Compute();
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//TCTGCAGTTTCAAACGGGCTTCCAACTGACTCATCTACATATTTATTAGCTTGTTAACTTGACATAACACCATGTAACTCTTCCATAGACTCTAAATGCTC
//AGCACGTTGTCACTCATTTCGAGATCCTTTTCAACTTGCTTTTTATTCTTTTCGAAATCAGCTGGTTGAGTAGTTATGAGTTCATTATTTTTATTAGAATA
//ACGTCTTGTTAATCAGTTTGCGTCTTACGATTGGCCACTAGATCTAGCTTTAATTTCTATTCCAATATTTTCTGTCAATGTGAGCTCAGATGAATTGACAC
//AGAAATCTTCTTTGCCCAATAACTTTCGATGGCTTTTTTCCATTCTCTTTTTCTACCTAATCTTGGGAATCCTAAGTTTGATGTTTTAATTGTTGTCATAT
//TTATTGACGTTGACCCTCTGAACCCTTCACAATCCCAACACTTGTCTAATGGTGGGCTACTTAGCTCACGTCACTTCTACTTTCTTCTTCACGTTATATAA
//AGGTTCTTGCATGATTTCGTATATTCTACTACTTGCACCGACTGCCTTTTTATAATCTGTAACTAACGTGGAAAGATTGATTAATGGCATAGGTAGCTGAT
//ACCCTTCCCTCTATCGTAATTGGTTGTGAACTTTCGTAACGAAACATATTTAAAGCACTAAAATAAACAGGTATCTTTATTTGTTGTGTTTCACGTTCGTA
//TATTAATCATGAACAAACTTTTGTTTAGTAACTATATTTGGAAAATAAATAGTTCATCTGATTATCCATAAAGTTCATTGTTAAAATCTAGTGTTAAAAAA
//TTAGATATTGTTTCAACAATTGCATTAACATATAGCGTAGTATTTTTTTGAGGAATTCTAACAGAAGTTTCTATTGGTGGTGTATGCTGTGTAATGTTTTT
//TAAGATACTGTATCAATTCCGCTGCAATTCAATTTATTCCATATGAAAAGTTAGAAGAATTGGGCTATGGCGATTTAATATCACATTTTGATAAGTAGGAG

/////////////////////////////////////////////////////////////////////////////////////////////
