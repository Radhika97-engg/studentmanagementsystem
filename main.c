#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NAME_LENGTH 50

// Structure to represent a student
typedef struct student
{
    char student_name [MAX_NAME_LENGTH]; // Array to store the student's name
    int student_id;                      // Integer to store the student's ID
    int mark;                            // Integer to store the student's marks
}student;

// Structure to represent a course
typedef struct course
{
    char course_name[MAX_NAME_LENGTH];   // Array to store the course name
    float average_grade;                 // Float to store the average grade of the course
    int number_of_students;              // Integer to store the number of students in the course
    student *enrolled_students;          // Pointer to a dynamic array of enrolled students
}course;
// Function to free memory allocated for a course
void free_course(course* course_input)
{
    if(course_input->enrolled_students != NULL) // Check if memory for students was allocated
    {
        free(course_input->enrolled_students);  // Free memory for the students
    }
    free(course_input);                         // Free memory for the course structure
}

// Structure to represent a school
typedef struct school
{
    char school_name[50];           // Array to store the name of the school
    int number_of_courses;          // Integer to store the number of courses offered
    course *courses_offered;        // Pointer to a dynamic array of courses offered by the school
}school;

// Function to free memory allocated for a school
void free_school(school* school_input)
{
    if(school_input->courses_offered != NULL) // Check if memory for courses was allocated
    {
        free(school_input->courses_offered);  // Free memory for the courses
    }
    free(school_input);                      // Free memory for the school structure
}

// Function to create a student with user input
student* create_a_student()
{
    // Allocate memory for a new student
    student *student_data = (student*)malloc(sizeof(student));
    
    // Prompt user for student details
    printf("enter the student name");
    scanf("%s", student_data->student_name); // Input the student's name
    printf("enter the student id");
    scanf("%d", &student_data->student_id); // Input the student's ID
    printf("enter the student marks");
    scanf("%d", &student_data->mark);       // Input the student's marks
    
    return student_data; // Return the pointer to the student structure
}
// Function to calculate the average grade of a course
float averagegradecalculator(course* studentdetails)
{
    float sum = 0.000; // Initialize sum to store the total marks
    // Loop through all students to calculate the sum of their marks
    for(int i = 0; i < studentdetails->number_of_students; i++)
    {
        sum = sum + (studentdetails->enrolled_students[i].mark);
    }
    // Calculate and print the average grade
    printf("the average value is %f\n", sum / studentdetails->number_of_students);
    // Return the calculated average
    return sum / studentdetails->number_of_students;
}
// Function to create a course with user input
course* create_a_course()
{
    // Allocate memory for a new course
    course* course_data = (course*)malloc(sizeof(course));
    
    // Prompt user for course details
    printf("enter the course name");
    scanf("%s", course_data->course_name); // Input the course name
    printf("\nthe number of students in the course is");
    scanf("%d", &course_data->number_of_students); // Input the number of students in the course
    
    // Allocate memory for the students in the course
    student* student_list = (student*)malloc(course_data->number_of_students * sizeof(student));
    
    // Loop to create and add students to the course
    for(int i = 0; i < course_data->number_of_students; i++)
    {
        // Create a temporary student using user input
        student* temp = create_a_student();
        
        // Copy the student details to the student list
        student_list[i] = *temp;
        
        // Free the temporary student structure
        free(temp);
    }
    
    // Assign the student list to the course
    course_data->enrolled_students = student_list;
    
    // Calculate and assign the average grade for the course
    course_data->average_grade = averagegradecalculator(course_data);
    
    // Return the pointer to the course structure
    return course_data;
}
//Create a School: Takes user input for the number of courses and their details.
//Allocates a new school struct in memory, and populates it with the provided details
school* create_a_school()
{
    printf("Enter the school name :");  // Prompt for school name input
    school *school1 = (school*)malloc(sizeof(school));  // Allocate memory for school struct
    scanf("%s", school1->school_name);  // Read school name input
    printf("The number of courses offered");  // Prompt for number of courses
    scanf("%d", &school1->number_of_courses);  // Read number of courses input
    course *course_list = (course*)malloc(school1->number_of_courses * sizeof(course));  // Allocate memory for courses array
    for(int i = 0; i < school1->number_of_courses; i++)
    {
        course *temp2 = create_a_course();  // Create course details
        course_list[i] = *temp2;  // Copy course details to list
    }
    school1->courses_offered = course_list;  // Set courses offered
    return school1;  // Return the created school
}

int selectcourse(school* schoolstruct)
{
    int choice;
    printf("The course list\n");  // Display course list
    for(int i = 0; i < schoolstruct->number_of_courses; i++)
    {
        printf("%d %s\n", i + 1, schoolstruct->courses_offered[i].course_name);  // Display course name with index
    }
    printf("\nEnter the choice:");  // Prompt for course selection
    scanf("%d", &choice);  // Read course selection input
    return choice - 1;  // Return selected course index
}

