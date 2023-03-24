#pragma once
class Student
{
private:
	char name[25];
	float gradeMath;
	float gradeEnglish;
	float gradeHistory;
	float gradeAverage;
	float updateGradeAverage();
public:
	void  setName(const char name[]);
	char* getName();

	void  setGradeMath(float grade);
	float getGradeMath();

	void  setGradeEnglish(float grade);
	float getGradeEnglish();

	void  setGradeHistory(float grade);
	float getGradeHistory();

	float getGradeAverage();
};

