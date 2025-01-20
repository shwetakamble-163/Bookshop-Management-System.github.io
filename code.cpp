
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

// Data structures and global variables
struct Product
 {
    string id;
    string name;
    int stock;
    double price;

    void updateStock(int quantity) {
        stock += quantity;
    }
};

struct Customer {
    string id;
    string name;
    int loyaltyPoints;
};

struct Transaction {
    string customerId;
    string productId;
    int quantity;
    double totalCost;
    string date;
};

vector<Product*> products;

vector<Customer*> customers;

vector<Transaction> transactions;

string adminPassword = "admin123";
bool adminLoggedIn = false;

// Function prototypes
void addCustomer();

void addProduct();

void purchaseProduct();

void viewProducts();

void viewCustomers();

void handleReturns(const string& transactionId);

void adminLogin();

void saveDataToFile();

void loadDataFromFile();

void categorizeLoyaltyTier(const Customer& customer);

void displayLoyaltyTiers();

void generateMonthlySalesReport(const string& monthYear);

void searchCustomerById(const string& customerId);

void applyBulkDiscountByGenre(const string& genre, double discountPercentage);

void categorizeProduct();

void searchProductByIdOrName(const string& query);  // New function


void updateProductPrice(const string& productId, double newPrice);  // New function

void deleteProduct(const string& productId);  // New function

void viewTransactionHistory(const string& customerId);  // New function

void updateCustomerLoyaltyPoints(const string& customerId, int newPoints);  // New function

void viewProductStock(const string& productId);  // New function

bool isProductAvailable(const string& productId, int quantity);  // New function

void generateCustomerLoyaltyReport();  // New function

void viewProductsByGenre(const string& genre);  // New function

void sortProductsByPrice(bool ascending = true);  // New function

void generateProductSalesReport(const string& productId);  // New function

void restockProduct(const string& productId, int additionalStock);  // New function

void calculateTotalLoyaltyPoints();

void findProductsByPriceRange(double minPrice, double maxPrice);

void deleteCustomerById(const string& customerId);

void generateInventorySummary();

void sendLoyaltyRewards(int topN);




// Function definitions
void addCustomer() {

    Customer* newCustomer = new Customer;

    cout << "Enter Customer ID: ";

    cin >> newCustomer->id;

    cout << "Enter Customer Name: ";

    cin >> newCustomer->name;

    newCustomer->loyaltyPoints = 0;

    customers.push_back(newCustomer);

    cout << "Customer added successfully!\n";
}
void updateProductPrice(const string& productId, double newPrice) {

    auto productIt = find_if(products.begin(), products.end(), [&](Product* p)
                              {
        return p->id == productId;
    });

    if (productIt != products.end())
        {
        (*productIt)->price = newPrice;

        cout << "Product price updated successfully!\n";

    }
    else
        {
        cout << "Product not found.\n";
    }
}
void deleteProduct(const string& productId)
 {
    auto productIt = find_if(products.begin(), products.end(), [&](Product* p)
                             {
        return p->id == productId;
    });

    if (productIt != products.end()) {
        products.erase(productIt);
        cout << "Product deleted successfully!\n";
    } else {
        cout << "Product not found.\n";
    }
}
void viewTransactionHistory(const string& customerId)
{

    cout << "--- Transaction History ---\n";

    for (const auto& transaction : transactions) {

        if (transaction.customerId == customerId) {

            cout << "Product ID: " << transaction.productId

                 << ", Quantity: " << transaction.quantity

                 << ", Total Cost: " << transaction.totalCost

                 << ", Date: " << transaction.date << endl;
        }
    }
}

void updateCustomerLoyaltyPoints(const string& customerId, int points)
{

    auto customerIt = find_if(customers.begin(), customers.end(), [&](Customer* c)
                               {



        return c->id == customerId;
    });

    if (customerIt != customers.end())
    {


        (*customerIt)->loyaltyPoints += points;

        cout << "Loyalty points updated successfully!\n";
    }

    else
     {
        cout << "Customer not found.\n";
    }
}
void viewProductStock(const string& productId)
 {

    auto productIt = find_if(products.begin(), products.end(), [&](Product* p)
                              {

        return p->id == productId;
    });

    if (productIt != products.end())

        {


        cout << "Product ID: " << (*productIt)->id

             << ", Name: " << (*productIt)->name

             << ", Stock: " << (*productIt)->stock

             << ", Price: " << (*productIt)->price << endl;
    }

    else
    {
        cout << "Product not found.\n";
    }
}
bool isProductAvailable(const string& productId, int quantity)
 {

    auto productIt = find_if(products.begin(), products.end(), [&](Product* p)
                              {

        return p->id == productId;
    });

    if (productIt != products.end() && (*productIt)->stock >= quantity)

        {
        return true;
    }
    return false;
}
void generateCustomerLoyaltyReport()
 {

    cout << "--- Customer Loyalty Report ---\n";

    for (const auto& customer : customers) {

        cout << "Customer ID: " << customer->id

             << ", Name: " << customer->name

             << ", Loyalty Points: " << customer->loyaltyPoints << endl;
    }
}

void viewProductsByGenre(const string& genre)


{

    cout << "--- Products in Genre: " << genre << " ---\n";

    for (const auto& product : products) {

        if (product->name == genre) { // Assuming 'name' represents the genre

            cout << "Product ID: " << product->id

                 << ", Name: " << product->name

                 << ", Stock: " << product->stock

                 << ", Price: " << product->price << endl;
        }
    }
}

void sortProductsByPrice(bool ascending)
 {
    sort(products.begin(), products.end(), [&](Product* p1, Product* p2)
         {
        if (ascending) {
            return p1->price < p2->price;
        }
        return p1->price > p2->price;
    });

    cout << "--- Products Sorted by Price ---\n";

    for (const auto& product : products)
        {

        cout << "Product ID: " << product->id

             << ", Name: " << product->name

             << ", Price: " << product->price << endl;
    }
}
void generateProductSalesReport(const string& monthYear)
 {

    double totalSales = 0;
    cout << "--- Sales Report for " << monthYear << " ---\n";

    for (const auto& transaction : transactions)
        {

        if (transaction.date.substr(0, 7) == monthYear)
            {

            auto productIt = find_if(products.begin(), products.end(), [&](Product* p)
                                     {

                return p->id == transaction.productId;
            });

            if (productIt != products.end())
                {
                totalSales += transaction.totalCost;
            }
        }
    }
    cout << "Total Sales for " << monthYear << ": $" << totalSales << endl;
}
void restockProduct(const string& productId, int quantity)
{

    auto productIt = find_if(products.begin(), products.end(), [&](Product* p)
                              {

        return p->id == productId;
    });

    if (productIt != products.end())
        {
        (*productIt)->stock += quantity;
        cout << "Product restocked. New stock: " << (*productIt)->stock << endl;
    }
    else
    {
        cout << "Product not found.\n";
    }
}


void addProduct()
{
    Product* newProduct = new Product;

    cout << "Enter Product ID: ";

    cin >> newProduct->id;

    cout << "Enter Product Name: ";

    cin >> newProduct->name;

    cout << "Enter Stock Quantity: ";

    cin >> newProduct->stock;

    cout << "Enter Product Price: ";

    cin >> newProduct->price;

    products.push_back(newProduct);

    cout << "Product added successfully!\n";
}

void purchaseProduct()
 {
    string customerId, productId;

    int quantity;

    cout << "Enter Customer ID: ";

    cin >> customerId;

    cout << "Enter Product ID: ";

    cin >> productId;

    cout << "Enter Quantity: ";

    cin >> quantity;

    auto productIt = find_if(products.begin(), products.end(), [&](Product* p) {
        return p->id == productId;
    });

    if (productIt != products.end() && (*productIt)->stock >= quantity)
        {

        double totalCost = quantity * (*productIt)->price;

        (*productIt)->updateStock(-quantity);

        auto customerIt = find_if(customers.begin(), customers.end(), [&](Customer* c)
                                   {

            return c->id == customerId;
        });

        if (customerIt != customers.end())
            {

            (*customerIt)->loyaltyPoints += static_cast<int>(totalCost / 10);
        }

        transactions.push_back({customerId, productId, quantity, totalCost, "2025-01-01"});
        cout << "Purchase successful!\n";
    }
     else
        {
        cout << "Product not available or insufficient stock.\n";
    }
}

void viewProducts()
 {
    cout << "--- Products ---\n";
    for (const auto& product : products)
        {

        cout << "ID: " << product->id

             << ", Name: " << product->name

             << ", Stock: " << product->stock

             << ", Price: " << product->price << endl;
    }
}
void searchProductByIdOrName(const string& query)
{
    bool found = false;
    for (const auto& product : products) {
        if (product->id == query || product->name == query) {
            cout << "Product ID: " << product->id
                 << ", Name: " << product->name
                 << ", Stock: " << product->stock
                 << ", Price: " << product->price << endl;
            found = true;
        }
    }
    if (!found)
        {
        cout << "Product not found.\n";
    }
}





void viewCustomers()
 {
    cout << "--- Customers ---\n";

    for (const auto& customer : customers) {

        cout << "ID: " << customer->id

             << ", Name: " << customer->name

             << ", Loyalty Points: " << customer->loyaltyPoints << endl;
    }
}




void handleReturns(const string& transactionId)
{

    auto it = find_if(transactions.begin(), transactions.end(), [&](const Transaction& t)
                       {

        return t.customerId == transactionId;
    });

    if (it != transactions.end())
        {

        for (auto& product : products)
            {

            if (product->id == it->productId)
                {

                product->updateStock(it->quantity);

                cout << "Product returned. Stock updated.\n";

                transactions.erase(it);

                return;
            }
        }
    }
    else
        {
        cout << "Transaction not found for return.\n";
    }
}



void adminLogin()
{
    string inputPassword;

    cout << "Enter admin password: ";

    cin >> inputPassword;

    if (inputPassword == adminPassword)
        {

        adminLoggedIn = true;

        cout << "Admin login successful!\n";

    }
    else
     {
        cout << "Incorrect password. Access denied.\n";
    }
}




 void saveDataToFile()
  {
    ofstream outFile("data.txt");
    if (outFile)
        {
        for (const auto& customer : customers)
         {
            outFile << customer->id << "," << customer->name << "," << customer->loyaltyPoints << "\n";
        }

        for (const auto& product : products) {
            outFile << product->id << "," << product->name << "," << product->stock << "," << product->price << "\n";
        }

        outFile << "Transactions:\n";
        for (const auto& transaction : transactions)
            {
            outFile << transaction.customerId << "," << transaction.productId << ","

                    << transaction.quantity << "," << transaction.totalCost << ","

                    << transaction.date << "\n";
        }
    }
    outFile.close();
}



void loadDataFromFile()
 {
    ifstream inFile("data.txt");
    string line;

    while (getline(inFile, line))
        {
        // Load customers, products, and transactions from file (to be implemented)
    }
    inFile.close();
}



void categorizeLoyaltyTier(const Customer& customer)
 {
    string tier;
    if (customer.loyaltyPoints < 50)
        {

        tier = "Bronze";

    }
    else if (customer.loyaltyPoints < 150)
        {

        tier = "Silver";
    }
    else
     {
        tier = "Gold";
    }
    cout << "Customer " << customer.name << " is in the " << tier << " tier.\n";
}



void displayLoyaltyTiers() {
    cout << "\n--- Loyalty Tiers ---\n";

    for (const auto& customer : customers) {

        categorizeLoyaltyTier(*customer); // Dereference the pointer here
    }
}




void searchCustomerById(const string& customerId)
{

    auto customerIt = find_if(customers.begin(), customers.end(), [&](Customer* c)
                               {

        return c->id == customerId;
    });

    if (customerIt != customers.end())
        {
        cout << "Customer Found: ID: " << (*customerIt)->id

             << ", Name: " << (*customerIt)->name

             << ", Loyalty Points: " << (*customerIt)->loyaltyPoints << endl;
    }
     else
        {
        cout << "Customer not found.\n";
    }
}



void generateMonthlySalesReport(const string& monthYear)
 {

    double totalSales = 0;
    cout << "--- Sales Report for " << monthYear << " ---\n";

    for (const auto& transaction : transactions)
        {

        if (transaction.date.substr(0, 7) == monthYear)
            { // Check if transaction date matches the monthYear
            totalSales += transaction.totalCost;
        }
    }

    cout << "Total Sales for " << monthYear << ": $" << totalSales << endl;
}



void applyBulkDiscountByGenre(const string& genre, double discountPercentage)
{

    bool discountApplied = false;

    for (auto& product : products)
        {
        if (product->name == genre)
         { // assuming 'name' is the genre field

            product->price -= product->price * (discountPercentage / 100);

            discountApplied = true;

            cout << "Discount applied to product: " << product->name << ", New Price: " << product->price << endl;
        }
    }

    if (!discountApplied)
        {
        cout << "No products found for the specified genre.\n";
    }
}
void findProductsByPriceRange(double minPrice, double maxPrice)
 {

    cout << "\nProducts in the price range " << minPrice << " to " << maxPrice << ":\n";

    for (const auto& product : products)
        {

        if (product->price >= minPrice && product->price <= maxPrice)
            {

            cout << "ID: " << product->id

                 << ", Name: " << product->name

                 << ", Price: " << product->price

                 << ", Stock: " << product->stock << endl;
        }
    }
}
void deleteCustomerById(const string& customerId)
 {

    auto it = find_if(customers.begin(), customers.end(), [&](Customer* c)
                      {

        return c->id == customerId;
    });

    if (it != customers.end())
        {

        delete *it;  // Free allocated memory

        customers.erase(it);

        cout << "Customer with ID " << customerId << " deleted successfully.\n";
    }
    else
        {
        cout << "Customer with ID " << customerId << " not found.\n";
    }
}
void generateInventorySummary()
{

    cout << "\n--- Inventory Summary ---\n";

    for (const auto& product : products)
        {

        cout << "Product ID: " << product->id

             << ", Name: " << product->name

             << ", Stock: " << product->stock

             << ", Price: " << product->price << endl;
    }
}
void sendLoyaltyRewards(int topN)
 {
    if (topN > customers.size())
        {
        cout << "The number of top customers exceeds the total number of customers.\n";
        return;
    }

    // Sort customers by loyalty points in descending order
    vector<Customer*> sortedCustomers = customers;

    sort(sortedCustomers.begin(), sortedCustomers.end(), [](Customer* a, Customer* b)
          {

        return a->loyaltyPoints > b->loyaltyPoints;
    });

    cout << "\n--- Sending Loyalty Rewards to Top " << topN << " Customers ---\n";

    for (int i = 0; i < topN; ++i)
        {
        cout << "Customer ID: " << sortedCustomers[i]->id

             << ", Name: " << sortedCustomers[i]->name

             << ", Loyalty Points: " << sortedCustomers[i]->loyaltyPoints << endl;
    }
}








