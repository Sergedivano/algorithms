//--------------------------------- Стек  --------------------------------------
// 18 (9). Организовать в основной памяти с помощью указателей стек из очередей. 
//         Обеспечить операции:
//          - ведения очереди из вершины стека, 
//          - расширения и сокращения стека, 
//          - выдачи содержимого стека.
//
//                  Сергей Домрачев 30.01.2023
//------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

struct QueueEl
{
    char item;
    QueueEl *next;
};

struct NodeQueue
{
    QueueEl *first;
    QueueEl *last;
};

struct StackEl
{
    NodeQueue queue;
    StackEl *next;
};

struct NodeStack
{
    StackEl *first;
};

void menu();

void printMessages();

void printQueue(NodeQueue queue);                           // Показать содержимое очереди.

void printStack(NodeStack stack);                           // Показать содержимое стека.

void pushStack(StackEl *&first, NodeQueue queue);           // Добавить элемент в существующую вершину стека.

void pushQueue(QueueEl *&first, QueueEl *&last, char ch);   // Добавить элемент в очередь.

void pushQueueInStack(NodeStack &stack);                    // Создать и поместить очередь в стек.

void popStackEl(NodeStack &stack);                          // Удалить элемент из существующей вершины стека.

void popQueue(QueueEl *&first);                             // Удалить элемент из очереди.

void addTopStack(NodeStack &stack);                         // Добавить элемент в существующую вершину стека.

void removeTopStackEl(NodeStack &stack);                    // Удалить элемент из существующей вершины стека.

int main()
{
    menu();
    return 0;
}

void printMessages()
{
    std::string infoMessages[] = {
        "Console program organizes a stack of queues in main memory using pointers. It provides operations for queuing from the top of the stack, expanding and shrinking the stack, and issuing the contents of the stack"
        //"Консольная программа организовывает в основной памяти с помощью указателей стек из очередей. Обеспечивает операции ведения очереди из вершины стека, расширения и сокращения стека, выдачи содержимого стека"
    };

    for (auto &infoMessage: infoMessages)
    {
        std::cout << infoMessage << std::endl;
    }

    std::cout << std::endl;

    std::string controlMessages[] = {
        "Control: ",                                                 // Управление:
        "0. Exit the program.",                                      // 0. Выход из программы.
        "1. Create and push a queue in the stack.",                  // 1. Создать и поместить очередь в стек.
        "2. Remove the top of the stack.",                           // 2. Удалить вершину стека.
        "3. Add element to existing stack top.",                     // 3. Добавить элемент в существующую вершину стека.
        "4. Remove an element from the existing top of the stack.",  // 4. Удалить элемент из существующей вершины стека.
        "5. Show stack contents.",                                   // 5. Показать содержимое стека.
    };

    for (auto &startMessage: controlMessages)
    {
        std::cout << startMessage << std::endl;
    }
}

void menu()
{
    printMessages();

    std::string menuMessages[] = {
        "Enter '#' to end input of queue elements.",      // Для окончания ввода элементов очереди введите '#'.
        "Stack contents: ",                               // Содержимое стека: 
    };

    char ch;
    char exit = '0';
    NodeStack stack{nullptr};

    while (std::cin >> ch && ch != exit)
    {
        if (ch == '1')
        {
            std::cout << menuMessages[0] << std::endl;
            pushQueueInStack(stack);
        }
        else if (ch == '2')
        {
            if (stack.first && stack.first->queue.first != nullptr)
            {
                removeTopStackEl(stack);
            }
        }    
        else if (ch == '3')
        {
            if (stack.first != nullptr)
            {
                std::cout << menuMessages[0] << std::endl;
                addTopStack(stack);
            }
        }    
        else if (ch == '4')
        {
            if (stack.first)
            {
                popStackEl(stack);
            }
        }
        else if (ch == '5')
        {
            if (stack.first)
            {
                std::cout << menuMessages[1] << std::endl;
            }
            printStack(stack);
        }
    }    
}

void popStackEl(NodeStack &stack)
{
    auto tempEl = stack.first;
    stack.first = stack.first->next;
    delete tempEl;
}

void pushStack(StackEl *&first, NodeQueue queue)
{
    auto nextEl = new StackEl{queue, nullptr};

    if (first != nullptr)
    {
        nextEl->next = first;
    }

    first = nextEl;
}

void pushQueue(QueueEl *&first, QueueEl *&last, char ch)
{
    auto nextEl = new QueueEl{ch, nullptr};

    if (first == nullptr)
    {
        first = nextEl;
    }
    else
    {
        last->next = nextEl;
    }

    last = nextEl;
}

void printQueue(NodeQueue queue)
{
    QueueEl tempQueue{};
    tempQueue = *queue.first;

    while (tempQueue.next != nullptr)
    {
        std::cout << tempQueue.item;
        tempQueue = *tempQueue.next;
    }
    std::cout << tempQueue.item << std::endl;
}

void printStack(NodeStack stack)
{

    if (stack.first)
    {
        StackEl tempStack{};
        tempStack = *stack.first;

        while (tempStack.next != nullptr)
        {
            printQueue(tempStack.queue);
            tempStack = *tempStack.next;
        }
        printQueue(tempStack.queue);
    }
}

void pushQueueInStack(NodeStack &stack)
{
    char ch;
    NodeQueue queue{nullptr, nullptr};

    while (std::cin >> ch && ch != '#')
    {
        pushQueue(queue.first, queue.last, ch);
    }

    pushStack(stack.first, queue);
}

void addTopStack(NodeStack &stack)
{
    char el;

    while (std::cin >> el && el != '#')
    {
        pushQueue(stack.first->queue.first, stack.first->queue.last, el);
    }
}

void removeTopStackEl(NodeStack &stack)
{
    if (stack.first->queue.first->next == nullptr)
    {
        popStackEl(stack);
        return;
    }

    popQueue(stack.first->queue.first);
}

void popQueue(QueueEl *&first)
{
    first = first->next;
}