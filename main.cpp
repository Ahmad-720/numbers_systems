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

std::string decimal_to_hexa(int n){
    std::string result = ""; 
    std::string tmp;
    node *head = decimal_to_binary(n);
    while(!list_is_empty(head)){
        node *mini = last_four_digits(&head);
        char x = get_hexa(&mini);
        tmp = result;
        result = x + tmp;
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
            std::cout << binary_to_decimal(n) << "\n";
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
            std::cout << decimal_to_hexa(n)<<"\n";
        }
        else if(command.compare("help") == 0){
            std::cout << "1: binary to decimal.\n";
            std::cout << "2: decimal to binary.\n";
            std::cout << "3: decimal to hexadecimal.\n";
            std::cout << "exit: to exit.\n";
        }
    }
}