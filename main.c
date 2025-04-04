#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct FacultyProfile {
    char fullName[100];
    int publications;
    int conferences;
    int subjectsTaught;
    float feedbackRating;
    float overallScore;
    char grade[30];
};
void calculateScore(struct FacultyProfile *fp) {

    fp->overallScore = (fp->publications * 2.0) +
                       (fp->conferences * 1.5) +
                       (fp->subjectsTaught * 1.2) +
                       (fp->feedbackRating * 5.0);
    if (fp->overallScore >= 80)
        strcpy(fp->grade, "Outstanding Contribution");
    else if (fp->overallScore >= 60)
        strcpy(fp->grade, "Excellent Performance");
    else if (fp->overallScore >= 40)
        strcpy(fp->grade, "Satisfactory");
    else
        strcpy(fp->grade, "Needs Improvement");
}
void saveProfile(struct FacultyProfile fp) {
    FILE *fptr = fopen("faculty_progress_log.txt", "a");
    if (fptr == NULL) {
        printf("❌ Unable to open file for saving details.\n");
        return;
    }
    fprintf(fptr, "%s,%d,%d,%d,%.2f,%.2f,%s\n", fp.fullName,
            fp.publications, fp.conferences, fp.subjectsTaught,
            fp.feedbackRating, fp.overallScore, fp.grade);
    fclose(fptr);

    printf("✅ Faculty profile successfully saved.\n");
}

void showAllProfiles() {
    FILE *fptr = fopen("faculty_progress_log.txt", "r");
    if (fptr == NULL) {
        printf("📂 No past records found.\n");
        return;
    }

    printf("\n📊 Faculty Performance Summary:\n");
    printf("------------------------------------------------------\n");
    printf("Name\t\t\tScore\t\tStatus\n");
    printf("------------------------------------------------------\n");

    char name[100], status[50];
    int pub, conf, teach;
    float feedback, total;

    while (fscanf(fptr, "%99[^,],%d,%d,%d,%f,%f,%49[^\n]\n", name, &pub, &conf, &teach, &feedback, &total, status) == 7) {
        printf("%-20s\t%.2f\t%s\n", name, total, status);
    }

    fclose(fptr);
}

int main() {
    struct FacultyProfile prof;
    int option;

    printf("🎓 Welcome to Faculty Progress Tracker System\n");

    do {
        printf("\n========= MENU =========\n");
        printf("1. Add New Faculty Data\n");
        printf("2. View All Records\n");
        printf("3. Exit the System\n");
        printf("Select an option: ");
        scanf("%d", &option);
        getchar(); 
        switch (option) {
            case 1:
                printf("Enter Full Name of Faculty: ");
                fgets(prof.fullName, sizeof(prof.fullName), stdin);
                prof.fullName[strcspn(prof.fullName, "\n")] = '\0'; 

                printf("Number of Research Publications: ");
                scanf("%d", &prof.publications);

                printf("Conferences Attended: ");
                scanf("%d", &prof.conferences);

                printf("Courses/Subjects Taught: ");
                scanf("%d", &prof.subjectsTaught);

                printf("Average Feedback Score (0.0 to 10.0): ");
                scanf("%f", &prof.feedbackRating);

                calculateScore(&prof);

                printf("\n🔍 Performance Overview:\n");
                printf("Final Score: %.2f\n", prof.overallScore);
                printf("Remark: %s\n", prof.grade);

                saveProfile(prof);
                break;

            case 2:
                showAllProfiles();
                break;

            case 3:
                printf("\n👋 Thank you! Exiting system.\n");
                break;

            default:
                printf("⚠️ Invalid selection. Please choose between 1 to 3.\n");
        }

    } while (option != 3);

    return 0;
}