
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void student_choices(int a);
void load_student(char *s1);
void add1_student(char *s1);
void delete_student(char *s1);
void modify_student(char *s1);

void instructor_choices(int a);
void print_instructors();
void load_instructor(char *f1);
void add1_instructor(char *f1);
void delete_instructor(char *f1);
void modify_instructor(char *f1);

void course_choices(int a);
void print_courses();
void load_course(char *s1);
void add1_course(char *s1);
void delete_course(char *s1);
void modify_course(char *s1);


enum branch {CSE, EE, ME};

struct course {
    char code[MAX];
    char name[MAX];
    int credits;
    int ninstructors;
    char **instructor_ids;
    int nstudents;
    char **student_rollnos;
};

struct student {
    char rollno[MAX];
    char name[MAX];
    enum branch branch;
    int semester;
    int ncourses;
    char **course_codes;
};

struct instructor {
    char id[MAX];
    char name[MAX];
    int ncourses;
    char **courses_codes;
};



void print_students();
void print_student(struct student s);
void print_to_file_student(struct student s);
void add_student(struct student s);
void add_instructor(struct instructor i);
void print_instructor(struct instructor i);
void print_to_file_instructor(struct instructor i);
void load_records();
void load_students();
void load_instructors();
void load_courses();
void print_course(struct course c);
void print_to_file_course(struct course c);
struct course *courses;
struct student *students;
struct instructor *instructors;

FILE *fps;
FILE *fpc;
FILE *fpi;

char students_file[MAX] = "students.txt";
char courses_file[MAX] = "courses.txt";
char instructors_file[MAX] = "instructors.txt";

int ncourses = 0, nstudents = 0, ninstructors = 0;

int main() {
    //printf("1");
    load_records();
    //printf("2");
    int flag=1;
    while(flag)
    {
	printf("Select(Enter the corresponding number):\n 1.Student Options(1).\n 2.Instructor Options(2).\n 3.Course Options(3).\n 4.Exit(4)\n\n");
	int option;
	scanf("%d",&option);
	putchar('\n');
	switch(option)
	{
    case 1:
        {printf("Choose the corresponding option:\n 1.Display all(Display details of all students)(1)\n 2.Display(Display details of a student)(2)\n 3.Add(Add the details of a new student)(3)\n 4.Delete(delete all the details of the student with a known roll no.)(4)\n 5.Modify(Modify details of a student)(5)\n\n");
		int choice;
		scanf("%d",&choice);
		putchar('\n');
		student_choices(choice);
		break;}
    case 2:
        {printf("Choose the corresponding option:\n 1.Display all(Display details of all instructors)(1)\n 2.Display(Display details of a instructor)(2)\n 3.Add(Add the details of a new instructor)(3)\n 4.Delete(delete all the details of the instructor with a known fac id)(4)\n 5.Modify(Modify details of an instructor)(5)\n\n");
        int choice;
        scanf("%d",&choice);
        putchar('\n');
        instructor_choices(choice);
        break;}
    case 3:
        {printf("Choose the corresponding option:\n 1.Display all(Display details of all courses)(1)\n 2.Display(Display details of a course)(2)\n 3.Add(Add the details of a new course)(3)\n 4.Delete(delete all the details of the course with a known course code)(4)\n 5.Modify(Modify details of a course)(5)\n\n");
        int choice;
        scanf("%d",&choice);
        putchar('\n');
        course_choices(choice);
        break;}
    case 4:
        flag=0;
        break;
    default:
        printf("Option does not exist, please enter a valid option\n");

    }

    }

    return 0;
}

