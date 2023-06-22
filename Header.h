#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <typeinfo>
#include <ctime>
using namespace std;

// Comment this whole file

class Topic	// Topic class
{
	string name;
public:
	Topic(string _name)
	{
		this->name = _name; 
	}
	void edit(string _name)
	{
		this->name = _name; 
	}
	void print()
	{
		cout<<"Topic : "<<name<<endl;
	}
	string getName()
	{
		return name;
	}
	void saveData(ofstream& fout)
	{
		fout<<name<<endl;
	}
	~Topic()
	{
		name="";
	}
};
class LO
{
protected:
	int id;
	string name;
public:
	LO(string _name,int _id)
	{
		this->id=_id;
		this->name=_name;
	}
	virtual void print()=0;			// Pure virtual function
	virtual void saveData(ofstream&)=0;  		// Pure virtual function
	virtual void edit(string)=0;		// Pure virtual function
	~LO(){}		// Destructor
};
class CLO: public LO
{
	Topic **topics;		// Array of pointers to Topic class
	int size;			
	int totalTopics;
public:
	CLO(string _name,int _id):LO(_name,_id)		
	{
		this->size=10;		// Initial size of array
		this->topics=new Topic*[this->size];	// Dynamically allocating array
		this->totalTopics=0;	// Initially no topics
	}
	void edit(string _name)
	{
		name=_name;
	}
	void addTopic(Topic* _topic)	// Add topic to array
	{
		if(size==totalTopics)
		{
			Topic** temp=topics;	// Temporary array
			size+=10;	// Increasing size of array
			topics=new Topic* [size];	// Dynamically allocating new array
			for(int i=0;i<totalTopics;i++)	// Copying elements from temp to topics
				topics[i]=temp[i];	
			delete [] temp;	// Deleting temp array
		}
		topics[totalTopics++]=_topic;	// Adding topic to array
	}
	void removeTopic(string _name)	// Remove topic from array
	{
		for(int i=0;i<totalTopics;i++)	// Searching for topic
		{
			if(topics[i]->getName()==_name)	// If topic found
			{
				for(;i<totalTopics-1;i++)	// Shifting elements
				{
					topics[i]=topics[i+1];	
				}
				totalTopics--;	// Decreasing totalTopics
			}
		}
	}
	void setId(int _id)	// Set id
	{
		id=_id;
	}
	int getID()
	{
		return id;
	}
	void print()
	{
		cout<<"CLO Name : "<<name<<"     ID : "<<id<<endl;
		for(int i=0;i<totalTopics;i++)	// Printing all topics
			topics[i]->print();		
		//cout<<"__________________________________________________"<<endl;
	}
	void saveData(ofstream& fout)	// Save data to file
	{
		fout<<name<<endl;
		fout<<id<<endl;
		fout<<totalTopics<<endl;
		for(int i=0;i<totalTopics;i++)	// Saving all topics
		{
			fout<<topics[i]->getName()<<endl;		
		}
	}
	~CLO()		// Destructor
	{
		if(size)	// If size is not 0
			delete [] topics;	// Delete array
	}
};
class PLO: public LO		// PLO class
{
	CLO **CLOs;		// Array of pointers to CLO class
	int size;
	int totalCLOs;
public:
	PLO(string _name,int _id):LO(_name,_id)
	{
		this->size=10;		// Initial size of array
		this->CLOs=new CLO* [this->size];	// Dynamically allocating array
		this->totalCLOs=0;	// Initially no CLOs
	}
	void edit(string _name)
	{
		name=_name;
	}
	int getID()
	{
		return id;
	}
	void getAllCLOs(CLO** &list, int &total)	// Get all CLOs
	{
		list=this->CLOs;
		total=this->totalCLOs;
	}
	string getName()
	{
		return this->name;
	}
	void addCLO(CLO* _CLO)		// Add CLO to array
	{
		if(size==totalCLOs)
		{
			CLO** temp=CLOs;	// Temporary array
			size+=10;
			CLOs=new CLO* [size];	// Dynamically allocating new array
			for(int i=0;i<totalCLOs;i++)	// Copying elements from temp to CLOs
				CLOs[i]=temp[i];	
			delete [] temp;	// Deleting temp array
		}
		CLOs[totalCLOs++]=_CLO;	// Adding CLO to array
	}
	void removeCLO(int _id)
	{
		for(int i=0;i<totalCLOs;i++)	// Searching for CLO
		{
			if(CLOs[i]->getID()==_id)	// If CLO found
			{
				for(;i<totalCLOs-1;i++)	// Shifting elements
				{
					CLOs[i]=CLOs[i+1];
				}
				totalCLOs--;	// Decreasing totalCLOs
			}
		}
	}
	void print()
	{
		cout<<"PLO Name : "<<name<<"     ID : "<<id<<endl;
		cout<<"Following CLOs are included in this PLO"<<endl;
		for(int i=0;i<totalCLOs;i++)	// Printing all CLOs
			CLOs[i]->print();			
		//cout<<"__________________________________________________"<<endl;
	}
	void saveData(ofstream& fout)
	{
		fout<<name<<endl;
		fout<<id<<endl;
		fout<<totalCLOs<<endl;
		for(int i=0;i<totalCLOs;i++)
		{
			fout<<CLOs[i]->getID()<<endl;	// Saving all CLOs
		}
	}
	~PLO()
	{
		if(size)		// If size is not 0
			delete [] CLOs; 		// Delete array
	}
};
class Course
{
	string name;		
	float creditHours;	
	string courseCode;	
	CLO **CLOs;	// Array of pointers to CLO class
	int size;
	int totalCLOs;
	int id;
public:
	Course(string _name,int _id,float _creditHours, string _courseCode)	// Constructor
	{
		this->id=_id;
		this->creditHours=_creditHours;
		this->courseCode=_courseCode;
		this->name=_name;
		this->size=10;	// Initial size of array
		this->CLOs=new CLO* [this->size];	// Dynamically allocating array
		this->totalCLOs=0;	// Initially no CLOs
	}
	void edit(string _name,float _creditHours, string _courseCode)	// Edit course
	{
		this->creditHours=_creditHours;
		this->courseCode=_courseCode;
		this->name=_name;
	}
	int getID()
	{
		return id;
	}
	void getAllCLOs(CLO** &list, int &total)	// Get all CLOs
	{
		list=this->CLOs;		
		total=this->totalCLOs;
	}
	void addCLO(CLO* _CLO)
	{
		if(size==totalCLOs)
		{
			CLO** temp=CLOs;	// Temporary array
			size+=10;	
			CLOs=new CLO* [size];	// Dynamically allocating new array
			for(int i=0;i<totalCLOs;i++)	// Copying elements from temp to CLOs
				CLOs[i]=temp[i];	
			delete [] temp;	// Deleting temp array
		}
		CLOs[totalCLOs++]=_CLO;	// Adding CLO to array
	}
	void removeCLO(int _id)
	{
		for(int i=0;i<totalCLOs;i++)	// Searching for CLO
		{
			if(CLOs[i]->getID()==_id)	// If CLO found
			{
				for(;i<totalCLOs-1;i++)	// Shifting elements
				{
					CLOs[i]=CLOs[i+1];	
				}
				totalCLOs--;	// Decreasing totalCLOs
			}
		}
	}
	bool findCLOs(CLO** list, int total)
	{
		for(int i=0;i<totalCLOs;i++)	// Searching for CLO
		{
			for(int j=0;j<total;j++)	
			{
				if(list[j]->getID()==this->CLOs[i]->getID())	// If CLO found
					return true;	// Return true
			}
		}
		return false;	// Return false
	}
	void saveData(ofstream& fout)	// Save data
	{
		fout<<name<<endl;
		fout<<id<<endl;
		fout<<courseCode<<endl;
		fout<<creditHours<<endl;
		fout<<totalCLOs<<endl;
		for(int i=0;i<totalCLOs;i++)
		{
			fout<<CLOs[i]->getID()<<endl;	// Saving all CLOs
		}
	}
	void print()
	{
		cout<<"Course Name : "<<name<<"     ID : "<<id<<endl;
		cout<<"Course Code : "<<courseCode<<"     Credit Hours : "<<creditHours<<endl;
		cout<<"Following CLOs are included in this Course"<<endl;
		for(int i=0;i<totalCLOs;i++)
			CLOs[i]->print();	// Printing all CLOs
		//cout<<"__________________________________________________"<<endl;
	}
	~Course()	
	{
		if(size)	// If size is not 0
			delete [] CLOs;	// Delete array
	}
};
class Program
{
	Course** courses;	// Array of pointers to Course class
	int totalCourses;
	int size1;
	PLO** PLOs;		// Array of pointers to PLO class
	int totalPLOs;
	int size2;
	string name;
	int duration;
	int totalCreditHours;
public:
	string getName()
	{
		return name;
	}
	Program(string _name,int _duration, int _totalCreditHours)
	{
		this->name=_name;
		this->duration=_duration;
		this->totalCreditHours=_totalCreditHours;
		this->totalCourses=0;
		this->totalPLOs=0;
		this->size1=10;
		this->size2=10;
		this->courses=new Course*[size1];	// Dynamically allocating array
		this->PLOs=new PLO*[size2];		// Dynamically allocating array
	}
	void edit(string _name, int _duration, int _totalCreditHours)
	{
		this->name=_name;
		this->duration=_duration;
		this->totalCreditHours=_totalCreditHours;
	}
	void addPLO(PLO* _PLO)	// Add PLO
	{
		if(size2==totalPLOs)	// If array is full
		{
			PLO** temp=PLOs;	// Temporary array
			size2+=10;		// Increasing size
			PLOs=new PLO* [size2];	// Dynamically allocating new array
			for(int i=0;i<totalPLOs;i++)	// Copying elements from temp to PLOs
				PLOs[i]=temp[i];	
			delete [] temp;		// Deleting temp array
		}
		PLOs[totalPLOs++]=_PLO;	// Adding PLO to array
	}
	void addCourse(Course* _Course)
	{
		if(size1==totalCourses)
		{
			Course** temp=courses;		// Temporary array
			size1+=10;	// Increasing size
			courses=new Course* [size1];	// Dynamically allocating new array
			for(int i=0;i<totalCourses;i++)		// Copying elements from temp to courses
				courses[i]=temp[i];  
			delete [] temp;		// Deleting temp array
		}
		courses[totalCourses++]=_Course;	// Adding Course to array
	}
	void removePLO(int _id)
	{
		for(int i=0;i<totalPLOs;i++)	// Searching for PLO
		{
			if(PLOs[i]->getID()==_id)	// If found
			{
				for(;i<totalPLOs-1;i++)
				{
					PLOs[i]=PLOs[i+1];	// Shifting elements
				}
				totalPLOs--;	// Decreasing totalPLOs
			}
		}
	}
	void removeCourse(int _id)
	{
		for(int i=0;i<totalCourses;i++)		// Searching for Course
		{
			if(courses[i]->getID()==_id)	// If found
			{
				for(;i<totalCourses-1;i++)
				{
					courses[i]=courses[i+1];	// Shifting elements
				}
				totalCourses--;		// Decreasing totalCourses
			}
		}
	}
	void getCoursesByPLO(PLO* _plo)		// Get Courses by PLO
	{
		cout<<"Following Courses are relevent to the PLO : "<<_plo->getName()<<endl;
		CLO **list;		// Array of pointers to CLO class
		int count;
		_plo->getAllCLOs(list,count);	// Getting all CLOs of PLO
		for(int i=0;i<totalCourses;i++)		
		{
			if(courses[i]->findCLOs(list,count)) // If CLOs of PLO are found in Course
				courses[i]->print();	// Print Course
		}
		cout<<"******************************************"<<endl;
	}
	void print()
	{
		//cout<<"______Program Details______\n";
		cout<<"Program : "<<this->name<<endl;
		cout<<"Duration : "<<duration<<" years        Total Credit Hours : "<<totalCreditHours<<endl;
		cout<<"Courses : "<<endl;
		for(int i=0;i<totalCourses;i++)
			courses[i]->print();		// Printing all Courses
		//cout<<endl;
		cout<<"PLOs : "<<endl;
		for(int i=0;i<totalPLOs;i++)	// Printing all PLOs
			PLOs[i]->print();
		//cout<<"\n_________________________________\n\n";
		//cout<<"__________________________________________________"<<endl;
	}
	void saveData(ofstream& fout)
	{
		fout<<name<<endl;
		fout<<totalCreditHours<<endl;
		fout<<duration<<endl;
		fout<<totalCourses<<endl;
		for(int i=0;i<totalCourses;i++)
		{
			fout<<courses[i]->getID()<<endl;	// Saving Course ID
		}
		fout<<totalPLOs<<endl;		// Saving total PLOs
		for(int i=0;i<totalPLOs;i++)		
		{
			fout<<PLOs[i]->getID()<<endl;	// Saving PLO ID
		}
	}
	~Program()
	{
		if(size1)		// If size1 is not 0
			delete [] courses;	// Deleting courses array
		if(size2)		// If size2 is not 0
			delete [] PLOs;		// Deleting PLOs array
	}
};

