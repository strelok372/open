#include <iostream>
#include <string.h>
#include <vector>
#include <conio.h>
#include <fstream>
#include <cctype>
#include <string>
#include <iomanip>
#include <sstream>

class record{
protected:
int phone;
friend std::ostream& operator<<(std::ostream &is, record &r) { return r.prin(is); };
virtual std::ostream& prin(std::ostream& is) { 
	std::cout << phone; 
	return is; 
};
public:
	record():phone(0) {};

	record(int p) :phone(p) {};
};

class individual: public record {
	std::string fullname;
	int passport;
public:
	virtual std::ostream& prin(std::ostream& is) override
	{
	std::cout << fullname << " | " << std::showpos << phone << std::noshowpos << " | " << passport << "\n";
	return is;
	}

	individual():fullname(""), passport(0) {};

	individual(int pa, std::string fn, int p) :fullname(fn), passport(pa), record(p) {};

	char returnletter(int a) {
		return fullname[a];
	};

	const char* returnfullname() {
		return fullname.c_str();
	}
};

class entity: public record{
	std::string name;
	int inn;
public:
	virtual std::ostream& prin(std::ostream& is) override
	{
		std::cout << name << " | " << std::showpos << phone << std::noshowpos << " | " << inn << "\n";
		return is;
	}
	entity():name(""), inn(0) {};
	entity(int inn, std::string fn, int p) : name(fn), inn(inn), record(p) {};
	char returnletter(int a) {
		return name[a];
	};
	const char* returnfullname() {
		return name.c_str();
	}
};

class direc
{
	int indcount = 0;
	int entcount = 0;
	individual *ind = 0;
	entity *ent = 0;

public:
	direc():ind(new individual[indcount]),ent(new entity[indcount]) {};

	~direc() { 	delete[] ind;	delete[] ent;	} //надо добавить сохранение в файл
	
	bool deleterecord(int recnum) {
		if (recnum <= indcount && recnum > 0) {
			individual *ind_temp = new individual[indcount-1];
			for (int i = 0; i < recnum; i++) {
				ind_temp[i] = ind[i];
			}
			for (int i = recnum + 1; i <= indcount; i++ ) {
				ind_temp[i - 1] = ind[i];
			}
			delete[] ind;
			ind = ind_temp;
			return true;
	}
		else if (recnum <= (indcount + indcount) && recnum > 0){
			entity *ent_temp = new entity[entcount-1];
			for (int i = 0; i < recnum; i++) {
				ent_temp[i] = ent[i];
			}
			for (int i = recnum + 1; i <= entcount; i++) {
				ent_temp[i - 1] = ent[ i];
			}
			delete[] ent;
			ent = ent_temp;
			return true;
		}
		else return false;
	};

	void sortdir(bool a) {
		if (a = true) {
			if (indcount > 2) {
				for (int i = 0; i < indcount - 1; i++)
					if (_stricoll(ind[i].returnfullname(), ind[i + 1].returnfullname()) == 1)
					{
						individual intemp = ind[i];
						ind[i] = ind[i + 1];
						ind[i + 1] = intemp;
					}
			}
			else
			{
				std::cout << "ERROR SORT, TOO LOW INDIVIDUAL RECORDS"; //Зачем вообще тут проверка?
			}
		}
		else
		{
			if (entcount > 2) {
				for (int i = 0; i < entcount - 1; i++)
					if (_stricoll(ent[i].returnfullname(), ent[i + 1].returnfullname()) == 1)
					{
						entity entemp = ent[i];
						ent[i] = ent[i + 1];
						ent[i + 1] = entemp;
					}
			}
			else
			{
				std::cout << "ERROR SORT, TOO LOW ENTITY RECORDS";
			}
		}
		
	
	}
	