void student_choices(int a)
{
	switch(a)
	{
    case 1:
        print_students();
        break;
    case 2:
        {
            char rollno[MAX];
            printf("Enter Roll number:");
            scanf("%s",rollno);
            load_student(rollno);
            break;
		}
    case 3:
        {
			char rollno[MAX];
			printf("Enter Roll number:");
			scanf("%s",rollno);
			add1_student(rollno);
			break;

        }
    case 4:
        {
            char rollno[MAX];
			printf("Enter Roll number:");
			scanf("%s",rollno);
			printf("\n");
			delete_student(rollno);
			break;
        }
    case 5:
        {
            char rollno[MAX];
			printf("Enter Roll number:");
			scanf("%s",rollno);
			printf("\n");
			modify_student(rollno);
			break;
        }
    default:
        printf("Error:Option doesn't exist.\n\n");

	}

}

void load_students() {
     fps = fopen(students_file, "r");
    int nstudents;
    char buf[MAX];
    struct student s;
    fscanf(fps, "%d", &nstudents);
    for (int i=0; i<nstudents; i++) {
        fgets(buf, MAX, fps);
        fscanf(fps, "%s", s.rollno);
        fscanf(fps, " %[^\n]s", s.name);
        fscanf(fps, "%u", &s.branch);
        fscanf(fps, "%d", &s.semester);
        fscanf(fps, "%d", &s.ncourses);
        s.course_codes = malloc (s.ncourses * sizeof(char *));
        for (int j=0; j<s.ncourses; j++) {
            s.course_codes[j] = malloc (MAX * sizeof (char));
            fscanf(fps, "%s", s.course_codes[j]);
        }
        add_student(s);
    }
    fclose(fps);
}

void load_student(char *s1)
{

	int found=0;
	int index;
	for(int i=0;i<nstudents;i++)
    {
        int temp;
        temp=strcmp(students[i].rollno,s1);
        if(temp==0)
        {
            found=1;
            index=i;
        }
    }
    if(found==0)
    {
        printf("Student Not Found\n\n");
        return;
    }
    printf("Student details\n_______________________________________________\n\n");
    print_student(students[index]);

}

void add1_student(char *s1)
{
    for(int i=0;i<nstudents;i++)
    {
        if(!(strcmp(s1,students[i].rollno)))
        {
            printf("Student already exists\n\n");
            return;
        }
    }
	struct student temp;
	strcpy(temp.rollno,s1);
    printf("Enter Details:\n ");
    printf("Enter Name:\n ");
    scanf(" %[^\n]s",temp.name);
    printf("Enter Branch:\(0 for CSE, 1 for EE, 2 for ME\)\n ");
    scanf("%u",&temp.branch);
    printf("Enter Semester:\n ");
    scanf("%d",&temp.semester);
    printf("Enter Number of courses:\n ");
    scanf("%d",&temp.ncourses);
    printf("Enter Courses:\n");
    temp.course_codes = malloc (temp.ncourses * sizeof(char *));
    for (int j=0; j<temp.ncourses; j++)
    {
        printf(" ");
        temp.course_codes[j] = malloc (MAX * sizeof (char));
        scanf("%s", temp.course_codes[j]);
        int found=0;
        for(int k=0;k<ncourses;k++)
        {
            if(temp.course_codes[j]==courses[k].code)
                found=1;
        }
        if(!found)
        {
            printf("\nThis course is not listed in the database. Do you want to add this course in the database? Yes(1) No(2) \n");
            int choice;
            scanf("%d",&choice);
            switch(choice)
            {
            case 1:
                add1_course(temp.course_codes[j]);
            case 2:
                continue;
            default:
                printf("Invalid choice\n");
                continue;
            }
        }
    }
	putchar('\n');
	add_student(temp);
	fps = fopen(students_file, "w");
	fprintf(fps,"%d\n\n",nstudents);
    for(int j=0;j<nstudents;j++)
    {
    	print_to_file_student(students[j]);
    }
    fclose(fps);

}

void add_student(struct student s) {
    students = realloc (students, (nstudents+1)*sizeof(struct student));
    students[nstudents] = s;
    nstudents++;
}

void print_students() {
    printf("Students' details:\n-----------------\n");
    for (int i=0; i<nstudents; i++) {
        print_student(students[i]);
    }
}

