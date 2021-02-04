#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <new>


template <typename TElem>
struct Stack_t {
    TElem *a;
    int sz;
    int max_sz;

    Stack_t() {
        a = nullptr;
        sz = 0;
        max_sz = 0;
    }

    ~Stack_t() {
        while (sz > 0) {
            pop();
        }
        free(a);
    }

    void push(TElem elem)  {
        if (sz == max_sz) {
            max_sz += (max_sz == 0);
            max_sz *= 2;
            a = (int*)realloc(a, max_sz * sizeof(TElem));
        }
        new (a + sz) TElem(elem);
        ++sz;
    }

    TElem top()  {
        return a[sz - 1];
    }

    TElem pop()  {
       return a[--sz];
    }
};


template <typename TElem>
struct Queue_t {
    Stack_t<TElem> stack_in;
    Stack_t<TElem> stack_out;
    int sz;

    Queue_t() {
        sz = 0;
    }

    void enqueue(int elem) {
        stack_in.push(elem);
        sz += 1;
    }

    TElem dequeue() {
        if (sz == 0) {
            printf("Error\n");
        } else {
            if (stack_out.sz == 0) {
                while (stack_in.sz > 0) {
                    TElem val = stack_in.pop();
                    stack_out.push(val);
                }
            }
            TElem val = stack_out.pop();
                sz -= 1;
                return val;
        }
    }

    TElem front() {
        if (sz == 0) {
            printf("Error\n");
        } else {
            if (stack_out.sz == 0) {
                while (stack_in.sz > 0) {
                    TElem val = stack_in.pop();
                    stack_out.push(val);
                }
            }
            TElem val = stack_out.top();
            return val;
        }
    }

    int q_size() {
        return sz;
    }
};


int main() {
    Queue_t<int> q;

    char str[100];

    while (1) {
        scanf("%s", str);

        if (strcmp(str, "exit") == 0) {
            break;
        }
        if (strcmp(str, "push") == 0) {
            int x = 0;
            scanf("%d", &x);
            q.enqueue(x);
            printf("Pushed %d\n", x);
        }
        if (strcmp(str, "pop") == 0) {
            if (q.sz > 0) {
                printf("Popped %d\n", q.dequeue());
            } else {
                printf("Error\n");
            }
        }
        if (strcmp(str, "front") == 0) {
            if (q.sz > 0) {
                printf("Front %d\n", q.front());
            } else {
                printf("Error\n");
            }
        }
        if (strcmp(str, "size") == 0) {
            printf("%d\n", q.q_size());
        }
    }

    return 0;
}