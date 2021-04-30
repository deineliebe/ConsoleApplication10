//Sorry for english comments, I didn't want to find that thing with russian localisation. Hope, all is understandable

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <chrono>

//Additional structure for node: I saw examples where it was realised in class, but I think this is more comfortable for me now
struct Node 
{
    //Our data
    int number;
    //Pointer on next element
    Node* next;
    //Pointer on next element
    Node* prev;
};

class two_linked_list
{
public:
    //Empty container: head and tail are NULL
    two_linked_list()
    {
        _head = _tail = NULL;
        _size = 0;
    }

    void add_tail(int number);
    void delete_by_index(int index);
    void delete_by_value(int number);
    void get_by_index(int index);
    void get_by_value(int value);
    void show_list();
    int get_size()
    {
        return _size;
    }
    void empty_list()
    {
        _head = _tail = NULL;
        _size = 0; 
    }

private:
    //Head - 1st element of structure
    Node* _head;
    //Tail - last element of structure
    Node* _tail;
    int _size;
};

//Function of adding last element to structure
void two_linked_list::add_tail(int number)
{
    //Make new node to link it with others
    Node* temp = new Node;
    //Adding data
    temp->number = number;
    //Checking was first element (head) in structure or not
    if (!_head) {
        temp->next = _tail;
        //If not, making our new node head
        _head = temp;
        //Previous element of first element is NULL cause there is nothing before head
        temp->prev = NULL;
    }
    else {
        //If is, add in our next element tail's next: if all is correct it is NULL
        temp->next = _tail->next;
        //Tail becomes previous element
        temp->prev = _tail;
        //Make new node tail's next element
        _tail->next = temp;
    }
    //Making new node a tail
    _tail = temp;
    _size++;
}

void two_linked_list::delete_by_index(int index)
{
    //Make pointer on head - start of structure
    Node* temp = _head;
    for (int i = 0; i < index; i++) temp = temp->next;
    if (temp->next != NULL)
    {
        temp->next->prev = temp->prev;
        temp->prev->next = temp->next;
    }
    else
    {
        temp->prev->next = temp->next;
        _tail = temp->prev;
    }
    _size--;
}

void two_linked_list::delete_by_value(int number)
{
    Node* temp = _head;
    while (temp->number == number)
    {
        _head = temp->next;
        temp = _head;
        _size--;
    }
    if (temp)
    {
        while (temp->next != NULL)
        {
            if (temp->number == number)
            {
                temp->next->prev = temp->prev;
                temp->prev->next = temp->next;
                _size--;
            }
            temp = temp->next;
        }
    }
    if (temp->number == number)
    {
        temp->prev->next = temp->next;
        _tail = temp->prev;
        _size--;
    }
}

void two_linked_list::get_by_index(int index)
{
    Node* temp = _head;
    for (int i = 0; i < index; i++) temp = temp->next;
    std::cout << "Element with index " << index + 1 << " is " << temp->number << '\n';
}

void two_linked_list::get_by_value(int value)
{
    Node* temp = _head;
    std::cout << "Index/Indexes of element " << value << ": ";
    for (int i = 0; i < _size; i++)
    {
        if (temp->number == value)
        {
            std::cout << i + 1 << ' ';
        }
        temp = temp->next;
    }
    std::cout << '\n';
}

void two_linked_list::show_list()
{
    Node* temp = _head;
    std::cout << '\n';
    for (int i = 0; i < _size; i++)
    {
        std::cout << i + 1 << ". " << temp->number << '\n';
        temp = temp->next;
    }
}

void da_add_element(int*& dynamic_array, int len_arr, int number)
{
    int* rez_array = new int[len_arr + 1];
    for (int i = 0; i < len_arr; i++)
    {
        rez_array[i] = dynamic_array[i];
    }
    dynamic_array = new int[len_arr + 1];
    delete[] dynamic_array;
    rez_array[len_arr++] = number;
    dynamic_array = rez_array;
}

void da_delete_element_by_index(int*& dynamic_array, int len_arr, int index)
{
    int* rez_array = new int[len_arr - 1];
    for (int i = 0; i < index; i++)
    {
        rez_array[i] = dynamic_array[i];
    }
    for (int i = index + 1; i < len_arr; i++)
    {
        rez_array[i - 1] = dynamic_array[i];
    }
    delete[] dynamic_array;
    dynamic_array = rez_array;
}

