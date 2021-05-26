#include <bits/stdc++.h>

using namespace std;

struct Person {
	string name;
	int number;
	vector<string> email;
	int total;
	int printed;
	vector<int> connections;
	int connected;
};

struct Mail {
	string mail;
	string name;
	string nr;
	int position;
};

int person_sorter(Person *a, Person *b) {
	if(a->name.compare(b->name) != 0)
		return a->name.compare(b->name);
	else if(a->number > b->number)
		return 1;
	else return -1;
}

int findPersoana(Person *pers, string mail) {
	// for (int i = 0; i <  pers->number; i++) {
	// 	if(pers->email == mail) return 1;
	// }
	// return 0;
	return find(pers->email.begin(), pers->email.end(), mail) != pers->email.end();
}

void printMails( Person *pers) {
	ofstream fout("adrese.out");
	fout<<"anaaaa";
	for (int i = 0 ; i < pers->number; i++) {
		fout << pers->email[i] << "\n";
	}
	pers->printed = 1;
}

int main() {
	ifstream fin("adrese.in");
	ofstream fout("adrese.out");

	int n;
	fin >> n;

	string name_aux;
	int number_aux;
	string email_aux;

	vector<Person *> persoane(n);
	vector<Mail *> mails;
	int dim = 0;
	for(int i = 0; i < n; i++) {
		Person *pers_aux = new Person;
		Mail *mail_aux = new Mail;
		fin >> pers_aux->name;
		fin >> pers_aux->number;
		pers_aux->total = pers_aux->number;
		pers_aux->connected = 0;
		pers_aux->printed = 0;
		mail_aux->name = pers_aux->name;
		mail_aux->nr = pers_aux->number;
		mail_aux->position = i;
		dim = dim + pers_aux->number;
		for (int j = 0; j < pers_aux->number; j++) {
			fin >> email_aux;
			mail_aux->mail = email_aux;
			pers_aux->email.push_back(email_aux);
			mails.push_back(mail_aux);
		}
		sort(pers_aux->email.begin(), pers_aux->email.end());
		persoane[i] = (pers_aux);
	}

	int nr_rez = n;

	for(int i = 0; i < n; i++) {
		for (int j = 0; j < dim; j++) {
			if (i != mails[j]->position &&
				find(persoane[i]->connections.begin(), persoane[i]->connections.end(), mails[j]->position) ==  persoane[i]->connections.end() &&
				find(persoane[i]->email.begin(), persoane[i]->email.end(), mails[j]->mail) != persoane[i]->email.end()) {
					//persoane[i]->email.push_back(mails[j]->mail);
					//persoane[i]->number = persoane[i]->number + persoane[mails[j]->position]->number ; // -1 ???
				for (int k = persoane[mails[j]->position]->number - 1; k >= 0; k--) {
					if(persoane[mails[j]->position]->email[k].compare(persoane[mails[j]->position]->email[k]) != 0) {
						persoane[i]->email.push_back(persoane[mails[j]->position]->email[k]);
						persoane[i]->number = persoane[i]->number + 1;
					}
					persoane[mails[j]->position]->email.pop_back();
				}
				nr_rez--;

				//fout << mails[j]->mail <<" " << i<<" " << mails[j]->position<<"\n";
				persoane[mails[j]->position]->connections.push_back(i);
				persoane[i]->connections.push_back(mails[j]->position);
				persoane[mails[j]->position]->number = 0;
				persoane[mails[j]->position]->name = "deleted";


			}
		}
		sort(persoane[i]->email.begin(), persoane[i]->email.end());
	}

	for (int i = 0; i < n; i++) {
		fout<< persoane[i]->name << "\n";
		for (int j = 0; j < persoane[i]->number; j++) {
			fout <<persoane[i]->email[j] << "\n";
		}
		fout <<" \n";
	}

	fout << nr_rez;
	// int total = n;
	// string rez;
	//vector<Person *> persoane_aux;
//	sort(persoane.begin(), persoane.end(), &person_sorter);
// 	for(int i = 0; i< n;i++) {
// 		for(int j = 0; j< persoane[i]->number; j++) {
// 			fout << persoane[i]->email[j] << "\n";
// 		}
// 		fout << "\n";
// 	}
// 	int aux = 0;
// 	while (aux < n - 1) {
// 		for(int j = 0; j < persoane[aux]->number; j++) {
// 			int aux2 = aux + 1;

// 			fout << findPersoana(persoane[aux2], persoane[aux]->email[j]) << "lalalal " << persoane[aux2]->name << " " <<  persoane[aux]->email[j] << " " << aux2 <<  "\n";
// 			//fout << find(persoane[aux2]->email.begin(), persoane[aux2]->email.end(),persoane[aux]->email[j]) << "balababakbakabk\n";
// 			if (findPersoana(persoane[aux2], persoane[aux]->email[j]) == 1) {
// 				persoane[aux2]->total = persoane[aux2]->total + persoane[aux]->number;
// 				persoane[aux]->total = persoane[aux]->total + persoane[aux2]->number;
// 				persoane[aux2]->connected = persoane[aux]->connected + 1;
// 				persoane[aux]->connected = persoane[aux2]->connected + 1;

// 				persoane[aux2]->connections.push_back(aux);
// 				persoane[aux]->connections.push_back(aux2);
// 			}
// 		}
// 		aux++;
// 	}

// 	aux = 0;
// 	while(aux < n) {
// 		if (persoane[aux]->printed) {
// 			aux ++;
// 		} else {
// 			fout << persoane[aux]->name << " " << persoane[aux]->total << "\n";

// 			for(int j = 0; j < persoane[aux]->connected; j++) {
// 			fout << persoane[aux]->name << " " << persoane[aux]->total << " " << persoane[aux]->connections[j] << "laa\n";

// 				printMails(persoane[(persoane[aux]->connections[j])]);
// 			}
// 			aux++;
// 		}
// 	}
// //	fout << persoane[1]->name;
	return 0;
}