void print_student(struct student s) {
    printf("Roll no.: %s\n", s.rollno);
    printf("Name: %s\n", s.name);
    printf("Branch: %d\n", s.branch);
    printf("Semester: %d\n", s.semester);
    printf("List of coures:\n");
    for (int i=0; i<s.ncourses; i++) {
        printf("%s\n", s.course_codes[i]);
    }
    printf("\n");
}


void delete_student(char *s1)
{
    int index;
    int found=0;
    for(int i=0;i<nstudents;i++)
    {
        if(!(strcmp(s1,students[i].rollno)))
        {
            index=i;
            found=1;
        }
    }
    if(found==0)
    {
        printf("Student does not exist in the database\n\n");
        return;
    }
    for(int i=index;i<nstudents-1;i++)
    {
        students[i]=students[i+1];
    }
    nstudents--;
    students=realloc(students,nstudents * sizeof(struct student));
    fps = fopen(students_file, "w");
	fprintf(fps,"%d\n\n",nstudents);
    for(int j=0;j<nstudents;j++)
    {
    	print_to_file_student(students[j]);
    }
    fclose(fps);

}

void modify_student(char *s1)
{
    int index;
    int found=0;
    for(int i=0;i<nstudents;i++)
    {
        if(!(strcmp(s1,students[i].rollno)))
        {
            index=i;
            found=1;
        }
    }
    if(found==0)
    {
        printf("Student does not exist in the database\n\n");
        return;
    }
    printf("Select the number corresponding to the data to be modified:\n 1.Name(1)\n 2.Branch(2)\n 3.Semester(3)\n 4.Courses(4)\n\n");
    int b;
    scanf("%d",&b);
    putchar('\n');
    switch(b)
    {
    int c;
    case 1 : printf("Enter the Modified Name:\n\n ");
    		 char name1[MAX];
    		 scanf(" %[^\n]s",name1);
    		 strcpy(students[index].name,name1);
    		 break;

    		case 2 : printf("Enter the Modified Branch('0' for CSE, '1' for EE, '2' for ME):\n ");
    				 scanf("%d",&c);
    				 if(students[index].branch!=c)
    				 {
    				 	students[index].branch=c;
    				 }
    				 else
    				 {
    				 	printf("Student is already in the same branch.\n");
    				 }

    				 break;
    		case 3 : printf("Enter the Modified Semester:\n ");
    				 scanf("%d",&c);
    				 if(students[index].semester!=c)
    				 {
    				 	students[index].semester=c;
    				 }
    				 else
    				 {
    				 	printf("Student is already in the same semester.\n");
    				 }
    				 break;
    		case 4 : printf("Enter the Modified Number of courses:");
    				 scanf("%d",&c);
    				 putchar('\n');
    				 students[index].ncourses=c;
    				 students[index].course_codes=realloc(students[index].course_codes, c * sizeof(char *));
    				 printf("Enter the Course Codes:\n");
    				 for (int j=0; j<c; j++)
        			{
            			students[index].course_codes[j] = malloc (MAX * sizeof (char));
            			scanf("%s", students[index].course_codes[j]);
        			}
        			break;
            default:printf("Invalid Option\n\n");
                    return;

    	}
    fps = fopen(students_file, "w");
	fprintf(fps,"%d\n\n",nstudents);
    for(int j=0;j<nstudents;j++)
    {
    	print_to_file_student(students[j]);
    }
    fclose(fps);
}

void print_to_file_student(struct student s)
{

    	fprintf(fps,"%s\n",s.rollno);
    	fprintf(fps,"%s\n",s.name);
    	fprintf(fps,"%u\n",s.branch);
    	fprintf(fps,"%d\n",s.semester);
    	fprintf(fps,"%d\n",s.ncourses);
    	for (int k=0; k<s.ncourses; k++)
        {
            fprintf(fps,"%s\n",s.course_codes[k]);
        }

        fprintf(fps,"\n");

}

