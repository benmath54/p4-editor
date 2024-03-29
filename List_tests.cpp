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

/*
copyctor
assignment
Iterator
op*
op++
++op
op==
op!=
begin
end
erase
insert
*/
TEST_MAIN()
