#include <iostream>
#include <math.h>
#include <string>

typedef int element;

struct node{
    element data;
    node *link;
};

node *create_list(){
    return NULL;
}

void push_at_beginning(node **H,int data){
    node *node_to_push = new node;
    node_to_push->data = data;
    node_to_push->link = NULL;
    if(*H == NULL){
        *H = node_to_push;
    }
    else{
        node_to_push->link = *H;
        *H = node_to_push;
    }
}

element delete_tail(node **H){
    if(*H == NULL){
        std::cout << "List is empty.\n";
    }
    else if((*H)->link == NULL){
        element result = (*H)->data;
        delete *H;
        *H = NULL;
        return result;
    }
    else{
        node *ptr = *H;
        node *pre;
        while(ptr->link != NULL){
            pre = ptr;
            ptr = ptr->link;
        }
        pre->link = NULL;
        element result = ptr->data;
        delete ptr;
        return result;
    }

}

element get_head(node **H){
    if(*H == NULL){
        std::cout << "list is empty.\n";
    }
    else{
        element result = (*H)->data;
        node *next = (*H)->link;
        delete (*H);
        (*H) = next;
        return result;
    }
}

bool list_is_empty(node *head){
    return head == NULL;
}

void print_list(node *head){
    node *ptr = head;
    while(ptr != NULL){
        std::cout << ptr->data;
        ptr = ptr->link;
    }
    std::cout << "\n";
}

node *fill_list(int n){
    node *head = create_list();
    while(n > 0){
        push_at_beginning(&head,n%10);
        n = n/10;
    }
    return head;
}

int count_nodes(node *head){
    int count = 0;
    node *ptr = head;
    while(ptr != NULL){
        count += 1;
        ptr = ptr->link;
    }
    return count;
}

node * decimal_to_binary(int n){
    node *list = create_list();
    while(true){
        if(n == 1 || n == 0){
            push_at_beginning(&list,n);
            break;
        }
        push_at_beginning(&list,n%2);
        n = n/2;
    }
    return list;
}

int binary_to_decimal(int binary){
    node *head = fill_list(binary);
    int result = 0,i = 0;
    while(!list_is_empty(head)){
        result += delete_tail(&head)*pow(2,i);
        i += 1;
    }
    return result;
}

bool valid_binary(int n){
    while(n > 0){
        if(n%10 != 0 && n%10 != 1){
            return false;
        }
        n = n/10;
    }
    return true;
}

node *last_four_digits(node **H){
    node *result_head = create_list();
    for(int i = 0;i < 4;i++){
        if(list_is_empty(*H)){
            return result_head;
        }
        push_at_beginning(&result_head,delete_tail(H));
    }
    return result_head;
}

