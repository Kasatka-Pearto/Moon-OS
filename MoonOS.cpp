#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>

using namespace std;

// OS operations
void wait(int sec) {
    this_thread::sleep_for(std::chrono::seconds(sec));
}
void print(string text) {
    cout << text << endl;
}
void print(int text) {
    cout << text << endl;
}
void read_file(string name) {
    ifstream file(name, ios_base::out);
    if(file.is_open()) {
        cout << file.rdbuf();
        file.close();
    } else {
        print("No such file in current directory!");
    }
}
void write_file(string name) {
    ofstream file(name, ios_base::out);
    if(file.is_open()) {
        string text;
        string line;
        print("Succesfully opened/created file!");
        while(true) {
            getline(cin, line);
            if(line == "/save") {
                break;
            }
            text += line + "\n";
        }
        file << text;
        file.close();
    }
}

// OS functions
void boot() { // Booting up OS
    print("Starting Moon OS...");
    wait(3);
    print("Loading...");
    wait(5);
}

// PC class
class PC {
private:
    string ram1;
    string rom1;
    bool run;
public:
    PC() {
        ram1 = "128mb";
        rom1 = "512mb";
        run = true;
    }
    void show_info() {
        cout << "RAM1: " << ram1 << endl;
        cout << "ROM1: " << rom1 << endl;
    }
    void runsys() {
        run = !run;
    }
    string get_ram() { return ram1; }
    string get_rom() { return rom1; }
    bool isRunning() { return run; }
};
// Apps class
class MoonApps {
private:
    // Calculator
    void calc_app() { 
        float num1, num2;
        char action;
        cout << "Number 1: ";
        cin >> num1;
        cout << "Number 2: ";
        cin >> num2;
        cout << "Action: ";
        cin >> action;
        switch(action) {
            case '+':
                cout << num1 << "+" << num2 << "=" << num1+num2 << endl;
                break;
            case '-':
                cout << num1 << "-" << num2 << "=" << num1-num2 << endl;
                break;
            case '*':
                cout << num1 << "*" << num2 << "=" << num1*num2 << endl;
                break;
            case '/': 
                if(num2 == 0) {
                    cout << "Error dividing by zero!" << endl;
                } else {
                    cout << num1 << "/" << num2 << "=" << num1/num2 << endl;
                }
                break;
        }
    }
    // Notepad
    void notepad_app() {
        string filename;
        char act;
        cout << "Enter filename>>>";
        cin >> filename;
        cout << "Action(r/w)>>>";
        cin >> act;
        switch(act) {
            case 'r': read_file(filename); break;
            case 'w': write_file(filename); break;
        }
    }
public:
    void execute(string name) {
        if (name == "calc") {
            calc_app();
        }
        else if (name == "notepad") {
            notepad_app();
        }
    }
};

// OS
int main() {
    PC pc;
    MoonApps moonapps;
    boot();
    print("MoonOS v0.1");
    print("By K4satka");
    pc.show_info();
    print("Type `help` for list of commands");
    while(pc.isRunning()) {
        string cmd;
        cout << "MoonOS>>>";
        cin >> cmd;
        if (cmd == "help") {
            print("List of commands:");
            print("help - list of commands");
            print("systeminfo - shows system info");
            print("exit - powers off Moon OS");
            print("calc - calculator");
            print("notepad - reads/writes data in files");
        }
        else if(cmd == "systeminfo") {
            print("---Moon OS---");
            print("Version: 0.1");
            pc.show_info();
        }
        else if(cmd == "exit") {
            print("Turning off Moon OS...");
            wait(2);
            pc.runsys();
        }
        else if(cmd == "calc") {
            moonapps.execute("calc");
        }
        else if(cmd == "notepad") {
            moonapps.execute("notepad");
        }
        else {
            cout << "Unknown command: " << cmd << ". Type `help` for list of commands" << endl;
        }
    }
    return 0;
}
