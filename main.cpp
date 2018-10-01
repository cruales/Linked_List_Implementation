//
//  main.cpp
//  Data_Structures_Project1
//
//  Created by Christie Ruales on 9/21/18.
//  Copyright © 2018 Christie Ruales. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Node {
public:
    string value;
    Node* next = NULL;
};

struct Node *head = NULL;

Node* insertEnd(Node* head, string newString){
    Node *newNode = new Node; //initializes newNode
    newNode->value = newString; //sets the value of newNode to newString
    
    if (head->value == "NULL"){
        head = newNode; //if the list is empty then it will insertEnd to the first position
    }
    //if list is not empty it will insertEnd to last position
    else{
        Node *currentNode = new Node;
        currentNode = head;
        while (currentNode->next != NULL){
            currentNode = currentNode->next;
        }
        currentNode->next = newNode; //sets the last node of the linked list next to new_node
    }
    return head;
}

Node* insert(Node* head, int index, string newString){
    if (index <= 0) return head; //if invalid index is passed in ignore it
    
    Node *newNode  = new Node;
    newNode->value = newString;
    
    //if list is empty
    if(head->value == "NULL"){
        //if index is 1 then add the value
        if(index == 1){
            head = newNode;
            return head;
        }
        //if invalid index then ignore it
        if(index != 1){
            return head;
        }
    }
    
    Node *currentNode = new Node;
    currentNode = head;
    
    if (index == 1){
        newNode->next = head;
        head = newNode;
        return head;
    }
    
    int i;
    while (i < index-2){
        if (currentNode->next == NULL && i!=index){
            return head; //if the index given is larger than the size of the linked list, don't add the newNode
        }
        currentNode = currentNode->next;
        i++;
    }
    
    newNode->next = currentNode->next;
    currentNode->next = newNode;
    
    return head;
}

Node* deleteValue(Node* head, int index){
    //if invalid index
    if(index <=0){
        return head;
    }
    
    
    if (index == 1){
        //if index is 1 but the list is empty then just return head
        if(head->value == "NULL"){
            return head;
        }
        //if index is 1 and the list is not empty then delete first value
        else{
            head = head->next;
            return head;
        }
    }
    
    Node *currentNode = new Node;
    Node *previousNode = new Node;
    
    currentNode = head;
    
    int i = 0;
    while (i < index-1){
        if (currentNode->next == NULL){
            if (i != index) {
                return head; //if the index given is larger than the size of the linked list, don't delete anything
            }
        }
        previousNode = currentNode;
        currentNode = currentNode->next;
        i++;
    }
    previousNode->next = currentNode->next;
    
    return head;
}

Node* edit(Node* head, int index, string newText){
    Node* newNode = new Node;
    newNode->value = newText;
    
    //if invalid index
    if(index <=0){
        return head;
    }
    
    //if empty list then ignore edit command
    if(head->value == "NULL" && index == 1){
        return head;
    }
    
    //if index equals 1 and list is not empty then move
    if (index == 1){
        newNode->next = head->next;
        head = newNode;
    }
    
    Node *currentNode = new Node;
    Node *previousNode = new Node;
    
    currentNode = head;
    
    int i = 0;
    while (i < index-1){
        if (currentNode->next == NULL){
            if (i != index) {
                return head; //if the index given is larger than the size of the linked list, don't edit anything
            }
        }
        previousNode = currentNode;
        currentNode = currentNode->next;
        i++;
    }
    newNode->next = currentNode->next;
    previousNode->next = newNode;
    
    return head;
}

void print (Node* head){
    
    //if empty list
    if(head->value == "NULL"){
        return;
    }
    
    Node *currentNode = new Node;
    currentNode = head;
    
    //prints the linked list
    if (currentNode->next == NULL){
        std::cout << "1 " << currentNode->value << std::endl;
    }
    else{
        int count = 1;
        while (currentNode != NULL){
            if (currentNode->next == NULL){
                std::cout << count << " " << currentNode->value << std::endl;
                count ++;
            }
            else{
                std::cout << count << " " << currentNode->value << std::endl;
                count ++;
            }
            currentNode = currentNode->next;
        }
    }
}

