#include <stdio.h>



// --- Structures ---
struct Student {
    int StudentID;
    char name[50];
    char course[50];
    int year;
    int semester;
    float fees;
};
struct Exam{
    int StudentID;
    char type[20];
};

struct Attendance {
    int present;
    char name[50];
    char course[50];
};

// --- Register Student ---
void registerStudent(struct Student s[], struct Attendance a[], int *n) {
    printf("\n---[Student Registration]---\n");

    printf("Enter Student ID: ");
    scanf("%d", &s[*n].StudentID);
    
    printf("\nEnter Name(no spacing): ");
    scanf("%s", s[*n].name);  // Reads name without spaces

    printf("Enter Course(no spacing): ");
    scanf("%s", s[*n].course);  // Reads course without spaces

    printf("Enter Academic Year: ");
    scanf("%d", &s[*n].year);

    printf("Enter Semester: ");
    scanf("%d", &s[*n].semester);

    printf("Enter Fees Paid: ");
    scanf("%f", &s[*n].fees);

    if(s[*n].fees < 50000){
        printf("Registration failed! Insufficient fees.\n");
        return;
    }
    // Copy student info to attendance record 
    for (int i = 0; i < 50; i++) {
        a[*n].name[i] = s[*n].name[i];
        a[*n].course[i] = s[*n].course[i];
    }
    a[*n].present = 0; // Default: Absent

    printf("\nStudent Registered Successfully!\n");
    (*n)++;
}
// --- Register for Examination ---
void registerExam( ){
    printf("\n---Exam Registration---\n");

    struct Exam e;
    printf("Enter Student ID: ");
    scanf("%d", &e.StudentID);
    printf("Select Exam Type:\n 1.Special\n2.Supplementary\n3.Retake\n ");
    scanf("%d", e.type);
    printf("Exam Registered Successfully!\n");
}

// --- Mark Attendance (Only for Entered Course) ---
void markAttendance(struct Attendance a[], int n) {
    printf("\n---[Mark Attendance]---\n");

    if (n == 0) {
        printf("No students registered yet!\n");
        return;
    }

    char courseInput[50];
    printf("\nEnter Course Name to Mark Attendance: ");
    scanf("%s", courseInput);

    int found = 0;
    for (int i = 0; i < n; i++) {
        if (courseInput[1] == a[i].course[1]) {
            printf("%s (%s) 1=Yes, 0=No: ", a[i].name, a[i].course);
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

    char courseInput[50];
    printf("\nEnter Course Name to View Attendance: ");
    scanf("%s", courseInput);

    int found = 0;
    printf("\nAttendance Report for %s:\n", courseInput);
    for (int i = 0; i < n; i++) {
        if (courseInput[0] == a[i].course[0]) {  // Match first letter only
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

    char courseInput[50];
    printf("\nEnter Course Name : ");
    scanf("%s", courseInput);

    int found = 0;
    printf("\nStudents in %s:\n", courseInput);
    for (int i = 0; i < n; i++) {
        if (courseInput[0] == s[i].course[0]) {  // Match first letter only
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
        printf("\n1. Student\n2. Lecturer\n3. Exit\nEnter your choice:\n\n ");
        scanf("%d", &ch);

        if (ch == 1) {
            printf("\n1. Register\n2. Register for Examination\n3. View Attendance\nEnter your choice: ");
            scanf("%d", &ch);

            switch (ch)
            {
            case 1:
                registerStudent( s, a, &n);
                 break;
            case 2:
                registerExam();
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

