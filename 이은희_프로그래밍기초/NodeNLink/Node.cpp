#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif
#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>
#include <iostream>


struct Node
{
    Node() = delete;
    Node(const char* str) : pLinkNode(nullptr)
    {
        strcpy_s(this->str, str);
    }
    char str[32] = "";
    Node* pLinkNode;
};

Node* g_NodePtr = nullptr;

void AddNode(const char* str)
{
    Node* pNewNode = new Node(str);

    pNewNode->pLinkNode = g_NodePtr;
    g_NodePtr = pNewNode;
}

void PrintNode()
{
    Node* pLink = g_NodePtr;
    while (pLink)
    {
        std::cout << pLink->str << "도 있고 \n";
        pLink = pLink->pLinkNode;
    }
}

void DeleteNode()
{
    Node* tempPtr;
    // 교수님, 저도 할 거 주세요...
    // 네..이거 해요.
    while (g_NodePtr != nullptr)
    {
        tempPtr = g_NodePtr->pLinkNode;

        delete g_NodePtr;

        g_NodePtr = tempPtr;
    }
}

int main()
{
    // 첫 줄은 꼭 이 함수를 호출하고 시작 합니다.
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    //_CrtSetBreakAlloc(160);

    std::cout << "시장에 가면 \n";

    AddNode("사과");
    AddNode("배");
    AddNode("귤");

    DeleteNode();

    PrintNode();

   

    return 0;
}