void instructor_choices(int a)
{
	char fac_id[MAX];
	switch(a)
	{
    case 1:
        print_instructors();
        break;
    case 2:
        printf("Enter Faculty Id:");
        scanf("%s",fac_id);
		load_instructor(fac_id);
		break;
    case 3:
        printf("Enter Faculty Id:");
        scanf("%s",fac_id);
		printf("\n");
		add1_instructor(fac_id);
		break;
    case 4:
        printf("Enter Faculty Id:");
		scanf("%s",fac_id);
		printf("\n");
		delete_instructor(fac_id);
        break;
    case 5:
        printf("Enter Faculty Id:");
		scanf("%s",fac_id);
		printf("\n");
		modify_instructor(fac_id);
		break;
    default:
        printf("Error:Option doesn't exist.\n\n");

	}

}

void load_instructors()
{
    fpi = fopen(instructors_file, "r");
    int ninstructors;
    char buf[MAX];
    struct instructor i;
    fscanf(fpi, "%d", &ninstructors);
    for (int a=0; a<ninstructors; a++) {
        fgets(buf, MAX, fpi);
        fscanf(fpi, "%s", i.id);
        fscanf(fpi, " %[^\n]s", i.name);
        fscanf(fpi, "%d", &i.ncourses);
        i.courses_codes = malloc (i.ncourses * sizeof(char *));
        for (int j=0; j<i.ncourses; j++) {
            i.courses_codes[j] = malloc (MAX * sizeof (char));
            fscanf(fpi, "%s", i.courses_codes[j]);
        }
        add_instructor(i);
    }

	fclose(fpi);
}

void load_instructor(char *s1)
{

	int found=0;
	int index;
	for(int i=0;i<ninstructors;i++)
    {
        int temp;
        temp=strcmp(instructors[i].id,s1);
        if(temp==0)
        {
            found=1;
            index=i;
        }
    }
    if(found==0)
    {
        printf("Instructor Not Found\n\n");
        return;
    }
    printf("Instructor details\n_______________________________________________\n\n");
    print_instructor(instructors[index]);

}

void add1_instructor(char *s1)
{
    for(int i=0;i<ninstructors;i++)
    {
        if(!(strcmp(s1,instructors[i].id)))
        {
            printf("Instructor already exists\n\n");
            return;
        }
    }
	struct instructor temp;
	strcpy(temp.id,s1);
    printf("Enter Details:\n ");
    printf("Enter Name:\n ");
    scanf(" %[^\n]s",temp.name);
    printf("Enter Number of courses:\n ");
    scanf("%d",&temp.ncourses);
    printf("Enter Courses:\n");
    temp.courses_codes = malloc (temp.ncourses * sizeof(char *));
    for (int j=0; j<temp.ncourses; j++)
    {
       	printf(" ");
        temp.courses_codes[j] = malloc (MAX * sizeof (char));
        scanf("%s", temp.courses_codes[j]);
    }
    add_instructor(temp);
    fpi = fopen(instructors_file, "w");
	fprintf(fpi,"%d\n\n",ninstructors);
    for(int j=0;j<ninstructors;j++)
    {
    	print_to_file_instructor(instructors[j]);
    }
    fclose(fpi);
}


void delete_instructor(char *s1)
{
    int index;
    int found=0;
    for(int i=0;i<ninstructors;i++)
    {
        if(!(strcmp(s1,instructors[i].id)))
        {
            index=i;
            found=1;
        }
    }
    if(found==0)
    {
        printf("Instructor does not exist in the database\n\n");
        return;
    }
    for(int i=index;i<ninstructors-1;i++)
    {
        instructors[i]=instructors[i+1];
    }
    ninstructors--;
    instructors=realloc(instructors,ninstructors * sizeof(struct instructor));
    fpi = fopen(instructors_file, "w");
	fprintf(fpi,"%d\n\n",ninstructors);
    for(int j=0;j<ninstructors;j++)
    {
    	print_to_file_instructor(instructors[j]);
    }
    fclose(fpi);

}