void productByIdOrName(const string& query)
 {

    bool found = false;

    for (const auto& product : products)
        {

        if (product->id == query || product->name == query)
            {

            cout << "Product ID: " << product->id

                 << ", Name: " << product->name

                 << ", Stock: " << product->stock

                 << ", Price: " << product->price << endl;
            found = true;
        }
    }
    if (!found)
        {
        cout << "Product not found.\n";
    }
}
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <ctime>

// Define the Supplier class to store supplier information


class Supplier

{
private:

    std::string supplierName;
    std::string supplierID;
    std::string contactPerson;
    std::string contactNumber;
    std::string address;

public:

    // Constructor to initialize supplier details

    Supplier(std::string name, std::string id, std::string contact, std::string number, std::string addr)

        : supplierName(name), supplierID(id), contactPerson(contact), contactNumber(number), address(addr) {}

    // Getter functions

    std::string getSupplierName() const { return supplierName; }

    std::string getSupplierID() const { return supplierID; }

    std::string getContactPerson() const { return contactPerson; }

    std::string getContactNumber() const { return contactNumber; }

    std::string getAddress() const { return address; }

    // Setter functions
    void setSupplierName(std::string name) { supplierName = name; }

    void setSupplierID(std::string id) { supplierID = id; }

    void setContactPerson(std::string contact) { contactPerson = contact; }

    void setContactNumber(std::string number) { contactNumber = number; }

    void setAddress(std::string addr) { address = addr; }

    // Display supplier information

    void displaySupplierInfo() const {

        std::cout << "Supplier ID: " << supplierID << std::endl;

        std::cout << "Supplier Name: " << supplierName << std::endl;

        std::cout << "Contact Person: " << contactPerson << std::endl;

        std::cout << "Contact Number: " << contactNumber << std::endl;

        std::cout << "Address: " << address << std::endl;
    }
};

// Define the Book class to store book information

class Book
 {
private:

    std::string title;
    std::string author;
    std::string bookID;
    double price;

public:

    // Constructor to initialize book details

    Book(std::string t, std::string a, std::string id, double p) : title(t), author(a), bookID(id), price(p) {}

    // Getter functions

    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getBookID() const { return bookID; }
    double getPrice() const { return price; }

    // Setter function for price

    void setPrice(double p) { price = p; }

    // Display book information

    void displayBookInfo() const
    {
        std::cout << "Book ID: " << bookID << std::endl;
        std::cout << "Title: " << title << std::endl;
        std::cout << "Author: " << author << std::endl;
        std::cout << "Price: $" << price << std::endl;
    }
};

// Define the Order class to store order information

class Order
{
private:
    std::string orderID;
    std::string supplierID;
    std::vector<Book> orderedBooks;
    std::time_t orderDate;
    bool isShipped;

public:

    // Constructor to initialize order details

    Order(std::string order_id, std::string supplier_id, std::vector<Book> books)
        : orderID(order_id), supplierID(supplier_id), orderedBooks(books), isShipped(false)
        {

        orderDate = std::time(nullptr);

         // Capture current time as order date

    }


    // Display order information

    void displayOrderInfo() const
     {
        std::cout << "Order ID: " << orderID << std::endl;
        std::cout << "Supplier ID: " << supplierID << std::endl;
        std::cout << "Order Date: " << std::ctime(&orderDate);
         // Print time in readable format

        std::cout << "Order Status: " << (isShipped ? "Shipped" : "Pending") << std::endl;
        std::cout << "Books Ordered: " << std::endl;
        for (const auto& book : orderedBooks)
            {

            book.displayBookInfo();
            std::cout << "---------------------------------" << std::endl;
        }

    }


    // Mark the order as shipped



    void markAsShipped()
    {

        isShipped = true;
    }


    // Check if the order is shipped


    bool isOrderShipped() const
    {

        return isShipped;

    }

    // Getter functions


    std::string getOrderID() const
    {

        return orderID;

    }

    std::string getSupplierID() const
    {

        return supplierID;

    }

    // Function to update the price of a book in the order


    void updateBookPrice(std::string bookID, double newPrice)
    {

        for (auto& book : orderedBooks)
            {

            if (book.getBookID() == bookID)
            {

                book.setPrice(newPrice);
                std::cout << "Book price updated successfully.\n";
                return;

            }
        }


        std::cout << "Book with ID " << bookID << " not found in the order.\n";

    }

    // Function to remove a book from the order

    void removeBookFromOrder(std::string bookID)
    {

        for (auto it = orderedBooks.begin(); it != orderedBooks.end(); ++it)
            {

            if (it->getBookID() == bookID)


                {

                orderedBooks.erase(it);
                std::cout << "Book removed from order successfully.\n";
                return;
            }



        }
        std::cout << "Book with ID " << bookID << " not found in the order.\n";

    }

};


// Define the SupplierManagementSystem class to manage suppliers and orders

class SupplierManagementSystem
{

private:
    std::vector<Supplier> suppliers;
    std::vector<Order> orders;

public:

    // Function to add a new supplier

    void addSupplier()
    {
        std::string name, id, contact, number, address;

        std::cout << "Enter Supplier Name: ";
        std::getline(std::cin, name);
        std::cout << "Enter Supplier ID: ";
        std::getline(std::cin, id);
        std::cout << "Enter Contact Person: ";
        std::getline(std::cin, contact);
        std::cout << "Enter Contact Number: ";
        std::getline(std::cin, number);
        std::cout << "Enter Address: ";
        std::getline(std::cin, address);

        suppliers.push_back(Supplier(name, id, contact, number, address));
        std::cout << "Supplier added successfully!\n";

    }

    // Function to edit an existing supplier

    void editSupplier()

    {

        std::string id;
        std::cout << "Enter the Supplier ID to edit: ";
        std::getline(std::cin, id);

        for (auto& supplier : suppliers)

            {

            if (supplier.getSupplierID() == id)
            {

                std::string name, contact, number, address;
                std::cout << "Enter new Supplier Name: ";
                std::getline(std::cin, name);
                supplier.setSupplierName(name);
                std::cout << "Enter new Contact Person: ";
                std::getline(std::cin, contact);
                supplier.setContactPerson(contact);
                std::cout << "Enter new Contact Number: ";
                std::getline(std::cin, number);
                supplier.setContactNumber(number);
                std::cout << "Enter new Address: ";
                std::getline(std::cin, address);
                supplier.setAddress(address);

                std::cout << "Supplier details updated successfully!\n";
                 return;

             }
         }
         std::cout << "Supplier with ID " << id << " not found.\n";

    }


    // Function to delete a supplier

    void deleteSupplier()
     {

        std::string id;
        std::cout << "Enter the Supplier ID to delete: ";
        std::getline(std::cin, id);


        for (auto it = suppliers.begin(); it != suppliers.end(); ++it)
            {

            if (it->getSupplierID() == id)
                {

                suppliers.erase(it);
                std::cout << "Supplier deleted successfully!\n";

                return;
            }

        }
        std::cout << "Supplier with ID " << id << " not found.\n";
    }

    // Function to display all suppliers

    void displayAllSuppliers() const
    {

        if (suppliers.empty())
            {

            std::cout << "No suppliers found.\n";
        }

        else
        {

            for (const auto& supplier : suppliers)
                {

                supplier.displaySupplierInfo();
                std::cout << "--------------------------------\n";
            }


        }
    }

    // Function to search for a supplier by ID

    void searchSupplierByID() const
    {

        std::string id;
        std::cout << "Enter the Supplier ID to search: ";
        std::getline(std::cin, id);

        for (const auto& supplier : suppliers)
         {

            if (supplier.getSupplierID() == id)

                {
                supplier.displaySupplierInfo();
                return;

            }
        }

        std::cout << "Supplier with ID " << id << " not found.\n";
    }

    // Function to place an order

    void placeOrder() {
        std::string orderID, supplierID;
        int numBooks;

        std::cout << "Enter Order ID: ";
        std::getline(std::cin, orderID);
        std::cout << "Enter Supplier ID: ";
        std::getline(std::cin, supplierID);

        std::vector<Book> books;
        std::cout << "Enter number of books to order: ";
        std::cin >> numBooks;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

          // Clear input buffer

        for (int i = 0; i < numBooks; ++i)
            {

            std::string title, author, bookID;
            double price;
            std::cout << "Enter Book " << i + 1 << " Title: ";
            std::getline(std::cin, title);
            std::cout << "Enter Book " << i + 1 << " Author: ";
            std::getline(std::cin, author);
            std::cout << "Enter Book " << i + 1 << " ID: ";
            std::getline(std::cin, bookID);
            std::cout << "Enter Book " << i + 1 << " Price: ";
            std::cin >> price;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

             // Clear input buffer


            books.push_back(Book(title, author, bookID, price));

        }

        orders.push_back(Order(orderID, supplierID, books));

        std::cout << "Order placed successfully!\n";

    }


    // Function to view all orders

    void viewOrders() const
    {

        if (orders.empty())

            {

        std::cout << "No orders found.\n";

        }

         else

        {

            for (const auto& order : orders)
                {

                order.displayOrderInfo();
                std::cout << "--------------------------------\n";


            }

        }


    }

    // Function to view a specific order by ID

    void viewOrderByID() const

    {

        std::string orderID;
        std::cout << "Enter the Order ID to view: ";
        std::getline(std::cin, orderID);

        for (const auto& order : orders)
         {

            if (order.getOrderID() == orderID)

                {

                order.displayOrderInfo();
                return;
            }

        }

        std::cout << "Order with ID " << orderID << " not found.\n";

    }

    // Function to update the price of a book in an order

    void updateOrderBookPrice()

    {
        std::string orderID, bookID;
        double newPrice;

        std::cout << "Enter the Order ID: ";
        std::getline(std::cin, orderID);
        std::cout << "Enter the Book ID: ";
        std::getline(std::cin, bookID);
        std::cout << "Enter the new price: ";
        std::cin >> newPrice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Clear input buffer

        for (auto& order : orders)
            {

            if (order.getOrderID() == orderID)

            {

                order.updateBookPrice(bookID, newPrice);
                return;

            }
        }

        std::cout << "Order with ID " << orderID << " not found.\n";
    }

    // Function to remove a book from an order

    void removeBookFromOrder()
    {

        std::string orderID, bookID;

        std::cout << "Enter the Order ID: ";
        std::getline(std::cin, orderID);
        std::cout << "Enter the Book ID to remove: ";
        std::getline(std::cin, bookID);

        for (auto& order : orders)
        {

            if (order.getOrderID() == orderID)

                {

                order.removeBookFromOrder(bookID);
                return;

            }

        }

        std::cout << "Order with ID " << orderID << " not found.\n";

    }

    // Function to mark an order as shipped


    void markOrderAsShipped()
    {

        std::string orderID;
        std::cout << "Enter the Order ID to mark as shipped: ";
        std::getline(std::cin, orderID);

        for (auto& order : orders)

            {

            if (order.getOrderID() == orderID && !order.isOrderShipped())
            {

                order.markAsShipped();
                std::cout << "Order marked as shipped.\n";
                return;

            }
        }

        std::cout << "Order with ID " << orderID << " not found or already shipped.\n";

    }

};
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<fstream>
#include<iomanip>
using namespace std;

const int Salary=10000;
int Comission=0;
string EmployeeID;

///-------------------------------------------Class Bookshop--------------------------------------------------------------------
class BookShop
{
    string BookName,AuthorName,BookId,Copy,Price;
public:
    void Add(),Edit(),Delete(),ShowAllBook(),SecondMenu(),SellBook(),EditStock(string,int),ShowBusiness(),ShowBalance();
    void Business(string,string,string,int,int);
    int CheckSpace(string),CheckInteger(string),CheckId(string),CheckBookAuthorName(string,string);
    void AddcomiSSion(int);
};
///--------------------------------------------Class Employee--------------------------------------------------------------------

class Employee: public BookShop
{
    string EmployeeName,EmployeePassword,GetEmployeeId;
    static string EmployeeId;
public:
    Employee();
    void SignIn(),SignUp(),ForgotIDPassword();
    friend void AddcmoSSion();
    int EmployeeCheckId(string);
};
///-----------------------------------------------  Static Declare-----------------------------------------------------------

string Employee ::EmployeeId;

///----------------------------------------------Add Book---------------------------------------------------------------------


void BookShop :: Add()
{
    system("CLS");

    string Choice;

    cout<<"Do You Want To add book ? \n\n";

    cout<<"\n\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~|";
    cout<<"\n\t\t\t| (1) Yes                   |";
    cout<<"\n\t\t\t| (2) No                    |";
    cout<<"\n\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~|";

    cout<<"\n\nEnter Your choice : ";
    getline(cin,Choice);

    try
    {
        if(Choice.length()>1)
            throw 6.0;
        else if(Choice.at(0)=='1')
        {
            try
            {
                system("CLS");
                cout<<"Note : Please Dont Use Space \n";
                cout<<"       You Can Use _(Under Score) instead of space \n";

                cout<<"\nEnter Book Id : ";
                getline(cin,BookId);
                int z=CheckId(BookId);
                if(z==1)
                {
                    cout<<"This Id is Already Exist \n\n";
                    system("pause");
                    Add();
                }
                int a=CheckSpace(BookId);
                if(a==1)
                    throw 99;

                cout<<"\nEnter Book Name : ";
                getline(cin,BookName);
                int b=CheckSpace(BookName);
                if(b==1)
                    throw 99;

                cout<<"\nEnter Author Name : ";
                getline(cin,AuthorName);
                int c=CheckSpace(AuthorName);
                if(c==1)
                    throw 99;

                int m=CheckBookAuthorName(BookName,AuthorName);

                if(m==1)
                {
                    cout<<"\nThis Book and author already exist\n\n";
                    system("pause");
                    Add();
                }


                cout<<"\nEnter How Much Copy Of This Book You Want To Add : ";
                getline(cin,Copy);
                int e=CheckInteger(Copy);
                if(e==0)
                    throw 'x';

                cout<<"\nEnter Price Of Every Piece : ";
                getline(cin,Price);
                int f=CheckInteger(Price);
                if(f==0)
                    throw 'y';


                ofstream Write("BookShop.txt",ios::app);
                Write<<BookId<<"\t\t"<<BookName<<"\t\t"<<AuthorName<<"\t\t"<<Copy<<"\t\t"<<Price<<endl;
                Write.close();


                cout<<"\nYour Book Is Succesfully Added \n\n";
                system("pause");

                SecondMenu();

            }

            catch(int n)
            {
                cout<<"\n\nPlease Dont Use Space \n";
                cout<<"You Can Use _(Under Score) instead of space \n\n\n";
                system("pause");
                Add();
            }

            catch(char f)
            {
                cout<<"\nPlease Input Integer Number \n\n";
                system("pause");
                Add();
            }

        }

        else if(Choice.at(0)=='2')
            SecondMenu();
        else
            throw "gh";
    }

    catch(...)
    {
        cout<<"\nInvalid Input \n\n";
        system("pause");
        Add();
    }

}
///---------------------------------------------------Edit Book-----------------------------------------------------------------

