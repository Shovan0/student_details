#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Class to represent a student record
class Student {
public:
    int roll;
    string name;
    int reg;
    int marksDS;
    int marksMath;
    int marksDE;
    int marksSS;
    int marksBio;

    // Constructor to initialize the student
    Student(int r, const string& n, int rg, int ds, int math, int de, int ss, int bio)
        : roll(r), name(n), reg(rg), marksDS(ds), marksMath(math), marksDE(de), marksSS(ss), marksBio(bio) {}

    // Function to calculate total marks for a student
    int calculateTotal() const {
        return marksDS + marksMath + marksDE + marksSS + marksBio;
    }

    // Function to display all details of a student
    void displayStudentDetails() const {
        cout << "Student Details for Roll No. " << roll << " - " << name << ":\n";
        cout << "Roll Number: " << roll << "\n";
        cout << "Name: " << name << "\n";
        cout << "Registration Number: " << reg << "\n";
        cout << "Marks in Data Structure & Algorithm: " << marksDS << "\n";
        cout << "Marks in Mathematics: " << marksMath << "\n";
        cout << "Marks in Digital Electronics: " << marksDE << "\n";
        cout << "Marks in Signal & Systems: " << marksSS << "\n";
        cout << "Marks in Biology: " << marksBio << "\n";
        cout << "Total Marks: " << calculateTotal() << "\n\n";
    }
};

// Node structure for AVL tree
class Node {
public:
    Student* data;
    Node* left;
    Node* right;
    int height;

    // Constructor to initialize the node
    Node(Student* s) : data(s), left(nullptr), right(nullptr), height(1) {}
};

// Function to get height of a node
int height(Node* node) {
    if (node == nullptr) return 0;
    return node->height;
}

// Function to get the balance factor of a node
int balanceFactor(Node* node) {
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

// Function to update the height of a node
void updateHeight(Node* node) {
    if (node != nullptr) {
        node->height = 1 + max(height(node->left), height(node->right));
    }
}

// Function to perform a right rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    // Return new root
    return x;
}

// Function to perform a left rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    // Return new root
    return y;
}

// Function to balance the AVL tree
Node* balance(Node* root) {
    // Update height of the current node
    updateHeight(root);

    // Get the balance factor
    int bf = balanceFactor(root);

    // Left-Left case
    if (bf > 1 && balanceFactor(root->left) >= 0) {
        return rightRotate(root);
    }

    // Right-Right case
    if (bf < -1 && balanceFactor(root->right) <= 0) {
        return leftRotate(root);
    }

    // Left-Right case
    if (bf > 1 && balanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right-Left case
    if (bf < -1 && balanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to insert a student into the AVL tree
Node* insert(Node* root, Student* student) {
    if (root == nullptr) {
        return new Node(student);
    }

    // Insertion
    if (student->roll < root->data->roll) {
        root->left = insert(root->left, student);
    } else if (student->roll > root->data->roll) {
        root->right = insert(root->right, student);
    } else {
        // Duplicate rolls not allowed
        return root;
    }

    // Balance the tree
    return balance(root);
}

// Function to search for a student by roll number
Node* search(Node* root, int roll) {
    if (root == nullptr || root->data->roll == roll) {
        return root;
    }

    if (roll < root->data->roll) {
        return search(root->left, roll);
    }

    return search(root->right, roll);
}

// Function to find the node with the minimum value
Node* minValueNode(Node* node) {
    Node* current = node;

    while (current->left != nullptr) {
        current = current->left;
    }

    return current;
}

// Function to delete a student from the AVL tree
Node* deleteNode(Node* root, int roll) {
    if (root == nullptr) return root;

    // Perform deletion
    if (roll < root->data->roll) {
        root->left = deleteNode(root->left, roll);
    } else if (roll > root->data->roll) {
        root->right = deleteNode(root->right, roll);
    } else {
        // Node with only one child or no child
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                // One child case
                *root = *temp;
            }

            delete temp;
        } else {
            // Node with two children, get the inorder successor
            Node* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->data = temp->data;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->data->roll);
        }
    }

    // If the tree had only one node, then return
    if (root == nullptr) return root;

    // Balance the tree
    return balance(root);
}

// Function to calculate total marks for a student
int calculateTotal(Student* student) {
    return student->marksDS + student->marksMath + student->marksDE + student->marksSS + student->marksBio;
}

