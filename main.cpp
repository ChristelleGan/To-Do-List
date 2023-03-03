#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

struct Task {
    string name;
    int dueDay, dueMonth, dueYear;
    bool isCompleted = false;
    int priority;
};

int getData(Task arrData[]);
void viewTasks(Task arrData2[],int);
int addTasks(Task addtasks[], int , int);
void completeTask(Task completetask[],int );
int removeTask(Task removetask[], int, int);
void sortTasks(Task sorttasks[], int);
void modifyTasks(Task modifytasks[], int, int);
void taskSummary(Task tasksummary[], int);

int main(){
    cout << fixed << setprecision(2) << endl;
    int size = 50;
    int num_of_tasks = 0;
    int action = 0;
    int chosen_index = 0;
    bool isContinue = true;
    Task tasks[size];
    
    num_of_tasks = getData(tasks);
    
    while(isContinue) {
        cout << "1 - add tasks" << endl;
        cout << "2 - mark task as completed" << endl;
        cout << "3 - remove a task " << endl;
        cout << "4 - display tasks " << endl;
        cout << "5 - sort tasks by due date " << endl;
        cout << "6 - modify tasks" << endl;
        cout << "7 - display task summary" << endl;
        cout << "What whould you like to do next? Enter a number to decide your action." << endl;
        cin >> action;
        cout << endl;
        
        switch (action){
            case 1:
                num_of_tasks = addTasks(tasks, num_of_tasks, size);
                cout << endl;
                break;
            case 2:
                completeTask(tasks,2);
                cout << endl;
                break;
            case 3:
                num_of_tasks = removeTask(tasks, chosen_index, num_of_tasks);
                cout << endl;
                break;
            case 4:
                viewTasks(tasks, num_of_tasks);
                cout << endl;
                break;
            case 5:
                sortTasks(tasks, num_of_tasks);
                cout << endl;
                break;
            case 6:
                modifyTasks(tasks, chosen_index, size);
                cout << endl;
                break;
            case 7:
                taskSummary(tasks, num_of_tasks);
                cout << endl;
                break;
            default:
                isContinue = false;
                exit(1);
        }
    }
    return 0;
}

int getData(Task arrData[]){
    ifstream infile;
    infile.open("/Users/christellegan/Documents/CSI/CSC211/Lab 5/tasks.txt");
    if(!infile){
        cout <<"File was not opened" << endl;
        exit(1);
    }
    int count = 0;
    while(!infile.eof()){
        infile >> arrData[count].name;
        infile >> arrData[count].dueMonth;
        infile >> arrData[count].dueDay;
        infile >> arrData[count].dueYear;
        infile >> arrData[count].priority;
        count++;
    }
    return count;
}

void viewTasks(Task arrData2[], int size){
    string result;
    
    cout << left << setw(40) << "Name of the task" << setw(24) << "Due date(mm dd yyyy)" << setw(13) << "Priority"
    << setw(20) << "Status(1-completedd, 0-open)" << endl ;
    cout << "_______________________________________________________________________________________________________" << endl;
    for (int j = 0; j < size; j++) {
        cout << j << ": " << left << setw(40) << arrData2[j].name << setw(3) << arrData2[j].dueMonth << setw(3) << arrData2[j].dueDay << setw(20) << arrData2[j].dueYear << setw(10) << arrData2[j].priority << setw(10) << arrData2[j].isCompleted << endl;
        
        if (arrData2[j].isCompleted){
            result = "completed";
        } else {
            result = "not completed";
        }
        cout << "status: " << result << endl;
    }
    
}

int addTasks(Task addtasks[], int totalTasks, int maxSize){
    int action = 0;
    do {
        if(totalTasks >= maxSize){
            cout << "No more space." << endl;
            return totalTasks;
        }
        cout << "Please enter your task's name: ";
        cin >> addtasks[totalTasks].name;
        cout << "Please enter your task's due date (month / day / year)";
        cin >> addtasks[totalTasks].dueMonth >> addtasks[totalTasks].dueDay >> addtasks[totalTasks].dueYear;
        cout << "Please enter your task's priority (1-high, 2-medium, 3-low)";
        cin >> addtasks[totalTasks].priority;
        cout << "Please enter the status of the task (1-completed, 0-open)" << endl;
        cin >> addtasks[totalTasks].isCompleted;
        
        totalTasks++;
        cout << "Do you want to add another task? (0-no, 1-yes)" << endl;
        cin >> action;
    } while (action == 1);
    return totalTasks;
}

