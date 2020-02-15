#include <cstdlib>
#include <cstdio>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////

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

bool PrintRead(char* read_chars) // Print read and its reverse complement
{
	int i, n=0; // Ignore reads which contain invalid characters
	for(i=0;read_chars[i];i++) {if(!IsValidChar(read_chars[i])) return false; n++;}

	int read_ints[1000]; // Convert characters to integers
	for(i=0;i<n;i++) read_ints[i]=CharToInt[(int)read_chars[i]];

	printf("%s\n", read_chars);
	for(i=0;i<n;i++) printf("%d", read_ints[i]); printf("\n");

	int reverse_comp_ints[1000]; // Get read reverse complement integers
	for(i=0;i<n;i++) reverse_comp_ints[i]=Complement[read_ints[n-1-i]];

	char reverse_comp_chars[1000]; // Convert integers to characters
	for(i=0;i<n;i++) reverse_comp_chars[i]=IntToChar[reverse_comp_ints[i]];
	reverse_comp_chars[n]=0;

	printf("%s\n", reverse_comp_chars);
	for(i=0;i<n;i++) printf("%d", reverse_comp_ints[i]); printf("\n");

	printf("\n");

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void Compute()
{
	InitializeTables();

	char buf[1000];
	FILE* file=fopen(DIR "frag_1.fastq", "r");

	int num_reads=0;
	while(num_reads<20) // Print the first valid 10 reads and their complements (20 printed reads)
	{
		buf[0]=0; fscanf(file, "%[^\n\r] ", buf); // Ignore this line
		buf[0]=0; fscanf(file, "%[^\n\r] ", buf);

		if(PrintRead(buf)) num_reads+=2;

		buf[0]=0; fscanf(file, "%[^\n\r] ", buf); // Ignore this line
		buf[0]=0; fscanf(file, "%[^\n\r] ", buf); // Ignore this line
	}

	fclose(file);
	fflush(NULL);
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
