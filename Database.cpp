#include "Database.h"

#include <cctype>
#include <iostream>

#define RELATION 0
#define VIEW 1

/*------------------------------------------------------------------------------------*/
/* QUERY FUNCTIONS */
/*------------------------------------------------------------------------------------*/

void Database::select(string view_name, string in_table_name, int row_index){
	bool VIEW_CHECK = true;
	for(unsigned int i=0; i<VIEW_LIST.size(); i++)
		if(VIEW_LIST[i][0][0] == view_name){
			VIEW_CHECK = false;
		}

	vector<vector<string>> TEMP_VIEW_TABLE;
	
	if(VIEW_CHECK){
		int RELATION_INDEX = get_relation_index(in_table_name);
		vector<string> temp_vec;
		temp_vec.push_back(view_name);
		for(unsigned int i=1; i<RELATION_LIST[RELATION_INDEX][0].size(); i++)
			temp_vec.push_back(RELATION_LIST[RELATION_INDEX][0][i]);

		TEMP_VIEW_TABLE.push_back(temp_vec);
		TEMP_VIEW_TABLE.push_back(RELATION_LIST[RELATION_INDEX][1]);
		TEMP_VIEW_TABLE.push_back(RELATION_LIST[RELATION_INDEX][2]);
		TEMP_VIEW_TABLE.push_back(RELATION_LIST[RELATION_INDEX][row_index]);

		VIEW_LIST.push_back(TEMP_VIEW_TABLE);
	}
	else{
		int VIEW_INDEX = get_view_index(view_name);
		int RELATION_INDEX = get_relation_index(in_table_name);
		VIEW_LIST[VIEW_INDEX].push_back(RELATION_LIST[RELATION_INDEX][row_index]);
	}
}

void Database::project(string view_name, string in_table_name, vector<string> attributes){
	int RELATION_INDEX = get_relation_index(in_table_name);
	vector<vector<string>> TEMP_VIEW_TABLE;
	vector<int> columns;
	for(unsigned int i=0; i<RELATION_LIST[RELATION_INDEX][1].size(); i++)
		for(unsigned int j=0; j<attributes.size(); j++)
			if(attributes[j] == RELATION_LIST[RELATION_INDEX][1][i])
				columns.push_back(i);
	for(unsigned int i=0; i< RELATION_LIST[RELATION_INDEX].size(); i++){
		vector<string> temp_vec;
		for(unsigned int j=0; j<columns.size(); j++)
			temp_vec.push_back(RELATION_LIST[RELATION_INDEX][i][j]);
		TEMP_VIEW_TABLE.push_back(temp_vec);
	}
	VIEW_LIST.push_back(TEMP_VIEW_TABLE);
}

/* rename all attributes in an existing table (can be a relation or view)
 * add resulting table into the view list
 */
void Database::rename(string new_view, string existing_table, vector<string> attributes){
	int existing_table_type;
	int existing_table_index;
	int new_view_index;

	// look for table in relation list
	if((existing_table_index = get_relation_index(existing_table)) != -1)
		existing_table_type = RELATION;
	else if((existing_table_index = get_view_index(existing_table)) != -1)
		existing_table_type = VIEW;
	else
		; // RETURN AN ERROR
		
	// ERROR - incorrect number of attributes 
	if(existing_table_type == RELATION && RELATION_LIST[existing_table_index][1].size() != attributes.size());
	if(existing_table_type == VIEW && VIEW_LIST[existing_table_index][1].size() != attributes.size());
		
	// create new view table with 2 rows (title and attribute rows)
	VIEW_LIST.push_back(vector<vector<string> >(2));
	new_view_index = VIEW_LIST.size() - 1;

	// set title
	VIEW_LIST[new_view_index][0].push_back(new_view);
	
	// set attributes
	VIEW_LIST[new_view_index][1] = attributes;

	// copy remaining data
	if(existing_table_type == RELATION)
		for(unsigned int i = 2; i < RELATION_LIST[existing_table_index].size(); ++i)
			VIEW_LIST[new_view_index].push_back(RELATION_LIST[existing_table_index][i]);
	else
		for(unsigned int i = 2; i < VIEW_LIST[existing_table_index].size(); ++i)
			VIEW_LIST[new_view_index].push_back(VIEW_LIST[existing_table_index][i]);
}

