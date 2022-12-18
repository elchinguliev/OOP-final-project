
#include<iostream>
#include<assert.h>
#include<string>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include <fstream>
#include<vector>

#include <fstream>

using namespace std;
template<class T>
#pragma region StackClass
class Stack {
    T* data;
    size_t size = 0;
public:
    Stack() :data(NULL), size(NULL) {}
    void Push(const T& newdata) {
        auto newarray = new T[size + 1]{};
        for (size_t i = 0; i < size; i++)
        {
            newarray[i] = data[i];
        }
        newarray[size] = newdata;
        if (size != 0) {
            delete[]data;
        }
        data = newarray;
        newarray = nullptr;
        ++size;
    }
    void Pop(int index = -1) {
        if (index != -1) {
            auto newitems = new T[size - 1]{};
            for (size_t i = 0; i < index; i++)
            {
                newitems[i] = data[i];
            }
            int index1 = index + 1;
            int index2 = index;
            for (size_t i = 0; i < size - (index + 1); i++)
            {
                newitems[index2] = data[index1];
                index1++;
                index2++;
            }
            data = newitems;
            newitems = nullptr;
            size -= 1;
        }
        else {
            auto newitems = new T[size - 1]{};
            for (size_t i = 0; i < size - 1; i++)
            {
                newitems[i] = data[i];
            }
            data = newitems;
            newitems = nullptr;
            size -= 1;
        }
    }
    int Peek()const {
        assert(size > 0 && "Empty Stack");
        return data[size - 1];
    }
    void Clear() {
        if (this->data == NULL || this->size == NULL) {
            return;
        }
        delete[]data;
        this->data = NULL;
        this->size = NULL;
    }
    void Show()const {
        for (size_t i = 0; i < size; i++)
        {
            cout << data[i] << endl;
        }
    }
    size_t GetSize()const {
        return size;
    }
    auto& operator[](int index) {
        assert(index >= 0 && index <= size && "Invalid Index");
        return data[index];
    }

};
#pragma endregion
#pragma region ProductClass
class Ingredients {
    string name;
    double price;
    int id;
    int count;
    double calories;
public:
    static int ID;
    Ingredients() = default;
    Ingredients(const string& name, const double& price, const int& count, const double& calories) {
        SetId(ID++);
        SetName(name);
        SetPrice(price);
        SetCount(count);
        SetCalories(calories);
    }
    void SetId(const int& id) {
        this->id = id;
    }
    void SetCount(const int& count) {
        assert(count > 0 && "Count of product  shoulde  be more than 0");
        this->count = count;

    }
    void SetName(const string& name) {
        assert(!name.empty() && "Name of product is null");
        this->name = name;
    }

    void SetPrice(const double& price) {
        assert(price >= 0 && "Price of product should be more than 0");
        if (price < 0)
        {
            throw"Price must be greater than 0 !!!";
        }
        this->price = price;
    }
    void SetCalories(const double& calories) {
        assert(calories >= 0 && "Calories of product should be more than 0");
        this->calories = calories;
    }
    double GetPrice()const {
        return price;
    }
    int GetCount()const {
        return count;
    }
    double GetCalories()const {
        return calories;
    }

    int GetId()const {
        return id;
    }
    string GetName()const {
        return name;
    }
    void Show() {
        cout << "Name : " << GetName() << endl;

    }
    friend ostream& operator<<(ostream& out, const Ingredients& products);

};
#pragma endregion
int Ingredients::ID = 1;
ostream& operator<<(ostream& out, const Ingredients& products) {
    out << "Id : " << products.GetId() << endl << endl;
    out << "Name of product  : " << products.name << endl;
    out << "Price of product  : " << products.price << endl;
    out << " Count of product  : " << products.count << endl;
    out << "Calories of product : " << products.calories << endl;
    return out;
}
#pragma region MealClass
class Meal {
    int id;
    double price;
    Stack<Ingredients>products;
    string name;
    double allCalories;
public:
    static int ID;
    Meal() = default;
    Meal(const double& price, const string& name) {
        SetId(ID++);
        SetName(name);
        SetPrice(price);
    }
    void SetName(const string& name) {
        assert(!name.empty() && "Name of Meal is null");
        this->name = name;
    }
    void SetPrice(const double& price) {
        assert(price > 0 && "Price of meal should be more than 0");
        this->price = price;
    }

