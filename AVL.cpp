
#include "AVL.hpp"



    AVL::Node::Node(const string& e, Node *parent, Node *left, Node *right) {

        this->element = e;
        this->left = left;
        this->right = right;
        this->parent = parent;
        this->height = 1;
    };

    AVL::Node* AVL::Node::getParent() const {
        return this->parent;
    };

    AVL::Node* AVL::Node::getLeft() const {
        return this->left;
    };

    AVL::Node* AVL::Node::getRight() const {
        return this->right;
    };

    string AVL::Node::getElement() const {
        return this->element;
    };

    int AVL::Node::getHeight() const {
        return this->height;
    };

    bool AVL::Node::isLeft() const {
        
        if(this->parent == NULL)
            return true;
        
        if(this->parent->left == this)
            return true;
        else
            return false;
    };

    bool AVL::Node::isRight() const {
        if(this->parent == NULL) // Ean einai h riza epistrefei true. Mou xreiazetai se alles 
            return true;
        
        if(this->parent->right == this)
            return true;
        else
            return false;
    };

    int AVL::Node::rightChildHeight() const {
        if(this->right == NULL)
            return 0;
        
        return this->right->height;
    };

    int AVL::Node::leftChildHeight() const {
        if(this->left == NULL)
            return 0;
        
        return this->left->height;
    };

    int AVL::Node::updateHeight() {
        
        if(this->left != NULL && this->right != NULL) {
            if(this->left->height > this->right->height)
                this->height = this->left->height + AVL::MAX_HEIGHT_DIFF;
            else
                this->height = this->right->height + AVL::MAX_HEIGHT_DIFF;
        }
        
        else {
            if(this->left != NULL) {
                this->height = this->left->height + AVL::MAX_HEIGHT_DIFF;
            }
            else {
                if(this->right != NULL)
                    this->height = this->right->height + AVL::MAX_HEIGHT_DIFF;
                else
                    this->height = AVL::MAX_HEIGHT_DIFF;
            }
            
            
        }
        
        return this->height;
        
    };


    bool AVL::Node::isBalanced() {
        int left_height = 0, right_height = 0;
        bool left_balanced = true, right_balanced = true;
        
        // Arxika elegxos oti yparxoun aristero kai deksi dentro.
        // Ean nai tote elegxw an kai afta einai balanced. An estw
        // kai ena den einai tote epistrefw diadoxika false mexri
        // na ftasw sth riza opoy kai afth tha epistrepsei false
        
        if(this == NULL)
            return true;
        
        
        if(this->left != NULL) {
            left_height = this->left->height;
            left_balanced = this->left->isBalanced();
        }
        
        if(this->right != NULL) {
            right_height = this->right->height;
            right_balanced = this->left->isBalanced();
        }
        

        if(right_height < left_height - AVL::MAX_HEIGHT_DIFF || right_height > left_height + AVL::MAX_HEIGHT_DIFF)
            return false;
        
        if(left_height < right_height - AVL::MAX_HEIGHT_DIFF || left_height > right_height + AVL::MAX_HEIGHT_DIFF)
            return false;
        
        if(!left_balanced || !right_balanced)
            return false;
        
        return(true);
    };

    void AVL::Node::setElement(string e) {
        this->element = e;
    };

    void AVL::Node::setParent(Node *new_parent) {
        this->parent = new_parent;
    //    new_parent = this->parent;
        
    };

    void AVL::Node::setRight(Node * right_child) {
    //    right_child = this->right;
        this->right = right_child;
    };

    void AVL::Node::setLeft(Node * left_child) {
    //    left_child = this->left;
        this->left = left_child;
        
    };

    AVL::Iterator::Iterator(AVL::Node* new_Node) {
        this->all_Nodes.push(new_Node);
        this->left_poped = false;
    }

    AVL::Iterator AVL::begin() const {
        AVL::Iterator it1(this->root);
        return(it1);
    }

    AVL::Iterator AVL::end() const {
        AVL::Iterator it1(this->root);
        
        
//        Node* curr_Node = this->root;
        /*
        while(true) {
            if(curr_Node->getRight() != NULL) {
                curr_Node = curr_Node->getRight();
            }
            else {
                if(curr_Node->getLeft() != NULL) {
                    curr_Node = curr_Node->getLeft();
                }
                else {
                    
                }
                    
            }
        }*/
        
        for(int i = 0; i < this->size - 1; i++) {
            ++it1;
        }
        
        return(it1);
    }

    // Prefix
    AVL::Iterator& AVL::Iterator::operator++() {
        
        
        Node* curr_Node = this->all_Nodes.top(); // Korifaio stoixeio
        
        
        if(curr_Node->getLeft() != NULL && !this->left_poped) {
            this->all_Nodes.push(curr_Node->getLeft());
        }
        
        else {
            if(curr_Node->getRight() != NULL) {
                this->all_Nodes.push(curr_Node->getRight());
                this->left_poped = false;
            }
            
            // Telikos elegxos... Ean kai ta dyo paidia einai NULL
            else {
                if(curr_Node->getParent() == NULL) {
                    this->all_Nodes.pop(); // Adeiazei to stack
                    return (*this);
                }
                
                this->all_Nodes.pop(); // Afairesh tou stoixeiou
                if(!this->all_Nodes.empty())
                    curr_Node = this->all_Nodes.top(); // Afairesh komvwn mexri na vrethei o prwtos
                
                else {
                    curr_Node = NULL;
                }
                
                while(true) {
                    
                    if(curr_Node == NULL || this->all_Nodes.empty())
                        break;
                    
                    // Mpainw mesa se afto to if mono ean kata thn epistrofh, o komvos pou elegxetai exei 2 Z
                    if((curr_Node->getRight() != NULL && curr_Node->getLeft() != NULL) ) {
    //                    this->all_Nodes.pop();
                        curr_Node = curr_Node->getRight();
                        break;
                    }
                    
                    
                    this->all_Nodes.pop();
                    if(this->all_Nodes.empty()) {
                        curr_Node = NULL;
                        break;
                    }
                    
                    curr_Node = this->all_Nodes.top();
                }
                
                if(curr_Node != NULL) {
                    if(!this->all_Nodes.empty())
                        this->all_Nodes.pop(); // Afairesh kai aftou poy exei deksi
                    
                    this->all_Nodes.push(curr_Node);
                }
                
            }
        }
        
        return *this;
    }

    // Postfix

    AVL::Iterator AVL::Iterator::operator++(int a) {
        Node* curr_Node = this->all_Nodes.top(); // Korifaio stoixeio
        Iterator old_Iterator = *this;
        
        
        if(curr_Node->getLeft() != NULL && !this->left_poped) {
            this->all_Nodes.push(curr_Node->getLeft());
        }
        
        else {
            if(curr_Node->getRight() != NULL) {
                this->all_Nodes.push(curr_Node->getRight());
                this->left_poped = false;
            }
            
            // Telikos elegxos... Ean kai ta dyo paidia einai NULL
            else {
                if(curr_Node->getParent() == NULL) {
                    this->all_Nodes.pop(); // Adeiazei to stack
                    return (*this);
                }
                
                this->all_Nodes.pop(); // Afairesh tou stoixeiou
                if(!this->all_Nodes.empty())
                    curr_Node = this->all_Nodes.top(); // Afairesh komvwn mexri na vrethei o prwtos
                
                while(true) {
                    
                    if(curr_Node == NULL)
                        break;
                    
                    if(curr_Node == NULL || this->all_Nodes.empty())
                        break;
                    
                    // Mpainw mesa se afto to if mono ean kata thn epistrofh, o komvos pou elegxetai exei 2 Z
                    if((curr_Node->getRight() != NULL && curr_Node->getLeft() != NULL) ) {
                        curr_Node = curr_Node->getRight();
                        break;
                    }
                    this->all_Nodes.pop();
                    if(this->all_Nodes.empty()) {
                        curr_Node = NULL;
                        break;
                    }
                    
                    curr_Node = this->all_Nodes.top();
                    
                }
                
                if(curr_Node != NULL) {
                    if(!this->all_Nodes.empty())
                        this->all_Nodes.pop(); // Afairesh kai aftou poy exei deksi
                    this->all_Nodes.push(curr_Node);
                }
                
            }
        }
        
        
        return old_Iterator;
    }

    string AVL::Iterator::operator*() {
        Node *curr_Node = this->all_Nodes.top();
        
        return (curr_Node->getElement());
    }

    bool AVL::Iterator::operator!=(Iterator it) {
        return((this->all_Nodes.top()) != (it.curr_Node())->getLeft());
    }

    bool AVL::Iterator::operator==(Iterator it) {
        return((this->all_Nodes.top()) == (it.curr_Node())->getLeft());
    }

    AVL::Node* AVL::Iterator::curr_Node() {
        return this->all_Nodes.top();
    }

    AVL::AVL() {
        size = 0;
        root = NULL;
    }

    AVL::AVL(const AVL& forCopy) {
        this->size = 0;
        this->root = NULL;
        
        AVL::Iterator it = forCopy.begin();
        
        for(int i = 0; i < forCopy.size; i++) {
            this->add(*it);
            ++it;
        }
        
    }

    bool AVL::contains(string e) {
        Iterator it = Iterator(this->root);
        
        for(int i = 0; i < this->size; i++) {
            if((*it) == e)
                return true;
            ++it;
        }
        return false;
        
    }

    bool AVL::add(string e) {
        Node* curr = this->root;
        Node * oldParent;
        bool left = false;
        
        if(curr == NULL) {
            Node* inserted = new Node(e, NULL, NULL, NULL);
            this->root = inserted;
            this->size = 1;
            return true;
        }
        
        while(true) {
            
            if(curr == NULL) {
                
                Node* inserted = new Node(e, oldParent, NULL, NULL);
                this->size++;
                
                if(left)
                    oldParent->setLeft(inserted);
                
                else
                    oldParent->setRight(inserted);
                inserted->updateHeight();
                oldParent->updateHeight();
                while(true) {
                    
                    
                    // Tha anevainw mexri na synantisw th riza kai an yparxei lathos sta epipeda to diorthwnw
                    
                    if(oldParent == NULL || inserted == NULL) // Gia opoio apo afta ftasoume prwto sth riza termatizw
                        break;
                    
                    
                    if(inserted->getParent() == oldParent) {
                        inserted->updateHeight();
                        oldParent->updateHeight();
                    }
                    
                    if(oldParent->getParent() == inserted) {
                        oldParent->updateHeight();
                        inserted->updateHeight();
                    }
                    
                    if(!oldParent->getParent()->isBalanced()) {
                        
                        if(inserted->isRight() && oldParent->isRight()) {
                            
                            simpleLeft(oldParent->getParent(), oldParent);
                            if(oldParent->getParent() == NULL)
                                this->root = oldParent;

                            if(inserted->getParent() == NULL)
                                this->root = inserted;
                            
                            continue;
                        }
                        
                        if(inserted->isLeft() && oldParent->isLeft()) {
                            simpleRight(oldParent->getParent(), oldParent);
                            if(oldParent->getParent() == NULL)
                                this->root = oldParent;

                            if(inserted->getParent() == NULL)
                                this->root = inserted;
                            continue;
                        }
                        
                        if(inserted->isRight() && oldParent->isLeft()) {
                            firstLeft(oldParent->getParent(), oldParent);
                            if(oldParent->getParent() == NULL)
                                this->root = oldParent;

                            if(inserted->getParent() == NULL)
                                this->root = inserted;
                            continue;
                        }
                        
                        if(inserted->isLeft() && oldParent->isRight()) {
                            firstRight(oldParent->getParent(), oldParent);
                            if(oldParent->getParent() == NULL)
                                this->root = oldParent;

                            if(inserted->getParent() == NULL)
                                this->root = inserted;
                            continue;
                        }
                        
                        if(oldParent->getParent() == NULL)
                            this->root = oldParent;
                        
                        if(inserted->getParent() == NULL)
                            this->root = inserted;
                    }
                    
                    oldParent = oldParent->getParent();
                    
                    // O inserted meta apo edw arxizei kai ginetai o gios tou oldParent apla. Afto symvainei gia thn eksetash twn arxeiwn
                    inserted = inserted->getParent();
                }
                
                // Ananewsh twn ypswn kai gia tous goneis
                
                return true;
            }
            
            if(curr->getElement() == e)
                break;
            
            int size; // Mhkos lekshs
            
            if(e.size() < curr->getElement().size())
                size = e.size();
            else
                size = curr->getElement().size();
            
            for(int i = 0; i < size; i++) {
                if(curr->getElement().at(i) > e.at(i)) {
                    oldParent = curr;
                    curr = curr->getLeft();
                    left = true;
                    break;
                }
                
                if(curr->getElement().at(i) < e.at(i)) {
                    oldParent = curr;
                    curr = curr->getRight();
                    left = false;
                    break;
                }
                
                if(i == size - 1) {
                    if(curr->getElement().size() < e.size()) {
                        oldParent = curr;
                        curr = curr->getRight();
                        left = false;
                        break;
                    }
                    else {
                        oldParent = curr;
                        curr = curr->getLeft();
                        left = true;
                        break;
                    }
                }
            }
            
        }
        return false;
    }

    bool AVL::rmv(string e) {
        Node* fordelete = NULL;
        Node* left_nodes = NULL;
        string buff = "";
        Node* curr = this->root;
        
        while(true) {
            if(curr == NULL)
                break;
            
            if(curr->getElement() == e) {
                fordelete = curr;
                break;
            }
            
            int size; // Mhkos lekshs
            if(e.size() < curr->getElement().size())
                size = e.size();
            else
                size = curr->getElement().size();
            
            for(int i = 0; i < size; i++) {
                if(curr->getElement().at(i) > e.at(i)) {
                    curr = curr->getLeft();
                    break;
                }
                
                if(curr->getElement().at(i) < e.at(i)) {
                    curr = curr->getRight();
                    break;
                }
                
                if(i == size - 1) {
                    if(curr->getElement().size() < e.size()) {
                        curr = curr->getRight();
                        break;
                    }
                    else {
                        curr = curr->getLeft();
                        break;
                    }
                }
            }
                
        }
        
        if(fordelete == NULL)
            return false;
        
        left_nodes = fordelete->getRight();
        
        if(fordelete->getLeft() == NULL && fordelete->getRight() == NULL) { // Ean einai fyllo ksekinaw diagrafh
                    Node* parent = fordelete->getParent();
                    
                    if(parent != NULL) {
                        if(fordelete->isLeft())
                            parent->setLeft(NULL);
                        else
                            parent->setRight(NULL);
                        
                        fordelete->setParent(NULL);
                        delete fordelete;
                        fordelete = parent;
                        this->size--;
                        while(true) {
                
                if(fordelete == NULL)
                    break;
                
                
                
                if(!fordelete->isBalanced()) {
                    
                    if(fordelete->rightChildHeight() > fordelete->leftChildHeight() + AVL::MAX_HEIGHT_DIFF) {
                        if(fordelete->getRight()->leftChildHeight() <= fordelete->getRight()->rightChildHeight()) {
                            simpleLeft(fordelete, fordelete->getRight());
                            
                            if(fordelete->getParent()->getParent() == NULL)
                                this->root = fordelete->getParent();
                        }
                        
                        else {
                            firstRight(fordelete, fordelete->getRight());
                            
                            if(fordelete->getParent()->getParent() == NULL)
                                this->root = fordelete->getParent();
                        }
                    }
                    
                    if(fordelete->leftChildHeight() > fordelete->rightChildHeight() + AVL::MAX_HEIGHT_DIFF) {
                        if(fordelete->getLeft()->rightChildHeight() <= fordelete->getLeft()->leftChildHeight()) {
                            simpleRight(fordelete, fordelete->getLeft());
                            
                            if(fordelete->getParent()->getParent() == NULL)
                                this->root = fordelete->getParent();
                        }
                        
                        else {
                            firstLeft(fordelete, fordelete->getLeft());
                            
                            if(fordelete->getParent()->getParent() == NULL)
                                this->root = fordelete->getParent();
                        }
                    } 
                    
                    
                }
                fordelete->updateHeight();
                fordelete = fordelete->getParent();
                
            }
                        
                        return true;
                    }
                    
                    else { // Ean einai riza
                        this->size--;
                        this->root = NULL;
                        delete fordelete;
                        return true;
                    }
                    
                    
                    
                }
        
        
        
        if(left_nodes == NULL) {
                    
            left_nodes = fordelete;
                    
                    
        }
        
        while(left_nodes->getLeft() != NULL) {
            left_nodes = left_nodes->getLeft();
        }
        
        buff = fordelete->getElement();
                
            
            if(left_nodes->getLeft() == NULL && left_nodes->getRight() != NULL) {
//                buff = left_nodes->getRight()->getElement();
                fordelete->setElement(left_nodes->getElement());
                left_nodes->getParent()->setRight(left_nodes->getRight());
                left_nodes->getRight()->setParent(left_nodes->getParent());
                delete left_nodes;
                this->size--;
            }
            else {
                fordelete->setElement(left_nodes->getElement());
                left_nodes->setElement(buff);

                // Analoga ti einai o left node ton afairw apo ton patera tou
                if(left_nodes->isLeft())
                    left_nodes->getParent()->setLeft(NULL);
                else
                    left_nodes->getParent()->setRight(NULL);
                left_nodes->getParent()->updateHeight();
                fordelete = left_nodes->getParent();
                left_nodes->setParent(NULL);
                delete left_nodes;
                this->size--;
            }
            while(true) {
                
                if(fordelete == NULL)
                    break;
                
                
                if(!fordelete->isBalanced()) {
                if(fordelete->rightChildHeight() > fordelete->leftChildHeight() + AVL::MAX_HEIGHT_DIFF) {
                        if(fordelete->getRight()->leftChildHeight() <= fordelete->getRight()->rightChildHeight()) {
                            simpleLeft(fordelete, fordelete->getRight());
                            
                            if(fordelete->getParent()->getParent() == NULL)
                                this->root = fordelete->getParent();
                        }
                        
                        else {
                            firstRight(fordelete, fordelete->getRight());
                            
                            if(fordelete->getParent()->getParent() == NULL)
                                this->root = fordelete->getParent();
                        }
                    }
                    
                    if(fordelete->leftChildHeight() > fordelete->rightChildHeight() + AVL::MAX_HEIGHT_DIFF) {
                        if(fordelete->getLeft()->rightChildHeight() <= fordelete->getLeft()->leftChildHeight()) {
                            simpleRight(fordelete, fordelete->getLeft());
                            
                            if(fordelete->getParent()->getParent() == NULL)
                                this->root = fordelete->getParent();
                        }
                        
                        else {
                            firstLeft(fordelete, fordelete->getLeft());
                            
                            if(fordelete->getParent()->getParent() == NULL)
                                this->root = fordelete->getParent();
                        }
                    } 
                }
                fordelete->updateHeight();
                fordelete = fordelete->getParent();
                
            }
        
        return true;
    }
    // Orisma panw apo 2
    void AVL::simpleRight(Node* parent, Node* oldParent) {
        
        if(parent->getParent() != NULL) {
            if(parent->isLeft())
                parent->getParent()->setLeft(parent->getLeft());
            else
                parent->getParent()->setRight(parent->getLeft());
            oldParent->setParent(parent->getParent());
        }
        
        else
            oldParent->setParent(NULL);
        
        parent->setLeft(oldParent->getRight());
        
        if(oldParent->getRight() != NULL) {
            oldParent->getRight()->setParent(parent);
        }
        
        oldParent->setRight(parent);
        parent->setParent(oldParent);
        
        oldParent->getLeft()->updateHeight();
        
        if(oldParent->getRight() != NULL)
            oldParent->getRight()->updateHeight();
        
        parent->updateHeight();
        
            oldParent->getLeft()->updateHeight();
        
        if(oldParent->getRight() != NULL)
            oldParent->getRight()->updateHeight();
        oldParent->updateHeight();
    };

    void AVL::simpleLeft(Node* parent, Node* oldParent) {
        
            if(parent->getParent() != NULL) {
                if(parent->isLeft())
                    parent->getParent()->setLeft(parent->getRight());
                else
                    parent->getParent()->setRight(parent->getRight());

                oldParent->setParent(parent->getParent());
            }
            
        
        else
            oldParent->setParent(NULL);
        
        parent->setRight(oldParent->getLeft());
        
        if(oldParent->getLeft() != NULL) {
            oldParent->getLeft()->setParent(parent);
        }
        
        oldParent->setLeft(parent);
        parent->setParent(oldParent);
        
        // Afou teleiwsoun oi peristrofes kanw enhmerwseis twn ypswn tou neou korifaioy komvou
        oldParent->getLeft()->updateHeight();
        
        if(oldParent->getRight() != NULL)
            oldParent->getRight()->updateHeight();
        oldParent->updateHeight();
        
    };

    void AVL::firstLeft(Node* parent, Node* oldParent) {
        Node *inserted = oldParent->getRight();
        
        inserted->setParent(parent);
        
    //    parent->setLeft(inserted);
        
        if(inserted->getLeft() != NULL)
            inserted->getLeft()->setParent(oldParent);
        
        oldParent->setRight(inserted->getLeft());
        
        oldParent->setParent(inserted);
        inserted->setLeft(oldParent);
        

        inserted->setLeft(oldParent);
        parent->setLeft(inserted);
        
        // Apo afto to shmeio kai panw ksekinaei h panw deksia peristrofh
         parent->setLeft(inserted->getRight());
        
        if(parent->getLeft() != NULL)
            inserted->getRight()->setParent(parent);
        if(parent->isLeft() && parent->getParent() != NULL) {
            parent->getParent()->setLeft(inserted);
            inserted->setParent(parent->getParent());
        }
        else {
            if(parent->isRight() && parent->getParent() != NULL) {
                parent->getParent()->setRight(inserted);
                inserted->setParent(parent->getParent());

            }
            else {
                inserted->setParent(NULL);
                this->root = inserted;
            }
       }
        inserted->setRight(parent);
        parent->setParent(inserted);
        
        oldParent->updateHeight();
        parent->updateHeight();
        inserted->updateHeight();
        
    }; 


    void AVL::firstRight(Node* parent, Node* oldParent) {
        Node* inserted = oldParent->getLeft();
        
        inserted->setParent(parent);
        oldParent->setLeft(inserted->getRight());
        
        if(inserted->getRight() != NULL)
            inserted->getRight()->setParent(oldParent);
        
        inserted->setRight(oldParent);
        oldParent->setParent(inserted);
        
        
        // Apo afto to shmeio kai panw ksekinaei h panw aristerh
        parent->setRight(inserted->getLeft());
         
        if(inserted->getLeft() != NULL)
             inserted->getLeft()->setParent(parent);
         
        if(parent->isLeft() && parent->getParent() != NULL) {
            parent->getParent()->setLeft(inserted);
            inserted->setParent(parent->getParent());
        }
        else {
            if(parent->isRight() && parent->getParent() != NULL) {
                parent->getParent()->setRight(inserted);
                inserted->setParent(parent->getParent());

            }
            else {
                inserted->setParent(NULL);
                this->root = inserted;
            }
       }
         
        inserted->setLeft(parent);
        parent->setParent(inserted);
        oldParent->updateHeight();
        parent->updateHeight();
        inserted->updateHeight();
        
    };

    void AVL::pre_order(std::ostream& out) {
        Iterator start = begin();
        
        for(int i = 0; i < this->size; i++) {
            
            out.write(((*start).append(" ")).c_str(), (*start).length() + 1);
//            if(i < this->size - 1)
                ++start;
        }
    }

    void AVL::print2DotFile(char* filename) {
        
        string currString = "graph G {\n";
        Node* parent;
        ofstream file;
        Iterator start = begin();
        file.open(filename);
        
        file << currString;
        
        if(this->size == 1) {
            file << *start;
            file << "\n";
            file << "}";
            return;
        }
        
        for(int i = 1; i < this->size; i++) {
            
            ++start;
            parent = start.curr_Node()->getParent();
            
            if(parent != NULL) {
                file << parent->getElement();
                file << " -- ";
            }
            file << (*start);
            file << "\n";
            
        }
        file << "}";
    }

    AVL& AVL::operator =(const AVL& rightAVL) {
        
        Iterator left = rightAVL.begin();
        
        this->del(root);
        delete root;
        this->root = NULL;
        this->size = 0;
        
        for(int i = 0; i < rightAVL.size; i++) {
            
            this->add(*left);
            ++left;
        }
        return *this;
    }

    AVL AVL::operator +(const AVL& avl)  {
        AVL newAvl;
        
        Iterator it = this->begin();
        
        Iterator secIt = avl.begin();
        
        
        for(int i = 0 ; i < this->size; i++) {
            
            newAvl.add(*it);
            ++it;
        }
        
        for(int i = 0; i < avl.size; i++) {
            
            
            newAvl.add(*secIt);
            ++secIt;
        }
        
        return(newAvl);
        
    }

    AVL& AVL::operator+=(const AVL& avl) {
        Iterator it = avl.begin();
        
        for(int i = 0; i < avl.size; i++) {
            this->add(*it);
            ++it;
        }
        
        return *this;
        
    }

    AVL& AVL::operator+=(const string &e) {
        this->add(e);
        
        return *this;
    }

    AVL& AVL::operator-=(const string &e) {
        
        this->rmv(e);
        
        return(*this);
    }

    AVL AVL::operator+(const string& e) {
        
        AVL newAVL;
        
        Iterator it = this->begin();
        
        for(int i = 0; i < this->size; i++) {
            newAVL.add(*it);
//            if(i != this->size)
                ++it;
        }
        
        newAVL.add(e);
        return newAVL;
    }

    AVL AVL::operator-(const string& e) {
        AVL newAVL;
        
        Iterator it = this->begin();
        
        for(int i = 0; i < this->size; i++) {
            newAVL.add(*it);
            ++it;
        }
        newAVL.rmv(e);
        return(newAVL);
    }

    void AVL::del(Node* deletedNode) {
        
        if(deletedNode == NULL)
            return;
        
        
        deletedNode->setParent(NULL);
        del(deletedNode->getLeft());
        deletedNode->setLeft(NULL);
        del(deletedNode->getRight());
        deletedNode->setRight(NULL);

        
    }

    std::ostream& operator <<(std::ostream& out, const AVL& tree) {
        AVL::Iterator start = tree.begin();
        
        for(int i = 0; i < tree.size; i++) {
            
            
            out.write(((*start).append(" ")).c_str(), (*start).length() + 1);
//            if(i < tree.size - 1)
                ++start;
        }
        return(out);
    }

