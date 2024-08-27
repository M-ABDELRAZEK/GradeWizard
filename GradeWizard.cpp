#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <unordered_map>
#include <limits>

using namespace std;

class Courses
{
public:
    string CourseName;
    int CourseCredits;
    string CourseGradeSymbol;
    float CourseGrade;

    Courses() {}

    Courses(string &name, int credits, string &Symbol, float grade)
    {
        CourseName = name;
        CourseCredits = credits;
        CourseGradeSymbol = Symbol;
        CourseGrade = grade;
    }
};

class GPA
{
public:
    virtual void input() = 0;
    virtual void calculate() = 0;
    virtual void display() = 0;
};

class SGPA : public GPA, public Courses
{
private:
    vector<Courses> courses;
    float GPA;

public:
    SGPA() {}
    int TotalCredits = 0;

    void input() override
    {
        int CoursesNum = 0;
        cout << "Enter The Number of Courses In This Semester: ";

        while (!(cin >> CoursesNum) || CoursesNum < 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Input. Enter a positive integer for number of courses: ";
        }

        unordered_map<string, float> Grades_Map = {
            {"A+", 4.00},
            {"A", 4.00},
            {"A-", 3.70},
            {"B+", 3.30},
            {"B", 3.00},
            {"B-", 2.70},
            {"C+", 2.30},
            {"C", 2.00},
            {"C-", 1.70},
            {"D+", 1.30},
            {"D", 1.00},
            {"F", 0},
        };

        for (int i = 0; i < CoursesNum; i++)
        {
            cout << "Enter The Name of The Course " << i + 1 << ": ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, CourseName);
            cout << "Enter The credits of The Course " << i + 1 << ": ";

            while (!(cin >> CourseCredits) || CourseCredits < 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid Input. Enter a positive integer for course credits: ";
            }
            cout << "Enter The grade of The Course " << i + 1 << " (A+, A, A-, B+, B, B-, C+, C, C-, D+, D, F): ";

            while (true)
            {
                cin >> CourseGradeSymbol;
                if (Grades_Map.find(CourseGradeSymbol) != Grades_Map.end())
                {
                    courses.emplace_back(CourseName, CourseCredits, CourseGradeSymbol, Grades_Map[CourseGradeSymbol]);
                    break;
                }
                else
                {
                    cout << "Invalid grade symbol. Please enter a valid grade (A+, A, A-, B+, B, B-, C+, C, C-, D+, D, F): ";
                }
            }
        }
    }

    void calculate() override
    {
        float TotalPoints = 0;

        for (auto &course : courses)
        {
            TotalPoints += course.CourseCredits * course.CourseGrade;
            TotalCredits += course.CourseCredits;
        }
        if (TotalCredits > 0)
        {
            GPA = TotalPoints / TotalCredits;
        }
        else
        {
            GPA = 0;
            cout << "Error: Cannot Calculate GPA." << endl;
        }
    }

    void display() override
    {
        cout << "Semester GPA: " << fixed << setprecision(2) << GPA << endl;
    }

    int GetTotalCredits()
    {
        return TotalCredits;
    }

    float GetGPA()
    {
        return GPA;
    }
};

class CGPA : public GPA, public Courses
{
private:
    float CurrentCGPA;
    float SemesterGPA;
    float NewCGPA;
    int CurrentCredits;
    int SemesterCredits;

public:
    void input() override
    {
        cout << "Enter Your Current CGPA: ";

        while (!(cin >> CurrentCGPA) || CurrentCGPA > 4 || CurrentCGPA < 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Input. Enter a CGPA between 0.0 and 4.0: ";
        }
        cout << "Enter Your Current Credits: ";

        while (!(cin >> CurrentCredits) || CurrentCredits <= 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Input. Enter a positive integer for the current credits: ";
        }
        SGPA Semester;
        Semester.input();
        Semester.calculate();
        SemesterGPA = Semester.GetGPA();
        SemesterCredits = Semester.GetTotalCredits();
    }

    void calculate() override
    {
        float TotalCurrentPoints = CurrentCGPA * CurrentCredits;
        float TotalSemesterPoints = SemesterGPA * SemesterCredits;
        float TotalPoints = TotalSemesterPoints + TotalCurrentPoints;
        int TotalCredits = SemesterCredits + CurrentCredits;
        if (TotalCredits > 0)
        {
            NewCGPA = TotalPoints / TotalCredits;
        }
        else
        {
            NewCGPA = 0;
            cout << "Error: Total credits are zero. Cannot calculate CGPA." << endl;
        }
    }

    void display() override
    {
        cout << "Cumulative GPA: " << fixed << setprecision(2) << NewCGPA << endl;
    }
};

class targetGPA : public GPA
{
private:
    float CurrentCGPA;
    int CurrentCredits;
    float TargetCGPA;
    int AdditionalCredits;
    float RequiredGPA;

public:
    void input() override
    {
        cout << "Enter Your Current CGPA: ";

        while (!(cin >> CurrentCGPA) || CurrentCGPA > 4 || CurrentCGPA < 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Input. Enter a CGPA between 0.0 and 4.0: ";
        }
        cout << "Enter Your Current Credits: ";

        while (!(cin >> CurrentCredits) || CurrentCredits <= 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Input. Enter a positive integer for the current credits: ";
        }
        cout << "Enter Your Target CGPA: ";

        while (!(cin >> TargetCGPA) || TargetCGPA > 4 || TargetCGPA < 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a target CGPA between 0.0 and 4.0: ";
        }
        cout << "Enter Your Additional Credits: ";

        while (!(cin >> AdditionalCredits) || AdditionalCredits <= 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a positive integer for the additional credits: ";
        }
    }

    void calculate() override
    {
        float TotalCredits = CurrentCredits + AdditionalCredits;
        float CurrentPoints = CurrentCredits * CurrentCGPA;
        float TargetPoints = TargetCGPA * TotalCredits;
        if (AdditionalCredits > 0)
        {
            RequiredGPA = (TargetPoints - CurrentPoints) / AdditionalCredits;
        }
        else
        {
            RequiredGPA = 0;
            cout << "Error: Additional credits are zero. Cannot calculate the required GPA." << endl;
        }
    }

    void display() override
    {
        cout << "Required GPA For The Next Semester To Achieve Target GPA: " << RequiredGPA;
    }
};

int main()
{
    char Choose;
    GPA *Calculator;
    cout << "Calculate (S)emester GPA or (C)umulative GPA or (T)arget GPA? ";
    cin >> Choose;
    switch (Choose)
    {
    case 'S':
    case 's':
        Calculator = new SGPA;
        break;

    case 'c':
    case 'C':
        Calculator = new CGPA;
        break;

    case 'T':
    case 't':
        Calculator = new targetGPA;
        break;

    default:
        cout << "Invalid Choise" << endl;
        return 1;
    }

    Calculator->input();
    Calculator->calculate();
    Calculator->display();

    return 0;
}