    void SetId(const int& id) {
        this->id = id;
    }
    int GetId()const {
        return id;
    }
    double GetPrice()const {
        return price;
    }

    string GetName()const {
        return name;
    }
    void AddProduct(Ingredients& product) {
        products.Push(product);
    }



    Ingredients* GetProductById(int id) {
        for (size_t i = 0; i < products.GetSize(); i++)
        {
            if (products[i].GetId() == id)
            {
                return &products[id];
            }
        }
    }
    void UpdateProduct()
    {
        cout << "Enter id of meal : " << endl;
        int id;
        cin >> id;
        auto products = GetProductById(id);
        cout << "1.Name of product  " << endl;
        cout << "2.Price of product  " << endl;
        cout << "3.Count of product  " << endl;
        cout << "3.Count of calories  " << endl;
        cout << "Enter your choice : ";
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            cin.ignore();
            cin.clear();
            cout << "Enter name : ";
            string name;
            getline(cin, name);
            products->SetName(name);
        }
        else if (choice == 2)
        {
            cout << "Enter price : ";
            double price;
            cin >> price;
            products->SetPrice(price);
        }
        else if (choice == 3)
        {
            cout << "Enter count : ";
            int count;
            cin >> count;
            products->SetCount(count);
        }


    }
    void ShowProductOfMEal()
    {
        products.Show();
    }
    friend ostream& operator<<(ostream& out, Meal& meal) {
        out << "Id : " << meal.GetId() << endl << endl;
        out << "Name of Meal : " << meal.name << endl << endl;
        meal.products.Show();
        return out;
    }
};
//void  to_json(json& js, const Stack<Meal>& f) {
//    for (Meal m : f) {
//       json  j = json{ {"ID ",m.GetId()},{"Name of meal ",m.GetName()},{"Price of meal ",m.GetPrice()}};
//       js += j;
//    }
//}
#pragma endregion
int Meal::ID = 1;

#pragma region KitchenClass
class Kitchen :public Meal {
public:
    Stack<Meal>meals;
    static int notificationCount;

    Kitchen() = default;
    Kitchen(const int& notificationCount, const string& meal) {
        SetNotificationCount(notificationCount);
    }
    void SetNotificationCount(const int& notificationCount) {
        assert(notificationCount >= 0 && "Notification count is negative number");
        this->notificationCount = notificationCount;
    }
    int GetNotificationCount()const {
        return notificationCount;
    }

    void AddMeal(Meal& meal) {
        meals.Push(meal);
    }
    void Show()const {
        meals.Show();
    }
    void ShowName() {
        for (size_t i = 0; i < meals.GetSize(); i++)
        {
            cout << meals[i].GetId() << ". " << meals[i].GetName() << " - " << meals[i].GetPrice() << " $" << endl << endl;
        }
    }
    void ShowMealById(int id) {
        for (size_t i = 0; i < meals.GetSize(); i++)
        {
            if (meals[i].GetId() == id) {
                cout << meals[i] << endl;
            }
        }
    }
    Meal* GetMealById(int id) {
        for (size_t i = 0; i < meals.GetSize(); i++)
        {
            if (meals[i].GetId() == id) {
                return &meals[i];
            }
        }
    }
    void MealsPop(int index) {
        meals.Pop(index);
    }

