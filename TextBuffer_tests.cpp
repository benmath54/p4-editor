#include "TextBuffer.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(test_line1) {
    TextBuffer buffer;
    buffer.insert('s');
    buffer.insert('t');
    buffer.insert('e');
    buffer.insert('a');
    buffer.insert('d');
    buffer.insert('y');
    buffer.up();
    buffer.backward();
    buffer.backward();
    buffer.backward();
    buffer.backward();
    buffer.up();
    buffer.forward();
    buffer.forward();
    buffer.up();
    buffer.forward();
    buffer.forward();
    buffer.up();
    buffer.insert('\n');
    buffer.backward();
    buffer.backward();
    buffer.insert('\n');
    buffer.up();
    buffer.up();
    buffer.get_column();
    ASSERT_EQUAL(buffer.get_column(),0)
    cout << buffer.stringify() << endl;
}

TEST_MAIN()
