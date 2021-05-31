#include <bits/stdc++.h>

using namespace std;

struct Person {
	string name;
	int number;
	vector<string> email;
	vector<int> connections;
};

struct Mail {
	string mail;
	int position;
};

int main() {
	ifstream fin("adrese.in");
	ofstream fout("adrese.out");

	int n;
	fin >> n;

	string name_aux;
	string email_aux;

	vector<Person *> persoane(n);
	vector<Mail *> mails;
	int dim = 0;
	for(int i = 0; i < n; i++) {
		Person *pers_aux = new Person;
		Mail *mail_aux = new Mail;
		fin >> pers_aux->name;
		fin >> pers_aux->number;
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
			// cautam mail-ul
			if (i != mails[j]->position &&
				find(persoane[i]->connections.begin(), persoane[i]->
					connections.end(), mails[j]->position) ==
				 	persoane[i]->connections.end() &&
				find(persoane[i]->email.begin(), persoane[i]->email.end(),
					mails[j]->mail) != persoane[i]->email.end()) {
				for (int k = persoane[mails[j]->position]->number - 1; k >= 0; k--) {
					if (find(persoane[i]->email.begin(), persoane[i]->email
						.end(), persoane[mails[j]->position]->email[k])
						== persoane[i]->email.end()) {
						// actualizam vectorul de persoane
						persoane[i]->email.push_back(persoane[mails[j]->position]->email[k]);
						persoane[i]->number = persoane[i]->number + 1;
					}
					persoane[mails[j]->position]->email.pop_back();
				}
				nr_rez--;

				persoane[mails[j]->position]->connections.push_back(i);
				persoane[i]->connections.push_back(mails[j]->position);
				persoane[mails[j]->position]->number = 0;
				persoane[mails[j]->position]->name = "deleted";
			}
		}
		sort(persoane[i]->email.begin(), persoane[i]->email.end());
	}

	fout << nr_rez << "\n";
	sort(persoane.begin(), persoane.end(), [](Person *a, Person *b)
		{if (a->number == b->number) {
			return (a->name < b->name);
		} else {
			return (a->number < b->number);
		}});

	for (int i = 0; i < (int)persoane.size(); i++) {
		if(persoane[i]->number == 0) {
			continue;
		}

		fout << persoane[i]->name << " " << persoane[i]->number << "\n";
		for (int j = 0; j < (int)persoane[i]->email.size(); j++) {
			fout << persoane[i]->email[j] << "\n";
		}
	}
	return 0;
}