void completeTask(Task completetask[],int chosen_index){
    cout << "Please choose the index of the task which you completed" << endl;
    cin >> chosen_index;
    completetask[chosen_index].isCompleted = true;
}

int removeTask(Task removetask[], int chosen_index, int totalTasks){
    cout << "Please choose the index of the task which you want to remove" << endl;
    cin >> chosen_index;
    
    if(chosen_index >= totalTasks){
        cout << "Error..." << endl;
    }
    while(chosen_index < totalTasks){
        removetask[chosen_index].name = removetask[chosen_index + 1].name;
        removetask[chosen_index].dueMonth = removetask[chosen_index + 1].dueMonth;
        removetask[chosen_index].dueDay = removetask[chosen_index + 1].dueDay;
        removetask[chosen_index].dueYear = removetask[chosen_index + 1].dueYear;
        removetask[chosen_index].priority = removetask[chosen_index + 1].priority;
        removetask[chosen_index].isCompleted = removetask[chosen_index + 1].isCompleted;
    
        chosen_index++ ;
    }
    return totalTasks - 1;
}

void sortTasks(Task sorttasks[], int size){
    int min;
    Task temp;
    for (int i = 0; i < size - 1; i++){
        min = i;
        for (int j = i + 1; j < size; j ++){
            if (sorttasks[j].dueYear < sorttasks[min].dueYear) {
                min = j;
            } else if (sorttasks[j].dueYear == sorttasks[min].dueYear && sorttasks[j].dueMonth < sorttasks[min].dueMonth) {
                min = j;
            } else if (sorttasks[j].dueYear == sorttasks[min].dueYear && sorttasks[j].dueMonth == sorttasks[min].dueMonth && sorttasks[j].dueDay < sorttasks[min].dueDay) {
                min = j;
            }
        }
        temp = sorttasks[min];
        sorttasks[min] = sorttasks[i];
        sorttasks[i] = temp;
    }
}

void modifyTasks(Task modifytasks[], int chosen_index, int size){
    string name;
    int dueDay, dueMonth, dueYear;
    bool isCompleted = false;
    int priority;
    
    cout << "Please choose the index of the task which you want to modify" << endl;
    cin >> chosen_index;
    
    if(chosen_index >= size){
        cout << "No more space." << endl;
    }
    cout << "Please enter your task's name: ";
    cin >> name;
    cout << "Please enter your task's due date (month / day / year)";
    cin >> dueMonth >> dueDay >> dueYear;
    cout << "Please enter your task's priority (1-high, 2-medium, 3-low)";
    cin >> priority;
    cout << "Please enter the status of the task (1-completed, 0-open)" << endl;
    cin >> isCompleted;
    
    modifytasks[chosen_index].name = name;
    modifytasks[chosen_index].dueMonth = dueMonth;
    modifytasks[chosen_index].dueDay = dueDay;
    modifytasks[chosen_index].dueYear = dueYear;
    modifytasks[chosen_index].priority = priority;
    modifytasks[chosen_index].isCompleted = isCompleted;
   
}

void taskSummary(Task tasksummary[], int total_tasks){
    double num_of_completed = 0;
    double percentage = 0.00;
    for(int i = 0; i < total_tasks; i++){
        if(tasksummary[i].isCompleted == 1){
            num_of_completed ++;
        }
    }
    percentage = num_of_completed / total_tasks;
    cout << "Summary of Johnny's To-Do List" << endl;
    cout << "Total number of tasks\t\t" << total_tasks << endl;
    cout << "Percentage completed\t\t" << (percentage * 100) << "%" << endl;
}