class Question
{
	int id;
	string statement;
	CLO* clo;		// Pointer to CLO class
public:
	Question(int _id,string _statement,CLO* _clo)	// Constructor
	{
		this->id=_id;
		this->statement=_statement;
		this->clo=_clo;
	}
	CLO* getCLO()	
	{
		return clo;		// Returning CLO
	}
	int getID()
	{
		return id;
	}
	void edit(string new_statement)	
	{
		this->statement=new_statement;		
	}
	void print()
	{
		cout<<"Question ID: "<<id<<" Statement: "<<statement<<" CLO: "<<clo->getID()<<endl;	// Printing Question
	}
	void saveData(ofstream& fout)
	{
		fout<<id<<endl<<statement<<endl<<clo->getID()<<endl;	// Saving Question data
	}
	~Question()
	{
		clo=NULL;	// Setting clo to NULL
	}
};

class Evaluation 
{	
protected:
	int totalMarks;
	float weightage;
public:
	Evaluation(int _totalMarks, float _weightage)
	{
		totalMarks=_totalMarks;
		weightage=_weightage;
	}
	virtual int countQuestions(int _id)=0;	// Pure virtual function
	virtual void addQuestion(Question* _Question)=0;	// Pure virtual function
	virtual string getName()=0;		// Pure virtual function
	virtual void removeQuestion(int)=0;		// Pure virtual function  
	virtual void saveData(ofstream&)=0;		// Pure virtual function
	virtual void edit(int ,float)=0;	// Pure virtual function
	virtual void print()=0;		// Pure virtual function
};
class Assignment : public Evaluation	// Assignment class derived from Evaluation class
{
	string name;
	char type;
	Question **ques;		// Array of pointers to Question class
	int totalQues;
	int size;
public:
	Assignment(string _name,int _totalMarks, float _weightage):Evaluation(_totalMarks,_weightage)
	{
		this->name=_name;	// Setting name
		this->type='A';		// Setting type to 'A'
		this->size=10;		// Setting size to 10
		this->ques=new Question* [this->size];	// Creating array of pointers to Question class
		this->totalQues=0;
	}
	string getName()
	{
		return name;
	}
	void print()
	{
		cout<<"Name: "<<name<<endl<<"Total Marks: "<<totalMarks<<" Weightage: "<<weightage<<endl;
		for(int i=0;i<totalQues;i++)	// Printing all Questions
		{
			ques[i]->print();	// Printing Question
		}
	}
	void edit(int new_totalmarks,float new_weightage)
	{
		totalMarks=new_totalmarks;	// Setting new total marks
		weightage=new_weightage;	// Setting new weightage
	}
	void saveData(ofstream &fout)
	{
		fout<<name<<endl<<type<<endl<<totalMarks<<endl<<weightage<<endl;	// Saving Assignment data
		fout<<totalQues<<endl;	// Saving total Questions
		for(int i=0;i<totalQues;i++)
		{
			fout<<ques[i]->getID()<<endl;	// Saving Question ID
		}
	}
	void addQuestion(Question* _Question)
	{
		if(size==totalQues)		// If size is equal to total Questions
		{
			Question** temp=ques;	// Creating temporary array of pointers to Question class
			size+=10;	// Increasing size by 10
			ques=new Question* [size];	// Creating new array of pointers to Question class
			for(int i=0;i<totalQues;i++)
				ques[i]=temp[i];	// Copying data from temp to ques
			delete [] temp;		// Deleting temp
		}
		ques[totalQues++]=_Question;	// Adding Question to ques array
	}
	int countQuestions(int _id)
	{
		int count =0;
		for(int i=0;i<totalQues;i++)
		{
			if(ques[i]->getCLO()->getID()==_id)	// If Question's CLO ID is equal to _id
			{
				count++;	// Incrementing count	
			}
		}
		return count;	// Returning count
	}
	void removeQuestion(int _id)
	{
		for(int i=0;i<totalQues;i++)	// Searching for Question
		{
			if(ques[i]->getID()==_id)
			{
				for(;i<totalQues-1;i++)
				{
					ques[i]=ques[i+1];	// Removing Question
				}
				totalQues--;	// Decrementing total Questions
			}
		}
	}
	~Assignment()	// Destructor
	{
		if(size)	// If size is not 0
			delete [] ques;	// Deleting ques array
	}
};
class Quiz : public Evaluation	// Quiz class derived from Evaluation class
{
	string name;
	char type;
	Question **ques;	// Array of pointers to Question class
	int totalQues;
	int size;
public:
	Quiz(string _name,int _totalMarks, float _weightage):Evaluation(_totalMarks,_weightage)
	{
		this->name=_name;
		this->type='Q';		// Setting type to 'Q'
		this->size=10;			
		this->ques=new Question* [this->size];	// Creating array of pointers to Question class
		this->totalQues=0;	// Setting total Questions to 0
	}
	string getName()
	{
		return name;
	}
	void print()
	{
		cout<<"Name: "<<name<<endl<<"Total Marks: "<<totalMarks<<" Weightage: "<<weightage<<endl;	// Printing Quiz data
		for(int i=0;i<totalQues;i++)
		{
			ques[i]->print();	// Printing Question
		}
	}
	void saveData(ofstream &fout)
	{
		fout<<name<<endl<<type<<endl<<totalMarks<<endl<<weightage<<endl;	// Saving Quiz data
		fout<<totalQues<<endl;
		for(int i=0;i<totalQues;i++)	// Saving total Questions
		{
			fout<<ques[i]->getID()<<endl;	// Saving Question ID
		}
	}
	void edit(int new_totalmarks,float new_weightage)
	{
		totalMarks=new_totalmarks;
		weightage=new_weightage;
	}
	void addQuestion(Question* _Question)
	{
		if(size==totalQues)		// If size is equal to total Questions
		{
			Question** temp=ques;
			size+=10;
			ques=new Question* [size];	// Creating new array of pointers to Question class
			for(int i=0;i<totalQues;i++)
				ques[i]=temp[i];	// Copying data from temp to ques
			delete [] temp;	// Deleting temp
		}
		ques[totalQues++]=_Question;	// Adding Question to ques array
	}
	int countQuestions(int _id)
	{
		int count =0;
		for(int i=0;i<totalQues;i++)
		{
			if(ques[i]->getCLO()->getID()==_id)	// If Question's CLO ID is equal to _id
			{
				count++;	// Incrementing count
			}
		}
		return count;	// Returning count
	}
	void removeQuestion(int _id)
	{
		for(int i=0;i<totalQues;i++)	// Searching for Question
		{
			if(ques[i]->getID()==_id)
			{
				for(;i<totalQues-1;i++)
				{
					ques[i]=ques[i+1];	// Removing Question
				}
				totalQues--;	// Decrementing total Questions
			}
		}
	}
	~Quiz()
	{
		if(size)		// If size is not 0
			delete [] ques;		// Deleting ques array
	}
};
class Exam : public Evaluation
{
	string name;
	char type;
	Question **ques;	// Array of pointers to Question class
	int totalQues;
	int size;
public:
	Exam(string _name,int _totalMarks, float _weightage):Evaluation(_totalMarks,_weightage)
	{
		this->name=_name;
		this->type='E';		// Setting type to 'E'
		this->size=10;
		this->ques=new Question* [this->size];		// Creating array of pointers to Question class
		this->totalQues=0;		// Setting total Questions to 0
	}
	string getName()
	{
		return name;
	}
	void print()
	{
		cout<<"Name: "<<name<<endl<<"Total Marks: "<<totalMarks<<" Weightage: "<<weightage<<endl;	// Printing Exam data
		for(int i=0;i<totalQues;i++)
		{
			ques[i]->print();		// Printing Question
		}
	}
	void edit(int new_totalmarks,float new_weightage)
	{
		totalMarks=new_totalmarks;
		weightage=new_weightage;
	}
	void saveData(ofstream &fout)
	{
		fout<<name<<endl<<type<<endl<<totalMarks<<endl<<weightage<<endl;	// Saving Exam data
		fout<<totalQues<<endl;
		for(int i=0;i<totalQues;i++)
		{
			fout<<ques[i]->getID()<<endl;	// Saving Question ID
		}
	}
	void addQuestion(Question* _Question)
	{
		if(size==totalQues)
		{
			Question** temp=ques;	// Creating new array of pointers to Question class
			size+=10;	// Increasing size by 10
			ques=new Question* [size];	// Creating new array of pointers to Question class
			for(int i=0;i<totalQues;i++)
				ques[i]=temp[i];	// Copying data from temp to ques
			delete [] temp;		// Deleting temp
		}
		ques[totalQues++]=_Question;	// Adding Question to ques array
	}
	int countQuestions(int _id)
	{
		int count =0;
		for(int i=0;i<totalQues;i++)
		{
			if(ques[i]->getCLO()->getID()==_id)	// If Question's CLO ID is equal to _id
			{
				count++;	// Incrementing count
			}
		}
		return count;	// Returning count
	}
	void removeQuestion(int _id)
	{
		for(int i=0;i<totalQues;i++)		// Searching for Question
		{
			if(ques[i]->getID()==_id)
			{
				for(;i<totalQues-1;i++)
				{
					ques[i]=ques[i+1];	// Removing Question
				}
				totalQues--;	// Decrementing total Questions
			}
		}
	}
	~Exam()
	{
		if(size)	// If size is not 0
			delete [] ques;	// Deleting ques array
	}
};