// Print Student Details
void print_student_details(student* student_details)
{
    printf("Name: %s, Student ID: %d, Student Mark: %d\n", student_details->student_name, student_details->student_id, student_details->mark);  // Display student details
}

// Print Course Details: Accepts a course struct and prints the details of the course and the students enrolled in it.
void print_course_details(course* course_details)
{
    printf("Course Name: %s, Average Grade: %.2f, Number of Students: %d\n", course_details->course_name, course_details->average_grade, course_details->number_of_students);  // Display course details
    for(int i = 0; i < course_details->number_of_students; i++)
    {
        print_student_details(&course_details->enrolled_students[i]);  // Display each enrolled student's details
    }
}

// Print School Details: Takes a school struct and prints the school's details, all the courses offered, and the students in those courses.
void print_school_details(school* school_details)
{
    printf("School Name: %s, Number of Courses Offered: %d\n", school_details->school_name, school_details->number_of_courses);  // Display school and course details
    for(int j = 0; j < school_details->number_of_courses; j++)
    {
        printf("\nCourse %d Details\n", j + 1);  // Display individual course details
        print_course_details(&school_details->courses_offered[j]);  // Print details of each course
    }
}

// Check if student in course: Takes a student's ID and a course struct, iterates over the course's student list, and checks if the student is enrolled.
void check_if_student_in_course(int student_id, course* ifstudentincourse)
{
    for(int j = 0; j < ifstudentincourse->number_of_students; j++)
    {
        if(ifstudentincourse->enrolled_students[j].student_id == student_id)  // Check if student ID matches
        {
            printf("The student is enrolled in the course %s\n", ifstudentincourse->course_name);  // Display course name
            print_student_details(&ifstudentincourse->enrolled_students[j]);  // Display student details
        }
    }
}

// Check if student in school: Accepts a student's ID and a school struct. It uses the previous function to check if the student is enrolled in any of the school's courses.
void check_if_student_in_school(int student_id, school* ifstudentinschool)
{
    for(int i = 0; i < ifstudentinschool->number_of_courses; i++)
    {
        check_if_student_in_course(student_id, &ifstudentinschool->courses_offered[i]);  // Check if student is enrolled in any course
    }
}

// Print all student courses: Receives a student's ID and a school struct. It prints out all the courses that the student is enrolled in.
void print_all_student_courses(int studentid, school* printstudentcourse)
{
    for(int i = 0; i < printstudentcourse->number_of_courses; i++)
    {
        for(int j = 0; j < printstudentcourse->courses_offered[i].number_of_students; j++)
        {
            if(printstudentcourse->courses_offered[i].enrolled_students[j].student_id == studentid)
            {
                printf("The student is enrolled in %s\n", printstudentcourse->courses_offered[i].course_name);  // Display course name
            }
        }
    }
}

// Print all students who failed a course: Accepts a course struct and a passing grade. Prints the details of students who didn't meet the passing grade.
void check_failed_students(int passing_grade, course* failed_student)
{
    printf("The student failed in the %s course\n", failed_student->course_name);  // Display failed course name
    for(int i = 0; i < failed_student->number_of_students; i++)
    {
        if(failed_student->enrolled_students[i].mark < passing_grade)  // Check if mark is below passing grade
        {
            print_student_details(&failed_student->enrolled_students[i]);  // Display student details
        }
    }
}

// Print all students who passed a course: Similar to the previous function but prints details of students who have met or exceeded the passing grade.
void check_passed_students(int passing_grade, course* passed_student)
{
    printf("The students who passed the %s course\n", passed_student->course_name);  // Display passed course name
    for(int i = 0; i < passed_student->number_of_students; i++)
    {
        if(passed_student->enrolled_students[i].mark >= passing_grade)  // Check if mark is above or equal to passing grade
        {
            print_student_details(&passed_student->enrolled_students[i]);  // Display student details
        }
    }
}

// Print all the courses with a passed average grade: Receives a school struct and a passing grade. Prints out courses where the average grade is equal to or higher than the passing grade.
void print_passed_average_grade(int passing_grade, school* passed_avg_grade)
{
    for(int i = 0; i < passed_avg_grade->number_of_courses; i++)
    {
        if(passed_avg_grade->courses_offered[i].average_grade >= passing_grade)
        {
            printf("%s course have passed average grade more than the average passing grade provided by you, i.e., %.2f\n", passed_avg_grade->courses_offered[i].course_name, passed_avg_grade->courses_offered[i].average_grade);  // Display courses with passed average grade
        }
    }
}