void search(Node* head, string searchString){
    
    //if empty list then ignore search command
    if(head->value == "NULL" && head->next == NULL){
        return;
    }
    
    Node *node = new Node;
    node = head;
    
    int count = 0;
    string located = "";
    
    int hit = 0;
    while (node != NULL){
        //attempts to locate the string in each node
        if ((node->value).find(searchString) != std::string::npos){
            located += std::to_string(count+1) + " " + node->value;
            std::cout << located << std::endl;
            located = "";
            hit += 1;
        }
        node = node->next;
        count++;
    }
    
    if (hit == 0) std::cout << "not found" << std::endl;
}


void LineEditor(Node* head){
    string line;
    string verifyFormat = "\"";
    
    //gets all lines of input as the entire line
    while (getline(cin, line)) {
        
        string text = "";
        stringstream ss;
        string stringIndex;
        int numIndex;
        
        //each if/else if finds which command is being used
        if(line.substr(0,9)=="insertEnd"){
            size_t found=line.find(verifyFormat); //verifies correct format of command (that is has quotes)
            text = line.substr(11, (line.length()-12)); //isolates text to be added to linked list
            
            //verifies valid format and text is not greater than 80 characters
            if (text.length() <= 80 && found!=string::npos){
                head = insertEnd(head, text);
            }
            else{
                continue;
            }
        }
        
        else if(line.substr(0,7)== "insert "){
            size_t found=line.find(verifyFormat); //verifies correct format of command (that is has quotes)
            char index = line[7]; //isolates index to pass into insert() function
            char indexTwo = line[8]; //notes the character
            char indexThree = line[9]; //notes the character
            
            //if indexTwo is a space then that means the index is only one digit
            if(int(indexTwo) == 32){
                ss << index;
                ss >> numIndex;
                text = line.substr(10, (line.length()-11));
            }
            //if indexThree is a space then that means the index is two digits
            else if(int(indexThree) == 32){
                stringIndex = line.substr(7,2);
                text = line.substr(11, (line.length()-12));
                numIndex = stoi(stringIndex);
            }
            //else the index is 3 digits
            else{
                stringIndex = line.substr(7,3);
                text = line.substr(12, (line.length()-13));
                numIndex = stoi(stringIndex);
            }
            
            if(text.length() <= 80 && found!=string::npos){
                head = insert(head, numIndex, text);
            }
            else{
                continue;
            }
        }
        
        else if(line.substr(0,6) == "delete"){
            //isolate index using same logic as insert
            char index = line[7];
            char indexTwo = line[8];
            char indexThree = line[9];
            
            if(int(indexTwo) == 32){
                ss << index;
                ss >> numIndex;
            }
            else if(int(indexThree) == 32){
                stringIndex = line.substr(7,3);
                numIndex = stoi(stringIndex);
            }
            else{
                stringIndex = line.substr(7,4);
                numIndex = stoi(stringIndex);
            }
            head = deleteValue(head, numIndex);
        }
        
        else if(line.substr(0,4) == "edit"){
            //isolate index and verify format using same logic as insert
            size_t found=line.find(verifyFormat);
            char index = line[5];
            char indexTwo = line[6];
            char indexThree = line[7];
            
            if(int(indexTwo) == 32){
                ss << index;
                ss >> numIndex;
                text = line.substr(8, (line.length()-9));
            }
            else if(int(indexThree) == 32){
                stringIndex = line.substr(5,2);
                text = line.substr(9, (line.length()-10));
                numIndex = stoi(stringIndex);
            }
            else{
                stringIndex = line.substr(5,3);
                text = line.substr(10, (line.length()-11));
                numIndex = stoi(stringIndex);
            }
            
            if(text.length() <= 80 && found!=string::npos){
                head = edit(head, numIndex, text);
            }
            else{
                continue;
            }
        }
        
        else if(line.substr(0,5) == "print"){
            print(head);
        }
        
        else if(line.substr(0,6) == "search"){
            size_t found=line.find(verifyFormat); //verify format using same logic as insertEnd
            text = line.substr(8, (line.length()-9));
            if(found!=string::npos){
                search(head, text);
            }
            else{
                continue;
            }
        }
        
        else if(line.substr(0,4) == "quit"){
            break;
        }
        else{
            continue; //any command called other than the specified ones will be ignored
        }
        
    }
}

int main()
{
    Node *head = new Node;
    head->value = "NULL";
    
    LineEditor(head);
}
