#ifndef __AVL_HPP_
#define __AVL_HPP_

#include <iostream>
#include <fstream>
#include <stack>

using namespace std;



class AVL {
private:
  class Node {
    Node *parent, *left, *right;
    int height;
    string element;

  public:
    Node(const string& e, Node *parent, Node *left, Node *right);
    
    Node*  getParent() const;
    Node*  getLeft() const;
    Node*  getRight() const;
    string getElement() const;
    int    getHeight() const;
  
    void setLeft(Node *);
    void setRight(Node *);
    void setParent(Node *);
    void setElement(string e);
    
    
    bool isLeft() const;
    bool isRight() const;
    int  rightChildHeight() const;
    int  leftChildHeight() const;
    int  updateHeight();
    bool isBalanced();
  };
private:
  
  int   size;
  Node* root;
  
public:
    
    class Iterator {
      
    public:
      Iterator(AVL::Node* );
      Iterator& operator++();
      Iterator operator++(int a);
      string operator*(); 
      bool operator!=(Iterator it);
      bool operator==(Iterator it);
      AVL::Node * curr_Node();
      
    private:
        struct stack< Node* > all_Nodes;
        bool left_poped;
    };
    
  Iterator begin() const;  
  Iterator end() const;
  
  static const int MAX_HEIGHT_DIFF = 1;
  AVL();
  AVL(const AVL& );
  void simpleRight(Node* , Node*);
  void simpleLeft(Node*, Node*);
  void firstLeft(Node* , Node*); // Ston patera ginetai mia peristrofh
  void firstRight(Node*, Node*);
  bool contains(string e);
  bool add(string e);
  bool rmv(string e);
  void print2DotFile(char *filename);
  void pre_order(ostream& out);
  void del(Node*); // Diagrafh olwn twn komvwn tou dentrou. Xrhsimevei sthn yperfortwsh tou telesth ison
  
  friend std::ostream& operator<<(ostream& out, const AVL& tree);  
  AVL& operator  =(const AVL& avl);
  AVL  operator  +(const AVL& avl);
  AVL& operator +=(const AVL& avl);
  AVL& operator +=(const string& e);
  AVL& operator -=(const string& e);
  AVL  operator  +(const string& e);
  AVL  operator  -(const string& e);
};

#endif
