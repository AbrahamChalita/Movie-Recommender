#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <cstring>
using namespace std;

class Content{
    protected:
        string title, genre;
        
    public:
        Content(string title = " " , string genre = " "){
            this->title = title;
            this->genre = genre;
        }

        Content(const Content& c){
            this->title = c.title;
            this->genre = c.genre;
        }

        virtual string getTitle() const = 0;

        virtual string getGenre() const{
            return genre;
        }
};

class ContDisney : public Content{
    private:
        string plot, runtime, director, actors, country, type,rating;
        int year;
    public:
        ContDisney(string title = "N/A", string plot = "N/A", string type = "N/A", int year = 0, string runtime = "N/A", string genre = "N/A", string director = "N/A", string actors = "N/A", string country = "N/A", string rating = "N/A"):Content(title, genre){
            this->plot = plot;
            this->runtime = runtime;
            this->director = director;
            this->actors = actors;
            this->country = country;
            this->year = year;
            this->type = type;
			this->rating = rating;
        }

        ContDisney(const ContDisney& contenido):Content(contenido.title, contenido.genre){
            this->plot = contenido.plot;
            this->runtime = contenido.runtime;
            this->director = contenido.director;
            this->actors = contenido.actors;
            this->country = contenido.country;
            this->year = contenido.year;
            this->type = contenido.type;
			this->rating = contenido.rating;
            
        }

        string getTitle() const{
            return title;
        }
        string getGenre() const{
            return genre;
        }
	    string getDirector() const{
		    return director;
	    }    
        string getRating() const{
            return rating;
        }
        string getType() const{
		    return type;
	    }
        int getYear()const{
            return year;
        }

        //OPERATORS OVERLOADING
        bool operator==(const ContDisney& contenido)const{
            return title == contenido.getTitle();
        }
        int operator>=(const int contenido) const{
            if(year >= contenido){
                return 1;
            }else{
                return 0;
            }
        }
        int operator>(const int contenido) const{
            if(year > contenido){
                return 1;
            }else{
                return 0;
            }
        }
        int operator<(const int contenido) const{
            if(year < contenido){
                return 1;
            }else{
                return 0;
            }
        }

         int operator<=(const int contenido) const{
            if(year <= contenido){
                return 1;
            }else{
                return 0;
            }
        }

    friend ostream& operator<<(ostream & salida, const ContDisney & contdisney);
};
ostream& operator<<(ostream & salida, const ContDisney & contdisney){
    salida << "Nombre: " << contdisney.title << endl <<
              "Plot: " << contdisney.plot << endl <<
              "Director " << contdisney.director << endl <<
              "Actor: " << contdisney.actors << endl <<
              "Country: " << contdisney.country << endl <<
              "Year: " << contdisney.year << endl <<
              "Genre: " << contdisney.genre << endl <<
              "Duration: " << contdisney.runtime << endl <<
              "Rating: " << contdisney.rating << endl <<
              "Plataforma: Disney+" << endl;
    return salida;
}

class DisneyPlus{
    private:
        vector<ContDisney> contents;
        void cargaDatos(){
            ifstream archivo("disney_plus_shows.csv");
            string title, plot, type, year, runtime, genre, director, actors, country, rating;
            string line;
            getline(archivo, line);

            while (getline(archivo, line)){
                istringstream parsing(line);
                getline(parsing, title, '|');
                getline(parsing, plot, '|');
                getline(parsing, type, '|');
                getline(parsing, year, '|');
                getline(parsing, runtime, '|');
                getline(parsing, genre, '|');
                getline(parsing, director, '|');
                getline(parsing, actors, '|');
                getline(parsing, country, '|');
                getline(parsing, rating, '|');


                int y_asn = strtod(year.c_str(), NULL);
                ContDisney ptemp = ContDisney(title, plot, type, y_asn, runtime, genre, director, actors, country, rating);

                contents.push_back(ptemp);
            }
        } 
    public:
        DisneyPlus(){
            contents = vector<ContDisney>();
            cargaDatos();
        }