	bool findrecord(char name[], int tp) {
		if (tp == 1) {
			int startnum = 0; //стартовая позиция
			int count = indcount; //количество записей
			int a = sizeof(name)-1;
			for (int index = 0; index < a; index++) { //поиск по заданным символам

				for (int i = startnum; i < count; i++) { //поиск стартовой позиции
					if (ind[i].returnletter(index) == name[index]) {
						startnum = i;
						break;
					}
					else return false;
				}

				int temp = count;
				count = 0; //обнуление счётчика

				for (int i = startnum; i < temp + startnum; i++) //подсчёт подходящих записей
					if (ind[i].returnletter(index) == name[index])
						count++;
			}
			showall(1, startnum, count);
			return true;
		}
		else 
		{
			int startnum = 0; //стартовая позиция
			int count = entcount; //количество записей
			int a = sizeof(name)-1;
			for (int index = 0; index < a; index++) { //поиск по заданным символам

				for (int i = startnum; i < count; i++) { //поиск стартовой позиции
					if (ent[i].returnletter(index) == name[index]) {
						startnum = i;
						break;
					}
					else return false;
				}

				int temp = count;
				count = 0; //обнуление счётчика

				for (int i = startnum; i < temp + startnum; i++) //подсчёт подходящих записей
					if (ent[i].returnletter(index) == name[index])
						count++;
			}
			showall(0, startnum, count);
			return true;
		}
	}

	//шаблон с T = параметром indcount|entcount?
	void addrecord(int type, int phone, int doc, std::string name) {
		if (type == 1)
		{	
			if (indcount > 0) {
				++indcount;
				individual* data = ind;
				ind = new individual[indcount];
				for (int index = 0; index < indcount; index++)
					ind[index] = data[index];
				individual indiv(phone, name, doc);
				ind[indcount - 1] = indiv;
				delete[] data;
			}			
			else
			{
				++indcount;
				ind = new individual[indcount];
				individual indiv(phone, name, doc);
				ind[indcount - 1] = indiv;
			}
			if (indcount >= 2)	sortdir(1); //сортировка
		}
		else {
			if (entcount > 0) {
				++entcount;
				entity* data = ent;
				ent = new entity[entcount];
				for (int index = 0; index < entcount; index++)
					ent[index] = data[index];
				entity entit(phone, name, doc);
				ent[entcount - 1] = entit;
				delete[] data;
			}
			else {
				++entcount;
				ent = new entity[entcount];
				entity entit(phone, name, doc);
				ent[entcount - 1] = entit;
			}			
			if (entcount >= 2) sortdir(0);
		}
	};

	bool showall() {
		system("cls");
		int nums = 0;
		if (indcount == 0 && entcount == 0)
			return false;
		if (indcount > 0) {
			std::cout << "==========INDIVIDUAL==========\n";
			for (int i = 0; i < indcount; i++) {
				nums++;
				std::cout << nums << ") " << ind[i] << "\n";
				return true;
			};
		}			
		if (entcount > 0) {
			std::cout << "============ENTITY============\n";
			for (int i = 0; i < entcount; i++) {
				nums++;
				std::cout << nums << ") " << ent[i] << "\n";
				return true;
			};
		}
		return true;
		std::cout << "\n";
	};
	void showall(bool a, int start, int count) {
		if (a == 1) {
			for (int i = start; i < count+start; i++) {
				std::cout << ind[i] << '\n';
			}
		}
		else {
			for (int i = start; i < count+start; i++) {
				std::cout << ent[i] << '\n';
			}
		}
	}

	int getcount(bool a) {
		if (a == 1)
			return indcount;
		else
			return entcount;
	}
	individual* getind(int a) { return &ind[a]; };
	entity* getent(int a) { return &ent[a]; }

	void setind(individual i, int n) {
		ind[n] = i;
	};
	void setent(entity e, int n) {
		ent[n] = e;
	};
	void setic(int n) { indcount=n; };
	void setec(int n) { entcount=n; };

};

