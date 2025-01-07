#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct student
{
    char student_name[40];
    int student_id;
    int mark;
}student;
typedef struct course
{
    char course_name[50];
    float average_grade;
    int number_of_students;
    //dynamic array of enrolled students
    student *enrolled_students;
}course;
typedef struct school
{
    
    char school_name[50];
    int number_of_courses;
    //a dynamic array of courses offered by the school.
    course *courses_offered;

}school;

//Create a Student: Takes user input for student details, allocates a new student struct 
//in memory, and populates the struct with the provided details. 
student* create_a_student()
{
   student *student_data= (student*)malloc(sizeof(student));
    printf("\nenter the student name");
    scanf("%s",student_data->student_name);
    printf("\nenter the student id");
    scanf("%d",&student_data->student_id);
    printf("\nenter the student marks");
    scanf("%d",&student_data->mark);
    return student_data;
}

/*Create a Course: Asks for the number of students in a course and their details.
Allocates a new course struct in memory, and populates it with the provided course
details and students*/

course* create_a_course()
{
   course* course_data=(course*)malloc(sizeof(course));
   printf("enter the course name");
   scanf("%s",course_data->course_name);
   printf("\nthe number of students in the course is");
   scanf("%d",&course_data->number_of_students);
   student* student_list=(student*)malloc(course_data->number_of_students*sizeof(student));

   for(int i=0;i<=course_data->number_of_students;i++)
   {
    // student_list[i]=create_a_student();
    student* temp=create_a_student();
    //student_list[i]=*create_a_student();
    student_list[i]=*temp;
    free(temp);
   }
   course_data->enrolled_students=student_list;
   course_data->average_grade= averagegradecalculator(course_data->enrolled_students,course_data->number_of_students);
   return course_data;


}
float averagegradecalculator(course* studentdetails)
{
    float sum=0.0;
    for(int i=0;i<studentdetails->number_of_students;i++)
    {
        sum=sum+(studentdetails->enrolled_students[i].mark);
        
        
    }
    return sum/studentdetails->number_of_students;
   
}

//Create a School: Takes user input for the number of courses and their details.
//Allocates a new school struct in memory, and populates it with the provided details
school* create_a_school()
{
    
    printf("enter the school name\n");
    school *school1=(school*)malloc(sizeof(school));
    scanf("%s",school1->school_name);
    printf("\nthe number of courses offered");
    scanf("%d",&school1->number_of_courses);
    course *course_list=(course*)malloc(school1->number_of_courses*sizeof(course));
    for(int i=0;i<=school1->number_of_courses;i++)
    {
    course *temp2=create_a_course();
    course_list[i]=*temp2;
    }
    school1->courses_offered=course_list;
    return school1;


}
/*Print Student Details*/
void print_student_details(student* student_details)
{
    printf("name %s\n, student_id %d\n, student_mark %d\n",student_details->student_name,student_details->student_id,student_details->mark);
}




int main()
{
    school* master_database;
    master_database=create_a_school();
    return 0;
}






