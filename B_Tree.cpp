

#include <iostream>
#define M 7
using namespace std;

// B-Tree의 노드 구조체 선언
struct B_Tree_Node      // 구조체 선언
{
    int* data;          // 자료의 배열 
    B_Tree_Node** child_ptr;    // 노드 포인트 배열
    bool leafN;                 // 리프 노드인지 확인한다.
    int n;                      // 자료의 개수
}*root = NULL, * np = NULL, * x = NULL;


// 노드 초기화 함수
B_Tree_Node* init()
{
    int i;
    np = new B_Tree_Node;                   // 객체를 할당한다.
    np->data = new int[M];                  // 최대 M개까지 데이터를 가질 수 있다.
    np->child_ptr = new B_Tree_Node * [6];  // M + 1개의 자식 노드
    np->leafN = true;                      
    np->n = 0;                            
    for (i = 0; i < 6; i++)
    {
        np->child_ptr[i] = NULL;            // 각 자식 노드 초기화
    }
    return np;
}


// 순회 함수
void traverse(B_Tree_Node* p)
{
    cout << endl;
    int i;
    

    for (i = 0; i < p->n; i++)
    {
        // 리프 노드가 아니면 밑으로 내려간다.
        if (p->leafN == false)
        {
            traverse(p->child_ptr[i]);
        }
        
        cout << " " << p->data[i];
    }

    // 리프 노드가 아니면 밑으로 내려간다.
    if (p->leafN == false)
    {
        traverse(p->child_ptr[i]);
    }
    cout << endl;
}

// n개의 배열 데이터를 정렬하는 함수
void sort(int* p, int n)
{
    int i, j, t;
    for (i = 0; i < n; i++)
    {
        for (j = i; j <= n; j++)
        {
            if (p[i] > p[j])
            {
                t = p[i];
                p[i] = p[j];
                p[j] = t;
            }
        }
    }
}


// 자식 분할 함수
int Split_Child(B_Tree_Node* x, int i)
{

    int j, mid;
    B_Tree_Node* np1, * np3, * y;

    np3 = init();
    np3->leafN = true;

    if (i == -1)
    {

        // M의 중간값이 분할 기준이다.
        mid = x->data[M / 2];
        x->data[M / 2] = 0;
        x->n--;
        np1 = init();

        // np1는 부모 노드 
        np1->leafN = false;
        x->leafN = true;
        for (j = M / 2 + 1; j < M; j++)
        {

            
            np3->data[j - (M / 2 + 1)] = x->data[j];
            np3->child_ptr[j - (M / 2 + 1)] = x->child_ptr[j];
            np3->n++;
         
            x->data[j] = 0;
            x->n--;
        }

        // x의 자식 노드가 NULL이 된다.
        for (j = 0; j < M + 1; j++)
        {
            x->child_ptr[j] = NULL;
        }
        np1->data[0] = mid;
        np1->child_ptr[np1->n] = x;
        np1->child_ptr[np1->n + 1] = np3;
        np1->n++;

        // 루트 노드로 설정
        root = np1;
    }

    // 부모 노드가 있는 경우
    else
    {
        y = x->child_ptr[i];
        mid = y->data[M / 2];
        y->data[M / 2] = 0;
        y->n--;
        for (j = M / 2 + 1; j < M; j++)
        {          
            np3->data[j - (M / 2 + 1)] = y->data[j];
            np3->n++;
            y->data[j] = 0;
            y->n--;
        }
        x->child_ptr[i + 1] = y;
        x->child_ptr[i + 1] = np3;
    }
    return mid;
}

// 원소 a를 삽입하는 함수
void insert(int a)
{
    int i, t;
    x = root;

    if (x == NULL)
    {
        root = init();
        x = root;
    }

    else
    {
        if (x->leafN == true && x->n == M)
        {
            t = Split_Child(x, -1);
            x = root;

            for (i = 0; i < (x->n); i++)
            {
                if ((a > x->data[i]) && (a < x->data[i + 1]))
                {
                    i++;
                    break;
                }
                else if (a < x->data[0])
                {
                    break;
                }
                else
                {
                    continue;
                }
            }
            x = x->child_ptr[i];
        }

        // 리프노드가 아닐 때
        else
        {
            while (x->leafN == false)
            {
                for (i = 0; i < (x->n); i++)
                {
                    if ((a > x->data[i]) && (a < x->data[i + 1]))
                    {
                        i++;
                        break;
                    }
                    else if (a < x->data[0])
                    {
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }

                // 리프 노드 위에서 최대치를 넘으면 분할
                if ((x->child_ptr[i])->n == M)
                {
                    t = Split_Child(x, i);
                    x->data[x->n] = t;
                    x->n++;
                    continue;
                }
                else
                {
                    x = x->child_ptr[i];
                }
            }
        }
    }
    x->data[x->n] = a;
    sort(x->data, x->n);
    x->n++;
}

int main(void)
{
    int i, n, t;
    cout << "삽입할 원소의 개수 : ";
    cin >> n;
    for (i = 0; i < n; i++)
    {
        cout << "삽입될 원소 입력 : ";
        cin >> t;
        insert(t);
    }
    cout << "\n트리 순회를 시작합니다." << endl;
    traverse(root);
    return 0;
}