void da_delete_element_by_value(int*& dynamic_array, unsigned int &len_arr, int number)
{
    int new_length = 0;
    for (int i = 0; i < len_arr; i++)
    {
        if (dynamic_array[i] != number) new_length++;
    }
    int* rez_array = new int[new_length];
    int j = 0;
    for (int i = 0; i < len_arr; i++)
    {
        if (dynamic_array[i] != number)
        {
            rez_array[j] = dynamic_array[i];
            j++;
        }
    }
    len_arr = new_length;
    dynamic_array = new int[new_length];
    delete[] dynamic_array;
    dynamic_array = rez_array;
}

int da_get_element_by_index(int*& dynamic_array, int index)
{
    return dynamic_array[index];
}

void da_get_element_by_value(int*& dynamic_array, int len_arr, int number)
{
    std::cout << "Index/Indexes of element " << number << ": ";
    for (int i = 0; i < len_arr; i++)
    {
        if (dynamic_array[i] == number)
        {
            std::cout << i + 1 << ' ';
        }
    }
    std::cout <<  '\n';
}

void da_show(int* dynamic_array, int len_arr)
{
    std::cout << '\n';
    for (int i = 0; i < len_arr; i++)
    {
        std::cout << i + 1 << ". " << dynamic_array[i] << '\n';
    }
}