void Database::set_union(string view_name, string relation1_name, string relation2_name){
vector< vector<string> > temp;
bool equal = false;
for (unsigned int i = 0; i < RELATION_LIST.size(); ++i)
{
	for (unsigned int j = 0; j < RELATION_LIST.size(); ++j)
	{
		temp[i][j] = RELATION_LIST[1][i][j];
	}
}

for (unsigned int i = 0; i < RELATION_LIST.size(); ++i)
{
	for (unsigned int j = 0; j < RELATION_LIST.size(); ++j)
	{
		if (RELATION_LIST[2][i][j] != RELATION_LIST[1][i][j])
			equal = true;
	}
	//if (equal == true)
	//temp.push_back (RELATION_LIST[2][i][j]);
}
}

void Database::set_difference(string view_name, string relation1_name, string relation2_name){
vector< vector<string> > temp;
bool equal = false;

for (unsigned int i = 0; i < RELATION_LIST.size(); ++i)
{
	for (unsigned int j = 0; j < RELATION_LIST.size(); ++j)
	{
		for (unsigned int k = 0; k < RELATION_LIST.size(); ++k)
		{
			for (unsigned int l = 0; l < RELATION_LIST.size(); ++l)
			{
				if (RELATION_LIST[1][i][j] == RELATION_LIST[2][k][l])
				equal = true;
			}
			//if (equal == false)
			//temp.push_back (RELATION_LIST[1][i][j]);
		}
	}
}
temp[0][0] = view_name;

}

void Database::cross_product(string view_name, string relation1_name, string relation2_name){

vector< vector<string> > temp;
for (unsigned int i = 0; i < RELATION_LIST.size(); ++i)
{
	for (unsigned int j = 0; j < RELATION_LIST.size(); ++j)
	{
		for (unsigned int k = 0; k < RELATION_LIST.size(); ++k)
		{
			for (unsigned int l = 0; l <RELATION_LIST.size(); ++l)
			{
				temp[k + i][l + j] = RELATION_LIST[1][i][j];
			}
		}
	}
}

for (unsigned int i = 0; i < RELATION_LIST.size(); ++i)
{
	for (unsigned int j = 0; j < RELATION_LIST.size(); ++j)
	{
		for (unsigned int k = 0; k < RELATION_LIST.size(); ++k)
		{
			for (unsigned int l = 0; l <RELATION_LIST.size(); ++l)
			{
				temp[k + 2 + i][l + 2 + j] = RELATION_LIST[2][k][l];
			}
		}
	}
}

temp[0][0] = view_name;
}

/*------------------------------------------------------------------------------------*/
/* COMMAND FUNCTIONS */
/*------------------------------------------------------------------------------------*/

void Database::close(string table_name){
	//dont need for monday Sept. 9th submission
}

void Database::write(string table_name){
	//dont need for monday Sept. 9th submission
}

void Database::show(string table_name){
	int INDEX = get_relation_index(table_name);
	int TABLE_TYPE = RELATION;
	if(INDEX == -1){
		INDEX = get_view_index(table_name);
		TABLE_TYPE = VIEW;
	}
	if(TABLE_TYPE == RELATION){
		cout<<RELATION_LIST[INDEX][0][0]<<" (";
		for(unsigned int i=1; i<RELATION_LIST[INDEX][0].size(); i++)
			cout<<RELATION_LIST[INDEX][0][i]<<",";
		cout<<")"<<endl;
		for(unsigned int i=1; i<RELATION_LIST[INDEX].size(); i++) {
			for(unsigned int j=0; j<RELATION_LIST[INDEX][i].size(); j++){
				cout<<RELATION_LIST[INDEX][i][j]<<"\t";
			}
			cout<<endl;
		}
	}
	else{
		cout<<VIEW_LIST[INDEX][0][0]<<" (";
		for(unsigned int i=1; i<VIEW_LIST[INDEX][0].size(); i++)
			cout<<VIEW_LIST[INDEX][0][i]<<",";
		cout<<")"<<endl;
		for(unsigned int i=1; i<VIEW_LIST[INDEX].size(); i++)
			for(unsigned int j=0; j<VIEW_LIST[INDEX][i].size(); j++){
				cout<<VIEW_LIST[INDEX][i][j]<<"\t";
			}
		cout<<endl;
	}
}

void Database::create(string table_name, vector<string> attributes, vector<string> attribute_types, vector<string> keys){
	vector<vector<string>> TEMP_RELATION_TABLE;
	vector<string> temp_vec1, temp_vec2, temp_vec3;

	temp_vec1.push_back(table_name);

	for(unsigned int i=0; i<keys.size(); i++)
		temp_vec1.push_back(keys[i]);
	for(unsigned int i=0; i<attributes.size(); i++)
		temp_vec2.push_back(attributes[i]);
	for(unsigned int i=0; i<attribute_types.size(); i++)
		temp_vec3.push_back(attribute_types[i]);

	TEMP_RELATION_TABLE.push_back(temp_vec1);
	TEMP_RELATION_TABLE.push_back(temp_vec2);
	TEMP_RELATION_TABLE.push_back(temp_vec3);

	RELATION_LIST.push_back(TEMP_RELATION_TABLE);
}


