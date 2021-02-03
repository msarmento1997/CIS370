/*Michael Sarmento
Lab4 Part1
9/30/19*/

#include <unistd.h>


//used to convert lower case to upper case
void lower_to_upper(char str[])
{
	int i;
	for(i=0; str[i]!='\0';i++)
	{
		if((str[i]>='a' && str[i]<='z'))
		{		
			str[i]=str[i]-32;
			continue;
		}
		if(str[i]==' ')
		{
			++i;
			if((str[i]>='a' && str[i]<='z'))
			{		
				str[i]=str[i]-32;
				continue;
			}
		}
		
	}

}



int main(void)
{

	ssize_t number;
	int i;
	char string[100];
	
	//reads from terminal and passes characters to lower_to_upper to convert the string from lower to upper case
	while( number = read(0,string,1))
	{
		lower_to_upper(string);
		
		//write to the terminal in upper case
		write(1,string,number);
					
		
	}
	
	return 0;


}
