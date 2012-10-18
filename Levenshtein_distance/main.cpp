#include    <iostream>
#include	<string.h>


using namespace std;

int	findLevenshteinDistance(const	std::string	&firstString,	const	string	&secondString)
{
    int	result	=	0;
    int	m	=	firstString.length();
    int n	=	secondString.length();
    if(m	==	0)
    {
        return  n;
    }
    if(n	==	0)
    {
        return	m;
    }
    int	**D	=	new	int*[m+1];
    for	(int	i	=	0;	i	<=   m;	i++)
    {
        D[i]	=	new	int[n+1];
    }
    for	(int	i	=	0;	i	<=	m;	i++)
    {
        D[i][0]	=	i;
    }
    for (int	j	=	0;	j	<=	n;	j++)
    {
        D[0][j]	=	j;
    }
    for	(int	i	=	1;	i	<=	m;	i++)
    {
                for (int	j	=	1;	j	<=	n;	j++)
                {
                    if(firstString[i-1]	==	secondString[j - 1])
                    {
                    D[i][j]	=	std::min(std::min(D[i - 1][j]	+	1
                                       ,D[i][j - 1]	+	1)
                                       ,D[i - 1][j - 1]);
                    }
                    else
                    {
                    D[i][j] = std::min(std::min(D[i - 1][j]	+	1
                                       ,D[i][j - 1]	+	1)
                                       ,D[i - 1][j - 1] +   1);
                    }
                }
    }
            result  =   D[m][n];
            delete	[]	D;
            return	result;
}
int main()
{
    std::string firstString;
    std::string	secondString;
    cout    <<  "Enter first string"    <<endl;
    cin >>  firstString;
    cout    <<  "Enter first string"    <<endl;
    cin >>  secondString;
    cout    <<  "Levenshtein distance = "   <<findLevenshteinDistance(firstString, secondString);
    return  0;
}