int main()
{
    unsigned int task_number, method_of_filling;
    //Variable for check: if array was filled at least once, its value is 1, else 0
    bool if_array = 0;
    //Variable for check: if two-linked list was filled at least once, its value is 1, else 0
    bool if_list = 0;
    //Variable for check: if user wants to continue work with element of cycle, he writes 1, else - 0
    bool if_continue = 1;
    //Adding a dynamic array
    int* dynamic_array = new int[1];
    int temp;
    unsigned size = 0;
    unsigned int len_arr = 0;
    unsigned int method_of_delete, method_of_get;
    two_linked_list list;
    //Structure try-throw-catch is used to notice user about where is his mistake and what need to avoid it
    try
    {
        std::ifstream fin("elements.txt");
        if (!fin.is_open()) throw "Check file: elements.txt must exist";
        std::cout << "Task numbers: \n";
        std::cout << "1. Form new dynamic array\n";
        std::cout << "2. Add new element of dynamic array\n";
        std::cout << "3. Delete element of dynamic array\n";
        std::cout << "4. Get element of dynamic array\n";
        std::cout << "5. Form new two-linked list\n";
        std::cout << "6. Add new element of two-linked list\n";
        std::cout << "7. Delete element of two-linked list\n";
        std::cout << "8. Get element of two-linked list\n";
        //I added functions of showing structures cause it's good in testing
        std::cout << "9. Show array\n";
        std::cout << "10. Show two-linked list\n";
        std::cout << "0. Exit\n";
        std::cout << "Write number of task: ";
        std::cin >> task_number;
        if (!std::cin) throw "Wrong task number (it must be an unsigned integer)";
        while (task_number)
        {
            switch (task_number)
            {
            case(1):
            {
                len_arr = 0;
                if_continue = 1;
                std::cout << "There are three methods of filling:\n";
                std::cout << "1. Filling by random numbers\n";
                std::cout << "2. Filling by console\n";
                std::cout << "3. Filling by file\n";
                std::cout << "Write number of method: ";
                std::cin >> method_of_filling;
                if (!std::cin) throw "Wrong method of filling (it must be an unsigned integer)";
                auto t_start = std::chrono::high_resolution_clock::now();
                switch (method_of_filling)
                {
                case(1):
                {
                    std::cout << "Write length of array:\n";
                    std::cin >> len_arr;
                    if (!std::cin) throw "Wrong length of array (it must be an unsigned integer)";
                    auto t_start = std::chrono::high_resolution_clock::now();
                    dynamic_array = new int[len_arr];
                    for (int i = 0; i < len_arr; i++)
                    {
                        dynamic_array[i] = (rand() % 100);
                        if (dynamic_array[i] < 0) dynamic_array[i] *= (-1);
                    }
                    auto t_end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration< double > t_cnt = t_end - t_start;
                    std::cout << "\nOn adding array spent " << std::fixed << t_cnt.count() << "s.\n";
                    if_array = 1;
                    break;
                }
                case(2):
                {
                    std::chrono::duration< double > t_cnt = std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now();
                    while (if_continue)
                    {
                         std::cout << "Write value: ";
                         std::cin >> temp;
                         if (!std::cin) throw ("Invalid value of array's element");
                         auto t_start = std::chrono::high_resolution_clock::now();
                         da_add_element(dynamic_array, len_arr, temp);
                         auto t_end = std::chrono::high_resolution_clock::now();
                         t_cnt += t_end - t_start;
                         len_arr++;
                         //Sorry of this. I really don't understand how to do programm inputing numbers until user wants to stop except of that
                         //I know I could use a "key number", but what if I say "You must write number -88567 to stop" and user'll be like
                         //"-88567?? It's my favourite number, I dissapointed until death", so I decided to use something which asking user every time
                         //It's also has a good point in that person don't need to remember number, but I'll be glad if u say a better decision
                         std::cout << "If you want to continue write 1, else write 0: ";
                         std::cin >> if_continue;
                         if (!std::cin) throw ("You must write 0 or 1");
                    }
                    std::cout << "\nOn adding array spent " << std::fixed << t_cnt.count() << "s.\n";
                    if_array = 1;
                    break;
                }
                case(3):
                {
                    //In this cycle last element added twice
                    auto t_start = std::chrono::high_resolution_clock::now();
                    while (fin)
                    {
                        fin >> temp;
                        da_add_element(dynamic_array, len_arr, temp);
                        len_arr++;
                    }
                    auto t_end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration< double > t_cnt = t_end - t_start;
                    std::cout << "\nOn adding array spent " << std::fixed << t_cnt.count() << "s.\n";
                    len_arr--;
                    //I don't found a way to avoid it, so delete this element
                    da_delete_element_by_index(dynamic_array, len_arr, len_arr);
                    if_array = 1;
                    break;
                }
                default:
                {
                    std::cout << "There isn't operation with number " << method_of_filling << '\n';
                }
                }
                //After all automatically starts function of showing array
                da_show(dynamic_array, len_arr);
                break;
            }
            case(2):
            {
                //Checking if array filled
                if (if_array and len_arr != 0)
                {
                    //Function same with 2nd case of filling array, but easier
                    std::cout << "Write value: ";
                    std::cin >> temp;
                    if (!std::cin) throw ("Invalid value of array's element");
                    auto t_start = std::chrono::high_resolution_clock::now();
                    da_add_element(dynamic_array, len_arr, temp);
                    auto t_end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration< double > t_cnt = t_end - t_start;
                    std::cout << "\nOn adding element in array spent " << std::fixed << t_cnt.count() << "s.\n";
                    len_arr++;
                    da_show(dynamic_array, len_arr);
                }
                else std::cout << "Sorry, you haven't filled array yet :<\n";
                break;
            }
            case(3):
            {
                if (if_array and len_arr != 0)
                {
                    std::cout << "There are two methods of delete:\n";
                    std::cout << "1. Delete by index\n";
                    std::cout << "2. Delete by value\n";
                    std::cout << "Write number of method: ";
                    std::cin >> method_of_delete;
                    if (!std::cin) throw ("Invalid value of method's element");
                    if (method_of_delete == 1)
                    {
                        std::cout << "Write index (from 1 to " << len_arr << "):\n";
                        std::cin >> temp;
                        temp--;
                        if (!std::cin or temp < 0 or temp >= len_arr) throw "Wrong index: it must be unsigned integer less than " + len_arr;
                        auto t_start = std::chrono::high_resolution_clock::now();
                        da_delete_element_by_index(dynamic_array, len_arr, temp);
                        auto t_end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration< double > t_cnt = t_end - t_start;
                        std::cout << "\nOn deleting element in array spent " << std::fixed << t_cnt.count() << "s.\n";
                        len_arr--;
                    }
                    else if (method_of_delete == 2)
                    {
                        std::cout << "Write value: ";
                        std::cin >> temp;
                        if (!std::cin) throw "Wrong value: it must be integer";
                        auto t_start = std::chrono::high_resolution_clock::now();
                        da_delete_element_by_value(dynamic_array, len_arr, temp);
                        auto t_end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration< double > t_cnt = t_end - t_start;
                        std::cout << "\nOn deleting element in array spent " << std::fixed << t_cnt.count() << "s.\n";
                    }
                    da_show(dynamic_array, len_arr);
                }
                else std::cout << "Sorry, you haven't filled array yet :<\n";
                break;
            }
            case(4):
            {
                if (if_array and len_arr != 0)
                {
                    std::cout << "There are two methods of getting:\n";
                    std::cout << "1. Get element by index\n";
                    std::cout << "2. Get index[es] by value\n";
                    std::cout << "Write number of method: ";
                    std::cin >> method_of_get;
                    if (!std::cin) throw ("Invalid value of method's element");
                    if (method_of_get == 1)
                    {
                        std::cout << "Write index (from 1 to " << len_arr << "):\n";
                        std::cin >> temp;
                        temp--;
                        if (!std::cin or temp < 0 or temp >= len_arr) throw "Wrong index: it must be unsigned integer less than " + len_arr;
                        auto t_start = std::chrono::high_resolution_clock::now();
                        std::cout << "Element with index " << temp + 1 << " is " << da_get_element_by_index(dynamic_array, temp) << '\n';
                        auto t_end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration< double > t_cnt = t_end - t_start;
                        std::cout << "\nOn getting element in array spent " << std::fixed << t_cnt.count() << "s.\n";
                    }
                    else if (method_of_get == 2)
                    {
                        std::cout << "Write value: ";
                        std::cin >> temp;
                        if (!std::cin) throw "Wrong value: it must be integer";
                        auto t_start = std::chrono::high_resolution_clock::now();
                        da_get_element_by_value(dynamic_array, len_arr, temp);
                        auto t_end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration< double > t_cnt = t_end - t_start;
                        std::cout << "\nOn getting element in array spent " << std::fixed << t_cnt.count() << "s.\n";
                    }
                }
                else std::cout << "Sorry, you haven't filled array yet :<\n";
                break;
            }
            case (5):
            {
                list.empty_list();
                if_continue = 1;
                std::cout << "There are three methods of filling:\n";
                std::cout << "1. Filling by random numbers\n";
                std::cout << "2. Filling by console\n";
                std::cout << "3. Filling by file\n";
                std::cout << "Write number of method: ";
                std::cin >> method_of_filling;
                if (!std::cin) throw "Wrong method of filling (it must be an unsigned integer)";
                switch (method_of_filling)
                {
                case(1):
                {
                    std::cout << "Write size of list:\n";
                    std::cin >> size;
                    if (!std::cin) throw "Wrong length of array (it must be an unsigned integer)";
                    auto t_start = std::chrono::high_resolution_clock::now();
                    for (int i = 0; i < size; i++)
                    {
                        temp = (rand() % 100);
                        if (temp < 0) temp *= (-1);
                        list.add_tail(temp);
                    }
                    auto t_end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration< double > t_cnt = t_end - t_start;
                    std::cout << "\nOn adding list spent " << std::fixed << t_cnt.count() << "s.\n";
                    if_list = 1;
                    break;
                }
                case(2):
                {
                    std::chrono::duration< double > t_cnt = std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now();
                    while (if_continue)
                    {
                        std::cout << "Write value: ";
                        std::cin >> temp;
                        if (!std::cin) throw ("Invalid value of array's element");
                        auto t_start = std::chrono::high_resolution_clock::now();
                        list.add_tail(temp);
                        auto t_end = std::chrono::high_resolution_clock::now();
                        t_cnt += t_end - t_start;
                        std::chrono::duration< double > t_cnt = t_end - t_start;
                        std::cout << "If you want to continue write 1, else write 0: ";
                        std::cin >> if_continue;
                        if (!std::cin) throw ("You must write 0 or 1");
                    }
                    std::cout << "\nOn adding list spent " << std::fixed << t_cnt.count() << "s.\n";
                    if_list = 1;
                    break;
                }
                case(3):
                {
                    auto t_start = std::chrono::high_resolution_clock::now();
                    while (fin)
                    {
                        fin >> temp;
                        list.add_tail(temp);
                    }
                    auto t_end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration< double > t_cnt = t_end - t_start;
                    std::cout << "\nOn adding list spent " << std::fixed << t_cnt.count() << "s.\n";
                    if (list.get_size()) list.delete_by_index(list.get_size() - 1);
                    if_list = 1;
                    break;
                }
                default:
                {
                    std::cout << "There isn't operation with number " << method_of_filling << '\n';
                }
                }
                
                list.show_list();
                break;
            }
            case (6):
            {
                if (if_list and list.get_size() != 0)
                {
                    std::cout << "Write value: ";
                    std::cin >> temp;
                    if (!std::cin) throw ("Invalid value of array's element");
                    auto t_start = std::chrono::high_resolution_clock::now();
                    list.add_tail(temp);
                    auto t_end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration< double > t_cnt = t_end - t_start;
                    std::cout << "\nOn adding element in list spent " << std::fixed << t_cnt.count() << "s.\n";
                    list.show_list();
                }
                else std::cout << "Sorry, you haven't filled list yet :<\n";
                break;
            }
            case(7):
            {
                if (if_list and list.get_size() != 0)
                {
                    std::cout << "There are two methods of delete:\n";
                    std::cout << "1. Delete by index\n";
                    std::cout << "2. Delete by value\n";
                    std::cout << "Write number of method: ";
                    std::cin >> method_of_delete;
                    if (!std::cin) throw ("Invalid value of method's element");
                    if (method_of_delete == 1)
                    {
                        std::cout << "Write index (from 1 to " << list.get_size() << "):\n";
                        std::cin >> temp;
                        temp--;
                        if (!std::cin or temp < 0 or temp >= list.get_size()) throw "Wrong index: it must be unsigned integer less than " + list.get_size();
                        auto t_start = std::chrono::high_resolution_clock::now();
                        list.delete_by_index(temp);
                        auto t_end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration< double > t_cnt = t_end - t_start;
                        std::cout << "\nOn deleting element in list spent " << std::fixed << t_cnt.count() << "s.\n";
                    }
                    else if (method_of_delete == 2)
                    {
                        std::cout << "Write value: ";
                        std::cin >> temp;
                        if (!std::cin) throw "Wrong value: it must be integer";
                        auto t_start = std::chrono::high_resolution_clock::now();
                        list.delete_by_value(temp);
                        auto t_end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration< double > t_cnt = t_end - t_start;
                        std::cout << "\nOn deleting element in list spent " << std::fixed << t_cnt.count() << "s.\n";
                    }
                    list.show_list();
                }
                else std::cout << "Sorry, you haven't filled list yet :<\n";
                break;
            }
            case(8):
            {
                if (if_list and list.get_size() != 0)
                {
                    std::cout << "There are two methods of getting:\n";
                    std::cout << "1. Get element by index\n";
                    std::cout << "2. Get index[es] by value\n";
                    std::cout << "Write number of method: ";
                    std::cin >> method_of_get;
                    if (!std::cin) throw ("Invalid value of method's element");
                    if (method_of_get == 1)
                    {
                        std::cout << "Write index (from 1 to " << list.get_size() << "):\n";
                        std::cin >> temp;
                        temp--;
                        if (!std::cin or temp < 0 or temp >= list.get_size()) throw "Wrong index: it must be unsigned integer less than " + list.get_size();
                        auto t_start = std::chrono::high_resolution_clock::now();
                        list.get_by_index(temp);
                        auto t_end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration< double > t_cnt = t_end - t_start;
                        std::cout << "\nOn getting element in list spent " << std::fixed << t_cnt.count() << "s.\n";
                    }
                    else if (method_of_get == 2)
                    {
                        std::cout << "Write value: ";
                        std::cin >> temp;
                        if (!std::cin) throw "Wrong value: it must be integer";
                        auto t_start = std::chrono::high_resolution_clock::now();
                        list.get_by_value(temp);
                        auto t_end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration< double > t_cnt = t_end - t_start;
                        std::cout << "\nOn getting element in list spent " << std::fixed << t_cnt.count() << "s.\n";
                    }
                }
                else std::cout << "Sorry, you haven't filled list yet :<\n";
                break;
            }
            case (9):
            {
                if (if_array and len_arr != 0) da_show(dynamic_array, len_arr);
                else std::cout << "Sorry, you haven't filled array yet :<\n";
            }
            case (10):
            {
                if (if_list and list.get_size() != 0) list.show_list();
                else std::cout << "Sorry, you haven't filled list yet :<\n";
            }
            }
            std::cout << '\n';
            std::cout << "Task numbers: \n";
            std::cout << "1. Form new dynamic array\n";
            std::cout << "2. Add new element of dynamic array\n";
            std::cout << "3. Delete element of dynamic array\n";
            std::cout << "4. Get element of dynamic array\n";
            std::cout << "5. Form new two-linked list\n";
            std::cout << "6. Add new element of two-linked list\n";
            std::cout << "7. Delete element of two-linked list\n";
            std::cout << "8. Get element of two-linked list\n";
            std::cout << "9. Show array\n";
            std::cout << "10. Show two-linked list\n";
            std::cout << "0. Exit\n";
            std::cout << "Write number of task: \n";
            std::cin >> task_number;
            if (!std::cin) throw "Wrong task number (it must be an unsigned integer)";
        }
    }
    catch (const char* ex)
    {
        std::cout << ex;
    }
    //Delete dynamic array
    delete[] dynamic_array;
}