void BookShop :: Edit()
{
    system("CLS");

    string EditBookName,EditAuthorName,EditBookId,EditCopy,EditPrice;

    string Choice;

    cout<<"Do You Want To Edit book ? \n\n";

    cout<<"\n\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~|";
    cout<<"\n\t\t\t| (1) Yes                   |";
    cout<<"\n\t\t\t| (2) No                    |";
    cout<<"\n\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~|";

    cout<<"\n\nEnter Your choice : ";
    getline(cin,Choice);

    try
    {
        if(Choice.length()>1)
            throw 6.0;
        else if(Choice.at(0)=='1')
        {
            try
            {
                system("CLS");

                string EditId;
                cout<<"\nEnter Book ID : ";
                getline(cin,EditId);
                int y=CheckSpace(EditId);
                if(y==1)
                    throw 99;
                int Check=CheckId(EditId);
                if(Check==0)
                {
                    cout<<"\nSorry No Such Id Exist \n";
                    system("pause");
                    Edit();
                }
                int a=CheckSpace(EditId);
                if(a==1)
                    throw 99;

                system("cls");

                cout<<"Note : Please Dont Use Space \n";
                cout<<"       You Can Use _(Under Score) instead of space \n";

                cout<<"\nEnter New Book Id : ";
                getline(cin,EditBookId);
                int z=CheckId(EditBookId);
                if(z==1)
                {
                    cout<<"This Id is Already Exist \n\n";
                    system("pause");
                    Edit();
                }
                int w=CheckSpace(EditBookId);
                if(w==1)
                    throw 99;


                cout<<"\nEnter New Book Name : ";
                getline(cin,EditBookName);
                int b=CheckSpace(EditBookName);
                if(b==1)
                    throw 99;

                cout<<"\nEnter New Author Name : ";
                getline(cin,EditAuthorName);
                int c=CheckSpace(EditAuthorName);
                if(c==1)
                    throw 99;



                cout<<"\nEnter How Much Copy Of This Book You Want To Add : ";
                getline(cin,EditCopy);
                int e=CheckInteger(EditCopy);
                if(e==0)
                    throw 'x';

                cout<<"\nEnter Price Of Every Piece : ";
                getline(cin,EditPrice);
                int f=CheckInteger(EditPrice);
                if(f==0)
                    throw 'y';



                ofstream Write("BookShop2.txt");
                ifstream Read("BookShop.txt");

                if(Read)
                {
                    while(Read>>BookId>>BookName>>AuthorName>>Copy>>Price)
                    {
                        if(EditId==BookId)
                        {
                            Write<<EditBookId<<"\t\t"<<EditBookName<<"\t\t"<<EditAuthorName<<"\t\t"<<EditCopy<<"\t\t"<<EditPrice<<endl;
                            continue;
                        }

                        Write<<BookId<<"\t\t"<<BookName<<"\t\t"<<AuthorName<<"\t\t"<<Copy<<"\t\t"<<Price<<endl;

                    }

                    Read.close();
                    Write.close();

                    remove("BookShop.txt");
                    rename("BookShop2.txt","BookShop.txt");
                }
                Read.close();
                Write.close();

                cout<<"\nYour Book Is Succesfully Edited \n\n";
                system("pause");

                SecondMenu();

            }

            catch(int n)
            {
                cout<<"\n\nPlease Dont Use Space \n";
                cout<<"You Can Use _(Under Score) instead of space \n\n\n";
                system("pause");
                Edit();
            }

            catch(char f)
            {
                cout<<"\nPlease Input Integer Number \n\n";
                system("pause");
                Edit();
            }

        }

        else if(Choice.at(0)=='2')
            SecondMenu();
        else
            throw "gh";
    }

    catch(...)
    {
        cout<<"\nInvalid Input \n\n";
        system("pause");
        Edit();
    }
}
///------------------------------------------------Delete Book------------------------------------------------------------------

void BookShop :: Delete()
{
    system("CLS");

    string Choice;

    cout<<"Do You Want To Delete book ? \n\n";

    cout<<"\n\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~|";
    cout<<"\n\t\t\t| (1) Yes                   |";
    cout<<"\n\t\t\t| (2) No                    |";
    cout<<"\n\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~|";

    cout<<"\n\nEnter Your choice : ";
    getline(cin,Choice);

    try
    {
        if(Choice.length()>1)
            throw 6.0;
        else if(Choice.at(0)=='1')
        {
            try
            {
                system("CLS");

                string EditId;
                cout<<"\nEnter Book ID : ";
                getline(cin,EditId);
                int y=CheckSpace(EditId);
                if(y==1)
                    throw 99;
                int Check=CheckId(EditId);
                if(Check==0)
                {
                    cout<<"\nSorry No Such Id Exist \n";
                    system("pause");
                    Delete();
                }
                int a=CheckSpace(EditId);
                if(a==1)
                    throw 99;

                system("cls");

                ofstream Write("BookShop2.txt");
                ifstream Read("BookShop.txt");

                if(Read)
                {
                    while(Read>>BookId>>BookName>>AuthorName>>Copy>>Price)
                    {
                        if(EditId==BookId)
                        {
                            continue;
                        }

                        Write<<BookId<<"\t\t"<<BookName<<"\t\t"<<AuthorName<<"\t\t"<<Copy<<"\t\t"<<Price<<endl;

                    }
                }
                else
                    cout<<"File Not Found";

                Read.close();
                Write.close();

                remove("BookShop.txt");
                rename("BookShop2.txt","BookShop.txt");

                cout<<"\nYour Book Is Succesfully Deleted \n\n";
                system("pause");

                SecondMenu();

            }

            catch(int n)
            {
                cout<<"\n\nPlease Dont Use Space \n";
                cout<<"You Can Use _(Under Score) instead of space \n\n\n";
                system("pause");
                Delete();
            }

            catch(char f)
            {
                cout<<"\nPlease Input Integer Number \n\n";
                system("pause");
                Delete();
            }

        }

        else if(Choice.at(0)=='2')
            SecondMenu();
        else
            throw "gh";
    }

    catch(...)
    {
        cout<<"\nInvalid Input \n\n";
        system("pause");
        Delete();
    }
}

///---------------------------------------------Show All Book------------------------------------------------------------------
void BookShop :: ShowAllBook()
{

    system("cls");
    cout<<"|~~~~~~~~~~~|~~~~~~~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~~~~~~~~|~~~~~~~~~~~|~~~~~~~~|\n";
    cout<<"|Id         | Book Name             | Author Name          | Copy      | Price  |\n";
    cout<<"|~~~~~~~~~~~|~~~~~~~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~~~~~~~~|~~~~~~~~~~~|~~~~~~~~|\n";

    ifstream Read("BookShop.txt");

    if(Read)
    {
        while(Read>>BookId>>BookName>>AuthorName>>Copy>>Price)
        {
            cout<<setiosflags(ios::left)<<setw(13)<<BookId<<setw(25)<<BookName<<setw(22)<<AuthorName<<setw(14)<<Copy<<setw(14)<<Price<<endl;
        }
        Read.close();
    }
    Read.close();

    system("pause");
    SecondMenu();
}
///-----------------------------------------------Bookshop Menu---------------------------------------------------------------------
void BookShop :: SecondMenu()
{
    string Choice;

    while(1)
    {
        system("CLS");

        cout<<"\n\n\t\t\t|~~~~~~~~~Menu~~~~~~~~~~~~~~|";
        cout<<"\n\t\t\t| (1) Sell Book             |";
        cout<<"\n\t\t\t| (2) Add Book              |";
        cout<<"\n\t\t\t| (3) Delete Book           |";
        cout<<"\n\t\t\t| (4) Edit Book             |";
        cout<<"\n\t\t\t| (5) Show All Book List    |";
        cout<<"\n\t\t\t| (6) Show Balance          |";
        cout<<"\n\t\t\t| (7) Show My Sold List     |";
        cout<<"\n\t\t\t| (8) Logout                |";
        cout<<"\n\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~|";

        cout<<"\n\nEnter Your choice : ";
        getline(cin,Choice);

        try
        {
            if(Choice.length()>1)
                throw 99;
            else if(Choice.at(0)=='1')
            {
                SellBook();
                system("pause");
            }

            else if(Choice.at(0)=='2')
            {
                Add();
                system("pause");
            }


            else if(Choice.at(0)=='3')
            {
                Delete();
                system("pause");
            }


            else if(Choice.at(0)=='4')
            {
                Edit();
                system("pause");
            }


            else if(Choice.at(0)=='5')
            {
                ShowAllBook();
                system("pause");
            }


            else if(Choice.at(0)=='6')
            {
                ShowBalance();
                system("pause");
            }


            else if(Choice.at(0)=='7')
            {
                ShowBusiness();
                system("pause");
            }


            else if(Choice.at(0)=='8')
            {
                cout<<"You Logged Out Successfully \n\n";
                system("pause");
                Employee();
            }

            else
            {
                throw 65;
            }
        }

        catch(...)
        {
            cout<<"Invalid Input \n\n";
            system("pause");
            system("CLS");

        }
    }
}
///-------------------------------------------Function For Check space------------------------------------------------------------

int BookShop :: CheckSpace(string Check)
{
    int c=0;
    for(int i=0; i<Check.length(); i++)
    {
        if(Check.at(i)==' ')
            return 1;
    }
    return 0; // Added return statement
}

///----------------------------------------Function For Check Integer-----------------------------------------------------------
int BookShop :: CheckInteger(string Check)
{
    int f=0;
    for(int i=0; i<Check.length(); i++)
    {
        if(Check.at(i)>='1' && Check.at(i)<='9')
            f++;
    }

    if(f>=1)
        return 1;
    else
        return 0;
}

///----------------------------------------Function For Check Id------------------------------------------------------------

int BookShop :: CheckId(string ID)
{
    string CheckBookId;
    int c=0;
    ifstream Read("BookShop.txt");
    if(Read)
    {
        while(Read>>CheckBookId>>BookName>>AuthorName>>Copy>>Price)
        {
            if(CheckBookId==ID)
            {
                c++;
            }
        }

        if(c>=1)
        {
            Read.close();
            return 1;
        }
        else
        {
            Read.close();
            return 0;
        }
    }
    else
    {
        Read.close();
        cout << "File not found"; // Fixed operator here
    }
    return 0;
}


///------------------------------------------------Employee Menu----------------------------------------------------------------

Employee ::Employee()
{
    string Choice;

    while(1)
    {
        system("CLS");
        system("COLOR 70");

        cout<<"\n\n\t\t\t|~~~~~~~~~Menu~~~~~~~~~~~~~~~~|";
        cout<<"\n\t\t\t| (1) Sign In                 |";
        cout<<"\n\t\t\t| (2) Sign Up                 |";
        cout<<"\n\t\t\t| (3) Forgot Id/Password      |";
        cout<<"\n\t\t\t| (4) Exit                    |";
        cout<<"\n\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|";

        cout<<"\n\nEnter Your choice : ";
        getline(cin,Choice);

        try
        {
            if(Choice.length()>1)
                throw 99;
            else if(Choice.at(0)=='1')
            {
                SignIn();
                system("pause");
            }
            else if(Choice.at(0)=='2')
            {
                SignUp();
                system("pause");
            }
            else if(Choice.at(0)=='3')
            {
                ForgotIDPassword();
                system("pause");
            }
            else if(Choice.at(0)=='4')
            {
                cout<<"Thanks For Using This Software \n\n";
                exit(0);
                system("pause");
            }
            else
            {
                throw 65;
            }
        }
        catch(...)
        {
            cout<<"Invalid Input \n\n";
            system("pause");
            system("CLS");
        }
    }
}
///---------------------------------------------------Sign Up-------------------------------------------------------------------

void Employee :: SignUp()
{
    system("cls");
    try
    {
        cout<<"Enter Id : ";
        getline(cin,EmployeeId);
        int z=EmployeeCheckId(EmployeeId);
        if(z==1)
        {
            cout<<"This Id is Already Exist \n";
            cout<<"\nPlz Try Again \n\n";
            system("pause");
            Employee();
        }
        int a=CheckSpace(EmployeeId);
        if(a==1)
            throw 99;
        cout<<"Enter Name : ";
        getline(cin,EmployeeName);
        int b=CheckSpace(EmployeeName);
        if(b==1)
            throw 99;
        cout<<"Enter Password : ";
        getline(cin,EmployeePassword);
        int c=CheckSpace(EmployeePassword);
        if(c==1)
            throw 99;
    }
    catch(int a)
    {
        cout<<"\n\nPlease Dont Use Space \n";
        cout<<"You Can Use _(Under Score) instead of space \n";
        cout<<"\nPlz Try Again \n\n";
        system("pause");
        Employee();
    }


    ofstream Write("login.txt",ios::app);
    Write<<EmployeeId<<"\t\t"<<EmployeeName<<"\t\t"<<EmployeePassword<<"\t\t"<<Salary<<"\t\t"<<Comission<<endl;
    cout<<"\nSign Up Success \n";
    Write.close();
    system("pause");
    SecondMenu();
}

///---------------------------------------------Sign In------------------------------------------------------------------------

