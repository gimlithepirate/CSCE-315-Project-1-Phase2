
using namespace std; 

void DBApp::Initialize(){

	//Create emmpty tables for users, threads, posts, statistics, commented and created - ER diagram
	p.parse("CREATE TABLE users (username VARCHAR(20), userID INTEGER, password VARCHAR(15), date VARCHAR(20), NoOfThreads INTEGER, NoOfPosts INTEGER);");
	//p.parse("CREATE TABLE threads ()")

}


void DBApp:Menu(){

	bool loop = true;
	
	while(loop){

		cout<<"Welcome to the Forum. What would you like to do? Please chose one of the following options:"<<endl<<endl;
	
		cout<<"1. Create a new account."<<endl;
		cout<<"2. Create a new thread."<<endl;
		cout<<"3. Comment on an existing thread."<<endl;
		cout<<"4. Update user information."<<endl;
		cout<<"5. Delete your account."<<endl;
		cout<<"6. Delete a thread."<<endl;
		cout<<"7. List all users."<<endl;
		cout<<"8. Find a particular user."<<endl;	
		cout<<"9. Display site statistics."<<endl;
		cout<<"10. Quit the App."<<endl;
	
		int x; cin>>x;
		//Switch or if-else statements.
		switch(x){
	
			case 1: loop = CreateAccount();
					break;
			case 2: loop = CreateThread();
					break;
			case 3: loop = CommentOnThread();
					break;
			case 4: loop = UpdateUserInfo();
					break;
			case 5: loop = DeleteAccount();
					break;
			case 6: loop = DeleteThread();
					break;
			case 7: loop = List();
					break;
			case 8: loop = FindUser();
					break;		
			case 9: loop = DisplayStatistics();
					break;
			case 10: loop = QuitApp();
					break;
			default: cout<<"Invalid Option. Try again."<<endl<<endl;
					break;				
	
		}
	
	}
	

}


bool DBApp::CreateAccount(){


	cout<<"Please enter a username (It should have atleast 6 characters)."<<endl;
	string username;
	cin>>username;
	cout<<"Please enter a password."<<endl;
	string password;
	cin>>password;
	cout<<"Please enter your password again to confirm the password."<<endl;
	string password2;
	cin>>password2;
	if(password!=password2){
		cout<<"The passwords entered do not match. Please try again."<<endl;
		//
		//
	}
	
	
	//GET current date using computer clock
	int NoOfThreads = 0;
	int NoOfPosts = 0;
	
	//users is an existing table
	string create = "INSERT INTO users VALUES FROM (\""+username+"\", \""+password+"\", \""+date+"\", \""+NoOfThreads+"\", \""+NoOfPosts+");"
	p.parse(create);
	
	cout<<"An account for "<<username<<" has ben created\n. Going back to main menu"<<endl<<endl;
	
	return true;
	
}

bool DBApp::DeleteAccount(){

	cout<<"Please enter your username."<<endl;
	string username;
	cin>>username;

	cout<<"Hi "<<username<<", are you sure you want to delete your account? (y or n)"<<endl;
	char x; cin>>x;

	if(x=='y'){

		string delete = "DELETE FROM users WHERE (username==" + username + ");"<<endl;		//users is an existing table
		p.parse(delete);
		cout<<"The account has been deleted. Going back to main menu."<<endl;		
	}

	else if(x=='n'){
		cout<<"Returning to main menu."<<endl;
	}
	return true;
}


bool DBApp::DisplayStatistics(){

	string display = "SHOW statistics;";	//statistics is an existing table
	p.parse(display);
	
	cout<<"\nReturning to main menu.\n"<<endl;
	
	return true;
	
}


bool DBApp::QuitApp(){

	string quit = "EXIT;"
	
	p.parse(quit);
	
	return false;
	
}