char get_hexa(node **H){
    int i = 0;
    char result;
    int x = 0;
    while(!list_is_empty(*H)){
        x += delete_tail(H)*pow(2,i);
        i += 1;
    }
    char arr[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    return arr[x];
}

char decimal_digit_in_hexa(int n){
    switch(n){
        case 0:
        return '0';
        case 1:
        return '1';
        case 2:
        return '2';
        case 3:
        return '3';
        case 4:
        return '4';
        case 5:
        return '5';
        case 6:
        return '6';
        case 7:
        return '7';
        case 8:
        return '8';
        case 9:
        return '9';
        case 10:
        return 'A';
        case 11:
        return 'B';
        case 12:
        return 'C';
        case 13:
        return 'D';
        case 14:
        return 'E';
        case 15:
        return 'F';
    }
    return ' ';
}

std::string decimal_to_hexa(int n){
    std::string result = ""; 
    while(n > 0){
        char x = decimal_digit_in_hexa(n%16);
        std::string tmp = result;
        result = x + tmp;
        n = n/16;
    }
    return result;
}

node *hexa_digit_in_binary(char character){
    if((character < '0' || character > '9') && (character < 'A' || character > 'F')){
        return NULL;
    }
    node *head = create_list();
    switch (character){
        case '0':
        head = fill_list(0);
        break;
        case '1':
        head = fill_list(1);
        break;
        case '2':
        head = fill_list(10);
        break;
        case '3':
        head = fill_list(11);
        break;
        case '4':
        head = fill_list(100);
        break;
        case '5':
        head = fill_list(101);
        break;
        case '6':
        head = fill_list(110);
        break;
        case '7':
        head = fill_list(111);
        break;
        case '8':
        head = fill_list(1000);
        break;
        case '9':
        head = fill_list(1001);
        break;
        case 'A':
        head = fill_list(1010);
        break;
        case 'B':
        head = fill_list(1011);
        break;
        case 'C':
        head = fill_list(1100);
        break;
        case 'D':
        head = fill_list(1101);
        break;
        case 'E':
        head = fill_list(1110);
        break;
        case 'F':
        head = fill_list(1111);
        break;
    }
    return head;
}

void fill_space(node **H){
    int nb = count_nodes(*H);
    if(nb >= 4){
        return;
    }
    while(nb < 4){
        push_at_beginning(H,0);
        nb += 1;
    }
}

node *hexa_decimal_to_binary(const std::string& number){
    node *head = create_list();
    node *tmp = create_list();
    for(int i = number.length() - 1;i >= 0; i--){
        tmp = hexa_digit_in_binary(number[i]);
        fill_space(&tmp);
        if(list_is_empty(head)){
            head = tmp;
        }
        else{
            node *tail = tmp;
            while(tail->link != NULL){
                tail = tail->link;
            }
            tail->link = head;
            head = tmp;
        }
    }
    return head;
}

bool valid_hexa(const std::string& number){
    for(int i = 0; i < number.length();i++){
        if((number[i] < '0' || number[i] > '9') && (number[i] < 'A' || number[i] > 'F')){
            return false;
        }
    }
    return true;
}

int hexa_digit_in_decimal(char character){
    switch(character){
        case '0':
        return 0;
        case '1':
        return 1;
        case '2':
        return 2;
        case '3':
        return 3;
        case '4':
        return 4;
        case '5':
        return 5;
        case '6':
        return 6;
        case '7':
        return 7;
        case '8':
        return 8;
        case '9':
        return 9;
        case 'A':
        return 10;
        case 'B':
        return 11;
        case 'C':
        return 12;
        case 'D':
        return 13;
        case 'E':
        return 14;
        case 'F':
        return 15;
    }   
    return -1;
}

int hexa_decimal_to_decimal(const std::string& number){
    int result = 0;
    for(int i = 0;i < number.length();i++){
        result += hexa_digit_in_decimal(number[number.length() - (i+1)])*pow(16,i);
    }
    return result;
}

int main(){
    bool running = true;
    std::string command;
    while(running){
        std::cout << "> ";
        std::getline(std::cin,command);
        if(command.compare("exit") == 0){
            running = false;
        }
        else if(command.compare("1") == 0){
            int n;
            int valid_type = scanf("%d",&n);
            fflush(stdin);
            if(valid_type == 0){
                std::cout << "entry must be an integer.\n";
                continue;
            }
            if(!valid_binary(n)){
                std::cout << "must be a binray number.\n";
                continue;
            }
            std::cout<< "decimal: " << binary_to_decimal(n) << "\n";
        }
        else if(command.compare("2") == 0){
            int n;
            int valid_type = scanf("%d",&n);
            fflush(stdin);
            if(valid_type == 0){
                std::cout << "entry must be an integer.\n";
                continue;
            }
            node *head =  decimal_to_binary(n);
            std::cout << "binary: ";
            print_list(head);
            while(!list_is_empty(head)){
                get_head(&head);
            }
        }
        else if(command.compare("3") == 0){
            int n;
            int valid_type = scanf("%d",&n);
            fflush(stdin);
            if(valid_type == 0){
                std::cout << "entry must be an integer.\n";
                continue;
            }
            std::cout << "hexadecimal: " << decimal_to_hexa(n)<<"\n";
        }
        else if(command.compare("4") == 0){
            std::string number;
            std::getline(std::cin,number);
            if(!valid_hexa(number)){
                std::cout << "invalid hexa number.\n";
                continue;
            }
            std::cout << "decimal: "<<hexa_decimal_to_decimal(number) << "\n";
        }
        else if(command.compare("5") == 0){
            std::string number;
            std::getline(std::cin,number);
            if(!valid_hexa(number)){
                std::cout << "invalid hexa number.\n";
                continue;
            }
            node *head = hexa_decimal_to_binary(number);
            std::cout << "binary: ";
            print_list(head);
            while(!list_is_empty(head)){
                get_head(&head);
            }

        }
        else if(command.compare("help") == 0){
            std::cout << "1: binary to decimal.\n";
            std::cout << "2: decimal to binary.\n";
            std::cout << "3: decimal to hexadecimal.\n";
            std::cout << "4: hexadecimal to decimal.\n";
            std::cout << "5: hexdecimal to binary.\n";
            std::cout << "exit: to exit.\n";
        }
    }
}