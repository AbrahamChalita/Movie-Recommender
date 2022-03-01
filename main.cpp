#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "Plataforma.h"

using namespace std;

int menu();


int main() {

  int cond;

  while(true){

    cond = menu();
    if (cond != 11){
      Plataforma pl = Plataforma(cond);
      cout << pl << endl;
    }else
    {
      cout << "Bye bye :)" << endl;
      break;
    }
  }
  return 0;
}

int menu(){
  cout << "Choose (number only) how do you want to search what you want to watch: " << endl <<
          "1. Word" << endl <<
          "2. Specific Year" << endl <<
          "3. Genre" << endl <<
          "4. Rating" << endl <<
          "5. Specific Title [==]" << endl <<
          "6. Greater than [x] year: " << endl <<
          "7. Greater than or equal to [x] year" << endl <<
          "8. Lower than [x] year" << endl <<
          "9. Lower than or equal to [x] year" << endl <<
          "10. Year range, between [x] and [y] year." << endl << 
          
          "11. Exit" << endl;

  int selection;
  bool estado = 1;
  while(estado){
    cout << "Selection: ";
    cin >> selection;

    try{
      if(selection == 0){
        throw 0;
      }else if(selection < 0){
        throw "Must be positive, please.";
      }else if (selection > 11){
        throw 10.1;
      }

      estado = 0;
    }

    catch(int cero){
      cout << "Entry = 0 not valid." << endl;
    }catch(const char * edad_negativa){
      cout << edad_negativa << endl;
    }catch(double error_plus_nine){
      cout << "Number not valid" << endl;
    }catch(...){
      cout << "Blue screen!" << endl;
    }

  }

  if(selection == 10){
    cout << "Enter the first year: " << endl;
  }

  return selection;
}
