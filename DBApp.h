//We need to remember to keep updating statistics, commented, created and other relations. 
//It might get a bit complicated but say if DeleteThread is called then we need to reduce the no of threads in the statistics relation and
// also reduce the no of threads associated with that particular userID in the users relation. And we also need to remove the entry from the created relation. 

#include "AST_Assembly.h"

class DBApp{

	AST_Assembly p;

public:

	void Initialize(); //VA
	
	void Menu();		//Done
	

	bool CreateThread(); //PMG
	bool CommentOnThread(); //PMG
	bool UpdateUserInfo();  //PMG
	bool FindUser();       //PMG 
	
	bool DeleteAccount();  //VA - need to update statistics and other relations accordingly
	bool DeleteThread();   //VA - need to update statistics and other relations accordingly
	bool CreateAccount();  //VA
	bool ShowUsers();		//PMG - Query to get a view of usernames only - not the whole table
	bool DisplayStatistics(); //Done
	bool QuitApp(); //Done

};
