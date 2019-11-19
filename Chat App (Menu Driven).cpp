#include<bits/stdc++.h>
using namespace std;


typedef struct node{
    string msg;
	string from;
    node* down;
}* nodeptr;

class Stack{
    public:
        nodeptr top = NULL;
        int size = 0;
        void push(string msg , string from);
        void print_stack();

};

void Stack :: push(string msg , string from){
    nodeptr t = new node;
	t->down = NULL;
    t->msg = msg;
	t->from = from;

    if(top == NULL){
        top = t;
        size++;
        return;
    }

    t->down = top;
    top = t;
    size++;

}

void Stack :: print_stack(){

    if(size == 0 or top == NULL){
        cout << "No messages found" << endl;
        return ;
    }

	cout << "Your messages from newest to oldest are : " << endl;

    nodeptr curr = top;

    while(curr != NULL){
        cout << curr->msg << " from " << curr->from << endl;
        curr = curr->down;
    }
    cout << '\n';

}

typedef struct profile{
	
	string name;
	string email;
	string phone;
	string username;
	string password;
	//vector<string> messages;	//Make this a stack so that earlier messages will be on the top 
	Stack messages;

}* profileptr;


typedef struct acnode{
    profileptr ptr;
    acnode* next = NULL;
}* acnodeptr;


class linkedlist{
    public :
       acnodeptr head = NULL;
       acnodeptr tail = NULL;
        int size = 0;
        void add(profileptr);
       void printlist();

};

void printdata(acnodeptr h){
    cout << h->ptr->name << endl;
    cout << h->ptr->phone << endl;
}

void linkedlist :: printlist(){

    acnodeptr curr = head;

    while(curr != NULL){

        printdata(curr);

        curr = curr->next;
    }

}

void linkedlist :: add(profileptr one){

    acnodeptr cont = new acnode;
    cont->ptr = one;
    cont->next = NULL;
   
   if(head == NULL){
       head = cont;
       tail = cont;
       size++;
       return;
   }

   tail->next = cont;
   tail = cont;
   size++;

}

class social_network{
	public:
		linkedlist accounts;
		//vector<profileptr> accounts;	//Make this a linked list
		social_network();
		void add_member();
		bool found(string  , string);
		void list_of_users();
		void send_message(string name , string msg , string from);
		void print_messages(string us);
};

void social_network :: print_messages(string us){

	// for(int x=0;x<accounts.size();x++){
	// 	if(accounts[x]->username == us){

	// 		accounts[x]->messages.print_stack();

	// 		return;
	// 	}
	// }

	acnodeptr curr = accounts.head;

	while(curr != NULL){
		if(curr->ptr->username == us){
			curr->ptr->messages.print_stack();
			return;
		}
		curr = curr->next;
	}

	cout << "Username not found" << endl;

}

void social_network :: send_message(string name , string msg , string from){

	// for(int x=0;x<accounts.size();x++){
	// 	if(accounts[x]->name == name){
	// 		accounts[x]->messages.push(msg);
	// 		return;
	// 	}
	// }

	acnodeptr curr = accounts.head;

	while(curr != NULL){
		if(curr->ptr->name == name){
			curr->ptr->messages.push(msg ,from);
			return;
		}

		curr = curr->next;
	}

	cout << "User not found , sorry " << endl;

}

void social_network :: list_of_users(){

	cout << "Currently , our network has " << accounts.size << " users" << endl;
	// for(int x=0;x<accounts.size();x++){
	// 	cout << (x+1) << ")" << accounts[x]->name << endl;
	// }
	int cnt = 0;

	acnodeptr curr = accounts.head;

	while(curr != NULL){
		cout << (++cnt) << ")" << curr->ptr->name << endl;
		curr = curr->next;
	}

}

bool social_network :: found(string us , string ps){

	// for(int x=0;x<accounts.size();x++){
	// 	if(accounts[x]->username == us and accounts[x]->password == ps)
	// 		return true;
	// }

	acnodeptr curr = accounts.head;

	while(curr != NULL){
		if(curr->ptr->username == us and curr->ptr->password == ps)
			return true;
		curr = curr->next;
	}

	return false;

}

void social_network :: add_member(){

	profileptr member = new profile;

	cout << "Please enter your details : \n";
	cout << "1. Name : ";	cin >> member->name;
	//cout << "2. Email : ";	cin >> member->email;
	//cout << "3. Phone : ";	cin >> member->phone;
	cout << "2. Username : ";	cin >> member->username;
	cout << "3. Password : " ;	cin >> member->password;	

	accounts.add(member);	//I should return the pointer here instead of vector ;)

	cout << "Your account has been successfully created " << endl;
}

social_network :: social_network(){
//Social network constructor

}

social_network a;

void create_account(){

	a.add_member();
}

void list_of_all_members(string inc = "all"){

	acnodeptr curr = a.accounts.head;

	if(curr == NULL) {
		cout << "No users found " << endl;
		return;
	}
	int cnt = 1;

	while(curr != NULL){

		if(curr->ptr->name == inc){
			curr = curr->next;
			continue;
		}

		cout << cnt++ << ")" << curr->ptr->name << endl;

		curr = curr->next;
	}

}

void login_to_account(){
	cout << "Login to your account " << endl;

	string un , ps;

	cout << "Enter your username : " ;	cin >> un ;
	cout << "Enter your password : " ;	cin >> ps;

	if(!a.found(un , ps)){
		cout << "You entered incorrect username and password " << endl;
		cout << "Try again ? ";	
		char yes;	cin >> yes;
		if(yes == 'n') return ;
		else login_to_account();
	}else{
		cout << "You have successfully logged in your account " << endl;
		cout << "Welcome , " << un << endl;
	}

	hello:

	cout << "What would you like to do today " << endl;
	int tc;
	cout << "1)Send someone a message " << endl;
	cout << "2)See your messages " << endl;

	cin >> tc;

	if(tc == 1){
		cout << "Who would you like to send message : " << endl;
		list_of_all_members(un);
		string nm;	cin >> nm;
		cout << "What message you want to send : ";
		string mess;	cin >> mess;
		a.send_message(nm , mess , un);
		cout << "Your message was sent " << endl;
		cout << "Logging you out " << endl;
		
	}else if(tc == 2){
		a.print_messages(un);
	}

	cout << "Do you want to continue ? ";
	char ch;	cin>> ch;
	if(ch == 'y')	goto hello;


}


int main(){


	char choice = 'y';

	while(choice == 'y'){

		cout << "Choose what you want to do : " << endl;
		cout << "1) Create an account on the network " << endl;
		cout << "2) See list of all members of the social network " << endl;
			//list_of_all_members();
		cout << "3) Login to your account (Check your messages/Send someone message) " << endl;
			//login_to_account();
		cout << "4) Exit the application " << endl;
		
			int t;	cin >> t;
			if(t == 1){
				create_account();
			}
			else if(t == 2){
				list_of_all_members();
			}else if(t == 3){
				login_to_account();
			}else if(t == 4)
				exit(0);
			else
				cout << "Wrong option chosen" << endl;

				cout << "Do you want to continue ? ";	cin >> choice ;

	}

	return 0;
}