    int GetMealCount() {
        return meals.GetSize();
    }
    void AddMeal() {
        cin.ignore();
        cin.clear();
        cout << "Enter name : ";
        string name;
        cin >> name;

        cout << "Enter price : ";
        double price;
        cin >> price;
        cout << endl;
        Meal newMeal(price, name);
        int count = 10000;
        int size = 0;
        //for (size_t i = 0; i < size; i++)
        //{
        //    cout << "Enter product name : ";
        //    string pName;
        //    getline(cin, pName);
        //    cin.ignore();
        //    cin.clear();
        //    cout << "Enter product price : ";
        //    double price;
        //    cin >> price;
        //    cin.ignore();
        //    cin.clear();
        //    cout << "Enter product count : ";
        //    int count;
        //    cin >> count;
        //    cin.ignore();
        //    cin.clear();
        //    Product p(name, price, count);
        //    newMeal.AddProduct(p);
        //}
        meals.Push(newMeal);
        cout << "Meal added successfully" << endl << endl;
        cout << "Click enter to continue !!!" << endl;
        system("pause");
        system("cls");
    };
    void UptadeMeals(int id) {
        cout << "Enter id of which meal you want to update : ";
        cin >> id;
        auto meal = GetMealById(id);
        cout << "1. Name" << endl;
        cout << "2. Price" << endl;
        cout << "Enter your choice : " << endl;
        int select;
        cin >> select;
        if (select == 1) {
            cin.ignore();
            cin.clear();
            cout << "Enter new name of meal : ";
            string name;
            getline(cin, name);
            meal->SetName(name);
        }
        else if (select == 2) {
            cout << "Enter new price of meal : ";
            double price;
            cin >> price;
            meal->SetPrice(price);
        }
    }
};

#pragma endregion

#pragma region StockClass
class Stock {
    Stack<Ingredients>products;
public:
    Stock() = default;
    void AddProduct(Ingredients& product) {
        products.Push(product);
    }
    void Show() {
        int id = 1;
        cout << "------ALL INGREDIENTS------" << endl << endl;
        for (size_t i = 0; i < products.GetSize(); i++)
        {
            cout << "Id : " << id++ << endl << endl;
            cout << products[i] << endl << endl;
        }
    }
    auto* GetProductById(int index) {
        for (size_t i = 0; i < products.GetSize(); i++)
        {
            if (products[i].GetId() == index) {
                return &products[i];
            }
        }
    }
    bool ProductCount(int index, int count) {
        auto product = GetProductById(index);
        int temp = product->GetCount() - count;
        if (temp >= 0) {
            products[index].SetCount(temp);
            return true;
        }
        return false;
    }
    void DeleteIngredientById(int index = -1) {
        products.Pop(index);
    }
    void ShowProductCount() {
        for (size_t i = 0; i < products.GetSize(); i++)
        {
            cout << products[i].GetId() << " - " << products[i].GetName() << " count " << products[i].GetCount() << endl << endl;
        }
    }
    int GetProductCount() {
        return products.GetSize();
    }
};
#pragma endregion
#pragma region UserClass
class User {
    string tableNo;
    Stack<Kitchen>menu;
public:
    User() = default;
    User(const string& tableNo) {
        SetTable(tableNo);
    }
    void SetTable(const string& tableNo) {
        assert(!tableNo.empty() && "Table should not be empty");
        this->tableNo = tableNo;
    }
    string GetTableNo()const {
        return tableNo;
    }
    void AddMenu(Kitchen& kitchen) {
        menu.Push(kitchen);
    }
    void ShowMenu() {
        for (size_t i = 0; i < menu.GetSize(); i++)
        {
            menu[i].ShowName();
        }
    }
};
#pragma endregion

class MyException {
    string message;
public:
    MyException(string message) { this->message = message; }
    string Message() const { return message; }
};

class NullReferenceException : public MyException {
public:
    NullReferenceException(string message) : MyException(message) {}
};

class OutOfRangeException : public MyException {
public:
    OutOfRangeException(string message) : MyException(message) {}
};

class ArgumentException : public MyException {
public:
    ArgumentException(string message) : MyException(message) {}
};

class ArgumentNullException : public ArgumentException {
public:
    ArgumentNullException(string message) : ArgumentException(message) {}
};

class ArgumentInvalidException : public ArgumentException {
public:
    ArgumentInvalidException(string message) : ArgumentException(message) {}
};


