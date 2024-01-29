#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class tel
{
public:
    int rollNo, roll1;
    char name[10];
    char div;
    char address[20];

    void accept()
    {
        cout << "\n\tEnter Roll Number: ";
        cin >> rollNo;
        cout << "\n\tEnter the Name: ";
        cin >> name;
        cout << "\n\tEnter the Division: ";
        cin >> div;
        cout << "\n\tEnter the Address: ";
        cin >> address;
    }

    void accept2()
    {
        cout << "\n\tEnter the Roll No. to modify: ";
        cin >> rollNo;
    }

    void accept3()
    {
        cout << "\n\tEnter the name to modify: ";
        cin >> name;
    }

    int getRollNo()
    {
        return rollNo;
    }

    void show()
    {
        cout << "\n\t" << rollNo << "\t\t" << name << "\t\t" << div << "\t\t" << address;
    }
};

int main()
{
    int i, n, ch, ch1, rec, start, count, add, n1, add2, start2, n2, y, a, b, on, oname, add3, start3, n3, y1, add4, start4, n4;
    char name[20], name2[20];
    tel t1;
    count = 0;
    fstream g, f;

    do
    {
        cout << "\n>>>>>>>>>>>>>>>>>>>>>>MENU<<<<<<<<<<<<<<<<<<<<";
        cout << "\n1.Insert and overwrite\n2.Show\n3.Search & Edit(number)\n4.Search & Edit(name)\n5.Search & Edit(onlynumber)\n6.Search & edit(only name)\n 7.Delete a Student Record\n 8.Exit\n\tEnter the Choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            f.open("StuRecord.txt", ios::out);
        x:
            t1.accept();
            f.write((char *)&t1, sizeof(t1));
            cout << "\nDo you want to enter more records?\n1.Yes\n2.No";
            cin >> ch1;
            if (ch1 == 1)
                goto x;
            else
            {
                f.close();
                break;
            }

        case 2:
            f.open("StuRecord.txt", ios::in);
            f.read((char *)&t1, sizeof(t1));
            // cout<<"\n\tRoll No.\t\tName \t\t Division \t\t Address";
            while (f)
            {
                t1.show();
                f.read((char *)&t1, sizeof(t1));
            }
            f.close();
            break;

        case 3:
            cout << "\nEnter the roll number you want to find: ";
            cin >> rec;
            f.open("StuRecord.txt", ios::in | ios::out);
            f.read((char *)&t1, sizeof(t1));
            while (f)
            {
                if (rec == t1.rollNo)
                {
                    cout << "\nRecord found";
                    add = f.tellg();
                    f.seekg(0, ios::beg);
                    start = f.tellg();
                    n1 = (add - start) / sizeof(t1);
                    f.seekp((n1 - 1) * sizeof(t1), ios::beg);
                    t1.accept();
                    f.write((char *)&t1, sizeof(t1));
                    f.close();
                    count++;
                    break;
                }
                f.read((char *)&t1, sizeof(t1));
            }
            if (count == 0)
                cout << "\nRecord not found";
            f.close();
            break;

        case 4:
            cout << "\nEnter the name you want to find and edit: ";
            cin >> name;
            f.open("StuRecord.txt", ios::in | ios::out);
            f.read((char *)&t1, sizeof(t1));
            while (f)
            {
                y = (strcmp(name, t1.name));
                if (y == 0)
                {
                    cout << "\nName found";
                    add2 = f.tellg();
                    f.seekg(0, ios::beg);
                    start2 = f.tellg();
                    n2 = (add2 - start2) / sizeof(t1);
                    f.seekp((n2 - 1) * sizeof(t1), ios::beg);
                    t1.accept();
                    f.write((char *)&t1, sizeof(t1));
                    f.close();
                    break;
                }
                f.read((char *)&t1, sizeof(t1));
            }
            break;

        case 5:
            cout << "\nEnter the roll number you want to modify: ";
            cin >> on;
            f.open("StuRecord.txt", ios::in | ios::out);
            f.read((char *)&t1, sizeof(t1));
            while (f)
            {
                if (on == t1.rollNo)
                {
                    cout << "\nNumber found";
                    add3 = f.tellg();
                    f.seekg(0, ios::beg);
                    start3 = f.tellg();
                    n3 = (add3 - start3) / sizeof(t1);
                    f.seekp((n3 - 1) * (sizeof(t1)), ios::beg);
                    t1.accept2();
                    f.write((char *)&t1, sizeof(t1));
                    f.close();
                    break;
                }
                f.read((char *)&t1, sizeof(t1));
            }
            break;

        case 6:
            cout << "\nEnter the name you want to find and edit: ";
            cin >> name2;
            f.open("StuRecord.txt", ios::in | ios::out);
            f.read((char *)&t1, sizeof(t1));
            while (f)
            {
                y1 = (strcmp(name2, t1.name));
                if (y1 == 0)
                {
                    cout << "\nName found";
                    add4 = f.tellg();
                    f.seekg(0, ios::beg);
                    start4 = f.tellg();
                    n4 = (add4 - start4) / sizeof(t1);
                    f.seekp((n4 - 1) * sizeof(t1), ios::beg);
                    t1.accept3();
                    f.write((char *)&t1, sizeof(t1));
                    f.close();
                    break;
                }
                f.read((char *)&t1, sizeof(t1));
            }
            break;

        case 7:
            int roll;
            cout << "Please Enter the Roll No. of Student Whose Info You Want to Delete: ";
            cin >> roll;
            f.open("StuRecord.txt", ios::in);
            g.open("temp.txt", ios::out);
            f.read((char *)&t1, sizeof(t1));
            while (!f.eof())
            {
                if (t1.getRollNo() != roll)
                    g.write((char *)&t1, sizeof(t1));
                f.read((char *)&t1, sizeof(t1));
            }
            cout << "The record with the roll no. " << roll << " has been deleted." << endl;
            f.close();
            g.close();
            remove("StuRecord.txt");
            rename("temp.txt", "StuRecord.txt");
            break;

        case 8:
            cout << "\n\tThank you";
            break;
        }
    } while (ch != 8);

    return 0;
}