void modify_instructor(char *s1)
{
    int index;
    int found=0;
    for(int i=0;i<ninstructors;i++)
    {
        if(!(strcmp(s1,instructors[i].id)))
        {
            index=i;
            found=1;
        }
    }
    if(found==0)
    {
        printf("Instructor does not exist in the database\n\n");
        return;
    }
   printf("Select the number corresponding to the data to be modified:\n 1.Name(1)\n 2.Courses(2)\n\n");
   int b;
   scanf("%d",&b);
   putchar('\n');
    	switch(b)
    	{
    		int c;
    		case 1 : printf("Enter the Modified Name:\n\n ");
    				 char name1[MAX];
    				 scanf(" %[^\n]s",name1);
    				 strcpy(instructors[index].name,name1);
    				 break;
    		case 2 : printf("Enter the Modified Number of courses:");
    				 scanf("%d",&c);
    				 putchar('\n');
    				 instructors[index].ncourses=c;
    				 printf("Enter the Course Codes:\n");
    				 instructors[index].courses_codes=realloc(instructors[index].courses_codes, c * sizeof(char *));
    				 for (int j=0; j<c; j++)
        			{
            			instructors[index].courses_codes[j] = malloc (MAX * sizeof (char));
            			scanf("%s", instructors[index].courses_codes[j]);
        			}
        			break;
            default:printf("Invalid Option\n\n");
                    return;

    	}
    putchar('\n');
   	fpi = fopen(instructors_file, "w");
	fprintf(fpi,"%d\n\n",ninstructors);
    for(int j=0;j<ninstructors;j++)
    {
    	print_to_file_instructor(instructors[j]);
    }
    fclose(fpi);
}


void print_to_file_instructor(struct instructor i)
{
	fprintf(fpi,"%s\n",i.id);
    fprintf(fpi,"%s\n",i.name);
    fprintf(fpi,"%d\n",i.ncourses);
    for (int k=0; k<i.ncourses; k++)
    {
    	fprintf(fpi,"%s\n",i.courses_codes[k]);
    }

    fprintf(fpi,"\n");

}

void add_instructor(struct instructor i) {
    instructors = realloc (instructors, (ninstructors+1)*sizeof(struct instructor));
    instructors[ninstructors] = i;
    ninstructors++;
}


void print_instructors()
{
	printf("Instructors' details:\n-----------------\n");
    for (int j=0; j<ninstructors; j++) {
        print_instructor(instructors[j]);
    }
}

void print_instructor(struct instructor i)
{
    printf("Faculty Id: %s\n", i.id);
    printf("Name: %s\n", i.name);
    printf("List of coures:\n");
    for (int j=0; j<i.ncourses; j++) {
        printf("%s\n", i.courses_codes[j]);
    }
    printf("\n");
}


void load_records() {
    load_students();
    load_instructors();
    load_courses();
}

void add_course(struct course c)
{
    courses = realloc (courses, (ncourses+1)*sizeof(struct course));
    courses[ncourses] = c;
    ncourses++;
}

void load_courses() {
    fpc = fopen(courses_file, "r");
    int ncourses;
    char buf[MAX];
    //char *ptr;
    struct course s;
    fscanf(fpc, "%d", &ncourses);
    for (int i=0; i<ncourses; i++) {
        fgets(buf, MAX, fpc);
        fscanf(fpc, "%s", s.code);
        //getchar();
        //fgetc(fpc);
        //char t1[MAX],t2[MAX];
        //fscanf(fpc,"%[^\n]s",s.name);
        //fscanf(fpc,"%s %s",t1,t2);
        //ptr=strcat(t1,t2);
        //strcpy(s.name,ptr);
        fscanf(fpc, " %[^\n]s",s.name);
        fscanf(fpc, "%d", &s.credits);
        fscanf(fpc, "%d", &s.ninstructors);
        s.instructor_ids = malloc(s.ninstructors * sizeof(char *));
        for(int j=0;j<s.ninstructors;j++)
        {
            s.instructor_ids[j] = malloc(MAX * sizeof(char));
            fscanf(fpc,"%s",s.instructor_ids[j]);
        }
        fscanf(fpc, "%d", &s.nstudents);
        s.student_rollnos = malloc(s.nstudents * sizeof(char *));
        for(int j=0;j<s.nstudents;j++)
        {
            s.student_rollnos[j] = malloc(MAX * sizeof(char));
            fscanf(fpc,"%s", s.student_rollnos[j]);
        }

        add_course(s);
    }
    fclose(fpc);
}