void Database::update(string relation_name, vector<string>attribute, vector<string> data, int row_index){
	int relation_index = -1;
	vector<int> attribute_indices;

	relation_index = get_relation_index(relation_name);

	// ERROR - no such relation
	if(relation_index == -1);

	// find attribute indices
	for(unsigned int i = 0; i < attribute.size(); ++i) {
		int attribute_index = -1;
		attribute_index = get_attribute_index(RELATION, relation_index, attribute[i]);

		// ERROR - no such attribute
		if(relation_index == -1);

		attribute_indices.push_back(attribute_index);
	}

	// update attributes
	for(unsigned int i = 0; i < attribute_indices.size(); ++i)
		RELATION_LIST[relation_index][row_index][attribute_indices[i]] = data[i];
}

void Database::insert_tuple(string relation_name, vector<string> tuple){
	int table_index;

	if((table_index = get_relation_index(relation_name)) == -1)
		; // RETURN ERROR

	RELATION_LIST[table_index].push_back(tuple);
}

void Database::insert_view(string relation_name, string view_name){
	int view_index = -1;
	int relation_index = -1;

	if((view_index = get_view_index(view_name)) == -1)
		; // RETURN ERROR

	if((relation_index = get_relation_index(relation_name)) == -1)
		; // RETURN ERROR

	// copy values from view table to relation table
	for(unsigned int i = 3; i < VIEW_LIST[relation_index].size(); ++i)
		RELATION_LIST[i].push_back(VIEW_LIST[relation_index][i]);
}

void Database::remove(string relation_name, int row_index){
	int relation_index = -1;
	relation_index = get_relation_index(relation_name);

	// ERROR - no such relation
	if(relation_index == -1);

	RELATION_LIST[relation_index].erase(RELATION_LIST[relation_index].begin() + row_index);
}

bool Database::compare(string attribute_type, string left_arg, string right_arg, string comparison_op) {
	bool result;
	switch(attribute_type[0]) {
		// INT or INTEGER
		case 'I':
			result = compare<int>(stoi(left_arg), stoi(right_arg), comparison_op);

		// FLOAT  or REAL
		case 'F': case 'R':
			result = compare<float>(stof(left_arg), stof(right_arg), comparison_op); 

		// CHAR or VARCHAR
		case 'C': case 'V':
			result = compare<string>(left_arg, right_arg, comparison_op);

		// DATE or TIME 
		case 'D': case 'T':
			result = compare<int>(extract_digits(left_arg), extract_digits(right_arg), comparison_op);
	}
	return result;
}

template <class T> bool Database::compare(T left_arg, T right_arg, string comparison_op) {
	if(comparison_op == "==")
		return left_arg == right_arg;
	else if(comparison_op == "!=")
		return left_arg != right_arg;
	else if(comparison_op == "<")
		return left_arg < right_arg;
	else if(comparison_op == ">")
		return left_arg > right_arg;
	else if(comparison_op == "<=")
		return left_arg <= right_arg;
	else
		return left_arg >= right_arg;
}

int Database::extract_digits(string input) {
	for(unsigned int i = input.size(); i > 0; --i)
		if(!isdigit(input[i-1]))
			input.erase(input.begin() + i);

	return stoi(input);
}

int Database::get_relation_index(string table_name){
	int INDEX = -1;

	for(unsigned int i=0; i<RELATION_LIST.size(); i++)
		if(RELATION_LIST[i][0][0] == table_name)
			INDEX = i;
	return INDEX;
}

int Database::get_view_index(string table_name){
	int INDEX = -1;

	for(unsigned int i=0; i<VIEW_LIST.size(); i++)
		if(VIEW_LIST[i][0][0] == table_name)
			INDEX = i;
	return INDEX;
}

int Database::get_attribute_index(int table_type, int table_index, string attribute_name){
	int COLUMN_INDEX = -1;
	if(table_type == RELATION){
		for(unsigned int i = 0; i<RELATION_LIST[table_index][1].size(); i++)
			if(attribute_name == RELATION_LIST[table_index][1][i])
				COLUMN_INDEX = i;
	}
	else{
		for(unsigned int i = 0; i<VIEW_LIST[table_index][1].size(); i++)
			if(attribute_name == VIEW_LIST[table_index][1][i])
				COLUMN_INDEX = i;
	}
	return COLUMN_INDEX;
}