bool addrec(bool a, direc &d) {
	std::string name;
	int phone;
	int doc;
	if (a == 1) {
		while (1) {
			system("cls");
			std::string tempstring;
			std::cout << "To abandon process type ""quit""" << "\n";
			std::cout << "Enter the full name\n";
			//bool a = true;
			std::getline(std::cin, tempstring);
			if (tempstring == "quit") {
				return false;
			}
			//std::cout << tempstring.length();
			/*for (uint32_t i = 0; i < tempstring.length() && a; i++) {
				if (isalpha(name[i]) || name[i] == ' ')
					continue;
				a = false;
			}*/
			//if (a == true) {
				name = tempstring;
				break;
			//}

		}
		while (1) {
			system("cls");
			std::string tempstring;
			std::cout << "To abandon process type ""quit""" << "\n";
			std::cout << "Enter the passport number\n(10 digits neccessary)\n";
			bool a = true;
			//std::cin.getline(tempstring, 14);
			std::cin >> std::setw(11) >> tempstring;
			if (tempstring == "quit") {
				return false;
			}
			//std::cin.clear();
			for (int i = 0; i < 10 && a; i++) {
				if (!isdigit(tempstring[i]))
					a = false;
			}
			if (a == true) {
				std::istringstream ist(tempstring);
				ist >> doc;
				break;
			}
		}
		while (1) {
			system("cls");
			std::string tempstring;
			std::cout << "To abandon process type ""quit""" << "\n";
			std::cout << "Enter the telephone number\n(10 digits neccessary)\n";
			bool a = true;
			//std::cin.getline(tempstring, 14);
			std::cin >> std::setw(11) >> tempstring;
			if (tempstring == "quit") {
				return false;
			}
			std::cin.clear();
			for (int i = 0; i < 10 && a; i++) {
				if (!isdigit(tempstring[i]))
					a = false;
			}
			if (a == true) {
				std::istringstream ist(tempstring);
				ist >> phone;
				break;
			}

		}
		d.addrecord(1, phone, doc, name);
		return true;
	}
	else {
		while (1) {
			system("cls");
			std::string tempstring;
			std::cout << "To abandon process type ""quit""" << "\n";
			std::cout << "Enter the name of organisation\n";
			//bool a = true;
			std::getline(std::cin, tempstring);
			if (tempstring == "quit") {
				return false;
			}
			/*for (uint32_t i = 0; i < tempstring.length() && a; i++) {
				if (!isalpha(name[i]) || name[i] != ' ')
					a = false;
			}*/
			//if (a == true) {
				name = tempstring;
				break;
			//}

		}
		while (1) {
			system("cls");
			std::string tempstring;
			std::cout << "To abandon process type ""quit""" << "\n";
			std::cout << "Enter the INN(10 digits)\n";
			bool a = true;
			std::cin >> std::setw(11) >> tempstring;
			if (tempstring == "quit") {
				return false;
			}
			std::cin.clear();
			for (int i = 0; i < 10 && a; i++) {
				if (!isdigit(tempstring[i]))
					a = false;
			}
			if (a == true) {
				std::istringstream ist(tempstring);
				ist >> doc;
				break;
			}
		}
		while (1) {
			system("cls");
			std::string tempstring;
			std::cout << "To abandon process type ""quit""" << "\n";
			std::cout << "Enter the telephone number(10 digits)\n";
			bool a = true;
			//std::cin.getline(tempstring, 14);
			std::cin >> std::setw(11) >> tempstring;
			if (tempstring == "quit") {
				return false;
			}
			std::cin.clear();
			for (int i = 0; i < 10 && a; i++) {
				if (!isdigit(tempstring[i]))
					a = false;
			}
			if (a == true) {
				std::istringstream ist(tempstring);
				ist >> phone;
				break;
			}

		}
		d.addrecord(0, phone, doc, name);
		return true;
	}
};