void Employee :: SignIn()
{

    string SignInId,SignInPassword,Balance,ComiSSion;
    int c=0;

    system("cls");
    try
    {
        cout<<"Enter Your Id  : ";
        getline(cin,EmployeeId);
        int a=CheckSpace(EmployeeId);
        if(a==1)
            throw 99;

        EmployeeID=EmployeeId;
        cout<<"Enter Password : ";
        getline(cin,EmployeePassword);
        int b=CheckSpace(EmployeePassword);
        if(b==1)
            throw 99;
    }
    catch(int a)
    {
        cout<<"\n\nPlease Dont Use Space \n";
        cout<<"You Can Use _(Under Score) instead of space \n";
        cout<<"Please Try Again \n\n";
        system("pause");
        Employee();
    }

    ifstream Read("login.txt");

    if(Read)
    {
        while(Read>>SignInId>>EmployeeName>>SignInPassword>>Balance>>ComiSSion)
        {
            if(EmployeeId==SignInId && EmployeePassword==SignInPassword)
            {
                cout<<"\nWelcome, Mr "<<EmployeeName<<". . ."<<endl;
                cout<<"You successfully signed in in your account \n\n";
                Read.close();
                system("pause");
                SecondMenu();
                c++;
            }
        }
        if(c==0)
        {
            cout<<"\nYour Name or Password is wrong \n\n";
            system("pause");
            Employee();
        }
        Read.close();
    }
    else
    {
        Read.close();
        cout<<"\nUser Not Found \n\n";
        system("pause");
        Employee();
    }
}
///-----------------------------------------Forgot ID/Password-----------------------------------------------------------------
void Employee ::ForgotIDPassword()
{
    string Choice;
    int c=0;

    system("CLs");

    cout<<"Which One You Forgot ? \n\n";
    cout<<"\n\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~|";
    cout<<"\n\t\t\t| (1) ID                    |";
    cout<<"\n\t\t\t| (2) Password              |";
    cout<<"\n\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~|";

    cout<<"\n\nEnter Your choice : ";
    getline(cin,Choice);

    try
    {
        if(Choice.length()>1)
            throw 6.0;
        else if(Choice.at(0)=='1')
        {
            string password;
            system("CLS");
            cout<<"Enter Your Password : ";
            getline(cin,password);
            int a =CheckSpace(password);
            if(a==1)
            {
                cout<<"\n\nPlease Dont Use Space For Recover \n";
                cout<<"\nPlz Try again \n\n";
                system("pause");
                Employee();

            }
            ifstream Read("login.txt");

            if(Read)
            {
                while(Read>>EmployeeId>>EmployeeName>>EmployeePassword)
                {
                    if(EmployeePassword==password)
                    {
                        cout<<"Your ID is : "<<EmployeeId<<endl;
                        system("pause");
                        Read.close();
                        Employee();
                        c++;
                    }
                }

                if(c==0)
                {
                    system("CLS");
                    cout<<"Your Password is wrong "<<endl;
                    system("pause");
                    Read.close();
                    Employee();
                }
            }
            else
            {
                Read.close();
                system("CLS");
                cout<<"ID not found "<<endl;
                system("pause");
                Employee();
            }

        }

        else if(Choice.at(0)=='2')
        {
            string ID;
            system("CLS");
            cout<<"Enter Your ID : ";
            getline(cin,ID);
            int a =CheckSpace(ID);
            if(a==1)
            {
                cout<<"\n\nPlease Dont Use Space For Recover \n";
                cout<<"\nPlz Try again \n\n";
                system("pause");
                Employee();

            }

            ifstream Read("login.txt");

            if(Read)
            {
                while(Read>>EmployeeId>>EmployeeName>>EmployeePassword)
                {
                    if(EmployeeId==ID)
                    {
                        cout<<"Your Password is : "<<EmployeePassword<<endl;
                        system("pause");
                        Read.close();
                        Employee();
                        c++;
                    }
                }

                if(c==0)
                {
                    system("CLS");
                    cout<<"Your ID is wrong "<<endl;
                    Read.close();
                    system("pause");
                    Employee();
                }
            }
            else
            {
                Read.close();
                system("CLS");
                cout<<"ID not found "<<endl;
                system("pause");
                Employee();
            }


        }

        else
            throw "gh";
    }

    catch(...)
    {
        cout<<"\nInvalid Input \n\n";
        system("pause");
        Employee();
    }
}
///--------------------------------------------------Employee Id Check-----------------------------------------------------------

int Employee ::EmployeeCheckId(string ID)
{
    ifstream Read("login.txt");
    if(Read)
    {
        string Balance,ComiSSion;
        string EmpLoyeeId;

        while(Read>>EmpLoyeeId>>EmployeeName>>EmployeePassword>>Balance>>ComiSSion)
        {
            if(ID==EmpLoyeeId)
            {
                Read.close();
                return 1;
            }
        }
        Read.close();
        return 0;
    }
    else
    {
        Read.close();
        return 0;
    }

}

///----------------------------------------------------Sell Book-------------------------------------------------------------------
void BookShop ::SellBook()
{
    string Bookname,Authorname;

    int Piece,price,c=0,stock;

    try
    {
        system("CLS");
        cout<<"Note : Please Dont Use Space \n";

        cout<<"       You Can Use _(Under Score) instead of space \n";


        cout<<"\nEnter Book Name : ";
        getline(cin,BookName);
        int b=CheckSpace(BookName);
        if(b==1)
            throw 99;

        cout<<"\nEnter Author Name : ";
        getline(cin,AuthorName);
        int c=CheckSpace(AuthorName);
        if(c==1)
            throw 99;

    }


    catch(int n)
    {
        cout<<"\n\nPlease Dont Use Space \n";
        cout<<"You Can Use _(Under Score) instead of space \nPlease Try again \n\n";
        system("pause");
        SecondMenu();
    }

    ifstream Read("BookShop.txt");
    if(Read)
    {
        while(Read>>BookId>>Bookname>>Authorname>>stock>>price)
        {
            if(BookName==Bookname && AuthorName==Authorname)
            {
                c++;
                cout<<"\nYes, We have "<<stock<<" copy of it "<<endl<<"Price of each piece is : "<<price<<"TK"<<endl;
                cout<<endl<<"How much piece you need ? : ";
                cin>>Piece;
                cin.ignore();
                if(Piece<=stock)
                {
                    int ComIssIon=(Piece*price*5)/100;
                    int Pay=Piece*price;

                    cout<<"\nYou Need to paid : "<<Pay<<"TK\n\n"<<endl;

                    Read.close();

                    system("pause");
                    system("CLS");

                    cout<<"Do You Want to Buy ???";

                    string Choice;

                    cout<<"\n\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~|";
                    cout<<"\n\t\t\t| (1) Yes                   |";
                    cout<<"\n\t\t\t| (2) No                    |";
                    cout<<"\n\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~|";

                    cout<<"\n\nEnter Your choice : ";
                    getline(cin,Choice);

                    try
                    {
                        if(Choice.length()>1)
                            throw 6.0;
                        else if(Choice.at(0)=='1')
                        {

                            cout<<"\nThanks for Buy This Book From our shop \n\n";

                            Business(BookId,Bookname,Authorname,Piece,Pay);
                            EditStock(BookId,Piece);
                            AddcomiSSion(ComIssIon);

                            system("pause");
                            SecondMenu();

                        }

                        else if(Choice.at(0)=='2')
                        {
                            system("pause");
                            SecondMenu();
                        }

                        else
                            throw "gh";
                    }

                    catch(...)
                    {
                        cout<<"\nInvalid Input \n\n";
                        system("pause");
                        Delete();
                    }

                    c++;

                    system("pause");
                    SecondMenu();

                }
                else
                {
                    cout<<"Sorry, Required copy not in stock \n";
                    Read.close();
                    system("pause");
                    SecondMenu();
                }
            }

        }
        if(c==0)
        {
            cout<<"Sorry, We haven't this book\n";
        }
    }
    else
    {
        Read.close();
        cout<<"Sorry, File not found\n";
    }


}
///----------------------------------------------------Edit Stock--------------------------------------------------------------
/////---------------------------------------------------------------------------------
////-----------------------------------------------------------------
void BookShop ::EditStock(string ID,int PIECE)
{

    ofstream Write("BookShop2.txt");
    ifstream Read("BookShop.txt");

    int stock,Count;
    if(Read)
    {
        while(Read>>BookId>>BookName>>AuthorName>>stock>>Price)
        {
            if(ID==BookId)
            {
                Count=stock-PIECE;
                stock=Count;
            }
            Write<<BookId<<"\t\t"<<BookName<<"\t\t"<<AuthorName<<"\t\t"<<stock<<"\t\t"<<Price<<endl;
        }

        Read.close();
        Write.close();

        remove("BookShop.txt");
        rename("BookShop2.txt","BookShop.txt");
    }
    else
    {
        Read.close();
        Write.close();
    }


}

///----------------------------------------------Function For Add Comission---------------------------------------------------

void BookShop ::  AddcomiSSion(int Money)
{

    string Balance,ID,EmployeeName,EmployeePassword;
    int ComiSSion;



    ofstream write("login2.txt");
    ifstream read("login.txt");

    if(read)
    {
        while(read>>ID>>EmployeeName>>EmployeePassword>>Balance>>ComiSSion)
        {
            if(ID==EmployeeID)
            {
                ComiSSion=Money;
            }


            write<<ID<<"\t\t"<<EmployeeName<<"\t\t"<<EmployeePassword<<"\t\t"<<Salary<<"\t\t"<<ComiSSion<<endl;

        }

        write.close();
        read.close();

        char* OldName="login.txt";
        char* NewName="login2.txt";
        remove(OldName);
        rename(NewName,OldName);
    }
    else
    {
        read.close();
        write.close();
    }

}
///---------------------------------------------Todays Business-----------------------------------------------------------------

void BookShop ::Business(string Bookid,string Bookname,string Authorname,int COPY,int Money)
{
    char ID[10]= {0};
    int c=0;
    for(int i=0; i<EmployeeID.length(); i++)
    {
        ID[i]=EmployeeID[i];
    }

    strcat(ID,".txt");

    ofstream Write(ID,ios::app);

    Write<<BookId<<"\t\t"<<Bookname<<"\t\t"<<Authorname<<"\t\t"<<COPY<<"\t\t"<<Money<<endl;

    Write.close();
}

///--------------------------------------------Show Today's Business-----------------------------------------------------------

void BookShop :: ShowBusiness()
{
    system("cls");
    cout<<"|~~~~~~~~~~~|~~~~~~~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~~~~~~~~|~~~~~~~~~~~|~~~~~~~~|\n";
    cout<<"|Id         | Book Name             | Author Name          | Copy      | Price  |\n";
    cout<<"|~~~~~~~~~~~|~~~~~~~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~~~~~~~~|~~~~~~~~~~~|~~~~~~~~|\n";


    int a=EmployeeID.length();
    int c=0;
    char ID2[20]= {0};
    for(int i=0; i<a; i++)
    {
        ID2[i]=EmployeeID[i];
    }
    strcat(ID2,".txt");

    ifstream Read(ID2);
    if(Read)
    {
        if(Read.is_open())
        {
            while(Read>>BookId>>BookName>>AuthorName>>Copy>>Price)
            {
                cout<<setiosflags(ios::left)<<setw(13)<<BookId<<setw(25)<<BookName<<setw(22)<<AuthorName<<setw(14)<<Copy<<setw(14)<<Price<<endl;
            }
            Read.close();
        }
        else
        {
            Read.close();
            cout<<"Error Opening\n";

        }
    }
    else
    {
        Read.close();
        cout<<"File Not found\n";

    }

    system("pause");
    SecondMenu();
}

///-----------------------------------------------------Show Balance----------------------------------------------------------


// This is a comment explaining the logic of the following block of code.
// It does not affect the execution of the program.



void BookShop:: ShowBalance()
{
    string ID,EmployeeName,EmployeePassword;
    int Balance,ComiSSion;

    ifstream Read("login.txt");
    if(Read)
    {
        while(Read>>ID>>EmployeeName>>EmployeePassword>>Balance>>ComiSSion)
        {
            if(ID==EmployeeID)
            {
                system("cls");
                cout<<"Your Salary is             :   "<<Balance<<endl;
                cout<<"Your Comission is          :   "<<ComiSSion<<endl;
                cout<<"-------------------------------------------"<<endl;
                cout<<"Total                      :   "<<Balance+ComiSSion<<endl;
                std::cout << "Debug: Code reached this point" << std::endl; // Optional, won't affect logic

            }
        }

        Read.close();

    }
    else
    {
        Read.close();
    }

    system("pause");
    SecondMenu();
}
///------------------------------------------------Check Book and Author Name--------------------------------------------------

int BookShop::CheckBookAuthorName(string Bookname,string Authorname)
{
    ifstream Read("BookShop.txt");
    if(Read)
    {
        string CheckBookName,CheckAuthorName,stock,Price,CheckBookId;
        while(Read>>CheckBookId>>CheckBookName>>CheckAuthorName>>stock>>Price)
        {
            if(CheckBookName==Bookname && CheckAuthorName==Authorname)
            {
                Read.close();
                return 1;
            }
        }
        Read.close();
        return 0;
    }
    else
    {
        Read.close();
        return 0;
    }


}
#include<fstream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<iostream>

using namespace std;

class book
{
          char book_number[30];
          char book_name[50];
          char author_name[20];
  public:
          void create_book()
          {
                    cout<<"\nEnter The Book Number: ";
                    cin>>book_number;
                    cout<<"\nEnter The Name of The Book: ";
                     cin.ignore();
                    cin.getline(book_name,50);
                    cout<<"\nEnter The Author's Name: ";
                    cin.ignore();
                    cin.getline(author_name,50);
                    cout<<"\t\t\n\nBook Created Successfully...";
          }

          void show_book()
          {
                    cout<<"\nBook Number: "<<book_number;
                    cout<<"\nBook Name: "<<book_name;
                    cout<<"\nAuthor's Name: "<<author_name;
          }
          void modify_book()
          {
                    cout<<"\nBook number : "<<book_number;
                    cout<<"\nModify Book Name : ";
                    cin.ignore();
                    cin.getline(book_name,50);
                    cout<<"\nModify Author's Name: ";
                    cin.ignore();
                    cin.getline(author_name,50);
          }
          char* getbooknumber()
          {
                    return book_number;
          }
          void report()
          {cout<<book_number<<setw(30)<<book_name<<setw(30)<<author_name<<endl;}

};

class student
{
          char ID_number[20];
          char Student_name[20];
          char stbno[6];
          int token;
public:
          void create_student()
          {
                    cout<<"\nEnter The ID Number ";
                    cin>>ID_number;
                    cout<<"\n\nEnter The Name of The Student: ";
                    cin>>Student_name;
                    token=0;
                    stbno[0]='/0';
                    cout<<"\t\t\n\nStudent Record Created Successfully...";
          }
          void show_student()
          {
                    cout<<"\nID Number: "<<ID_number;
                    cout<<"\nStudent Name: ";
                    puts(Student_name);
                    cout<<"\nNo of Book issued: "<<token;
                    if(token==1)
                               cout<<"\nBook No "<<stbno;
          }
          void modify_student()
          {
                    cout<<"\nID Number: "<<ID_number;
                    cout<<"\nModify Student Name: ";
                    cin.ignore();
                    cin.getline(Student_name,50);
          }
          char* get_ID_number()
          {
                    return ID_number;
          }
          char* retstbno()
          {
                    return stbno;
          }
          int rettoken()
          {
                    return token;
          }
          void addtoken()
          {token=1;}
          void resettoken()
          {token=0;}
          void getstbno(char t[])
          {
                    strcpy(stbno,t);
          }
          void report()
          {cout<<"\t"<<ID_number<<setw(20)<<Student_name<<setw(10)<<token<<endl;}
};

