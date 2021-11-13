#include <bits/stdc++.h>
using namespace std;

#define MAX_MSG_LENGTH 1000
//Function to check if randomly generated number is prime or not 
bool isPrime(long long int n)
{
    // Corner case
    if (n <= 1)
        return false;
 
    // Check from 2 to square root of n
    for (long long int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
            return false;
    }

    return true;
}

//Function to calculate GCD
long long int gcd(long long int a, long long int b)
{
    if (a == 0)
        return b;

    return gcd(b%a, a);
}

//fucntion to generate generator
long long int generator(long long int p)
{
	int flag=0;
	long long int temp,temp2;
	long long int v[p+1];
	for (long long int i=2;i<p;i++)
	{
	    for(long long int i1=1;i1<p+1;i1++)
	    {

			v[i1]=0;
	    }
		flag =0; temp=1;
		for(long long int j=0;j<p;j++)
		{
			if (j!=0)
                temp=(temp*i) %p;
			if (v[temp] != 0)
			{
				flag=1;
				break;
			}
			v[temp] = j;
		}
		if (flag==0) return i;
	}
}

//Calculting private and public keys
void calculate_keys(long long int p, long long int g, long long int *x,long long int *y)
{
	std::srand(static_cast<unsigned int>(std::time(NULL))); 
	long long int temp=1;
	bool is_coprime=false;
	// generating x co-prime to p randomly
	while(is_coprime == false)
	{
		*x= std::rand();
		if ((*x<p) && (gcd(*x,p)==1))
		{
			is_coprime=true;
		}
	}
	for (long long int i=0;i<*x;i++)
	{
		temp = (temp*g)%p;
	}
	*y=temp;
}

//Decryption function
void str_decryption(long long int c1,long long int enc_c2[],long long int p,long long int x,long long int dec_msg[])
{
	long long int temp=1;
	
	//Calculating power(c1,x) mod p
	for(int i=0;i<x;i++)
	{
		temp=(temp*c1)%p;
	}

    //Calculating c2/power(c1,x) mod p
	for(int i=0;i<MAX_MSG_LENGTH;i++)
	{
		if (enc_c2[i] == -1)
		{
			break;
		}
		dec_msg[i] = enc_c2[i]/temp;
	}
}
//Encrytion function
void str_encryption(char msg[],long long int p,long long int g,long long int y,long long int *c1,long long int enc_c2[])
{
	cout<<"\nTo be encrypted.........(m,p,g,y): ( "<<msg<<" , "<<p<<" , "<<g<<" , "<<y<<" )";
	long long int r,temp=1;
	int a;
	bool is_coprime=false;

	// generating r co-prime to p randomly
	while(is_coprime == false)
	{
		r= std::rand();
		if ((r<p-1) && (gcd(r,p)==1))
		{
			is_coprime=true;
		}
	}
	cout<<"\nrendomly gen r:"<<r;

    // Calcculating c1 = power(g,r) mod p
	for (int i=0;i<r;i++)
	{
		temp =(temp*g)%p;
	}
	*c1=temp;

    //Calculating power(y,r) mod p
	temp=1;
	for (int i=0;i<r;i++)
	{
		temp=(temp*y)%p;
	}
	
	//Calculating m*power(y,r) mod p
	for(int i=0;i<strlen(msg);i++)
	{
		a=msg[i];
		enc_c2[i]= temp*a;
	}
}

int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL))); 
	long long int p,g,x,y,c1,enc_c2[MAX_MSG_LENGTH],dec_msg[MAX_MSG_LENGTH];
	bool is_prime = false;
	char message[MAX_MSG_LENGTH]={-1},final_decrypted_msg[MAX_MSG_LENGTH]={-1};

	// generating p prime number randomly
	while(is_prime == false)
	{
		p= std::rand();
		is_prime = isPrime(p);
	}
    
    //finding generator of group Zp*
    g = generator(p);
    //Calculating private and public key
    calculate_keys(p,g,&x,&y);
    cout<<"\n----------------------------------------------------------------------------------------------------";
	cout<<"\n publisc key (p,g,y): ("<<p<<" , "<<g<<" , "<<y<<" )";
	cout<<"\n private key x:"<<x;
    cout<<"\n----------------------------------------------------------------------------------------------------";

    //Enter message to send
    cout<<"\nEnter MSG:";cin.getline(message,MAX_MSG_LENGTH);

    //Calling encryption function
    str_encryption(message,p,g,y,&c1,enc_c2);
    cout<<"\n----------------------------------------------------------------------------------------------------";
    cout<<"\nSender sending...........................(c1,c2):\n"<<"( "<<c1<<" , ";
    for (int i=0;i<strlen(message);i++) cout<<enc_c2[i];cout<<" )";
    
    //Calling decrytion function
    str_decryption(c1,enc_c2,p,x,dec_msg);

    char temp_ch1;
    cout<<"\n----------------------------------------------------------------------------------------------------"<<"\nReceiver decrypted message: ";
    
    //Converting decrypted message from ascii to char
    for(int i=0;i<strlen(message);i++)
	{
		if (dec_msg[i]==-1)
		{
			break;
		}
	    final_decrypted_msg[i]=dec_msg[i];cout<<final_decrypted_msg[i];
    }
}
