#include "Student.h"
#include <cstring>
#include <stdio.h>


void Student::setName(const char name[]) {
	strcpy_s(this->name, name);
}

char* Student::getName() {
	return this->name;
}

void Student::setGradeMath(float grade) {
	gradeMath = grade;
}

float  Student::getGradeMath() {
	return gradeMath;
}

void Student::setGradeEnglish(float grade) {
	gradeEnglish = grade;
}

float  Student::getGradeEnglish() {
	return gradeEnglish;
}

void Student::setGradeHistory(float grade) {
	gradeHistory = grade;
}

float  Student::getGradeHistory() {
	return gradeHistory;
}

float Student::getGradeAverage() {
	return updateGradeAverage();
}

float Student::updateGradeAverage() {
	gradeAverage = (gradeMath + gradeEnglish + gradeHistory) / 3;
	return gradeAverage;

}

