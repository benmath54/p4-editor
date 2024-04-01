#include "TextBuffer.hpp"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

TextBuffer::TextBuffer()
:data(CharList()), cursor(data.begin()), row(1), column(0),index(0){}

bool TextBuffer::forward(){
    if(cursor == data.end()){
      return false;
    }
    else if(*cursor == '\n'){
      column = 0;
      row++;
    }
    else{column++;}
    cursor++;
    index++;
    return true;
  }

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor one position backward and returns true,
  //          unless the cursor is is already at the first character in
  //          the buffer, in which case this does nothing and returns false.
  //HINT:     Implement and use the private compute_column() member
  //          function to compute the column when moving left from the
  //          beginning of a line to the end of the previous one.
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  bool TextBuffer::backward(){
    if(cursor == data.begin()){
      return false;
    }
    cursor--;
    if(*cursor == '\n'){
      row--;
      }
    column = compute_column();
    index--;
    return true;
  }

  //MODIFIES: *this
  //EFFECTS:  Inserts a character in the buffer before the cursor position.
  //          If the cursor is at the past-the-end position, this means the
  //          inserted character is the last character in the buffer.
  //          The cursor remains in the same place as before the insertion.
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  void TextBuffer::insert(char c){
    data.insert(cursor,c);
    if(c == '\n'){
      row++;
      column = 0;
      index++;
    }
    else{
      column++;
      index++;
    }
  }

  //MODIFIES: *this
  //EFFECTS:  Removes the character from the buffer that is at the cursor and
  //          returns true, unless the cursor is at the past-the-end position,
  //          in which case this does nothing and returns false.
  //          The cursor will now point to the character that was after the
  //          deleted character, or the past-the-end position if the deleted
  //          character was the last one in the buffer.
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  bool TextBuffer::remove(){
    if(cursor == data.end()){
      return false;
    }
    char c = *cursor;
    cursor = data.erase(cursor);
    if(c == '\n'){
      index--;
      row--;
      column = compute_column();
    }
    return true;
  }

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the start of the current row (column 0).
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  void TextBuffer::move_to_row_start(){
    while(column > 0){
      column--;
      cursor--;
      index--;
    }
  }

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the end of the current row (the
  //          newline character that ends the row, or the past-the-end
  //          position if the row is the last one in the buffer).
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  void TextBuffer::move_to_row_end(){
    while(cursor != data.end()&& *cursor != '\n'){
      cursor++;
      column++;
      index++;
    }
  }

  //REQUIRES: new_column >= 0
  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the given column in the current row,
  //          if it exists. If the row does not have that many columns,
  //          moves to the end of the row (the newline character that
  //          ends the row, or the past-the-end position if the row is
  //          the last one in the buffer).
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  void TextBuffer::move_to_column(int new_column){
    assert(new_column >= 0);
    if(new_column > column){
      while(column != new_column&&*cursor != '\n'&&cursor != data.end()){
        column++;
        index++;
        cursor++;
      }
    }
    else if(new_column < column){
      while(column != new_column&&cursor != data.begin()){
        column--;
        index--;
        cursor--;
      }
    }
  }

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the previous row, retaining the
  //          current column if possible. If the previous row is
  //          shorter than the current column, moves to the end of the
  //          previous row (the newline character that ends the row).
  //          Does nothing if the cursor is already in the first row.
  //          Returns true if the position changed, or false if it did
  //          not (i.e. if the cursor was already in the first row).
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  bool TextBuffer::up(){
    int current_column = column;
    Iterator it1 = cursor;
    int count = 0;
    int dummy = 0;
    if(it1 == data.end()){
      it1--;
      dummy++;
    }
    while(it1 != data.begin()&& *it1 != '\n'){
      it1--;
      count++;
    }
    if(it1 == data.begin()){return false;}
    cursor = it1;
    cursor--;
    column = compute_column()+dummy;
    index = index -count;
    row--;
    if(current_column > column){
      return true;
    }

    while(cursor != data.end() && column != current_column && *cursor != '\n'){
      cursor--;
      column--;
      index--;
    } 
    return true;
  }

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the next row, retaining the current
  //          column if possible. If the next row is shorter than the
  //          current column, moves to the end of the next row (the
  //          newline character that ends the row, or the past-the-end
  //          position if the row is the last one in the buffer). Does
  //          nothing if the cursor is already in the last row.
  //          Returns true if the position changed, or false if it did
  //          not (i.e. if the cursor was already in the last row).
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  bool TextBuffer::down(){
    int current_column = column;
    Iterator it1 = cursor;
    int count = 0;
    while(*it1 != '\n'&&it1 != data.end()){
      it1++;
      count++;
    }
    if(it1 == data.end()){return false;}
    cursor = it1;
    cursor++;
    column = 0;
    index = index + count;
    row++;

    while(column != current_column && cursor != data.end()&& *cursor != '\n'){
      cursor++;
      column++;
      index++;
    } 
    return true;
  }

  //EFFECTS:  Returns whether the cursor is at the past-the-end position.
  bool TextBuffer::is_at_end() const{
    return cursor == data.end();
  }

  //REQUIRES: the cursor is not at the past-the-end position
  //EFFECTS:  Returns the character at the current cursor
  char TextBuffer::data_at_cursor() const{
    assert(cursor != data.end());
    return *cursor;
  }

  //EFFECTS:  Returns the row of the character at the current cursor.
  int TextBuffer::get_row() const{
    return row;
  }

  //EFFECTS:  Returns the column of the character at the current cursor.
  int TextBuffer::get_column() const{
    return column;
  }

  //EFFECTS:  Returns the index of the character at the current cursor
  //          with respect to the entire contents. If the cursor is at
  //          the past-the-end position, returns size() as the index.
  int TextBuffer::get_index() const{
    if(cursor == data.end()){
      return size();
    }
    return index;
  }

  //EFFECTS:  Returns the number of characters in the buffer.
  int TextBuffer::size() const{
    return data.size();
  }

  //EFFECTS:  Returns the contents of the text buffer as a string.
  //HINT: Implement this using the string constructor that takes a
  //      begin and end iterator. You may use this implementation:
  //        return std::string(data.begin(), data.end());
  string TextBuffer::stringify() const{
    string s = string(data.begin(),data.end());
    return s;
  }

  //EFFECTS: Computes the column of the cursor within the current row.
  //NOTE: This does not assume that the "column" member variable has
  //      a correct value (i.e. the row/column INVARIANT can be broken).
  int TextBuffer::compute_column() const{
    Iterator it1 = cursor;
    Iterator it2 = cursor;
    if(it2 != data.begin()){it2--;}
    int col = 0;
    if(*it1 == '\n'){
      it1--;
      col++;
      if(it2 != data.begin()){it2--;}
    }
    while(it1 != data.begin()&&*it2 != '\n'){
      it1--;
      col++;
      if(it2 != data.begin()){it2--;}
    }
    return col;
  }