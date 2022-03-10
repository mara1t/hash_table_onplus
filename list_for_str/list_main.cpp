#include "list.h"

signed main() {

    List lst = {};
    ListCtor(&lst);
/*
    INSERT_AFT(0, 20);
    INSERT_AFT(1, 30);
    INSERT_AFT(2, 15);
    INSERT_AFT(3, 25);
    INSERT_BEF(4, 100);
*/

    ListRealloc (&lst, 10);
    
    
    

    //graph_print(lst);

    ListDtor(&lst);

    return 0;
}