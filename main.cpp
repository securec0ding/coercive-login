#include <iostream>
#include <iomanip>
#include <signal.h>
#include <string>

using namespace std;


// -------------------------------------
// Access Violation Handler Code
// -------------------------------------
// Makes erroneous user attempts
// a little more user friendly (by not crashing)
// -------------------------------------
typedef void(*SignalHandlerPointer)(int);

void SignalHandler(int signal)
{
  cout << "Cheater. You are getting close..." << endl;
  exit(0);
}

void handleAccessViolations() {
  SignalHandlerPointer previousHandler;
  previousHandler = signal(SIGSEGV, SignalHandler);
}

// -------------------------------------
// Start Admin and Guest Data Structures
// -------------------------------------
// There are 5 administrators and 5 guests.
// The user is *supposed* to be able to
// log in *only* as a guest.
// -------------------------------------
struct user {
  const char* name;
  enum usertype {admin, guest} type;
};

user admins[] = {
  {"John Galt", user::admin},
  {"Vader",     user::admin},
  {"Luke",      user::admin},
  {"TARS",      user::admin},
  {"Maximus",   user::admin}
};

int numAdmins = 5;
int numGuests = 5;

user guests[] = {
  {"Plebian",   user::guest},
  {"Peasant",   user::guest},
  {"Underling", user::guest},
  {"Follower",  user::guest},
  {"Sycophant", user::guest}
};
// -------------------------------------
// End Admin and Guest Data Structures
// -------------------------------------


int main(int argc, char *argv[])
{
  // set up graceful memory access violation handler
  handleAccessViolations();

  cout << "  Guest List  " << endl;
  cout << "--------------" << endl;
  for (int i = 0; i < numGuests; ++i){
    printf("%d) %s \n", i + 1, guests[i].name);
  }

  // get guest id from user
  cout << endl << "Welcome! Please enter a guest ID to log in: ";

  // convert to id from string
  // std::setw(3) limits user to 3 characters of input (including terminator)
  // to prevent overflow attacks
  char input[3];
  cin >> setw(3) >> input;
  unsigned int guestID = stoi(input);

  cout << "Attempting to log in in as guest " << guestID << "..." << endl << endl;

  // calculate idx into guest array
  int guestIdx = guestID - 1;

  // if guest id is an overflow attempt, don't allow it!
  if (guestIdx >= numGuests) {
    cout << "Overflow attack detected. Nice try. You lose!" << endl << endl;
    exit(0);
  }

  // get guest from the guests array
  user u = guests[guestIdx];

  // greet the guest
  cout << u.name << ", welcome back!" << endl;

  // check if user is an admin
  if (u.type == user::admin) {
    cout << "Nice job. You won!" << endl << endl;
    exit(0);
  }

  // user is a guest
  cout << "Guests aren't welcome. You lost! Please try again." << endl << endl;
}