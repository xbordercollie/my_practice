#include <stdio.h>
#define MAX_LINE 1000

int main(void)
{
	char max_line[MAX_LINE];
	char line[1000];
	int max_len = 0;
	int temp;
	char c;

	max_line[0] = '\0';
	while((c=getchar()) != EOF)
	{
		line[0] = c;
		for(temp=1; temp<MAX_LINE && (c=getchar())!=EOF && c!='\n'; temp++)
                	{
                  	      line[temp] = c;
               	 	}
        	line[temp] = '\0';
        	if(temp>max_len)
                	{
                        	for(int i=0; i<=temp; i++)
                                	{
                                        	max_line[i] = line[i];
                                	}
                        	max_len = temp;
                	}
	}

	printf("%s\n", max_line);
	return 0;
}

