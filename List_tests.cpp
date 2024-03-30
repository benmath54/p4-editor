#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

TEST(test_list_empty_both){
    List<int> emptylist;
    ASSERT_TRUE(emptylist.empty());

    emptylist.push_front(3);
    ASSERT_FALSE(emptylist.empty());
}

TEST(test_list_size_empty_not){
    List<int> l;
    size_t s = 0;
    ASSERT_EQUAL(l.size(),s);
    
    l.push_back(3);
    l.push_back(3);
    l.push_back(3);
    s = 3;
    ASSERT_EQUAL(l.size(),s);

    l.pop_front();
    l.pop_back();
    s = 1;
    ASSERT_EQUAL(l.size(),s);
}

TEST(test_list_front){
    List<int> l;
    l.push_back(3);
    l.push_back(4);
    l.push_front(2);

    ASSERT_EQUAL(l.front(),2);
    l.pop_back();
    ASSERT_EQUAL(l.front(),2);

    l.pop_front();
    ASSERT_EQUAL(l.front(),3);
}

TEST(test_list_back){
    List<int> l;
    l.push_back(3);
    l.push_back(4);
    l.push_front(2);

    ASSERT_EQUAL(l.back(),4);

    l.pop_front();
    ASSERT_EQUAL(l.back(),4);

    l.pop_back();
    ASSERT_EQUAL(l.back(),3);
}

TEST(test_list_pf){
    List<int> l;
    l.push_front(1);
    ASSERT_EQUAL(l.front(),1);

    l.push_front(3);
    ASSERT_EQUAL(l.front(),3);
    ASSERT_EQUAL(l.back(),1);

    l.push_front(4);
    ASSERT_EQUAL(l.front(),4);
}

TEST(test_list_pb){
    List<int> l;
    l.push_back(1);
    ASSERT_EQUAL(l.front(),1);

    l.push_back(3);
    ASSERT_EQUAL(l.front(),1);
    ASSERT_EQUAL(l.back(),3);

    l.push_back(4);
    ASSERT_EQUAL(l.back(),4);
}

TEST(test_list_popf){
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);

    ASSERT_EQUAL(l.front(),1);
    l.pop_front();
    ASSERT_EQUAL(l.front(),2);
    l.pop_front();
    ASSERT_EQUAL(l.front(),3);
    l.pop_front();
    ASSERT_EQUAL(l.front(),4);
    l.pop_front();
    ASSERT_EQUAL(l.front(),5);
    l.pop_front();
    ASSERT_TRUE(l.empty());
}

TEST(test_list_popb){
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);

    ASSERT_EQUAL(l.back(),5);
    l.pop_back();
    ASSERT_EQUAL(l.back(),4);
    l.pop_back();
    ASSERT_EQUAL(l.back(),3);
    l.pop_back();
    ASSERT_EQUAL(l.back(),2);
    l.pop_back();
    ASSERT_EQUAL(l.back(),1);
    l.pop_back();
    ASSERT_TRUE(l.empty());  
}

TEST(test_list_clear){
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);

    l.clear();
    ASSERT_TRUE(l.empty());  
}

TEST(test_list_copyctor){
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);    

    List<int> copy_l(l);

    ASSERT_EQUAL(copy_l.front(),1);
    copy_l.pop_front();
    ASSERT_EQUAL(copy_l.front(),2);
    copy_l.pop_front();
    ASSERT_EQUAL(copy_l.front(),3);
    copy_l.pop_front();
    ASSERT_EQUAL(copy_l.front(),4);
    copy_l.pop_front();
    ASSERT_EQUAL(copy_l.front(),5);
    copy_l.pop_front();
    ASSERT_TRUE(copy_l.empty());
}

TEST(test_list_copy_null){
    List<int> l;
    List<int> copy_l(l);

    ASSERT_TRUE(copy_l.empty());
}

