#include <stdio.h>
#include <string.h>


// --- Structures ---
struct Student {
    char StudentID[20];
    char name[100];
    char course[100];
    int year;
    int semester;
    float fees;
};
struct Exam{
    char StudentID[20];
    char type[20];
};

struct Attendance {
    int present;
    char name[100];
    char course[100];
    char StudentID[20];
};

// --- Register Student ---
void registerStudent(struct Student s[], struct Attendance a[], int *n) {
    printf("\n---[Student Registration]---\n");

    printf("\nEnter Student ID:\n ");
    scanf(" %19[^\n]", s[*n].StudentID);
    
    printf("\nEnter Name:\n ");
    scanf(" %[^\n]", s[*n].name);  

    printf("\nEnter  Course:\n ");
    scanf(" %[^\n]", s[*n].course);  

    printf("\nEnter Academic Year:\n ");
    scanf("%d", &s[*n].year);

    printf("\nEnter Semester:\n ");
    scanf("%d", &s[*n].semester);

    printf("\nEnter Fees Paid:\n ");
    scanf("%f", &s[*n].fees);

    if(s[*n].fees < 50000){
        printf("Registration failed! Insufficient fees.\n");
        return;
    }
    // Copy student info to attendance record 
    strcpy(a[*n].name, s[*n].name);
    strcpy(a[*n].course, s[*n].course);
    strcpy(a[*n].StudentID, s[*n].StudentID);
    a[*n].present = 0;  

    printf("\nStudent Registered Successfully!\n");
    (*n)++;
}

// --- Register for Examination ---
void registerExam(struct Student s[], int n ){
    printf("\n---Exam Registration---\n");

    struct Exam e;
    int choice;

    printf("\nEnter Student ID:\n ");
    scanf("%s", &e.StudentID);

    for(int i = 0; i < n; i++) {
     if(strcmp(s[i].StudentID, e.StudentID)== 0) {
             if(s[i].fees < 50000) {
                printf("Registration failed! Insufficient fees.\n");
                return;
            }

            printf("Enter exam type:\n 1. Special\n 2. Supplementary\n 3. Retake\n Choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    strcpy(e.type, "Special");
                    break;
                case 2:
                    strcpy(e.type, "Supplementary");
                    break;
                case 3:
                    strcpy(e.type, "Retake");
                    break;
                default:
                    printf("Invalid Choice\n");
            }

            printf("Exam Registration Successful!\n");
            return;
            

        }
    }
    printf("Student ID not found!\n");
    printf("Exam Registration Failed!\n");
}

// --- Mark Attendance (Only for Entered Course) ---
void markAttendance(struct Attendance a[], int n) {
    printf("\n---[Mark Attendance]---\n");

    if (n == 0) {
        printf("No students registered yet!\n");
        return;
    }

    char courseInput[100];
    printf("\nEnter Course Name to Mark Attendance: ");
    scanf(" %[^\n]", courseInput);

    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(courseInput, a[i].course)== 0) {
            printf("%s %s (%s) 1=Yes, 0=No: ", a[i].StudentID,a[i].name, a[i].course);
            scanf("%d", &a[i].present);
            found = 1;
        }
    }
    if (!found) {
        printf("No students found in this course.\n");
    }
}

// --- View Attendance Report ---
void showAttendance(struct Attendance a[], int n) {
    printf("\n---[ Attendance ]---\n");
    if (n == 0) {
        printf("No attendance records available!\n");
        return;
    }

    char courseInput[100];
    printf("\nEnter Course Name to View Attendance: ");
    scanf(" %[^\n]", courseInput);

    int found = 0;
    printf("\nAttendance Report for %s:\n", courseInput);
    for (int i = 0; i < n; i++) {
        if(strcmp(a[i].course, courseInput) == 0) {  // Compare course names
            printf("%s - %s\n", a[i].name, a[i].present ? "Present" : "Absent");
            found = 1;
        }
    }
    if (!found) {
        printf("No students found in this course.\n");
    }
}

// --- Show Students Per Course ---
void showStudents(struct Student s[], int n) {
    printf("\n---[ View Students Per Course ]---\n");
    if (n == 0) {
        printf("No students registered yet!\n");
        return;
    }

    char courseInput[100];
    printf("\nEnter Course Name : ");
    scanf(" %[^\n]", courseInput);

    int found = 0;
    printf("\nStudents in %s:\n", courseInput);
    for (int i = 0; i < n; i++) {
        if (strcmp(s[i].course, courseInput) == 0) {  // Compare course names
            printf("%s\n", s[i].name);
            found = 1;
        }
    }
    if (!found) {
        printf("No students found in this course.\n");
    }
}

// --- Main Menu ---
int main() {
    struct Student s[100];
    struct Attendance a[100];
    int n = 0 , ch;
    printf("---[Main Menu]---");

    while (1) {
        printf("\n1. Student\n2. Lecturer\n3. Exit\nEnter your choice: ");
        scanf("%d", &ch);

        if (ch == 1) {
            printf("\n1. Register for Semester\n2. Register for Examination\n3. View Attendance\nEnter your choice: ");
            scanf("%d", &ch);

            switch (ch)
            {
            case 1:
                registerStudent( s, a, &n);
                 break;
            case 2:
                registerExam(s, n);
                break;
            
            default:
                showAttendance(a, n);
                break;
            }
        } else if (ch == 2) {
            printf("\n1. Mark Attendance\n2. View Attendance\n3. View Students Per Course\nEnter your choice: ");
            scanf("%d", &ch);

            if (ch == 1) {
                markAttendance(a, n);
            } else if (ch == 2) {
                showAttendance(a, n);
            } else {
                showStudents(s, n);
            }
        
        } else {
            printf("Thankyou for using our system.\nExiting...\n");
            break;
        }
    }
    return 0;
}


