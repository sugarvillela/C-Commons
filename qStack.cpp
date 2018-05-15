/* By David Swanson https://github.com/sugarvillela */
#include "qStack.h"
void test_qstack_stack(){
    cout << "Test stack: Pushing five! four three two one zero" << endl;
    QStack< string > Q;
    Q.push("five!");
    Q.push("four ");
    Q.push("three ");
    Q.push("two ");
    Q.push("one ");
    Q.push("zero ");
    cout << "Top element is: " << Q.top() << endl;
    cout << "Start popping:" << endl;
    while( !Q.empty() ){
        cout << Q.pop();
    }
    cout << endl << endl;
}
void test_qstack_itr(){
    cout << "Test itr: Pushing five! four three two one zero" << endl;
    QStack< string > Q;
    Q.push("five!");
    Q.push("four ");
    Q.push("three ");
    Q.push("two ");
    Q.push("one ");
    Q.push("zero ");
    cout << "Start iterating:" << endl;
    Q.reset();          //set 'next' pointer to top element
    string returnMe=""; //for return value; Q.next returns 0 when done
    while( Q.next( returnMe ) ){
        cout << returnMe;
    }
    cout << endl << endl;
}
void test_qstack_at(){
    cout << "Test at() function: Pushing five! four three two one zero" << endl;
    QStack< string > Q;
    Q.push("five!");
    Q.push("four ");
    Q.push("three ");
    Q.push("two ");
    Q.push("one ");
    Q.push("zero ");
    cout << "Using at() 0 through 5:" << endl;
    int i=0;
    string returnMe=""; //for return value; Q.at returns 0 when out of range
    while( Q.at( i, returnMe ) ){
        cout << i << ":" << returnMe << endl;
        i++;
    }
    cout << endl << endl;
}
void test_qstack_queue(){
    cout << "Test queue functions: Pushing five! four three two one zero" << endl;
    QStack< string > Q;
    Q.enqueue("five!");
    Q.enqueue("four ");
    Q.enqueue("three ");
    Q.enqueue("two ");
    Q.enqueue("one ");
    Q.enqueue("zero ");
    cout << "Bottom element is: " << Q.bottom() << endl;
    cout << "Start dequeueing:" << endl;
    while( !Q.empty() ){
        cout << Q.dequeue();
    }
    cout << endl << endl;
}