void print_courses()
{
    printf("Courses' details:\n-----------------\n");
    for (int j=0; j<ncourses; j++) {
        print_course(courses[j]);
    }
}

void print_course(struct course c)
{
    printf("Course code: %s\n",c.code);
    printf("Name of course: %s\n",c.name);
    printf("Credits: %d\n",c.credits);
    printf("No. of instructors: %d\n",c.ninstructors);
    printf("IDs of the instructors: \n");
    for(int i=0;i<c.ninstructors;i++)
    {
        printf("%s\n",c.instructor_ids[i]);
    }
    printf("No. of students enrolled: %d\n",c.nstudents);
    for(int i=0;i<c.nstudents;i++)
    {
        printf("%s\n",c.student_rollnos[i]);
    }
    printf("\n\n");
}


void course_choices(int a)
{
	switch(a)
	{
    case 1:
        print_courses();
        break;
    case 2:
        {
            char coursecode[MAX];
            printf("Enter Course Code:");
            scanf("%s",coursecode);
            load_course(coursecode);
            break;
		}
    case 3:
        {
			char coursecode[MAX];
			printf("Enter Course Code:");
			scanf("%s",coursecode);
			add1_course(coursecode);
			break;

        }
    case 4:
        {
            char coursecode[MAX];
			printf("Enter Course Code:");
			scanf("%s",coursecode);
			printf("\n");
			delete_course(coursecode);
			break;
        }
    case 5:
        {
            char coursecode[MAX];
			printf("Enter Course Code:");
			scanf("%s",coursecode);
			printf("\n");
			modify_course(coursecode);
			break;
        }
    default:
        printf("Error:Option doesn't exist.\n\n");

	}

}


void load_course(char *s1)
{
    int found=0;
	int index;
	for(int i=0;i<ncourses;i++)
    {
        int temp;
        temp=strcmp(courses[i].code,s1);
        if(temp==0)
        {
            found=1;
            index=i;
        }
    }
    if(found==0)
    {
        printf("Course Not Found\n\n");
        return;
    }
    printf("Course details\n_______________________________________________\n\n");
    print_course(courses[index]);

}

void add1_course(char *s1)
{
    for(int i=0;i<ncourses;i++)
    {
        if(!(strcmp(s1,courses[i].code)))
        {
            printf("Instructor already exists\n\n");
            return;
        }
    }
	struct course temp;
	strcpy(temp.code,s1);
    printf("Enter Details\n");
    printf("Enter name of course:\n");
    scanf(" %[^\n]s",temp.name);
    printf("Enter credits for the course:\n");
    scanf("%d",&temp.credits);
    printf("Enter number of instructors for the course:\n");
    scanf("%d",&temp.ninstructors);
    printf("Enter the IDs of the instructors:\n");
    temp.instructor_ids = malloc(ninstructors * sizeof(char *));
    for(int i=0;i<temp.ninstructors;i++)
    {
        temp.instructor_ids[i] = malloc(MAX * sizeof(char));
        scanf("%s",temp.instructor_ids[i]);
    }
    printf("Enter no. of students enrolled in the course:\n");
    scanf("%d",&temp.nstudents);
    printf("Enter the roll numbers of the students:\n");
    temp.student_rollnos = malloc(nstudents * sizeof(char *));
    for(int i=0;i<temp.nstudents;i++)
    {
        temp.student_rollnos[i] = malloc(MAX * sizeof(char));
        scanf("%s",temp.student_rollnos[i]);
    }
    putchar('\n');
    add_course(temp);
    fpc = fopen(courses_file, "w");
	fprintf(fpc,"%d\n\n",ncourses);
    for(int j=0;j<ncourses;j++)
    {
    	print_to_file_course(courses[j]);
    }
    fclose(fpc);
}