class Evaluator
{
	Evaluation **evaluations;	// Array of pointers to Evaluation class
	int totalEvaluations;
	int size1;
	Question **questions;	// Array of pointers to Question class
	int totalQuestions;
	int size2;
public:
	Evaluator()
	{
		size1=10;
		totalEvaluations=0;
		evaluations=new Evaluation* [size1];	// Creating array of pointers to Evaluation class
		size2=10;		
		totalQuestions=0;
		questions=new Question* [size2];	// Creating array of pointers to Question class
	}
	void createEvaluation(char type,string _name, int _totalMarks,float _weightage)
	{
		Evaluation* _Evaluation=NULL;	// Creating pointer to Evaluation class
		if(type=='A')	// If type is 'A'
			_Evaluation = new Assignment(_name,_totalMarks,_weightage);	// Creating pointer to Assignment class
		if(type=='Q')		// If type is 'Q'
			_Evaluation = new Quiz(_name,_totalMarks,_weightage);	// Creating pointer to Quiz class
		if(type=='E')	// If type is 'E'
			_Evaluation = new Exam(_name,_totalMarks,_weightage);	// Creating pointer to Exam class
		if(size1==totalEvaluations)	// If size is equal to total Evaluations
		{
			Evaluation** temp=evaluations;	// Creating new array of pointers to Evaluation class
			size1+=10;	// Increasing size by 10
			evaluations=new Evaluation* [size1];	// Creating new array of pointers to Evaluation class
			for(int i=0;i<totalEvaluations;i++)
				evaluations[i]=temp[i];	// Copying data from temp to evaluations
			delete [] temp;	// Deleting temp
		}
		evaluations[totalEvaluations++]=_Evaluation;	// Adding Evaluation to evaluations array
	}
	void createQuestion(int _id,string _statement,CLO* _CLO)
	{
		Question* _Question = new Question(_id,_statement,_CLO);	// Creating pointer to Question class
		if(size1==totalQuestions)	// If size is equal to total Questions
		{
			Question** temp=questions;	// Creating new array of pointers to Question class
			size1+=10;
			questions=new Question* [size1];	// Creating new array of pointers to Question class
			for(int i=0;i<totalQuestions;i++)
				questions[i]=temp[i];	// Copying data from temp to questions
			delete [] temp;		// Deleting temp
		}	
		questions[totalQuestions++]=_Question;	// Adding Question to questions array
	}
	bool checkCLOHasTested(int _id)	// Function to check if CLO has been tested
	{
		int totalCount=0;	// Total count of Questions
		for(int i=0;i<totalEvaluations;i++)	// Looping through all Evaluations
			totalCount+=evaluations[i]->countQuestions(_id);	// Adding count of Questions to totalCount
		if(totalCount>2)	// If totalCount is greater than 2
			return true;	// Return true
		return false;	// Else return false
	}
	void printAllQuestions()
	{
		for(int i=0;i<totalQuestions;i++)	// Looping through all Questions
			questions[i]->print();	// Printing Question
	}
	void printAllEvaluations()
	{
		for(int i=0;i<totalEvaluations;i++)		// Looping through all Evaluations
			evaluations[i]->print();	// Printing Evaluation
	}
	void saveQuestions(ofstream &fout)
	{
		fout<<totalQuestions<<endl;	// Saving total Questions
		for(int i=0;i<totalQuestions;i++)	// Looping through all Questions
			questions[i]->saveData(fout);	// Saving Question
	}
	void saveEvaluations(ofstream &fout)
	{
		fout<<totalEvaluations<<endl;	// Saving total Evaluations
		for(int i=0;i<totalEvaluations;i++)		// Looping through all Evaluations
			evaluations[i]->saveData(fout);		// Saving Evaluation
	}
	Question* findQuestion(int _id)	// Function to find Question
	{
		for(int i=0;i<totalQuestions;i++)	// Looping through all Questions
		{
			if(questions[i]->getID()==_id)	// If Question's ID is equal to _id
				return questions[i];	// Return Question
		}
		return NULL;	// Else return NULL
	}
	Evaluation* findEvaluation(string _name)	// Function to find Evaluation
	{
		for(int i=0;i<totalEvaluations;i++)	// Looping through all Evaluations
		{
			if(evaluations[i]->getName()==_name)	// If Evaluation's name is equal to _name
				return evaluations[i];	// Return Evaluation
		}
		return NULL;	// Else return NULL
	}
	void addQuestionToEvaluation(int _id, string _name)
	{
		Question* _Question = this->findQuestion(_id);	// Finding Question
		if(_Question)	// If Question is not NULL
		{
			Evaluation* _Evaluation = this->findEvaluation(_name);	// Finding Evaluation
			if(_Evaluation)	
			{
				_Evaluation->addQuestion(_Question);	// Adding Question to Evaluation
			}
			else
			{
				cout<<"Evaluation not Found"<<endl;	// Else print Evaluation not Found
			}
		}
		else
		{
			cout<<"Question not Found"<<endl;	// Else print Question not Found
		}
	}
	void editQuestion(int _id,string new_Statement)
	{
		Question* _Question= findQuestion(_id);	// Finding Question
		if(_Question)
		{
			_Question->edit(new_Statement);	// Editing Question
		}
		else
		{
			cout<<"Question not Found"<<endl;	// Else print Question not Found
		}
	}
	void editEvaluation(string name, int new_totalMarks,float new_weightage)
	{
		Evaluation* _Evaluation= findEvaluation(name);	// Finding Evaluation
		if(_Evaluation)
		{
			_Evaluation->edit(new_totalMarks,new_weightage);	// Editing Evaluation
		}
		else
		{
			cout<<"Question not Found"<<endl;	// Else print Question not Found
		}
	}
	void removeQuestionFromEvaluation(int Question_id,string Evaluation_name)
	{
		Evaluation* _Evaluation=this->findEvaluation(Evaluation_name);	// Finding Evaluation
		if(_Evaluation)
		{
			_Evaluation->removeQuestion(Question_id);	// Removing Question from Evaluation
		}
		else
		{
			cout<<"Evaluation not found"<<endl;		// Else print Evaluation not found
		}
	}
	~Evaluator()
	{
		if(evaluations)	// If evaluations is not NULL
			delete [] evaluations;	// Delete evaluations
	}
};
class AcademicManager
{
	Topic **topics;		// Array of pointers to Topic class
	int totalTopics;
	int size1;
	CLO **CLOs;			// Array of pointers to CLO class
	int totalCLOs;
	int size2;
	PLO **PLOs;			// Array of pointers to PLO class
	int totalPLOs;
	int size3;
	Course **courses;		// Array of pointers to Course class
	int totalCourses;
	int size4;
	Program **programs;		// Array of pointers to Program class
	int totalPrograms;
	int size5;
	Evaluator *evaluator;	// Pointer to Evaluator class

public:
	AcademicManager()
	{
		totalTopics=0;
		size1=10;
		topics=new Topic* [size1];	// Allocating memory to topics
		totalCLOs=0;
		size2=10;
		CLOs=new CLO* [size2];	// Allocating memory to CLOs
		totalPLOs=0;
		size3=10;
		PLOs=new PLO* [size3];	// Allocating memory to PLOs
		totalCourses=0;
		size4=10;
		courses=new Course* [size4];	// Allocating memory to courses
		totalPrograms=0;
		size5=10;
		programs=new Program* [size5];	// Allocating memory to programs
		evaluator=new Evaluator();	// Creating Evaluator object
	}
	void printAllTopics()
	{
		cout<<"\nAll Topics\n";
		for(int i=0;i<totalTopics;i++)
			topics[i]->print();		// Printing all Topics
		cout<<"__________________________________________"<<endl;
	}
	void printAllCLOs()
	{
		cout<<"\nAll CLOs\n";
		for(int i=0;i<totalCLOs;i++)
			CLOs[i]->print();	// Printing all CLOs
		cout<<"__________________________________________"<<endl;
	}
	void printAllPLOs()
	{
		cout<<"\nAll PLOs\n";
		for(int i=0;i<totalPLOs;i++)
			PLOs[i]->print();		// Printing all PLOs
		cout<<"__________________________________________"<<endl;
	}
	void printAllCourses()
	{
		cout<<"\nAll Courses\n";
		for(int i=0;i<totalCourses;i++)
			courses[i]->print();		// Printing all Courses
		cout<<"__________________________________________"<<endl;
	}
	void printAllPrograms()
	{
		cout<<"\nAll Programs\n";
		for(int i=0;i<totalPrograms;i++)
			programs[i]->print();		// Printing all Programs
		//cout<<"__________________________________________"<<endl;
	}
	void printAllQuestions()
	{
		evaluator->printAllQuestions();		// Printing all Questions
	}
	void printAllEvaluations()
	{
		evaluator->printAllEvaluations();	// Printing all Evaluations
	}
	void createTopic(string _name)	// Creating Topic
	{
		Topic *_topic = new Topic(_name);	// Creating Topic object
		if(size1==totalTopics)
		{
			Topic** temp=topics;	// Creating temp array
			size1+=10;
			topics=new Topic* [size1];	// Allocating memory to topics
			for(int i=0;i<totalTopics;i++)
				topics[i]=temp[i];	// Copying temp to topics
			delete [] temp;		// Deleting temp
		}
		topics[totalTopics++]=_topic;	// Adding Topic to topics
	}
	void createCLO(string _name,int _id)	// Creating CLO
	{
		CLO *_CLO = new CLO(_name,_id);		// Creating CLO object
		if(size2==totalCLOs)
		{
			CLO** temp=CLOs;	// Creating temp array
			size2+=10;
			CLOs=new CLO* [size2];	// Allocating memory to CLOs
			for(int i=0;i<totalCLOs;i++)
				CLOs[i]=temp[i];	// Copying temp to CLOs
			delete [] temp;		// Deleting temp
		}
		CLOs[totalCLOs++]=_CLO;		// Adding CLO to CLOs
	}
	void createPLO(string _name, int _id)	// Creating PLO
	{
		PLO *_PLO = new PLO(_name,_id);	// Creating PLO object
		if(size3==totalCLOs)
		{
			PLO** temp=PLOs;	// Creating temp array
			size3+=10;
			PLOs=new PLO* [size3];	// Allocating memory to PLOs
			for(int i=0;i<totalPLOs;i++)
				PLOs[i]=temp[i];	// Copying temp to PLOs
			delete [] temp;		// Deleting temp
		}
		PLOs[totalPLOs++]=_PLO;		// Adding PLO to PLOs
	}
	void createCourse(string _name, int _id,string _courseCode,float _creditHours)	// Creating Course
	{
		Course *_Course = new Course(_name,_id,_creditHours,_courseCode);	// Creating Course object
		if(size4==totalCourses)
		{
			Course** temp=courses;		// Creating temp array
			size4+=10;
			courses=new Course* [size4];	// Allocating memory to courses
			for(int i=0;i<totalCourses;i++)		
				courses[i]=temp[i];		// Copying temp to courses
			delete [] temp;		// Deleting temp
		}
		courses[totalCourses++]=_Course;	// Adding Course to courses
	}
	void createProgram(string _name,int _duration,int _totalCreditHours)	// Creating Program
	{
		Program *_Program = new Program(_name,_duration,_totalCreditHours);	// Creating Program object
		if(size5==totalPrograms)
		{	
			Program** temp=programs;	// Creating temp array
			size5+=10;	
			programs=new Program* [size5];	// Allocating memory to programs
			for(int i=0;i<totalPrograms;i++)
				programs[i]=temp[i];	// Copying temp to programs
			delete [] temp;		// Deleting temp
		}
		programs[totalPrograms++]=_Program;		// Adding Program to programs
	}
	void createQuestion(int _id,string _statement,int CLO_id)	// Creating Question
	{
		CLO* _CLO = this->findCLO(CLO_id);		// Finding CLO
		if(!_CLO)	// If CLO not found
			cout<<"CLO not found"<<endl;	// Print CLO not found
		evaluator->createQuestion(_id,_statement,_CLO);	// Creating Question
	}
	void createEvaluation(char _type,string _name, int _totalMarks, float _weightage)	// Creating Evaluation
	{
		evaluator->createEvaluation(_type,_name,_totalMarks,_weightage);
	}
	Topic* findTopic(string _name)	// Finding Topic
	{
		for(int i=0;i<totalTopics;i++)
		{
			if(topics[i]->getName()==_name)	// If Topic found
				return topics[i];	// Return Topic
		}
		return NULL;	// Return NULL
	}
	CLO* findCLO(int _id)		// Finding CLO
	{
		for(int i=0;i<totalCLOs;i++)
		{
			if(CLOs[i]->getID()==_id)	// If CLO found
				return CLOs[i];		// Return CLO
		}
		return NULL;	// Return NULL
	}
	PLO* findPLO(int _id)	// Finding PLO
	{
		for(int i=0;i<totalPLOs;i++)
		{
			if(PLOs[i]->getID()==_id)	// If PLO found
				return PLOs[i];		// Return PLO
		}
		return NULL;	// Return NULL
	}
	Course* findCourse(int _id)		// Finding Course
	{
		for(int i=0;i<totalCourses;i++)
		{
			if(courses[i]->getID()==_id)	// If Course found
				return courses[i];	// Return Course
		}
		return NULL;	// Return NULL
	}
	Program* findProgram(string _name)	// Finding Program
	{
		for(int i=0;i<totalPrograms;i++)
		{
			if(programs[i]->getName()==_name)	// If Program found
				return programs[i];	// Return Program
		}
		return NULL;	// Return NULL
	}
	void addTopicToCLO(string topicName,int _id)	// Adding Topic to CLO
	{
		Topic* _topic = this->findTopic(topicName);	// Finding Topic
		if(_topic)	
		{
			CLO* _CLO = this->findCLO(_id);	// Finding CLO
			if(_CLO)
			{
				_CLO->addTopic(_topic);	// Adding Topic to CLO
			}
			else
			{
				cout<<"CLO not Found"<<endl;	// Print CLO not found
			}
		}
		else
		{
			cout<<"Topic not Found"<<endl;	// Print Topic not found
		}
	}
	void addCLOToPLO(int CLO_id,int PLO_id)
	{
		CLO* _CLO = this->findCLO(CLO_id);	// Finding CLO
		if(_CLO)
		{
			PLO* _PLO = this->findPLO(PLO_id);	// Finding PLO
			if(_PLO)
			{
				_PLO->addCLO(_CLO);	// Adding CLO to PLO
			}
			else
			{
				cout<<"PLO not Found"<<endl;	// Print PLO not found
			}
		}
		else
		{
			cout<<"CLO not Found"<<endl;	// Print CLO not found
		}
	}
	void addCLOToCourse(int CLO_id,int Course_id)	// Adding CLO to Course
	{
		CLO* _CLO = this->findCLO(CLO_id);	// Finding CLO
		if(_CLO)
		{
			Course* _Course = this->findCourse(Course_id);	// Finding Course
			if(_Course)
			{
				_Course->addCLO(_CLO);	// Adding CLO to Course
			}
			else
			{
				cout<<"Course not Found"<<endl;	// Print Course not found
			}
		}
		else
		{
			cout<<"CLO not Found"<<endl;	// Print CLO not found
		}
	}
	void addCourseToProgram(int Course_id, string name)	// Adding Course to Program
	{
		Course* _Course = this->findCourse(Course_id);	// Finding Course
		if(_Course)
		{
			Program* _Program = this->findProgram(name);	// Finding Program
			if(_Program)
			{	
				_Program->addCourse(_Course);	// Adding Course to Program
			}
			else
			{
				cout<<"Program not Found"<<endl;	// Print Program not found
			}
		}
		else
		{
			cout<<"Course not Found"<<endl;		// Print Course not found
		}
	}
	void addPLOToProgram(int PLO_id, string name)	// Adding PLO to Program
	{
		PLO* _PLO = this->findPLO(PLO_id);	// Finding PLO
		if(_PLO)
		{
			Program* _Program = this->findProgram(name);	// Finding Program
			if(_Program)
			{
				_Program->addPLO(_PLO);		// Adding PLO to Program
			}
			else
			{
				cout<<"Program not Found"<<endl;	// Print Program not found
			}
		}
		else
		{
			cout<<"PLO not Found"<<endl;		// Print PLO not found
		}
	}
	void addQuestionToEvaluation(int Question_id, string _name)	// Adding Question to Evaluation
	{
		evaluator->addQuestionToEvaluation(Question_id,_name);	
	}
	void editTopic(string old_name,string new_name)	// Editing Topic
	{
		Topic* _topic= findTopic(old_name);	// Finding Topic
		if(_topic)
		{
			_topic->edit(new_name);	// Editing Topic
		}
		else
		{
			cout<<"Topic not Found"<<endl;	// Print Topic not found
		}
	}
	void editCLO(int _id,string new_name)	// Editing CLO
	{
		CLO* _CLO= findCLO(_id);	// Finding CLO
		if(_CLO)
		{
			_CLO->edit(new_name);	// Editing CLO
		}
		else
		{
			cout<<"CLO not Found"<<endl;	// Print CLO not found
		}
	}
	void editPLO(int _id,string new_name)	// Editing PLO
	{
		PLO* _PLO= findPLO(_id);	// Finding PLO
		if(_PLO)
		{
			_PLO->edit(new_name);	// Editing PLO
		}
		else
		{
			cout<<"PLO not Found"<<endl;	// Print PLO not found
		}
	}
	void editCourse(int _id,string new_name,string new_courseCode,float new_creditHours)	// Editing Course
	{
		Course* _Course= findCourse(_id);	// Finding Course
		if(_Course)
		{
			_Course->edit(new_name,new_creditHours,new_courseCode);	// Editing Course
		}
		else
		{
			cout<<"Course not Found"<<endl;		// Print Course not found
		}
	}
	void editProgram(string old_name,string new_name,int new_duration,int new_totalCreditHours)	// Editing Program
	{
		Program* _Program= findProgram(old_name);	// Finding Program
		if(_Program)
		{
			_Program->edit(new_name,new_duration,new_totalCreditHours);	// Editing Program
		}
		else
		{
			cout<<"Program not Found"<<endl;	// Print Program not found
		}
	}
	void editQuestion(int _id,string new_Statement)	// Editing Question
	{
		evaluator->editQuestion(_id,new_Statement);
	}
	void editEvaluation(string name, int new_totalMarks,float new_weightage) // Editing Evaluation
	{
		evaluator->editEvaluation(name,new_totalMarks,new_weightage);
	}
	void removeTopicFromCLO(int _id,string _name)	// Removing Topic from CLO
	{
		CLO* _CLO=this->findCLO(_id);	// Finding CLO
		if(_CLO)
		{
			_CLO->removeTopic(_name);	// Removing Topic from CLO
		}
		else
		{
			cout<<"CLO not found"<<endl;	// Print CLO not found
		}
	}
	void removeCLOFromPLO(int CLO_id,int PLO_id)	// Removing CLO from PLO
	{
		PLO* _PLO=this->findPLO(PLO_id);	// Finding PLO
		if(_PLO)
		{
			_PLO->removeCLO(CLO_id);	// Removing CLO from PLO
		}
		else
		{
			cout<<"PLO not found"<<endl;	// Print PLO not found
		}
	}
	void removeCLOFromCourse(int Course_id,int CLO_id)	// Removing CLO from Course
	{
		Course* _Course=this->findCourse(Course_id);	// Finding Course
		if(_Course)
		{
			_Course->removeCLO(CLO_id);	// Removing CLO from Course
		}
		else
		{
			cout<<"Course not found"<<endl;	// Print Course not found
		}
	}
	void removePLOFromProgram(string _name,int PLO_id)	// Removing PLO from Program
	{
		Program* _Program=this->findProgram(_name);	// Finding Program
		if(_Program)
		{
			_Program->removePLO(PLO_id);	// Removing PLO from Program
		}
		else
		{
			cout<<"Program not found"<<endl;	// Print Program not found
		}
	}
	void removeCourseFromProgram(string _name,int Course_id)	// Removing Course from Program
	{
		Program* _Program=this->findProgram(_name);		// Finding Program
		if(_Program)
		{
			_Program->removeCourse(Course_id);		// Removing Course from Program
		}
		else
		{
			cout<<"Program not found"<<endl;	// Print Program not found
		}
	}
	void removeQuestionFromEvaluation(int Question_id,string Evaluation_name)
	{
		evaluator->removeQuestionFromEvaluation(Question_id,Evaluation_name);	// Removing Question from Evaluation
	}
	void listOfRelevantCourses(string _name,int PLO_id)	// List of Relevant Courses
	{
		PLO* _PLO = this->findPLO(PLO_id);	// Finding PLO
		if(_PLO)
		{
			Program* _Program = this->findProgram(_name);	// Finding Program
			if(_Program)
			{
				_Program->getCoursesByPLO(_PLO);	// Getting Courses by PLO
			}
			else
			{
				cout<<"Program not Found"<<endl;	// Print Program not found
			}
		}
		else
		{
			cout<<"PLO not Found"<<endl;	// Print PLO not found
		}
	}
	bool allCLOsTested(int Course_id)	// All CLOs Tested
	{
		bool check=true;	// Check
		Course* _Course=this->findCourse(Course_id);	// Finding Course
		CLO** _CLOs;	// CLOs array pointer 
		int total; 
		_Course->getAllCLOs(_CLOs,total);	// Getting all CLOs
		for(int i=0;i<total && check;i++)	// Looping through all CLOs
			if(!evaluator->checkCLOHasTested(_CLOs[i]->getID()))	// Checking if CLO has been tested
				check=false;	// If not, check is false
		return check;	// Return check
	}
	void saveData()	// Saving Data
	{
		char option;	// Option to save data
		cout<<"Save Data? (y/n) : ";  
		cin>>option;	// Getting option
		if(option=='y')	
		{
			ofstream fout;	// File output stream
			fout.open("topics.txt");	// Opening topics file
			fout<<totalTopics<<endl;	// Writing total topics
			for(int i=0;i<totalTopics;i++)	// Looping through all topics
				topics[i]->saveData(fout);	// Saving topic data
			fout.close();	// Closing topics file
			fout.open("CLOs.txt");	// Opening CLOs file
			fout<<totalCLOs<<endl;	// Writing total CLOs
			for(int i=0;i<totalCLOs;i++)	// Looping through all CLOs
				CLOs[i]->saveData(fout);	// Saving CLO data
			fout.close();	// Closing CLOs file
			fout.open("PLOs.txt");	// Opening PLOs file
			fout<<totalPLOs<<endl;	// Writing total PLOs
			for(int i=0;i<totalPLOs;i++)	// Looping through all PLOs
				PLOs[i]->saveData(fout);	// Saving PLO data
			fout.close();	// Closing PLOs file
			fout.open("Courses.txt");	// Opening Courses file
			fout<<totalCourses<<endl;	// Writing total Courses
			for(int i=0;i<totalCourses;i++)	// Looping through all Courses
				courses[i]->saveData(fout);	// Saving Course data
			fout.close();	// Closing Courses file
			fout.open("Programs.txt");	// Opening Programs file
			fout<<totalPrograms<<endl;	// Writing total Programs
			for(int i=0;i<totalPrograms;i++)	// Looping through all Programs
				programs[i]->saveData(fout);	// Saving Program data
			fout.close();	// Closing Programs file
			fout.open("Questions.txt");	// Opening Questions file
			evaluator->saveQuestions(fout);	// Saving Questions
			fout.close();	// Closing Questions file
			fout.open("Evaluations.txt");	// Opening Evaluations file
			evaluator->saveEvaluations(fout);	// Saving Evaluations
			fout.close();	// Closing Evaluations file

		}
		else
		{
			cout<<"***Data not Saved***"<<endl;	
		}
	}
	void readData()	// Reading Data
	{
		ifstream fin;	// File input stream
		fin.open("topics.txt");	// Opening topics file
		if(fin)	// 
		{
			string _name;	// Topic name
			int total;		
			fin>>total;	// Reading total topics
			for(int i=0;i<total;i++)
			{
				fin>>_name;	// Reading topic name
				this->createTopic(_name);	// Creating topic
			}
		}
		fin.close();	// Closing topics file

		fin.open("CLOs.txt");	// Opening CLOs file
		if(fin)
		{
			int total;
			string _name;	// CLO name
			int _id;	// CLO id
			int count;	// Count
			fin>>total;	// Reading total CLOs
			for(int i=0;i<total;i++)
			{
				fin>>_name>>_id;	// Reading CLO name and id
				this->createCLO(_name,_id);	// Creating CLO
				fin>>count;	// Reading count
				for(int j=0;j<count;j++)
				{
					fin>>_name;	// Reading topic name
					addTopicToCLO(_name,_id);	// Adding topic to CLO
				}
			}
		}
		fin.close();	// Closing CLOs file


		fin.open("PLOs.txt");	// Opening PLOs file
		if(fin)	
		{
			int total;
			string _name;	// PLO name
			int _id;	// PLO id
			int count;	// Count
			fin>>total;		// Reading total PLOs
			for(int i=0;i<total;i++)
			{
				fin>>_name>>_id;	// Reading PLO name and id
				this->createPLO(_name,_id);	// Creating PLO
				fin>>count;		// Reading count
				int CLO_id;	// CLO id
				for(int j=0;j<count;j++)
				{
					fin>>CLO_id;	// Reading CLO id
					addCLOToPLO(CLO_id,_id);	// Adding CLO to PLO
				}
			}
		}
		fin.close();	// Closing PLOs file


		fin.open("Courses.txt");	// Opening Courses file
		if(fin)
		{
			int total;		// Total Courses
			string _name;	// Course name
			int _id;
			float creditHour;	// Credit hour
			string courseCode;	// Course code
			int count;
			fin>>total;		// Reading total Courses
			for(int i=0;i<total;i++)
			{
				fin>>_name>>_id>>courseCode>>creditHour;	// Reading Course name, id, course code and credit hour
				this->createCourse(_name,_id,courseCode,creditHour);	// Creating Course
				fin>>count;	// Reading count
				int CLO_id;	// CLO id
				for(int j=0;j<count;j++)
				{
					fin>>CLO_id;	// Reading CLO id
					addCLOToCourse(CLO_id,_id);		// Adding CLO to Course
				}
			}
		}
		fin.close();	// Closing Courses file


		fin.open("Programs.txt");	// Opening Programs file
		if(fin)
		{
			int total;
			string _name;	// Program name
			int totalCreditHour;	// Total credit hour
			int duration;	// Duration
			int count;	// Count
			fin>>total;	// Reading total Programs
			for(int i=0;i<total;i++)	
			{
				fin>>_name>>totalCreditHour>>duration;	// Reading Program name, total credit hour and duration
				this->createProgram(_name,duration,totalCreditHour);	// Creating Program
				fin>>count;	// Reading count
				int Course_id;	// Course id
				for(int j=0;j<count;j++)	
				{
					fin>>Course_id;	// Reading Course id
					addCourseToProgram(Course_id,_name);	// Adding Course to Program
				}
				fin>>count;	// Reading count
				int PLO_id;	// PLO id
				for(int j=0;j<count;j++)
				{
					fin>>PLO_id;	// Reading PLO id
					addPLOToProgram(PLO_id,_name);	// Adding PLO to Program
				}
			}
		}
		fin.close();	// Closing Programs file


		fin.open("Questions.txt");	// Opening Questions file
		if(fin)
		{
			int total;
			string _name;	// Question name
			int Question_id,CLO_id;	// Question id and CLO id
			fin>>total;	// Reading total Questions
			for(int i=0;i<total;i++)
			{
				fin>>Question_id>>_name>>CLO_id;	// Reading Question id, name and CLO id
				this->createQuestion(Question_id,_name,CLO_id);	// Creating Question
			}
		}
		fin.close();	// Closing Questions file


		fin.open("Evaluations.txt");	// Opening Evaluations file
		if(fin)
		{
			int total;
			string _name;	// Evaluation name
			char type;		// Evaluation type
			int totalMarks;	// Total marks
			float weightage;	// Weightage
			int count,_id;	// Count and id
			fin>>total;	// Reading total Evaluations
			for(int i=0;i<total;i++)
			{
				fin>>_name>>type>>totalMarks>>weightage;	// Reading Evaluation name, type, total marks and weightage
				this->createEvaluation(type,_name,totalMarks,weightage);	// Creating Evaluation
				fin>>count;		// Reading count
				for(int j=0;j<count;j++)
				{
					fin>>_id;		// Reading id
					addQuestionToEvaluation(_id,_name);		// Adding Question to Evaluation
				}
			}
		}
		fin.close();	// Closing Evaluations file
	}
	~AcademicManager()	// Destructor
	{
		if (size1)
			delete [] topics;	// Deleting topics
		if (size2)
			delete [] CLOs;		// Deleting CLOs
		if (size3)	
			delete [] PLOs;		// Deleting PLOs
		if (size4)
			delete [] courses;	// Deleting courses
		if (size5)	
			delete [] programs;		// Deleting programs
		if(evaluator)
			delete evaluator;		// Deleting evaluator
	}
};	// End of class AcademicManager


