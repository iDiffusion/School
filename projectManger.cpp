#include <iostream>
#include <fstream>
#include <stdio.h>
#include <array>
using namespace std;

#define SIZE 50
struct Project {
  string title;
  string startDate, endDate;
  string timeExpected, timeElasped;
  string complete;
  string description;
};

void addProject(Project projects[], int& size, Project p);
void printProject(Project p);
void displayProjects(Project projects[], int size);
int lookupProject(Project projects[], int& size, Project p);

int main () {
  ifstream inFile;
  string fileName;

  char choice;
  string input;

  Project projects[SIZE];
  int size = 0;

  // Prompt and save file name
  cout << "Please enter the file name: ";
  cin >> fileName;

  // Read file and input all data
  inFile.open(fileName);
   while (!inFile.eof()) {
     Project p;
     inFile.ignore(0, '\n');
     getline(inFile, p.title, ','); //get name of project
     getline(inFile, p.startDate, ',');
     getline(inFile, p.endDate, ',');
     getline(inFile, p.timeExpected, ',');
     getline(inFile, p.timeElasped, ',');
     getline(inFile, p.complete, '\n');
     getline(inFile, p.description, '\n');
     addProject(projects, size, p);
   }
  inFile.close();

    // Interact with the user to display and modify the project list
  while (1 == 1) {
    cout << endl << "Operations:" << endl
    << "'q' = quit out of the program" << endl
    << "'d' = display the projects" << endl
    << "'a' = add projects to the program" << endl
    << "'l' = lookup projects:" << endl
    << "Please enter the desired operation: ";
    cin >> choice;

    if (choice == 'q' || choice == 'Q') {
      ofstream outFile;
      outFile.open(fileName);
      for (int i = 0; i < size; i++) {
        if(i != 0) outFile << endl;
        outFile << projects[i].title << ","
        << projects[i].startDate << ","
        << projects[i].endDate << ","
        << projects[i].timeExpected << ","
        << projects[i].timeElasped << ","
        << projects[i].complete << endl
        << projects[i].description;
      }
      outFile.close();
      cout << endl << "Information has been saved to a file.";
      return 0;
    }

    else if (choice == 'd' || choice == 'D') {
      displayProjects(projects, size);
    }

    else if (choice == 'a' || choice == 'A') {
      Project p;
      cin.ignore(1000, '\n');
      cout << endl << endl << "Please enter the title of the project: ";
      getline(cin, p.title);
      cout << "Please enter the start date of the project (mm/dd/yy): ";
      getline(cin, p.startDate);
      cout << "Please enter the due date of the project (mm/dd/yy): ";
      getline(cin, p.endDate);
      cout << "Please enter the time expected to complete the project: ";
      getline(cin, p.timeExpected);
      cout << "Please enter the time taken to complete the project: ";
      getline(cin, p.timeElasped);
      cout << "Please enter whether the project was completed or not: ";
      getline(cin, p.complete);
      cout << "Please enter the project description: ";
      getline(cin, p.description);
      addProject(projects, size, p);
    }

    else if (choice == 'l' || choice == 'L') {
      while(1 == 1) {
        Project p;
        cout << endl << endl << "Operations:" << endl
        << "'b' = back to main menu" << endl
        << "'d' = to lookup by date" << endl
        << "'n' = to lookup by name" << endl
        << "Please enter the desired operation: ";
        cin >> choice;
        if(choice == 'b' || choice == 'B'){
          break;
        } else if(choice == 'd' || choice == 'D'){
          cin.ignore(1000, '\n');
          cout << "Please enter the date of the project you would like to search for (mm/dd/yy): ";
          getline(cin, p.startDate);
        } else if(choice == 'n' || choice == 'N'){
          cin.ignore(1000, '\n');
          cout << "Please enter the name of the project you would like to search for: ";
          getline(cin, p.title);
        }
        int index = lookupProject(projects, size, p);
        if(index != -1){
          while(1 == 1) {
            Project p;
            cout << endl << "Operations:" << endl
            << "'b' = back to main menu" << endl
            << "'r' = remove project" << endl
            << "'d' = to display" << endl
            << "Please enter the desired operation: ";
            cin >> choice;
            if(choice == 'b' || choice == 'B'){
              break;
            } else if(choice == 'r' || choice == 'r'){
              for(int i = index; i < size - 1; i++){
                projects[i] = projects[i + 1];
              }
              size--;
              break;
            } else if(choice == 'd' || choice == 'd'){
              printProject(projects[index]);
            }
          }
          break;
        }
        else {
          cout << endl << "File not found";
        }
      }
      cout << endl;
    }
  }
}

void printProject(Project p) {
  cout << endl << "Project Name: " << p.title << endl
  << "Date: " << p.startDate << " - " << p.endDate << endl
  << "Estimated time: " << p.timeExpected
  << "\tExpended Time: " << p.timeElasped << endl
  << p.complete << endl
  << "Description: " << p.description << endl;
}

void displayProjects(Project projects[], int size){
  if(size == 0){
    cout<< endl << "There is currently no projects scheduled.";
  }
 for(int i = 0; i< size; i++) {
    printProject(projects[i]);
  }
}

void addProject(Project projects[], int& size, Project p){
   if(size < SIZE) projects[size++] = p;
}

int lookupProject(Project projects[], int& size, Project p){
  for(int i = 0; i < size; i++){
    if(!p.title.empty() && p.title == projects[i].title){
      return i;
    }
    else if(!p.startDate.empty() && p.startDate == projects[i].startDate){
      return i;
    }
    return -1;
  }
}