void print_to_file_course(struct course c)
{
    fprintf(fpc,"%s\n",c.code);
    fprintf(fpc,"%s\n",c.name);
    fprintf(fpc,"%d\n",c.credits);
    fprintf(fpc,"%d\n",c.ninstructors);
    for(int i=0;i<c.ninstructors;i++)
    {
        fprintf(fpc,"%s\n",c.instructor_ids[i]);
    }
    fprintf(fpc,"%d\n",c.nstudents);
    for(int i=0;i<c.nstudents;i++)
    {
        fprintf(fpc,"%s\n",c.student_rollnos[i]);
    }
    fprintf(fpc,"%c",'\n');
}

void delete_course(char *s1)
{
   int index;
    int found=0;
    for(int i=0;i<ncourses;i++)
    {
        if(!(strcmp(s1,courses[i].code)))
        {
            index=i;
            found=1;
        }
    }
    if(found==0)
    {
        printf("Course does not exist in the database\n\n");
        return;
    }
    for(int i=index;i<ncourses-1;i++)
    {
        courses[i]=courses[i+1];
    }
    ncourses--;
    courses=realloc(courses,ncourses * sizeof(struct course));
    fpc = fopen(courses_file, "w");
	fprintf(fpc,"%d\n\n",ncourses);
    for(int j=0;j<ncourses;j++)
    {
    	print_to_file_course(courses[j]);
    }
    fclose(fpc);

}

void modify_course(char *s1)
{
    int index;
    int found=0;
    for(int i=0;i<ncourses;i++)
    {
        if(!(strcmp(s1,courses[i].code)))
        {
            index=i;
            found=1;
        }
    }
    if(found==0)
    {
        printf("Course does not exist in the database\n\n");
        return;
    }
   printf("Select the number corresponding to the data to be modified:\n 1.Name(1)\n 2.Credits(2)\n 3.Instructors\n 4.Students\n\n");
   int b;
   scanf("%d",&b);
   putchar('\n');
    	switch(b)
    	{
    		int c;
    		case 1 : printf("Enter the Modified Name:\n\n ");
    				 char name1[MAX];
    				 scanf(" %[^\n]s",name1);
    				 strcpy(courses[index].name,name1);
    				 break;
    		case 2 : printf("Enter the Modified Credits: ");
    				 scanf("%d",&c);
    				 putchar('\n');
    				 putchar('\n');
    				 courses[index].credits=c;
    				 break;
            case 3:  printf("Enter number of instructors: ");
                     scanf("%d",&courses[index].ninstructors);
                     putchar('\n');
                     putchar('\n');
                     printf("Enter IDs of instructors: \n");
                     courses[index].instructor_ids = malloc(courses[index].ninstructors * sizeof(char *));
                     for(int i=0;i<courses[index].ninstructors;i++)
                     {
                         courses[index].instructor_ids[i] = malloc(MAX * sizeof(char));
                         scanf("%s",courses[index].instructor_ids[i]);
                     }
                     break;
            case 4:  printf("Enter number of students: ");
                     scanf("%d",&courses[index].nstudents);
                     printf("\n\n");
                     printf("Enter roll numbers of students: \n");
                     courses[index].student_rollnos =  malloc(courses[index].nstudents * sizeof(char *));
                     for(int i=0;i<courses[index].nstudents;i++)
                     {
                         courses[index].student_rollnos[i] =  malloc(MAX * sizeof(char));
                         scanf("%s",courses[index].student_rollnos[i]);
                     }
                     break;
            default: printf("Invalid Option\n\n");
                     return;



    	}
    putchar('\n');
   	fpc = fopen(courses_file, "w");
	fprintf(fpc,"%d\n\n",ncourses);
    for(int j=0;j<ncourses;j++)
    {
    	print_to_file_course(courses[j]);
    }
    fclose(fpc);
}