fstream fp,fp1;
book bk;
student st;
void write_book()
{
          system("cls");
          int more_or_main;
          fp.open("book.dat",ios::out|ios::app);
          do
          {
                    bk.create_book();
                    fp.write((char*)&bk,sizeof(book));
                    cout<<"\nPress 1 to add more books.";
                    cout<<"\nPress 2 to return to main menu.\n";
                    cout<<"Enter: ";
                    cin>>more_or_main;
          }while(more_or_main == 1);
          fp.close();
}
void write_student()
{
        system("cls");
          int more_or_main;
          fp.open("student.dat",ios::out|ios::app);
          do
          {
                    st.create_student();
                    fp.write((char*)&st,sizeof(student));
                    cout<<"\nPress 1 to add more students.";
                    cout<<"\nPress 2 to return to main menu.\n";
                    cout<<"Enter: ";
                    cin>>more_or_main;
          }while(more_or_main == 1);
          fp.close();
}
void display_a_book(char n[])
{
          system("cls");
          cout<<"\nBOOK DETAILS\n";
          int check=0;
          fp.open("book.dat",ios::in);
          while(fp.read((char*)&bk,sizeof(book)))
          {
                    if(strcmpi(bk.getbooknumber(),n)==0)
                    {
                               bk.show_book();
                              check=1;
                    }
          }
          fp.close();
          if(check==0)
                    cout<<"\n\nBook does not exist";
        getch();
}
void display_a_student(char n[])
{
          system("cls");
          cout<<"\nSTUDENT DETAILS\n";
          int check=0;
          fp.open("student.dat",ios::in);
          while(fp.read((char*)&st,sizeof(student)))
          {
                    if((strcmpi(st.get_ID_number(),n)==0))
                    {
                               st.show_student();
                               check=1;
                    }
          }
          fp.close();
          if(check==0)
                    cout<<"\n\nStudent does not exist";
          getch();
}
void modify_book()
{
          system("cls");
          char n[20];
          int found=0;
          cout<<"\n\n\tMODIFY BOOK";
          cout<<"\n\n\tEnter The book number: ";
          cin>>n;
          fp.open("book.dat",ios::in|ios::out);
          while(fp.read((char*)&bk,sizeof(book)) && found==0)
          {
                    if(strcmpi(bk.getbooknumber(),n)==0)
                    {
                               bk.show_book();
                               cout<<"\nEnter The New Details of book"<<endl;
                               bk.modify_book();
                               int pos=-1*sizeof(bk);
                              fp.seekp(pos,ios::cur);
                              fp.write((char*)&bk,sizeof(book));
                              cout<<"\n\n\t Record Updated Successfully...";
                              found=1;
                    }
          }
          fp.close();
          if(found==0)
                    cout<<"\n\n Record Not Found ";
          getch();
}
void modify_student()
{
          system("cls");
          char n[20];
          int found=0;
          cout<<"\n\n\tMODIFY STUDENT RECORD... ";
          cout<<"\n\n\tEnter Student's ID number: ";
          cin>>n;
          fp.open("student.dat",ios::in|ios::out);
          while(fp.read((char*)&st,sizeof(student)) && found==0)
          {
                    if(strcmpi(st.get_ID_number(),n)==0)
                    {
                               st.show_student();
                               cout<<"\nEnter The New Details of student"<<endl;
                               st.modify_student();
                               int pos=-1*sizeof(st);
                               fp.seekp(pos,ios::cur);
                               fp.write((char*)&st,sizeof(student));
                               cout<<"\n\n\t Record Updated Successfully...";
                               found=1;
                    }
          }
          fp.close();
          if(found==0)
                    cout<<"\n\n Record Not Found ";
          getch();
}
void delete_student()
{
    int unusedVariable; // Declared but not used

          system("cls");
          char n[20];
          int flag=0;
          cout<<"\n\n\n\tDELETE STUDENT";
          cout<<"\n\nEnter The ID number of the Student You Want To Delete: ";
          cin>>n;
          fp.open("student.dat",ios::in|ios::out);
          fstream fp2;
          fp2.open("Temp.dat",ios::out);
          fp.seekg(0,ios::beg);
          while(fp.read((char*)&st,sizeof(student)))
          {
                    if(strcmpi(st.get_ID_number(),n)!=0)
                              fp2.write((char*)&st,sizeof(student));
                    else
                              flag=1;
          }
          fp2.close();
          fp.close();
          remove("student.dat");
          rename("Temp.dat","student.dat");
          if(flag==1)
                    cout<<"\n\n\tRecord Deleted ..";
          else
                    cout<<"\n\nRecord not found";
        getch();
}
void delete_book()
{
    int unusedVariable; // Declared but not used

          system("cls");
          char n[20];
          int flag=0;
          cout<<"\n\n\n\tDELETE BOOK";
          cout<<"\n\nEnter The Book's number You Want To Delete: ";
          cin>>n;
          fp.open("book.dat",ios::in|ios::out);
          fstream fp2;
          fp2.open("Temp.dat",ios::out);
          fp.seekg(0,ios::beg);
          while(fp.read((char*)&bk,sizeof(book)))
          {
                    if(strcmpi(bk.getbooknumber(),n)!=0)
                    {
                               fp2.write((char*)&bk,sizeof(book));
                    }
                    else
                              flag=1;
          }
          fp2.close();
          fp.close();
          remove("book.dat");
          rename("Temp.dat","book.dat");
          if(flag==1)
                    cout<<"\n\n\tRecord Deleted ..";
          else
                    cout<<"\n\nRecord not found";
          getch();
}
void display_all_students()
{
    int unusedVariable; // Declared but not used
    int num90;
              system("cls");
          fp.open("student.dat",ios::in);
          if(!fp)
          {
                    cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
                    getch();
                    return;
          }
          cout<<"\n\n\t\tSTUDENT LIST\n\n";
          cout<<"==================================================================\n";
          cout<<"\tID Number."<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
          cout<<"==================================================================\n";
          while(fp.read((char*)&st,sizeof(student)))
          {
                    st.report();
          }
          fp.close();
          getch();
}
void display_allb()
{
          system("cls");
          fp.open("book.dat",ios::in);
          if(!fp)
          {
                    cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
                    getch();
                    return;
          }
          cout<<"\n\n\t\tBook LIST\n\n";
         cout<<"=========================================================================\n";
          cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author\n";
          cout<<"=========================================================================\n";
          while(fp.read((char*)&bk,sizeof(book)))
          {
                    bk.report();
          }
          fp.close();
          getch();
}
void issue_book()
{
          system("cls");
          char sn[20],bn[20];
          int found=0,flag=0;
          int unusedVariable; // Declared but not used

   cout<<"\t\t\nBOOK ISSUE";
          cout<<"\n\n\tEnter student's ID number: ";
          cin>>sn;
          fp.open("student.dat",ios::in|ios::out);
          fp1.open("book.dat",ios::in|ios::out);
          while(fp.read((char*)&st,sizeof(student)) && found==0)
          {
                    if(strcmpi(st.get_ID_number(),sn)==0)
                    {
                               found=1;
                               if(st.rettoken()==0)
                               {
                                        cout<<"\n\n\tEnter book number: ";
                                         cin>>bn;
                                         while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
                                         {
                                                   if(strcmpi(bk.getbooknumber(),bn)==0)
                                                 {
                                                           bk.show_book();
                                                             flag=1;
                                                             st.addtoken();
                                                             st.getstbno(bk.getbooknumber());
                                                             int pos=-1*sizeof(st);
                                                             fp.seekp(pos,ios::cur);
                                                             fp.write((char*)&st,sizeof(student));
                                                             cout<<"\n\n\t Book issued successfully...";
                                                   }
                                        }
                                        if(flag==0)
                                                   cout<<"Book number does not exist";
                               }
                              else
                                        cout<<"You have not returned the last book ";
                    }
          }
          if(found==0)
                    cout<<"Student record not exist...";
          getch();
          system("cls");
          fp.close();
          fp1.close();
}
void book_return()
{
    system("cls");
    char sn[20],bn[20];
    int found=0, flag=0, day, fine;
    int unusedVariable; // Declared but not used

   cout<<"\t\tRETURN BOOKS\n";
    cout<<"\n\n\tEnter The student�s ID Number: ";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
       {
                       if(strcmpi(st.get_ID_number(),sn)==0)
              {
                        found=1;
                        if(st.rettoken()==1)
                        {
                               while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
                               {
                                         if(strcmpi(bk.getbooknumber(),st.retstbno())==0)
                               {
                                         bk.show_book();
                                         flag=1;
                                         cout<<"\n\nBook returned in no. of days";
                                         cin>>day;
                                         if(day>15)
                                         {
                                            fine=(day-15)*1;
                                            cout<<"\n\nThe Book is last. You have to pay a fine of  "<<fine;
                                         }
                                                   st.resettoken();
                                                   int pos=-1*sizeof(st);
                                                   fp.seekp(pos,ios::cur);
                                                   fp.write((char*)&st,sizeof(student));
                                                  cout<<"\n\n\t Book returned successfully...";
                               }
                        }
                      if(flag==0)
                        cout<<"Book number does not exist";
                          }
                     else
                               cout<<"No book is issued..please check!!";
                    }
             }
      if(found==0)
          cout<<"Student record not exist...";
          getch();
          system("cls");
  fp.close();
  fp1.close();
  }
void intro()
{
     system("color 05");
     system("cls");
  cout<<"\t\t\t\t*\t*";
  cout<<"\t\t\t\t**\t**";
   cout<<"\t\t\t\t***\t***";
   cout<<"\t\t\t\t****\t****";
   cout<<"\t\t\t\t*****\t*****";
    cout<<"\t\t\t\t******\t******";
   cout<<"\t\t\t\t*******\t*******";
   cout<<"\t\t\t\t*******\t*******";
   cout<<"\t\t\t\t******\t******";
   cout<<"\t\t\t\t*****\t*****";
   cout<<"\t\t\t\t****\t****";
   cout<<"\t\t\t\t***\t***";
   cout<<"\t\t\t\t**\t**";
   cout<<"\t\t\t\t*\t*";
}
void book_menu()
{
          int option;
            cout<<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
                cout<<"\n\t\tPress 1 to CREATE BOOKS";
                cout<<"\n\t\tPress 2 to DISPLAY ALL BOOKS";
                cout<<"\n\t\tPress 3 to DISPLAY SPECIFIC BOOK";
                cout<<"\n\t\tPress 4 to MODIFY BOOKS";
                cout<<"\n\t\tPress 5 to DELETE BOOKS";
                cout<<"\n\t\tPress 6 to GO BACK TO MAIN MENU";
 cout<<"\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
 cout<<"\n\t\tOption: ";
 cin>>option;
 switch(option)
          {
                    case 1:  system("cls");
                                         write_book();
                                                   break;
                               case 2: display_allb();
                                 break;
                    case 3:
                              char num[20];
                               system("cls");
                              cout<<"\n\n\tPlease Enter The book No. ";
                              cin>>num;
                              display_a_book(num);
                              break;
                    case 4: modify_book();break;
                    case 5: delete_book();break;
                    case 6: system("cls");
                               break;
                    default:cout<<"\a";
          }
};



// This is a no-op statement


void student_menu()
{
          int option;
          int unusedVariable; // Declared but not used

           cout<<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
                cout<<"\n\t\tPress 1 to CREATE STUDENT RECORD";
                cout<<"\n\t\tPress 2 to DISPLAY ALL STUDENTS RECORD";
                cout<<"\n\t\tPress 3 to DISPLAY SPECIFIC STUDENT RECORD";
                cout<<"\n\t\tPress 4 to MODIFY STUDENT RECORD";
                cout<<"\n\t\tPress 5 to DELETE STUDENT RECORD";
                 cout<<"\n\t\tPress 6 to GO BACK TO MAIN MENU";
 cout<<"\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
 cout<<"\n\t\tOption: ";
 cin>>option;
 switch(option)
          {
                    case 1:  system("cls");
                            write_student();
                             break;
                    case 2: system("cls");

                              display_all_students();
                            break;
                    case 3:
                              char num[20];
                               system("cls");
                        cout<<"\n\n\tPlease Enter The ID Number: ";
                              cin>>num;
                         display_a_student(num);
                              break;
                    case 4:system("cls");
                           modify_student();break;
                    case 5: system("cls");
                           delete_student();break;
                    case 6:
                               break;
                    default:cout<<"\a";
          }
}

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <cmath>
#include <map>
#include <fstream>

using namespace std;

// Structure to represent a Book in the system
struct Book2 {
    int id;

    // Unique identifier for the book

    string title;

    // Title of the book

    string author;
     // Author of the book

    string category;
    // Category of the book

    int year;
    // Publication year

    int stock;

    // Number of copies available in stock

    double price;

    // Price per unit

    int sales;

    // Total sales for the book

    vector<int> monthlySales;

     // Monthly sales data

    // Default constructor

    Book2() : id(0), title(""), author(""), category(""), year(0), stock(0), price(0.0), sales(0), monthlySales(12, 0) {}

    // Parameterized constructor to initialize book details

    Book2(int id, string title, string author, string category, int year, int stock, double price)

        : id(id), title(title), author(author), category(category), year(year), stock(stock), price(price), sales(0), monthlySales(12, 0) {}
};

// Class to manage the book store operations

class BookStore
{

private:
    unordered_map<string, Book2> inventory;

    // Inventory of books, key is book title

    vector<Book2> books;

    // List of books for additional operations

    // Display details of a single book

    void displayBook(const Book2& book) const

    {

        cout << left << setw(5) << book.id
             << setw(30) << book.title
             << setw(20) << book.author
             << setw(20) << book.category
             << setw(6) << book.year
             << setw(10) << book.stock
             << setw(10) << book.price
             << setw(10) << book.sales << endl;

    }

public:

    // Add a new book to the inventory

    void addBook()
     {
        int id, year, stock;
        double price;
        string title, author, category;

        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();

         // Ignore trailing newline

        cout << "Enter Title: ";
        getline(cin, title);

        cout << "Enter Author: ";
        getline(cin, author);

        cout << "Enter Category: ";
        getline(cin, category);

        cout << "Enter Year: ";
        cin >> year;

        cout << "Enter Stock: ";
        cin >> stock;

        cout << "Enter Price: ";
        cin >> price;

        if (inventory.count(title))
            {

            cout << "Book already exists in the inventory." << endl;
            return;

         }

        Book2 book(id, title, author, category, year, stock, price);
        inventory[title] = book;
        books.push_back(book);
        cout << "Book added successfully!" << endl;

     }

     // Record a sale for a book

    void recordSale()
     {

        string title;
        int month, quantity;

        cin.ignore();
        // Ignore trailing newline

        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Month (1-12): ";
        cin >> month;
        cout << "Enter Quantity Sold: ";
        cin >> quantity;

        if (inventory.find(title) == inventory.end())
            {

            cout << "Book not found in the inventory." << endl;
            return;
        }


        if (month < 1 || month > 12)
            {

            cout << "Invalid month. Please provide a value between 1 and 12." << endl;
            return;
        }


        if (quantity <= 0)
            {

            cout << "Invalid quantity. Please provide a positive value." << endl;
            return;
        }


        if (inventory[title].stock < quantity)
            {

            cout << "Insufficient stock for this sale." << endl;
            return;
        }


        inventory[title].sales += quantity;
        inventory[title].stock -= quantity;
        inventory[title].monthlySales[month - 1] += quantity;
        cout << "Sale recorded successfully!" << endl;
    }


    // Display the inventory of books

    void displayInventory() const
    {

        cout << left << setw(5) << "ID"

             << setw(30) << "Title"

             << setw(20) << "Author"

             << setw(20) << "Category"

             << setw(6) << "Year"

             << setw(10) << "Stock"

             << setw(10) << "Price"

             << setw(10) << "Sales" << endl;

        cout << string(121, '-') << endl;

        for (const auto& [title, book] : inventory)
            {

            displayBook(book);

        }

    }