// Print all the courses with a failed average grade: Similar to the previous function but prints out courses where the average grade is below the passing grade.
void print_failed_average_grade(int passing_grade, school* failed_avg_grade)
{
    for(int i = 0; i < failed_avg_grade->number_of_courses; i++)
    {
        if(failed_avg_grade->courses_offered[i].average_grade < passing_grade)
        {
            printf("%s course have passed average grade less than the average passing grade provided by you : %.2f\n", failed_avg_grade->courses_offered[i].course_name, failed_avg_grade->courses_offered[i].average_grade);  // Display courses with failed average grade
        }
    }
}

// Print the average grade between all the courses: Accepts a school struct, calculates the average grade for each course, then calculates and prints the overall average of these averages.
void print_average_grade_between_all_the_courses(school *average_between_courses)
{
    float average;
    float sum = 0;
    for(int i = 0; i < average_between_courses->number_of_courses; i++)
    {
        sum += (average_between_courses->courses_offered[i].average_grade);  // Accumulate each course's average grade
    }
    average = sum / (average_between_courses->number_of_courses);  // Calculate overall average
    printf("Average of all the offered courses combined is %.2f\n", average);  // Display overall average
}
/* Print the course with the highest average grade: Receives a school struct, finds the course with the highest average grade, and prints its details. */
void print_course_with_highest_average_grade(school* course_with_highest_average)
{
    int highest_average = 0;  // Initialize index for the highest average course
    for(int i = 1; i < course_with_highest_average->number_of_courses; i++)
    {
        if(course_with_highest_average->courses_offered[i].average_grade >= course_with_highest_average->courses_offered[highest_average].average_grade)
        {
            highest_average = i;  // Update index of highest average course
        }
    }
    printf("The highest average graded course is %s with an average of %.2f\n", 
           course_with_highest_average->courses_offered[highest_average].course_name, 
           course_with_highest_average->courses_offered[highest_average].average_grade);
}

int main()
{
    int passing_grade;
    int student_id;
    int selection;
    int choice;
    int flag=0;
    school* master_database;
    printf("\n 1.Create a School\n");
    master_database = create_a_school();  // Create and populate the school database
    printf("\nEnter a passing grade threshold from 0 to 100:");  // Prompt for passing grade
    scanf("%d", &passing_grade);
    do
    {
        printf("MAIN MENU\n");
        printf("1.Print Course and Enrolled Student Details\n");
        printf("2.Print School Details\n");
        printf("3.Check courses enrolled by the student\n");
        printf("4.Check Students who passed and failed a particular course\n");
        printf("5.Print all courses with passed average grade\n");
        printf("6.Print all courses with failed average grade\n");
        printf("7.Print the average grade across all courses\n");
        printf("8.the course with the highest average grade\n");
        printf("9.Exit\n");
        printf("Enter your Choice : ");
        scanf("%d",&choice);
        switch(choice)
        {
           case 1:
                // Print details of all courses offered by the school
                for(int i = 0; i < master_database->number_of_courses; i++)
                 {
                    print_course_details(&master_database->courses_offered[i]);
                 }
                 break;
            case 2: 
                //Print School Details
                print_school_details(master_database);
                break;
            case 3:
                do{
                printf("\nEnter the student ID to be scanned:");  // Prompt for student ID
                scanf("%d", &student_id);
                for(int i=0;i<master_database->number_of_courses;i++)
                {
                    for(int j=0;j<master_database->courses_offered[i].number_of_students;j++)
                    {
                        if(student_id==master_database->courses_offered[i].enrolled_students[j].student_id)
                        {
                            flag=1;
                        }
                        
                    }
                }
                // Print all courses the student is enrolled in
                if(flag==1)
                {
                print_all_student_courses(student_id, master_database);
                }
                else
                printf("enter valid Student ID");
                }
                while(flag!=1);
                flag=0;
                break;
            case 4:
                selection = selectcourse(master_database);  // Select a specific course
                // Check failed and passed students for the selected course
                check_failed_students(passing_grade, &master_database->courses_offered[selection]);
                check_passed_students(passing_grade, &master_database->courses_offered[selection]);
                break;
            case 5:
                // Print courses with passed average grades
                print_passed_average_grade(passing_grade, master_database);
                break;
            case 6:
                // Print courses with failed average grades
                print_failed_average_grade(passing_grade, master_database);
                break;
            case 7:
                // Print the average grade across all courses
                print_average_grade_between_all_the_courses(master_database);
                break;
            case 8:
                // Print the course with the highest average grade
                print_course_with_highest_average_grade(master_database);
                break;
            case 0:
                //exit 
                break;
        }
    } while (choice !=0);
    free_school(master_database);
    return 0;
}