        void addToContent(ContDisney content){
            contents.push_back(content);
        }

        // Método que recibe una consulta de tipo string y regresa un vector con los contenidos que tengan el título especificado
        // Se utiliza el método find dentro del ciclo

                vector<ContDisney> searchByTitle(string consulta)const{
            vector<ContDisney> salida = vector<ContDisney>();
            for (int i = 0; i < contents.size(); i++){
                if (contents[i].getTitle().find(consulta) != string::npos){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }

        //Método que recibe una consulta de tipo int y regresa un vector comparando el año del objeto con el especificado
        //Se utiliza la sobrecarga del operador ==
        
				vector<ContDisney> searchByYear(int consulta)const{
            vector<ContDisney> salida = vector<ContDisney>();
            for (int i = 0; i < contents.size(); i++){
                if (contents[i].getYear() == consulta){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }

        // Método que recibe una consulta de tipo string y regresa un vector con los contenidos que tengan el género especificado
        // Se utiliza el método find dentro del ciclo
        

			vector<ContDisney> searchByGenre(string consulta)const{
                consulta[0] = toupper(consulta[0]);
            vector<ContDisney> salida = vector<ContDisney>();
            for (int i = 0; i < contents.size(); i++){
                if (contents[i].getGenre().find(consulta) != string::npos){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }

        // Método que recibe una consulta de tipo string y regresa un vector con los contenidos que tengan el rating especificado
        // Se utiliza el método find dentro del ciclo

				vector<ContDisney> searchByRating(string consulta)const{
            vector<ContDisney> salida = vector<ContDisney>();
            for (int i = 0; i < contents.size(); i++){
                if (contents[i].getRating().find(consulta) != string::npos){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }

        //Método que recibe una consulta de tipo string y regresa un vector comparando el título específico del objeto con el especificado
        //Se utiliza la sobrecarga del operador ==

                vector<ContDisney> searchBySpecific(string consulta)const{
            vector<ContDisney> salida = vector<ContDisney>();
            for (int i = 0; i < contents.size(); i++){
                if (contents[i] == consulta){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }

        //Método que recibe una consulta de tipo int y regresa un vector comparando el año del objeto con el especificado
        //Se utiliza la sobrecarga del operador >

                vector<ContDisney> searchByYbigger(int consulta)const{
            vector<ContDisney> salida = vector<ContDisney>();
            for (int i = 0; i < contents.size(); i++){
                if (contents[i] > consulta){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }

        //Método que recibe una consulta de tipo int y regresa un vector comparando el año del objeto con el especificado
        //Se utiliza la sobrecarga del operador >=

                vector<ContDisney> searchByYbiggerE(int consulta)const{
            vector<ContDisney> salida = vector<ContDisney>();
            for (int i = 0; i < contents.size(); i++){
                if (contents[i] >= consulta){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }

        //Método que recibe una consulta de tipo int y regresa un vector comparando el año del objeto con el especificado
        //Se utiliza la sobrecarga del operador <

                vector<ContDisney> searchByYminus(int consulta)const{
            vector<ContDisney> salida = vector<ContDisney>();
            for (int i = 0; i < contents.size(); i++){
                if (contents[i] < consulta){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }

        //Método que recibe una consulta de tipo int y regresa un vector comparando el año del objeto con el especificado
        //Se utiliza la sobrecarga del operador <=

                vector<ContDisney> searchByYminusEqual(int consulta)const{
            vector<ContDisney> salida = vector<ContDisney>();
            for (int i = 0; i < contents.size(); i++){
                if (contents[i] <= consulta){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }

        //Método que recibe una consulta de tipo int y regresa un vector comparando el año del objeto con el especificado
        //Se utiliza la sobrecarga del operador >=

        vector<ContDisney> searchByYrange(int consulta, int consulta2)const{
            vector<ContDisney> salida = vector<ContDisney>();
            for (int i = 0; i < contents.size(); i++){
                if (contents[i] >= consulta && contents[i] <= consulta2){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }

        friend ostream &operator<<(ostream &salida, const DisneyPlus &disneyplus);
};
ostream &operator<<(ostream &salida, const DisneyPlus &disneyplus){
    if (disneyplus.contents.size() == 0){
        salida << "Empty";
    }else{
        for (int i = 0; i < disneyplus.contents.size(); i++){
            salida << disneyplus.contents[i] << endl;
        }
    }
    return salida;
}




//NEFLISSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
class ContNetflix : public Content{
    private:
        string type, director, country, duration, description, rating;
        int year;
    public:
        ContNetflix(string type = "N/A", string title = "N/A", string director = "N/A", string country = "N/A", int year = 0, string rating = "N/A", string duration = "N/A", string genre = "N/A", string description = "N/A"):Content(title, genre){
            this->type = type;
            this->director = director;
            this->country = country;
            this->year = year;
            this->rating = rating;
            this->duration = duration;
			this->description = description;
			this->rating = rating;
        }

         ContNetflix(const ContNetflix& contenido):Content(contenido.title, contenido.genre){
            this->type = contenido.type;
            this->director = contenido.director;
            this->country = contenido.country;
            this->year = contenido.year;
            this->rating = contenido.rating;
            this->duration = contenido.duration;
			this->description = contenido.description;
			this->rating = contenido.rating;
        }

        string getTitle() const{
            return title;
        }
        string getGenre() const{
            return genre;
        }
	    string getDirector() const{
		    return director;
	    }    
        string getRating() const{
            return rating;
        }
        string getType() const{
		    return type;
	    }
        int getYear() const{
            return year;
        }

         //OPERATORS OVERLOADING
        bool operator==(const string contenido)const{
            return title == contenido;
        }

        int operator>=(const int contenido) const{
            if(year >= contenido){
                return 1;
            }else{
                return 0;
            }
        }
        int operator>(const int contenido) const{
            if(year > contenido){
                return 1;
            }else{
                return 0;
            }
        }
        int operator<(const int contenido) const{
            if(year < contenido){
                return 1;
            }else{
                return 0;
            }
        }

         int operator<=(const int contenido) const{
            if(year <= contenido){
                return 1;
            }else{
                return 0;
            }
        }

        friend ostream& operator<<(ostream & salida, const ContNetflix & contnetflix);
};
ostream& operator<<(ostream & salida, const ContNetflix & contnetflix){
    salida << "Type: " << contnetflix.type << endl <<
              "Title: " << contnetflix.title << endl <<
              "Director: " << contnetflix.director << endl <<
              "Country: " << contnetflix.country << endl <<
              "Year: " << contnetflix.year << endl <<
              "Rating: " << contnetflix.rating << endl <<
              "Duration: " << contnetflix.duration << endl <<
              "Genre: " << contnetflix.genre << endl <<
              "Description: " << contnetflix.description << endl <<
              "Plataforma: Netflix" << endl;
    return salida;
}

class Netflix{
    private:
        vector<ContNetflix> contents;  
        void cargaDatos(){
            ifstream archivo("netflix_titles.csv");
            string type, title, director, country, year, rating, duration, genre, description;
            string line;
            getline(archivo, line);
      
            while(getline(archivo, line)){
                istringstream  parsing(line);
                getline(parsing, type, '|');
                getline(parsing, title, '|');
                getline(parsing, director, '|');
                getline(parsing, country, '|');
                getline(parsing, year, '|');
                getline(parsing, rating, '|');
                getline(parsing, duration, '|');
                getline(parsing, genre, '|');
                getline(parsing, description, '|');

                int y_asn = strtod(year.c_str(), NULL);
                ContNetflix ptemp = ContNetflix(type, title, director, country, y_asn, rating, duration, genre, description);
                contents.push_back(ptemp);
            }
        }   
    public:
        Netflix(){
            contents = vector<ContNetflix>();
            cargaDatos();
        }
        void addToContent(ContNetflix content){
            contents.push_back(content);
        }

        vector<ContNetflix> searchByTitle(string consulta){
            vector<ContNetflix> salida = vector<ContNetflix>();
            for(int i = 0; i < contents.size(); i++){
                if(contents[i].getTitle().find(consulta) != string::npos){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }  
        vector<ContNetflix> searchByYear(int consulta){
            vector<ContNetflix> salida = vector<ContNetflix>();
            for(int i = 0; i < contents.size(); i++){
                if(contents[i].getYear() == consulta){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }
				vector<ContNetflix> searchByGenre(string consulta){
                consulta[0] = toupper(consulta[0]);
            vector<ContNetflix> salida = vector<ContNetflix>();
            for(int i = 0; i < contents.size(); i++){
                if(contents[i].getGenre().find(consulta) != string::npos){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }
			    vector<ContNetflix> searchByRating(string consulta){
            vector<ContNetflix> salida = vector<ContNetflix>();
            for(int i = 0; i < contents.size(); i++){
                if(contents[i].getRating().find(consulta) != string::npos){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }
                 vector<ContNetflix> searchBySpecific(string consulta)const{
            vector<ContNetflix> salida = vector<ContNetflix>();
            for (int i = 0; i < contents.size(); i++){
                if (contents[i] == consulta){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }
                vector<ContNetflix> searchByYbigger(int consulta)const{
            vector<ContNetflix> salida = vector<ContNetflix>();
            for (int i = 0; i < contents.size(); i++){
                if (contents[i] > consulta){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }
                vector<ContNetflix> searchByYbiggerE(int consulta)const{
            vector<ContNetflix> salida = vector<ContNetflix>();
            for (int i = 0; i < contents.size(); i++){
                if (contents[i] >= consulta){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }
                vector<ContNetflix> searchByYminus(int consulta)const{
            vector<ContNetflix> salida = vector<ContNetflix>();
            for (int i = 0; i < contents.size(); i++){
                if (contents[i] < consulta){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }
                vector<ContNetflix> searchByYminusEqual(int consulta)const{
            vector<ContNetflix> salida = vector<ContNetflix>();
            for (int i = 0; i < contents.size(); i++){
                if (contents[i] <= consulta){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }

        vector<ContNetflix> searchByYrange(int consulta, int consulta2)const{
            vector<ContNetflix> salida = vector<ContNetflix>();
            for (int i = 0; i < contents.size(); i++){
                if (contents[i] >= consulta && contents[i] <= consulta2){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }

        friend ostream& operator<<(ostream & salida, const Netflix & netflix);
};
ostream& operator<<(ostream & salida, const Netflix & netflix){
    if(netflix.contents.size() == 0){
        salida << "Empty";
    }
    for(int i = 0; i < netflix.contents.size(); i++){
        salida << netflix.contents[i] << endl;
    }
    return salida;
}

// BIDA OTACOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO

class ContCrunchy : public Content{
    private:
        string episodes, rate;
    public:
        ContCrunchy(string title = "N/A", string episodes = "N/A", string rate = "N/A", string genre = "N/A") : Content(title, genre){
            this->episodes = episodes;
            this->rate = rate;
        }

        ContCrunchy(const ContCrunchy& contenido):Content(contenido.title, contenido.genre){
            this->episodes = contenido.episodes;
            this->rate = contenido.rate;
        }
        
        string getTitle() const{
            return title;
        }  
        string getGenre() const{
            return genre;
        }
        string getEpisodes() const{
            return episodes;
        }
        string getRating() const{
            return rate;
        }

        //OPERATOR OVERLOADING

        bool operator==(const ContCrunchy& contenido)const{
            return title == contenido.getTitle();
        }

        friend ostream &operator<<(ostream &salida, const ContCrunchy & contcrunchy);
};
ostream &operator<<(ostream &salida, const ContCrunchy & contcrunchy){
    salida << "Anime: " << contcrunchy.title << endl 
           << "Episodios: " << contcrunchy.episodes << endl
           << "Rating: " << contcrunchy.rate << endl
           << "Genre: " << contcrunchy.genre << endl
           << "Plataforma: CrunchyRoll" << endl;
    return salida;
}

class Crunchy{
    private:
        vector<ContCrunchy> contents;  
        void cargaDatos(){
            ifstream archivo("Crunchyroll-animes.csv");
            string title, episodes, rating, genre;
            string line;
            getline(archivo, line);
      
            while(getline(archivo, line)){
                istringstream  parsing(line);
                getline(parsing, title, '|');
                getline(parsing, episodes, '|');
                getline(parsing, rating, '|');
                getline(parsing, genre, '|');

                ContCrunchy ptemp = ContCrunchy(title, episodes, rating, genre);
                contents.push_back(ptemp);
            }
        }   
    public:
        Crunchy(){
            contents = vector<ContCrunchy>();
            cargaDatos();
        }
        void addToContent(ContCrunchy content){
            contents.push_back(content);
        }
        vector<ContCrunchy> searchByTitle(string consulta){
            vector<ContCrunchy> salida = vector<ContCrunchy>();
            for(int i = 0; i < contents.size(); i++){
                if(contents[i].getTitle().find(consulta) != string::npos){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }
        vector<ContCrunchy> searchByGenre(string consulta){
            consulta[0] = tolower(consulta[0]);
            vector<ContCrunchy> salida = vector<ContCrunchy>();
            for(int i = 0; i < contents.size(); i++){
                if(contents[i].getGenre().find(consulta) != string::npos){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }
        vector<ContCrunchy> searchByRating(string consulta){
            vector<ContCrunchy> salida = vector<ContCrunchy>();
            for(int i = 0; i < contents.size(); i++){
                if(contents[i].getRating().find(consulta) != string::npos){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }
        vector<ContCrunchy> searchBySpecific(string consulta)const{
            vector<ContCrunchy> salida = vector<ContCrunchy>();
            for (int i = 0; i < contents.size(); i++){
                if (contents[i] == consulta){
                    salida.push_back(contents[i]);
                }
            }
            return salida;
        }


        friend ostream& operator<<(ostream & salida, const Crunchy & crunchy);
};
ostream& operator<<(ostream & salida, const Crunchy & crunchy){
    if(crunchy.contents.size() == 0){
        salida << "Empty";
    }
    for(int i = 0; i < crunchy.contents.size(); i++){
        salida << crunchy.contents[i] << endl;
    }
    return salida;
}


class Plataforma{
  private:
    int condition;
    //string consulta;
    char consulta[100];

    vector<ContDisney> contents;
    vector<ContNetflix> contents2;
    vector<ContCrunchy> contents3;
  public:
    Plataforma(int condition = 1, string consulta = "0"){
      this->condition = condition;

      cout << "What do you want to see?" << endl;
      scanf(" %[^\n]consulta",this->consulta);
      //cin >> this->consulta;
      cout << endl;
  }
  friend ostream& operator<<(ostream & salida, const Plataforma & plataforma);
};
    ostream& operator<<(ostream & salida, const Plataforma & plataforma){

    //Creación de objetos de tipo: ContDisney, ContNetflix y ContCrunchy
    //En conjunto de objetos de tipo: Disney, Netflix y Crunchy
    //Todos en valores por default
     
    ContDisney cd = ContDisney();
    DisneyPlus dp = DisneyPlus();

    ContNetflix cn = ContNetflix();
    Netflix nf = Netflix();

    ContCrunchy cc = ContCrunchy();
    Crunchy cr = Crunchy();

    //Se hace la validación de la elección del usuario y dependiendo de ella
    // se establece el método de búsqueda

      if(plataforma.condition == 1){
            salida << "By name..." << endl << endl;
            vector<ContDisney> contents = dp.searchByTitle(plataforma.consulta);
            vector<ContNetflix> contents2 = nf.searchByTitle(plataforma.consulta);
            vector<ContCrunchy> contents3 = cr.searchByTitle(plataforma.consulta);
            if(contents.empty()){
            cout << "There is NO Disney+ content in this parameter" << endl; 
        }else{
            for(int i = 0; i < contents.size(); i++){
                salida << contents[i] << endl;
            }
        }

        if(contents2.empty()){
            cout << "There is NO Netflix content in this parameter" << endl; 
        }else{
            for(int i = 0; i < contents2.size(); i++){
                salida << contents2[i] << endl;
            }
        }

        if(contents3.empty()){
            cout << "There is NO Crunchy content in this parameter" << endl; 
        }else{
            for(int i = 0; i < contents3.size(); i++){
                salida << contents3[i] << endl;
            }
        }
      } else if(plataforma.condition == 2){
        salida << "By year..." << endl << endl;
        vector<ContDisney> contents = dp.searchByYear(stoi(plataforma.consulta));
        vector<ContNetflix> contents2 = nf.searchByYear(stoi(plataforma.consulta));
        if(contents.empty()){
            cout << "There is NO Disney+ content in this parameter" << endl; 
        }else{
            for(int i = 0; i < contents.size(); i++){
                salida << contents[i] << endl;
            }
        }

        if(contents2.empty()){
            cout << "There is NO Netflix content in this parameter" << endl; 
        }else{
            for(int i = 0; i < contents2.size(); i++){
                salida << contents2[i] << endl;
            }
        }
      } else if(plataforma.condition == 3){
        salida << "By genre..." << endl << endl;
        vector<ContDisney> contents = dp.searchByGenre(plataforma.consulta);
        vector<ContNetflix> contents2 = nf.searchByGenre(plataforma.consulta);
        vector<ContCrunchy> contents3 = cr.searchByGenre(plataforma.consulta);
        if(contents.empty()){
            cout << "There is NO Disney+ content in this parameter" << endl; 
        }else{
            for(int i = 0; i < contents.size(); i++){
                salida << contents[i] << endl;
            }
        }

        if(contents2.empty()){
            cout << "There is NO Netflix content in this parameter" << endl; 
        }else{
            for(int i = 0; i < contents2.size(); i++){
                salida << contents2[i] << endl;
            }
        }

        if(contents3.empty()){
            cout << "There is NO Crunchy content in this parameter" << endl; 
        }else{
            for(int i = 0; i < contents3.size(); i++){
                salida << contents3[i] << endl;
            }
        } 
      } else if(plataforma.condition == 4){
        salida << "By rating..." << endl << endl;
        vector<ContDisney> contents = dp.searchByRating(plataforma.consulta);
        vector<ContCrunchy> contents3 = cr.searchByRating(plataforma.consulta);
        if(contents.empty()){
            cout << "There is NO Disney+ content in this parameter" << endl; 
        }else{
            for(int i = 0; i < contents.size(); i++){
                salida << contents[i] << endl;
            }
        }
        if(contents3.empty()){
            cout << "There is NO Crunchy content in this parameter" << endl; 
        }else{
            for(int i = 0; i < contents3.size(); i++){
                salida << contents3[i] << endl;
            }
        } 
      }else if(plataforma.condition == 5){
        salida << "By Specific Title..." << endl << endl;
        vector<ContDisney> contents = dp.searchBySpecific(plataforma.consulta);
        vector<ContNetflix> contents2 = nf.searchBySpecific(plataforma.consulta);
        vector<ContCrunchy> contents3 = cr.searchBySpecific(plataforma.consulta);
        if(contents.empty()){
            cout << "There is NO Disney+ content in this parameter" << endl; 
        }else{
            for(int i = 0; i < contents.size(); i++){
                salida << contents[i] << endl;
            }
        }

        if(contents2.empty()){
            cout << "There is NO Netflix content in this parameter" << endl; 
        }else{
            for(int i = 0; i < contents2.size(); i++){
                salida << contents2[i] << endl;
            }
        }

        if(contents3.empty()){
            cout << "There is NO Crunchy content in this parameter" << endl; 
        }else{
            for(int i = 0; i < contents3.size(); i++){
                salida << contents3[i] << endl;
            }
        }
      }else if(plataforma.condition == 6){
        salida << "Year > test..." << endl << endl;
        vector<ContDisney> contents = dp.searchByYbigger(stoi(plataforma.consulta));
        vector<ContNetflix> contents2 = nf.searchByYbigger(stoi(plataforma.consulta));
        if(contents.empty()){
            cout << "There is NO Disney+ content in this parameter" << endl; 
        }else{
            for(int i = 0; i < contents.size(); i++){
                salida << contents[i] << endl;
            }
        }

        if(contents2.empty()){
            cout << "There is NO Netflix content in this parameter" << endl; 
        }else{
            for(int i = 0; i < contents2.size(); i++){
                salida << contents2[i] << endl;
            }
        }
      }else if(plataforma.condition == 7){
        salida << "Year >= test..." << endl << endl;
        vector<ContDisney> contents = dp.searchByYbiggerE(stoi(plataforma.consulta));
        vector<ContNetflix> contents2 = nf.searchByYbiggerE(stoi(plataforma.consulta));
        if(contents.empty()){
            cout << "There is NO Disney+ content in this parameter" << endl; 
        }else{
            for(int i = 0; i < contents.size(); i++){
                salida << contents[i] << endl;
            }
        }

        if(contents2.empty()){
            cout << "There is NO Netflix content in this parameter" << endl; 
        }else{
            for(int i = 0; i < contents2.size(); i++){
                salida << contents2[i] << endl;
            }
        }
      }else if(plataforma.condition == 8){
        salida << "Year >= test..." << endl << endl;
        vector<ContDisney> contents = dp.searchByYminus(stoi(plataforma.consulta));
        vector<ContNetflix> contents2 = nf.searchByYminus(stoi(plataforma.consulta));
        if(contents.empty()){
            cout << "There is NO Disney+ content in this parameter" << endl; 
        }else{
            for(int i = 0; i < contents.size(); i++){
                salida << contents[i] << endl;
            }
        }

        if(contents2.empty()){
            cout << "There is NO Netflix content in this parameter" << endl; 
        }else{
            for(int i = 0; i < contents2.size(); i++){
                salida << contents2[i] << endl;
            }
        }
      }else if(plataforma.condition == 9){
        salida << "Year >= test..." << endl << endl;
        vector<ContDisney> contents = dp.searchByYminusEqual(stoi(plataforma.consulta));
        vector<ContNetflix> contents2 = nf.searchByYminusEqual(stoi(plataforma.consulta));
        if(contents.empty()){
            cout << "There is NO Disney+ content in this parameter" << endl; 
        }else{
            for(int i = 0; i < contents.size(); i++){
                salida << contents[i] << endl;
            }
        }

        if(contents2.empty()){
            cout << "There is NO Netflix content in this parameter" << endl; 
        }else{
            for(int i = 0; i < contents2.size(); i++){
                salida << contents2[i] << endl;
            }
        }
      }else if(plataforma.condition == 10){
        int year2;

        //cout << "Year 1: " << endl;
        //cin >> year1;
        cout << "Year 2: " << endl;
        cin >> year2;

        vector<ContDisney> contents = dp.searchByYrange(stoi(plataforma.consulta), year2);
        vector<ContNetflix> contents2 = nf.searchByYrange(stoi(plataforma.consulta), year2);
        

        if(contents.empty()){
            cout << "There is NO Disney+ content in this parameter" << endl; 
        }else{
            for(int i = 0; i < contents.size(); i++){
                salida << contents[i] << endl;
            }
        }

        if(contents2.empty()){
            cout << "There is NO Netflix content in this parameter" << endl; 
        }else{
            for(int i = 0; i < contents2.size(); i++){
                salida << contents2[i] << endl;
            }
        }
      }
      return salida;
}