    // Generate a sales report for all books

    void generateSalesReport() const
    {

        double totalRevenue = 0;
        map<string, int> categorySales;

        cout << "Sales Report:\n";

        cout << left << setw(5) << "ID"

             << setw(30) << "Title"

             << setw(15) << "Total Sales"

             << setw(15) << "Revenue" << endl;

        cout << string(65, '-') << endl;

        for (const auto& [title, book] : inventory)
            {

            if (book.sales > 0)
            {

                double revenue = book.sales * book.price;

                totalRevenue += revenue;

                categorySales[book.category] += book.sales;

                cout << left << setw(5) << book.id

                     << setw(30) << book.title

                     << setw(15) << book.sales

                     << setw(15) << fixed << setprecision(2) << revenue << endl;
            }


        }

        cout << "\nTotal Revenue: " << totalRevenue << endl;

        cout << "\nSales by Category:\n";

        for (const auto& entry : categorySales)
            {

            cout << "  " << entry.first << ": " << entry.second << " sales\n";
        }

    }


    // Display monthly sales data for a specific book

    void displayMonthlySales() const
    {

        string title;

        cin.ignore();
         // Ignore trailing newline

        cout << "Enter Book Title: ";

        getline(cin, title);

        if (inventory.find(title) == inventory.end())
            {

            cout << "Book not found in the inventory." << endl;

            return;
        }


        cout << "Monthly sales for: " << title << endl;

        const vector<int>& sales = inventory.at(title).monthlySales;

        for (int i = 0; i < 12; ++i)
            {

            cout << "Month " << i + 1 << ": " << sales[i] << " units" << endl;
        }

    }

    // Analyze sales trends for all books

    void analyzeTrends() const
    {

        cout << "\nTrend Analysis:\n";

        for (const auto& [title, book] : inventory)
            {

            if (book.sales > 0)
            {

                cout << "Monthly sales trend for " << book.title << ":\n";

                for (size_t i = 0; i < book.monthlySales.size(); ++i)
                {

                    cout << "Month " << i + 1 << ": " << book.monthlySales[i] << " units" << endl;

                }
            }
        }

    }


    // Forecast demand for a specific book using linear regression

    void forecastDemand() const
    {
        string title;

        cin.ignore();

         // Ignore trailing newline
        cout << "Enter Book Title: ";

        getline(cin, title);

        if (inventory.find(title) == inventory.end())
            {

            cout << "Book not found in the inventory." << endl;
            return;
        }


        const auto& sales = inventory.at(title).monthlySales;

        double avgSales = accumulate(sales.begin(), sales.end(), 0) / 12.0;


        // Performing simple linear regression for a more advanced forecast

        int n = sales.size();

        double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

        for (int i = 0; i < n; ++i)
            {

            sumX += i + 1;
            sumY += sales[i];
            sumXY += (i + 1) * sales[i];
            sumX2 += (i + 1) * (i + 1);
        }


        double slope = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);

        double intercept = (sumY - slope * sumX) / n;

        double forecast = slope * (n + 1) + intercept;

