#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>
#include <ctime>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

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
    ifstream file(name);
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
    } else {
        print("Error cannot open file!");
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
    void shutdown() {
        run = false;
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
        cin >> filename;
        write_file(filename);
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
// File system class
class MoonFS {
private:
    fs::path current_dir;
public:
    MoonFS() {
        current_dir = fs::current_path();
    }
    string cur_dir() {
        return current_dir.string();
    }
    void ls() {
        for (const auto& entry : fs::directory_iterator(current_dir)) {
            if(entry.is_directory()) {
                cout << "[DIR] " << entry.path().filename().string() << endl;
            } else {
                cout << "[FILE] " << entry.path().filename().string() << endl;
            }
        }
    }
    void cd(string path) {
        fs::path new_path = current_dir / path;
        if(fs::exists(new_path) && fs::is_directory(new_path)) {
            current_dir = fs::canonical(new_path);
        } else {
            print("Directory not found!");
        }
    }
    void touch(string name) {
        fs::path file_path = current_dir / name;
        ofstream file(file_path);

        if (file.is_open()) {
            print("File created successfully!");
            file.close();
        }
        else {
            print("Error: file wasn't created!");
        }
    }
    void cat(string name) {
        read_file(name);
    }
    void mkdir(string name) {
        try {
            fs::path new_path = current_dir / name;

            if (fs::create_directory(new_path)) {
                print("Directory created!");
            }
            else {
                print("Directory already exists or cannot be created!");
            }
        }
        catch (const fs::filesystem_error& e) {
            cout << "Filesystem error: " << e.what() << endl;
        }
    }
    void rmdir(string name) {
        fs::path dir_path = current_dir / name;
        if (fs::exists(dir_path) && fs::is_directory(dir_path)) {
            if (fs::remove_all(dir_path)) {
                print("Directory deleted!");
            }
            else {
                print("Directory is not empty!");
            }
        }
        else {
            print("Directory not found!");
        }
    }
    void rm(string name) {
        fs::path file_path = current_dir / name;
        if (fs::exists(file_path) && fs::is_regular_file(file_path)) {
            fs::remove(file_path);
            print("File deleted!");
        }
        else {
            print("File not found!");
        }
    }
};
// OS
int main() {
    PC pc;
    MoonApps moonapps;
    MoonFS moonfs;
    // boot();
    print("MoonOS v0.1");
    print("By K4satka");
    pc.show_info();
    print("Type `help` for list of commands");
    while(pc.isRunning()) {
        string cmd;
        cout << moonfs.cur_dir() << "@MoonOS>>>";
        cin >> cmd;
        if (cmd == "help") {
            print("List of commands:");
            print("help - list of commands");
            print("systeminfo - shows system info");
            print("exit - powers off Moon OS");
            print("calc - calculator");
            print("notepad - writes data in files");
            print("clock - displays local time");
            print("calendar - displays date");
            print("ls - lists all files and directories in the current directory");
            print("cd - moves current directory to the path");
            print("pwd - shows current directory");
            print("touch - creates file");
            print("rm - removes file");
            print("cat - reads the text in file");
            print("mkdir - creates directory");
            print("rmdir - removes directory");
        }
        else if(cmd == "systeminfo") {
            print("-------------");
            print("   MOON OS   ");
            print("     v0.1    ");
            print("-------------");
            pc.show_info();
        }
        else if(cmd == "exit") {
            print("Turning off Moon OS...");
            wait(2);
            pc.shutdown();
        }
        else if(cmd == "calc") {
            moonapps.execute("calc");
        }
        else if(cmd == "notepad") {
            moonapps.execute("notepad");
        }
        else if(cmd == "clock") {
            time_t t1 = time(NULL);
            tm t = *localtime(&t1);
            printf("%.2d:%.2d:%.2d\n", t.tm_hour, t.tm_min, t.tm_sec);
        }
        else if(cmd == "calendar") {
            auto now = chrono::system_clock::now();
            time_t now_c = chrono::system_clock::to_time_t(now);
            tm* now_tm = localtime(&now_c);
            cout << (now_tm->tm_year + 1900) << '-' 
                    << (now_tm->tm_mon + 1) << '-'
                    <<  now_tm->tm_mday << '\n';
        }
        else if(cmd == "ls") {
            moonfs.ls();
        }
        else if(cmd == "cd") {
            string path;
            cin >> path;
            moonfs.cd(path);
        }
        else if(cmd == "pwd") {
            print(moonfs.cur_dir());
        }
        else if(cmd == "touch") {
            string name;
            cin >> name;
            moonfs.touch(name);
        }
        else if(cmd == "rm") {
            string name;
            cin >> name;
            moonfs.rm(name);
        }
        else if(cmd == "cat") {
            string name;
            cin >> name;
            moonfs.cat(name);
        }
        else if(cmd == "mkdir") {
            string name;
            cin >> name;
            moonfs.mkdir(name);
        }
        else if(cmd == "rmdir") {
            string name;
            cin >> name;
            moonfs.rmdir(name);
        }
        else {
            cout << "Unknown command: " << cmd << ". Type `help` for list of commands" << endl;
        }
    }
    return 0;
}