// Function to display all details of a student
void displayStudentDetails(Student* student) {
    cout << "Student Details for Roll No. " << student->roll << " - " << student->name << ":\n";
    cout << "Roll Number: " << student->roll << "\n";
    cout << "Name: " << student->name << "\n";
    cout << "Registration Number: " << student->reg << "\n";
    cout << "Marks in Data Structure & Algorithm: " << student->marksDS << "\n";
    cout << "Marks in Mathematics: " << student->marksMath << "\n";
    cout << "Marks in Digital Electronics: " << student->marksDE << "\n";
    cout << "Marks in Signal & Systems: " << student->marksSS << "\n";
    cout << "Marks in Biology: " << student->marksBio << "\n";
    cout << "Total Marks: " << calculateTotal(student) << "\n\n";
}

// Function to modify student data
void modifyStudent(Node* root, int roll) {
    Node* node = search(root, roll);

    if (node != nullptr) {
        cout << "Enter updated details for Roll No. " << roll << ":\n";
        cout << "Name: ";
        cin.ignore();  // Ignore the newline character left in the buffer
        getline(cin, node->data->name);
        cout << "Registration Number: ";
        cin >> node->data->reg;
        cout << "Marks in Data Structure & Algorithm: ";
        cin >> node->data->marksDS;
        cout << "Marks in Mathematics: ";
        cin >> node->data->marksMath;
        cout << "Marks in Digital Electronics: ";
        cin >> node->data->marksDE;
        cout << "Marks in Signal & Systems: ";
        cin >> node->data->marksSS;
        cout << "Marks in Biology: ";
        cin >> node->data->marksBio;

        cout << "Student data successfully modified!\n\n";
    } else {
        cout << "Student with Roll No. " << roll << " not found.\n\n";
    }
}

// Function to display all students in-order with all details
void displayInOrderDetails(Node* root) {
    if (root != nullptr) {
        displayInOrderDetails(root->left);
        displayStudentDetails(root->data);
        displayInOrderDetails(root->right);
    }
}

int main() {
    Node* root = nullptr;

    while (true) {
        cout << "1. Add Student\n";
        cout << "2. Search Student\n";
        cout << "3. Modify Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Display All Students\n";
        cout << "6. Exit\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int roll, reg, marksDS, marksMath, marksDE, marksSS, marksBio;
                string name;

                cout << "Enter Roll Number: ";
                cin >> roll;

                // Check for duplicate roll numbers
                if (search(root, roll) != nullptr) {
                    cout << "Student with Roll Number " << roll << " already exists. Please enter a unique Roll Number.\n\n";
                    break;
                }

                cout << "Enter Name: ";
                cin.ignore();  // Ignore the newline character left in the buffer
                getline(cin, name);
                cout << "Enter Registration Number: ";
                cin >> reg;
                cout << "Enter Marks in Data Structure & Algorithm: ";
                cin >> marksDS;
                cout << "Enter Marks in Mathematics: ";
                cin >> marksMath;
                cout << "Enter Marks in Digital Electronics: ";
                cin >> marksDE;
                cout << "Enter Marks in Signal & Systems: ";
                cin >> marksSS;
                cout << "Enter Marks in Biology: ";
                cin >> marksBio;

                Student* newStudent = new Student(roll, name, reg, marksDS, marksMath, marksDE, marksSS, marksBio);
                root = insert(root, newStudent);

                cout << "Student successfully added!\n\n";
                break;
            }

            case 2: {
                int roll;
                cout << "Enter Roll Number to Search: ";
                cin >> roll;

                Node* result = search(root, roll);

                if (result != nullptr) {
                    cout << "Student found:\n";
                    displayStudentDetails(result->data);
                } else {
                    cout << "Student with Roll Number " << roll << " not found.\n\n";
                }

                break;
            }

            case 3: {
                int roll;
                cout << "Enter Roll Number to Modify: ";
                cin >> roll;

                modifyStudent(root, roll);
                break;
            }

            case 4: {
                int roll;
                cout << "Enter Roll Number to Delete: ";
                cin >> roll;

                root = deleteNode(root, roll);
                cout << "Student with Roll Number " << roll << " deleted successfully.\n\n";
                break;
            }

            case 5:
                if (root == nullptr) {
                    cout << "No students registered.\n\n";
                } else {
                    displayInOrderDetails(root);
                }
                break;

            case 6:
                cout << "Exiting program...\n";
                return 0;

            default:
                cout << "Invalid choice. Please enter a valid option.\n\n";
                break;
        }
    }

    return 0;
}