TEST(test_list_assignment){
    List<int> l;
    l.push_front(1);
    l.push_front(2);
    l.push_front(3);
    l.push_front(4);
    l.push_front(5);    

    List<int> a;
    a.push_back(6);

    a = a;
    ASSERT_EQUAL(a.front(),6);

    a = l;

    ASSERT_EQUAL(a.front(),5);
    a.pop_front();
    ASSERT_EQUAL(a.front(),4);
    a.pop_front();
    ASSERT_EQUAL(a.front(),3);
    a.pop_front();
    ASSERT_EQUAL(a.front(),2);
    a.pop_front();
    ASSERT_EQUAL(a.front(),1);
    a.pop_front();
    ASSERT_TRUE(a.empty());
}

TEST(test_iterator_deref){
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);   

    List<int>::Iterator i = l.begin();
    ASSERT_EQUAL(*i,1);
}

TEST(test_iterator_end){
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);   

    List<int>::Iterator i = l.end();
    --i;
    ASSERT_EQUAL(*i,5);
}

TEST(test_iterator_eq){
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);   
    List<int> copy_l(l);

    List<int>::Iterator it1 = l.begin();
    List<int>::Iterator it2 = copy_l.begin();

    ASSERT_FALSE(it1 == it2);
    it2 = l.begin();
    ASSERT_TRUE(it1 == it2)
}

TEST(test_iterator_neq){
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);   
    List<int> copy_l(l);

    List<int>::Iterator it1 = l.begin();
    List<int>::Iterator it2 = copy_l.begin();

    ASSERT_TRUE(it1 != it2);
    it2 = l.begin();
    ASSERT_FALSE(it1 != it2)
}

TEST(test_iterator_pp){
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(4);
    l.push_back(5);
    l.push_back(6); 
    List<int>::Iterator it1 = l.begin(); 
    ++it1;
    ASSERT_EQUAL(*it1,2);

    ++(*it1);
    ASSERT_EQUAL(*it1,3);
    ASSERT_EQUAL(*(++it1),4);
}

TEST(test_iterator_p_pp){
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(4);
    l.push_back(5);
    l.push_back(6); 
    List<int>::Iterator it1 = l.begin(); 
    it1++;
    ASSERT_EQUAL(*it1,2);

    ASSERT_EQUAL(*(it1++),2);
    ASSERT_EQUAL(*it1,4);
    it1++;
    it1++;
    ASSERT_EQUAL((*it1)++,6);
    ASSERT_EQUAL(*it1,7);
}

TEST(test_iterator_erase){
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5); 
    List<int>::Iterator it1 = l.begin(); 

    for(int i = 2;i <=5;i++){
    List<int>::Iterator it2 = l.erase(it1);
    ASSERT_EQUAL(*it2,i);
    it1 = it2;
    }
    l.erase(it1);
    ASSERT_TRUE(l.empty());
}

TEST(test_iterator_erase_end){
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5); 
    List<int>::Iterator it1 = l.end();
    it1--; 
    ASSERT_EQUAL(*it1,5);

    List<int>::Iterator it2 = l.erase(it1);
    it2--;
    ASSERT_EQUAL(*it2,4);
    it1 = it2;

    it2 = l.erase(it1);
    it2--;
    ASSERT_EQUAL(*it2,3);
    it1 = it2;

    it2 = l.erase(it1);
    it2--;
    ASSERT_EQUAL(*it2,2);
    it1 = it2;

    it2 = l.erase(it1);
    it2--;
    ASSERT_EQUAL(*it2,1);
    it1 = it2;
}

TEST(test_iterator_insert){
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5); 
    List<int>::Iterator it1 = l.begin();

    List<int>::Iterator it2 = l.insert(it1,0);

    ASSERT_EQUAL(*it2,*(l.begin()))
    l.erase(it2);
    ASSERT_EQUAL(*it1,1);

    it1 = l.end();
    it2 = l.insert(it1,6);
    it1 = l.end();
    it1--;
    ASSERT_EQUAL(*it1,6);
}

TEST(test_iterator_insert_empty){
    List<int> l;
    List<int>::Iterator it1 = l.begin();
    List<int>::Iterator it2 = l.insert(it1,0);
    ASSERT_EQUAL(*it2,*(l.begin()))
}
TEST_MAIN()