int mainmenu(direc& d) {
		int b = 1;
		while (true) {
			system("cls");
			std::cout << "////////////////////////\n" "Welcome to the directory\n" "////////////////////////\n";			

			switch (b)
			{
			case (1):
				std::cout << ">Show all records\nAdd new record\nDelete record\nFind record\nExit\n";				
				break;
			case (2):
				std::cout << "Show all records\n>Add new record\nDelete record\nFind record\nExit\n";
				break;
			case (3):
				std::cout << "Show all records\nAdd new record\n>Delete record\nFind record\nExit\n";
				break;
			case (4):
				std::cout << "Show all records\nAdd new record\nDelete record\n>Find record\nExit\n";
				break;
			case (5):
				std::cout << "Show all records\nAdd new record\nDelete record\nFind record\n>Exit\n";
				break;
		}

			switch (_getch())
			{
			case(72):
				if (b > 1) b--;
				break;

			case(80):
				if (b < 5) b++; 
				break;
			case(13):
				switch(b)
				{
				//================================================================================================
				case(1):
					if (!d.showall()) {
						std::cout << "There are no records yet\n\n";
					}
					while (true) {
						std::cout << "Press ENTER to return in menu\n";
						if (_getch() == 13) break;
					}
					break;
				//================================================================================================
				case(2):
					system("cls");
					std::cout << "What type of record you want to add?\n 1 - Individual person\n 2 - Entity\n";
					int a;
					std::cin >> a;
					switch (a)
					{
					case(1):
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						if (addrec(1, d)) 
						{
							std::cout << "You have successfully add a record\nPress any key to return in menu\n";
						}
						else
						{
							std::cout << "You have cancelled an operation\nPress any key to return in menu\n";
							_getch();
						}
						break;
					case(2):
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						if (addrec(0, d))
						{
							std::cout << "You have successfully add a record\nPress any key to return in menu\n";
						}
						else 
						{
							std::cout << "You have cancelled an operation\nPress any key to return in menu\n";
							_getch();
						}
						break;
					default:
						std::cout << "Wrong type was entered, please try again.\nPress any key to return in menu\n";
						_getch();
						break;
					}	
					break;		
				//================================================================================================
				case(3):
					if (!d.showall()) {
						std::cout << "There are no records yet\n\n";	
						std::cout << "Press ENTER to return in menu\n";
						if (_getch() == 13) break;
					}
					else
					{
						int n;
						std::cout << "Enter the number of the entry to be deleted.\n";
						std::cin >> n;
						if (d.deleterecord(n)) {
							while (true) {
								std::cout << "Record was successfully deleted\nPress ENTER to return in menu\n";
								if (_getch() == 13) break;
							}
						}
						else {
							std::cout << "Number you entered is incorrect\n";
							while (true) {
								std::cout << "Press ENTER to return in menu\n";
								if (_getch() == 13) break;
							}
						}
					}
					break;
				//================================================================================================
				case(4):
					std::cin.ignore(32767, '\n');
					char* temps;
					std::cout << "What type of record you want to find?\n 1 - Individual person\n 2 - Entity\n";
					int n;
					std::cin >> n;
					std::cout << "Type the name you want to find";
					char temp[50];
					std::cin.get(temp, 50);
					temps = new char[std::cin.gcount()];
					//strcpy_s(temps, temp);
					//strcpy_s(temps[std::cin.gcount()], &temp);
					strcpy_s(temps, std::cin.gcount(), temp);
					std::cin.ignore(32767, '\n');
					d.findrecord(temps, n);
					//проверка на введённые данные???
					break;
				//================================================================================================
				case(5):
					system("cls");
					std::cout << "THANKS FOR USING OUR PRODUCT!\nHAVE A NICE DAY!\n";
					return 0;
					break;
				}
			}
		}
	};




void savedir(direc &dircollect) {
	std::ofstream ofs1("data.bin", std::ios::binary | std::ios::out); 
	int tempcount = dircollect.getcount(1);
	ofs1.write((const char*)tempcount, sizeof(int));
		if (ofs1) {
			for (int i = 0; i < tempcount; i++)
				ofs1.write((const char*)dircollect.getind(i), sizeof(individual));
		}
	tempcount = dircollect.getcount(0);
	ofs1.write((const char*)tempcount, sizeof(int));

		if (ofs1) {
			for (int i = 0; i < tempcount; i++)
				ofs1.write((const char*)dircollect.getent(i), sizeof(entity));
		}
		ofs1.close();
};

void startprog(direc &dir) {
	std::ifstream ifs("data.bin", std::ios::binary | std::ios::in);
	if (ifs) {
		int* tempc;
		ifs.read((char*)&tempc, sizeof(tempc));
		dir.setic(*tempc);
		individual tempd;
		for (int i = 0; i < *tempc; i++) {			
			ifs.read((char*)&tempd, sizeof(individual));
			dir.setind(tempd, i);
		}
		ifs.read((char*)&tempc, sizeof(tempc));
		dir.setec(*tempc);
		entity tempent;
		for (int i = 0; i < *tempc; i++) {
			ifs.read((char*)&tempent, sizeof(entity));
			dir.setent(tempent, i);
		}
	}
	ifs.close();
};

int main() {
	direc d;
	//startprog(d);
	mainmenu(d);
	//d.addrecord(1, 83927439, 9974554, "Seoiwrjrewr");
	//d.addrecord(1, 52526234, 234612834, "ihuqngmimvcx");
	//d.addrecord(1, 23153412, 626263, "uciuwmeuieiqu");
	//d.showall();
	//savedir(d);
}

//в перспективе:
//запрет на переопределение
//проверка на нулевое и отрицательное значение
//частично специализированные функции
//массив словарей
//класс умных указателей
//функция выбора словаря
//флаги?

//template<typename T>
//void sro(T *t) {
//	//std::cout << t.returnfullname();
//}
//
//template<>
//void sro(){
//	std::cout << ind.returnfullname();
//}