#include "users.h"
#if __has_include(<Arduino.h>)
#include <Arduino.h>
#endif

void User::show() {
#if __has_include(<Arduino.h>)
    // Print the array in hex format
    for (auto elem : UID) {
        Serial.print("0x");
        if (elem < 0x10) {
            Serial.print("0"); // Print leading zero for single digit hex values
        }
        Serial.println(elem, HEX); // Print each element in hex
    }
#endif
}

Users::Users(){ //This actually already happened in the constructor of Users
    for (IDXt i = 0; i < N_USERS; ++i)
    {
        users[i] = User(BADUSER);
    }
}

bool Users::find(UIDt uid){
    for(User &user:users)
    {
        if(user == User(uid)){
            return true;
        }
    }
    return false;
}

bool Users::add(UIDt uid){
    if(find(uid))
    {
      return false;
    }
    for(User &user:users)
    {
        if(user == User(BADUSER)){
            user = User(uid);
            return true;
        }
    }
    return false;
}

bool Users::del(UIDt uid){
    for(User &user:users)
    {
        if(user == User(uid)){
            user = User(BADUSER);
            return true;
        }
    }
    return false;
}

void Users::show(){
  for(User &user:users)
  {
    if(!(user == User(BADUSER)))
    {
      user.show();
    }
  }
}