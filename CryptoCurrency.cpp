#include <iostream>
#include <string>
using namespace std;
string website_api(string coin_address, int chainid) {
    
    string url;
    switch (chainid) {
    	case 1: {
    		url = "https://api.etherscan.io/api?module=account&action=balance&address=" + coin_address + "&tag=latest";
    		
			break;
		}
		case 2:{
			url =  url = "https://api.etherscan.io/api?module=account&action=balance&address=" + coin_address + "&tag=latest";
			break;
		}
	}
}

int main()
{	
    string	address_coin;
	cout<<"Please enter coin address: "<<endl;
	cin>>address_coin;
	
	int id;
	cout<<"Please enter chain id: "<<endl;
	cin>>id;
	
	
}


    