        cout << "Forecasted demand for the next month (based on linear regression): " << forecast << " units" << endl;

    }

    // Display best-selling books

    void bestSellingBooks()
    {

        cout << "Best-Selling Books:\n";

        cout << left << setw(5) << "ID"

             << setw(30) << "Title"

             << setw(10) << "Sales" << endl;

        vector<Book2> sortedBooks = books;

        sort(sortedBooks.begin(), sortedBooks.end(), [](const Book2& a, const Book2& b)
             {

            return a.sales > b.sales;
        }

        );

        for (const auto& book : sortedBooks)
            {

            if (book.sales > 0)
            {

                cout << left << setw(5) << book.id
                     << setw(30) << book.title
                     << setw(10) << book.sales << endl;
            }


        }
    }


    // Save the sales report to a file

    void saveReportToFile(const string& filename) const
    {

        ofstream outFile(filename);

        if (outFile.is_open())
            {

            outFile << "Sales Report:" << endl;

            for (const auto& [title, book] : inventory)
            {

                if (book.sales > 0)
                {

                    double revenue = book.sales * book.price;
                    outFile << left << setw(5) << book.id

                            << setw(30) << book.title

                            << setw(15) << book.sales


                            << setw(15) << fixed << setprecision(2) << revenue << endl;
                }


            }
            outFile.close();

            cout << "Report saved to " << filename << endl;

        }

        else
         {
            cerr << "Error opening file " << filename << endl;

        }
    }


    // Load sales data from a file

    void loadSalesData(const string& filename)
    {

        ifstream inFile(filename);

        if (inFile.is_open())
            {
            string title, author, category;

            int id, year, stock, sales;

            double price;

            vector<int> monthlySales(12, 0);

            while (inFile >> id >> title >> author >> category >> year >> stock >> price >> sales)
            {

                for (int & monthSale : monthlySales)
                {

                    inFile >> monthSale;
                }

                Book2 book(id, title, author, category, year, stock, price);
                book.sales = sales;
                book.monthlySales = monthlySales;
                inventory[title] = book;

                books.push_back(book);
            }


            inFile.close();
            cout << "Sales data loaded from " << filename << endl;

        }
         else
            {

            cerr << "Error opening file " << filename << endl;
        }

    }



    // Search for a book by title

    void searchBookByTitle() const
    {

        string title;
        cin.ignore();
        cout << "Enter Book Title: ";
        getline(cin, title);

        if (inventory.find(title) != inventory.end())
            {

            displayBook(inventory.at(title));
        }
        else
        {

            cout << "Book with title \"" << title << "\" not found in the inventory." << endl;

        }
    }

    // Update the details of an existing book

    void updateBookDetails()
    {

        string title;
        cin.ignore();
        cout << "Enter Book Title to Update: ";
        getline(cin, title);

        if (inventory.find(title) == inventory.end())
            {

            cout << "Book not found in the inventory." << endl;
            return;

        }

        int year, stock;
        double price;
        cout << "Enter Updated Year: ";
        cin >> year;
        cout << "Enter Updated Stock: ";
        cin >> stock;
        cout << "Enter Updated Price: ";
        cin >> price;

        Book2& book = inventory[title];
        book.year = year;
        book.stock = stock;
        book.price = price;
        cout << "Book details updated successfully!" << endl;

    }


    // Remove a book from the inventory
    void removeBook()
    {

        string title;
        cin.ignore();
        cout << "Enter Book Title to Remove: ";
        getline(cin, title);

        if (inventory.find(title) == inventory.end())
            {

            cout << "Book not found in the inventory." << endl;
            return;

        }

        inventory.erase(title);
        books.erase(remove_if(books.begin(), books.end(), [&](const Book2& b) { return b.title == title; }), books.end());
        cout << "Book removed successfully!" << endl;

    }

    // Display books by category

    void displayBooksByCategory() const
    {

        string category;
        cin.ignore();
        cout << "Enter Category: ";
        getline(cin, category);

        cout << "Books in category \"" << category << "\":\n";
        for (const auto& [title, book] : inventory)
        {

            if (book.category == category)

                {
                displayBook(book);

            }


        }
    }


    // Display books by author

    void displayBooksByAuthor() const {
        string author;
        cin.ignore();
        cout << "Enter Author: ";
        getline(cin, author);

        cout << "Books by author \"" << author << "\":\n";
        for (const auto& [title, book] : inventory)
            {

            if (book.author == author)
            {

                displayBook(book);
            }


        }
    }


    // Display books by year

    void displayBooksByYear() const
    {

        int year;
        cout << "Enter Year: ";
        cin >> year;

        cout << "Books published in year " << year << ":\n";
        for (const auto& [title, book] : inventory)
            {

            if (book.year == year)
            {

                displayBook(book);
            }


        }
    }


    // Sort books by title

    void sortBooksByTitle()
    {

        sort(books.begin(), books.end(), [](const Book2& a, const Book2& b)
             {

            return a.title < b.title;
        });

        cout << "Books sorted by title.\n";
    }


    // Sort books by author

    void sortBooksByAuthor()
    {

        sort(books.begin(), books.end(), [](const Book2& a, const Book2& b)
             {

            return a.author < b.author;
        }

        );
        cout << "Books sorted by author.\n";
    }

    // Sort books by year

    void sortBooksByYear()
    {

        sort(books.begin(), books.end(), [](const Book2& a, const Book2& b)
             {

            return a.year < b.year;
        }
        );
        cout << "Books sorted by year.\n";

    }

    // Function to add sample books into the inventory

    void addSampleBooks()
    {

        vector<Book2> sampleBooks =
        {
            //..............................................................
            {1, "The Great Gatsby", "F. Scott Fitzgerald", "Fiction", 1925, 50, 10.99},

            {2, "To Kill a Mockingbird", "Harper Lee", "Fiction", 1960, 40, 7.99},

            {3, "1984", "George Orwell", "Dystopian", 1949, 60, 8.99},

            {4, "Pride and Prejudice", "Jane Austen", "Romance", 1813, 30, 12.49},

            {5, "The Catcher in the Rye", "J.D. Salinger", "Fiction", 1951, 70, 9.99},

            {6, "The Hobbit", "J.R.R. Tolkien", "Fantasy", 1937, 45, 15.99},

            {7, "Moby Dick", "Herman Melville", "Adventure", 1851, 25, 11.99},

            {8, "Harry Potter and the Sorcerer's Stone", "J.K. Rowling", "Fantasy", 1997, 80, 14.99},

            {9, "To Kill a Mockingbird", "Harper Lee", "Fiction", 1960, 60, 12.99},

{10, "Pride and Prejudice", "Jane Austen", "Romance", 1813, 50, 10.99},

{11, "1984", "George Orwell", "Dystopian", 1949, 70, 9.49},

{12, "The Great Gatsby", "F. Scott Fitzgerald", "Fiction", 1925, 65, 13.99},

{13, "War and Peace", "Leo Tolstoy", "Historical", 1869, 30, 19.99},

{14, "Crime and Punishment", "Fyodor Dostoevsky", "Psychological", 1866, 40, 11.49},

{15, "Jane Eyre", "Charlotte Bront�", "Gothic", 1847, 55, 9.99},

{16, "The Alchemist", "Paulo Coelho", "Philosophical", 1988, 90, 10.99},

{17, "The Catch-22", "Joseph Heller", "Satire", 1961, 35, 13.49},

{18, "The Lord of the Rings", "J.R.R. Tolkien", "Fantasy", 1954, 85, 22.99},

{19, "The Grapes of Wrath", "John Steinbeck", "Fiction", 1939, 45, 14.99},

{20, "Wuthering Heights", "Emily Bront�", "Gothic", 1847, 50, 9.99},

{21, "Brave New World", "Aldous Huxley", "Dystopian", 1932, 60, 12.49},

{22, "Anna Karenina", "Leo Tolstoy", "Romance", 1877, 40, 15.49},

{23, "The Road", "Cormac McCarthy", "Post-apocalyptic", 2006, 75, 10.49},

{24, "Slaughterhouse-Five", "Kurt Vonnegut", "Satire", 1969, 35, 13.99},

{25, "Of Mice and Men", "John Steinbeck", "Fiction", 1937, 70, 9.99},

{26, "The Picture of Dorian Gray", "Oscar Wilde", "Philosophical", 1890, 45, 12.99},

{27, "A Tale of Two Cities", "Charles Dickens", "Historical", 1859, 40, 9.49},

{28, "Don Quixote", "Miguel de Cervantes", "Adventure", 1605, 30, 17.49},

{29, "The Kite Runner", "Khaled Hosseini", "Fiction", 2003, 90, 14.49},

{30, "Memoirs of a Geisha", "Arthur Golden", "Historical", 1997, 65, 11.99},

//...........................................................................................

{31, "The Handmaid's Tale", "Margaret Atwood", "Dystopian", 1985, 70, 13.99},

{32, "Les Mis�rables", "Victor Hugo", "Historical", 1862, 25, 19.99},

{33, "The Book Thief", "Markus Zusak", "Historical", 2005, 80, 12.99},

{34, "The Count of Monte Cristo", "Alexandre Dumas", "Adventure", 1844, 50, 15.99},

{35, "The Fault in Our Stars", "John Green", "Romance", 2012, 95, 9.49},

{36, "Life of Pi", "Yann Martel", "Adventure", 2001, 85, 11.49},

{37, "The Chronicles of Narnia", "C.S. Lewis", "Fantasy", 1950, 80, 20.99},

{38, "Gone with the Wind", "Margaret Mitchell", "Historical", 1936, 45, 13.99},

{39, "The Secret Garden", "Frances Hodgson Burnett", "Children", 1911, 70, 8.99},

{40, "A Thousand Splendid Suns", "Khaled Hosseini", "Fiction", 2007, 85, 13.49},

{41, "Beloved", "Toni Morrison", "Historical", 1987, 50, 12.99},

{42, "Middlemarch", "George Eliot", "Fiction", 1871, 35, 14.49},

{43, "Great Expectations", "Charles Dickens", "Fiction", 1861, 45, 11.99},

{44, "The Shining", "Stephen King", "Horror", 1977, 80, 14.99},

{45, "Dracula", "Bram Stoker", "Gothic", 1897, 40, 10.99},

{46, "The Giver", "Lois Lowry", "Dystopian", 1993, 85, 8.99},

{47, "The Time Traveler's Wife", "Audrey Niffenegger", "Romance", 2003, 60, 13.99},

{48, "The Hunger Games", "Suzanne Collins", "Dystopian", 2008, 90, 12.49},

{49, "The Maze Runner", "James Dashner", "Science Fiction", 2009, 80, 11.99},

{50, "Percy Jackson & the Olympians: The Lightning Thief", "Rick Riordan", "Fantasy", 2005, 95, 9.99},

{51, "Dune", "Frank Herbert", "Science Fiction", 1965, 60, 14.49},

{52, "Fahrenheit 451", "Ray Bradbury", "Dystopian", 1953, 70, 10.99},

{53, "A Wrinkle in Time", "Madeleine L'Engle", "Fantasy", 1962, 75, 9.49},

{54, "The Outsiders", "S.E. Hinton", "Fiction", 1967, 85, 8.99},

{55, "The Stand", "Stephen King", "Horror", 1978, 40, 19.99},

{56, "The Goldfinch", "Donna Tartt", "Fiction", 2013, 65, 14.99},

{57, "The Midnight Library", "Matt Haig", "Fantasy", 2020, 75, 12.99},

{58, "The Silent Patient", "Alex Michaelides", "Thriller", 2019, 80, 11.99},

{59, "Where the Crawdads Sing", "Delia Owens", "Mystery", 2018, 85, 13.49},

{60, "Circe", "Madeline Miller", "Fantasy", 2018, 80, 14.99},

//...................................................................................

{61, "The Shadow of the Wind", "Carlos Ruiz Zaf�n", "Mystery", 2001, 70, 13.99},

{62, "The Name of the Wind", "Patrick Rothfuss", "Fantasy", 2007, 85, 15.99},

{63, "The Pillars of the Earth", "Ken Follett", "Historical", 1989, 65, 16.49},

{64, "The Girl with the Dragon Tattoo", "Stieg Larsson", "Thriller", 2005, 90, 12.99},

{65, "Cloud Atlas", "David Mitchell", "Science Fiction", 2004, 50, 14.49},

{66, "The Lovely Bones", "Alice Sebold", "Fiction", 2002, 60, 11.49},

{67, "Shantaram", "Gregory David Roberts", "Fiction", 2003, 55, 18.99},

{68, "Big Little Lies", "Liane Moriarty", "Fiction", 2014, 75, 13.99},

{69, "The Help", "Kathryn Stockett", "Historical", 2009, 85, 12.49},

{70, "The Night Circus", "Erin Morgenstern", "Fantasy", 2011, 80, 14.99},

{71, "The Light We Lost", "Jill Santopolo", "Romance", 2017, 70, 11.99},

{72, "The Rosie Project", "Graeme Simsion", "Romance", 2013, 75, 10.49},

{73, "The 5th Wave", "Rick Yancey", "Science Fiction", 2013, 65, 13.49},

{74, "All the Light We Cannot See", "Anthony Doerr", "Historical", 2014, 90, 14.49},

{75, "Room", "Emma Donoghue", "Fiction", 2010, 70, 11.99},

{76, "Me Before You", "Jojo Moyes", "Romance", 2012, 85, 12.99},

{77, "An Ember in the Ashes", "Sabaa Tahir", "Fantasy", 2015, 75, 14.99},

{78, "The Goldfinch", "Donna Tartt", "Fiction", 2013, 55, 14.49},

{79, "Red Queen", "Victoria Aveyard", "Fantasy", 2015, 80, 13.99},

{80, "The Seven Husbands of Evelyn Hugo", "Taylor Jenkins Reid", "Fiction", 2017, 90, 13.49},

{81, "Verity", "Colleen Hoover", "Thriller", 2018, 95, 11.99},

{82, "It Ends with Us", "Colleen Hoover", "Romance", 2016, 100, 12.49},

{83, "Ugly Love", "Colleen Hoover", "Romance", 2014, 95, 11.99},

{84, "Reminders of Him", "Colleen Hoover", "Fiction", 2022, 85, 13.49},

{85, "The Inheritance Games", "Jennifer Lynn Barnes", "Mystery", 2020, 75, 14.99},

{86, "The Ballad of Songbirds and Snakes", "Suzanne Collins", "Dystopian", 2020, 80, 14.49},

{87, "Caraval", "Stephanie Garber", "Fantasy", 2017, 70, 12.99},

{88, "Legend", "Marie Lu", "Dystopian", 2011, 90, 11.49},

{89, "The Cruel Prince", "Holly Black", "Fantasy", 2018, 85, 13.49},

{90, "Serpent & Dove", "Shelby Mahurin", "Fantasy", 2019, 75, 14.99},

{91, "The Song of Achilles", "Madeline Miller", "Fantasy", 2011, 90, 13.99},

{92, "Circe", "Madeline Miller", "Fantasy", 2018, 80, 14.49},

{93, "A Court of Thorns and Roses", "Sarah J. Maas", "Fantasy", 2015, 95, 15.49},

{94, "Throne of Glass", "Sarah J. Maas", "Fantasy", 2012, 85, 14.99},

{95, "Crescent City: House of Earth and Blood", "Sarah J. Maas", "Fantasy", 2020, 75, 16.99},

{96, "Kingdom of the Wicked", "Kerri Maniscalco", "Fantasy", 2020, 70, 14.49},

{97, "The Midnight Library", "Matt Haig", "Fiction", 2020, 85, 12.99},

{98, "Beach Read", "Emily Henry", "Romance", 2020, 80, 13.99},

{99, "People We Meet on Vacation", "Emily Henry", "Romance", 2021, 85, 13.49},

{100, "Book Lovers", "Emily Henry", "Romance", 2022, 95, 12.99},

{101, "Malibu Rising", "Taylor Jenkins Reid", "Fiction", 2021, 80, 13.99},

{102, "Daisy Jones & The Six", "Taylor Jenkins Reid", "Fiction", 2019, 90, 14.49},

{103, "One True Loves", "Taylor Jenkins Reid", "Romance", 2016, 70, 13.99},

{104, "Before We Were Strangers", "Ren�e Carlino", "Romance", 2015, 75, 12.49},

{105, "The Nightingale", "Kristin Hannah", "Historical", 2015, 95, 14.99},

{106, "The Four Winds", "Kristin Hannah", "Historical", 2021, 85, 13.49},

{107, "Firefly Lane", "Kristin Hannah", "Fiction", 2008, 70, 12.99},

{108, "The Great Alone", "Kristin Hannah", "Fiction", 2018, 80, 14.99},

{109, "Winter Garden", "Kristin Hannah", "Historical", 2010, 60, 13.49},

{110, "The Paris Library", "Janet Skeslien Charles", "Historical", 2021, 85, 13.99},

{111, "The Giver of Stars", "Jojo Moyes", "Historical", 2019, 75, 14.49},

{112, "Paris by the Book", "Liam Callanan", "Fiction", 2018, 50, 12.99},

{113, "The Night Watchman", "Louise Erdrich", "Historical", 2020, 70, 14.49},

{114, "The Book of Lost Names", "Kristin Harmel", "Historical", 2020, 85, 14.99},

{115, "The Light Between Oceans", "M.L. Stedman", "Fiction", 2012, 65, 12.49},

{116, "A Man Called Ove", "Fredrik Backman", "Fiction", 2012, 85, 12.99},

{117, "Beartown", "Fredrik Backman", "Fiction", 2017, 80, 13.49},

{118, "Anxious People", "Fredrik Backman", "Fiction", 2020, 75, 13.99},

{119, "My Grandmother Asked Me to Tell You She's Sorry", "Fredrik Backman", "Fiction", 2015, 65, 12.99},

{120, "Us Against You", "Fredrik Backman", "Fiction", 2018, 70, 13.99},

{121, "Eleanor Oliphant Is Completely Fine", "Gail Honeyman", "Fiction", 2017, 85, 13.49},

{122, "The House in the Cerulean Sea", "TJ Klune", "Fantasy", 2020, 80, 14.49},

{123, "Under the Whispering Door", "TJ Klune", "Fantasy", 2021, 75, 14.99},

{124, "The Priory of the Orange Tree", "Samantha Shannon", "Fantasy", 2019, 70, 16.99},

{125, "The Bone Season", "Samantha Shannon", "Fantasy", 2013, 50, 14.49},

{126, "City of Bones", "Cassandra Clare", "Fantasy", 2007, 85, 13.99},

{127, "Clockwork Angel", "Cassandra Clare", "Fantasy", 2010, 80, 13.49},

{128, "Lady Midnight", "Cassandra Clare", "Fantasy", 2016, 75, 14.99},

{129, "Chain of Gold", "Cassandra Clare", "Fantasy", 2020, 70, 15.49},

{130, "Queen of Air and Darkness", "Cassandra Clare", "Fantasy", 2018, 80, 15.49},

//.......................................................................

{131, "King of Scars", "Leigh Bardugo", "Fantasy", 2019, 75, 14.99},

{132, "Shadow and Bone", "Leigh Bardugo", "Fantasy", 2012, 90, 13.99},

{133, "Six of Crows", "Leigh Bardugo", "Fantasy", 2015, 95, 15.49},

{134, "Crooked Kingdom", "Leigh Bardugo", "Fantasy", 2016, 85, 14.99},

{135, "Ninth House", "Leigh Bardugo", "Fantasy", 2019, 75, 15.49},

{136, "The Wrath & the Dawn", "Ren�e Ahdieh", "Fantasy", 2015, 80, 14.99},

{137, "Flame in the Mist", "Ren�e Ahdieh", "Fantasy", 2017, 70, 13.99},

{138, "The Beautiful", "Ren�e Ahdieh", "Fantasy", 2019, 75, 13.49},

{139, "The Damned", "Ren�e Ahdieh", "Fantasy", 2020, 80, 13.99},

{140, "The Stolen Heir", "Holly Black", "Fantasy", 2023, 85, 15.99},

{141, "Howl's Moving Castle", "Diana Wynne Jones", "Fantasy", 1986, 65, 12.99},

{142, "Spinning Silver", "Naomi Novik", "Fantasy", 2018, 75, 14.49},

{143, "Uprooted", "Naomi Novik", "Fantasy", 2015, 80, 14.99},

{144, "The Paper Palace", "Miranda Cowley Heller", "Fiction", 2021, 70, 13.99},

{145, "The Guest List", "Lucy Foley", "Mystery", 2020, 75, 13.49},

{146, "The Paris Library", "Janet Skeslien Charles", "Historical", 2021, 80, 13.99},

{147, "The Alice Network", "Kate Quinn", "Historical", 2017, 85, 14.99},

{148, "The Huntress", "Kate Quinn", "Historical", 2019, 80, 14.49},

{149, "The Rose Code", "Kate Quinn", "Historical", 2021, 90, 15.99},

{150, "The Diamond Eye", "Kate Quinn", "Historical", 2022, 85, 15.49},

{151, "Lessons in Chemistry", "Bonnie Garmus", "Fiction", 2022, 75, 14.99},

{152, "Tomorrow, and Tomorrow, and Tomorrow", "Gabrielle Zevin", "Fiction", 2022, 80, 14.49},

{153, "Sea of Tranquility", "Emily St. John Mandel", "Science Fiction", 2022, 70, 13.99},

{154, "Station Eleven", "Emily St. John Mandel", "Science Fiction", 2014, 85, 13.49},

{155, "The Glass Hotel", "Emily St. John Mandel", "Fiction", 2020, 75, 14.49},

{156, "Hamnet", "Maggie O'Farrell", "Historical", 2020, 80, 14.99},

{157, "The Marriage Portrait", "Maggie O'Farrell", "Historical", 2022, 70, 15.49},

{158, "Transcendent Kingdom", "Yaa Gyasi", "Fiction", 2020, 75, 13.99},

{159, "Homegoing", "Yaa Gyasi", "Historical", 2016, 85, 14.49},

{160, "The Water Dancer", "Ta-Nehisi Coates", "Historical", 2019, 70, 14.99},

{161, "Where the Crawdads Sing", "Delia Owens", "Fiction", 2018, 85, 14.99},

{162, "The Alchemist", "Paulo Coelho", "Fiction", 1988, 90, 13.49},

{163, "The Kite Runner", "Khaled Hosseini", "Fiction", 2003, 95, 14.49},

{164, "A Thousand Splendid Suns", "Khaled Hosseini", "Fiction", 2007, 85, 13.99},

{165, "And the Mountains Echoed", "Khaled Hosseini", "Fiction", 2013, 80, 14.49},

{166, "The Road", "Cormac McCarthy", "Fiction", 2006, 75, 13.49},

{167, "No Country for Old Men", "Cormac McCarthy", "Fiction", 2005, 70, 13.99},

{168, "Blood Meridian", "Cormac McCarthy", "Fiction", 1985, 65, 14.49},

{169, "All the Pretty Horses", "Cormac McCarthy", "Fiction", 1992, 60, 13.99},

{170, "Suttree", "Cormac McCarthy", "Fiction", 1979, 55, 13.49},

{171, "East of Eden", "John Steinbeck", "Fiction", 1952, 85, 15.49},

{172, "Of Mice and Men", "John Steinbeck", "Fiction", 1937, 90, 13.49},

{173, "The Grapes of Wrath", "John Steinbeck", "Fiction", 1939, 95, 14.99},

{174, "Cannery Row", "John Steinbeck", "Fiction", 1945, 70, 13.49},

{175, "Travels with Charley", "John Steinbeck", "Non-Fiction", 1962, 65, 14.49},

{176, "Brave New World", "Aldous Huxley", "Science Fiction", 1932, 90, 13.99},

{177, "1984", "George Orwell", "Dystopian", 1949, 95, 14.99},

{178, "Animal Farm", "George Orwell", "Fiction", 1945, 85, 12.99},

{179, "Homage to Catalonia", "George Orwell", "Non-Fiction", 1938, 75, 13.49},

{180, "Down and Out in Paris and London", "George Orwell", "Non-Fiction", 1933, 70, 12.99},

{181, "Lord of the Flies", "William Golding", "Fiction", 1954, 80, 14.49},

{182, "The Bell Jar", "Sylvia Plath", "Fiction", 1963, 85, 14.99},

{183, "To Kill a Mockingbird", "Harper Lee", "Fiction", 1960, 95, 13.99},

{184, "Go Set a Watchman", "Harper Lee", "Fiction", 2015, 70, 13.49},

{185, "A Farewell to Arms", "Ernest Hemingway", "Fiction", 1929, 75, 14.49},

{186, "For Whom the Bell Tolls", "Ernest Hemingway", "Fiction", 1940, 80, 14.99},

{187, "The Old Man and the Sea", "Ernest Hemingway", "Fiction", 1952, 90, 12.99},

{188, "The Sun Also Rises", "Ernest Hemingway", "Fiction", 1926, 85, 13.99},

{189, "The Great Gatsby", "F. Scott Fitzgerald", "Fiction", 1925, 95, 13.49},

{190, "Tender Is the Night", "F. Scott Fitzgerald", "Fiction", 1934, 70, 14.49},

{191, "This Side of Paradise", "F. Scott Fitzgerald", "Fiction", 1920, 65, 13.99},

{192, "The Beautiful and Damned", "F. Scott Fitzgerald", "Fiction", 1922, 60, 14.49},

{193, "Slaughterhouse-Five", "Kurt Vonnegut", "Science Fiction", 1969, 80, 13.99},

{194, "Cat's Cradle", "Kurt Vonnegut", "Science Fiction", 1963, 75, 13.49},

{195, "Breakfast of Champions", "Kurt Vonnegut", "Science Fiction", 1973, 70, 14.49},

{196, "Mother Night", "Kurt Vonnegut", "Science Fiction", 1961, 65, 13.99},

{197, "Gal�pagos", "Kurt Vonnegut", "Science Fiction", 1985, 60, 14.49},

{198, "The Catcher in the Rye", "J.D. Salinger", "Fiction", 1951, 95, 14.49},

{199, "Franny and Zooey", "J.D. Salinger", "Fiction", 1961, 75, 13.99},

{200, "Nine Stories", "J.D. Salinger", "Fiction", 1953, 65, 12.99},

{201, "Raise High the Roof Beam, Carpenters", "J.D. Salinger", "Fiction", 1955, 55, 13.49},

{202, "The Fellowship of the Ring", "J.R.R. Tolkien", "Fantasy", 1954, 95, 14.99},

{203, "The Two Towers", "J.R.R. Tolkien", "Fantasy", 1954, 90, 13.99},

{204, "The Return of the King", "J.R.R. Tolkien", "Fantasy", 1955, 85, 14.49},

{205, "The Silmarillion", "J.R.R. Tolkien", "Fantasy", 1977, 75, 13.99},

{206, "Unfinished Tales", "J.R.R. Tolkien", "Fantasy", 1980, 65, 14.49},

{207, "Dune", "Frank Herbert", "Science Fiction", 1965, 95, 14.99},

{208, "Children of Dune", "Frank Herbert", "Science Fiction", 1976, 75, 14.49},

{209, "God Emperor of Dune", "Frank Herbert", "Science Fiction", 1981, 70, 13.99},

{210, "Heretics of Dune", "Frank Herbert", "Science Fiction", 1984, 65, 14.49},

{211, "Chapterhouse: Dune", "Frank Herbert", "Science Fiction", 1985, 60, 14.99},

{212, "Foundation", "Isaac Asimov", "Science Fiction", 1951, 90, 13.99},

{213, "Foundation and Empire", "Isaac Asimov", "Science Fiction", 1952, 85, 14.49},

{214, "Second Foundation", "Isaac Asimov", "Science Fiction", 1953, 80, 13.99},

{215, "I, Robot", "Isaac Asimov", "Science Fiction", 1950, 95, 12.99},

{216, "The Gods Themselves", "Isaac Asimov", "Science Fiction", 1972, 75, 13.99},

{217, "Neuromancer", "William Gibson", "Science Fiction", 1984, 90, 14.49},

{218, "Count Zero", "William Gibson", "Science Fiction", 1986, 85, 13.99},

{219, "Mona Lisa Overdrive", "William Gibson", "Science Fiction", 1988, 80, 14.49},

{220, "Pattern Recognition", "William Gibson", "Science Fiction", 2003, 75, 13.99},

{221, "Snow Crash", "Neal Stephenson", "Science Fiction", 1992, 95, 14.99},

{222, "Cryptonomicon", "Neal Stephenson", "Science Fiction", 1999, 85, 14.49},

{223, "The Diamond Age", "Neal Stephenson", "Science Fiction", 1995, 80, 13.99},

{224, "Anathem", "Neal Stephenson", "Science Fiction", 2008, 75, 14.99},

{225, "Seveneves", "Neal Stephenson", "Science Fiction", 2015, 70, 13.49},

{226, "Hyperion", "Dan Simmons", "Science Fiction", 1989, 90, 14.49},

{227, "The Fall of Hyperion", "Dan Simmons", "Science Fiction", 1990, 85, 13.99},

{228, "Endymion", "Dan Simmons", "Science Fiction", 1996, 80, 14.99},

{229, "The Rise of Endymion", "Dan Simmons", "Science Fiction", 1997, 75, 13.99},

{230, "The Left Hand of Darkness", "Ursula K. Le Guin", "Science Fiction", 1969, 95, 14.49},

{231, "The Dispossessed", "Ursula K. Le Guin", "Science Fiction", 1974, 90, 13.99},

{232, "A Wizard of Earthsea", "Ursula K. Le Guin", "Fantasy", 1968, 85, 14.49},

{233, "The Tombs of Atuan", "Ursula K. Le Guin", "Fantasy", 1971, 80, 13.99},

{234, "The Farthest Shore", "Ursula K. Le Guin", "Fantasy", 1972, 75, 14.49},

{235, "The Lathe of Heaven", "Ursula K. Le Guin", "Science Fiction", 1971, 70, 13.49},

{236, "Do Androids Dream of Electric Sheep?", "Philip K. Dick", "Science Fiction", 1968, 95, 14.99},

{237, "Ubik", "Philip K. Dick", "Science Fiction", 1969, 90, 14.49},

{238, "A Scanner Darkly", "Philip K. Dick", "Science Fiction", 1977, 85, 13.99},

{239, "The Man in the High Castle", "Philip K. Dick", "Science Fiction", 1962, 80, 14.49},

{240, "Flow My Tears, the Policeman Said", "Philip K. Dick", "Science Fiction", 1974, 75, 13.99},

{241, "The Three-Body Problem", "Liu Cixin", "Science Fiction", 2008, 90, 14.99},

{242, "The Dark Forest", "Liu Cixin", "Science Fiction", 2008, 85, 14.49},

{243, "Death's End", "Liu Cixin", "Science Fiction", 2010, 80, 14.99},

{244, "Remembrance of Earth's Past", "Liu Cixin", "Science Fiction", 2008, 75, 13.99},

{245, "Spin", "Robert Charles Wilson", "Science Fiction", 2005, 90, 14.49},

{246, "Axis", "Robert Charles Wilson", "Science Fiction", 2007, 85, 13.99},

{247, "Vortex", "Robert Charles Wilson", "Science Fiction", 2011, 80, 14.49},

{248, "Blind Lake", "Robert Charles Wilson", "Science Fiction", 2003, 75, 13.99},

{249, "The Chronoliths", "Robert Charles Wilson", "Science Fiction", 2001, 70, 14.49},

{250, "American Gods", "Neil Gaiman", "Fantasy", 2001, 90, 14.99},

{251, "Neverwhere", "Neil Gaiman", "Fantasy", 1996, 85, 14.49},

{252, "Stardust", "Neil Gaiman", "Fantasy", 1999, 80, 13.99},

{253, "Coraline", "Neil Gaiman", "Fantasy", 2002, 75, 14.49},

{254, "The Graveyard Book", "Neil Gaiman", "Fantasy", 2008, 70, 14.99},

{255, "Good Omens", "Neil Gaiman and Terry Pratchett", "Fantasy", 1990, 95, 13.99},

{256, "The Colour of Magic", "Terry Pratchett", "Fantasy", 1983, 85, 14.49},

{257, "Mort", "Terry Pratchett", "Fantasy", 1987, 80, 13.99},

{258, "Guards! Guards!", "Terry Pratchett", "Fantasy", 1989, 75, 14.49},

{259, "Small Gods", "Terry Pratchett", "Fantasy", 1992, 70, 13.99},

{260, "Hogfather", "Terry Pratchett", "Fantasy", 1996, 65, 14.49},



//.....................................................................

        };


        for (const auto& book : sampleBooks)
            {

            inventory[book.title] = book;
            books.push_back(book);
        }


        // Record some hypothetical sales for the sample books

        inventory["The Great Gatsby"].sales = 30;

        inventory["To Kill a Mockingbird"].sales = 25;

        inventory["1984"].sales = 50;

        inventory["Pride and Prejudice"].sales = 20;

        inventory["The Catcher in the Rye"].sales = 35;

        inventory["The Hobbit"].sales = 40;

        inventory["Moby Dick"].sales = 15;

        inventory["Harry Potter and the Sorcerer's Stone"].sales = 60;

        inventory["The Great Gatsby"].monthlySales[0] = 30;

        inventory["To Kill a Mockingbird"].monthlySales[1] = 25;

        inventory["1984"].monthlySales[2] = 50;

        inventory["Pride and Prejudice"].monthlySales[3] = 20;

        inventory["The Catcher in the Rye"].monthlySales[4] = 35;

        inventory["The Hobbit"].monthlySales[5] = 40;
        \

        inventory["Moby Dick"].monthlySales[6] = 15;

        inventory["Harry Potter and the Sorcerer's Stone"].monthlySales[7] = 60;

        cout << "Sample books added successfully!" << endl;
    }
};

 int main() {

    int choice;

    loadDataFromFile();

    SupplierManagementSystem sms;
     BookStore store;

    do {
            cout << "\n--- Book Management System ---\n";
        cout << "1. Add Book\n";
        cout << "2. Record Sale\n";
        cout << "3. Display Inventory\n";
        cout << "4. Forecast Demand\n";
        cout << "5. Generate Sales Report\n";
        cout << "6. Display Monthly Sales\n";
        cout << "7. Analyze Trends\n";
        cout << "8. Best-Selling Books\n";
        cout << "9. Save Report to File\n";
        cout << "10. Load Sales Data from File\n";
        cout << "11. Search Book by Title\n";
        cout << "12. Update Book Details\n";
        cout << "13. Remove Book\n";
        cout << "14. Display Books by Category\n";
        cout << "15. Display Books by Author\n";
        cout << "16. Display Books by Year\n";
        cout << "17. Sort Books by Title\n";
        cout << "18. Sort Books by Author\n";
        cout << "19. Sort Books by Year\n";
        cout << "\n--- Menu ---\n";

        cout << "20. Add Customer\n";

        cout << "21. Add Product\n";

        cout << "22. Purchase Product\n";

        cout << "23. View All Products\n";

        cout << "24. View All Customers\n";

        cout << "25. View Transactions\n";



        cout<<"29.Generate monthly sales report\n";


         cout<<"31.search product by ID or name\n";



        cout << "32. Update Product Price\n";

cout << "33. Delete Product\n";

cout << "34. View Transaction History of Customer\n";

cout << "35. Update Customer Loyalty Points\n";

cout << "36. View Product Stock\n";

cout << "37. Check Product Availability\n";

cout << "38. Generate Customer Loyalty Report\n";



cout << "40. Sort Products by Price\n";



cout << "41. Restock Product\n";


cout << "42. Find Products by Price Range\n";

cout << "43. Delete Customer by ID\n";

cout << "44. Generate Inventory Summary\n";

cout << "45. Send Loyalty Rewards to Top Customers\n";

        std::cout << "\nBook Management System\n";

        std::cout << "46. Exit\n";



cout<<"enter your choice";

        cin >> choice;

        switch (choice) {
            case 1:
                store.addBook();
                break;

            case 2:
                store.recordSale();
                break;

            case 3:
                store.displayInventory();
                break;

            case 4:
                store.forecastDemand();
                break;


            case 5:
                store.generateSalesReport();
                break;

            case 6:
                store.displayMonthlySales();
                break;

            case 7:
                store.analyzeTrends();
                break;

            case 8:
                store.bestSellingBooks();
                break;

            case 9: {
                string filename;
                cin.ignore();

                // Ignore trailing newline

                cout << "Enter filename to save report: ";
                getline(cin, filename);
                store.saveReportToFile(filename);
                break;

            }

            case 10:

                {

                string filename;
                cin.ignore();

                // Ignore trailing newline

                cout << "Enter filename to load sales data: ";
                getline(cin, filename);
                store.loadSalesData(filename);
                break;

            }
            case 11:
                store.searchBookByTitle();
                break;

            case 12:
                store.updateBookDetails();
                break;

            case 13:
                store.removeBook();
                break;

            case 14:
                store.displayBooksByCategory();
                break;

            case 15:
                store.displayBooksByAuthor();
                break;

            case 16:
                store.displayBooksByYear();
                break;

            case 17:
                store.sortBooksByTitle();
                break;

            case 18:
                store.sortBooksByAuthor();
                break;

            case 19:
                store.sortBooksByYear();
                break;

            case 20:
                addCustomer();
                break;

            case 21:
                addProduct();
                break;

            case 22:
                purchaseProduct();
                break;


            case 23:
                viewProducts();
                break;


            case 24:
                viewCustomers();
                break;


            case 25:
                cout << "--- Transactions ---\n";
                for (const auto& transaction : transactions) {

                    cout << "Customer ID: " << transaction.customerId

                         << ", Product ID: " << transaction.productId

                         << ", Quantity: " << transaction.quantity

                         << ", Total Cost: " << transaction.totalCost

                         << ", Date: " << transaction.date << endl;
                }
                break;

            case 26: {
                string transactionId;

                cout << "Enter Transaction ID to return: ";

                cin >> transactionId;

                handleReturns(transactionId);

                break;
            }

            case 27:
                adminLogin();

                break;

            case 28:
                saveDataToFile();
break;

    case 29:
    {
        string monthYear;

        cout << "Enter month and year (format YYYY-MM): ";

        cin >> monthYear;

        generateMonthlySalesReport(monthYear);
        break;
    }
    case 30:
    {
        string genre;

        double discountPercentage;

        cout << "Enter genre for discount: ";

        cin >> genre;

        cout << "Enter discount percentage: ";

        cin >> discountPercentage;

        applyBulkDiscountByGenre(genre, discountPercentage);

        break;
    }
    case 31:
        {
            string query;

            cout << "Enter Product ID or Name: ";

            cin >> query;

            searchProductByIdOrName(query);
            break;

        }
    case 32:
        {
            string productId;

            double newPrice;

            cout << "Enter Product ID: ";

            cin >> productId;

            cout << "Enter New Price: ";

            cin >> newPrice;

            updateProductPrice(productId, newPrice);
            break;
        }
    case 33:
        {
            string productId;

            cout << "Enter Product ID to delete: ";

            cin >> productId;

            deleteProduct(productId);
            break;
        }

    case 34:
        {
            string customerId;

            cout << "Enter Customer ID to view transaction history: ";

            cin >> customerId;

            viewTransactionHistory(customerId);
            break;
        }

 case 35:
        {
            string customerId;

            int newPoints;

            cout << "Enter Customer ID: ";

            cin >> customerId;

            cout << "Enter New Loyalty Points: ";

            cin >> newPoints;

            updateCustomerLoyaltyPoints(customerId, newPoints);

            break;
        }

    case 36:
        {
            string productId;

            cout << "Enter Product ID to view stock: ";

            cin >> productId;

            viewProductStock(productId);

            break;
        }
        case 37:
        {
            string productId;

            int quantity;

            cout << "Enter Product ID: ";

            cin >> productId;

            cout << "Enter Quantity to check availability: ";

            cin >> quantity;

            if (isProductAvailable(productId, quantity)) {

                cout << "Product is available.\n";
            } else {
                cout << "Product is not available or insufficient stock.\n";
            }
            break;
        }

    case 38:
        generateCustomerLoyaltyReport();

        break;


 case 39:
        {
            string genre;
            cout << "Enter Genre to view products: ";
            cin >> genre;
            viewProductsByGenre(genre);
            break;
        }

    case 40:
        {
            int order;
            cout << "Enter 1 for Ascending or 0 for Descending order: ";
            cin >> order;
            sortProductsByPrice(order == 1);  // Pass true for ascending, false for descending
            break;
        }


    case 41:
        {
            string productId;
            int additionalStock;
            cout << "Enter Product ID to restock: ";
            cin >> productId;
            cout << "Enter quantity to restock: ";
            cin >> additionalStock;
            restockProduct(productId, additionalStock);
            break;
        }
        case 42: {
    double minPrice, maxPrice;
    cout << "Enter minimum price: ";
    cin >> minPrice;
    cout << "Enter maximum price: ";
    cin >> maxPrice;
    findProductsByPriceRange(minPrice, maxPrice);
    break;
}
case 43: {
    string customerId;
    cout << "Enter Customer ID to delete: ";
    cin >> customerId;
    deleteCustomerById(customerId);
    break;
}
case 44:
    generateInventorySummary();
    break;
case 45: {
    int topN;
    cout << "Enter the number of top customers to reward: ";
    cin >> topN;
    sendLoyaltyRewards(topN);
    break;
}
case 46:
                exit(0);
                break;




            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (true);

    return 0;

}