void main() {

    Ingredients i1("Tomato", 0.7, 20, 30);
    Ingredients i2("Olive", 0.3, 35, 44);
    Ingredients i3("Mushroom", 1.2, 20, 21);
    Ingredients i4("Flour", 1.8, 40, 77);
    Ingredients i5("Chicken", 3, 50, 100);
    Ingredients i6("Bacon", 5, 10, 120);

 /*   vector<Product>products;
    Product temp;*/

  /*  string filename = "ingredients.txt";

    ofstream outfile;
    outfile.open(filename.c_str(), ios::out | ios::app);
    outfile.write((char*)(&i1), sizeof(i1));
    outfile.close();
    ifstream infile;
    infile.open(filename.c_str(), ios::in);

    while (infile.read((char*)&i1, sizeof(i1)))
        infile.close();
    cout << i1.GetId();
    cout << i1.GetName();
    cout << i1.GetPrice();
    cout << i1.GetCount();
    cout << i1.GetCalories();



    outfile.open(filename.c_str(), ios::out | ios::app);
    outfile.write((char*)(&i2), sizeof(i2));
    outfile.close();
    infile.open(filename.c_str(), ios::in);
    while (infile.read((char*)&i2, sizeof(i2)))
        infile.close();
    cout << i2.GetId() ;
    cout << i2.GetName() ;;
    cout << i2.GetPrice();
    cout << i2.GetCount();
    cout << i2.GetCalories();

    cout << endl;

    outfile.open(filename.c_str(), ios::out | ios::app);
    outfile.write((char*)(&i3), sizeof(i3));
    outfile.close();
    infile.open(filename.c_str(), ios::in);
    while (infile.read((char*)&i3, sizeof(i3)))
        infile.close();
    cout << i3.GetId();
    cout << i3.GetName();
    cout << i3.GetPrice();
    cout << i3.GetCount();
    cout << i3.GetCalories();

    cout << endl;

    outfile.open(filename.c_str(), ios::out | ios::app);
    outfile.write((char*)(&i4), sizeof(i4));
    outfile.close();
    infile.open(filename.c_str(), ios::in);
    while (infile.read((char*)&i4, sizeof(i4)))
        infile.close();
    cout << i4.GetId();
    cout << i4.GetName();
    cout << i4.GetPrice();
    cout << i4.GetCount();
    cout << i4.GetCalories();


    cout << endl;

    outfile.open(filename.c_str(), ios::out | ios::app);
    outfile.write((char*)(&i5), sizeof(i5));
    outfile.close();
    infile.open(filename.c_str(), ios::in);
    while (infile.read((char*)&i5, sizeof(i5)))
        infile.close();
    cout << i5.GetId();
    cout << i5.GetName();
    cout << i5.GetPrice();
    cout << i5.GetCount();
    cout << i5.GetCalories();



    cout << endl;

    outfile.open(filename.c_str(), ios::out | ios::app);
    outfile.write((char*)(&i6), sizeof(i6));
    outfile.close();
    infile.open(filename.c_str(), ios::in);
    while (infile.read((char*)&i6, sizeof(i6)))
        infile.close();
    cout << i6.GetId();
    cout << i6.GetName();
    cout << i6.GetPrice();
    cout << i6.GetCount();
    cout << i6.GetCalories();*/


    Stock stock;
    stock.AddProduct(i1);
    stock.AddProduct(i2);
    stock.AddProduct(i3);
    stock.AddProduct(i4);
    stock.AddProduct(i5);
    stock.AddProduct(i6);
    Meal f(20, "Salami Pizza");
    f.AddProduct(i1);
    f.AddProduct(i2);
    f.AddProduct(i3);
    f.AddProduct(i4);
    f.AddProduct(i5);
    f.AddProduct(i6);


    //string filameal = "meals.txt";

    //outfile.open(filameal.c_str(), ios::out | ios::app);
    //outfile.write((char*)(&f), sizeof(f));
    //outfile.close();
    //infile.open(filameal.c_str(), ios::in);
    //while (infile.read((char*)&f, sizeof(f)))
    //    infile.close();
    //cout << f.GetId();
    //cout << f.GetName();
    //cout << f.GetPrice();
    //outfile.close();

    //cout << endl;

    Meal f1(13, "Hamburger");
    f1.AddProduct(i1);
    f1.AddProduct(i2);
    f1.AddProduct(i5);


    Kitchen k;
    k.AddMeal(f);
    k.AddMeal(f1);
    User c("T-20");
    c.AddMenu(k);

#pragma region START
    double totalPrice = 0;



    while (true)
    {

        system("cls");

        cout << " .----------------.  .----------------.  .----------------.          .----------------.  .----------------.  .----------------.  .----------------.                                                    " << endl;
        cout << "| .--------------. || .--------------. || .--------------. |        | .--------------. || .--------------. || .--------------. || .--------------. |                                                    " << endl;
        cout << "| |  _________   | || |      __      | || |  _________   | |        | | ____    ____ | || |     ____     | || |  _______     | || |  _________   | |                                                    " << endl;
        cout << "| | |_   ___  |  | || |     /  \\     | || | |  _   _  |  | |        | ||_   \\  /   _|| || |   .'    `.   | || | |_   __ \\    | || | |_   ___  |  | |                                                    " << endl;
        cout << "| |   | |_  \\_|  | || |    / /\\ \\    | || | |_/ | | \\_|  | |        | |  |   \\/   |  | || |  /  .--.  \  | || |   | |__) |   | || |   | |_  \\_|  | |                                                    " << endl;
        cout << "| |   |  _|  _   | || |   / ____ \\   | || |     | |      | |        | |  | |\\  /| |  | || |  | |    | |  | || |   |  __ /    | || |   |  _|  _   | |                                                    " << endl;
        cout << "| |  _| |___/ |  | || | _/ /    \\ \\_ | || |    _| |_     | |        | | _| |_\\/_| |_ | || |  \\  `--'  /  | || |  _| |  \\ \\_  | || |  _| |___/ |  | |                                                    " << endl;
        cout << "| | |_________|  | || ||____|  |____|| || |   |_____|    | |        | ||_____||_____|| || |   `.____.'   | || | |____| |___| | || | |_________|  | |                                                    " << endl;
        cout << "| |              | || |              | || |              | |        | |              | || |              | || |              | || |              | |                                                    " << endl;
        cout << "| '--------------' || '--------------' || '--------------' |        | '--------------' || '--------------' || '--------------' || '--------------' |                                                    " << endl;
        cout << " '----------------'  '----------------'  '----------------'          '----------------'  '----------------'  '----------------'  '----------------'                                                     " << endl;
        cout << " .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .-----------------. .----------------. " << endl;
        cout << "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |" << endl;
        cout << "| |  _______     | || |  _________   | || |    _______   | || |  _________   | || |      __      | || | _____  _____ | || |  _______     | || |      __      | || | ____  _____  | || |  _________   | |" << endl;
        cout << "| | |_   __ \\    | || | |_   ___  |  | || |   /  ___  |  | || | |  _   _  |  | || |     /  \\     | || ||_   _||_   _|| || | |_   __ \\    | || |     /  \\     | || ||_   \\|_   _| | || | |  _   _  |  | |" << endl;
        cout << "| |   | |__) |   | || |   | |_  \\_|  | || |  |  (__ \\_|  | || | |_/ | | \\_|  | || |    / /\\ \\    | || |  | |    | |  | || |   | |__) |   | || |    / /\\ \\    | || |  |   \ | |   | || | |_/ | | \\_|  | |" << endl;
        cout << "| |   |  __ /    | || |   |  _|  _   | || |   '.___`-.   | || |     | |      | || |   / ____ \\   | || |  | '    ' |  | || |   |  __ /    | || |   / ____ \\   | || |  | |\\ \\| |   | || |     | |      | |" << endl;
        cout << "| |  _| |  \\ \\_  | || |  _| |___/ |  | || |  |`\\____) |  | || |    _| |_     | || | _/ /    \\ \_ | || |   \\ `--' /   | || |  _| |  \\ \\_  | || | _/ /    \\ \\_ | || | _| |_\\   |_  | || |    _| |_     | |" << endl;
        cout << "| | |____| |___| | || | |_________|  | || |  |_______.'  | || |   |_____|    | || ||____|  |____|| || |    `.__.'    | || | |____| |___| | || ||____|  |____|| || ||_____|\\____| | || |   |_____|    | |" << endl;
        cout << "| |              | || |              | || |              | || |              | || |              | || |              | || |              | || |              | || |              | || |              | |" << endl;
        cout << "| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |" << endl;
        cout << " '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' " << endl;
        cout << endl << endl;
        cout << "                                                                                     _   _   _   _   _   _      " << endl;
        cout << "                                                                                    / \\ / \\ / \\ / \\ / \\ / \\     " << endl;
        cout << "                                                                                   ( 1 | . | U | S | E | R )    " << endl;
        cout << "                                                                                    \\_/ \\_/ \\_/ \\_/ \\_/ \\_/     " << endl;
        cout << "                                                                                     _   _   _   _   _   _   _  " << endl;
        cout << "                                                                                    / \\ / \\ / \\ / \\ / \\ / \\ / \\ " << endl;
        cout << "                                                                                   ( 2 | . | A | D | M | I | N )" << endl;
        cout << "                                                                                    \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ " << endl << endl;
        cout << "                                                                          Enter select : ";
        string select;
        cin >> select;
        if (select == "1") {
            system("cls");
            cout << "Hey dear user,please register by writing your fullname  : ";
            string fullname;
            cin >> fullname;
            system("cls");
            cout << "--------------------------WELCOME TO OUR RESTAURANT--------------------------" << endl;
            c.ShowMenu();
            cout << "Enter your choice to view : ";
            int select;
            cin >> select;
            cout << endl;
            k.ShowMealById(select);
            cout << "1. Order !!!" << endl;
            cout << "2. Add ingredients !!!" << endl;
            cout << "Enter select : ";
            int select1;
            cin >> select1;
            if (select1 == 1) {
                cout << "Enter count of meal  : ";
                int count;
                cin >> count;
                if (count > 0) {
                    auto meal = k.GetMealById(select);
                    totalPrice += count * meal->GetPrice();
                    cout << "Total price : " << totalPrice << " $" << endl;
                    cout << "1. Continue" << endl;
                    cout << "2. Finish" << endl;
                    cout << "Select : ";
                    int select;
                    cin >> select;
                    if (select == 1) {
                    }
                }
            }
            else if (select1 == 2) {
                system("cls");
                cout << endl;
                cout << "1.Show ingredients " << endl;
                stock.Show();
                cout << "Enter id of ingredients  : ";
                int id;
                cin >> id;
                auto product = stock.GetProductById(id);
                cout << product << endl;
                cout << "Enter " << product->GetName() << " count : ";
                double count;
                cin >> count;
                if (stock.ProductCount(id, count)) {
                    auto meal = k.GetMealById(select);
                    meal->AddProduct(*product);
                    totalPrice += meal->GetPrice();
                    totalPrice += product->GetPrice() * count;
                    cout << "\n" << meal << endl;
                    cout << "Ingredients added successfully" << endl << endl;
                    cout << "Total price : " << totalPrice << " $" << endl;
                }
                else {
                    auto meal = k.GetMealById(select);
                    totalPrice += meal->GetPrice();
                    cout << "Ingredients is out of stock" << endl;
                }
            }
        }
        else if (select == "2") {
            system("cls");
            cout << "PLEASE LOGIN " << endl;
            while (true)
            {
                cin.ignore();
                cin.clear();
                cout << "Enter username : ";
                string username;
                getline(cin, username);
                system("cls");
                cout << "Enter password : ";
                string password;
                getline(cin, password);
                cout << endl;
                if (username == "e") {
                    if (password == "e") {
                        system("cls");
                        cout << "---------------------WELCOME ADMIN--------------------- " << endl;
                        cout << "1. KITCHEN " << endl;
                        cout << "2. STOCK   " << endl;
                        cout << "3. FINISH " << endl;
                        cout << "Enter select : ";
                        int adminselect = 0;
                        cin >> adminselect;
                        if (adminselect == 1) {
                            system("cls");
                            cout << "-----KITCHEN-----" << endl;
                            k.ShowName();
                            cout << "1. Delete meal " << endl;
                            cout << "2. Update meal" << endl;
                            cout << "3. Add meal" << endl;
                            cout << "Enter your select : ";
                            int select;
                            cin >> select;
                            system("cls");
                            if (select == 1) {
                                while (true)
                                {
                                    cout << "Enter ID of meal : ";
                                    int id;
                                    cin >> id;
                                    if (k.GetMealCount() >= id) {
                                        --id;
                                        k.MealsPop(id);
                                        system("cls");
                                        k.ShowName();
                                        cout << "Meal deleted successfully !!!" << endl;
                                        cout << "Click enter to continue !!!" << endl;
                                        system("pause");
                                        system("cls");
                                        break;
                                    }
                                    else {
                                        cout << "Meal does not found!" << endl;
                                    }
                                }
                            }
                            else if (select == 2)
                            {
                                k.UptadeMeals(2);
                                //k.UpdateProduct();
                               /* k.Show();*/
                                cout << "Meal updated successfully !!" << endl;
                                cout << "Click enter to continue !!" << endl;
                            }
                            else if (select == 3) {
                                k.ShowName();
                                k.AddMeal();
                            }
                        }
                        else if (adminselect == 2)
                        {
                            system("cls");
                            cout << "-----STOCK-----" << endl;
                            cout << "1. Show Ingredients" << endl;
                            cout << "2. Add Ingredients" << endl;
                            cout << "3. Delete Ingredients" << endl;
                            cout << "4. Update ingredients count" << endl;
                            cout << "5. BACK" << endl;
                            cout << "Select : ";
                            int select;
                            cin >> select;
                            if (select == 1) {
                                system("cls");
                                stock.Show();
                                cout << "Click enter to continue !!!" << endl;
                                system("pause");
                                system("cls");
                            }
                            else if (select == 2) {
                                system("cls");
                                cin.ignore();
                                cin.clear();
                                cout << "Enter name of ingredient  : ";
                                string name;
                                getline(cin, name);
                                cout << "Enter price of  ingredient : ";
                                double price;
                                cin >> price;
                                cout << "Enter count of ingredient  : ";
                                int count;
                                cin >> count;
                                cout << "Enter calories of ingredient : ";
                                double calories;
                                cin >> calories;
                                Ingredients i(name, price, count, calories);
                                stock.AddProduct(i);
                                cout << "Ingredient added successfully" << endl;
                                cout << "Click enter to continue !!!" << endl;
                                system("pause");
                                system("cls");
                            }
                            else if (select == 3) {
                                system("cls");
                                stock.Show();
                                cout << "Enter id of ingredients : ";
                                int id;
                                cin >> id;
                                --id;
                                stock.DeleteIngredientById(id);
                                system("cls");
                                cout << "Ingredient deleted successfully" << endl;
                                cout << "Click enter to continue !!!" << endl;
                                system("pause");
                                system("cls");
                            }
                            else if (select == 4) {
                                system("cls");
                                stock.ShowProductCount();
                                cout << "Enter id of ingredient : ";
                                int id1;
                                cin >> id1;
                                Ingredients* i = stock.GetProductById(id1);
                                cout << "Enter new count : ";
                                int count;
                                cin >> count;
                                i->SetCount(count);
                                cout << "Count uptaded successfully" << endl;
                                cout << "Click enter to continue !!!" << endl;
                                system("pause");
                                system("cls");
                            }
                            else if (select == 5) {
                                cout << "Click enter to back !!!" << endl;
                                system("pause");
                                system("cls");

                            }
                            else {
                                cout << "Invalid select !!" << endl;
                                cout << "Click enter to continue !!!" << endl;
                                system("pause");
                                /* system("cls");*/
                            }

                        }
                        else if (adminselect == 3)
                        {
                            system("cls");
                            cout << "You finished your choice,if you want try again something,please click 'Enter button'  and start again !!!" << endl;
                            break;
                        }
                    }

                    else {
                        cout << "Wrong password!" << endl;
                    }
                }

                else {
                    cout << "Wrong username!" << endl;
                }
            }
        }

        else {
            cout << "Your select is incorrect!!!\nPlease try again !" << endl;
        }
        system("pause");
    }

#pragma endregion
}

